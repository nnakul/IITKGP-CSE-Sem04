
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <regex>
#include <cmath>
#include "Date.h"
#include "Exceptions.h"
using namespace std ;

// initializing static constants of Date
const vector<string> Date::sMonthNames = { "January" , "February" , "March" , "April" , "May" , "June" , 
                                           "July" , "August" , "September" , "October" , "November" , "December" } ;
const vector<string> Date::sDayNames = { "Monday" , "Tuesday" , "Wednesday" , "Thursday" , "Friday" , "Saturday" , "Sunday" } ;
const vector<unsigned int> Date::sDaysInMonths = { 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 } ;
// intialize based on the master data
const unsigned int Date::sMaxValidYear = 2099 ;
const unsigned int Date::sMinValidYear = 1900 ;

// constructor
Date::Date ( unsigned int d , unsigned int m , unsigned int y )
    : date_(d) , month_(m) , year_(y)   // initializer list
{   
    #ifdef _DEBUG
        cout << "Date CONSTRUCTED : " << *this << endl ;
    #endif
}

Date Date::CreateDate ( const string & date )
{
    // FIRST CHECK FOR THE VALIDITY OF THE DATE IN STRING FORMAT
    regex dateFormat("[0-9]{2}/[0-9]{2}/[0-9]{4}") ;    // regex object -- used for matching patterns
                                                        // this pattern the conventional format of a valid date    
    if ( ! regex_match(date, dateFormat) )  // match the string with the regex object
        throw Bad_Date_Format("Incorrect string format for a date") ;
    
    // parse the string and extract the date, month and year from it
    unsigned int d = stoul(date.substr(0, 2)) ;
    unsigned int m = stoul(date.substr(3, 2)) ;
    unsigned int y = stoul(date.substr(6, 4)) ;
    
    // check if year is in bounds
    if ( y < Date::sMinValidYear || y > Date::sMaxValidYear )
        throw Bad_Date_Year("Year cannot be outside of bounds") ;
    // check if month is in bounds
    if ( m < 1 || m > 12 )
        throw Bad_Date_Month("Month cannot be outside of bounds") ;
    // check if day is in bounds
    if ( d < 1 || d > 31 )
        throw Bad_Date_Day("Day cannot be outside of [1, 31]") ;
    // handle case of February separately
    if ( m == 2 )
    {
        if ( d > 29 )   // February can never have more than 29 days, in any year
            throw Bad_Date_Day("February can not have more than 29 days") ;
        if ( y % 4 != 0 && d > 28 ) // February cannot have more than 28 days in February of a non-leap year
            throw Bad_Date_Day("February can not have more than 28 days in a non-leap year") ;
    }
    else
        // check if day is in bounds, depending on the no. of days in the month
        if ( d > Date::sDaysInMonths.at(m-1) )
            throw Bad_Date_Day("Day cannot be outside of bounds") ;
    // this implies all the arguements are validated and a Date object can be constructed
    return Date(d, m, y) ;
    // return the constructed object by-value
}

Date Date::CreateDate ( unsigned int d , unsigned int m , unsigned int y )
{
    // FIRST CHECK FOR THE VALIDITY OF THE DATE IN TRIPLET FORMAT
    // check if year is in bounds
    if ( y < Date::sMinValidYear || y > Date::sMaxValidYear )
        throw Bad_Date_Year("Year cannot be outside of bounds") ;
    // check if month is in bounds
    if ( m < 1 || m > 12 )
        throw Bad_Date_Month("Month cannot be outside of bounds") ;
    // check if day is in bounds
    if ( d < 1 || d > 31 )
        throw Bad_Date_Day("Day cannot be outside of [1, 31]") ;
    // handle case of February separately
    if ( m == 2 )
    {
        if ( d > 29 )   // February can never have more than 29 days, in any year
            throw Bad_Date_Day("February can not have more than 29 days") ;
        if ( y % 4 != 0 && d > 28 ) // February cannot have more than 28 days in February of a non-leap year
            throw Bad_Date_Day("February can not have more than 28 days in a non-leap year") ;
    }
    else
        // check if day is in bounds, depending on the no. of days in the month
        if ( d > Date::sDaysInMonths.at(m-1) )
            throw Bad_Date_Day("Day cannot be outside of bounds") ;
    // this implies all the arguements are validated and a Date object can be constructed
    return Date(d, m, y) ;
    // return the constructed object by-value
}

Date Date::GetTodaysDate ( )
{
    // all this functions are declared in <ctime> header
    time_t t = time(0) ;
    tm* now = localtime(&t) ;   // get current time
    return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900) ;   
    // construct Date object based on the current time -- 'now'
    // and then return it by value
}

int Date::GetDifferenceInYears ( const Date & d ) const
{
    // STRATEGY -- Count the number of days passed since the hypothetical
    // reference date 00/00/0000, for both the Date objects; and then find the
    // difference between the two numbers of days and scale the difference to get
    // it in years
    unsigned int count1 = 0 ;
    if ( year_ % 4 == 0 )   // handle leap year differently -- account for the extra day(s)
        count1 += (year_/4 -1) * 366 + (3*year_/4) * 365 ;
    else 
        count1 += (year_/4) * 366 + (year_-year_/4-1) * 365 ;
    int i = 1 ;
    while ( i < month_ )    // loop over the already passed months of the year in which the date is
    {
        if ( i == 2 )   // for month of February
        {
            if ( year_ % 4 )    count1 += 28 ;  // non-leap year Feb has 28 days
            else count1 += 29 ; i++ ;  // leap year Feb has 29 days
            continue ;
        }
        count1 += Date::sDaysInMonths.at(i++) ;
    }
    count1 += date_ ; // add no. of days already passed in the month in which the date is

    // Repeat the entire procedure (exactly same) for the second Date object --
    // the one that is passed as arguement
    unsigned int count2 = 0 ;
    if ( d.year_ % 4 == 0 )
        count2 += (d.year_/4 -1) * 366 + (3*d.year_/4) * 365 ;
    else 
        count2 += (d.year_/4) * 366 + (d.year_-d.year_/4-1) * 365 ;
    i = 1 ;
    while ( i < d.month_ )
    {
        if ( i == 2 )
        {
            if ( d.year_ % 4 )    count2 += 28 ;
            else count2 += 29 ; i++ ;
            continue ;
        }
        count2 += Date::sDaysInMonths.at(i++) ;
    }
    count2 += d.date_ ;
    int difference = count1 - count2 ;  // finally take the difference
    return round(difference / 365.25) ; // divide it by the average no. of days in a year and round it off
                                        // before returning
}

int Date::GetDifferenceInDays ( const Date & d ) const
{
    // STRATEGY -- Count the number of days passed since the hypothetical
    // reference date 00/00/0000, for both the Date objects; and then find the
    // difference between the two numbers of days and scale the difference to get
    // it in years
    unsigned int count1 = 0 ;
    if ( year_ % 4 == 0 )   // handle leap year differently -- account for the extra day(s)
        count1 += (year_/4 -1) * 366 + (3*year_/4) * 365 ;
    else 
        count1 += (year_/4) * 366 + (year_-year_/4-1) * 365 ;
    int i = 1 ;
    while ( i < month_ )    // loop over the already passed months of the year in which the date is
    {
        if ( i == 2 )   // for month of February
        {
            if ( year_ % 4 )    count1 += 28 ;  // non-leap year Feb has 28 days
            else count1 += 29 ; i++ ;  // leap year Feb has 29 days
            continue ;
        }
        count1 += Date::sDaysInMonths.at(i++) ;
    }
    count1 += date_ ; // add no. of days already passed in the month in which the date is

    // Repeat the entire procedure (exactly same) for the second Date object --
    // the one that is passed as arguement
    unsigned int count2 = 0 ;
    if ( d.year_ % 4 == 0 )
        count2 += (d.year_/4 -1) * 366 + (3*d.year_/4) * 365 ;
    else 
        count2 += (d.year_/4) * 366 + (d.year_-d.year_/4-1) * 365 ;
    i = 1 ;
    while ( i < d.month_ )
    {
        if ( i == 2 )
        {
            if ( d.year_ % 4 )    count2 += 28 ;
            else count2 += 29 ; i++ ;
            continue ;
        }
        count2 += Date::sDaysInMonths.at(i++) ;
    }
    count2 += d.date_ ;
    int difference = count1 - count2 ;  // finally take the difference
    return difference ;  // and return it
}

bool Date::IsAfter ( const Date & d ) const
{ return ( this->GetDifferenceInDays(d) > 0 ) ; }
// use Date::GetDifferenceInDays method as the subroutine

// copy constructor
Date::Date ( const Date & date )
    :   date_(date.date_) , month_(date.month_) , year_(date.year_) // initializer list
{   
    #ifdef _DEBUG
        cout << "Date CONSTRUCTED : " << *this << endl ;
    #endif
}

Date & Date::operator = ( const Date & date )   // overloaded copy assignment operator
{
    date_ = date.date_ ; month_ = date.month_ ; year_ = date.year_ ;
    return *this ;      // return the instance to which the parameter 
                        // is copied to enable chained assignment operations
}

bool Date::operator == ( const Date & d ) const   // overloaded equality check operator
{   return ( d.date_  == date_ ) && ( d.month_  == month_ ) &&  ( d.year_  == year_ ) ; }
// two 'Date' instances are "equal" if and only if they have the same date, month and year.

bool Date::operator != ( const Date & d ) const   // overloaded inequality check operator
{   return ( d.date_  != date_ ) || ( d.month_  != month_ ) ||  ( d.year_  != year_ ) ; }
// two 'Date' instances are "unequal" if and only if atleast one of the date, month and year is unequal.

ostream & operator << ( ostream & out , const Date & date ) // overloaded output streaming operator
{
    // print date in "DD/MMM/YYYY" format, where the day and year are written in numbers and
    // the month is represented by the 3-letter prefix of its name.
    out << setw(2) << setfill('0') << date.date_ ; cout << "/" ;  // set width 2 and pad with a leading zero if required
    out << Date::sMonthNames[date.month_-1].substr(0, 3) ; cout << "/" ;
    out << setw(4) << setfill('0') << date.year_ ;  // set width 4 and pad with leading zeroes if required
    return out ;    // returning the 'ostream' object is important for streaming 
                    // of multiple instances chained in the same instruction
}

Date::~Date ( ) 
{   
    #ifdef _DEBUG
        cout << "Date DESTRUCTED : " << *this << endl ;
    #endif
}     // no explicit memory management needed -- no dynamically 
      // allocated memory for any data member -- hence empty body


// Implementing the unit test plan written for Date class
void Date::UnitTestDate ( )
{
    // TEST CASES FOR CHECKING ERRONEOUS DATE FORMATS/INPUTS BY STRINGS
    // bad formats for dates represented by strings
    try
    { Date::CreateDate("16/11/20") ; }
    catch( Bad_Date_Format )
    { cout << "   TEST CASE C.1.1.1 PASSED" << endl ; }

    try
    { Date::CreateDate("2020/11/16") ; }
    catch( Bad_Date_Format )
    { cout << "   TEST CASE C.1.1.2 PASSED" << endl ; }

    try
    { Date::CreateDate("4/11/2020") ; }
    catch( Bad_Date_Format )
    { cout << "   TEST CASE C.1.1.3 PASSED" << endl ; }

    try
    { Date::CreateDate("04/Nov/2020") ; }
    catch( Bad_Date_Format )
    { cout << "   TEST CASE C.1.1.4 PASSED" << endl ; }

    try
    { Date::CreateDate("16-11-2020") ; }
    catch( Bad_Date_Format )
    { cout << "   TEST CASE C.1.1.5 PASSED" << endl ; }
    
    // year out of bounds
    try
    { Date::CreateDate("16/11/1889") ; }
    catch( Bad_Date_Year )
    { cout << "   TEST CASE C.1.2.1 PASSED" << endl ; }

    try
    { Date::CreateDate("16/11/2100") ; }
    catch( Bad_Date_Year )
    { cout << "   TEST CASE C.1.2.2 PASSED" << endl ; }

    // months out of bounds
    try
    { Date::CreateDate("16/00/2020") ; }
    catch( Bad_Date_Month )
    { cout << "   TEST CASE C.1.3.1 PASSED" << endl ; }

    try
    { Date::CreateDate("16/13/2020") ; }
    catch( Bad_Date_Month )
    { cout << "   TEST CASE C.1.3.2 PASSED" << endl ; }

    // various scenarios when the date is out of bounds
    try
    { Date::CreateDate("32/11/2020") ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.1.4.1 PASSED" << endl ; }

    try
    { Date::CreateDate("00/11/2020") ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.1.4.2 PASSED" << endl ; }

    // specific test cases for the month of February
    try
    { Date::CreateDate("30/02/2020") ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.1.5.1 PASSED" << endl ; }

    try
    { Date::CreateDate("30/02/2021") ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.1.5.2 PASSED" << endl ; }

    try
    { Date::CreateDate("29/02/2021") ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.1.5.3 PASSED" << endl ; }

    // check if the 31st day is permitted for those months that have exactly 30 days
    try
    { Date::CreateDate("31/04/2020") ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.1.6.1 PASSED" << endl ; }

    try
    { Date::CreateDate("31/04/2021") ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.1.6.2 PASSED" << endl ; }

    try
    { Date::CreateDate("31/06/2020") ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.1.6.3 PASSED" << endl ; }

    try
    { Date::CreateDate("31/09/2020") ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.1.6.4 PASSED" << endl ; }

    try
    { Date::CreateDate("31/11/2020") ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.1.6.5 PASSED" << endl ; }

    // test various scenarios of valid dates represented by valid strings
    // involves matching with golden/expected output(s)
    Date d1 = Date::CreateDate("01/01/1900") ;
    if ( d1.date_ == 1 && d1.month_ == 1 && d1.year_ == 1900 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.1.7.1 PASSED" << endl ;

    Date d2 = Date::CreateDate("31/12/2099") ;
    if ( d2.date_ == 31 && d2.month_ == 12 && d2.year_ == 2099 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.1.7.2 PASSED" << endl ;
    
    Date d3 = Date::CreateDate("29/02/2020") ;
    if ( d3.date_ == 29 && d3.month_ == 2 && d3.year_ == 2020 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.1.7.3 PASSED" << endl ;
    
    Date d4 = Date::CreateDate("28/02/2021") ;
    if ( d4.date_ == 28 && d4.month_ == 2 && d4.year_ == 2021 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.1.7.4 PASSED" << endl ;
    
    Date d5 = Date::CreateDate("30/04/2021") ;
    if ( d5.date_ == 30 && d5.month_ == 4 && d5.year_ == 2021 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.1.7.5 PASSED" << endl ;
    
    Date d6 = Date::CreateDate("30/04/2020") ;
    if ( d6.date_ == 30 && d6.month_ == 4 && d6.year_ == 2020 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.1.7.6 PASSED" << endl ;
    
    Date d7 = Date::CreateDate("30/06/2021") ;
    if ( d7.date_ == 30 && d7.month_ == 6 && d7.year_ == 2021 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.1.7.7 PASSED" << endl ;
    
    Date d8 = Date::CreateDate("30/09/2021") ;
    if ( d8.date_ == 30 && d8.month_ == 9 && d8.year_ == 2021 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.1.7.8 PASSED" << endl ;
    
    Date d9 = Date::CreateDate("30/11/2021") ;
    if ( d9.date_ == 30 && d9.month_ == 11 && d9.year_ == 2021 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.1.7.9 PASSED" << endl ;

    // TEST CASES FOR CHECKING ERRONEOUS DATE FORMATS/INPUTS BY TRIPLETS OF UNSIGNED INTEGERS
    // year out of bounds
    try
    { Date::CreateDate(16, 11, 1889) ; }
    catch( Bad_Date_Year )
    { cout << "   TEST CASE C.2.1.1 PASSED" << endl ; }

    try
    { Date::CreateDate(16, 11, 2100) ; }
    catch( Bad_Date_Year )
    { cout << "   TEST CASE C.2.1.2 PASSED" << endl ; }

    // month out of bounds
    try
    { Date::CreateDate(16, 0, 2021) ; }
    catch( Bad_Date_Month )
    { cout << "   TEST CASE C.2.2.1 PASSED" << endl ; }

    try
    { Date::CreateDate(16, 13, 2021) ; }
    catch( Bad_Date_Month )
    { cout << "   TEST CASE C.2.2.2 PASSED" << endl ; }

    // various scenarios when the date is out of bounds
    try
    { Date::CreateDate(32, 11, 2020) ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.2.3.1 PASSED" << endl ; }

    try
    { Date::CreateDate(0, 11, 2020) ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.2.3.2 PASSED" << endl ; }

    // specific test cases for the month of February
    try
    { Date::CreateDate(30, 2, 2020) ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.2.4.1 PASSED" << endl ; }

    try
    { Date::CreateDate(30, 2, 2021) ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.2.4.2 PASSED" << endl ; }

    try
    { Date::CreateDate(29, 2, 2021) ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.2.4.3 PASSED" << endl ; }

    // check if the 31st day is permitted for those months that have exactly 30 days
    try
    { Date::CreateDate(31, 4, 2020) ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.2.5.1 PASSED" << endl ; }

    try
    { Date::CreateDate(31, 4, 2021) ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.2.5.2 PASSED" << endl ; }

    try
    { Date::CreateDate(31, 6, 2020) ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.2.5.3 PASSED" << endl ; }

    try
    { Date::CreateDate(31, 9, 2020) ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.2.5.4 PASSED" << endl ; }

    try
    { Date::CreateDate(31, 11, 2020) ; }
    catch( Bad_Date_Day )
    { cout << "   TEST CASE C.2.5.5 PASSED" << endl ; }

    // test various scenarios of valid dates constructed by valid triplets
    // involves matching with golden/expected output(s)
    d1 = Date::CreateDate(1, 1, 1900) ;
    if ( d1.date_ == 1 && d1.month_ == 1 && d1.year_ == 1900 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.2.6.1 PASSED" << endl ;

    d2 = Date::CreateDate(31, 12, 2099) ;
    if ( d2.date_ == 31 && d2.month_ == 12 && d2.year_ == 2099 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.2.6.2 PASSED" << endl ;
    
    d3 = Date::CreateDate(29, 2, 2020) ;
    if ( d3.date_ == 29 && d3.month_ == 2 && d3.year_ == 2020 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.2.6.3 PASSED" << endl ;
    
    d4 = Date::CreateDate(28, 2, 2021) ;
    if ( d4.date_ == 28 && d4.month_ == 2 && d4.year_ == 2021 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.2.6.4 PASSED" << endl ;
    
    d5 = Date::CreateDate(30, 4, 2021) ;
    if ( d5.date_ == 30 && d5.month_ == 4 && d5.year_ == 2021 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.2.6.5 PASSED" << endl ;
    
    d6 = Date::CreateDate(30, 4, 2020) ;
    if ( d6.date_ == 30 && d6.month_ == 4 && d6.year_ == 2020 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.2.6.6 PASSED" << endl ;
    
    d7 = Date::CreateDate(30, 6, 2021) ;
    if ( d7.date_ == 30 && d7.month_ == 6 && d7.year_ == 2021 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.2.6.7 PASSED" << endl ;
    
    d8 = Date::CreateDate(30, 9, 2021) ;
    if ( d8.date_ == 30 && d8.month_ == 9 && d8.year_ == 2021 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.2.6.8 PASSED" << endl ;
    
    d9 = Date::CreateDate(30, 11, 2021) ;
    if ( d9.date_ == 30 && d9.month_ == 11 && d9.year_ == 2021 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.2.6.9 PASSED" << endl ;

    Date d10 = Date::CreateDate(10, 9) ;
    if ( d10.date_ == 10 && d10.month_ == 9 && d10.year_ == 1900 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.2.7 PASSED" << endl ;

    d10 = Date::CreateDate(10) ;
    if ( d10.date_ == 10 && d10.month_ == 1 && d10.year_ == 1900 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.2.8 PASSED" << endl ;
    
    d10 = Date::CreateDate() ;
    if ( d10.date_ == 1 && d10.month_ == 1 && d10.year_ == 1900 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.2.9 PASSED" << endl ;

    // test copy constructor
    d10 = Date::CreateDate("02/04/2021") ;
    Date d11 = d10 ;
    if ( d11.date_ == 2 && d11.month_ == 4 && d11.year_ == 2021 )  // check if non-static data members were correctly initialized
        cout << "   TEST CASE C.3.1 PASSED" << endl ;

    // test overloaded equality operator
    d10 = Date::CreateDate("01/01/2020") ;
    d11 = Date::CreateDate("01/01/2021") ;
    if ( ! ( d10 == d11 ) )
        cout << "   TEST CASE C.4.1 PASSED" << endl ;

    d10 = Date::CreateDate("01/01/2021") ;
    if ( d10 == d11 )
        cout << "   TEST CASE C.4.2 PASSED" << endl ;

    // test overloaded inequality operator
    d10 = Date::CreateDate("01/01/2020") ;
    d11 = Date::CreateDate("01/01/2021") ;
    if ( d10 != d11 )
        cout << "   TEST CASE C.5.1 PASSED" << endl ;

    d10 = Date::CreateDate("01/01/2021") ;
    if ( ! ( d10 != d11 ) )
        cout << "   TEST CASE C.5.2 PASSED" << endl ;

    // print the Date object onto the console using overloaded output streaming operator
    cout << "   TEST CASE C.6.1 --  " << Date::CreateDate("01/01/2021") << endl ;

    // test overloaded copy assignment operator
    d10 = Date::CreateDate("01/01/2020") ;
    d11 = Date::CreateDate("03/04/2021") ;
    d10 = d11 ;
    if ( d10.date_ == 3 && d10.month_ == 4 && d10.year_ == 2021 )
        cout << "   TEST CASE C.7.1 PASSED" << endl ;

    // TEST NON-STATIC MEMBER FUNCTIONS
    Date today = Date::GetTodaysDate() ;
    // check if the current date on calendar matches the one represented by the data members of Date object 'today'
    if ( today.date_ == 8 && today.month_ == 4 && today.year_ == 2021 ) // (**) golden output naturally depends on the date of execution of this test case
        cout << "   TEST CASE C.8.1 PASSED" << endl ;

    // various scenarios of testing Date::GetDifferenceInYears
    // match with golden/expected output
    if ( Date::CreateDate("11/03/2022").GetDifferenceInYears(Date::CreateDate("02/04/2021")) == 1 )
        cout << "   TEST CASE C.9.1.1 PASSED" << endl ;
    
    if ( Date::CreateDate("11/12/2022").GetDifferenceInYears(Date::CreateDate("02/04/2021")) == 2 )
        cout << "   TEST CASE C.9.1.2 PASSED" << endl ;

    if ( Date::CreateDate("11/09/2021").GetDifferenceInYears(Date::CreateDate("02/04/2021")) == 0 )
        cout << "   TEST CASE C.9.2.1 PASSED" << endl ;
    
    if ( Date::CreateDate("02/12/2020").GetDifferenceInYears(Date::CreateDate("02/04/2021")) == 0 )
        cout << "   TEST CASE C.9.2.2 PASSED" << endl ;

    if ( Date::CreateDate("02/04/2021").GetDifferenceInYears(Date::CreateDate("11/05/2022")) == -1 )
        cout << "   TEST CASE C.9.3.1 PASSED" << endl ;
    
    if ( Date::CreateDate("02/04/2021").GetDifferenceInYears(Date::CreateDate("11/12/2022")) == -2 )
        cout << "   TEST CASE C.9.3.2 PASSED" << endl ;

    // various scenarios of testing Date::GetDifferenceInDays
    // match with golden/expected output
    if ( Date::CreateDate("02/04/2021").GetDifferenceInDays(Date::CreateDate("02/04/2019")) == 731 )
        cout << "   TEST CASE C.9.4.1 PASSED" << endl ;
    
    if ( Date::CreateDate("02/04/2021").GetDifferenceInDays(Date::CreateDate("01/04/2021")) == 1 )
        cout << "   TEST CASE C.9.4.2 PASSED" << endl ;

    if ( Date::CreateDate("02/04/2021").GetDifferenceInDays(Date::CreateDate("02/04/2021")) == 0 )
        cout << "   TEST CASE C.9.5 PASSED" << endl ;

    if ( Date::CreateDate("02/04/2019").GetDifferenceInDays(Date::CreateDate("02/04/2021")) == -731 )
        cout << "   TEST CASE C.9.6.1 PASSED" << endl ;
    
    if ( Date::CreateDate("01/04/2021").GetDifferenceInDays(Date::CreateDate("02/04/2021")) == -1 )
        cout << "   TEST CASE C.9.6.2 PASSED" << endl ;

    // various scenarios of testing Date::IsAfter
    if ( ! Date::CreateDate("02/04/2021").IsAfter(Date::CreateDate("02/04/2021")) ) // both Date objects represent the same date
        cout << "   TEST CASE C.9.7.1 PASSED" << endl ;
    
    if ( ! Date::CreateDate("01/04/2021").IsAfter(Date::CreateDate("02/04/2021")) ) // parameter Date object in future of the other
        cout << "   TEST CASE C.9.7.2 PASSED" << endl ;

    if ( Date::CreateDate("02/04/2021").IsAfter(Date::CreateDate("01/04/2021")) ) // parameter Date object in past of the other
        cout << "   TEST CASE C.9.8 PASSED" << endl ;

    // various scenarios of testing Date::IsLeapYear
    if ( ! Date::CreateDate("02/04/2021").IsLeapYear() )
        cout << "   TEST CASE C.9.9 PASSED" << endl ;
    
    if ( Date::CreateDate("02/04/2020").IsLeapYear() )
        cout << "   TEST CASE C.9.10 PASSED" << endl ;
    
}