
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <map>
#include "Divyaang.h"
#include "Exceptions.h"
using namespace std ;

// overloaded output streaming operator
ostream & operator << ( ostream & out , const Divyaang & d )
{
    out << endl ;
    out << " " << d.GetName() << endl ; // print the name of the Divyaang sub-type onto the console
    // print the values of concession factors in each BookingClass sub-type for this particular Divyaang type
    // use "DivyaangTypes<T>::GetConcessionFactor" method for this
    out << " Concession for AC First Class: " << d.GetConcessionFactor(BookingClass::ACFirstClass::Type()) << endl ;
    out << " Concession for Executive Chair Car: " << d.GetConcessionFactor(BookingClass::ExecutiveChairCar::Type()) << endl ;
    out << " Concession for AC 2 Tier: " << d.GetConcessionFactor(BookingClass::AC2Tier::Type()) << endl ;
    out << " Concession for First Class: " << d.GetConcessionFactor(BookingClass::FirstClass::Type()) << endl ;
    out << " Concession for AC 3 Tier: " << d.GetConcessionFactor(BookingClass::AC3Tier::Type()) << endl ;
    out << " Concession for AC Chair Car: " << d.GetConcessionFactor(BookingClass::ACChairCar::Type()) << endl ;
    out << " Concession for Sleeper: " << d.GetConcessionFactor(BookingClass::Sleeper::Type()) << endl ;
    out << " Concession for Second Sitting: " << d.GetConcessionFactor(BookingClass::SecondSitting::Type()) << endl ;
    return out ;    // returning the 'ostream' object is important for streaming 
                    // of multiple instances chained in the same instruction
}

// initialize the static const data members for all the static sub-types
template<> const string Divyaang::Blind::sName = "Blind" ;
template<> const string Divyaang::OrthopaedicallyHandicapped::sName = "Orthopaedically Handicapped" ;
template<> const string Divyaang::CancerPatients::sName = "Cancer Patients" ;
template<> const string Divyaang::TBPatients::sName = "TB Patients" ;

// initialize the [ Booking Class -> Concession Factor ] map for each of the 
// four Divyaang sub-types with the data given in Master Data of specificiations
template<> const map<string, double> Divyaang::Blind::sConcessionFactors = {
    {"AC First Class", 0.50},
    {"Executive Chair Car", 0.75},
    {"AC 2 Tier", 0.50},
    {"First Class", 0.75},
    {"AC 3 Tier", 0.75},
    {"AC Chair Car", 0.75},
    {"Sleeper", 0.75},
    {"Second Sitting", 0.75}
} ;

template<> const map<string, double> Divyaang::OrthopaedicallyHandicapped::sConcessionFactors = {
    {"AC First Class", 0.50},
    {"Executive Chair Car", 0.75},
    {"AC 2 Tier", 0.50},
    {"First Class", 0.75},
    {"AC 3 Tier", 0.75},
    {"AC Chair Car", 0.75},
    {"Sleeper", 0.75},
    {"Second Sitting", 0.75}
} ;

template<> const map<string, double> Divyaang::CancerPatients::sConcessionFactors = {
    {"AC First Class", 0.50},
    {"Executive Chair Car", 0.75},
    {"AC 2 Tier", 0.50},
    {"First Class", 0.75},
    {"AC 3 Tier", 1.00},
    {"AC Chair Car", 1.00},
    {"Sleeper", 1.00},
    {"Second Sitting", 1.00}
} ;

template<> const map<string, double> Divyaang::TBPatients::sConcessionFactors = {
    {"AC First Class", 0.00},
    {"Executive Chair Car", 0.00},
    {"AC 2 Tier", 0.00},
    {"First Class", 0.75},
    {"AC 3 Tier", 0.00},
    {"AC Chair Car", 0.00},
    {"Sleeper", 0.75},
    {"Second Sitting", 0.75}
} ;

// Now give definition of 'DivyaangTypes<T>::GetConcessionFactor' method for each of the
// four Divyaang sub-types independently

// overriden 'DivyaangTypes<T>::GetConcessionFactor' method in 'Divyaang::Blind' sub-class
template < >
double Divyaang::Blind::GetConcessionFactor ( const BookingClass & b ) const
{
    // first of all check if the BookingClass sub-type passed as a parameter
    // is a valid sub-type, i.e., it must match one one of the 8 BookingClass sub-types
    if ( &b != &BookingClass::ACFirstClass::Type() &&
         &b != &BookingClass::ExecutiveChairCar::Type() &&
         &b != &BookingClass::AC2Tier::Type() &&
         &b != &BookingClass::FirstClass::Type() &&
         &b != &BookingClass::AC3Tier::Type() &&
         &b != &BookingClass::ACChairCar::Type() &&
         &b != &BookingClass::Sleeper::Type() &&
         &b != &BookingClass::SecondSitting::Type() )
        // if it does not match any of them, a Bad_Access exception must be thrown
        throw Bad_Access("Invalid BookingClass sub-type passed as arguement to Divyaang::Blind::GetConcessionFactor") ;
    return Divyaang::Blind::sConcessionFactors.at(b.GetName()) ;    // otherwise, get the name of the BookingClass sub-type and search
                                                                    // the map Divyaang::Blind::sConcessionFactors using this name as key.
                                                                    // return the corresponding value.
}

// overriden 'DivyaangTypes<T>::GetConcessionFactor' method in 'Divyaang::TBPatients' sub-class
template < >
double Divyaang::TBPatients::GetConcessionFactor ( const BookingClass & b ) const
{
    // first of all check if the BookingClass sub-type passed as a parameter
    // is a valid sub-type, i.e., it must match one one of the 8 BookingClass sub-types
    if ( &b != &BookingClass::ACFirstClass::Type() &&
         &b != &BookingClass::ExecutiveChairCar::Type() &&
         &b != &BookingClass::AC2Tier::Type() &&
         &b != &BookingClass::FirstClass::Type() &&
         &b != &BookingClass::AC3Tier::Type() &&
         &b != &BookingClass::ACChairCar::Type() &&
         &b != &BookingClass::Sleeper::Type() &&
         &b != &BookingClass::SecondSitting::Type() )
         // if it does not match any of them, a Bad_Access exception must be thrown
        throw Bad_Access("Invalid BookingClass sub-type passed as arguement to Divyaang::TBPatients::GetConcessionFactor") ;
    return Divyaang::TBPatients::sConcessionFactors.at(b.GetName()) ;   // otherwise, get the name of the BookingClass sub-type and search
                                                                        // the map Divyaang::TBPatients::sConcessionFactors using this name as key.
                                                                        // return the corresponding value.
}

// overriden 'DivyaangTypes<T>::GetConcessionFactor' method in 'Divyaang::CancerPatients' sub-class
template < >
double Divyaang::CancerPatients::GetConcessionFactor ( const BookingClass & b ) const
{
    // first of all check if the BookingClass sub-type passed as a parameter
    // is a valid sub-type, i.e., it must match one one of the 8 BookingClass sub-types
    if ( &b != &BookingClass::ACFirstClass::Type() &&
         &b != &BookingClass::ExecutiveChairCar::Type() &&
         &b != &BookingClass::AC2Tier::Type() &&
         &b != &BookingClass::FirstClass::Type() &&
         &b != &BookingClass::AC3Tier::Type() &&
         &b != &BookingClass::ACChairCar::Type() &&
         &b != &BookingClass::Sleeper::Type() &&
         &b != &BookingClass::SecondSitting::Type() )
         // if it does not match any of them, a Bad_Access exception must be thrown
        throw Bad_Access("Invalid BookingClass sub-type passed as arguement to Divyaang::CancerPatients::GetConcessionFactor") ;
    return Divyaang::CancerPatients::sConcessionFactors.at(b.GetName()) ;   // otherwise, get the name of the BookingClass sub-type and search
                                                                            // the map Divyaang::CancerPatients::sConcessionFactors using this name as key.
                                                                            // return the corresponding value.
}

// overriden 'DivyaangTypes<T>::GetConcessionFactor' method in 'Divyaang::OrthopaedicallyHandicapped' sub-class
template < >
double Divyaang::OrthopaedicallyHandicapped::GetConcessionFactor ( const BookingClass & b ) const
{
    // first of all check if the BookingClass sub-type passed as a parameter
    // is a valid sub-type, i.e., it must match one one of the 8 BookingClass sub-types
    if ( &b != &BookingClass::ACFirstClass::Type() &&
         &b != &BookingClass::ExecutiveChairCar::Type() &&
         &b != &BookingClass::AC2Tier::Type() &&
         &b != &BookingClass::FirstClass::Type() &&
         &b != &BookingClass::AC3Tier::Type() &&
         &b != &BookingClass::ACChairCar::Type() &&
         &b != &BookingClass::Sleeper::Type() &&
         &b != &BookingClass::SecondSitting::Type() )
         // if it does not match any of them, a Bad_Access exception must be thrown
        throw Bad_Access("Invalid BookingClass sub-type passed as arguement to Divyaang::OrthopaedicallyHandicapped::GetConcessionFactor") ;
    return Divyaang::OrthopaedicallyHandicapped::sConcessionFactors.at(b.GetName()) ;   // otherwise, get the name of the BookingClass sub-type and search
                                                                                        // the map Divyaang::OrthopaedicallyHandicapped::sConcessionFactors 
                                                                                        // using this name as key. Return the corresponding value.
}

// In order to model the test case of checking the erroneous
// BookingClass type, an invalid BookingClass sub-type has to be introduced
// as given in the test plan document. 
struct BCTestType { } ;    // placeholder for the invalid static sub-type
// give arbitrarily any values to the static data members for this invalid sub-type
template<>  const string BookingClassTypes<BCTestType>::sName = "Test" ;
template<>  const double BookingClassTypes<BCTestType>::sLoadFactor = false ;
template<>  const bool BookingClassTypes<BCTestType>::sIsSitting = false ;
template<>  const bool BookingClassTypes<BCTestType>::sIsAC = false ;
template<>  const bool BookingClassTypes<BCTestType>::sIsLuxury = 0 ;
template<>  const unsigned int BookingClassTypes<BCTestType>::sNumberOfTiers = 0 ;
template<>  const double BookingClassTypes<BCTestType>::sReservationCharge = 0.0 ;
template<>  const double BookingClassTypes<BCTestType>::sTatkalCharge = 0.0 ;
template<>  const double BookingClassTypes<BCTestType>::sMaxTatkalCharge = 0.0 ;
template<>  const double BookingClassTypes<BCTestType>::sMinTatkalCharge = 0.0 ;
template<>  const unsigned int BookingClassTypes<BCTestType>::sMinDistanceForTatkalCharge = 0 ;

// implementation of the Unit Test Plan written for Divyaang hierarchy
void Divyaang::UnitTestDivyaangHierarchy ( )
{
    // print a Divyaang sub-type onto the concole
    cout << "   TEST CASE E.1.1 --" << Divyaang::Blind::Type() ;

    // test non-static member functions
    if ( Divyaang::Blind::Type().GetName() == "Blind" ) // test GetName method on Blind sub-type
        cout << "   TEST CASE E.2.1.1 PASSED" << endl ;
    
    if ( Divyaang::TBPatients::Type().GetName() == "TB Patients" )  // change the sub-type and test again
        cout << "   TEST CASE E.2.1.2 PASSED" << endl ;
    
    // test GetConcessionFactor method on Blind sub-type for ACFirstClass
    if ( Divyaang::Blind::Type().GetConcessionFactor(BookingClass::ACFirstClass::Type()) == 0.50 ) 
        cout << "   TEST CASE E.2.2.1 PASSED" << endl ;
    
    // change only the BookingClass sub-type and test again
    if ( Divyaang::Blind::Type().GetConcessionFactor(BookingClass::FirstClass::Type()) == 0.75 )
        cout << "   TEST CASE E.2.2.2 PASSED" << endl ;

    // check for an invalid BookingClass sub-type and ensure an exception is thrown
    try
    { Divyaang::Blind::Type().GetConcessionFactor(BookingClassTypes<BCTestType>::Type()) ; }
    catch ( Bad_Access )
    { cout << "   TEST CASE E.2.3 PASSED" << endl ; }

    // change the Divyaang sub-type and test again
    if ( Divyaang::TBPatients::Type().GetConcessionFactor(BookingClass::ACFirstClass::Type()) == 0.00 )
        cout << "   TEST CASE E.2.4 PASSED" << endl ;

    // check if the sub-types of Divyaang are implemented as singletons
    const Divyaang & d1 = Divyaang::Blind::Type() ;    // upcast the Divyaang sub-type to the const reference of base class
    const Divyaang & d2 = Divyaang::Blind::Type() ;
    if ( &d1 == &d2 )   // check if the Divyaang sub-type is constructed only once.
                        // compare the addresses to ensure that they are indeed the same instances and
                        // hence the sub-type class is indeed a singleton class
        cout << "   TEST CASE E.3.1 PASSED" << endl ;

    // test dynamic dispatch of all the polymorphic methods
    if ( d1.GetName() == "Blind" )
        cout << "   TEST CASE E.4.1 PASSED" << endl ;
    
    if ( d1.GetConcessionFactor(BookingClass::ACFirstClass::Type()) == 0.50 )
        cout << "   TEST CASE E.4.2.1 PASSED" << endl ;
    
    if ( d1.GetConcessionFactor(BookingClass::FirstClass::Type()) == 0.75 )
        cout << "   TEST CASE E.4.2.2 PASSED" << endl ;

}