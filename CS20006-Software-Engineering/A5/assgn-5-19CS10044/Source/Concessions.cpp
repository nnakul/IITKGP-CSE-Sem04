
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include "Concessions.h"
#include "BookingCategory.h"
#include "Exceptions.h"
using namespace std ;

// initialize all the static data members based on the
// master data given in the specifications
const double GeneralConcession::sConcessionFactor = 0.00 ;  // no concession for General
const double LadiesConcession::sConcessionFactorMales = 0.00 ;  // no concession for Ladies -- neither for Males
const double LadiesConcession::sConcessionFactorFemales = 0.00 ; // nor for Females
const double SeniorCitizenConcession::sConcessionFactorMales = 0.40 ;
const double SeniorCitizenConcession::sConcessionFactorFemales = 0.50 ;

double GeneralConcession::GetConcessionFactor ( )
{ return GeneralConcession::sConcessionFactor ; }   // simply return the value of GeneralConcession::sConcessionFactor

double LadiesConcession::GetConcessionFactor ( const Passenger & p )
{   
    // first of all check if the Passenger passed as arguement is even elligible for
    // Ladies booking category. Use 'BookingCategory::Ladies::IsElligible' method.
    if ( ! BookingCategory::Ladies::Type().IsElligible(p, Date::CreateDate()) ) // if not elligible
        throw Bad_Elligibility("Passenger is not elligible for Ladies booking category") ;  // throw an exception
    // otherwise check the gender of 'p' and return the value of 
    // appropriate static data member
    if ( Gender::IsMale(p.GetGender()) )
        return LadiesConcession::sConcessionFactorMales ;
    return LadiesConcession::sConcessionFactorFemales ;
}

double SeniorCitizenConcession::GetConcessionFactor ( const Passenger & p )
{   
    // first of all check if the Passenger passed as arguement is even elligible for
    // SeniorCitizen booking category. Use 'BookingCategory::SeniorCitizen::IsElligible' method.
    if ( ! BookingCategory::SeniorCitizen::Type().IsElligible(p, Date::CreateDate()) ) // if not elligible
        throw Bad_Elligibility("Passenger is not elligible for SeniorCitizen booking category") ;  // throw an exception
    // otherwise check the gender of 'p' and return the value of 
    // appropriate static data member
    if ( Gender::IsMale(p.GetGender()) )
        return SeniorCitizenConcession::sConcessionFactorMales ;
    return SeniorCitizenConcession::sConcessionFactorFemales ;
}

double DivyaangConcession::GetConcessionFactor ( const Passenger & p , const BookingClass & b )
{   
    // first of all check if the Passenger passed as arguement is even elligible for
    // Divyaang booking category. Use 'BookingCategory::Divyaang::IsElligible' method.
    if ( ! BookingCategory::Divyaang::Type().IsElligible(p, Date::CreateDate()) ) // if not elligible
        throw Bad_Elligibility("Passenger is not elligible for Divyaang booking category") ;  // throw an exception
    double concession = 0.00 ;
    try // use DivyaangTypes<T>::GetConcessionFactor method to get the
        // concession factor for a particular Divyaang/diability type given
        // a BookingClass sub-type
    { concession = p.GetDisabilityType()->GetConcessionFactor(b) ; }    // this method is capable of throwing a Bad_Access
                                                                        // exception in case the BookingClass sub-type is
                                                                        // invalid.
    catch ( Bad_Access )    // if it happens, catch the exception and
    { throw ; }             // re-throw it
    return concession ; // otherwise return the concession factor
}

// In order to model the test case of checking the erroneous
// BookingClass type, an invalid BookingClass sub-type has to be introduced
// as given in the test plan document.
struct TestType { } ;    // placeholder for the invalid static sub-type
// give arbitrarily any values to the static data members for this invalid sub-type
template<>  const string BookingClassTypes<TestType>::sName = "Test" ;
template<>  const double BookingClassTypes<TestType>::sLoadFactor = false ;
template<>  const bool BookingClassTypes<TestType>::sIsSitting = false ;
template<>  const bool BookingClassTypes<TestType>::sIsAC = false ;
template<>  const bool BookingClassTypes<TestType>::sIsLuxury = 0 ;
template<>  const unsigned int BookingClassTypes<TestType>::sNumberOfTiers = 0 ;
template<>  const double BookingClassTypes<TestType>::sReservationCharge = 0.0 ;
template<>  const double BookingClassTypes<TestType>::sTatkalCharge = 0.0 ;
template<>  const double BookingClassTypes<TestType>::sMaxTatkalCharge = 0.0 ;
template<>  const double BookingClassTypes<TestType>::sMinTatkalCharge = 0.0 ;
template<>  const unsigned int BookingClassTypes<TestType>::sMinDistanceForTatkalCharge = 0 ;

// implementation of the Unit Test Plan for Concessions hierarchy
void Concessions::UnitTestConcessionsHierarchy ( )
{
    // test GeneralConcession::GetConcessionFactor
    // never throws an exception because anybody is elligible for General
    if ( GeneralConcession::GetConcessionFactor() == 0.00 )
        cout << "   TEST CASE F.1.1 PASSED" << endl ;

    // test LadiesConcession::GetConcessionFactor by passing an ineligible Passenger as arguement
    Passenger p1 = Passenger::CreatePassenger(Date::CreateDate("15/04/2006"), "Male", "123456789012", "John") ;
    try
    {   LadiesConcession::GetConcessionFactor(p1) ; }
    catch ( Bad_Elligibility )
    {   cout << "   TEST CASE F.1.2 PASSED" << endl ;  }
    
    // test LadiesConcession::GetConcessionFactor by passing an eligible Passenger as arguement --
    // exhaustively cover both the Gender sub-types
    Passenger p2 = Passenger::CreatePassenger(Date::CreateDate("15/04/2010"), "Male", "123456789012", "John") ;
    Passenger p3 = Passenger::CreatePassenger(Date::CreateDate("15/12/1990"), "Female", "123456789012", "Jane") ;
    if ( LadiesConcession::GetConcessionFactor(p2) == 0.00 )
        cout << "   TEST CASE F.1.3.1 PASSED" << endl ;
    if ( LadiesConcession::GetConcessionFactor(p3) == 0.00 )
        cout << "   TEST CASE F.1.3.2 PASSED" << endl ;

    // test SeniorCitizenConcession::GetConcessionFactor by passing an ineligible Passenger as arguement
    Passenger p4 = Passenger::CreatePassenger(Date::CreateDate("15/04/1963"), "Male", "123456789012", "John") ;
    try
    {   SeniorCitizenConcession::GetConcessionFactor(p4) ; }
    catch ( Bad_Elligibility )
    {   cout << "   TEST CASE F.1.4 PASSED" << endl ;  }
    
    // test SeniorCitizenConcession::GetConcessionFactor by passing an eligible Passenger as arguement --
    // exhaustively cover both the Gender sub-types
    Passenger p5 = Passenger::CreatePassenger(Date::CreateDate("15/04/1958"), "Male", "123456789012", "John") ;
    Passenger p6 = Passenger::CreatePassenger(Date::CreateDate("15/04/1961"), "Female", "123456789012", "Jane") ;
    if ( SeniorCitizenConcession::GetConcessionFactor(p5) == 0.40 )
        cout << "   TEST CASE F.1.5.1 PASSED" << endl ;
    if ( SeniorCitizenConcession::GetConcessionFactor(p6) == 0.50 )
        cout << "   TEST CASE F.1.5.2 PASSED" << endl ;

    // test DivyaangConcession::GetConcessionFactor by passing an ineligible Passenger (but a valid BookingClass sub-type) as arguement
    Passenger p7 = Passenger::CreatePassenger(Date::CreateDate("15/04/2020"), "Male", "123456789012", "John") ;
    try
    {   DivyaangConcession::GetConcessionFactor(p7, BookingClass::ACFirstClass::Type()) ; }
    catch ( Bad_Elligibility )
    {   cout << "   TEST CASE F.1.6 PASSED" << endl ;  }

    // test DivyaangConcession::GetConcessionFactor by passing an invalid BookingClass sub-type (but elligible Passenger) as arguement
    Passenger p8 = Passenger::CreatePassenger(Date::CreateDate("15/04/2020"), "Male", "123456789012", "John", "", "", "", &Divyaang::Blind::Type()) ;
    try
    {   DivyaangConcession::GetConcessionFactor(p8, BookingClassTypes<TestType>::Type()) ; }
    catch ( Bad_Access )
    {   cout << "   TEST CASE F.1.7 PASSED" << endl ;  }
    
    // test DivyaangConcession::GetConcessionFactor for correct arguement values
    // check for Blind Divyaang type and ACFirstClass BookingClass type -- match with golden output
    if ( DivyaangConcession::GetConcessionFactor(p8, BookingClass::ACFirstClass::Type()) == 0.50 )
        cout << "   TEST CASE F.1.8.1 PASSED" << endl ;

    // check again by changing the Divyaang sub-type -- match with golden output
    Passenger p9 = Passenger::CreatePassenger(Date::CreateDate("15/04/2020"), "Male", "123456789012", "John", "", "", "", &Divyaang::TBPatients::Type()) ;
    if ( DivyaangConcession::GetConcessionFactor(p9, BookingClass::ACFirstClass::Type()) == 0.00 )
        cout << "   TEST CASE F.1.8.2 PASSED" << endl ;
    
    // check again by changing the BookingClass sub-type -- match with golden output
    if ( DivyaangConcession::GetConcessionFactor(p8, BookingClass::FirstClass::Type()) == 0.75 )
        cout << "   TEST CASE F.1.8.3 PASSED" << endl ;

}

