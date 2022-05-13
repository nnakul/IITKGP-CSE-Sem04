
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#pragma once
#include <iostream>
#include <string>
#include "Date.h"
#include "Gender.h"
#include "Divyaang.h"
using namespace std ;

class Passenger
{
    private :   // data members
        const string firstName_ ;
        const string middleName_ ;
        const string lastName_ ;
        const Date dateOfBirth_ ;
        const Gender & gender_ ;
        const string adhaarNumber_ ;
        string mobileNumber_ ;
        const Divyaang * const disabilityType_ ;
        const string disabilityID_ ;
        Passenger & operator = ( const Passenger & ) { }   // the copy assignment operator is blocked because Passenger
                                                           // has const data members that cannot be changed

        // constructor -- kept private because the arguements passed to the constructor
        // have to be first checked for validity so that the constructor does not need to 
        // throw an exception 
        Passenger ( const Date & , const Gender & , const string & , const string & , const string & ,
                    const string & , const string & , const Divyaang * , const string & ) ;
        
    public :
        static Passenger CreatePassenger (  const Date & , const string & , const string & , const string & = "" , const string & = "" ,
                                            const string & = "" , const string & = "" , const Divyaang * = NULL , const string & = "" ) ;    
                                                            // static member function. This is what is used in the application
                                                            // in place of the constructor.
        Passenger ( const Passenger & ) ;   // copy constructor
        friend ostream & operator << ( ostream & , const Passenger & ) ;  // overloaded output streaming operator. Useful in testing.
                                                                          // it is not a member function but rather a global function
                                                                          // that is a "friend" of Passenger
        bool operator == ( const Passenger & ) const ;    // overloaded equality checking operator. Very useful in testing.
        ~Passenger ( ) ;    // destructor
        // non static member functions
        inline const Gender & GetGender ( ) const ;
        inline const Divyaang * GetDisabilityType ( ) const ;
        inline unsigned int GetAge ( ) const ;
        // implements the unit test plan for Passenger class
        static void UnitTestPassenger ( ) ;
} ;

inline const Gender & Passenger::GetGender ( ) const    // implementation of "Passenger::GetGender" as an inline function
{   return gender_ ;    }

inline unsigned int Passenger::GetAge ( ) const    // implementation of "Passenger::GetAge" as an inline function
{   return Date::GetTodaysDate().GetDifferenceInYears(dateOfBirth_) ;   }

inline const Divyaang * Passenger::GetDisabilityType ( ) const    // implementation of "Passenger::GetDisabilityType" as an inline function
{   return disabilityType_ ;   }