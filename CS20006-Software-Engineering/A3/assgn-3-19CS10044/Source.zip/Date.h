
//  SOFTWARE ENGINEERING -- ASSIGNMENT O3
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include <vector>
using namespace std ;

class Date
{
    private :   // data members
        unsigned int date_ , month_ , year_ ;
    
    public :
        static const vector<string> sMonthNames ;   // static constant -- stores the names of the 12 months of a year
        static const vector<string> sDayNames ;   // static constant -- stores the names of the 7 days of a week
        Date ( unsigned int = 1 , unsigned int = 1 , unsigned int = 1970 ) ;    // constructor (with default parameters)
        Date ( const Date & ) ; // copy constructor
        Date & operator = ( const Date & ) ;  // copy assignment operator

        // overloaded relational operators to check equality and inequality of 'Date' instances are very
        // useful in the unit tests of some classes like 'Booking' and 'Passenger'. These might not be 
        // that useful in the application part.
        bool operator == ( const Date & ) const ;        // overloaded relational '==' operator 
        bool operator != ( const Date & ) const ;        // overloaded relational '!=' operator 
        friend ostream & operator << ( ostream & , const Date & ) ;  // overloaded output streaming operator
        ~Date ( ) ; // destructor
        static void UnitTestDate ( ) ;  // unit test
} ;