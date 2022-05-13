
//  SOFTWARE ENGINEERING -- ASSIGNMENT O3
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
using namespace std ;

class Station
{
    private :   // data members
        string name_ ;

    public :
        Station ( const string & ) ;    // constructor
        Station ( const Station & ) ;   // copy constructor
        Station & operator = ( const Station & ) ;    // copy assignment operator

        // overloaded relational operators to check equality and inequality of 'Station' instances are very
        // useful in the unit tests of various classes like 'Booking' and 'Railways'. These might not
        // be that useful in the application part.
        bool operator == ( const Station & ) const ;        // overloaded relational '==' operator 
        bool operator != ( const Station & ) const ;        // overloaded relational '!=' operator
                                                            
        friend ostream & operator << ( ostream & , const Station & ) ;  // overloaded output streaming operator
                                                                        // -- friend function
        string GetName ( ) const ;      // non-static member function -- returns name of the 'Station'
        int GetDistance ( const Station & ) const ;      // non-static member function -- returns distance of a 'Station'
                                                         // from another 'Station'
        ~Station ( ) ;  // destructor

        // unit tests -- two broad scenarios
        static void UnitTestStationScenarioO1 ( ) ;
        static void UnitTestStationScenarioO2 ( ) ;
} ;
