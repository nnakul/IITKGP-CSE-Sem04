
//  SOFTWARE ENGINEERING -- ASSIGNMENT O3
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include "Date.h"
using namespace std ;

class Passenger
{
    public :
        // user-defined enumerated data types
        // kept public so that they can be used while sending appropriate values to the constructor
        enum Gender { Male, Female } ;  
        enum Category { General, Ladies, SeniorCitizen, Divyaang, Tatkaal, PremiumTatkaal } ;
        // enumerated types are useful in this case because there are limited number of options
        // to choose a gender or a category from.
    private :   // data members
        string name_ ;
        string adhaarNumber_ ;
        Date dateOfBirth_ ; // association of user-defined data types
        Gender gender_ ; // enumerated data type
        Category category_ ; // enumerated data type
        string mobileNumber_ ;
    public :
        // constructor
        Passenger ( const string & , const string & , const Date & , Gender , Category , const string & = "NA" ) ;
                                                                                        // default value for 'Passenger::mobileNumber_'
                                                                                        // for it is "optional"
        Passenger ( const Passenger & ) ;      // copy constructor
        Passenger & operator = ( const Passenger & ) ; // overloaded copy assignment operator
        friend ostream & operator << ( ostream & , const Passenger & ) ; // overloaded output streaming operator -- friend function
        virtual ~Passenger ( ) ;    // destructor; kept virtual for future extension of 'Passenger'
                                    // class into a polymorphic heirarchy
        // unit test
        static void UnitTestPassenger ( ) ;
} ;