
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#include <string>
#include "BookingClass.h"
using namespace std ;

// initialize the static const data members for all the static sub-types
// of BookingClass with the information given in the master data of the specifications

// initialize sName const static data member for all the static sub-types
template<> const string BookingClass::ACFirstClass::sName = "AC First Class" ;
template<> const string BookingClass::ExecutiveChairCar::sName = "Executive Chair Car" ;
template<> const string BookingClass::AC2Tier::sName = "AC 2 Tier" ;
template<> const string BookingClass::FirstClass::sName = "First Class" ;
template<> const string BookingClass::AC3Tier::sName = "AC 3 Tier" ;
template<> const string BookingClass::ACChairCar::sName = "AC Chair Car" ;
template<> const string BookingClass::Sleeper::sName = "Sleeper" ;
template<> const string BookingClass::SecondSitting::sName = "Second Sitting" ;

// initialize sLoadFactor const static data member for all the static sub-types
template<> const double BookingClass::ACFirstClass::sLoadFactor = 6.50 ;
template<> const double BookingClass::ExecutiveChairCar::sLoadFactor = 5.00 ;
template<> const double BookingClass::AC2Tier::sLoadFactor = 4.00 ;
template<> const double BookingClass::FirstClass::sLoadFactor = 3.00 ;
template<> const double BookingClass::AC3Tier::sLoadFactor = 2.50 ;
template<> const double BookingClass::ACChairCar::sLoadFactor = 2.00 ;
template<> const double BookingClass::Sleeper::sLoadFactor = 1.00 ;
template<> const double BookingClass::SecondSitting::sLoadFactor = 0.60 ;

// initialize sIsSitting const static data member for all the static sub-types
template<> const bool BookingClass::ACFirstClass::sIsSitting = false ;
template<> const bool BookingClass::ExecutiveChairCar::sIsSitting = true ;
template<> const bool BookingClass::AC2Tier::sIsSitting = false ;
template<> const bool BookingClass::FirstClass::sIsSitting = false ;
template<> const bool BookingClass::AC3Tier::sIsSitting = false ;
template<> const bool BookingClass::ACChairCar::sIsSitting = true ;
template<> const bool BookingClass::Sleeper::sIsSitting = false ;
template<> const bool BookingClass::SecondSitting::sIsSitting = true ;

// initialize sIsAC const static data member for all the static sub-types
template<> const bool BookingClass::ACFirstClass::sIsAC = true ;
template<> const bool BookingClass::ExecutiveChairCar::sIsAC = true ;
template<> const bool BookingClass::AC2Tier::sIsAC = true ;
template<> const bool BookingClass::FirstClass::sIsAC = false ;
template<> const bool BookingClass::AC3Tier::sIsAC = true ;
template<> const bool BookingClass::ACChairCar::sIsAC = true ;
template<> const bool BookingClass::Sleeper::sIsAC = false ;
template<> const bool BookingClass::SecondSitting::sIsAC = false ;

// initialize sIsLuxury const static data member for all the static sub-types
template<> const bool BookingClass::ACFirstClass::sIsLuxury = true ;
template<> const bool BookingClass::ExecutiveChairCar::sIsLuxury = true ;
template<> const bool BookingClass::AC2Tier::sIsLuxury = false ;
template<> const bool BookingClass::FirstClass::sIsLuxury = true ;
template<> const bool BookingClass::AC3Tier::sIsLuxury = false ;
template<> const bool BookingClass::ACChairCar::sIsLuxury = false ;
template<> const bool BookingClass::Sleeper::sIsLuxury = false ;
template<> const bool BookingClass::SecondSitting::sIsLuxury = false ;

// initialize sNumberOfTiers const static data member for all the static sub-types
template<> const unsigned BookingClass::ACFirstClass::sNumberOfTiers = 2 ;
template<> const unsigned BookingClass::ExecutiveChairCar::sNumberOfTiers = 0 ;
template<> const unsigned BookingClass::AC2Tier::sNumberOfTiers = 2 ;
template<> const unsigned BookingClass::FirstClass::sNumberOfTiers = 2 ;
template<> const unsigned BookingClass::AC3Tier::sNumberOfTiers = 3 ;
template<> const unsigned BookingClass::ACChairCar::sNumberOfTiers = 0 ;
template<> const unsigned BookingClass::Sleeper::sNumberOfTiers = 3 ;
template<> const unsigned BookingClass::SecondSitting::sNumberOfTiers = 0 ;

// initialize sReservationCharge const static data member for all the static sub-types
template<> const double BookingClass::ACFirstClass::sReservationCharge = 60.00 ;
template<> const double BookingClass::ExecutiveChairCar::sReservationCharge = 60.00 ;
template<> const double BookingClass::AC2Tier::sReservationCharge = 50.00 ;
template<> const double BookingClass::FirstClass::sReservationCharge = 50.00 ;
template<> const double BookingClass::AC3Tier::sReservationCharge = 40.00 ;
template<> const double BookingClass::ACChairCar::sReservationCharge = 40.00 ;
template<> const double BookingClass::Sleeper::sReservationCharge = 20.00 ;
template<> const double BookingClass::SecondSitting::sReservationCharge = 15.00 ;

// initialize sTatkalCharge const static data member for all the static sub-types
template<> const double BookingClass::ACFirstClass::sTatkalCharge = 0.30 ;
template<> const double BookingClass::ExecutiveChairCar::sTatkalCharge = 0.30 ;
template<> const double BookingClass::AC2Tier::sTatkalCharge = 0.30 ;
template<> const double BookingClass::FirstClass::sTatkalCharge = 0.30 ;
template<> const double BookingClass::AC3Tier::sTatkalCharge = 0.30 ;
template<> const double BookingClass::ACChairCar::sTatkalCharge = 0.30 ;
template<> const double BookingClass::Sleeper::sTatkalCharge = 0.30 ;
template<> const double BookingClass::SecondSitting::sTatkalCharge = 0.10 ;

// initialize sMaxTatkalCharge const static data member for all the static sub-types
template<> const double BookingClass::ACFirstClass::sMaxTatkalCharge = 500.00 ;
template<> const double BookingClass::ExecutiveChairCar::sMaxTatkalCharge = 500.00 ;
template<> const double BookingClass::AC2Tier::sMaxTatkalCharge = 500.00 ;
template<> const double BookingClass::FirstClass::sMaxTatkalCharge = 500.00 ;
template<> const double BookingClass::AC3Tier::sMaxTatkalCharge = 400.00 ;
template<> const double BookingClass::ACChairCar::sMaxTatkalCharge = 225.00 ;
template<> const double BookingClass::Sleeper::sMaxTatkalCharge = 200.00 ;
template<> const double BookingClass::SecondSitting::sMaxTatkalCharge = 15.00 ;

// initialize sMinTatkalCharge const static data member for all the static sub-types
template<> const double BookingClass::ACFirstClass::sMinTatkalCharge = 400.00 ;
template<> const double BookingClass::ExecutiveChairCar::sMinTatkalCharge = 400.00 ;
template<> const double BookingClass::AC2Tier::sMinTatkalCharge = 400.00 ;
template<> const double BookingClass::FirstClass::sMinTatkalCharge = 400.00 ;
template<> const double BookingClass::AC3Tier::sMinTatkalCharge = 300.00 ;
template<> const double BookingClass::ACChairCar::sMinTatkalCharge = 125.00 ;
template<> const double BookingClass::Sleeper::sMinTatkalCharge = 100.00 ;
template<> const double BookingClass::SecondSitting::sMinTatkalCharge = 10.00 ;

// initialize sMinDistanceForTatkalCharge const static data member for all the static sub-types
template<> const unsigned BookingClass::ACFirstClass::sMinDistanceForTatkalCharge = 500 ;
template<> const unsigned BookingClass::ExecutiveChairCar::sMinDistanceForTatkalCharge = 250 ;
template<> const unsigned BookingClass::AC2Tier::sMinDistanceForTatkalCharge = 500 ;
template<> const unsigned BookingClass::FirstClass::sMinDistanceForTatkalCharge = 500 ;
template<> const unsigned BookingClass::AC3Tier::sMinDistanceForTatkalCharge = 500 ;
template<> const unsigned BookingClass::ACChairCar::sMinDistanceForTatkalCharge = 250 ;
template<> const unsigned BookingClass::Sleeper::sMinDistanceForTatkalCharge = 500 ;
template<> const unsigned BookingClass::SecondSitting::sMinDistanceForTatkalCharge = 100 ;

// overloaded output streaming operator
ostream & operator << ( ostream & out , const BookingClass & bc )
{
    out << endl ;
    // print all the details for the BookingClass sub-type
    // stored in the static data members.
    // get the information using the various non-static member functions
    // each one of which is meant to return the value of a particular 
    // static data member
    out << endl << "  +++ DETAILS OF THE BOOKING CLASS +++" ;
    out << endl << "    - Name : " << bc.GetName() ;
    out << endl << "    - Load factor : " << bc.GetLoadFactor() ;
    out << endl << "    - No. of tiers : " << bc.GetNumberOfTiers() ;
    out << endl << "    - Is sitting : " << bc.IsSitting() ;
    out << endl << "    - Is AC : " << bc.IsAC() ;
    out << endl << "    - Is luxury : " << bc.IsLuxury() ;
    out << endl << "    - Reservation Charge : " << bc.IsLuxury() ;
    out << endl << "    - Tatkal Charge : " << bc.GetTatkalCharge() ;
    out << endl << "    - Minimum Distance for Tatkal Charge : " << bc.GetMinDistanceForTatkalCharge() ;
    out << endl << "    - Minimum Tatkal Charge : " << bc.GetMaxTatkalCharge() ;
    out << endl << "    - Maximum Tatkal Charge : " << bc.GetMinTatkalCharge() ;
    out << endl ;
    return out ;    // returning the 'ostream' object is important for streaming 
                    // of multiple instances chained in the same instruction
}

// implementation of the Unit Test Plan written for BookingClass hierarchy
void BookingClass::UnitTestBookingClassHierarchy ( )
{
    // print a BookingClass sub-type onto the console using the
    // overloaded output streaming operator
    cout << "   TEST CASE D.1.1 -- " << BookingClass::ACFirstClass::Type() << endl ;
    
    // test the non-static member functions for a BookingClass sub-type
    // match the returned values with the golden output
    if ( BookingClass::ACFirstClass::Type().GetName() == "AC First Class" )
        cout << "   TEST D.2.1.1 PASSED" << endl ;
    
    if ( BookingClass::ACFirstClass::Type().GetLoadFactor() == 6.50 )
        cout << "   TEST D.2.2.1 PASSED" << endl ;

    if ( BookingClass::ACFirstClass::Type().IsSitting() == false )
        cout << "   TEST D.2.3.1 PASSED" << endl ;

    if ( BookingClass::ACFirstClass::Type().IsAC() == true )
        cout << "   TEST D.2.4.1 PASSED" << endl ;
    
    if ( BookingClass::ACFirstClass::Type().IsLuxury() == true )
        cout << "   TEST D.2.5.1 PASSED" << endl ;

    if ( BookingClass::ACFirstClass::Type().GetNumberOfTiers() == 2 )
        cout << "   TEST D.2.6.1 PASSED" << endl ;
    
    if ( BookingClass::ACFirstClass::Type().GetReservationCharge() == 60.00 )
        cout << "   TEST D.2.7.1 PASSED" << endl ;
    
    if ( BookingClass::ACFirstClass::Type().GetTatkalCharge() == 0.30 )
        cout << "   TEST D.2.8.1 PASSED" << endl ;
    
    if ( BookingClass::ACFirstClass::Type().GetMinTatkalCharge() == 400.00 )
        cout << "   TEST D.2.9.1 PASSED" << endl ;
    
    if ( BookingClass::ACFirstClass::Type().GetMaxTatkalCharge() == 500.00 )
        cout << "   TEST D.2.10.1 PASSED" << endl ;

    if ( BookingClass::ACFirstClass::Type().GetMinDistanceForTatkalCharge() == 500 )
        cout << "   TEST D.2.11.1 PASSED" << endl ;

    // test the non-static member functions again by changing the BookingClass sub-type
    // to any type other than ACFirstClass
    // match the returned values with the golden output
    if ( BookingClass::ExecutiveChairCar::Type().GetName() == "Executive Chair Car" )
        cout << "   TEST D.2.1.2 PASSED" << endl ;
    
    if ( BookingClass::AC2Tier::Type().GetLoadFactor() == 4.00 )
        cout << "   TEST D.2.2.2 PASSED" << endl ;

    if ( BookingClass::FirstClass::Type().IsSitting() == false )
        cout << "   TEST D.2.3.2 PASSED" << endl ;

    if ( BookingClass::ACChairCar::Type().IsAC() == true )
        cout << "   TEST D.2.4.2 PASSED" << endl ;
    
    if ( BookingClass::Sleeper::Type().IsLuxury() == false )
        cout << "   TEST D.2.5.2 PASSED" << endl ;

    if ( BookingClass::Sleeper::Type().GetNumberOfTiers() == 3 )
        cout << "   TEST D.2.6.2 PASSED" << endl ;
    
    if ( BookingClass::SecondSitting::Type().GetReservationCharge() == 15.00 )
        cout << "   TEST D.2.7.2 PASSED" << endl ;
    
    if ( BookingClass::SecondSitting::Type().GetTatkalCharge() == 0.10 )
        cout << "   TEST D.2.8.2 PASSED" << endl ;
    
    if ( BookingClass::SecondSitting::Type().GetMinTatkalCharge() == 10.00 )
        cout << "   TEST D.2.9.2 PASSED" << endl ;
    
    if ( BookingClass::SecondSitting::Type().GetMaxTatkalCharge() == 15.00 )
        cout << "   TEST D.2.10.2 PASSED" << endl ;

    if ( BookingClass::ACChairCar::Type().GetMinDistanceForTatkalCharge() == 250 )
        cout << "   TEST D.2.11.2 PASSED" << endl ;

    // check if the sub-types of Divyaang are implemented as singletons
    const BookingClass & b1 = BookingClass::ACFirstClass::Type() ;
    const BookingClass & b2 = BookingClass::ACFirstClass::Type() ;
    if ( &b1 == &b2 )   // check if the BookingClass sub-type is constructed only once.
                        // compare the addresses to ensure that they are indeed the same instances and
                        // hence the sub-type class is indeed a singleton class
        cout << "   TEST D.3.1 PASSED" << endl ;

    // test dynamic dispatch of all the polymorphic methods
    const BookingClass & b = BookingClass::ACFirstClass::Type() ;    // upcast the Divyaang sub-type to the const reference of base class

    // call all the polymorphic methods on this upcasted reference variable and match the
    // returned values with the golden outputs
    if ( b.GetName() == "AC First Class" )
        cout << "   TEST D.4.1 PASSED" << endl ;
    
    if ( b.GetLoadFactor() == 6.50 )
        cout << "   TEST D.4.2 PASSED" << endl ;

    if ( b.IsSitting() == false )
        cout << "   TEST D.4.3 PASSED" << endl ;

    if ( b.IsAC() == true )
        cout << "   TEST D.4.4 PASSED" << endl ;
    
    if ( b.IsLuxury() == true )
        cout << "   TEST D.4.5 PASSED" << endl ;

    if ( b.GetNumberOfTiers() == 2 )
        cout << "   TEST D.4.6 PASSED" << endl ;
    
    if ( b.GetReservationCharge() == 60.00 )
        cout << "   TEST D.4.7 PASSED" << endl ;
    
    if ( b.GetTatkalCharge() == 0.30 )
        cout << "   TEST D.4.8 PASSED" << endl ;
    
    if ( b.GetMinTatkalCharge() == 400.00 )
        cout << "   TEST D.4.9 PASSED" << endl ;
    
    if ( b.GetMaxTatkalCharge() == 500.00 )
        cout << "   TEST D.4.10 PASSED" << endl ;

    if ( b.GetMinDistanceForTatkalCharge() == 500 )
        cout << "   TEST D.4.11 PASSED" << endl ;

}