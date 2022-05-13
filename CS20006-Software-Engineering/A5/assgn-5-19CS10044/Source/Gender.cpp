
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include "Gender.h"
using namespace std ;

// initialize static const data members for the Gender sub-types
template<> const string Gender::Male::sName = "Male" ;
template<> const string Gender::Female::sName = "Female" ;
template<> const string Gender::Male::sSalutation = "Mr." ;
template<> const string Gender::Female::sSalutation = "Ms." ;

// overloaded output streaming operator
ostream & operator << ( ostream & out , const Gender & g )
{
    out << g.GetName() << " / " << g.GetTitle() ;   // print the name and salutation of the gender onto the console
    return out ;    // returning the 'ostream' object is important for streaming 
                    // of multiple instances chained in the same instruction
}

// implementation of the Unit Test Plan written for Gender hierarchy
void Gender::UnitTestGenderHierarchy ( )
{
    const Gender & g1 = Gender::Male::Type() ;
    const Gender & g2 = Gender::Male::Type() ;

    if ( &g1 == &g2 )   // check if the Gender sub-type is constructed only once.
                        // compare the addresses to ensure that they are indeed the same instances and
                        // hence the sub-type class is indeed a singleton class
        cout << "   TEST CASE H.1.1 PASSED" << endl ;
    
    // test static member function
    // match with golden outputs
    if ( Gender::IsMale(Gender::Male::Type()) == true )
        cout << "   TEST CASE H.1.2.1 PASSED" << endl ;
    
    if ( Gender::IsMale(Gender::Female::Type()) == false )
        cout << "   TEST CASE H.1.2.2 PASSED" << endl ;
    
    // test non static member functions
    // match with golden outputs
    if ( Gender::Male::Type().GetName() == "Male" )
        cout << "   TEST CASE H.2.1.1 PASSED" << endl ;
    
    if ( Gender::Female::Type().GetName() == "Female" )
        cout << "   TEST CASE H.2.1.2 PASSED" << endl ;
    
    if ( Gender::Male::Type().GetTitle() == "Mr." )
        cout << "   TEST CASE H.2.2.1 PASSED" << endl ;
    
    if ( Gender::Female::Type().GetTitle() == "Ms." )
        cout << "   TEST CASE H.2.2.2 PASSED" << endl ;
    
    // print the Gender sub-types onto the console
    cout << "   TEST CASE H.3.1.1 -- " << Gender::Male::Type() << endl ;
    cout << "   TEST CASE H.3.1.2 -- " << Gender::Female::Type() << endl ;

    // check dynamic dispatch for the polymorphic methods
    const Gender & g3 = Gender::Female::Type() ;    // upcast the Gender sub-type to the const reference of base class
    if ( g1.GetTitle() == "Mr." )
        cout << "   TEST CASE H.4.1.1 PASSED" << endl ;
    if ( g3.GetTitle() == "Ms." )
        cout << "   TEST CASE H.4.1.2 PASSED" << endl ;

}
