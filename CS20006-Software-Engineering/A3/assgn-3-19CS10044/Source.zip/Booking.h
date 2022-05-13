
//  SOFTWARE ENGINEERING -- ASSIGNMENT O3
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <vector>
#include "Railways.h"
#include "BookingClass.h"
#include "Passenger.h"
using namespace std ;

class Booking
{
    private :
        // static non-'const' data member
        static unsigned int sBookingPNRSerial ; // 'non-const' because it is updated after each instantiation
                                                // keeps track of the next available PNR number in a serial order
        
        // static constant data members
        static const double sBaseFarePerKM ;    // base fare rate (currency/km)
        static const double sACSurcharge ;      // surplus AC charge for those bookings whose booking-classes have an AC
        static const double sLuxuryTaxPercent ; // tax percentage overhead for those bookings that are of "luxury" category
        
        // non-static data members
        Station fromStation_ ; // association of user-defined data types
        Station toStation_ ; // association of user-defined data types
        const BookingClass * bookingClass_ ; // association of user-defined data types
        unsigned int pnr_ ;
        int fare_ ;
        Date dateOfTravel_ ; // association of user-defined data types
        const Passenger * passenger_ ; // association of user-defined data types
        bool bookingStatus_ ;
        string bookingMessage_ ;
    
    public :
        // static non-'const' data member
        static vector<const Booking*> sBookings ;   // updated everytime a constructor or destructor of this class is called
        Booking ( const Station & , const Station & , const Date & , const BookingClass & , const Passenger * = NULL ) ;    // constructor
        Booking ( const Booking & ) ;   // copy constructor
        virtual int ComputeFair ( ) const ; // implements "Fair Computation Algorithm"
                                            // -- made "polymorphic" for the sake of future extension of this class into polymorphic hierarchy
        Booking & operator = ( const Booking & ) ;    // overloaded copy assignment operator '='
        friend ostream & operator << ( ostream & , const Booking & ) ;  // overloaded output streaming operator -- "friend" function
        virtual ~Booking ( ) ;  // destructor -- made "polymorphic" for the sake of future extension of this class into polymorphic hierarchy
        static void UnitTestBooking ( ) ;   // unit test
} ;