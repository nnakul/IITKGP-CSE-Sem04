
//  SOFTWARE ENGINEERING -- ASSIGNMENT O3
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include "Station.h"
using namespace std ;

class Railways
{
    private :
        // static data members to store the state of the "singleton" Railways instance
        // If these were 'const' data members then either they will have to be initialized 
        // before any instantiation of 'Railways' or they will be assigned some garbage value 
        // that cannot be overwritten. In that case, when the singleton object is constructed, 
        // these data members can not be changed as per the properties of the object. Therefore,
        // these static data members cannot be 'const' despite of the non-static data members
        // of the singleton instance being 'const'. 
        static vector<Station> sStations ;
        static map<pair<string, string>, int> sDistStations ;
        
        // non-static 'const' data members that store the "constant" state of 
        // the "singleton" Railways instance
        const vector<Station> stations_ ;
        const map<pair<string, string>, int> distStations_ ;

        // private constructor -- in order to control the number of instances of 'Railways' class
        Railways ( const vector<Station> & , const map<pair<string, string>, int> & ) ;
        
        // it is important to block the copy assignment operator for a "singleton" class
        Railways & operator = ( const Railways & ) const {    }
        
        // private destructor -- It is a good idea to make a destructor of a 'singleton' class 
        // private because then the client/application code won't call the destructor by accident. 
        // Calling the destructor would cause the singleton to fail for all applications in the 
        // project as the instance would become invalid.
        ~Railways ( ) ;

    public :
        friend ostream & operator << ( ostream & , const Railways & ) ; // overloaded output streaming operator
                                                                        // -- friend function
        
        // This method acts as an interface or mediator between the client-side/application and the
        // private constructor. The internal routine of this method takes care of instantiating 'Railways'
        // only once -- when it is called for the first time. In subsequent calls, it simply returns the
        // same instance that is constructed in the first call.
        // Though in the assignment everything is inspired from the "Indian Railways", this method is
        // quite flexible in the sense that it can also construct the singleton instance of 'Railways' class
        // modelling any arbitrary railways, say "European Railways". This is taken care of by the parameters.
        // While this feature will help a lot in testing this method thoroughly for its functionality,
        // the attributes of an "Indian Railways" are kept as default parameters so that by default
        // the application is set to work with only "Indian Railways" and we dont have to worry on the 
        // client-side about passing parameters.
        static const Railways & SpecialRailways ( const vector<Station> & = {
                                                                                Station("Mumbai") , Station("Delhi") ,
                                                                                Station("Bangalore") , Station("Kolkata") , Station("Chennai") } , 
                                                  const map<pair<string, string>, int> & = {
                                                                                                { {"Delhi", "Mumbai"}, 1447 } ,
                                                                                                { {"Bangalore", "Mumbai"}, 981 } ,
                                                                                                { {"Kolkata", "Mumbai"}, 2014 } ,
                                                                                                { {"Chennai", "Mumbai"}, 1338 } ,
                                                                                                { {"Bangalore", "Delhi"}, 2150 } ,
                                                                                                { {"Delhi", "Kolkata"}, 1472 } ,
                                                                                                { {"Chennai", "Delhi"}, 2180 } ,
                                                                                                { {"Bangalore", "Kolkata"}, 1871 } ,
                                                                                                { {"Bangalore", "Chennai"}, 350 } ,
                                                                                                { {"Chennai", "Kolkata"}, 1659 }    } ) ;
        
        // non-static method to get the distance between two stations passed as
        // parameters in a 'Railways' network
        int GetDistance ( const Station & , const Station & ) const ;

        // unit tests -- two broad scenarios
        static void UnitTestRailwaysScenarioO1 ( ) ;
        static void UnitTestRailwaysScenarioO2 ( ) ;
} ;