
//  SOFTWARE ENGINEERING -- ASSIGNMENT O3
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Date.h"
using namespace std ;

// initializing static constants
const vector<string> Date::sMonthNames = { "January" , "February" , "March" , "April" , "May" , "June" , 
                                           "July" , "August" , "September" , "October" , "November" , "December" } ;
const vector<string> Date::sDayNames = { "Monday" , "Tuesday" , "Wednesday" , "Thursday" , "Friday" , "Saturday" , "Sunday" } ;

Date::Date ( unsigned int d , unsigned int m , unsigned int y )
    :   date_(d) , month_(m) , year_(y) // initializer list
{   }

Date::Date ( const Date & date )
    :   date_(date.date_) , month_(date.month_) , year_(date.year_) // initializer list
{   }

Date & Date::operator = ( const Date & date )
{
    date_ = date.date_ ; month_ = date.month_ ; year_ = date.year_ ;
    return *this ;      // return the instance to which the parameter 
                        // is copied to enable chained assignment operations
}

bool Date::operator == ( const Date & d ) const
{   return ( d.date_  == date_ ) && ( d.month_  == month_ ) &&  ( d.year_  == year_ ) ; }
// two 'Date' instances are "equal" if and only if they have the same date, month and year.
// Note that two objects can have different locations in the memory and thus can be 
// distinct instances of 'Date' class but still they can be "equal" in a somewhat loose 
// sense if they have represent the same date on the calendar

bool Date::operator != ( const Date & d ) const
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

Date::~Date ( ) {   }     // no explicit memory management needed -- no dynamically 
                          // allocated memory for any data member -- hence empty body

void Date::UnitTestDate ( )
{
    cout << "\n\n [ Date::UnitTestDate ( ) ]" << endl ;
    bool allPassed = true ;

    //  TEST 1 : Check constructor
    Date d1, d2(5), d3(7, 11), d4(21, 10, 2021) ;

    if ( d1.date_ != 1 || d1.month_ != 1 || d1.year_ != 1970 )  // with no parameters -- default day, month, year
    { cout << "Error in construction of 'Date' instance on Date by 'Date::Date(unsigned int=1, unsigned int=1, unsigned int=1970)'" << endl ; allPassed = false ;  }
    if ( d2.date_ != 5 || d2.month_ != 1 || d2.year_ != 1970 )  // with one parameter -- default month, year
    { cout << "Error in construction of 'Date' instance on Date(5) by 'Date::Date(unsigned int=1, unsigned int=1, unsigned int=1970)'" << endl ; allPassed = false ;  }
    if ( d3.date_ != 7 || d3.month_ != 11 || d3.year_ != 1970 )  // with two parameters -- default year
    { cout << "Error in construction of 'Date' instance on Date(7, 11) by 'Date::Date(unsigned int=1, unsigned int=1, unsigned int=1970)'" << endl ; allPassed = false ;  }
    if ( d4.date_ != 21 || d4.month_ != 10 || d4.year_ != 2021 )  // with three parameters
    { cout << "Error in construction of 'Date' instance on Date(21, 10, 2021) by 'Date::Date(unsigned int=1, unsigned int=1, unsigned int=1970)'" << endl ; allPassed = false ;  }

    //  TEST 2 : Check copy constructor
    Date d5 = d4 ;
    if ( d4.date_ != d5.date_ || d4.month_ != d5.month_ || d4.year_ != d5.year_ )   // compare the data members of the two objects
    { cout << "Error in construction of 'Date' instance by the copy constructor 'Date::Date(const Date &)'" << endl ; allPassed = false ;  }

    //  TEST 3 : Check overloaded copy assignment operator '='
    bool compareBeforeCopying = ! ( d4.date_ != d1.date_ || d4.month_ != d1.month_ || d4.year_ != d1.year_ ) ;
    d1 = d4 ;
    bool compareAfterCopying = ! ( d4.date_ != d1.date_ || d4.month_ != d1.month_ || d4.year_ != d1.year_ ) ;
    // to confirm the test, it is important to pick the situation where the 'Date' objects
    // initially had at least one unequal data member. Merely comparing the data members of two 
    // 'Date' objects after copying one to the other might give a "false pass" if they were 
    // already "equal", i.e, i they already had all the data members equal
    if ( ! ( ! compareBeforeCopying && compareAfterCopying ) )
    { cout << "Error in correctly assigning all the data members in the destination instance from the source instance by the copy assignment operator 'const Date& Date::operator=(const Date&)'" << endl ; allPassed = false ;  }

    //  TEST 4 : Check overloaded relational operators -- '==' and '!='
    Date d6(12, 9, 1999) , d7(4, 7, 2000), d8(4, 7, 2000) ;
    if ( d6 == d7 )     // compare "unequal" dates with '==' operator
    { cout << "Relational operator 'bool Date::operator==(const Date &) const' does not return the correct result of equality check" << endl ; allPassed = false ;  }
    if ( ! ( d6 != d7 ) )     // compare "unequal" dates with '!=' operator
    { cout << "Relational operator 'bool Date::operator!=(const Date &) const' does not return the correct result of inequality check" << endl ; allPassed = false ;  }
    if ( ! ( d7 == d8 ) )     // compare "equal" dates with '==' operator
    { cout << "Relational operator 'bool Date::operator==(const Date &) const' does not return the correct result of equality check" << endl ; allPassed = false ;  }
    if ( d7 != d8 )     // compare "equal" dates with '!=' operator
    { cout << "Relational operator 'bool Date::operator!=(const Date &) const' does not return the correct result of inequality check" << endl ; allPassed = false ;  }

    //  TEST 5 : Check static constants
    if ( Date::sMonthNames.size() != 12 || Date::sMonthNames.at(0) != "January" || Date::sMonthNames.at(1) != "February" ||
         Date::sMonthNames.at(2) != "March" || Date::sMonthNames.at(3) != "April" || Date::sMonthNames.at(4) != "May" ||
         Date::sMonthNames.at(5) != "June" || Date::sMonthNames.at(6) != "July" || Date::sMonthNames.at(7) != "August" ||
         Date::sMonthNames.at(8) != "September" || Date::sMonthNames.at(9) != "October"  || Date::sMonthNames.at(10) != "November" ||
         Date::sMonthNames.at(11) != "December" ) // check both size and element at each and every index from 0 to 11
    { cout << "'const vector<string> Date::sMonthNames' not correctly initialized" << endl ; allPassed = false ;  }
    if ( Date::sDayNames.size() != 7 || Date::sDayNames.at(0) != "Monday" || Date::sDayNames.at(1) != "Tuesday" ||
         Date::sDayNames.at(2) != "Wednesday" || Date::sDayNames.at(3) != "Thursday" || Date::sDayNames.at(4) != "Friday" ||
         Date::sDayNames.at(5) != "Saturday" || Date::sDayNames.at(6) != "Sunday" )
        // check both size and element at each and every index from 0 to 6
    { cout << "'const vector<string> Date::sDayNames' not correctly initialized" << endl ; allPassed = false ;  }

    //  TEST 6 : Check overloaded output streaming operator
    cout << d1 ;    // stream a single instance
    cout << endl ;
    cout << d2 << " " << d3 << " " << d4 << " " << d5 << " " << d6 << " " << d7 << " " << d8 << endl ; // stream a chain of instances

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed

}