
//  SOFTWARE ENGINEERING -- ASSIGNMENT O3
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include "Railways.h"
using namespace std ;

Station::Station ( const string & name )
    :   name_(name)     // initializer-list
{   }

Station::Station ( const Station & station )
    :   name_(station.name_)    // initializer-list
{   }

Station & Station::operator = ( const Station & station )
{
    name_ = station.name_ ;
    return *this ;      // return the instance to which the parameter 
                        // is copied to enable chained assignment operations
}

bool Station::operator == ( const Station & s ) const
{   return s.name_ == name_ ;   }   // two 'Station' objects are said to be "equal" if and only if they
                                    // have the same name. Note that two objects can have different locations
                                    // in the memory and thus can be distinct instances of 'Station' class but
                                    // still they can be "equal" in a somewhat loose sense if they have same names

bool Station::operator != ( const Station & s ) const
{   return s.name_ != name_ ;   }   // two 'Station' objects are said to be "unequal" if and only if they
                                    // have different names

ostream & operator << ( ostream & out , const Station & station )
{
    out << "[ " << station.name_ << " ]" ;      // sqaure brackets help in identifying the 'Station' data type
                                                // when printed on terminal. Otherwise it might be confused with
                                                // string literals or character arrays
    return out ;    // returning the 'ostream' object is important for streaming 
                    // of multiple instances chained in the same instruction
}

string Station::GetName ( ) const
{   return name_ ;  }       // return the value 'Station::name_' data member

int Station::GetDistance ( const Station & station  ) const
{   return Railways::SpecialRailways().GetDistance(*this, station) ;  }
// use the routine of 'int Railways::GetDistance(const Station &, const Station &) const' method
// to obtain the distance between the two stations
// The definition of 'Railways::GetDistance' is given in "Railways.cpp" file.

Station::~Station ( ) {   }     // no explicit memory management needed -- no dynamically 
                                // allocated memory for any data member -- hence empty body

void Station::UnitTestStationScenarioO1 ( )     // using the default "Indian Railways" as the singleton 'Railways' instance
{
    cout << "\n\n   [ Station::UnitTestStationScenarioO1 ( ) ]" << endl ;
    bool allPassed = true ;

    //  TEST 1 : Check constructor
    Station s1("Arbitrary Station Name") ;
    if ( s1.name_ != string("Arbitrary Station Name") ) // check if the data member is correctly initialized
    { cout << "Attribute 'Station::name_' not initialized correctly by 'Station::Station(const string &)' constructor" << endl ; allPassed = false ;  }

    //  TEST 2 : Check copy constructor
    Station s2 = s1 ;
    if ( s2.name_ != s1.name_ ) // check if the data members are equal
    { cout << "Attribute 'Station::name_' not initialized correctly by 'Station::Station(const Station &)' constructor" << endl ; allPassed = false ;  }

    //  TEST 3 : Check overloaded copy assignment operator '='
    Station s3("Special Station Name") ;
    bool compareBeforeCopying = ( s2.name_ == s3.name_ ) ;
    s2 = s3 ;
    bool compareAfterCopying = ( s2.name_ == s3.name_ ) ;
    // to confirm the test, it is important to pick the situation where the 'Station' objects
    // initially did not have the same name. Merely comparing the names of two 'Station' objects 
    // after copying one to the other might give a "false pass" if they were already "equal"
    if ( ! ( ! compareBeforeCopying && compareAfterCopying ) )
    { cout << "Copy assignment operator 'Station & Station::operator=(const Station &)' does not correctly copy the attribute 'Station::name_'" << endl ; allPassed = false ;  }

    //  TEST 4 : Check overloaded relational operators -- '==' and '!='
    Station s4("Station O1") , s5("Station O2") ;   // TEST 4.1 : Consider two stations with different names
    if ( s4 == s5 )
    { cout << "Relational operator 'bool Station::operator==(const Station &) const' does not return the correct result of equality check" << endl ; allPassed = false ;  }
    if ( ! (s4 != s5) )
    { cout << "Relational operator 'bool Station::operator!=(const Station &) const' does not return the correct result of inequality check" << endl ; allPassed = false ;  }
    Station s6("Station O3") , s7("Station O3") ;   // TEST 4.2 : Consider two stations with same names
    if ( ! (s6 == s7) )
    { cout << "Relational operator 'bool Station::operator==(const Station &) const' does not return the correct result of equality check" << endl ; allPassed = false ;  }
    if ( s6 != s7 )
    { cout << "Relational operator 'bool Station::operator!=(const Station &) const' does not return the correct result of inequality check" << endl ; allPassed = false ;  }

    //  TEST 5 : Check accuracy of value returned by 'Station::GetName' method
    if ( s1.GetName() != string("Arbitrary Station Name") )
    { cout << "Member function 'string Station::GetName( )const' does not return the correct value of the data member 'Station::name_'" << endl ; allPassed = false ;  }

    //  TEST 6 : Check accuracy of 'Station::GetDistance' method
    Station st1("Mumbai"), st2("Delhi"), st3("Bangalore"), st4("Kolkata"), st5("Chennai") ;

    // check "mathematical-symmetry" of the method. If distance is a two-variable function
    // with "departure-station" and "destination-station" as the two inputs, then it must
    // be a symmetric function
    if ( st1.GetDistance(st2) != st2.GetDistance(st1) ||
         st1.GetDistance(st3) != st3.GetDistance(st1) ||
         st1.GetDistance(st4) != st4.GetDistance(st1) ||
         st1.GetDistance(st5) != st5.GetDistance(st1) ||
         st2.GetDistance(st3) != st3.GetDistance(st2) ||
         st2.GetDistance(st4) != st4.GetDistance(st2) ||
         st2.GetDistance(st5) != st5.GetDistance(st2) ||
         st3.GetDistance(st4) != st4.GetDistance(st3) ||
         st3.GetDistance(st5) != st5.GetDistance(st3) ||
         st4.GetDistance(st5) != st5.GetDistance(st4)  )
    { cout << "Member function 'int Station::GetDistance(const Station &)const' is not a \"mathematically symmetric\" function" << endl ; allPassed = false ;  }

    // match the values returned for different "unordered" pairs of stations with the expected/golden outputs
    if ( st1.GetDistance(st2) != 1447 || st1.GetDistance(st3) != 981 || st1.GetDistance(st4) != 2014 ||
         st1.GetDistance(st5) != 1338 || st2.GetDistance(st3) != 2150 || st2.GetDistance(st4) != 1472 ||
         st2.GetDistance(st5) != 2180 || st3.GetDistance(st4) != 1871 || st3.GetDistance(st5) != 350 ||
         st4.GetDistance(st5) != 1659 )
    { cout << "Member function 'int Station::GetDistance(const Station &)const' does not return the correct distance between all pairs of stations" << endl ; allPassed = false ;  }

    //  TEST 7 : Check overloaded output streaming operator
    cout << s1 ;    // stream a single instance
    cout << s2 << s3 << s4 << st1 << st2 << st3 << st4 << st5 << endl ; // stream a chain of instances

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed

}

void Station::UnitTestStationScenarioO2 ( )     // using the custom "European Railways" as the singleton 'Railways' instance
{
    cout << "\n\n   [ Station::UnitTestStationScenarioO2 ( ) ]" << endl ;
    bool allPassed = true ;

    const vector<Station> testStations = { Station("Paris"), Station("Rome"), Station("Venice") } ;
    const map<pair<string, string>, int> testPairwiseDistances = {
                                                                            { {"Paris", "Rome"}, 1531 } ,
                                                                            { {"Paris", "Venice"}, 1145 } ,
                                                                            { {"Rome", "Venice"}, 566 }   } ;
    
    // Since this is the first call to the method 'Railways::SpecialRailways', the
    // singleton 'Railways' object that will be constructed will be based on these
    // parameters. Note that this test is independent of the previous test. Conduct
    // only one unit test in one execution.
    Railways::SpecialRailways(testStations, testPairwiseDistances) ;

    // Check accuracy of 'Station::GetDistance' method

    Station st1("Paris"), st2("Rome"), st3("Venice") ;
    
    // check "mathematical-symmetry" of the method. If distance is a two-variable function
    // with "departure-station" and "destination-station" as the two inputs, then it must
    // be a symmetric function
    if ( st1.GetDistance(st2) != st2.GetDistance(st1) ||
         st1.GetDistance(st3) != st3.GetDistance(st1) ||
         st2.GetDistance(st3) != st3.GetDistance(st2)  )
    { cout << "Member function 'int Station::GetDistance(const Station &)const' is not a \"mathematically symmetric\" function" << endl ; allPassed = false ;  }

    // match the values returned for different unordered pairs of stations with the expected/golden outputs
    if ( st1.GetDistance(st2) != 1531 || st1.GetDistance(st3) != 1145 || st2.GetDistance(st3) != 566 )
    { cout << "Member function 'int Station::GetDistance(const Station &)const' does not return the correct distance between all pairs of stations" << endl ; allPassed = false ;  }
    
    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed
}
