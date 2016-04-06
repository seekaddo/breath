// NOTE: for the moment, only *closed* and bounded ("limited") intervals are supported
//
// gps should this be derived from "set"?

namespace breath {

template< typename T > // gps space after "template"? (cerca tutte le occorrenze!)
class interval //gps not range(?)
{
public:
    typedef T           value_type ;
    explicit            interval( T const & lower, T const & upper) ; // gps explicit?; gps what if lower > upper?

    explicit /* gps */  interval( T const & other )
        :   m_lower( other.lower_bound() ),
            m_upper( other.upper_bound() )
    {
    }

    bool                contains( T const & t ) const ;

    T                   lower_bound() const { return m_lower ; }
    T                   upper_bound() const { return m_upper ; }

// not implemented yet --gps da vedere come gestire aperto/chiuso, etc.

    T                   centre() const
    {
        // gps assert ! empty (e controlla bene se è OK usare m_lower sempre)
        return m_lower + radius() / 2 ;
    }
    T                   radius() const ; // { return a < b ? b - a : 0 ; }
    //bool                operator==() const ; // gps complex :-)

private:
    T                   m_lower ;
    T                   m_upper ;
} ;

template< typename T >
interval< T >
interval_from_centre_and_radius( T const & centre, T const & radius )
{
    // gps DO BOUNDS CHECKING!

    return interval< T >( centre - radius/2, centre + radius/2 ) ;
}


// per il .cpp --gps

template< typename T >
interval< T >::interval( T const & lower, T const & upper )
    :   m_lower( lower ),
        m_upper( upper )
{
}

template< typename T >
bool
interval< T >::contains( T const & t ) const
{
    return m_lower <= t && t <= m_upper ;
}

}
