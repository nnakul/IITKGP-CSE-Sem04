
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std ;

class Date
{
    private :   
        unsigned int date_ , month_ , year_ ;   // non-static data members

        // static constants -- used in validating the arguement(s) passed to
        // Date::CreateDate method(s)
        static const vector<unsigned int> sDaysInMonths ;   // vector of size 12 -- stores the number of days in each month of the year
        static const unsigned int sMinValidYear ;   // minimum valid year -- as given in the master data of specifications
        static const unsigned int sMaxValidYear ;   // maximum valid year -- as given in the master data of specifications
        Date ( unsigned int , unsigned int , unsigned int ) ;   // constructor -- kept private because the arguements passed to the constructor
                                                                // have to be first checked for validity so that the constructor does not need to 
                                                                // throw an exception 
        
    public :
        static const vector<string> sMonthNames ; // static constant -- stores the names of the 12 months of a year
        static const vector<string> sDayNames ;   // static constant -- stores the names of the 7 days of a week
        Date ( const Date & ) ; // copy constructor
        
        // Static Member Functions --
        // These are the methods that are used in the application in place of the constructors.
        // They are overloaded in two types to provide flexibility in the arguements that need to be passed.
        static Date CreateDate ( const string & ) ;
        static Date CreateDate ( unsigned int = 1 , unsigned int = 1 , unsigned int = Date::sMinValidYear ) ;
        // returns the current date on the system/machine
        static Date GetTodaysDate ( ) ;

        int GetDifferenceInYears ( const Date & ) const ;   // returns the difference in years between two Date objects 
                                                            // -- difference can be negative
        int GetDifferenceInDays ( const Date & ) const ;    // returns the difference in days between two Date objects 
                                                            // -- difference can be negative
        bool IsAfter ( const Date & ) const ;   // checks if one Date occurs before the other on the calendar
        inline bool IsLeapYear ( ) const ;  // checks if a Date falls in a leap year

        Date & operator = ( const Date & ) ;  // overloaded copy assignment operator

        bool operator == ( const Date & ) const ;    // overloaded equality checking operator. Useful in testing
        bool operator != ( const Date & ) const ;    // overloaded inequality checking operator. Useful in testing
        friend ostream & operator << ( ostream & , const Date & ) ; // overloaded output streaming operator. Useful in testing.
                                                                    // it is not a member function but rather a global function
                                                                    // that is a "friend" of Date
        ~Date ( ) ; // destructor
        // Implements the unit test plan
        static void UnitTestDate ( ) ;
} ;

inline bool Date::IsLeapYear ( ) const // implementation of 'Date::IsLeapYear' as an inline function
{   return year_ % 4 == 0 ;     }