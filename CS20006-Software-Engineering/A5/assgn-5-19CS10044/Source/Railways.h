
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include "Station.h"
using namespace std ;

class Railways  // a singleton class
{
    private :
        // non-static data members
        const vector<Station> stations_ ;
        const map<pair<string, string>, unsigned int> distStations_ ;

        // static const data members
        // store the master data regarding a miniature Indian Railways consisting of 5 stations
        static const vector<Station> sIndianRailwaysStations ;
        static const map<pair<string, string>, unsigned int> sIndianRailwaysDistStations ;

        // private constructor -- kept private because Railways is a singleton class
        Railways ( const vector<Station> & , const map<pair<string, string>, unsigned> & ) ;

        // block the copy assignment operator because the singleton Railways instance
        // is supposed to be treated as a constant object
        Railways & operator = ( const Railways & ) const {    }

        // private destructor -- not needed to be public because the only instance
        // pf this class is a static object
        ~Railways ( ) ;

    public :
        friend ostream & operator << ( ostream & , const Railways & ) ; // overloaded output streaming operator
                                                                        // -- friend function
        
        // This method acts as an interface or mediator between the client-side/application and the
        // private constructor. The internal routine of this method takes care of instantiating 'Railways'
        // only once -- when it is called for the first time. In subsequent calls, it simply returns the
        // same instance that is constructed in the first call.
        // Besides, before instantiating the singleton object of Railways, it checks for the validity of the
        // passed arguements for a number of scenarios so that no erroneous arguements are passed to the private 
        // constructor
        static const Railways & SpecialRailways ( const vector<Station> & = Railways::sIndianRailwaysStations , 
                                                  const map<pair<string, string>, unsigned> & = Railways::sIndianRailwaysDistStations ) ;
        // The default parameters are based on the master data given in the specifications.
        
        // non-static method to get the distance between two stations passed as
        // parameters in a 'Railways' network
        unsigned int GetDistance ( const Station & , const Station & ) const ;
        // Implement the unit test plan written for Railways class
        static void UnitTestRailwaysO1 ( ) ;
        static void UnitTestRailwaysO2 ( ) ;
} ;