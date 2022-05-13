
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include "Railways.h"
#include "Exceptions.h"
using namespace std ;

// initialize the static const data members of Railways class
// initialize based on the master data given in the specifications
const vector<Station> Railways::sIndianRailwaysStations {
                                                  Station::CreateStation("Mumbai") , Station::CreateStation("Delhi") ,
                                                  Station::CreateStation("Bangalore") , Station::CreateStation("Kolkata") , Station::CreateStation("Chennai") } ;
const map<pair<string, string>, unsigned int> Railways::sIndianRailwaysDistStations = {
                                                                                { {"Delhi", "Mumbai"}, 1447 } ,
                                                                                { {"Bangalore", "Mumbai"}, 981 } ,
                                                                                { {"Kolkata", "Mumbai"}, 2014 } ,
                                                                                { {"Chennai", "Mumbai"}, 1338 } ,
                                                                                { {"Bangalore", "Delhi"}, 2150 } ,
                                                                                { {"Delhi", "Kolkata"}, 1472 } ,
                                                                                { {"Chennai", "Delhi"}, 2180 } ,
                                                                                { {"Bangalore", "Kolkata"}, 1871 } ,
                                                                                { {"Bangalore", "Chennai"}, 350 } ,
                                                                                { {"Chennai", "Kolkata"}, 1659 }    } ;

// constructor
Railways::Railways ( const vector<Station> & stations , const map<pair<string, string>, unsigned int> & distStations )
    :   stations_(stations) , distStations_(distStations)   // intializer-list
{  
     #ifdef _DEBUG
        cout << "Railways CONSTRUCTED : Indian Railways" << endl ;
     #endif
} 

const Railways & Railways::SpecialRailways ( const vector<Station> & stations , 
                                             const map<pair<string, string>, unsigned int> & distStations )
{
     // FIRST CHECK THE VALIDITY OF THE PASSED/DEFAULT PARAMETERS

     if (stations.size() < 2)      // a valid Railways must have at least two Station objects in its network
          throw Bad_Railways_NotEnoughStations("Railways must have atleast 2 stations") ; // if not, throw a suitable exception
     
     // store in a vector the names of all the Station in the first parameter -- stations
     vector<string> stationNames = { } ;
     
     for ( const Station & s : stations )    // iterate over the vector
          stationNames.push_back(s.GetName()) ;   // use public method Station::GetName to get the name of the Station
     
     // now we can identify the duplicates by looking at the stationNames vector
     sort(stationNames.begin(), stationNames.end()) ;  // sort in order to identify the duplicates
     string prev = "" ;  // keep track of the recently seen Station name
     for ( string & name : stationNames )
          if ( name == prev ) // if there are no duplicates, every Station name will be different from its
                              // immediately preceeding Station name
               throw Bad_Railways_DuplicateStations("No duplicate Station names allowed") ;    // if not, throw a suitable exception
          else      prev = name ;
     
     for ( string & s1 : stationNames )
     {
          if ( distStations.find(pair<string, string>(s1, s1)) != distStations.end() )
               // if for any Station name in stationNames there exist a definition of distance to itsself, then
               // throw a suitable exception
               throw Bad_Railways_DistBwSameStationsDefined("Duplicate distance definition not allowed") ;
          for ( string & s2 : stationNames )
          {
               if ( s1 == s2 )     continue ;     // already checked
               unsigned int dir1 = distStations.find(pair<string, string>(s1, s2)) == distStations.end() ;    // check presence of one order pair in distStations
               unsigned int dir2 = distStations.find(pair<string, string>(s2, s1)) == distStations.end() ;    // check presence of other order pair in distStations
               // exactly one ordered pair of the two distinct Station names must be present in distStations
               if ( dir1 + dir2 == 2 )  // throw exceptions -- no definition
                         throw Bad_Railways_NoDefinition("Distance must be defined between every pair of Stations") ;
               if ( dir1 + dir2 == 0 )  // throw exception -- multiple definitions
                         throw Bad_Railways_RepeatedDefinition("Distance definition is considered symmetric so only one direction must be given") ;
          }
     }
     
     static Railways sSpecialRailways(stations, distStations) ;   // "Meyer's Implementation of a Singleton Class"
     // static locals are declared only once; its lifetime starts when the 
     // function is called and ends only when the program ends. Therefore,
     // the constructor is called only once and that happens when this function
     // is called for the first time
     return sSpecialRailways ; // always return the singleton instance as a const reference
}

ostream & operator << ( ostream & out , const Railways & railways )   // overloaded output streaming operator
{
    out << endl << "   +++ STATIONS +++ " ;
    for ( auto & it : railways.stations_ )   // iterate over the vector of 'Station' and print all of them
                                             // uses 'ostream& operator<<(ostream &, const Station&)'
                                             // defined in "Station.cpp"
        out << endl << " - " << it ;
    out << endl << "--------------------------------------------------------" 
        << endl << "   +++ DISTANCES BETWEEN STATIONS +++ " ;
    for ( auto & it : railways.distStations_ )
        out << endl << " - between " << (it.first).first << " and " << (it.first).second << " : " << it.second ;
          // iterate over the map storing pairwise distances  
          // between all pair of stations and print all of them.
    out << endl ;
    return out ;    // returning the 'ostream' object is important for streaming 
                    // of multiple references to the 'singleton' object chained 
                    // in the same instruction
}

unsigned int Railways::GetDistance ( const Station & s1 , const Station & s2 ) const
{
     pair<string, string> link ;    // the data type of the key in the map 'Railways::distStations_'
     string name1 = s1.GetName() ; string name2 = s2.GetName() ;  // get the names of the 'Station' using 'Station::GetName' method
     link.first = name1 ; link.second = name2 ;    // initialize the link
     if ( distStations_.find(link) != distStations_.end() )  
          return distStations_.at(link) ; // if the key is found, return the value corresponding to that key
     link.first = name2 ; link.second = name1 ;    // otherwise try the reverse order
     if ( distStations_.find(link) != distStations_.end() )
          return distStations_.at(link) ; // if the "reversed" key is found, return the value corresponding to it
     // if none of the ordered pairs is found, throw an exception
     throw Bad_Railways_Distance("No distance defined between the passed pair of stations") ;    
}

// destructor
Railways::~Railways ( ) 
{   
     #ifdef _DEBUG
        cout << "Railways DESTRUCTED : Indian Railways" << endl ;
     #endif
}     // no explicit memory management needed -- no dynamically 
      // allocated memory for any data member -- hence empty body

// Implement unit test plan written for Railways class.
// This method implements all test cases except TEST CASE B.1.7
void Railways::UnitTestRailwaysO1 ( )
{
     const Railways & r1 = Railways::SpecialRailways() ;
     vector<Station> expectedStations = {    Station::CreateStation("Mumbai") , Station::CreateStation("Delhi") ,
                                             Station::CreateStation("Bangalore") , Station::CreateStation("Kolkata") , 
                                             Station::CreateStation("Chennai") } ;
     map<pair<string, string>, unsigned> expectedDistances = {
                                                                 { {"Delhi", "Mumbai"}, 1447 } ,
                                                                 { {"Bangalore", "Mumbai"}, 981 } ,
                                                                 { {"Kolkata", "Mumbai"}, 2014 } ,
                                                                 { {"Chennai", "Mumbai"}, 1338 } ,
                                                                 { {"Bangalore", "Delhi"}, 2150 } ,
                                                                 { {"Delhi", "Kolkata"}, 1472 } ,
                                                                 { {"Chennai", "Delhi"}, 2180 } ,
                                                                 { {"Bangalore", "Kolkata"}, 1871 } ,
                                                                 { {"Bangalore", "Chennai"}, 350 } ,
                                                                 { {"Chennai", "Kolkata"}, 1659 }    } ;
     if ( r1.stations_ == expectedStations && r1.distStations_ == expectedDistances )     // check if the data members are correctly initialized
          cout << "   TEST CASE B.1.1 PASSED" << endl ;
     
     // NOW CHECK ALL THE ERRONEOUS CASES
     // Try passing arguements with empty stations vector
     try
     { Railways::SpecialRailways({}, {}) ; }
     catch( Bad_Railways_NotEnoughStations )
     { cout << "   TEST CASE B.1.2.1 PASSED" << endl ; }

     // Try passing arguements with a singleton station vector
     try
     { Railways::SpecialRailways({Station::CreateStation("Delhi")}, {}) ; }
     catch( Bad_Railways_NotEnoughStations )
     { cout << "   TEST CASE B.1.2.2 PASSED" << endl ; }

     // Try passing arguements where duplicate stations are present
     try
     { Railways::SpecialRailways(  { Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Station::CreateStation("Mumbai") }, 
                                   { {{"Delhi", "Mumbai"}, 1447} }   ) ; }
     catch( Bad_Railways_DuplicateStations )
     { cout << "   TEST CASE B.1.3 PASSED" << endl ; }
     
     // Try passing arguements where distance between same stations is defined
     try
     { Railways::SpecialRailways(  { Station::CreateStation("Mumbai"), Station::CreateStation("Delhi") }, 
                                   { {{"Delhi", "Delhi"}, 5} }   ) ; }
     catch( Bad_Railways_DistBwSameStationsDefined )
     { cout << "   TEST CASE B.1.4 PASSED" << endl ; }

     // Try passing arguements where distance between two distinct stations is defined
     // for both the ordered pairs
     try
     { Railways::SpecialRailways(  { Station::CreateStation("Mumbai"), Station::CreateStation("Delhi") }, 
                                   { {{"Delhi", "Mumbai"}, 1447}, {{"Mumbai", "Delhi"}, 1447} }   ) ; }
     catch( Bad_Railways_RepeatedDefinition )
     { cout << "   TEST CASE B.1.5 PASSED" << endl ; }

     // Try passing arguements where distance between a pair of distinct stations is not defined
     try
     { Railways::SpecialRailways(  { Station::CreateStation("Mumbai"), Station::CreateStation("Delhi") }, 
                                   { }   ) ; }
     catch( Bad_Railways_NoDefinition )
     { cout << "   TEST CASE B.1.6 PASSED" << endl ; }

     // check if the same instance is returned everytime "Railways::SpecialRailways()" is called
     const Railways & r2 = Railways::SpecialRailways() ;
     const Railways & r3 = Railways::SpecialRailways() ;
     // compare the addresses of the two variables to check if they are the same instance
     if ( &r2 == &r3 )
          cout << "   TEST CASE B.1.8 PASSED" << endl ;

     // print Railways object onto the console
     cout << "   TEST CASE B.2.1 -- \n\t" << r1 << endl ;

     // test non static data members
     // try getting distance between a pair of stations, for which it is not defined
     try
     { Railways::SpecialRailways().GetDistance(Station::CreateStation("Delhi"), Station::CreateStation("Pune")) ; }
     catch( Bad_Railways_Distance )
     { cout << "   TEST CASE B.3.1 PASSED" << endl ; }
     // check if the correct distance is returned (match with the golden output)
     if ( Railways::SpecialRailways().GetDistance(Station::CreateStation("Delhi"), Station::CreateStation("Mumbai")) == 1447 )
          cout << "   TEST CASE B.3.2.1 PASSED" << endl ;
     // check for symmetry in distance function
     if ( Railways::SpecialRailways().GetDistance(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi")) == 1447 )
          cout << "   TEST CASE B.3.2.2 PASSED" << endl ;

}

// Implement unit test plan written for Railways class.
// This method implements only the TEST CASE B.1.7
void Railways::UnitTestRailwaysO2 ( )
{
     // CUSTOM INDIAN RAILWAYS
     // Pass custom arguements, adhering to the validity protocols, to the first call of Railways::SpecialRailways method
     // to construct the singleton Railways object with the passed arguements, not with the default arguements
     vector<Station> stations = {  Station::CreateStation("Mumbai") , Station::CreateStation("Delhi") } ;
     map<pair<string, string>, unsigned> distances = { { {"Delhi", "Mumbai"}, 1447 }  } ;
     const Railways & r1 = Railways::SpecialRailways(stations, distances) ;     // first call to Railways::SpecialRailways
     if ( r1.stations_ == stations && r1.distStations_ == distances )     // check if the data members are correctly initialized
          cout << "   TEST CASE B.1.7 PASSED" << endl ;
}