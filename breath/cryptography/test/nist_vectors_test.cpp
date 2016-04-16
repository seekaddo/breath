// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//      Tests the SHA-1 implementation with the test vectors
//      described at <http://www.nsrl.nist.gov/testdata/>.
//

#include "breath/cryptography/sha1_hasher.hpp"
#include "breath/cryptography/digest.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/time/c_clock_timer.hpp"
#include "breath/environment/find_environment_string.hpp"
#include "breath/time/windows_only/performance_counter_timer.hpp"
#include "breath/cryptography/sha512_hasher.hpp"

#include <algorithm>
#include <string>

#include <istream>
#include <ostream>
#include <fstream>
#include <iostream>
#include <sstream>


namespace {

    template< typename T >
    T
    from_string( std::string const & s )
    {
        T t ;
        std::istringstream ss( s ) ;
        ss >> t ;
        return t ;
    }

    template< typename T >
    std::string
    to_string( T const & t )
    {
        std::ostringstream ss ;
        ss << t ;
        return ss.str();
    }




    class nist_file
    {
        std::ifstream m_stream;

        template< typename T >
        friend nist_file & operator>>( nist_file &, T & t );

    public:
        explicit nist_file( const char * filename );
        bool good() const;
        bool new_section();

    };

    nist_file::nist_file( const char * filename )
    {
        std::string const 
                        breath_root( breath::find_environment_string( "BREATH_ROOT" ).value() ) ;
        std::string const
                        subdir( breath_root + "/breath/cryptography/test/nist_vectors/" );
        m_stream.open( ( subdir + filename ).c_str() );
        if ( m_stream )
        {
            for ( std::string s; s != "D>"; ) {
                m_stream >> s;
            }
        }

        if ( m_stream.rdstate() & ( std::ios::failbit | std::ios::eofbit ) )
            throw std::ios::failure( "cannot construct nist_file object" );
        
    }

    bool nist_file::good() const
    {
        return m_stream.good();
    }

    bool nist_file::new_section()
    {
        for ( std::string s; s != "D>" && m_stream; ) {
            m_stream >> s;
        }

        return m_stream.good();
    }

    template< typename T >
    nist_file & operator>>( nist_file & f, T & t )
    {
        f.m_stream >> t;
        return f;
    }

    class montecarlo_test
    {
        breath::sha1_hasher m;
        int m_count;
        typedef breath::sha1_engine::word_type word_type;
        typedef breath::sha1_engine::byte_type byte_type; // gps esporre dall'hasher?
    public:
        montecarlo_test() : m_count( 0 )
        {}

        int get_count()
        {
            return m_count;
        }

        void init( const std::string & seed ) // gps come la chiamo (vedi rnd)
        {
            m.append( seed.begin(), seed.end() );
        }

        breath::sha1_digest next()
        {
            breath::sha1_digest result( m /* bogus argument */ );
            const word_type tot( 50 * 1000 );
            for ( word_type i( 1 ); i <= tot; ++i )
            {
                for ( byte_type a( 1 ); a <= m_count / 4 + 3; ++a )
                    m.push_back( '\0' );

                m.push_back( static_cast< char >( ( i >> 24 ) & 0xff ) );
                m.push_back( static_cast< char >( ( i >> 16 ) & 0xff ) );
                m.push_back( static_cast< char >( ( i >>  8 ) & 0xff ) );
                m.push_back( static_cast< char >( ( i       ) & 0xff ) );

                // our "moral equivalent" of m = SHA1( m )
                result = breath::sha1_digest( m );
                m = breath::sha1_hasher( result.begin(), result.end() );

            }

            ++m_count;
            return result;
        }
    
    };



    std::string read_compact_string( nist_file & messages, int z )
    {
        bool b;
        messages >> b;

        std::string msg;
        char curr( 0 );
        unsigned mask = 128; // gps
        for ( int i = 0; i < z; ++i )
        {
            unsigned n;
            messages >> n;

            while( n-- > 0 )
            {
                if ( b )
                    curr |= mask;

                mask /= 2;
                if ( mask == 0 )
                    msg += curr, curr = 0, mask = 128;
            }

            b = !b;
        }

        return msg;
     }

}


void tests()
{
    using namespace breath;

    nist_file messages( "byte-messages.sha1" );
    nist_file hashes  ( "byte-hashes.sha1" );

    int total = 0;
    int failed = 0;

    static const struct { int section; bool pseudorandom; } section_types[]
    = {
        { 0, false },
        { 1, false },
        { 2, true  }
    };

    const int sections( sizeof section_types / sizeof section_types[ 0 ] );

    std::string calculated;
    std::string msg;
    montecarlo_test montecarlo_harness;

    for ( int sn( 0 ); sn < sections && hashes.good() ; /*++sn*/ )
    {
        bool montecarlo_section( section_types[ sn ].pseudorandom );
        if ( /*!montecarlo_section ||*/ montecarlo_harness.get_count() == 0 )
        {
            // terminator found?
            //
            std::string s;
            messages >> s;
            if ( s == "<D" )
            {
                messages.new_section();
                hashes.new_section();
                ++sn;
                continue;
            }

            int z( from_string< int >( s ) );

            if ( montecarlo_section )
            {
                if ( montecarlo_harness.get_count() == 0 ) {
                    
                    msg = read_compact_string( messages, z );
                    BREATH_ASSERT( 8 * msg.length() == 416 );
                    
                    //----------
                    //msg = "8BFD162CB9D3B04DCB7E54B4DDB2B5D8D9C899F8"; // gps temp
                    //--------------------

                    montecarlo_harness.init( msg );
                }
            }
            else
            {
                msg = read_compact_string( messages, z );
            }

            std::string dummy;
            messages >> dummy; // skip terminator
        }


        std::string expected;
        hashes >> expected;
        if ( expected == "<D" )
            break; // done!

        std::string unused;
        hashes >> unused; // terminator

        if ( hashes.good() )
            ++total;

        calculated = to_string(
            montecarlo_section?
                montecarlo_harness.next()
              : make_digest( sha1_hasher( msg.begin(), msg.end() ) )
            );

        if ( calculated != expected )
        {
            ++failed;
            std::clog << "Failure on test vector # " << total << '\n';
            std::clog << "\tCalculated: " << calculated << '\n';
            std::clog << "\tExpected:   " << expected   << '\n';
        }

    }

    // report results
    //
    std::cout << "\n\nTotal:  " << total  << " (of which "
              << montecarlo_harness.get_count() << " pseudorandom) " << '\n'
              <<     "Failed: " << failed << std::endl;

}

int main()
try
{
    breath::elapsed_timer<breath::performance_counter_timer>
                        timer ;
    tests();

    // ----------------------

    std::string large =
    "380c01ba00a433bfe62f91dddeffcd4944021c7aeb8867d0358c3e9ead6182e5"
    "6d849f6e29d32d1003bfeee1bfbb2b04bd487ea9d0e6790572b7a31f19260486"
    "aaa4f4d47822e47be2d25da18d89a54bd124f4a20a6ea77c264b9b3f72a0c61d"
    "45bbf1beddd539c0a8976135200780f22c759437e33cb409875048f9f10f1736"
    "ca08f5a7de2f6786c6c9bbe7d13cd9feb16d3595a9e99f3139e72b2bf64261c1"
    "4a56682986d0af4c9a6b336ca70d6a597b9fee25898d56c37582ee6cc4502d0f"
    "a796382d67e8790153ad6efabbd8543678435b01d1b2c44734b3b4f903e109aa"
    "7842d7df2a51e17dff4f78ba28cdf1a0104ca1e1fe66293319dd2c1dbf36c737"
    "789f17a3f1f920f14999ac71669d1177e9b359e819821b336048501f7e1856f7"
    "b86d9aa967bb9ab0554621bce43333cde78db6000fd2346f1b858e9a9de59155"
    "532cffbae79a6b3de18df9c5c02c93a7b949a8c91cdd393762c8d100ae635501"
    "8f55bc77ef27b4d0b4ad9675da291d9473c55e8fa397c6056098050efc5b108b"
    "b0cc03a0f4b771a965071e40303bd4a4013233a4cafaaa2a93af398f0b491bbc"
    "161e5c0ad6cdb43cd5d37c060f50aa1082deb54dd95f776c0fb0fc1bfa17d710"
    "35331b0c01cf48d6a3c4dcb21486c3976478e43dd85caae80da60307bdda18f3"
    "0e33000f0348e5a60dc15821481cb9ad949eeb6dfa9556073c5a0ff93427ed43"
    "5aed525e36370543f95e65427a1eef0fbdda7cb770d3bfac2dcfa662f694a551"
    "81f7afb72fb5fb2913606b8d7f5b9c3c3618f4a6ecb3531982fa7b798e21ca0f"
    "197ac7482fc2714222ddcfa1386bde6e84d2157086698a08630682f1284c0141"
    "c7c989f68cfb38afd9085011742f80f80196698700f49063fb1255235f576426"
    "20ee1cace9555bc25eacd4d2db55cbddec3564ec2af4502507a64866fdad8c1e"
    "9ba9cb85ff27485dd31c30af72fc8c5e31f14b5be69b81ed41ca543f77e05d13"
    "8a2898894fe0e723fd18d3701460cf46511ba238b62325f8ee7938655a9679e5"
    "be116e0ef25632f06e0561836530c9b74b6bef028e15fb7c8f34e2eaca5bcf88"
    "6d3e976095c95103ceb28734e350ec2fbbdc314af22dc78161a96c2b053bb473"
    "794cd40f152512e4d89a19bbea05eaa6e21cf0d44ab756ab61c2d767fe8cdb78"
    "d8af87edd599d2ad34eb691ef154c4d371b5a7bb6cfd66cec03e36beca1136a2"
    "c1bd90965762448b4eaea93f026e137323bb2f90b8955e79d395379ea66e4067"
    "2bd1fe8234430e82f1b8c2f426d668499197da4a2d39c300cefb9e7569dfdc94"
    "b1db17e51e25680fdd2b0304016c4e920328dc3061a031309bd0a504b0829961"
    "5db0467bd6ae8ab4d98eb8dbfa076dfe2f4a2f91ea60c18531678ae1e9234246"
    "d488c1ab374c5f11db18ecd61f5ad44fa403e08e64a21495099f76f3c2b83997"
    "41fb427947a18a23ba76f9d9d1cd2875d1090436ab19cbb5b841a87bfae2123c"
    "dd55b525f73f48b1b6418b870fb3fde1bc0217681be21ed424c64f1fa9625b86"
    "b811acaf51f5610836ec90469f8d275c8f3ec5ab21e37f46aacf655332c1daea"
    "d2879a247cfb2cb2e7bcf9874a20e4da5fa985818d05c737d42d8b06ee65f1c1"
    "ed8be56987111c6fce15f61836dbf296857717127dde4a510bd658fa3c4abb29"
    "d6a1925db3aecc81c3c39afa9e8c902304a736818681d391572b8c947648bd4c"
    "e94fa99cfd761ec139b8bbd8444cfc49f333cb79b49e0b0cca98a040e05d8cc9"
    "ad3666abac846de63d29bf8275bbcb68ee96e2a334eeb0ff86503f66aecc305b"
    "029707af1b7496589d55da1210a67bff3d5da2724c5271d3a3b03a517d6aad80"
    "01b52f1d29c676c71b50d92cf7542b34b2cea6ff2117d2c4c80c164576c4c578"
    "79f595a3bb0b6ad75c440354982f884bfe2f4a1f471ce40f29fb55a0bf1b1839"
    "11aeddcdba47a4178ba86b24d8f470d623bbf56ad8d97a01d4d0a194ecb9cefd"
    "68abcb22f370397f18a5a4f19914c7bdcfbc28a796a2a96b734a005f04ce5d6c"
    "7a288e6d99c8edb26e91a307a66ac57527ed1dbe8fc6290310296215f8c08172"
    "e910e082d9cd34475ed74f0442147a69019828915f5194707bf78573b706e6a0"
    "17c623f0945737f32f86f8729a73dc9c0b042d6a56c2dad1b95f4571662c127d"
    "f3356d878da57abd2b722fc6e50b63f110905b665336370c967d7efda9907b9c"
    "c6e823548e9e12ba114181f74de4e85d7544c3c87bfbd51278530f22e48abeab"
    "73e200018112bb92543d89a12172ff96b6c25f32be3444368853586dde171951"
    "f919537a2b0f0d804c96216d092004c0e363f2a19736d8208a318d6848a7ba42"
    "c00dbdec1dca6c69618ed76aafdb2a923f1d34d7540cf7de3d8547862c02c8ed"
    "1085d92d4f4697b1d46e1b834a461689634a60b757579695dddd1b09e0e4f6f0"
    "6ad01dba17b56beb23876f6dcd85f630d056e828ae7ebe8b5cda953cbe8c2d28"
    "5d4be374004e6023d5cf91a25587d326debc4e8d3a0d1997e7aed4a63b01cf98"
    "4cb20c4c006d70d63c017892894cb8680807f543140fdafcbeaea2f9af7192fc"
    "239f48240cb8fa48b973da43bf93abc89aa00cafb0e6ab6e954d6745bffa41e2"
    "998a07a54301eefd74c940345cebfdf78c09a63cf052aa869f12cb5e0c0d41a5"
    "98484bdb4a3ad8be0318f36004f15790fbfecdeb507771f08a3d4f964a903ce3"
    "d988be23c297e2c6afd626b4c77e45c27c12aecd8a20be145d0daba89ee88b77"
    "714a9b33e17ef9915420451c9f8adf1c9c8de926aea73b0bb5e7b453cf3fcb41"
    "8966746ae46efb398f41552ecb354a68c3348f71dbca7c91b231e48270afc3fa"
    "163865fba6613435a28a646ebfaed682e265f4be30704fe2a1346412e3280dfa"
    "6072f607d42a3c76b5a1e4754fbbf83220ecf1505c4033fe74981158c01e5320"
    "914927657464dc2906c19e567c97889c8379ede0ba21de2fb9f0887a0fdb9ba1"
    "25c3069928e3c32ea4628421f90dbe7c87ac5c42cd3b71872bf9013bd59ddcfa"
    "60e39489c757b76bb93c8db24a4b2fd1f78b14c4c7854cf27f4e2e55eb0b4f4c"
    "eee3d5b53b8d21f4c9aea714fad7e6f162fab62980021c00504b553c56a58845"
    "895dfac4ea1cb9b4cb61c8c538afb79aa96dc4296fe129c02c7ffc822484c7ae"
    "e2c272cddf2c82aa8d4b70c5fa2760a39425cd0406f7c53376c1b59b467d4929"
    "40bcf61fe878ca75c43a3bbe629b61f7c02ffbc726c1fa9c82b038c92d82f26e"
    "3ee98d2662589c2693d7e4f57346ec3475e8fb9ba9f6382ca671f5d4f3e84231"
    "d1d0583428f45abccc3fb13f869e74fb8670973066d05c0d4152e1343a24650c"
    "f4bd411db29cd97edb8bbe6129335dafa3f4e00ac53c17068ef93ac91da0d612"
    "5d172f10b3098e8e944df0be804e6e24434e2e088a460e193f48e25ce8b86e46"
    "cf9e5682a7e5113c3302fab45068d893b6079c414daa5a8df33de9dbf55822c5"
    "f779489f5e5adb915cd646ad3f1e41f526dd37748791017aceeb56c44479893b"
    "f2d1da502cb6e2888c2836cc4777c26e55f9e2dc8be4575ad0ae1e1427a8501a"
    "7a2a6aa6e14d2f6e76653abeddfc2c32f60f0f81f466dcc415fad83da329571e"
    "53c2c43510f3a48659de4536db7268d281775375de2f3af42a1331ce3c89ec90"
    "4bb1c55ba469e2fe482834249a9df61c154a91f47acce8a4df1a731ba35fabef"
    "10704ab5da2db42355e947f0863d0c9c879e90016a78a649921a64367a10258b"
    "8070415b9ef57ef3dec6e46504f0018c8e918ef80a34429d4fa6d3c9b6f85437"
    "689593068b12fa69d8decedccfd0685d61f7566c2c98097b3fdc44f6d5992e3e"
    "2fc145bbd44024ac1ff389eec4f24b26e9a192153a9b917978d66f4e6f9d8d9f"
    "5ed25a32127fdf32736920375c6c5d450eef5b488becc104c2305232cedfd22d"
    "b22c60c5ab3ff71fa918560584b34b92a2a6da2e939b3256cc85889a655ac817"
    "8728dd3368d45211eca817715b6203fe09dd2c9c795ff246e47be149d6a9615d"
    "d13e903a13e24b008a6371e6c574e5cf52116ccc715f1255daf49fb09d000d6f"
    "3f9ea95280f5520b58c3f11e38d6ed8be8595759b86aaf935e4e43fc4e516b8d"
    "ef14e07009327b62f66d802f446dba2dc612867f7d3612db8456d7d3a7426197"
    "574107617483c36bf1439a35b155637768eaf7e52009c1a460987808dbd99f33"
    "1ba7948f2b58fa1c9b95524debb5c4549fbc39bfc6fa642693dd2e6eb6cea1d1"
    "763661a18e5cbe2af11077ddc63c3166f86b26be658ae5f96813681ee209f058"
    "4051f9ceadb7f89fc8707d8facaef5a5191b647fa649790e5de12d3feb1e972b"
    "6f91f91d49f2bd11633aa10fe997b503b219835962fc68bfdd96ffc8b496f324"
    "27ed4170e0ff824339235323ba08266d21a9c784a5304482c6434b7bd93e9f01"
    "2ce1720de0f4501a18a43dd3ad6441cf0d0953b339983500db817bb5c01ab6ec"
    "fc28f9dd1d4af736ef35099c994b6ba654bf598d578f8e321109e8d1249fbe20"
    "c7b8fde503f51bf22a258fc470fa6bc5bac5531155e14466ea2d370eccf52f94"
    "ae2d79b12295a34dbb32112c2d7cf1e84144fa97253efd106c351f382a4eccd9"
    "7b458a9edb2deb9660fcc38e79b476bbf970521faf4f301b844f53af9e1f8819"
    "6513b74141a3d8a19f9b301950a6d44a172769c67799e2fce936ab875634a0bb"
    "4758fd88fbd52a9b715ab4c101890b18b075df280fc124f8f7d07f4d0520094c"
    "7906d575dc00114d5bc60f5c4f1b7400905428a0154d990d1d195b223a646fb3"
    "6b452948453a96a000a5fd50c0725151c679f1dcc78be9e4a44406dea9769115"
    "bbbb5d01f5f4a2f6999f465a1197abd8119db4d8289dbccce2c3ab8c3a3da2f5"
    "f800f6edf498e38d382ae74ac19322d231d6ab59746826572bd1e4650e865b06"
    "8652f47aead8082302f06dc4839096b466410edba93432d506163b159d961b23"
    "e8109ed3e8a6f7eb9664af1af446ce5b87dd37311169071880432d1dd94941c2"
    "59df9642868e2d1cf3dd37e8230643abe37addf5e4e40d65273a830184c4c4dd"
    "a45b202ae94d47dc2b7ec54e8408fa6883d75d68bc6acee3a551e52916aa07ba"
    "0527e5ef752dcca0ab91ef309ae9981ec0f6877d60556006a64630bdf13778f6"
    "5f5ee6d48bb37537456467df4e00fe0ff6858c57daed5d81338e3e24c5b71b24"
    "1502f9a0b56ed7fad33eda213fd830355dbc8d37a9ebb8dd79f7013eae1d63c3"
    "205c63d5cb3bd09e7aaac0b983f0efe0ac7c185667d133e0c8351f7752833b72"
    "e09e48abda194a54c40a0d47fbfd27a77940fee11131c2da67e251ba658c2c45"
    "2b75f1058e3b595246679a4164c2e9de02e7c0131982ed80653f3acacb670ff7"
    "dd01fc6c3d56bf84be59c5231baf011d97c231b1451e31aa5e6c742ad48421b1"
    "861e1ec375dd4733360d5651bc586f541aa0055fbf370a1da37e477803692a89"
    "87484cfc25942f5ba186ad5dde1cb1f8bcb7587cee629991e1e10ae44a346dd2"
    "7cbacea24efefeef84ab4d63c8ff5b85b6b401a4169a36f87c41dcc6754a98f2"
    "05679453669243eb3e914e0690aa8b475e8cec7527236da3644a6ada9402cc99"
    "6a61edd0f431bb32c2093953b3c49a1251878778aaf51c0f3f86e9d489b66ef3"
    "175cc40c8d7f3e4f8977a23d3c3d4f8dc4d7066fcc237e0ca968e1321f4f2636"
    "acea43396a8188f4f92b31356881c32d58c99d25ec1c32968413c9a363f0da0f"
    "da1d49459fd13998fd6bce66ec9193455b306a484d9dded1b0a8751498502373"
    "6e6cb80d3ef2a63c5d74a24a06368f6167faaab49789864831fb5cc94c803cba"
    "edf5c82ce76f6844e40b8fea411e4ca818f65cb080e3f8b1de557b2bd6b7e5c3"
    "adaeef941d58d9016368eca487394da030aa50b08d49616c9fdd9775957d3842"
    "2b28d64981b04be4193889a071d740a18191520edab47b799112ee26902768bc"
    "4f3f05d1f051b509893fa9fb16ea9d977befa656a322d03434be5ac5e6c38136"
    "028707f2d9bdfc62fca55e1290fbaa0bea51618d7331c1a8f01c6ed7dfef0de2"
    "7614d450d2d1b2ce7611e1070c8c12f6de748452a645fb9762696e41587b23cf"
    "90f81f62c9d23140e31347f09f5ae77dcf6bd075b1cb0c13347b558df7795d88"
    "717cea3b4f1c7c332fc423cf1e0a4ced751c6327e8703a1ceb8fa9e208066a7a"
    "8355b6d3723206a1f62a701535bd03abda66d2c2d70cdfc29c89a5a5900f1f14"
    "65d5e7d707ee78fe18e9144da717f8817ecb4455d7231774adbc193dcc385131"
    "0e3908162781143f6b288d12408693be51d81429fc2b9da9e8b6e7b5ef39e7fd"
    "72f013997128d9dd5166ef91ed83503f5b64685890050179bce92eab2215a894"
    "06bc2d78e40755356d44c65bc8179a247b027c0b087e84c467b37089c8191dcf"
    "d54b47b9529cefc0e1b61ba9cdb6cd48b94a53c1c8d886308bf6ba540fd723e4"
    "236a9e76068d36e743529110095f59c2a9ad8372850aa310015d65103588f558"
    "f294cef92205e16558727661d2d0237c7da7ee02b19113b2ef78c32400b97df3"
    "4d4bed7051ced6a9414c0a131d2e8f9ad57e9c8710b039ff28fd2429b7a11d05"
    "ed0a753ed94be81a98f32eb521be4ff63dec7d4d9db74dc5b572ef6c130d7100"
    "17e63ff032270bca1a3a803cf8d03236bdb0845a67d1201d430f89571cfb5834"
    "e2982514bf31dfda6b5f17642f499aedfa1e4761f0677e3477088b9403e4c9e5"
    "7ceefa3c20d9178b392ef069788a5672a99dd39a0552ce7c5b5a115e3fda44bb"
    "c93ef7e9180f74513d65bab5f0102799aefb33b34e0230aa5d41099c1c4d57e5"
    "8c4fcfa45e44f69ca9b15199c2793370756724c469546ec7967763b3c5bb9851"
    "0a67f669abec05559d57ee5fd121d04788f40bf2497ab9e0f11d93b6d82c08e3"
    "94fe4d40eb539588aa83e87ca5b8c42eadcf21f649dbd63bf86af2d196fab42a"
    "f9016ae454006dff84557c290e4058bb0f79b1595488954df2871e8982d2b47c"
    "d41e60291fcd28a323a4cc31e425ecf49f9e4ef427e4411a6b60a3ee32586a07"
    "76cb3096995939bcfd06eee22bdbd7ca7926bea10a00bc76605f6593b8cf9a2e"
    "9bcbc43424fef02204de052fb9dcfa3303b8d40db8908419f0e9aca8b947d754"
    "129c88369a78599e575ece103bc8443e81194c3aaad0539bbaff4373461bc859"
    "b8508f53c9e8f22147c032828976c00a8f0d4439de97d49897180cde34d437ec"
    "25c740efb03210f7f343797cb93a874947cc83266358befb71cbd9a5a01192c5"
    "d8d3b58805c67ff909f975c334fd0c7cc990a22de86028592b02ffcb139291eb"
    "6547736b0df36417ecdada20d7e69ca0773ece5f9ff6b9cbf8b9970c4b29f7b1"
    "706b1d7e5f81954b5c706c335709d4ce48a22de899e7b392a04b9eec74969ee5"
    "02bb64613df9ad99691acdc123a18f6c44bd55dda4096f45540e32c9a5d0aea7"
    "8c1308c90db66276d02f38f4d1c7611584b6f329bf636e1371a0dc16718bbefd"
    "9fc6c7ac7d29234d595b412a22a33fa65933cf18963e2b07df081e5094dc4e33"
    "a315df203f026e985db0c280530226ac35f6c4cc35f0d314f9f2658eceb3c272"
    "c9a29309a501a103b164830467aab19da17569d6663dea5f2f4feefe03b070cd"
    "5204d6f80578fbb7dc7ebb44286ce2cae24ba048888aa8b8da97b6dd4727ab9a"
    "2b819231fa8ee8d60ca31b3510fdfff3499f3cd12ae58a047c40e2c4688d5f93"
    "0ff2c50980ade08d51fcc261f9c255426291148c779e91f3df74b8480117dc11"
    "0aa11b8a4efb189ff7db01f19d563400e8498d5fe71e52c7930b109523eca62d"
    "8dc1b8dcbdd07bb5ac7ca64ad3da4abb23d71a0bf66dd38979e31e9cd0c5ca5e"
    "87823a4453b5f90032a04a057b94c19f6cdbab63497eedc2620c5f33d1299158"
    "accb9d00809700b3374bb8b2df79514c55fcb09f7b9d62dea9c1117aeba3d397"
    "6e7098ef0799a23fe45af1c4d443112a40c1cabc5e2c9b07eead82d9505671be"
    "c60aadcea34f0d88aaff4c7f435daa841e74417ca1dc848f890769d95ddb9724"
    "e545f2889500113f005dbf44ba69c8d9dd09567fe6db0e6fe277493f52e06338"
    "2656c1bb57d2fb572fba9cea2365c4016e1a8055f58fc4d7060d1759ee7a9115"
    "d152d02824cb8054851c3ea98102abf01d2b4512bb0aeac218011b067cad1b4d"
    "00ec7524b7f5793d12b7e694ba9284d8becaea79d4d53becd757f354040fa204"
    "fb1829b30da2f0205ad7b4156939ed2703d8a1d7addcc48534b8da38c77c3dc2"
    "946675a20966c2633d7779a7b066cfb33e718bec4d507181084bbacfc8f7915c"
    "5e07fe686ec1ccac384553e8ab239ce99427d5e27747647f931e4f5b16e1b775"
    "e9b6dd5777aa03b0ef57999b7a35840f5d5af2d5a256553575a4918c8549016e"
    "ffdfc57789c9287920c1149bf699aa54f39c2995f37ecb68225cf5a8a5f616a5"
    "d6dc1c60a544d9c605ee61fc870c507ba979119cf8dc051a39fac2def1d983c8"
    "b6a0285be50222ebf183e7799038f439b205d6aae2dcc41bd787fac9617e9117"
    "1eba7204bd94efae18d628a80f1ce2c122b96b059530206db81b361999c830b8"
    "82a3bc4038acef508317f99234dc545695c05b2bf07c99a998cfc23198f2ea1a"
    "95a75bce534a1ed662186996f5bdec8a7d48b66ec450175c1fd98eb7cc79d262"
    "212e3075794f4bdb67b5715c725ee7f0a79e5e6bee75c80e4f57c61bd1997ef2"
    "c8ae6741fdb31c65688ec2dbedaacb94492900389fc947ee210d0af2a788e56f"
    "364db03400cd9a695c5d444a080fde5139df89d8a8d0c6c9ded0bc8658a2f58f"
    "efa6c4f0745e59d0bc9e1ac4adf915e7d89fbf8170864b4f5607d5afa9ca3f99"
    "710489e562e2b61f80d0e32ecaf915a298d524095b6f58b2762e6220f9a2b96a"
    "a6424f09250528a6d60bd4a004ea439dbf67a71bd600ce4d2e306e27d2289279"
    "6be28290e7aa36beb60b5fbaf5a258b50a00d1e1009f2e2ed09d56a3c5e81c30"
    "ca9ec1b249f771ff03d0baf97312af7e12815f13208e42f12b9895f181b2214c"
    "50e3fe9ada7099de4053d7b46587327808918c291fce1a4b66b03ce8625e34b3"
    "41334d1ca3e6fae339d2979f59ca18615ba48a7b72a5c6d95502c1b860f56ba2"
    "29b9becc9fb8b0d98a4879e41292456d37d0e8a975af83cbb14583123befb464"
    "a87330482be022b6289b9a3b2de0a865b0910f264092f1f2d775051265ba770d"
    "2da75659887810b114abec428b95a73c27b6636848555a20ca60332f1aaa3d48"
    "5293a1db0bb18d205d7a62e810092537bf889f07ddfa28a85a5bd8750615bd58"
    "a95f34b511c1d56e3b37574b407d83ff052207e31d2f8b778a63ed9179abe922"
    "0a1ed71cdfad8b1be4e266245fe924650c2b48295bd4a1e6388e77b13961d344"
    "7fab605e58eb793ccee0612eca8593d6b1dc000cb1a1f2e92f699a69ca6ead4a"
    "190ea971fa22aec80310f7cd958ba44768a4531945460275af9cde7a0a8cc524"
    "9b6e969590445e94545561eae1053149a98562eecb65647b0142f60ccebb3169"
    "29c7ffba0c5d4e61b3af4c94b57ddd5f03404ecea5b249a7f43fb4c3fae52d23"
    "ad2ddeb98a2c1b3edc67d291e5b0f1e8f03fb696f1003de640f1a93bd7d75f84"
    "043d3e8f6959cd45c1a0d7a651c88f420746d8f94615df860789c2de60216365"
    "5ea2f4c7fbc20dbd63e463b4adf2f6b439cead7fe48d06eb16c8ca77e92edc48"
    "d0d10fcc941c89f701edabaee0a16319701198549e9f40b5680a2c5239099a09"
    "daaad56ec75e66c84c11772cb3da4523ebde788a7eb83fe6c36c39fc75d30650"
    "7ddbbf443a250d863784b3ea5ef80e4ad786d5553e143c028075fff6490546c7"
    "e0050c1b2b19a2629e554cfd4e5b4725e11d7a2031b722b22c22a97627ef3d08"
    "f54a232064c583021bd0ff692b478e0c64092d96c05049ed72f26399e2a1a1d7"
    "ebc5f84f8b7b52a64b521076999e83fea8b0956800de5672d1b90cb35bad8b47"
    "738397feffe9a54a3bb5c1d55444d4fcf46965f548bb67197574cdd021581795"
    "dcae94db983a25d3efe7a9442b7d4120e6a6162f617e48d6f216a7146ebfa94a"
    "6e3d2606774bda673384ac5e01ed7fe8939517f51360cc05767319e533c230a1"
    "0056a878a283e0d5078c330979b3f10d4808025c68cf61df437bc4763ef4183f"
    "4ac0b7ec4497c14b24f5549da846abf14ead4eb77db096c02b5b366a4f4ea999"
    "0f618653f8479f1c3df4bae63a65d78913264090d6d7500132876c81d5151be4"
    "76a1386fe9d78c26cb460d05ace48ec00bcf50e1a6a1e3d9284f5afe6476e3db"
    "181b4b01f2d728be1e35c4cb1a528b2522dc06c97de9a2a639fda49e7387798b"
    "a2c58d959cb653bbeb1786066a122b8dee32566b1cf81155f5b5f3693c6df5df"
    "328274cf38c88b24e0112a4b2356d811882e7da4268efa1c44ed85815a7a618d"
    "fcd65d359ee8597ff984ca1ddaa22f62d0ac07f73b011380ef98024a1363d70f"
    "393445d81c9f5716232134fec464619511688c4d6aa0cd5939cfa34c337b5c6c"
    "b0a145cc419ce364be1862827cc3188d2ca4da9645a8ef7e7893caab0e2618be"
    "c75d8b08fa6f6db887d03b04945392c1f86d573d1647bb8edb853ae9ac52a874"
    "b0337daaa3eb622bbb9e3050f1c211e930692646b1e2d48c680e7614611e8911"
    "5206bcf6f11f21adbd51fdae140f974479be8a2aa15fb7096e2e1ecf4da7e1a0"
    "ad9d969fbcb84c79094a281e59c062d37fedfe204db529bbe4488a31ef6cd19d"
    "09683cc62089402ad368482d28aa01a898ffc8e5b5f2a0993a2bca2a979cc8a1"
    "050568258ea84f621197903a4291e2da90aac0459d60ded78ca9022446cac64b"
    "d02e715ed7c0c1e95851249be2067573b136b94e9698262341294788f40dd4c4"
    "3c45231406e4fd5f3621fa1928708cdaa645293ddd50601f79a8a86db57c32f2"
    "c25506c9390429702623894f9415293a5b537839a3d8591c80018a367ebc2941"
    "11300a4b3534bb5c5744abeb5ad526b6289eefcb7748e8f84a722fc82e580a40"
    "89158bbe49471aa08cc68ce69bb39dc4528d8fc9d678c120eaf1e91949f359d3"
    "08e591512dabf2b9717fa00d323dd284ca624ea0da10c1c401aade4b9e381ea7"
    "1eb0f94b5beb05cd6ba5db9ee3ad23ae0f714ee98110ae83bb8dcf59c5ed00e3"
    "9df92ff9e534c751daa3efbd50126b6083ba4a05caf888858558df4b45df2ee3"
    "d95eddbf92a4106c47002a981295f89650439b1a3c24a0c17c7f0dc25f3ba639"
    "9a83f82c2809997009c3081c5901b2a9454ec381726442efe350b2428b587b25"
    "dc7452047eeb7488af7da4087f56b1c4a4754517d98807bdd8b90064127b8aee"
    "f0ddf36fc968f778e59b8165f2332a97a970ae82f8b640d16f403682bcc070ac"
    "9e631c67cb13dfb1ae6117a19441383db1e6c0aa9c007c0c40b28efc73ffa911"
    "63c5782fd858e087baf8294e39618ceb484c96e54c12f18dc4808938803349e3"
    "f9c212d21bf35ad5eb832424e4b0102cfca61149b803d77d8461b50494ffe78d"
    "c1f95fddecb9b3d73cd7fc21880d4d85b35fce6c62a5e9e7069feb9b9ed22960"
    "cb893db843f09080c88ca1509aefd54d4ea4bab149a398504383ece156154122"
    "9e7fdae16f6a6237f7038891f25ddf410199f34b3d8c9c80108862669ea3883d"
    "22631f92ce81cac684525877af37b9b1d1acfc0e39988f4921f1b0c09539fdb8"
    "9c1d4a6b9e14312367899b16c154c89201c4a13a5d30847e22343eb76d3c6f0a"
    "59b976f8cea71b3530b64cf10b14840cd925473655cbb577fff42f6d309e788a"
    "58ee8227969d5dc654a9b85fbe3d6c9762b3ceb87e83307e775feca8fe643256"
    "53b47ee952dbb0a684690643a672db0826a9c0a52df123a450104c4e757fa5c8"
    "3323b285fe622c83cb32c672a5a17acc4b3b71782d941d7da56acc1ae972e21c"
    "9594a294f7cf17c301de35a780b073ccece444197961971fcb6339b4d51cd16b"
    "b174ffa843176b45f6a1ed765160423e458757bfe8eedeb452186927343b93e5"
    "af928ef3aafa38a09b2617ed865a2ccce1838cca726b7ec583e8edb823809dd3"
    "132cc6bd26ff5dc22574afaccedb79b05f057ad270f998f4e185ac04054ad719"
    "769ed69c9e345ec4a90e7078eae92849efa21c609bb4557d3a01813f4c5959c2"
    "f82f5f9663be5a0dcccb85b7b5ad00a4501d05ecd25a690c5cea4ca844a56a3d"
    "d5cad338882e4655f9cb0caf780d53c82b59b4fdb31e090f0955b74dfb228ad0"
    "ed5e09758d4fcb871ad83692e58a5b10e3100d962e17a6376d5e8468800f386d"
    "6e41e3fb90af82aa87b83d6c43997d26a98bbdd7a2630e0fc1937842a2b0b011"
    "f2930c82438e2dca476b378a04b4b1ad406e84e2d193f293266ad5c91b85da0d"
    "19e7905c75bd27bd295f482d14f9db5467603739f32acd1994a2e3b028bebd42"
    "a54d9e1a0bc6d834252062391a3d8d829dc5bc91ef89aa842c8e34544cf197f1"
    "3f350c4bfce4802105e25b2020e9a3beae5f4f9de9fa211588556ad44701c687"
    "37d2d233b75255bd35b1dd559a801448e063e6c95d07dfe55d49baa44b812b83"
    "53feb70b500cc886bea6dc5827f0a1075387d1b08eb096ebfa519046d2bcc926"
    "ba80310a8df9914ba06da3c75d45cfb0cca0615b51f8474c4ad7921d935b434e"
    "db7458686ee9b30f5657d6b49da6646947c6c598be0de409e4762678d269c6ad"
    "de1f164d09c95c60213314beda79282140eebafffb9e08e0152e59e797209576"
    "3fabc4497520aa9754bf562f397f50796d0a7868a98048bfafa1a747c13cbd01"
    "e8814b5ea2f6f5f7b54c26efcb77683881e1a02b62e9ea118b91584cce164eb6"
    "979a153a900b314657583522cf9e5b5180fc7ce2e566f370f84cbdc6620c7dfa"
    "a69234369d667df4beb2178d5172ded16e5bb354c1a7c4baf38280568efd5034"
    "90846b2deae922a99b3936ecac15be1b71716f321933ed0db66d63446bb379fb"
    "38e52822ce4bcb6a8402573118154c8986bbbca0efa9ada51710ea82c4637dfc"
    "49a61f17f1ea8176edd8a706eef49074af4c149ef6c2440dd22e8f96920d92db"
    "b3b1f2a49c741b8a4dc3903bb720b0676dc50663874a71597801f00a0e82e6c1"
    "34d866d14d825b9a45ecd5fc0d86637a4b69ded2b44f2c2d511c385f9f1e21d3"
    "f788a5440a01de4fedb44cfb3ab076851a5458cea484fbf5a033543f51761349"
    "feb88d08ba6c58a721a4a25b5418e16e6d3a3d12be38075f6c5c9fbed3b207d1"
    "6b94da250132cd22d6707e2b89609af79ad709581011b87c6e573b4109421275"
    "d7ec9bd91f69fbf5d9792163d9bc5a749363cda4758521e3dc5c24e69f375c77"
    "24f75043604c393ac55a9d9f16f714aa5be14ed0666fb443ccd82a6b1086e234"
    "7e3377df7fb019450bb7e422aff9cd0ada1bdb418b8f855768afc27836a5adb4"
    "d8249357d5ad9de1648203137bd11e55ecfa9778891ccff2cb926b013718b610"
    "3d496812f605f45b87f86e02c98d58b687ef2e110cfd03d88f6edac78790d8c4"
    "da40d7d046cb2ccdc49bd08d282943af1871c0256fc4fdff33d7c7ba679f7e41"
    "df561226213ef3e5dac47302edb7b20629732b983728986a005f2467fea3a9de"
    "f9bc041bfaf801d5bd74d7aa2c89b155fcdcee3405869e05e5c36de46717c360"
    "d3c77bcec07da37df17a281d04d97301b66135bbe7d4c1cd982fb2ff46755f19"
    "3ddbe7fd588b7b4a06a3680a7ddb0c333d42ef2517b0f3afdfa5ae261a0e3f57"
    "ea275442b2d08db874f5c3f1d1d0250f1214342ac527d9a5cc88cbe6960b3e80"
    "3392c3e563519ed74762c91832ee2745035c6fc983486e50d13a37674575e878"
    "08ac5e6bfefc42455e0c5d91fb85d6fee246c7658f36b56070edc8b662b12e6a"
    "5e8cd55c8918a1e824ff7a2084501e6696e6cc251d82868d6f4e43d1ff723b5d"
    "ff11b988295b714e5aeb6ede3c8d45d37412f991947f1e04cd62d6cdd4122bd3"
    "23e55c4c40cd9b9ab80979f497bfc70bd1c09c6640ba6b0d1d41dbf15306c576"
    "eb21c32bef5ec6a8683f9cfffe640ad025a6366661a1747fe24f70365536ac41"
    "57706d47cf33ef37738c3771f0414116e8787c4a19f0c9fc403a339670e0d7c8"
    "50450f1f79fe57ec8a8e5d7bd09f92b9170f033100cc2e400761d67741ae4092"
    "f350b26c4e0958d998b6556856e7226ef6259ff6f2ce37f9300d7172bcb204b0"
    "02b61c51c0752a592c7fc28267e4f05e099055fc5f8cf58f9a6701561905061b"
    "bc236c7d9997d6c61799497e7d3add87ca328329bf78b95ae0bab0f9c0b7147d"
    "db81fa7418d13b306a84afe8be8c6f89bff3b37f6c6cd94c268a45e6415a631d"
    "db5e92f430cd259b51d4831061f39921e64da052b9799edf04e3c6453e2a631a"
    "88f50fb8c234531409d7256acabf8bb00c2c03c5a5a1a5a9856befc49652de1e"
    "48edd70a222b1f2b034495cd04217e104d82d5f2247a9caae68c6e7cdf4c9b27"
    "3a73325c9f5287a2971c709b3defab8a71807d95fb1a3fe2a7ad5e86fafaae34"
    "6de0910c3218aec9351f64730e10fe7f907c158c96556e3e02cdc4fdc7733235"
    "53c34186dcf050110fb5851ec5839e56ffb3e2960851d40b1f9909e60c3b1c60"
    "ff5de6db4e37ed5eec737cb1f61b07f6ceea8dd73c61e25bfbeb4208275e6826"
    "bc4f020b86f0697264e6245a012c51d017dea753408aae3b76f1449d4facc40b"
    "fbc71682b880f41c6719776945c9395ca7e0b0e86b5f24e150687f9f1443ab10"
    "0bc192c44287e0a9a05812e6214c43c92df3b19852d579a23df941523cec6248"
    "aef40cf17ced9b1c45ad0267f945302739e1bf8bb7392df5326f476f5caab70b"
    "9fc4fc1bb19737f7453a5e3f808f66b9712644285f721d92e265013e0fb94aaf"
    "7d46ca2fde0226243d8564bd14cb7785f1bcae512ecce31131e54f419e99f01c"
    "e0bb4cbfbe73e4fbf948b90d14309306ed41581b0d3b2c3f217c80c01671ddf7"
    "2c29b6eb9d9be696e4a0a4f8d037ffbe7957d9879206c6b48347749ab85191e5"
    "7b48d018e3b7afc75753c0288abfe60416c08ba9c7515d4b98d2e5512376379f"
    "be08b8a1bf676917ba293f45e82649fee7d4a7ae2604f9bfd6de10fa54489a13"
    "5052b510ba1e27744767b9308d022e74d7d523fdda1cbcb1fbccac5015466465"
    "99197553379dc77f0481af9283dd075ab32b578e48143f43e0ec94f632f85bcb"
    "11d11f496fe6c873677806eb550e46093a9e9882b2d8c693c45a89f652e5c264"
    "b7e1ad26c8769a30eea11c44b0624eea01e66cb4be3247828dd179e0b73c446e"
    "1ef295e7692f1758d0339c8096eb6a97d1d74c900a941397658d771dc9bc8ce8"
    "ae21cf1850e770211a0ca2b1f70c49c9e49559ee296d858ffafcacc4b939ac67"
    "5a7c7faa63f0cc7dfc6e2ff47b78be5f0d184d3785d3c67fd0734389acf0f107"
    "6c71b2cf617e4d5eed7c5368f411c802291539afe9002eb974724221623428ce"
    "a5da9d0659ea654666b8ae5bca765df48c97a37697d12f0b44722ca6a655744c"
    "2f125388fdb8cf64717dbf3bf41d2f81b4d2f74ba42757e899848f40d9038d09"
    "16e092139961770adf3645d453745508474d54eb74abd40d30634e0a67db147d"
    "bca6905508085fe83ea4bc9219129a605fef4bd39b20e1cb8330d5ea0be968c8"
    "90f91d99017c8140213dd23a506d9aaf5ce683f70665c389959974a183dd6913"
    "d686add8032e18246ceb5ebc59f86cb6def0aee555716fea0be48c8ec1f5a298"
    "7c4f707f7d89a4ea7402a6cefb1384da0332bf58a42e43af12cf3ed4c5e16c42"
    "30ddc2ae666698db693fa964532d3e5660feae052df2b53fc1f31487d480ca05"
    "5d8cb4c4f24d9f5c8d48c0e075ff36d6fde5db2bd7906a99847f2159ffeb5f5d"
    "7713216a61c0c6ee0987ce7f86045584ea31afc1c11a5b46997c9f9967fff6df"
    "12184973d91061e29730611d35b7a21fe851e1aa6c3cf105b8909f209096ffa2"
    "ae48168858786aefa8cc0dde84affd6c01de176d1b0873d39912f429a8f3cc57"
    "3be2df945b4a84041791e29b41e00842bf20b0da2923aec236a2ecdf95b837d1"
    "9a1665f661eafa797bdc15bdbc1e007b3eb05667d4042a0aa616e93bce200d69"
    "37725f995d5a13d8372896f346966f8546c6ed1aca1725712e0fadfd30ba6668"
    "2dc6028a201563573df94b8490bb0ad681f7f14c0f17bd3e266b3b5725a1bf52"
    "68c1dd88d740e0143a2c99cae8a3a16a9b93b6abaa74e9d1df242905c5e8582d"
    "aa35b681769796b0c4307bacd31c166fafcd1a5a42032c22275527ed3e7f1be9"
    "b5d26b2b6902db2d3256da0673f07523be8f7e0093aa23ba004aa73fcac2287f"
    "9494abfe96872cc8dd06cf51f74474b5d4f3b6679ed9229e24c9deee8c076e21"
    "9b192032a04cfa7e53cad04a0f4500e338b74bd6916d75b53653a4c35a13e5f6"
    "2d0528cd51234ca5ed1deffc62f0e09aa82b713998e6efcf3a939395a6788bd3"
    "7db4a1cfd7ee75c50b65c26d55a208fdcd7937666026369abac92f6141bb35bf"
    "6fd68f47c5040dd169cf3fbf7147bd3fc1f4a6211bdcbcd5a6ec37e8a76ca717"
    "43375f083c6cd9a53b1865ad6022ed211793433270ff0816eb3ffe93aca6abef"
    "de0af71a76d1bfb2ea245f4b474c6d5ee0b09150b09a679cda6630860cdb75ea"
    "e56d055c3fc40e29e96d7530bae28f9b9321ec43bb53e095ba101bc7eb90b2d1"
    "feb72e3d7c3c6765aadc9665be26005147ec9502407698fa86b3c27244744442"
    "2b7280a7aee70d59c3a3be82cabed411ab6914ebdface66660a8d8a51d1ce848"
    "8e68f03d4ffd9613a154956b13697dbed391aab33d91199e3af243570e2ca09d"
    "9491dbe48e72f830c68d9cdaf71999caaa437de8d596871088ca6797f708358c"
    "9a10702883685949f6f524ed0ebdb7b90135a1d6cc28e654f34eeceb572277f1"
    "33e71ab65073004669243478e1ec31e221d3b9eefc9f43efee2fdb4551523685"
    "39513b8ac43bd12e5f05a641f2d82314abdc02a77c45976a7572afc6c4e64bfe"
    "378789fcc25a2b2260d16353aa8667556369fddfae95492407f9eacce036cb17"
    "be541480af3fa20f110562bb8cca11ef330fcfe2a41806ac12f179f228440ae7"
    "991e67485e0a587010bb2c9d853e8db94d5c9cf174a39d87941679bd5b83a4f4"
    "a20c3d0117957127519ec5d7dc529029ae2c1b23cfb8aa64cf23222ba6c61f49"
    "d35d4aeaf3bc12445ad71b3629ac60d7d87bfaa834a40d03c82f2e6ef64eb7c9"
    "ac02b49fbec6e3189eff4fc7abaf9f842a9a2c5e3e3962066991755fe02d298c"
    "2fde2beea40f06430e550ab905aa3d30446a8e83a4f18a0d83ff6d632d97f05c"
    "751b4b1a2b515d39a768f3ac1231dc"
    ;

    std::string large2;
    for ( std::size_t i = 0; i + 1 < large.size(); i += 2 )
    {
        int v1 = large[ i ] >= 'a'? 10 + large[ i ]-'a' : large[ i ]-'0';
        int v2 = large[ i + 1 ] >= 'a'? 10 + large[ i+1 ]-'a' : large[ i+1 ]-'0';

        large2.push_back( static_cast< char >( 16 * v1 + v2 ) ); // gps check this cast!
    }

    auto const          elapsed = timer.elapsed() ;

    std::cout << breath::sha512_digest(
        breath::sha512_hasher( large2.begin(), large2.end() ) ) << std::endl;

    std::cout << "Elapsed " << elapsed << " ms" << std::endl ;
    std::cout << "[ resolution: "
        << timer.resolution() << " ms ]" << std::endl ;

}
catch( std::exception & ex )
{
    std::cout << "Error: '" << ex.what() << '\'';
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
