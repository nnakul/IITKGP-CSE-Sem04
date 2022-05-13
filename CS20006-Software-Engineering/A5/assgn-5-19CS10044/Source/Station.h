
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#pragma once
#include <iostream>
#include <string>
using namespace std ;

class Station
{
    private :
        const string name_ ;    // the only non-static data member of the class
        Station & operator = ( const Station & ) {  }   // the copy assignment operator is blocked because the 
                                                        // only data member of any Station instance is constant
        Station ( const string & ) ;    // constructor -- kept private because the arguements passed to the constructor
                                        // have to be first checked for validity so that the constructor does not need to 
                                        // throw an exception 

    public :
        static Station CreateStation ( const string & ) ;   // static member function. This is what is used in the application
                                                            // in place of the constructor.
        Station ( const Station & ) ;   // copy constructor. 
        bool operator == ( const Station & ) const ;    // overloaded equality checking operator. Useful in testing.
        bool operator != ( const Station & ) const ;    // overloaded inequality checking operator. Useful in testing.
        friend ostream & operator << ( ostream & , const Station & ) ;    // overloaded output streaming operator. Useful in testing.
                                                                          // it is not a member function but rather a global function
                                                                          // that is a "friend" of Station
        // Non Static Member functions
        inline string GetName ( ) const ;
        unsigned int GetDistance ( const Station & ) const ;
        ~Station ( ) ;  // destructor
        static void UnitTestStation ( ) ;   // implements the unit test plan written for Station class
} ;

inline string Station::GetName ( ) const    // implementation of "Station::GetName" as an inline function
{   return name_ ;  }

