
//  SOFTWARE ENGINEERING -- ASSIGNMENT O3
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include "BookingClass.h"
using namespace std ;

// Destructors of the Abstract Base Classes
// no explicit memory management needed 
// no dynamically allocated memory for any data member -- hence empty body
BookingClass::~BookingClass ( ) {   }
BookingClassSeat::~BookingClassSeat ( ) {   }
BookingClassSeatNoTier::~BookingClassSeatNoTier ( ) {   }
BookingClassBerth::~BookingClassBerth ( ) {  }
BookingClassBerthDoubleTier::~BookingClassBerthDoubleTier ( ) {  }
BookingClassBerthTripleTier::~BookingClassBerthTripleTier ( ) {  }

// in each of the "impure" virtual functions of the root
// class 'BookingClass', return values of appropriate data members
string BookingClass::GetName ( ) const
{   return name_ ;  }

double BookingClass::GetLoadFactor ( ) const
{   return loadFactor_ ;  }

bool BookingClass::IsLuxury ( ) const
{   return isLuxury_ ;  }

bool BookingClass::IsAC ( ) const
{   return isAC_ ;  }

// overload output streaming operator
ostream & operator << ( ostream & out , const BookingClass & bc )
{
    // print all the details of the booking class
    out << endl ;
    out << endl << "+++ DETAILS OF THE BOOKING CLASS +++" ;
    out << endl << "    - Name : " << bc.GetName() ;
    out << endl << "    - Load factor : " << bc.GetLoadFactor() ;
    out << endl << "    - No. of tiers : " << bc.GetNumberOfTiers() ;
    out << endl << "    - Is sitting : " << bc.IsSitting() ;
    out << endl << "    - Is AC : " << bc.IsAC() ;
    out << endl << "    - Is luxury : " << bc.IsLuxury() ;
    out << endl ;
    return out ;    // returning the 'ostream' object is important for streaming 
                    // of multiple references to the 'singleton' object chained 
                    // in the same instruction
}

// Initialize the static constant 'BookingClass::sLoadFactors' with the load factors of all
// concrete booking classes in the hierarchy.
// This makes it easy to analyse the load factors of various booking classes in the
// application. Since the static constant data members in the concrete booking classes
// that store their load factors are "encapsulated" (private), the only way to get an
// overall idea of load factors (without 'BookingClass::sLoadFactors') will be to 
// construct the singleton objects of all the 7 booking classes and then call the method
// 'BookingClass::GetLoadFactor' on each one them.
// With the following public data member, one can do various analytics (like how many 
// booking classes have load factor more than 1.5 or how many classes have a load factor 
// of 2 or what is the average load factor) on the client side.
const vector<double> BookingClass::sLoadFactors = {0.5, 1.0, 1.25, 1.75, 2.0, 2.0, 3.0} ;

void BookingClass::UnitTestBookingClass ( )
{
    cout << "\n\n   [ BookingClass::UnitTestBookingClass ( ) ]" << endl ;
    bool allPassed = true ;

    // Each of the 7 concrete booking classes is a specialization of 'BookingClass'
    // Store each one of them as a 'const' reference of 'BookingClass' to test dynamic binding.
    const BookingClass & polyB1 = BookingClassSeatNoTierAcOrdinary::SpecialBookingClass() ;
    const BookingClass & polyB2 = BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass() ;
    const BookingClass & polyB3 = BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass() ;
    const BookingClass & polyB4 = BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass() ;
    const BookingClass & polyB5 = BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass() ;
    const BookingClass & polyB6 = BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass() ;
    const BookingClass & polyB7 = BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass() ;

    // match the attributes of 'polyB1' with the real properties of the class 'BookingClassSeatNoTierAcOrdinary'
    if ( polyB1.loadFactor_ != 1.25 || polyB1.name_ != "AC Chair Car (CC)" || polyB1.remarks_ != "AC chairs" || polyB1.isLuxury_ || ! polyB1.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClass & polyB1'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassSeatNoTierAcOrdinary'
    if ( polyB1.GetLoadFactor() != 1.25 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClass & polyB1'" << endl ; allPassed = false ;  }
    if ( polyB1.GetName() != "AC Chair Car (CC)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClass & polyB1'" << endl ; allPassed = false ;  }
    if ( ! polyB1.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClass & polyB1'" << endl ; allPassed = false ;  }
    if ( ! polyB1.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClass & polyB1'" << endl ; allPassed = false ;  }
    if ( polyB1.GetNumberOfTiers() != 0 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClass & polyB1'" << endl ; allPassed = false ;  }
    if ( polyB1.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClass & polyB1'" << endl ; allPassed = false ;  }
    cout << polyB1 << endl ;

    // match the attributes of 'polyB2' with the real properties of the class 'BookingClassSeatNoTierNonAcOrdinary'
    if ( polyB2.loadFactor_ != 0.5 || polyB2.name_ != "Second Sitting (2S)" || polyB2.remarks_ != "Bench seating" || polyB2.isLuxury_ || polyB2.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClass & polyB2'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassSeatNoTierNonAcOrdinary'
    if ( polyB2.GetLoadFactor() != 0.5 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClass & polyB2'" << endl ; allPassed = false ;  }
    if ( polyB2.GetName() != "Second Sitting (2S)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClass & polyB2'" << endl ; allPassed = false ;  }
    if ( polyB2.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClass & polyB2'" << endl ; allPassed = false ;  }
    if ( ! polyB2.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClass & polyB2'" << endl ; allPassed = false ;  }
    if ( polyB2.GetNumberOfTiers() != 0 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClass & polyB2'" << endl ; allPassed = false ;  }
    if ( polyB2.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClass & polyB2'" << endl ; allPassed = false ;  }
    cout << polyB2 << endl ;

    // match the attributes of 'polyB3' with the real properties of the class 'BookingClassBerthDoubleTierAcLuxury'
    if ( polyB3.loadFactor_ != 3.0 || polyB3.name_ != "AC First Class (1A)" || polyB3.remarks_ != "AC 2 berth coupe" || ! polyB3.isLuxury_ || ! polyB3.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClass & polyB3'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthDoubleTierAcLuxury'
    if ( polyB3.GetLoadFactor() != 3.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClass & polyB3'" << endl ; allPassed = false ;  }
    if ( polyB3.GetName() != "AC First Class (1A)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClass & polyB3'" << endl ; allPassed = false ;  }
    if ( ! polyB3.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClass & polyB3'" << endl ; allPassed = false ;  }
    if ( polyB3.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClass & polyB3'" << endl ; allPassed = false ;  }
    if ( polyB3.GetNumberOfTiers() != 2 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClass & polyB3'" << endl ; allPassed = false ;  }
    if ( ! polyB3.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClass & polyB3'" << endl ; allPassed = false ;  }
    cout << polyB3 << endl ;

    // match the attributes of 'polyB4' with the real properties of the class 'BookingClassBerthDoubleTierNonAcLuxury'
    if ( polyB4.loadFactor_ != 2.0 || polyB4.name_ != "First Class (FC)" || polyB4.remarks_ != "Non-AC 2 berth coupe" || ! polyB4.isLuxury_ || polyB4.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClass & polyB4'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthDoubleTierNonAcLuxury'
    if ( polyB4.GetLoadFactor() != 2.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClass & polyB4'" << endl ; allPassed = false ;  }
    if ( polyB4.GetName() != "First Class (FC)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClass & polyB4'" << endl ; allPassed = false ;  }
    if ( polyB4.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClass & polyB4'" << endl ; allPassed = false ;  }
    if ( polyB4.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClass & polyB4'" << endl ; allPassed = false ;  }
    if ( polyB4.GetNumberOfTiers() != 2 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClass & polyB4'" << endl ; allPassed = false ;  }
    if ( ! polyB4.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClass & polyB4'" << endl ; allPassed = false ;  }
    cout << polyB4 << endl ;

    // match the attributes of 'polyB5' with the real properties of the class 'BookingClassBerthDoubleTierAcOrdinary'
    if ( polyB5.loadFactor_ != 2.0 || polyB5.name_ != "AC 2 Tier (2A)" || polyB5.remarks_ != "AC 2 berth inside, 2 berth on side" || polyB5.isLuxury_ || ! polyB5.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClass & polyB5'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthDoubleTierAcOrdinary'
    if ( polyB5.GetLoadFactor() != 2.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClass & polyB5'" << endl ; allPassed = false ;  }
    if ( polyB5.GetName() != "AC 2 Tier (2A)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClass & polyB5'" << endl ; allPassed = false ;  }
    if ( ! polyB5.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClass & polyB5'" << endl ; allPassed = false ;  }
    if ( polyB5.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClass & polyB5'" << endl ; allPassed = false ;  }
    if ( polyB5.GetNumberOfTiers() != 2 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClass & polyB5'" << endl ; allPassed = false ;  }
    if ( polyB5.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClass & polyB5'" << endl ; allPassed = false ;  }
    cout << polyB5 << endl ;

    // match the attributes of 'polyB6' with the real properties of the class 'BookingClassBerthTripleTierAcOrdinary'
    if ( polyB6.loadFactor_ != 1.75 || polyB6.name_ != "AC 3 Tier (3A)" || polyB6.remarks_ != "AC 3 berth inside, 2 berth onside" || polyB6.isLuxury_ || ! polyB6.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClass & polyB6'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthTripleTierAcOrdinary'
    if ( polyB6.GetLoadFactor() != 1.75 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClass & polyB6'" << endl ; allPassed = false ;  }
    if ( polyB6.GetName() != "AC 3 Tier (3A)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClass & polyB6'" << endl ; allPassed = false ;  }
    if ( ! polyB6.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClass & polyB6'" << endl ; allPassed = false ;  }
    if ( polyB6.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClass & polyB6'" << endl ; allPassed = false ;  }
    if ( polyB6.GetNumberOfTiers() != 3 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClass & polyB6'" << endl ; allPassed = false ;  }
    if ( polyB6.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClass & polyB6'" << endl ; allPassed = false ;  }
    cout << polyB6 << endl ;

    // match the attributes of 'polyB7' with the real properties of the class 'BookingClassBerthTripleTierNonAcOrdinary'
    if ( polyB7.loadFactor_ != 1.0 || polyB7.name_ != "Sleeper (SL)" || polyB7.remarks_ != "Non-AC 3 berth inside, 2 berth onside" || polyB7.isLuxury_ || polyB7.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClass & polyB7'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthTripleTierNonAcOrdinary'
    if ( polyB7.GetLoadFactor() != 1.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClass & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.GetName() != "Sleeper (SL)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClass & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClass & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClass & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.GetNumberOfTiers() != 3 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClass & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClass & polyB7'" << endl ; allPassed = false ;  }
    cout << polyB7 << endl ;

    // check if the static constant data member -- 'BookingClass::sLoadFactors' was correctly initialized
    // check the size of 'BookingClass::sLoadFactors' and also value of element at each and every index from 0 to 7
    if ( sLoadFactors.size() != 7 || sLoadFactors.at(0) != 0.5 || sLoadFactors.at(1) != 1.0 || sLoadFactors.at(2) != 1.25 ||
         sLoadFactors.at(3) != 1.75 || sLoadFactors.at(4) != 2.0 || sLoadFactors.at(5) != 2.0 || sLoadFactors.at(6) != 3.0  )
    { cout << "Static data member 'BookingClass::sLoadFactors' was not correctly initialized" << endl ; allPassed = false ;   }

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;      // to indicate that all tests have passed

}

bool BookingClassSeat::IsSitting ( ) const
{   return true ;   }   // overriding 'BookingClass::IsSitting'

void BookingClassSeat::UnitTestSeat ( )
{
    cout << "\n\n   [ BookingClassSeat::UnitTestSeat ( ) ]" << endl ;
    bool allPassed = true ;

    // Only 2 of the concrete booking classes are a specialization of 'BookingClassSeat'
    // Store each one of them as a 'const' reference of 'BookingClassSeat' to test dynamic binding.
    const BookingClassSeat & polyB1 = BookingClassSeatNoTierAcOrdinary::SpecialBookingClass() ;
    const BookingClassSeat & polyB2 = BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass() ;

    // match the attributes of 'polyB1' with the real properties of the class 'BookingClassSeatNoTierAcOrdinary'
    if ( polyB1.loadFactor_ != 1.25 || polyB1.name_ != "AC Chair Car (CC)" || polyB1.remarks_ != "AC chairs" || polyB1.isLuxury_ || ! polyB1.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassSeat & polyB1'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassSeatNoTierAcOrdinary'
    if ( polyB1.GetLoadFactor() != 1.25 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassSeat & polyB1'" << endl ; allPassed = false ;  }
    if ( polyB1.GetName() != "AC Chair Car (CC)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassSeat & polyB1'" << endl ; allPassed = false ;  }
    if ( ! polyB1.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassSeat & polyB1'" << endl ; allPassed = false ;  }
    if ( ! polyB1.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassSeat & polyB1'" << endl ; allPassed = false ;  }
    if ( polyB1.GetNumberOfTiers() != 0 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassSeat & polyB1'" << endl ; allPassed = false ;  }
    if ( polyB1.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassSeat & polyB1'" << endl ; allPassed = false ;  }
    cout << polyB1 << endl ;

    // match the attributes of 'polyB2' with the real properties of the class 'BookingClassSeatNoTierNonAcOrdinary'
    if ( polyB2.loadFactor_ != 0.5 || polyB2.name_ != "Second Sitting (2S)" || polyB2.remarks_ != "Bench seating" || polyB2.isLuxury_ || polyB2.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassSeat & polyB2'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassSeatNoTierNonAcOrdinary'
    if ( polyB2.GetLoadFactor() != 0.5 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassSeat & polyB2'" << endl ; allPassed = false ;  }
    if ( polyB2.GetName() != "Second Sitting (2S)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassSeat & polyB2'" << endl ; allPassed = false ;  }
    if ( polyB2.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassSeat & polyB2'" << endl ; allPassed = false ;  }
    if ( ! polyB2.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassSeat & polyB2'" << endl ; allPassed = false ;  }
    if ( polyB2.GetNumberOfTiers() != 0 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassSeat & polyB2'" << endl ; allPassed = false ;  }
    if ( polyB2.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassSeat & polyB2'" << endl ; allPassed = false ;  }
    cout << polyB2 << endl ;

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;      // to indicate that all tests have passed

}

int BookingClassSeatNoTier::GetNumberOfTiers ( ) const
{   return 0 ;  }   // overriding 'BookingClass::GetNumberOfTiers'

void BookingClassSeatNoTier::UnitTestSeatNoTier ( )
{
    cout << "\n\n   [ BookingClassSeatNoTier::UnitTestSeatNoTier ( ) ]" << endl ;
    bool allPassed = true ;

    // Only 2 of the concrete booking classes are a specialization of 'BookingClassSeatNoTier'
    // Store each one of them as a 'const' reference of 'BookingClassSeatNoTier' to test dynamic binding.
    const BookingClassSeatNoTier & polyB1 = BookingClassSeatNoTierAcOrdinary::SpecialBookingClass() ;
    const BookingClassSeatNoTier & polyB2 = BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass() ;

    // match the attributes of 'polyB1' with the real properties of the class 'BookingClassSeatNoTierAcOrdinary'
    if ( polyB1.loadFactor_ != 1.25 || polyB1.name_ != "AC Chair Car (CC)" || polyB1.remarks_ != "AC chairs" || polyB1.isLuxury_ || ! polyB1.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassSeatNoTier & polyB1'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassSeatNoTierAcOrdinary'
    if ( polyB1.GetLoadFactor() != 1.25 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassSeatNoTier & polyB1'" << endl ; allPassed = false ;  }
    if ( polyB1.GetName() != "AC Chair Car (CC)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassSeatNoTier & polyB1'" << endl ; allPassed = false ;  }
    if ( ! polyB1.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassSeatNoTier & polyB1'" << endl ; allPassed = false ;  }
    if ( ! polyB1.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassSeatNoTier & polyB1'" << endl ; allPassed = false ;  }
    if ( polyB1.GetNumberOfTiers() != 0 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassSeatNoTier & polyB1'" << endl ; allPassed = false ;  }
    if ( polyB1.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassSeatNoTier & polyB1'" << endl ; allPassed = false ;  }
    cout << polyB1 << endl ;

    // match the attributes of 'polyB2' with the real properties of the class 'BookingClassSeatNoTierNonAcOrdinary'
    if ( polyB2.loadFactor_ != 0.5 || polyB2.name_ != "Second Sitting (2S)" || polyB2.remarks_ != "Bench seating" || polyB2.isLuxury_ || polyB2.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassSeatNoTier & polyB2'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassSeatNoTierNonAcOrdinary'
    if ( polyB2.GetLoadFactor() != 0.5 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassSeatNoTier & polyB2'" << endl ; allPassed = false ;  }
    if ( polyB2.GetName() != "Second Sitting (2S)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassSeatNoTier & polyB2'" << endl ; allPassed = false ;  }
    if ( polyB2.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassSeatNoTier & polyB2'" << endl ; allPassed = false ;  }
    if ( ! polyB2.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassSeatNoTier & polyB2'" << endl ; allPassed = false ;  }
    if ( polyB2.GetNumberOfTiers() != 0 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassSeatNoTier & polyB2'" << endl ; allPassed = false ;  }
    if ( polyB2.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassSeatNoTier & polyB2'" << endl ; allPassed = false ;  }
    cout << polyB2 << endl ;

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef BookingClassSeatNoTierAcOrdinary BCSNTAO ; 
const double BCSNTAO::sLoadFactor = 1.25 ;      // initialize the load factor for this booking class

BCSNTAO::BookingClassSeatNoTierAcOrdinary ( const string & name , const string & remarks )  // constructor
{   remarks_ = remarks ; name_ = name ; loadFactor_ = sLoadFactor ; isLuxury_ = false ; isAC_ = true ;    }

const BCSNTAO & BCSNTAO::SpecialBookingClass ( const string & name , const string & remarks )
{
    static BCSNTAO sSpecialBookingClass(name, remarks) ;   // "Meyer's Implementation of a Singleton Class"
    // static locals are declared only once; its lifetime starts when the 
    // function is called and ends only when the program ends. Therefore,
    // the constructor is called only once and that happens when this function
    // is called for the first time

    return sSpecialBookingClass ; // always return the singleton instance as a 'const' reference of 'BookingClassSeatNoTierAcOrdinary'
}

BCSNTAO::~BookingClassSeatNoTierAcOrdinary ( )  {   }     // no explicit memory management needed -- no dynamically 
                                                          // allocated memory for any data member -- hence empty body   

void BCSNTAO::UnitTestSeatNoTierAcOrdinary ( )
{
    cout << "\n\n   [ BookingClassSeatNoTierAcOrdinary::UnitTestSeatNoTierAcOrdinary ( ) ]" << endl ;
    bool allPassed = true ;

    // TEST 1 : check if the static constant 'BCSNTAO::sLoadFactor' was initialized correctly
    if ( BCSNTAO::sLoadFactor != 1.25 )
    { cout << "'BookingClassSeatNoTierAcOrdinary::sLoadFactor' is not initialized the intended value" << endl ; allPassed = false ;  }
    
    // TEST 2 : Construction of singleton instance with default parameters
    // first call to 'BCSNTAO::SpecialBookingClass'
    const BCSNTAO & b1 = BCSNTAO::SpecialBookingClass() ;
    // check all the data members of the returned instance and match them with actual properties of the booking class
    if ( b1.loadFactor_ != 1.25 || b1.name_ != "AC Chair Car (CC)" || b1.remarks_ != "AC chairs" || b1.isLuxury_ || ! b1.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassSeatNoTierAcOrdinary & b1'" << endl ; allPassed = false ;  }

    // TEST 3 : Call 'BCSNTAO::SpecialBookingClass' once again with no parameters
    const BCSNTAO & b2 = BCSNTAO::SpecialBookingClass() ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b2.loadFactor_ != 1.25 || b2.name_ != "AC Chair Car (CC)" || b2.remarks_ != "AC chairs" || b2.isLuxury_ || ! b2.isAC_ )
    { cout << "Repeated call 'BookingClassSeatNoTierAcOrdinary::SpecialBookingClass()' returns an object 'const BookingClassSeatNoTierAcOrdinary & b2' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b2 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the default parameters should not have been constructed
    { cout << "'BookingClassSeatNoTierAcOrdinary' is not a singleton class because it returns a new instance on repeating call 'BookingClassSeatNoTierAcOrdinary::SpecialBookingClass()'" << endl ; allPassed = false ;  }

    // TEST 4 : Call 'BCSNTAO::SpecialBookingClass' once again with arbitrary parameters
    const BCSNTAO & b3 = BCSNTAO::SpecialBookingClass("My Booking Class", "No Remarks") ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b3.loadFactor_ != 1.25 || b3.name_ != "AC Chair Car (CC)" || b3.remarks_ != "AC chairs" || b3.isLuxury_ || ! b3.isAC_ )
    { cout << "Call with parameters 'BookingClassSeatNoTierAcOrdinary::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")' returns an object 'const BookingClassSeatNoTierAcOrdinary & b3' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b3 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the passed parameters should not have been constructed
    { cout << "'BookingClassSeatNoTierAcOrdinary' is not a singleton class because it returns a new instance on calling 'BookingClassSeatNoTierAcOrdinary::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")'" << endl ; allPassed = false ;  }

    // TEST 5 : Test accuracy of the values returned by the various methods and match them
    // with the actual properties of this booking class
    if ( b1.GetLoadFactor() != 1.25 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassSeatNoTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetName() != "AC Chair Car (CC)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassSeatNoTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( ! b1.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassSeatNoTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( ! b1.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassSeatNoTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetNumberOfTiers() != 0 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassSeatNoTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassSeatNoTierAcOrdinary & b1'" << endl ; allPassed = false ;  }

    // TEST 6 : Check overloaded output streaming operator
    cout << b1 ;    // stream a single reference to the singleton object
    cout << b2 << b3 << endl ; // stream a chain of references to the singleton object

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef BookingClassSeatNoTierNonAcOrdinary BCSNTNO ;
const double BCSNTNO::sLoadFactor = 0.50 ;      // initialize the load factor for this booking class

BCSNTNO::BookingClassSeatNoTierNonAcOrdinary ( const string & name , const string & remarks ) // constructor
{   remarks_ = remarks ; name_ = name ; loadFactor_ = sLoadFactor ; isLuxury_ = false ; isAC_ = false ;   }

const BCSNTNO & BCSNTNO::SpecialBookingClass ( const string & name , const string & remarks )
{
    static BCSNTNO sSpecialBookingClass(name, remarks) ;   // "Meyer's Implementation of a Singleton Class"
    // static locals are declared only once; its lifetime starts when the 
    // function is called and ends only when the program ends. Therefore,
    // the constructor is called only once and that happens when this function
    // is called for the first time

    return sSpecialBookingClass ; // always return the singleton instance as a 'const' reference of 'BookingClassSeatNoTierNonAcOrdinary'
}

BCSNTNO::~BookingClassSeatNoTierNonAcOrdinary ( )  {   }     // no explicit memory management needed -- no dynamically 
                                                             // allocated memory for any data member -- hence empty body

void BCSNTNO::UnitTestSeatNoTierNonAcOrdinary ( )
{
    cout << "\n\n   [ BookingClassSeatNoTierNonAcOrdinary::UnitTestSeatNoTierNonAcOrdinary ( ) ]" << endl ;
    bool allPassed = true ;

    // TEST 1 : check if the static constant 'BCSNTNO::sLoadFactor' was initialized correctly
    if ( BCSNTNO::sLoadFactor != 0.5 )
    { cout << "'BookingClassSeatNoTierNonAcOrdinary::sLoadFactor' is not initialized the intended value" << endl ; allPassed = false ;  }
    
    // TEST 2 : Construction of singleton instance with default parameters
    // first call to 'BCSNTNO::SpecialBookingClass'
    const BCSNTNO & b1 = BCSNTNO::SpecialBookingClass() ;
    // check all the data members of the returned instance and match them with actual properties of the booking class
    if ( b1.loadFactor_ != 0.5 || b1.name_ != "Second Sitting (2S)" || b1.remarks_ != "Bench seating" || b1.isLuxury_ || b1.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassSeatNoTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }

    // TEST 3 : Call 'BCSNTNO::SpecialBookingClass' once again with no parameters
    const BCSNTNO & b2 = BCSNTNO::SpecialBookingClass() ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b2.loadFactor_ != 0.5 || b2.name_ != "Second Sitting (2S)" || b2.remarks_ != "Bench seating" || b2.isLuxury_ || b2.isAC_ )
    { cout << "Repeated call 'BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass()' returns an object 'const BookingClassSeatNoTierNonAcOrdinary & b2' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b2 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the default parameters should not have been constructed
    { cout << "'BookingClassSeatNoTierNonAcOrdinary' is not a singleton class because it returns a new instance on repeating call 'BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass()'" << endl ; allPassed = false ;  }

    // TEST 4 : Call 'BCSNTNO::SpecialBookingClass' once again with arbitrary parameters
    const BCSNTNO & b3 = BCSNTNO::SpecialBookingClass("My Booking Class", "No Remarks") ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b3.loadFactor_ != 0.5 || b3.name_ != "Second Sitting (2S)" || b3.remarks_ != "Bench seating" || b3.isLuxury_ || b3.isAC_ )
    { cout << "Call with parameters 'BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")' returns an object 'const BookingClassSeatNoTierNonAcOrdinary & b3' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b3 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the passed parameters should not have been constructed
    { cout << "'BookingClassSeatNoTierNonAcOrdinary' is not a singleton class because it returns a new instance on calling 'BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")'" << endl ; allPassed = false ;  }

    // TEST 5 : Test accuracy of the values returned by the various methods and match them
    // with the actual properties of this booking class
    if ( b1.GetLoadFactor() != 0.5 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassSeatNoTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetName() != "Second Sitting (2S)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassSeatNoTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassSeatNoTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( ! b1.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassSeatNoTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetNumberOfTiers() != 0 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassSeatNoTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassSeatNoTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }

    // TEST 6 : Check overloaded output streaming operator
    cout << b1 ;    // stream a single reference to the singleton object
    cout << b2 << b3 << endl ; // stream a chain of references to the singleton object

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool BookingClassBerth::IsSitting ( ) const
{   return false ;   }  // overriding 'BookingClass::IsSitting'

void BookingClassBerth::UnitTestBerth ( )
{
    cout << "\n\n   [ BookingClassBerth::UnitTestBerth ( ) ]" << endl ;
    bool allPassed = true ;

    // Only 5 of the concrete booking classes are a specialization of 'BookingClassBerth'
    // Store each one of them as a 'const' reference of 'BookingClassBerth' to test dynamic binding.
    const BookingClassBerth & polyB3 = BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass() ;
    const BookingClassBerth & polyB4 = BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass() ;
    const BookingClassBerth & polyB5 = BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass() ;
    const BookingClassBerth & polyB6 = BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass() ;
    const BookingClassBerth & polyB7 = BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass() ;

    // match the attributes of 'polyB3' with the real properties of the class 'BookingClassBerthDoubleTierAcLuxury'
    if ( polyB3.loadFactor_ != 3.0 || polyB3.name_ != "AC First Class (1A)" || polyB3.remarks_ != "AC 2 berth coupe" || ! polyB3.isLuxury_ || ! polyB3.isAC_  )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerth & polyB3'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthDoubleTierAcLuxury'
    if ( polyB3.GetLoadFactor() != 3.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerth & polyB3'" << endl ; allPassed = false ;  }
    if ( polyB3.GetName() != "AC First Class (1A)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerth & polyB3'" << endl ; allPassed = false ;  }
    if ( ! polyB3.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerth & polyB3'" << endl ; allPassed = false ;  }
    if ( polyB3.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerth & polyB3'" << endl ; allPassed = false ;  }
    if ( polyB3.GetNumberOfTiers() != 2 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerth & polyB3'" << endl ; allPassed = false ;  }
    if ( ! polyB3.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerth & polyB3'" << endl ; allPassed = false ;  }
    cout << polyB3 << endl ;

    // match the attributes of 'polyB4' with the real properties of the class 'BookingClassBerthDoubleTierNonAcLuxury'
    if ( polyB4.loadFactor_ != 2.0 || polyB4.name_ != "First Class (FC)" || polyB4.remarks_ != "Non-AC 2 berth coupe" || ! polyB4.isLuxury_ || polyB4.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerth & polyB4'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthDoubleTierNonAcLuxury'
    if ( polyB4.GetLoadFactor() != 2.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerth & polyB4'" << endl ; allPassed = false ;  }
    if ( polyB4.GetName() != "First Class (FC)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerth & polyB4'" << endl ; allPassed = false ;  }
    if ( polyB4.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerth & polyB4'" << endl ; allPassed = false ;  }
    if ( polyB4.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerth & polyB4'" << endl ; allPassed = false ;  }
    if ( polyB4.GetNumberOfTiers() != 2 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerth & polyB4'" << endl ; allPassed = false ;  }
    if ( ! polyB4.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerth & polyB4'" << endl ; allPassed = false ;  }
    cout << polyB4 << endl ;

    // match the attributes of 'polyB5' with the real properties of the class 'BookingClassBerthDoubleTierAcOrdinary'
    if ( polyB5.loadFactor_ != 2.0 || polyB5.name_ != "AC 2 Tier (2A)" || polyB5.remarks_ != "AC 2 berth inside, 2 berth on side" || polyB5.isLuxury_ || ! polyB5.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerth & polyB5'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthDoubleTierAcOrdinary'
    if ( polyB5.GetLoadFactor() != 2.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerth & polyB5'" << endl ; allPassed = false ;  }
    if ( polyB5.GetName() != "AC 2 Tier (2A)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerth & polyB5'" << endl ; allPassed = false ;  }
    if ( ! polyB5.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerth & polyB5'" << endl ; allPassed = false ;  }
    if ( polyB5.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerth & polyB5'" << endl ; allPassed = false ;  }
    if ( polyB5.GetNumberOfTiers() != 2 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerth & polyB5'" << endl ; allPassed = false ;  }
    if ( polyB5.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerth & polyB5'" << endl ; allPassed = false ;  }
    cout << polyB5 << endl ;

    // match the attributes of 'polyB6' with the real properties of the class 'BookingClassBerthTripleTierAcOrdinary'
    if ( polyB6.loadFactor_ != 1.75 || polyB6.name_ != "AC 3 Tier (3A)" || polyB6.remarks_ != "AC 3 berth inside, 2 berth onside" || polyB6.isLuxury_ || ! polyB6.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerth & polyB6'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthTripleTierAcOrdinary'
    if ( polyB6.GetLoadFactor() != 1.75 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerth & polyB6'" << endl ; allPassed = false ;  }
    if ( polyB6.GetName() != "AC 3 Tier (3A)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerth & polyB6'" << endl ; allPassed = false ;  }
    if ( ! polyB6.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerth & polyB6'" << endl ; allPassed = false ;  }
    if ( polyB6.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerth & polyB6'" << endl ; allPassed = false ;  }
    if ( polyB6.GetNumberOfTiers() != 3 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerth & polyB6'" << endl ; allPassed = false ;  }
    if ( polyB6.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerth & polyB6'" << endl ; allPassed = false ;  }
    cout << polyB6 << endl ;

    // match the attributes of 'polyB7' with the real properties of the class 'BookingClassBerthTripleTierNonAcOrdinary'
    if ( polyB7.loadFactor_ != 1.0 || polyB7.name_ != "Sleeper (SL)" || polyB7.remarks_ != "Non-AC 3 berth inside, 2 berth onside" || polyB7.isLuxury_ || polyB7.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerth & polyB7'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthTripleTierNonAcOrdinary'
    if ( polyB7.GetLoadFactor() != 1.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerth & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.GetName() != "Sleeper (SL)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerth & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerth & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerth & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.GetNumberOfTiers() != 3 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerth & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerth & polyB7'" << endl ; allPassed = false ;  }
    cout << polyB7 << endl ;

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed

}

int BookingClassBerthDoubleTier::GetNumberOfTiers ( ) const
{   return 2 ;  }   // overriding 'BookingClass::GetNumberOfTiers'

void BookingClassBerthDoubleTier::UnitTestBerthDoubleTier ( )
{
    cout << "\n\n   [ BookingClassBerthDoubleTier::UnitTestBerthDoubleTier ( ) ]" << endl ;
    bool allPassed = true ;

    // Only 3 of the concrete booking classes are a specialization of 'BookingClassBerthDoubleTier'
    // Store each one of them as a 'const' reference of 'BookingClassBerthDoubleTier' to test dynamic binding.
    const BookingClassBerthDoubleTier & polyB3 = BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass() ;
    const BookingClassBerthDoubleTier & polyB4 = BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass() ;
    const BookingClassBerthDoubleTier & polyB5 = BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass() ;

    // match the attributes of 'polyB3' with the real properties of the class 'BookingClassBerthDoubleTierAcLuxury'
    if ( polyB3.loadFactor_ != 3.0 || polyB3.name_ != "AC First Class (1A)" || polyB3.remarks_ != "AC 2 berth coupe" || ! polyB3.isLuxury_ || ! polyB3.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerthDoubleTier & polyB3'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthDoubleTierAcLuxury'
    if ( polyB3.GetLoadFactor() != 3.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB3'" << endl ; allPassed = false ;  }
    if ( polyB3.GetName() != "AC First Class (1A)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB3'" << endl ; allPassed = false ;  }
    if ( ! polyB3.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB3'" << endl ; allPassed = false ;  }
    if ( polyB3.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB3'" << endl ; allPassed = false ;  }
    if ( polyB3.GetNumberOfTiers() != 2 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB3'" << endl ; allPassed = false ;  }
    if ( ! polyB3.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB3'" << endl ; allPassed = false ;  }
    cout << polyB3 << endl ;

    // match the attributes of 'polyB4' with the real properties of the class 'BookingClassBerthDoubleTierNonAcLuxury'
    if ( polyB4.loadFactor_ != 2.0 || polyB4.name_ != "First Class (FC)" || polyB4.remarks_ != "Non-AC 2 berth coupe" || ! polyB4.isLuxury_ || polyB4.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerthDoubleTier & polyB4'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthDoubleTierNonAcLuxury'
    if ( polyB4.GetLoadFactor() != 2.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB4'" << endl ; allPassed = false ;  }
    if ( polyB4.GetName() != "First Class (FC)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB4'" << endl ; allPassed = false ;  }
    if ( polyB4.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB4'" << endl ; allPassed = false ;  }
    if ( polyB4.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB4'" << endl ; allPassed = false ;  }
    if ( polyB4.GetNumberOfTiers() != 2 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB4'" << endl ; allPassed = false ;  }
    if ( ! polyB4.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB4'" << endl ; allPassed = false ;  }
    cout << polyB4 << endl ;

    // match the attributes of 'polyB5' with the real properties of the class 'BookingClassBerthDoubleTierAcOrdinary'
    if ( polyB5.loadFactor_ != 2.0 || polyB5.name_ != "AC 2 Tier (2A)" || polyB5.remarks_ != "AC 2 berth inside, 2 berth on side" || polyB5.isLuxury_ || ! polyB5.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerthDoubleTier & polyB5'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthDoubleTierAcOrdinary'
    if ( polyB5.GetLoadFactor() != 2.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB5'" << endl ; allPassed = false ;  }
    if ( polyB5.GetName() != "AC 2 Tier (2A)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB5'" << endl ; allPassed = false ;  }
    if ( ! polyB5.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB5'" << endl ; allPassed = false ;  }
    if ( polyB5.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB5'" << endl ; allPassed = false ;  }
    if ( polyB5.GetNumberOfTiers() != 2 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB5'" << endl ; allPassed = false ;  }
    if ( polyB5.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerthDoubleTier & polyB5'" << endl ; allPassed = false ;  }
    cout << polyB5 << endl ;

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed

}

int BookingClassBerthTripleTier::GetNumberOfTiers ( ) const
{   return 3 ;  }   // overriding 'BookingClass::GetNumberOfTiers'

void BookingClassBerthTripleTier::UnitTestBerthTripleTier ( )
{

    cout << "\n\n   [ BookingClassBerthTripleTier::UnitTestBerthTripleTier ( ) ]" << endl ;
    bool allPassed = true ;

    // Only 2 of the concrete booking classes are a specialization of 'BookingClassBerthTripleTier'
    // Store each one of them as a 'const' reference of 'BookingClassBerthTripleTier' to test dynamic binding.
    const BookingClassBerthTripleTier & polyB6 = BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass() ;
    const BookingClassBerthTripleTier & polyB7 = BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass() ;

    // match the attributes of 'polyB6' with the real properties of the class 'BookingClassBerthTripleTierAcOrdinary'
    if ( polyB6.loadFactor_ != 1.75 || polyB6.name_ != "AC 3 Tier (3A)" || polyB6.remarks_ != "AC 3 berth inside, 2 berth onside" || polyB6.isLuxury_ || ! polyB6.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerthTripleTier & polyB6'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthTripleTierAcOrdinary'
    if ( polyB6.GetLoadFactor() != 1.75 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerthTripleTier & polyB6'" << endl ; allPassed = false ;  }
    if ( polyB6.GetName() != "AC 3 Tier (3A)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerthTripleTier & polyB6'" << endl ; allPassed = false ;  }
    if ( ! polyB6.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerthTripleTier & polyB6'" << endl ; allPassed = false ;  }
    if ( polyB6.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerthTripleTier & polyB6'" << endl ; allPassed = false ;  }
    if ( polyB6.GetNumberOfTiers() != 3 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerthTripleTier & polyB6'" << endl ; allPassed = false ;  }
    if ( polyB6.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerthTripleTier & polyB6'" << endl ; allPassed = false ;  }
    cout << polyB6 << endl ;

    // match the attributes of 'polyB7' with the real properties of the class 'BookingClassBerthTripleTierNonAcOrdinary'
    if ( polyB7.loadFactor_ != 1.0 || polyB7.name_ != "Sleeper (SL)" || polyB7.remarks_ != "Non-AC 3 berth inside, 2 berth onside" || polyB7.isLuxury_ || polyB7.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerthTripleTier & polyB7'" << endl ; allPassed = false ;  }
    // check dynamic binding on each of the polymorphic methods and compare their values
    // with the real properties of the class 'BookingClassBerthTripleTierNonAcOrdinary'
    if ( polyB7.GetLoadFactor() != 1.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerthTripleTier & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.GetName() != "Sleeper (SL)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerthTripleTier & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerthTripleTier & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerthTripleTier & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.GetNumberOfTiers() != 3 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerthTripleTier & polyB7'" << endl ; allPassed = false ;  }
    if ( polyB7.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerthTripleTier & polyB7'" << endl ; allPassed = false ;  }
    cout << polyB7 << endl ;

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef BookingClassBerthDoubleTierAcLuxury BCBDTAL ; 
const double BCBDTAL::sLoadFactor = 3.00 ;      // initialize the load factor for this booking class

BCBDTAL::BookingClassBerthDoubleTierAcLuxury ( const string & name , const string & remarks )   // constructor
{   remarks_ = remarks ; name_ = name ; loadFactor_ = sLoadFactor ; isLuxury_ = true ; isAC_ = true ;   }

const BCBDTAL & BCBDTAL::SpecialBookingClass ( const string & name , const string & remarks )
{
    static BCBDTAL sSpecialBookingClass(name, remarks) ;   // "Meyer's Implementation of a Singleton Class"
    // static locals are declared only once; its lifetime starts when the 
    // function is called and ends only when the program ends. Therefore,
    // the constructor is called only once and that happens when this function
    // is called for the first time

    return sSpecialBookingClass ; // always return the singleton instance as a 'const' reference of 'BookingClassBerthDoubleTierAcLuxury'
}

BCBDTAL::~BookingClassBerthDoubleTierAcLuxury ( )   {   }     // no explicit memory management needed -- no dynamically 
                                                              // allocated memory for any data member -- hence empty body

void BCBDTAL::UnitTestBerthDoubleTierAcLuxury ( )
{
    cout << "\n\n   [ BookingClassBerthDoubleTierAcLuxury::UnitTestBerthDoubleTierAcLuxury ( ) ]" << endl ;
    bool allPassed = true ;

    // TEST 1 : check if the static constant 'BCBDTAL::sLoadFactor' was initialized correctly
    if ( BCBDTAL::sLoadFactor != 3.00 )
    { cout << "'BookingClassBerthDoubleTierAcLuxury::sLoadFactor' is not initialized the intended value" << endl ; allPassed = false ;  }
    
    // TEST 2 : Construction of singleton instance with default parameters
    // first call to 'BCBDTAL::SpecialBookingClass'
    const BCBDTAL & b1 = BCBDTAL::SpecialBookingClass() ;
    // check all the data members of the returned instance and match them with actual properties of the booking class
    if ( b1.loadFactor_ != 3.00 || b1.name_ != "AC First Class (1A)" || b1.remarks_ != "AC 2 berth coupe" || ! b1.isLuxury_ || ! b1.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerthDoubleTierAcLuxury & b1'" << endl ; allPassed = false ;  }

    // TEST 3 : Call 'BCBDTAL::SpecialBookingClass' once again with no parameters
    const BCBDTAL & b2 = BCBDTAL::SpecialBookingClass() ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b2.loadFactor_ != 3.00 || b2.name_ != "AC First Class (1A)" || b2.remarks_ != "AC 2 berth coupe" || ! b2.isLuxury_ || ! b2.isAC_ )
    { cout << "Repeated call 'BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass()' returns an object 'const BookingClassBerthDoubleTierAcLuxury & b2' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b2 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the default parameters should not have been constructed
    { cout << "'BookingClassBerthDoubleTierAcLuxury' is not a singleton class because it returns a new instance on repeating call 'BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass()'" << endl ; allPassed = false ;  }

    // TEST 4 : Call 'BCBDTAL::SpecialBookingClass' once again with arbitrary parameters
    const BCBDTAL & b3 = BCBDTAL::SpecialBookingClass("My Booking Class", "No Remarks") ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b3.loadFactor_ != 3.00 || b3.name_ != "AC First Class (1A)" || b3.remarks_ != "AC 2 berth coupe" || ! b3.isLuxury_ || ! b3.isAC_ )
    { cout << "Call with parameters 'BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")' returns an object 'const BookingClassBerthDoubleTierAcLuxury & b3' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b3 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the passed parameters should not have been constructed
    { cout << "'BookingClassBerthDoubleTierAcLuxury' is not a singleton class because it returns a new instance on calling 'BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")'" << endl ; allPassed = false ;  }

    // TEST 5 : Test accuracy of the values returned by the various methods and match them
    // with the actual properties of this booking class
    if ( b1.GetLoadFactor() != 3.00 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerthDoubleTierAcLuxury & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetName() != "AC First Class (1A)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerthDoubleTierAcLuxury & b1'" << endl ; allPassed = false ;  }
    if ( ! b1.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerthDoubleTierAcLuxury & b1'" << endl ; allPassed = false ;  }
    if ( b1.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerthDoubleTierAcLuxury & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetNumberOfTiers() != 2 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerthDoubleTierAcLuxury & b1'" << endl ; allPassed = false ;  }
    if ( ! b1.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerthDoubleTierAcLuxury & b1'" << endl ; allPassed = false ;  }

    // TEST 6 : Check overloaded output streaming operator
    cout << b1 ;    // stream a single reference to the singleton object
    cout << b2 << b3 << endl ; // stream a chain of references to the singleton object

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef BookingClassBerthDoubleTierAcOrdinary BCBDTAO ;
const double BCBDTAO::sLoadFactor = 2.00 ;      // initialize the load factor for this booking class

BCBDTAO::BookingClassBerthDoubleTierAcOrdinary ( const string & name , const string & remarks ) // constructor
{   remarks_ = remarks ; name_ = name ; loadFactor_ = sLoadFactor ; isLuxury_ = false ; isAC_ = true ;   }

const BCBDTAO & BCBDTAO::SpecialBookingClass ( const string & name , const string & remarks )
{
    static BCBDTAO sSpecialBookingClass(name, remarks) ;   // "Meyer's Implementation of a Singleton Class"
    // static locals are declared only once; its lifetime starts when the 
    // function is called and ends only when the program ends. Therefore,
    // the constructor is called only once and that happens when this function
    // is called for the first time

    return sSpecialBookingClass ; // always return the singleton instance as a 'const' reference of 'BookingClassBerthDoubleTierAcOrdinary'
}

BCBDTAO::~BookingClassBerthDoubleTierAcOrdinary ( ) {   }     // no explicit memory management needed -- no dynamically 
                                                              // allocated memory for any data member -- hence empty body

void BCBDTAO::UnitTestBerthDoubleTierAcOrdinary ( )
{
    cout << "\n\n   [ BookingClassBerthDoubleTierAcOrdinary::UnitTestBerthDoubleTierAcOrdinary ( ) ]" << endl ;
    bool allPassed = true ;

    // TEST 1 : check if the static constant 'BCBDTAO::sLoadFactor' was initialized correctly
    if ( BCBDTAO::sLoadFactor != 2.0 )
    { cout << "'BookingClassBerthDoubleTierAcOrdinary::sLoadFactor' is not initialized the intended value" << endl ; allPassed = false ;  }
    
    // TEST 2 : Construction of singleton instance with default parameters
    // first call to 'BCBDTAO::SpecialBookingClass'
    const BCBDTAO & b1 = BCBDTAO::SpecialBookingClass() ;
    // check all the data members of the returned instance and match them with actual properties of the booking class
    if ( b1.loadFactor_ != 2.0 || b1.name_ != "AC 2 Tier (2A)" || b1.remarks_ != "AC 2 berth inside, 2 berth on side" || b1.isLuxury_ || ! b1.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerthDoubleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }

    // TEST 3 : Call 'BCBDTAO::SpecialBookingClass' once again with no parameters
    const BCBDTAO & b2 = BCBDTAO::SpecialBookingClass() ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b2.loadFactor_ != 2.0 || b2.name_ != "AC 2 Tier (2A)" || b2.remarks_ != "AC 2 berth inside, 2 berth on side" || b2.isLuxury_ || ! b2.isAC_ )
    { cout << "Repeated call 'BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass()' returns an object 'const BookingClassBerthDoubleTierAcOrdinary & b2' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b2 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the default parameters should not have been constructed
    { cout << "'BookingClassBerthDoubleTierAcOrdinary' is not a singleton class because it returns a new instance on repeating call 'BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass()'" << endl ; allPassed = false ;  }

    // TEST 4 : Call 'BCBDTAO::SpecialBookingClass' once again with arbitrary parameters
    const BCBDTAO & b3 = BCBDTAO::SpecialBookingClass("My Booking Class", "No Remarks") ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b3.loadFactor_ != 2.0 || b3.name_ != "AC 2 Tier (2A)" || b3.remarks_ != "AC 2 berth inside, 2 berth on side" || b3.isLuxury_ || ! b3.isAC_ )
    { cout << "Call with parameters 'BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")' returns an object 'const BookingClassBerthDoubleTierAcOrdinary & b3' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b3 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the passed parameters should not have been constructed
    { cout << "'BookingClassBerthDoubleTierAcOrdinary' is not a singleton class because it returns a new instance on calling 'BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")'" << endl ; allPassed = false ;  }

    // TEST 5 : Test accuracy of the values returned by the various methods and match them
    // with the actual properties of this booking class
    if ( b1.GetLoadFactor() != 2.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerthDoubleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetName() != "AC 2 Tier (2A)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerthDoubleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( ! b1.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerthDoubleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerthDoubleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetNumberOfTiers() != 2 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerthDoubleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerthDoubleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }

    // TEST 6 : Check overloaded output streaming operator
    cout << b1 ;    // stream a single reference to the singleton object
    cout << b2 << b3 << endl ; // stream a chain of references to the singleton object

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef BookingClassBerthDoubleTierNonAcLuxury BCBDTNL ;
const double BCBDTNL::sLoadFactor = 2.00 ;      // initialize the load factor for this booking class

BCBDTNL::BookingClassBerthDoubleTierNonAcLuxury ( const string & name , const string & remarks )    // constructor
{   remarks_ = remarks ; name_ = name ; loadFactor_ = sLoadFactor ; isLuxury_ = true ; isAC_ = false ;   }

const BCBDTNL & BCBDTNL::SpecialBookingClass ( const string & name , const string & remarks )
{
    static BCBDTNL sSpecialBookingClass(name, remarks) ;   // "Meyer's Implementation of a Singleton Class"
    // static locals are declared only once; its lifetime starts when the 
    // function is called and ends only when the program ends. Therefore,
    // the constructor is called only once and that happens when this function
    // is called for the first time

    return sSpecialBookingClass ; // always return the singleton instance as a 'const' reference of 'BookingClassBerthDoubleTierNonAcLuxury'
}

BCBDTNL::~BookingClassBerthDoubleTierNonAcLuxury ( )    {   }     // no explicit memory management needed -- no dynamically 
                                                                  // allocated memory for any data member -- hence empty body

void BCBDTNL::UnitTestBerthDoubleTierNonAcLuxury ( )
{

    cout << "\n\n   [ BookingClassBerthDoubleTierNonAcLuxury::UnitTestBerthDoubleTierNonAcLuxury ( ) ]" << endl ;
    bool allPassed = true ;

    // TEST 1 : check if the static constant 'BCBDTNL::sLoadFactor' was initialized correctly
    if ( BCBDTNL::sLoadFactor != 2.0 )
    { cout << "'BookingClassBerthDoubleTierNonAcLuxury::sLoadFactor' is not initialized the intended value" << endl ; allPassed = false ;  }
    
    // TEST 2 : Construction of singleton instance with default parameters
    // first call to 'BCBDTNL::SpecialBookingClass'
    const BCBDTNL & b1 = BCBDTNL::SpecialBookingClass() ;
    // check all the data members of the returned instance and match them with actual properties of the booking class
    if ( b1.loadFactor_ != 2.0 || b1.name_ != "First Class (FC)" || b1.remarks_ != "Non-AC 2 berth coupe" || ! b1.isLuxury_ || b1.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerthDoubleTierNonAcLuxury & b1'" << endl ; allPassed = false ;  }

    // TEST 3 : Call 'BCBDTNL::SpecialBookingClass' once again with no parameters
    const BCBDTNL & b2 = BCBDTNL::SpecialBookingClass() ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b2.loadFactor_ != 2.0 || b2.name_ != "First Class (FC)" || b2.remarks_ != "Non-AC 2 berth coupe" || ! b2.isLuxury_ || b2.isAC_ )
    { cout << "Repeated call 'BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass()' returns an object 'const BookingClassBerthDoubleTierNonAcLuxury & b2' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b2 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the default parameters should not have been constructed
    { cout << "'BookingClassBerthDoubleTierNonAcLuxury' is not a singleton class because it returns a new instance on repeating call 'BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass()'" << endl ; allPassed = false ;  }

    // TEST 4 : Call 'BCBDTNL::SpecialBookingClass' once again with arbitrary parameters
    const BCBDTNL & b3 = BCBDTNL::SpecialBookingClass("My Booking Class", "No Remarks") ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b3.loadFactor_ != 2.0 || b3.name_ != "First Class (FC)" || b3.remarks_ != "Non-AC 2 berth coupe" || ! b3.isLuxury_ || b3.isAC_ )
    { cout << "Call with parameters 'BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")' returns an object 'const BookingClassBerthDoubleTierNonAcLuxury & b3' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b3 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the passed parameters should not have been constructed
    { cout << "'BookingClassBerthDoubleTierNonAcLuxury' is not a singleton class because it returns a new instance on calling 'BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")'" << endl ; allPassed = false ;  }

    // TEST 5 : Test accuracy of the values returned by the various methods and match them
    // with the actual properties of this booking class
    if ( b1.GetLoadFactor() != 2.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerthDoubleTierNonAcLuxury & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetName() != "First Class (FC)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerthDoubleTierNonAcLuxury & b1'" << endl ; allPassed = false ;  }
    if ( b1.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerthDoubleTierNonAcLuxury & b1'" << endl ; allPassed = false ;  }
    if ( b1.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerthDoubleTierNonAcLuxury & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetNumberOfTiers() != 2 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerthDoubleTierNonAcLuxury & b1'" << endl ; allPassed = false ;  }
    if ( ! b1.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerthDoubleTierNonAcLuxury & b1'" << endl ; allPassed = false ;  }

    // TEST 6 : Check overloaded output streaming operator
    cout << b1 ;    // stream a single reference to the singleton object
    cout << b2 << b3 << endl ; // stream a chain of references to the singleton object

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef BookingClassBerthTripleTierAcOrdinary BCBTTAO ;
const double BCBTTAO::sLoadFactor = 1.75 ;      // initialize the load factor for this booking class

BCBTTAO::BookingClassBerthTripleTierAcOrdinary ( const string & name , const string & remarks )     // constructor
{   remarks_ = remarks ; name_ = name ; loadFactor_ = sLoadFactor ; isLuxury_ = false ; isAC_ = true ;   }

const BCBTTAO & BCBTTAO::SpecialBookingClass ( const string & name , const string & remarks )
{
    static BCBTTAO sSpecialBookingClass(name, remarks) ;   // "Meyer's Implementation of a Singleton Class"
    // static locals are declared only once; its lifetime starts when the 
    // function is called and ends only when the program ends. Therefore,
    // the constructor is called only once and that happens when this function
    // is called for the first time

    return sSpecialBookingClass ; // always return the singleton instance as a 'const' reference of 'BookingClassBerthTripleTierAcOrdinary'
}

BCBTTAO::~BookingClassBerthTripleTierAcOrdinary ( ) {   }     // no explicit memory management needed -- no dynamically 
                                                              // allocated memory for any data member -- hence empty body

void BCBTTAO::UnitTestBerthTripleTierAcOrdinary ( )
{

    cout << "\n\n   [ BookingClassBerthTripleTierAcOrdinary::UnitTestBerthTripleTierAcOrdinary ( ) ]" << endl ;
    bool allPassed = true ;

    // TEST 1 : check if the static constant 'BCBTTAO::sLoadFactor' was initialized correctly
    if ( BCBTTAO::sLoadFactor != 1.75 )
    { cout << "'BookingClassBerthTripleTierAcOrdinary::sLoadFactor' is not initialized the intended value" << endl ; allPassed = false ;  }
    
    // TEST 2 : Construction of singleton instance with default parameters
    // first call to 'BCBTTAO::SpecialBookingClass'
    const BCBTTAO & b1 = BCBTTAO::SpecialBookingClass() ;
    // check all the data members of the returned instance and match them with actual properties of the booking class
    if ( b1.loadFactor_ != 1.75 || b1.name_ != "AC 3 Tier (3A)" || b1.remarks_ != "AC 3 berth inside, 2 berth onside" || b1.isLuxury_ || ! b1.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerthTripleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }

    // TEST 3 : Call 'BCBTTAO::SpecialBookingClass' once again with no parameters
    const BCBTTAO & b2 = BCBTTAO::SpecialBookingClass() ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b2.loadFactor_ != 1.75 || b2.name_ != "AC 3 Tier (3A)" || b2.remarks_ != "AC 3 berth inside, 2 berth onside" || b2.isLuxury_ || ! b2.isAC_ )
    { cout << "Repeated call 'BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass()' returns an object 'const BookingClassBerthTripleTierAcOrdinary & b2' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b2 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the default parameters should not have been constructed
    { cout << "'BookingClassBerthTripleTierAcOrdinary' is not a singleton class because it returns a new instance on repeating call 'BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass()'" << endl ; allPassed = false ;  }

    // TEST 4 : Call 'BCBTTAO::SpecialBookingClass' once again with arbitrary parameters
    const BCBTTAO & b3 = BCBTTAO::SpecialBookingClass("My Booking Class", "No Remarks") ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b3.loadFactor_ != 1.75 || b3.name_ != "AC 3 Tier (3A)" || b3.remarks_ != "AC 3 berth inside, 2 berth onside" || b3.isLuxury_ || ! b3.isAC_ )
    { cout << "Call with parameters 'BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")' returns an object 'const BookingClassBerthTripleTierAcOrdinary & b3' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b3 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the passed parameters should not have been constructed
    { cout << "'BookingClassBerthTripleTierAcOrdinary' is not a singleton class because it returns a new instance on calling 'BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")'" << endl ; allPassed = false ;  }

    // TEST 5 : Test accuracy of the values returned by the various methods and match them
    // with the actual properties of this booking class
    if ( b1.GetLoadFactor() != 1.75 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerthTripleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetName() != "AC 3 Tier (3A)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerthTripleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( ! b1.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerthTripleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerthTripleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetNumberOfTiers() != 3 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerthTripleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerthTripleTierAcOrdinary & b1'" << endl ; allPassed = false ;  }

    // TEST 6 : Check overloaded output streaming operator
    cout << b1 ;    // stream a single reference to the singleton object
    cout << b2 << b3 << endl ; // stream a chain of references to the singleton object

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef BookingClassBerthTripleTierNonAcOrdinary BCBTTNO ;
const double BCBTTNO::sLoadFactor = 1.00 ;      // initialize the load factor for this booking class

BCBTTNO::BookingClassBerthTripleTierNonAcOrdinary ( const string & name , const string & remarks )  // constructor
{   remarks_ = remarks ; name_ = name ; loadFactor_ = sLoadFactor ; isLuxury_ = false ; isAC_ = false ;   }

const BCBTTNO & BCBTTNO::SpecialBookingClass ( const string & name , const string & remarks )
{
    static BCBTTNO sSpecialBookingClass(name, remarks) ;   // "Meyer's Implementation of a Singleton Class"
    // static locals are declared only once; its lifetime starts when the 
    // function is called and ends only when the program ends. Therefore,
    // the constructor is called only once and that happens when this function
    // is called for the first time

    return sSpecialBookingClass ; // always return the singleton instance as a 'const' reference of 'BookingClassBerthTripleTierNonAcOrdinary'
}

BCBTTNO::~BookingClassBerthTripleTierNonAcOrdinary ( )   {   }     // no explicit memory management needed -- no dynamically 
                                                                   // allocated memory for any data member -- hence empty body

void BCBTTNO::UnitTestBerthTripleTierNonAcOrdinary ( )
{
    cout << "\n\n   [ BookingClassBerthTripleTierNonAcOrdinary::UnitTestBerthTripleTierNonAcOrdinary ( ) ]" << endl ;
    bool allPassed = true ;

    // TEST 1 : check if the static constant 'BCBTTNO::sLoadFactor' was initialized correctly
    if ( BCBTTNO::sLoadFactor != 1.0 )
    { cout << "'BookingClassBerthTripleTierNonAcOrdinary::sLoadFactor' is not initialized the intended value" << endl ; allPassed = false ;  }
    
    // TEST 2 : Construction of singleton instance with default parameters
    // first call to 'BCBTTNO::SpecialBookingClass'
    const BCBTTNO & b1 = BCBTTNO::SpecialBookingClass() ;
    // check all the data members of the returned instance and match them with actual properties of the booking class
    if ( b1.loadFactor_ != 1.0 || b1.name_ != "Sleeper (SL)" || b1.remarks_ != "Non-AC 3 berth inside, 2 berth onside" || b1.isLuxury_ || b1.isAC_ )
    { cout << "Data members are not correctly initialized for 'const BookingClassBerthTripleTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }

    // TEST 3 : Call 'BCBTTNO::SpecialBookingClass' once again with no parameters
    const BCBTTNO & b2 = BCBTTNO::SpecialBookingClass() ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b2.loadFactor_ != 1.0 || b2.name_ != "Sleeper (SL)" || b2.remarks_ != "Non-AC 3 berth inside, 2 berth onside" || b2.isLuxury_ || b2.isAC_ )
    { cout << "Repeated call 'BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()' returns an object 'const BookingClassBerthTripleTierNonAcOrdinary & b2' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b2 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the default parameters should not have been constructed
    { cout << "'BookingClassBerthTripleTierNonAcOrdinary' is not a singleton class because it returns a new instance on repeating call 'BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()'" << endl ; allPassed = false ;  }

    // TEST 4 : Call 'BCBTTNO::SpecialBookingClass' once again with arbitrary parameters
    const BCBTTNO & b3 = BCBTTNO::SpecialBookingClass("My Booking Class", "No Remarks") ;
    // check all the data members of the returned instance and ensure that it has same properties as the instance returned by the first call
    if ( b3.loadFactor_ != 1.0 || b3.name_ != "Sleeper (SL)" || b3.remarks_ != "Non-AC 3 berth inside, 2 berth onside" || b3.isLuxury_ || b3.isAC_ )
    { cout << "Call with parameters 'BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")' returns an object 'const BookingClassBerthTripleTierNonAcOrdinary & b3' with a different state" << endl ; allPassed = false ;  }
    if ( & b1 != & b3 )  // for a singleton class, the instance returned must be same as the former 
                         // -- a new instance with the passed parameters should not have been constructed
    { cout << "'BookingClassBerthTripleTierNonAcOrdinary' is not a singleton class because it returns a new instance on calling 'BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass(\"My Booking Class\", \"No Remarks\")'" << endl ; allPassed = false ;  }

    // TEST 5 : Test accuracy of the values returned by the various methods and match them
    // with the actual properties of this booking class
    if ( b1.GetLoadFactor() != 1.0 )
    { cout << "Member function 'BookingClass::GetLoadFactor()' does not return the correct value for 'const BookingClassBerthTripleTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetName() != "Sleeper (SL)" )
    { cout << "Member function 'BookingClass::GetName()' does not return the correct value for 'const BookingClassBerthTripleTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.IsAC() )
    { cout << "Member function 'BookingClass::IsAC()' does not return the correct value for 'const BookingClassBerthTripleTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.IsSitting() )
    { cout << "Member function 'BookingClass::IsSitting()' does not return the correct value for 'const BookingClassBerthTripleTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.GetNumberOfTiers() != 3 )
    { cout << "Member function 'BookingClass::GetNumberOfTiers()' does not return the correct value for 'const BookingClassBerthTripleTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }
    if ( b1.IsLuxury() )
    { cout << "Member function 'BookingClass::IsLuxury()' does not return the correct value for 'const BookingClassBerthTripleTierNonAcOrdinary & b1'" << endl ; allPassed = false ;  }

    // TEST 6 : Check overloaded output streaming operator
    cout << b1 ;    // stream a single reference to the singleton object
    cout << b2 << b3 << endl ; // stream a chain of references to the singleton object

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed
    
}