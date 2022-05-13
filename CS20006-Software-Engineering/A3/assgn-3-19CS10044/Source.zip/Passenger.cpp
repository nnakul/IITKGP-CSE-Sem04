
//  SOFTWARE ENGINEERING -- ASSIGNMENT O3
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include "Passenger.h"
using namespace std ;

Passenger::Passenger ( const string & name , const string & adhaar , const Date & dob , 
                       Passenger::Gender gender , Passenger::Category categ , const string & mobile  )
    :   name_(name) , adhaarNumber_(adhaar) , dateOfBirth_(dob) ,
        gender_(gender) , category_(categ) , mobileNumber_(mobile)      // initializer list
{   }

Passenger::Passenger ( const Passenger & p )
    :   name_(p.name_) , adhaarNumber_(p.adhaarNumber_) , dateOfBirth_(p.dateOfBirth_) ,
        gender_(p.gender_) , category_(p.category_) , mobileNumber_(p.mobileNumber_)      // initializer list
{   }

Passenger & Passenger::operator = ( const Passenger & p )
{   
    // copy all the data members
    name_ = p.name_ ; adhaarNumber_ = p.adhaarNumber_ ; dateOfBirth_ = p.dateOfBirth_ ; // uses "const Date &Date::operator=(const Date &)"
    gender_ = p.gender_ ; category_ = p.category_ ; mobileNumber_ = p.mobileNumber_ ;
    return *this ;  // return the instance to which the parameter 
                    // is copied to enable chained assignment operations
}

ostream & operator << ( ostream & out , const Passenger & p )
{
    vector <string> genders = {"Male", "Female"} ;  // vector to get the gender as a string for an enum vale 'Passenger::gender_'
    vector <string> categories = {"General", "Ladies", "Senior Citizen", "Divyaang", "Tatkaal", "Premium Tatkaal"} ;  // vector to get the category as a string for an enum vale 'Passenger::category_'
    out << endl ;
    // print all details
    out << " Name = " << p.name_ << endl ;
    out << " Adhaar Card No. = " << p.adhaarNumber_ << endl ;
    out << " Date of Birth = " << p.dateOfBirth_ << endl ;  // using "std::ostream &operator<<(std::ostream &out, const Date &date)"
    out << " Gender = " << genders.at(p.gender_) << endl ;  // to print the gender as a string and not just the enum value
    out << " Category = " << categories.at(p.category_) ;   // to print the category as a string and not just the enum value
    if ( p.mobileNumber_ != "NA" )  // mobile-number was optional; do not print this detail if none was given
        out << endl << " Mobile No. = " << p.mobileNumber_ ;
    out << endl ;
    return out ;    // returning the 'ostream' object is important for streaming 
                    // of multiple instances chained in the same instruction
}

Passenger::~Passenger ( ) {     }     // no explicit memory management needed -- no dynamically 
                                      // allocated memory for any data member -- hence empty body

void Passenger::UnitTestPassenger ( )
{
    cout << "\n\n [ Passenger::UnitTestPassenger ( ) ]" << endl ;
    bool allPassed = true ;

    // TEST 1 : Construct a 'Passenger' instance by not passing the sixth parameter
    Passenger p1("John Doe", "1234 5678 9230", Date(16,11,1998), Passenger::Gender::Male, Passenger::Category::General) ;
    
    // Check all the data members and match them with the passed parameters. Match 'Passenger::mobileNumber_' data member
    // with the default parameter
    if ( p1.name_ != "John Doe" || p1.adhaarNumber_ != "1234 5678 9230" || p1.dateOfBirth_ != Date(16, 11, 1998) ||
         p1.gender_ != Passenger::Gender::Male || p1.category_ != Passenger::Category::General || p1.mobileNumber_ != "NA" )
    { cout << "Error in construction of 'Passenger' instance Passenger 'p1(\"John Doe\", \"1234 5678 9230\", Date(16,11,1998), Passenger::Gender::Male, Passenger::Category::General)'" << endl ; allPassed = false ;  }

    // TEST 2 : Construct a 'Passenger' instance by passing the sixth parameter
    Passenger p2("Jane Doe", "9230 5678 1234", Date(25, 12, 1991), Passenger::Gender::Female, Passenger::Category::Ladies, "9872488100") ;
    
    // Check all the data members and match them with the passed parameters. Match 'Passenger::mobileNumber_' data member
    // with the default parameter
    if ( p2.name_ != "Jane Doe" || p2.adhaarNumber_ != "9230 5678 1234" || p2.dateOfBirth_ != Date(25, 12, 1991) ||
         p2.gender_ != Passenger::Gender::Female || p2.category_ != Passenger::Category::Ladies || p2.mobileNumber_ != "9872488100" )
    { cout << "Error in construction of 'Passenger' instance Passenger 'p2(\"Jane Doe\", \"9230 5678 1234\", Date(25, 12, 1991), Passenger::Gender::Female, Passenger::Category::Ladies, \"9872488100\")'" << endl ; allPassed = false ;  }

    // TEST 3 : Check copy constructor
    Passenger p3 = p2 ;
    // compare the data members of the two objects
    if ( p2.name_ != p3.name_ || p2.adhaarNumber_ != p3.adhaarNumber_ || p2.dateOfBirth_ != p3.dateOfBirth_ ||
         p2.gender_ != p3.gender_ || p2.category_ != p3.category_ || p2.mobileNumber_ != p3.mobileNumber_ )  
    { cout << "Error in construction of 'Passenger' instance by the copy constructor 'Passenger::Passenger(const Passenger&)'" << endl ; allPassed = false ; }

    // TEST 4 : Check copy assignment operator
    p2 = p1 ;
    // compare the data members of the two objects
    if ( p2.name_ != p1.name_ || p2.adhaarNumber_ != p1.adhaarNumber_ || p2.dateOfBirth_ != p1.dateOfBirth_ ||
         p2.gender_ != p1.gender_ || p2.category_ != p1.category_ || p2.mobileNumber_ != p1.mobileNumber_ )  
    { cout << "Error in correctly assigning all the data members in the destination instance from the source instance by the copy assignment operator 'const Passenger& Passenger::operator=(const Passenger&)'" << endl ; allPassed = false ; }

    // TEST 5 : Check overloaded output streaming operator
    cout << p1 ;    // stream a single instance
    cout << p3 << p2 << p1 ; // stream a chain of instances

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed

}