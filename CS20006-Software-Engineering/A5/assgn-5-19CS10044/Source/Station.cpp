
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include "Railways.h"
#include "Exceptions.h"
using namespace std ;

// constructor
Station::Station ( const string & name )
    :   name_(name)     // initializer-list
{   
    #ifdef _DEBUG
        cout << "Station CONSTRUCTED : " << name << endl ;
    #endif
}

// copy constructor
Station::Station ( const Station & station )
    :   name_(station.name_)    // initializer-list
{   
    #ifdef _DEBUG
        cout << "Station CONSTRUCTED : " << station.name_ << endl ;
    #endif
}

Station Station::CreateStation ( const string & name )
{
    if ( name.find_first_not_of(' ') == name.npos ) // there must be at least one character in the name other than the whitespace.
                                                    // If such character is not found, the string is empty (has no meaningful characters
                                                    // to define the name).
        throw Bad_Station("Station name cannot be empty") ; // in this case throw Bad_Station exception
    return Station(name) ;  // otherwise call the private constructor and return the new instance by value
}

bool Station::operator == ( const Station & s ) const
{   return s.name_ == name_ ;   }   // two 'Station' objects are said to be "equal" if and only if they
                                    // have the same name.

bool Station::operator != ( const Station & s ) const
{   return s.name_ != name_ ;   }   // two 'Station' objects are said to be "unequal" if and only if they
                                    // have different names.

ostream & operator << ( ostream & out , const Station & station )
{
    out << "[ " << station.name_ << " ]" ;      // sqaure brackets help in identifying the 'Station' data type
                                                // when printed on terminal.
    return out ;    // returning the 'ostream' object is important for streaming 
                    // of multiple instances chained in the same instruction
}

unsigned int Station::GetDistance ( const Station & station  ) const
{  
    // use the routine of 'unsigned int Railways::GetDistance(const Station &, const Station &) const'
    // method to obtain the distance between the two stations
    // The definition of 'Railways::GetDistance' is given in "Railways.cpp" file.
    unsigned int d = 0 ;
    try // 'Railways::SpecialRailways' method can thrown an exception if the
        // distance between the two Station objects passed as parameters is
        // not defined in the map data member of the singleton Railways object.
    { d = Railways::SpecialRailways().GetDistance(*this, station) ; }
    catch ( Bad_Railways_Distance )     // in this the exception has to be caught
    { throw ; }     // and re-thrown
    return d ;  // otherwise, whatever distance is returned by 'Railways::SpecialRailways' is returned
}


Station::~Station ( ) 
{   
    #ifdef _DEBUG
        cout << "Station DESTRUCTED : " << name_ << endl ;
    #endif
}     // no explicit memory management needed -- no dynamically 
      // allocated memory for any data member -- hence empty body


// UNIT TEST PLAN FOR Station CLASS

void Station::UnitTestStation ( )
{
    Station s1 = Station::CreateStation("I am an arbitrary name") ;    // try constructing a Station with arbitrary non-empty name
    if ( s1.name_.compare("I am an arbirary name") )
        cout << "   TEST CASE A.1.1 PASSED" << endl ;

    try
    { Station::CreateStation("") ; }    // try constructing a Station with empty name
    catch ( Bad_Station )
    { cout << "   TEST CASE A.1.2.1 PASSED" << endl ; }

    try
    { Station::CreateStation("  ") ; }    // try constructing a Station with empty name
    catch ( Bad_Station )
    { cout << "   TEST CASE A.1.2.2 PASSED" << endl ; }

    // test copy constructor
    Station s2 = s1 ;
    if ( s2.name_ == s1.name_ )
        cout << "   TEST CASE A.2.1 PASSED" << endl ;

    // test the equality check operator
    Station s3 = Station::CreateStation("Delhi") ;
    Station s4 = Station::CreateStation("Mumbai") ;
    if ( ! ( s3 == s4 ) )
        cout << "   TEST CASE A.3.1 PASSED" << endl ;
    Station s5 = Station::CreateStation("Mumbai") ;
    if ( s5 == s4 )
        cout << "   TEST CASE A.3.2 PASSED" << endl ;

    // test the inequality check operator
    if ( s3 != s4 )
        cout << "   TEST CASE A.4.1 PASSED" << endl ;
    if ( ! ( s5 != s4 ) )
        cout << "   TEST CASE A.4.2 PASSED" << endl ;

    cout <<  "   TEST CASE A.5.1 -- \n\t" << s1 << endl ;

    // test non-static member functions
    if ( s1.GetName() == "I am an arbitrary name" )
        cout << "   TEST CASE A.6.1 PASSED" << endl ;
    if ( s4.GetDistance(s3) == 1447 )
        cout << "   TEST CASE A.6.2 PASSED" << endl ;

    // try to get distance from a Station with which it is not
    // defined in the Indian Railways 
    try
    { s4.GetDistance(Station::CreateStation("Pune")) ; }
    catch(Bad_Railways_Distance)
    { cout << "   TEST CASE A.6.3 PASSED" << endl ; }
    
}

