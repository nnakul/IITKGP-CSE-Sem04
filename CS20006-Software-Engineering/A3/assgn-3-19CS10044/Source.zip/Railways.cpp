
//  SOFTWARE ENGINEERING -- ASSIGNMENT O3
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include "Railways.h"
using namespace std ;

// initialize the static data members with empty values
vector<Station> Railways::sStations = { } ;
map<pair<string, string>, int> Railways::sDistStations = { } ;

Railways::Railways ( const vector<Station> & stations , const map<pair<string, string>, int> & distStations )
    :   stations_(stations) , distStations_(distStations)   // intializer-list
{   sStations = stations ;  sDistStations = distStations ;  }    // overwrite the static data members with
                                                                 // attributes of the singleton instance

const Railways & Railways::SpecialRailways ( const vector<Station> & stations , const map<pair<string, string>, int> & distStations )
{
    static Railways sSpecialRailways(stations, distStations) ;   // "Meyer's Implementation of a Singleton Class"
    // static locals are declared only once; its lifetime starts when the 
    // function is called and ends only when the program ends. Therefore,
    // the constructor is called only once and that happens when this function
    // is called for the first time

    return sSpecialRailways ; // always return the singleton instance as a 'const' reference of 'Railways'
}

ostream & operator << ( ostream & out , const Railways & railways )   // overloaded output streaming operator
{
    out << endl << "   +++ STATIONS +++ " ;
    for ( auto & it : railways.stations_ )   // iterate over the vector of 'Station' and print all of them
                                             //  uses 'ostream& operator<<(ostream &, const Station&)'
                                             // defined in "Station.cpp"
        out << endl << " - " << it ;
    out << endl << "--------------------------------------------------------" 
        << endl << "   +++ DISTANCES BETWEEN STATIONS +++ " ;
    for ( auto & it : railways.distStations_ )
        out << endl << " - between " << (it.first).first << " and " << (it.first).second << " : " << it.second ;
          // iterate over the map storing pairwise distances of 
          // unordered pair of stations and print all of them.
    out << endl ;
    return out ;    // returning the 'ostream' object is important for streaming 
                    // of multiple references to the 'singleton' object chained 
                    // in the same instruction
}

int Railways::GetDistance ( const Station & s1 , const Station & s2 ) const
{
    pair<string, string> link ;    // the data type of the key in the map 'Railways::distStations_'
    string name1 = s1.GetName() ; string name2 = s2.GetName() ;  // get the names of the 'Station' using 'Station::GetName' method
    link.first = name1 ; link.second = name2 ;    // initialize the link
    if ( distStations_.find(link) != distStations_.end() )  
        return distStations_.at(link) ; // if the key is found, return the value corresponding to that key
    link.first = name2 ; link.second = name1 ;    // otherwise try the reverse order
    if ( distStations_.find(link) != distStations_.end() )
        return distStations_.at(link) ; // if the "reversed" key is found, return the value corresponding to it
    return -1 ;     // return if no such unordered pair of stations was found in the map 'Railways::distStations_'
}

Railways::~Railways ( ) {   }     // no explicit memory management needed -- no dynamically 
                                  // allocated memory for any data member -- hence empty body

// BROAD SCENARIO O1 -- When the singleton 'Railways' instance was constructed as default "Indian Railways"
void Railways::UnitTestRailwaysScenarioO1 ( )
{
    cout << "\n\n   [ Railways::UnitTestRailwaysScenarioO1 ( ) ]" << endl ;
    bool allPassed = true ;

    // TEST 1 : Construction of singleton instance with default parameters
    // first call to 'Railways::SpecialRailways'
    // since no parameters are passed, the default "Indian Railways" should be constructed -- check that
    const Railways & r1 = Railways::SpecialRailways() ;

     // check the size of 'r1.stations_' and also check element at each and every index of 'r1.stations_' from 0 to 4
    if ( ! ( r1.stations_.at(0) == Station("Mumbai") && r1.stations_.at(1) == Station("Delhi") && r1.stations_.at(2) == Station("Bangalore")
             && r1.stations_.at(3) == Station("Kolkata") && r1.stations_.at(4) == Station("Chennai") && r1.stations_.size() == 5 ) )
    { cout << "Default value of 'const vector<Station> &' was not correctly assigned to the data member 'Railways::stations_' in 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ; }

     // check if all the keys in the second default parameter of 'Railways::SpecialRailways' are present in 'r1.distStations_'
    if ( r1.distStations_.find(pair<string, string>{"Delhi", "Mumbai"}) == r1.distStations_.end() ||
         r1.distStations_.find(pair<string, string>{"Bangalore", "Mumbai"}) == r1.distStations_.end() ||
         r1.distStations_.find(pair<string, string>{"Kolkata", "Mumbai"}) == r1.distStations_.end() ||
         r1.distStations_.find(pair<string, string>{"Chennai", "Mumbai"}) == r1.distStations_.end() || 
         r1.distStations_.find(pair<string, string>{"Bangalore", "Delhi"}) == r1.distStations_.end() ||
         r1.distStations_.find(pair<string, string>{"Delhi", "Kolkata"}) == r1.distStations_.end() ||
         r1.distStations_.find(pair<string, string>{"Chennai", "Delhi"}) == r1.distStations_.end() || 
         r1.distStations_.find(pair<string, string>{"Bangalore", "Kolkata"}) == r1.distStations_.end() ||
         r1.distStations_.find(pair<string, string>{"Bangalore", "Chennai"}) == r1.distStations_.end() ||
         r1.distStations_.find(pair<string, string>{"Chennai", "Kolkata"}) == r1.distStations_.end() || r1.distStations_.size() != 10 )
    { cout << "Default value of 'const map<pair<string, string>, int> &' was not correctly assigned to the data member 'Railways::distStations_' in 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ; }
    
    // check the size of 'r1.distStations_' and also check the value corresponding to each and every key in the map
    if ( r1.distStations_.size() != 10 || r1.distStations_.at({"Delhi", "Mumbai"}) != 1447 || r1.distStations_.at({"Bangalore", "Mumbai"}) != 981
         || r1.distStations_.at({"Kolkata", "Mumbai"}) != 2014 || r1.distStations_.at({"Chennai", "Mumbai"}) != 1338 || r1.distStations_.at({"Bangalore", "Delhi"}) != 2150 
         || r1.distStations_.at({"Delhi", "Kolkata"}) != 1472 || r1.distStations_.at({"Chennai", "Delhi"}) != 2180 || r1.distStations_.at({"Bangalore", "Kolkata"}) != 1871
         || r1.distStations_.at({"Bangalore", "Chennai"}) != 350 || r1.distStations_.at({"Chennai", "Kolkata"}) != 1659 )
    { cout << "Default value of 'const map<pair<string, string>, int> &' was not correctly assigned to the data member 'Railways::distStations_' in 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ; }
    

    // TEST 2 : Check the static data members
    // check the size of 'Railways::sStations' and also check element at each and every index of 'Railways::sStations' from 0 to 4
    if ( Railways::sStations.size() != 5 || Railways::sStations.at(0) != Station("Mumbai") || Railways::sStations.at(1) != Station("Delhi") ||
         Railways::sStations.at(2) != Station("Bangalore") || Railways::sStations.at(3) != Station("Kolkata") || Railways::sStations.at(4) != Station("Chennai"))
    { cout << "'vector<Station> Railways::sStations' was not correctly assigned in 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }
    
    // check the size of 'Railways::sDistStations' and also check the value corresponding to each and every key in the map
    if ( Railways::sDistStations.size() != 10 || Railways::sDistStations.at({"Delhi", "Mumbai"}) != 1447 || Railways::sDistStations.at({"Bangalore", "Mumbai"}) != 981
         || Railways::sDistStations.at({"Kolkata", "Mumbai"}) != 2014 || Railways::sDistStations.at({"Chennai", "Mumbai"}) != 1338 || Railways::sDistStations.at({"Bangalore", "Delhi"}) != 2150 
         || Railways::sDistStations.at({"Delhi", "Kolkata"}) != 1472 || Railways::sDistStations.at({"Chennai", "Delhi"}) != 2180 || Railways::sDistStations.at({"Bangalore", "Kolkata"}) != 1871
         || Railways::sDistStations.at({"Bangalore", "Chennai"}) != 350 || Railways::sDistStations.at({"Chennai", "Kolkata"}) != 1659 )
    { cout << "'map<pair<string, string>, int> Railways::sDistStations' was not correctly assigned in 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }


    // TEST 3 : Call 'Railways::SpecialRailways' once more without any arguements
    const Railways & r2 = Railways::SpecialRailways() ;
    if ( & r1 != & r2 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the default parameters should not have been constructed
    { cout << "'Railways' is not a singleton class because it instantiates a new 'Railways' object on repeating default construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ; }
    
    // check and ensure that the static data members have stayed intact after the second call to 'Railways::SpecialRailways'
    // repeat the tests in "TEST 2"
    if ( Railways::sStations.size() != 5 || Railways::sStations.at(0) != Station("Mumbai") || Railways::sStations.at(1) != Station("Delhi") ||
         Railways::sStations.at(2) != Station("Bangalore") || Railways::sStations.at(3) != Station("Kolkata") || Railways::sStations.at(4) != Station("Chennai"))
    { cout << "'vector<Station> Railways::sStations' was changed on repeating default construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }

    if ( Railways::sDistStations.size() != 10 || Railways::sDistStations.at({"Delhi", "Mumbai"}) != 1447 || Railways::sDistStations.at({"Bangalore", "Mumbai"}) != 981
         || Railways::sDistStations.at({"Kolkata", "Mumbai"}) != 2014 || Railways::sDistStations.at({"Chennai", "Mumbai"}) != 1338 || Railways::sDistStations.at({"Bangalore", "Delhi"}) != 2150 
         || Railways::sDistStations.at({"Delhi", "Kolkata"}) != 1472 || Railways::sDistStations.at({"Chennai", "Delhi"}) != 2180 || Railways::sDistStations.at({"Bangalore", "Kolkata"}) != 1871
         || Railways::sDistStations.at({"Bangalore", "Chennai"}) != 350 || Railways::sDistStations.at({"Chennai", "Kolkata"}) != 1659 )
    { cout << "'map<pair<string, string>, int> Railways::sDistStations' was changed on repeating default construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }
    
    // TEST 4 : Call 'Railways::SpecialRailways' once more with arguements different than the default parameters
    // Let us consider "European Railways"
    const vector<Station> testStations = { Station("Amsterdam"), Station("Berlin"), Station("Brussels"), Station("Athens") } ;
    const map<pair<string, string>, int> testPairwiseDistances = {
                                                                        { {"Amsterdam", "Berlin"}, 649 } ,
                                                                        { {"Amsterdam", "Brussels"}, 209 } ,
                                                                        { {"Amsterdam", "Athens"}, 3082 } ,
                                                                        { {"Athens", "Berlin"}, 2552 } ,
                                                                        { {"Athens", "Brussels"}, 3021 } ,
                                                                        { {"Berlin", "Brussels"}, 782 }     } ;
    
    // calling 'Railways::SpecialRailways' with parameters. Since this is NOT the first
    // call to the method, the object for the custom "European Railways" should not be constructed
    // and the same singleton object that is already instantiated should be returned
    const Railways & r4 = Railways::SpecialRailways(testStations, testPairwiseDistances) ;
    
    // compare the addresses of the instance returned in this TEST and the instance returned 
    // by the first call to 'Railways::SpecialRailways' in the first case
    if ( & r1 != & r4 )  // equality of addresses will confirm that the two are the same instances of 'Railways' class
    { cout << "'Railways' is not a singleton class because it instantiates a new 'Railways' object on parametric construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ; }

    // reconduct tests in "TEST 1" for 'r4' to ensure that the returned instance has the same properties as the
    // instance returned by the first call to 'Railways::SpecialRailways'
    // check the size of 'r4.stations_' and also check element at each and every index of 'r4.stations_' from 0 to 4
    if ( ! ( r4.stations_.at(0) == Station("Mumbai") && r4.stations_.at(1) == Station("Delhi") && r4.stations_.at(2) == Station("Bangalore")
             && r4.stations_.at(3) == Station("Kolkata") && r4.stations_.at(4) == Station("Chennai") && r4.stations_.size() == 5 ) )
    { cout << "Parametric construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)' returns a 'Railways' instance with different value of 'Railways::stations_' attribute" << endl ; allPassed = false ; }

     // check if all the keys in the second default parameter of 'Railways::SpecialRailways' are present in 'r4.distStations_'
    if ( r4.distStations_.find(pair<string, string>{"Delhi", "Mumbai"}) == r4.distStations_.end() ||
         r4.distStations_.find(pair<string, string>{"Bangalore", "Mumbai"}) == r4.distStations_.end() ||
         r4.distStations_.find(pair<string, string>{"Kolkata", "Mumbai"}) == r4.distStations_.end() ||
         r4.distStations_.find(pair<string, string>{"Chennai", "Mumbai"}) == r4.distStations_.end() || 
         r4.distStations_.find(pair<string, string>{"Bangalore", "Delhi"}) == r4.distStations_.end() ||
         r4.distStations_.find(pair<string, string>{"Delhi", "Kolkata"}) == r4.distStations_.end() ||
         r4.distStations_.find(pair<string, string>{"Chennai", "Delhi"}) == r4.distStations_.end() || 
         r4.distStations_.find(pair<string, string>{"Bangalore", "Kolkata"}) == r4.distStations_.end() ||
         r4.distStations_.find(pair<string, string>{"Bangalore", "Chennai"}) == r4.distStations_.end() ||
         r4.distStations_.find(pair<string, string>{"Chennai", "Kolkata"}) == r4.distStations_.end() || r4.distStations_.size() != 10 )
    { cout << "Parametric construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)' returns a 'Railways' instance with different value of 'Railways::distStations_' attribute" << endl ; allPassed = false ; }
    
    // check the size of 'r4.distStations_' and also check the value corresponding to each and every key in the map
    if ( r4.distStations_.size() != 10 || r4.distStations_.at({"Delhi", "Mumbai"}) != 1447 || r4.distStations_.at({"Bangalore", "Mumbai"}) != 981
         || r4.distStations_.at({"Kolkata", "Mumbai"}) != 2014 || r4.distStations_.at({"Chennai", "Mumbai"}) != 1338 || r4.distStations_.at({"Bangalore", "Delhi"}) != 2150 
         || r4.distStations_.at({"Delhi", "Kolkata"}) != 1472 || r4.distStations_.at({"Chennai", "Delhi"}) != 2180 || r4.distStations_.at({"Bangalore", "Kolkata"}) != 1871
         || r4.distStations_.at({"Bangalore", "Chennai"}) != 350 || r4.distStations_.at({"Chennai", "Kolkata"}) != 1659 )
    { cout << "Parametric construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)' returns a 'Railways' instance with different value of 'Railways::distStations_' attribute" << endl ; allPassed = false ; }

    // check and ensure that the static data members have stayed intact after the third call to 'Railways::SpecialRailways' with parameters
    // repeat the tests in "TEST 2"
    if ( Railways::sStations.size() != 5 || Railways::sStations.at(0) != Station("Mumbai") || Railways::sStations.at(1) != Station("Delhi") ||
         Railways::sStations.at(2) != Station("Bangalore") || Railways::sStations.at(3) != Station("Kolkata") || Railways::sStations.at(4) != Station("Chennai"))
    { cout << "'vector<Station> Railways::sStations' was changed on attempting parametric construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }

    if ( Railways::sDistStations.size() != 10 || Railways::sDistStations.at({"Delhi", "Mumbai"}) != 1447 || Railways::sDistStations.at({"Bangalore", "Mumbai"}) != 981
         || Railways::sDistStations.at({"Kolkata", "Mumbai"}) != 2014 || Railways::sDistStations.at({"Chennai", "Mumbai"}) != 1338 || Railways::sDistStations.at({"Bangalore", "Delhi"}) != 2150 
         || Railways::sDistStations.at({"Delhi", "Kolkata"}) != 1472 || Railways::sDistStations.at({"Chennai", "Delhi"}) != 2180 || Railways::sDistStations.at({"Bangalore", "Kolkata"}) != 1871
         || Railways::sDistStations.at({"Bangalore", "Chennai"}) != 350 || Railways::sDistStations.at({"Chennai", "Kolkata"}) != 1659 )
    { cout << "'map<pair<string, string>, int> Railways::sDistStations' was changed on attempting parametric construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }

     // "TEST 3" and "TEST 4" confirm that after the first call to 'Railways::SpecialRailways', the
     // subsequent calls have absolutely NO impact on (1.) the number of instances of 'Railways'
     // class, (2.) the state of the singleton instance, (3.) the values of the static data members.
     // Hence, 'Railways' is a singleton class (at least when the first call is made without any arguements)

     // TEST 5 : Test member function 'Railways::GetDistance'
    Station s1("Mumbai"), s2("Delhi"), s3("Bangalore"), s4("Kolkata"), s5("Chennai") ;

    // check "mathematical-symmetry" of the method. If distance is a two-variable function
    // with "departure-station" and "destination-station" as the two inputs, then it must
    // be a symmetric function
    if ( r1.GetDistance(s1, s2) != r1.GetDistance(s2, s1) ||
         r1.GetDistance(s1, s3) != r1.GetDistance(s3, s1) ||
         r1.GetDistance(s1, s4) != r1.GetDistance(s4, s1) ||
         r1.GetDistance(s1, s5) != r1.GetDistance(s5, s1) ||
         r1.GetDistance(s2, s3) != r1.GetDistance(s3, s2) ||
         r1.GetDistance(s2, s4) != r1.GetDistance(s4, s2) ||
         r1.GetDistance(s2, s5) != r1.GetDistance(s5, s2) ||
         r1.GetDistance(s3, s4) != r1.GetDistance(s4, s3) ||
         r1.GetDistance(s3, s5) != r1.GetDistance(s5, s3) ||
         r1.GetDistance(s4, s5) != r1.GetDistance(s5, s4)  )
    { cout << "'Railways::GetDistance(const Station &, const Station &) const' is not a 'mathematically-symmetric' function" << endl ; allPassed = false ; }

     // match the values returned for different "unordered" pairs of stations with the expected/golden outputs
    if ( r1.GetDistance(s1, s2) != 1447 || r1.GetDistance(s1, s3) != 981 || r1.GetDistance(s1, s4) != 2014 ||
         r1.GetDistance(s1, s5) != 1338 || r1.GetDistance(s2, s3) != 2150 || r1.GetDistance(s2, s4) != 1472 ||
         r1.GetDistance(s2, s5) != 2180 || r1.GetDistance(s3, s4) != 1871 || r1.GetDistance(s3, s5) != 350 ||
         r1.GetDistance(s4, s5) != 1659 )
    { cout << "'Railways::GetDistance(const Station &, const Station &) const' does not return the correct distance between all pairs of stations" << endl ; allPassed = false ; }

     // TEST 6 : Check the overloaded output streaming operator
    cout << r1 ;    // stream a single reference to the singleton object
    cout << r2 << r4 ; // stream a chain of references to the singleton object

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed

}

// BROAD SCENARIO O2 -- When the singleton 'Railways' instance was constructed as some custom railways
void Railways::UnitTestRailwaysScenarioO2 ( )
{
    cout << "\n\n   [ Railways::UnitTestRailwaysScenarioO2 ( ) ]" << endl ;
    bool allPassed = true ;

     // TEST 1 : Construction of singleton instance with the passed parameters
    const vector<Station> testStations = { Station("Amsterdam"), Station("Berlin"), Station("Brussels"), Station("Athens") } ;
    const map<pair<string, string>, int> testPairwiseDistances = {
                                                                        { {"Amsterdam", "Berlin"}, 649 } ,
                                                                        { {"Amsterdam", "Brussels"}, 209 } ,
                                                                        { {"Amsterdam", "Athens"}, 3082 } ,
                                                                        { {"Athens", "Berlin"}, 2552 } ,
                                                                        { {"Athens", "Brussels"}, 3021 } ,
                                                                        { {"Berlin", "Brussels"}, 782 }     } ;
    // first call to 'Railways::SpecialRailways'
    // since parameters are passed, the singleton 'Railways' instance will have these "custom" attributes
    const Railways & r1 = Railways::SpecialRailways(testStations, testPairwiseDistances) ;
    
    // check the size of 'r1.stations_' and also its element at each and every index from 0 to 3
    if ( ! ( r1.stations_.at(0) == Station("Amsterdam") && r1.stations_.at(1) == Station("Berlin") && r1.stations_.at(2) == Station("Brussels")
             && r1.stations_.at(3) == Station("Athens") && r1.stations_.size() == 4 ) )
    { cout << "Passed value of 'const vector<Station> &' was not correctly assigned to the data member 'Railways::stations_' in 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ; }
     
     // check if every key in the map 'testPairwiseDistances' is also present in 'r1.distStations_'
    if ( r1.distStations_.find(pair<string, string>{"Amsterdam", "Berlin"}) == r1.distStations_.end() ||
         r1.distStations_.find(pair<string, string>{"Amsterdam", "Brussels"}) == r1.distStations_.end() ||
         r1.distStations_.find(pair<string, string>{"Amsterdam", "Athens"}) == r1.distStations_.end() ||
         r1.distStations_.find(pair<string, string>{"Athens", "Berlin"}) == r1.distStations_.end() || 
         r1.distStations_.find(pair<string, string>{"Athens", "Brussels"}) == r1.distStations_.end() ||
         r1.distStations_.find(pair<string, string>{"Berlin", "Brussels"}) == r1.distStations_.end() ||
         r1.distStations_.size() != 6 )
    { cout << "Passed value of 'const map<pair<string, string>, int> &' was not correctly assigned to the data member 'Railways::distStations_' in 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ; }
    
    // check the size of 'r1.distStations_' and match the values in 'r1.distStations_' corresponding 
    // to each and every key of 'testPairwiseDistances'
    if ( r1.distStations_.size() != 6 || r1.distStations_.at({"Amsterdam", "Berlin"}) != 649 || r1.distStations_.at({"Amsterdam", "Brussels"}) != 209
         || r1.distStations_.at({"Amsterdam", "Athens"}) != 3082 || r1.distStations_.at({"Athens", "Berlin"}) != 2552 || r1.distStations_.at({"Athens", "Brussels"}) != 3021 
         || r1.distStations_.at({"Berlin", "Brussels"}) != 782 )
    { cout << "Passed value of 'const map<pair<string, string>, int> &' was not correctly assigned to the data member 'Railways::distStations_' in 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ; }
    
     // TEST 2 : Check static data members
     // check if 'Railways::sStations' is assigned appropriate value
     // check the size of 'Railways::sStations' and also its element at each and every index from 0 to 3
    if ( Railways::sStations.size() != 4 || Railways::sStations.at(0) != Station("Amsterdam") || Railways::sStations.at(1) != Station("Berlin") ||
         Railways::sStations.at(2) != Station("Brussels") || Railways::sStations.at(3) != Station("Athens") )
    { cout << "'vector<Station> Railways::sStations' was not correctly assigned in 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }

    // check the size of 'Railways::sDistStations' and match the values in 'Railways::sDistStations' corresponding 
    // to each and every key of 'testPairwiseDistances'
    if ( Railways::sDistStations.size() != 6 || Railways::sDistStations.at({"Amsterdam", "Berlin"}) != 649 || Railways::sDistStations.at({"Amsterdam", "Brussels"}) != 209
         || Railways::sDistStations.at({"Amsterdam", "Athens"}) != 3082 || Railways::sDistStations.at({"Athens", "Berlin"}) != 2552 || Railways::sDistStations.at({"Athens", "Brussels"}) != 3021 
         || Railways::sDistStations.at({"Berlin", "Brussels"}) != 782 )
    { cout << "'map<pair<string, string>, int> Railways::sDistStations' was not correctly assigned in 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }

     // TEST 3 : Call 'Railways::SpecialRailways' once more with the same parameters
    const Railways & r2 = Railways::SpecialRailways(testStations, testPairwiseDistances) ;
    if ( & r1 != & r2 )  // for a singleton class, the returned instance must be same as the instance returned 
                         // in the first TEST (on first call to 'Railways::SpecialRailways')
                         // Equality of addresses will confirm that the two are the same instances of 'Railways' class
                         // and not a new instance with the same data members is constructed
    { cout << "'Railways' is not a singleton class because it instantiates a new 'Railways' object on repeating construction with same parameters through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ; }
    
    // check if the static data members have stayed intact
    // repeat tests in "TEST 2"
    if ( Railways::sStations.size() != 4 || Railways::sStations.at(0) != Station("Amsterdam") || Railways::sStations.at(1) != Station("Berlin") ||
         Railways::sStations.at(2) != Station("Brussels") || Railways::sStations.at(3) != Station("Athens") )
    { cout << "'vector<Station> Railways::sStations' was changed on repeating parametric construction with same parameters through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }

    if ( Railways::sDistStations.size() != 6 || Railways::sDistStations.at({"Amsterdam", "Berlin"}) != 649 || Railways::sDistStations.at({"Amsterdam", "Brussels"}) != 209
         || Railways::sDistStations.at({"Amsterdam", "Athens"}) != 3082 || Railways::sDistStations.at({"Athens", "Berlin"}) != 2552 || Railways::sDistStations.at({"Athens", "Brussels"}) != 3021 
         || Railways::sDistStations.at({"Berlin", "Brussels"}) != 782 )
    { cout << "'map<pair<string, string>, int> Railways::sDistStations' was changed on repeating parametric construction with same parameters through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }
    
     // TEST 4 : Call 'Railways::SpecialRailways' once more with different parameters
    const vector<Station> repeatTestStations = { Station("Paris"), Station("Rome"), Station("Venice") } ;
    const map<pair<string, string>, int> repeatTestPairwiseDistances = {
                                                                            { {"Paris", "Rome"}, 1531 } ,
                                                                            { {"Paris", "Venice"}, 1145 } ,
                                                                            { {"Rome", "Venice"}, 566 }   } ;
    // call 'Railways::SpecialRailways' with different parameters
    const Railways & r4 = Railways::SpecialRailways(repeatTestStations, repeatTestPairwiseDistances) ;
    
    if ( & r1 != & r4 ) // for a singleton class, the returned instance must be same as the instance returned 
                         // in the first TEST (on first call to 'Railways::SpecialRailways')
                         // Equality of addresses will confirm that the two are the same instances of 'Railways' class
    { cout << "'Railways' is not a singleton class because it instantiates a new 'Railways' object on a different parametric construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ; }

    // repeat tests in "TEST 1" for 'r4' to ensure that the attributes of 'r4' are same as
    // the attributes of the instance returned in the first case. Even if 'r1' and 'r4' are 
    // references to the same 'Railways' object (having same location), this test is important
    // in order to conirm that calling 'Railways::SpecialRailways' with different parameters
    // does not change their "state". In other words, the parameters passed to this function
    // in calls subsequent to the first call have no impact on the 'singleton' object.

    // check the size of 'r4.stations_' and also its element at each and every index from 0 to 3
    if ( ! ( r4.stations_.at(0) == Station("Amsterdam") && r4.stations_.at(1) == Station("Berlin") && r4.stations_.at(2) == Station("Brussels")
             && r4.stations_.at(3) == Station("Athens") && r4.stations_.size() == 4 ) )
    { cout << "Different parametric construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)' returns a 'Railways' instance with different value of 'Railways::stations_' attribute" << endl ; allPassed = false ; }

     // check if every key in the map 'testPairwiseDistances' is also present in 'r4.distStations_'
    if ( r4.distStations_.find(pair<string, string>{"Amsterdam", "Berlin"}) == r4.distStations_.end() ||
         r4.distStations_.find(pair<string, string>{"Amsterdam", "Brussels"}) == r4.distStations_.end() ||
         r4.distStations_.find(pair<string, string>{"Amsterdam", "Athens"}) == r4.distStations_.end() ||
         r4.distStations_.find(pair<string, string>{"Athens", "Berlin"}) == r4.distStations_.end() || 
         r4.distStations_.find(pair<string, string>{"Athens", "Brussels"}) == r4.distStations_.end() ||
         r4.distStations_.find(pair<string, string>{"Berlin", "Brussels"}) == r4.distStations_.end() ||
         r4.distStations_.size() != 6 )
    { cout << "Different parametric construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)' returns a 'Railways' instance with different value of 'Railways::distStations_' attribute" << endl ; allPassed = false ; }

     // check the size of 'r4.distStations_' and match the values in 'r4.distStations_' corresponding 
     // to each and every key of 'testPairwiseDistances'
    if ( r4.distStations_.size() != 6 || r4.distStations_.at({"Amsterdam", "Berlin"}) != 649 || r4.distStations_.at({"Amsterdam", "Brussels"}) != 209
         || r4.distStations_.at({"Amsterdam", "Athens"}) != 3082 || r4.distStations_.at({"Athens", "Berlin"}) != 2552 || r4.distStations_.at({"Athens", "Brussels"}) != 3021 
         || r4.distStations_.at({"Berlin", "Brussels"}) != 782 )
    { cout << "Different parametric construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)' returns a 'Railways' instance with different value of 'Railways::distStations_' attribute" << endl ; allPassed = false ; }

     // repeat tests in "TEST 2" to ensure that the static data members stay intact
    if ( Railways::sStations.size() != 4 || Railways::sStations.at(0) != Station("Amsterdam") || Railways::sStations.at(1) != Station("Berlin") ||
         Railways::sStations.at(2) != Station("Brussels") || Railways::sStations.at(3) != Station("Athens") )
    { cout << "'vector<Station> Railways::sStations' was changed on repeating parametric construction with different parameters through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }

    if ( Railways::sDistStations.size() != 6 || Railways::sDistStations.at({"Amsterdam", "Berlin"}) != 649 || Railways::sDistStations.at({"Amsterdam", "Brussels"}) != 209
         || Railways::sDistStations.at({"Amsterdam", "Athens"}) != 3082 || Railways::sDistStations.at({"Athens", "Berlin"}) != 2552 || Railways::sDistStations.at({"Athens", "Brussels"}) != 3021 
         || Railways::sDistStations.at({"Berlin", "Brussels"}) != 782 )
    { cout << "'map<pair<string, string>, int> Railways::sDistStations' was changed on repeating parametric construction with different parameters through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }
    
     // TEST 5 : Call 'Railways::SpecialRailways' once more with no parameters
    const Railways & r5 = Railways::SpecialRailways() ;

    if ( & r1 != & r5 )  // for a singleton class, the returned instance must be same as the instance returned 
                         // in the first TEST (on first call to 'Railways::SpecialRailways')
                         // Equality of addresses will confirm that the two are the same instances of 'Railways' class
    { cout << "'Railways' is not a singleton class because it instantiates a new 'Railways' object on deafult construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ; }

    // repeat tests in "TEST 1" for 'r5' to ensure that the attributes of 'r5' are same as
    // the attributes of the instance returned in the first case. Even if 'r1' and 'r5' are 
    // references to the same 'Railways' object (having same location), this test is important
    // in order to confirm that calling 'Railways::SpecialRailways' without any parameters
    // does not change their "state". In other words, calls to 'Railways::SpecialRailways'
    // method (without any arguements) subsequent to the first call has no impact on the
    // 'singleton' object

     // check the size of 'r5.stations_' and also its element at each and every index from 0 to 3
    if ( ! ( r5.stations_.at(0) == Station("Amsterdam") && r5.stations_.at(1) == Station("Berlin") && r5.stations_.at(2) == Station("Brussels")
             && r5.stations_.at(3) == Station("Athens") && r5.stations_.size() == 4 ) )
    { cout << "Default construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)' returns a 'Railways' instance with different value of 'Railways::stations_' attribute" << endl ; allPassed = false ; }

     // check if every key in the map 'testPairwiseDistances' is also present in 'r5.distStations_'
    if ( r5.distStations_.find(pair<string, string>{"Amsterdam", "Berlin"}) == r5.distStations_.end() ||
         r5.distStations_.find(pair<string, string>{"Amsterdam", "Brussels"}) == r5.distStations_.end() ||
         r5.distStations_.find(pair<string, string>{"Amsterdam", "Athens"}) == r5.distStations_.end() ||
         r5.distStations_.find(pair<string, string>{"Athens", "Berlin"}) == r5.distStations_.end() || 
         r5.distStations_.find(pair<string, string>{"Athens", "Brussels"}) == r5.distStations_.end() ||
         r5.distStations_.find(pair<string, string>{"Berlin", "Brussels"}) == r5.distStations_.end() ||
         r5.distStations_.size() != 6 )
    { cout << " Default construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)' returns a 'Railways' instance with different value of 'Railways::distStations_' attribute" << endl ; allPassed = false ; }

     // check the size of 'r5.distStations_' and match the values in 'r5.distStations_' corresponding 
     // to each and every key of 'testPairwiseDistances'
    if ( r5.distStations_.size() != 6 || r5.distStations_.at({"Amsterdam", "Berlin"}) != 649 || r5.distStations_.at({"Amsterdam", "Brussels"}) != 209
         || r5.distStations_.at({"Amsterdam", "Athens"}) != 3082 || r5.distStations_.at({"Athens", "Berlin"}) != 2552 || r5.distStations_.at({"Athens", "Brussels"}) != 3021 
         || r5.distStations_.at({"Berlin", "Brussels"}) != 782 )
    { cout << " Default construction through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)' returns a 'Railways' instance with different value of 'Railways::distStations_' attribute" << endl ; allPassed = false ; }

     // repeat tests in "TEST 2" to ensure that the static data members stay intact
    if ( Railways::sStations.size() != 4 || Railways::sStations.at(0) != Station("Amsterdam") || Railways::sStations.at(1) != Station("Berlin") ||
         Railways::sStations.at(2) != Station("Brussels") || Railways::sStations.at(3) != Station("Athens") )
    { cout << "'vector<Station> Railways::sStations' was changed on default construction with different parameters through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }

    if ( Railways::sDistStations.size() != 6 || Railways::sDistStations.at({"Amsterdam", "Berlin"}) != 649 || Railways::sDistStations.at({"Amsterdam", "Brussels"}) != 209
         || Railways::sDistStations.at({"Amsterdam", "Athens"}) != 3082 || Railways::sDistStations.at({"Athens", "Berlin"}) != 2552 || Railways::sDistStations.at({"Athens", "Brussels"}) != 3021 
         || Railways::sDistStations.at({"Berlin", "Brussels"}) != 782 )
    { cout << "'map<pair<string, string>, int> Railways::sDistStations' was changed on default construction with different parameters through 'Railways::SpecialRailways(const vector<Station>&, const map<pair<string, string>, int>&)'" << endl ; allPassed = false ;  }
    
     // "TEST 3", "TEST 4" and "TEST 5" confirm that after the first call to 'Railways::SpecialRailways',
     // the subsequent calls have absolutely NO impact on (1.) the number of instances of 'Railways'
     // class, (2.) the state of the singleton instance, (3.) the values of the static data members.
     // Hence, 'Railways' is a singleton class (even when first call is made with parameters)

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed

}
