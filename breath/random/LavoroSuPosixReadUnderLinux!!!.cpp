// This implementation uses the POSIX file-read functions because they allow specifying the O_NONBLOCK flag.
// gps 30 nov 2013

#if 1
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <unistd.h> // for sleep

int
main()
{
    printf("POSIX impl.\n");
    printf("EAGAIN flag: %d\n", EAGAIN ) ;
    printf("EWOULDBLOCK: %d\n", EWOULDBLOCK ) ;

    // The O_NONBLOCK flag is very important. With it, ::read() will tell us if the read would
    // block. Thus we can tell if more random bits are available.
    // (What about multiple bytes? --gps)
    //
    // Note, however, that the call can still return less bytes than requested.
    //
    // Recommended: read one byte at a time. You can still get zero bytes read, but if not you have
    //              all you have requested.
    //
    char const path[] = "/dev/random" ; //"/media/BACKUPS/Slackware/breath/read_me.txt" ;
    auto const additional_flags = O_SYNC /*| O_DIRECT*/ ; // O_DIRECT gives errors --gps
    int fd = ::open( path, O_RDONLY | O_NONBLOCK | additional_flags /*| O_SYNC*/ ) ;

    int const count = 24;
    unsigned char buffer[ count ] ;

    for( int i = 0 ; /*i < 10 * 1000*/; ++ i ) {
        int to_be_read = count ;
        while ( to_be_read ) {
            printf("Attempt reading %d bytes:\n", to_be_read);
            auto const          read =
                ::read( fd, buffer, /*sizeof buffer*/ to_be_read ) ;

            if (read == -1 ) {
                printf( "\terror!\n" ) ;
                if ( errno == EAGAIN /*gps check EWOULDBLOCK too!*/ ) {
                    printf( "\t\twould block!\n" ) ;
                }

                printf(">");
                for ( int i = 1 ; i <= 7 ; ++i ) {
                    ::sleep( 1 ) ;
                    printf("%d ", i);
                    fflush(stdout);
                }
                printf("\n");


            } else {
                if ( read < to_be_read ) {
                    printf( "Aho!\n" ) ;

                }

                printf( "read: %lu\n-----\n", read ) ;
                to_be_read -= read ;
            }
        }
    }


    ::close( fd ) ;
}
#else



#include <stdio.h>
#undef NDEBUG
#include <assert.h>
#include <unistd.h>

int
main()
{
    printf( "stdio version\n" ) ;
    char const path[] = "/dev/random" ; //"/media/BACKUPS/Slackware/breath/read_me.txt" ;
    FILE * f = ::fopen( path, "rb" ) ;

    assert( f != nullptr );
    auto n = ::setvbuf( f, nullptr, _IONBF, 0 ) ;

    assert( n == 0 ) ;

// -----------------

    int const count = 24;
    unsigned char buffer[ count ] ;

    for( int i = 0 ; /*i < 10 * 1000*/; ++ i ) {
        int to_be_read = count ;
        while ( to_be_read ) {
            printf("Attempt reading %d bytes:\n", to_be_read);
            auto const          read =
                ::fread( buffer, sizeof buffer[ 0 ], count, f ) ;

            if (read == /*-1*/ 0 ) {
                printf( "\terror!\n" ) ;
                //if ( errno == EWOULDBLOCK ) {
                //    printf( "\t\twould block!\n" ) ;
                //}

                printf(">");
                for ( int i = 1 ; i <= 7 ; ++i ) {
                    ::sleep( 1 ) ;
                    printf("%d ", i);
                    fflush(stdout);
                }
                printf("\n");


            } else {
                if ( read < to_be_read ) {
                    printf( "Aho!\n" ) ;

                }

                printf( "read: %lu\n-----\n", read ) ;
                to_be_read -= read ;
            }
        }
    }



// ---------------------------------


    ::fclose( f ) ;
}
#endif
