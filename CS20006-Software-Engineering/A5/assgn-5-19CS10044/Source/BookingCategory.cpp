
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include <cmath>
#include "BookingCategory.h"
#include "Divyaang.h"
#include "Exceptions.h"
using namespace std ;

// initialize all the static data members by the information
// given in the master data of the specifications
const unsigned int BookingCategory::sMaxAgeMalesForLadies = 12 ;
const unsigned int BookingCategory::sMinAgeMalesForSenCit = 60 ;
const unsigned int BookingCategory::sMinAgeFemalesForSenCit = 58 ;
const unsigned int BookingCategory::sHoursBeforeTravelForPriority = 24 ;

// overloaded output streaming operator
ostream & operator << ( ostream & out , const BookingCategory & b )
{
  out << b.GetName() ;  // print the name of the BookingCategory sub-type onto the console
  return out ;    // returning the 'ostream' object is important for streaming 
                  // of multiple instances chained in the same instruction
}

/////////////////////////////////////////////////////////////////////////////////////

// initialize the statatic data member
template<> const string BookingCategory::General::sName = "General" ;

// write definition of BookingCategory::General::SelectBooking
// +++ virtual construction idiom +++
template<>
const Booking * BookingCategory::General::SelectBooking
                                        ( const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                          const BookingClass & bc , const Passenger & p , const Date & dateOfRes ) const
{ 
  const Booking * b = NULL ;
  try // Call Booking::GeneralBooking::CreateSpecialBooking to construct an instance of the corresponding Booking sub-type.
      // Note that this call is not dispatched directly to the constructor of General Booking sub-type. The validity of the 
      // arguements is first checked in CreateSpecialBooking method and if any invalidity is found, an exception may be thrown.
  { b = Booking::GeneralBooking::CreateSpecialBooking(sFrom, sTo, dateOfBook, bc, *this, p, dateOfRes) ; return b ; }
  // Called method is capable of throwing 5 types of exceptions. In this case catch them and re-throw.
  catch ( Bad_Booking_UndefinedTerminals )
  { throw ; }
  catch ( Bad_Booking_DateOfBooking )
  { throw ; }
  catch ( Bad_Booking_BookingCategory )
  { throw ; }
  catch ( Bad_Booking_BookingClass )
  { throw ; }
  catch ( Bad_Booking_Passenger )
  { throw ; }
}

// write definition of BookingCategory::General::IsElligible
template <>
bool BookingCategory::General::IsElligible ( const Passenger & p , const Date & d ) const
{ return true ; } // Eligibility criteria for General is always satisfied irrespective of Passenger
                  // information and the date of booking.

/////////////////////////////////////////////////////////////////////////////////////

// initialize the statatic data member
template<> const string BookingCategory::Ladies::sName = "Ladies" ;

// write definition of BookingCategory::Ladies::SelectBooking
// +++ virtual construction idiom +++
template<>
const Booking * BookingCategory::Ladies::SelectBooking
                                        ( const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                          const BookingClass & bc , const Passenger & p , const Date & dateOfRes ) const
{ 
  const Booking * b = NULL ;
  try // Call Booking::LadiesBooking::CreateSpecialBooking to construct an instance of the corresponding Booking sub-type.
      // Note that this call is not dispatched directly to the constructor of Ladies Booking sub-type. The validity of the 
      // arguements is first checked in CreateSpecialBooking method and if any invalidity is found, an exception may be thrown.
  { b = Booking::LadiesBooking::CreateSpecialBooking(sFrom, sTo, dateOfBook, bc, *this, p, dateOfRes) ; return b ; }
  // Called method is capable of throwing 5 types of exceptions. In this case catch them and re-throw.
  catch ( Bad_Booking_UndefinedTerminals )
  { throw ; }
  catch ( Bad_Booking_DateOfBooking )
  { throw ; }
  catch ( Bad_Booking_BookingCategory )
  { throw ; }
  catch ( Bad_Booking_BookingClass )
  { throw ; }
  catch ( Bad_Booking_Passenger )
  { throw ; }
}

// write definition of BookingCategory::Ladies::IsElligible
template <>
bool BookingCategory::Ladies::IsElligible ( const Passenger & p , const Date & d ) const
{ 
  if ( & p.GetGender() == & Gender::Female::Type() )  return true ; // females are always eligible for Ladies booking category
  if ( p.GetAge() <= BookingCategory::sMaxAgeMalesForLadies ) return true ; // males have to satisfy the maximum age criteria to be eligible for the same
  return false ;
}

/////////////////////////////////////////////////////////////////////////////////////

// initialize the statatic data member
template<> const string BookingCategory::Divyaang::sName = "Divyaang" ;

// write definition of BookingCategory::Divyaang::SelectBooking
// +++ virtual construction idiom +++
template<>
const Booking * BookingCategory::Divyaang::SelectBooking
                                        ( const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                          const BookingClass & bc , const Passenger & p , const Date & dateOfRes ) const
{ 
  const Booking * b = NULL ;
  try // Call Booking::DivyaangBooking::CreateSpecialBooking to construct an instance of the corresponding Booking sub-type.
      // Note that this call is not dispatched directly to the constructor of Divyaang Booking sub-type. The validity of the 
      // arguements is first checked in CreateSpecialBooking method and if any invalidity is found, an exception may be thrown.
  { b = Booking::DivyaangBooking::CreateSpecialBooking(sFrom, sTo, dateOfBook, bc, *this, p, dateOfRes) ; return b ; }
  // Called method is capable of throwing 5 types of exceptions. In this case catch them and re-throw.
  catch ( Bad_Booking_UndefinedTerminals )
  { throw ; }
  catch ( Bad_Booking_DateOfBooking )
  { throw ; }
  catch ( Bad_Booking_BookingCategory )
  { throw ; }
  catch ( Bad_Booking_BookingClass )
  { throw ; }
  catch ( Bad_Booking_Passenger )
  { throw ; }
}

// write definition of BookingCategory::Divyaang::IsElligible
template <>
bool BookingCategory::Divyaang::IsElligible ( const Passenger & p , const Date & d ) const
{ 
  if ( p.GetDisabilityType() )  return true ; // the disability type of the Passenger cannot be NULL to be
                                              // eligible for Divyaang booking category
  return false ;
}

/////////////////////////////////////////////////////////////////////////////////////

// initialize the statatic data member
template<> const string BookingCategory::SeniorCitizen::sName = "Senior Citizen" ;

// write definition of BookingCategory::SeniorCitizen::SelectBooking
// +++ virtual construction idiom +++
template<>
const Booking * BookingCategory::SeniorCitizen::SelectBooking
                                        ( const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                          const BookingClass & bc , const Passenger & p , const Date & dateOfRes ) const
{ 
  const Booking * b = NULL ;
  try // Call Booking::SeniorCitizenBooking::CreateSpecialBooking to construct an instance of the corresponding Booking sub-type.
      // Note that this call is not dispatched directly to the constructor of SeniorCitizen Booking sub-type. The validity of the 
      // arguements is first checked in CreateSpecialBooking method and if any invalidity is found, an exception may be thrown.
  { b = Booking::SeniorCitizenBooking::CreateSpecialBooking(sFrom, sTo, dateOfBook, bc, *this, p, dateOfRes) ; return b ; }
  // Called method is capable of throwing 5 types of exceptions. In this case catch them and re-throw.
  catch ( Bad_Booking_UndefinedTerminals )
  { throw ; }
  catch ( Bad_Booking_DateOfBooking )
  { throw ; }
  catch ( Bad_Booking_BookingCategory )
  { throw ; }
  catch ( Bad_Booking_BookingClass )
  { throw ; }
  catch ( Bad_Booking_Passenger )
  { throw ; }
}

// write definition of BookingCategory::SeniorCitizen::IsElligible
template <>
bool BookingCategory::SeniorCitizen::IsElligible ( const Passenger & p , const Date & d ) const
{ 
  if ( & p.GetGender() == & Gender::Female::Type() )
    if ( p.GetAge() < BookingCategory::sMinAgeFemalesForSenCit )  return false ; // females have to satisfy the minimum age criteria to be eligible for SeniorCitizen
    else  return true ;
  if ( p.GetAge() < BookingCategory::sMinAgeMalesForSenCit ) return false ; // males also have to satisfy the minimum age criteria to be eligible for the same
  return true ;
}

/////////////////////////////////////////////////////////////////////////////////////

// initialize the statatic data member
template<> const string BookingCategory::Tatkal::sName = "Tatkal" ;

// write definition of BookingCategory::Tatkal::SelectBooking
// +++ virtual construction idiom +++
template<>
const Booking * BookingCategory::Tatkal::SelectBooking
                                        ( const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                          const BookingClass & bc , const Passenger & p , const Date & dateOfRes ) const
{ 
  const Booking * b = NULL ;
  try // Call Booking::TatkalBooking::CreateSpecialBooking to construct an instance of the corresponding Booking sub-type.
      // Note that this call is not dispatched directly to the constructor of Tatkal Booking sub-type. The validity of the 
      // arguements is first checked in CreateSpecialBooking method and if any invalidity is found, an exception may be thrown.
  { b = Booking::TatkalBooking::CreateSpecialBooking(sFrom, sTo, dateOfBook, bc, *this, p, dateOfRes) ; return b ; }
  // Called method is capable of throwing 5 types of exceptions. In this case catch them and re-throw.
  catch ( Bad_Booking_UndefinedTerminals )
  { throw ; }
  catch ( Bad_Booking_DateOfBooking )
  { throw ; }
  catch ( Bad_Booking_BookingCategory )
  { throw ; }
  catch ( Bad_Booking_BookingClass )
  { throw ; }
  catch ( Bad_Booking_Passenger )
  { throw ; }
}

// write definition of BookingCategory::Tatkal::IsElligible
template <>
bool BookingCategory::Tatkal::IsElligible ( const Passenger & p , const Date & d ) const
{ 
  if ( d.GetDifferenceInDays(Date::GetTodaysDate()) * 24 == 
       BookingCategory::sHoursBeforeTravelForPriority ) return true ; // Tatkal booking category is applicable if and only if the date of booking is after
                                                                      // a particular number of days (in this case -- 1) from the today, i.e, the date of reservation
  return false ;
}

/////////////////////////////////////////////////////////////////////////////////////

// initialize the statatic data member
template<> const string BookingCategory::PremiumTatkal::sName = "Premium Tatkal" ;

// write definition of BookingCategory::PremiumTatkal::SelectBooking
// +++ virtual construction idiom +++
template<>
const Booking * BookingCategory::PremiumTatkal::SelectBooking
                                        ( const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                          const BookingClass & bc , const Passenger & p , const Date & dateOfRes ) const
{ 
  const Booking * b = NULL ;
  try // Call Booking::PremiumTatkalBooking::CreateSpecialBooking to construct an instance of the corresponding Booking sub-type.
      // Note that this call is not dispatched directly to the constructor of PremiumTatkal Booking sub-type. The validity of the 
      // arguements is first checked in CreateSpecialBooking method and if any invalidity is found, an exception may be thrown.
  { b = Booking::PremiumTatkalBooking::CreateSpecialBooking(sFrom, sTo, dateOfBook, bc, *this, p, dateOfRes) ; return b ; }
  // Called method is capable of throwing 5 types of exceptions. In this case catch them and re-throw.
  catch ( Bad_Booking_UndefinedTerminals )
  { throw ; }
  catch ( Bad_Booking_DateOfBooking )
  { throw ; }
  catch ( Bad_Booking_BookingCategory )
  { throw ; }
  catch ( Bad_Booking_BookingClass )
  { throw ; }
  catch ( Bad_Booking_Passenger )
  { throw ; }
}

// write definition of BookingCategory::PremiumTatkal::IsElligible
template <>
bool BookingCategory::PremiumTatkal::IsElligible ( const Passenger & p , const Date & d ) const
{
  if ( d.GetDifferenceInDays(Date::GetTodaysDate()) * 24 == 
       BookingCategory::sHoursBeforeTravelForPriority ) return true ; // PremiumTatkal booking category is applicable if and only if the date of booking is after
                                                                      // a particular number of days (in this case -- 1) from the today, i.e, the date of reservation
  return false ;
}

///////////////////////////////////////////////////////////////////////////////////////

typedef Divyaang::Blind Blind ;

// In order to model the test case of checking the erroneous
// BookingClass type, an invalid BookingClass sub-type has to be introduced
// as given in the test plan document. 
struct TestTypeBC { } ;    // placeholder for the invalid static sub-type
// give arbitrarily any values to the static data members for this invalid sub-type
template<>  const string BookingClassTypes<TestTypeBC>::sName = "Test" ;
template<>  const double BookingClassTypes<TestTypeBC>::sLoadFactor = false ;
template<>  const bool BookingClassTypes<TestTypeBC>::sIsSitting = false ;
template<>  const bool BookingClassTypes<TestTypeBC>::sIsAC = false ;
template<>  const bool BookingClassTypes<TestTypeBC>::sIsLuxury = 0 ;
template<>  const unsigned int BookingClassTypes<TestTypeBC>::sNumberOfTiers = 0 ;
template<>  const double BookingClassTypes<TestTypeBC>::sReservationCharge = 0.0 ;
template<>  const double BookingClassTypes<TestTypeBC>::sTatkalCharge = 0.0 ;
template<>  const double BookingClassTypes<TestTypeBC>::sMaxTatkalCharge = 0.0 ;
template<>  const double BookingClassTypes<TestTypeBC>::sMinTatkalCharge = 0.0 ;
template<>  const unsigned int BookingClassTypes<TestTypeBC>::sMinDistanceForTatkalCharge = 0 ;

// implementation of the Unit Test Plan written for BookingCategory hierarchy
void BookingCategory::UnitTestBookingCategoryHierarchy ( )
{
  // check if the sub-types of BookingCategory are implemented as singletons
  const BookingCategory & b1 = BookingCategory::General::Type() ;
  const BookingCategory & b2 = BookingCategory::General::Type() ;
  if ( &b1 == &b2 )   // check if the BookingCategory sub-type is constructed only once.
                      // compare the addresses to ensure that they are indeed the same instances and
                      // hence the sub-type class is indeed a singleton class
    cout << "   TEST CASE I.1.1 PASSED" << endl ;
  
  // TEST ALL THE NON-STATIC MEMBER FUNCTIONS
  if ( BookingCategory::General::Type().GetName() == "General" )
    cout << "   TEST CASE I.2.1 PASSED" << endl ;
  
  // test IsElligible method for all the BookingCategory sub-types, for various scenarios
  // of fulfilled and unfulfilled eligibility criteria
  if ( BookingCategory::General::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/06/2020"), "Male", 
        "123456789012", "John"), Date::CreateDate("01/01/2022")) == true )
    cout << "   TEST CASE I.2.2 PASSED" << endl ;

  // various scenarios to check eligibility for Ladies
  if ( BookingCategory::Ladies::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/06/2008"), "Male", 
        "123456789012", "John"), Date::CreateDate("01/01/2022")) == false )
    cout << "   TEST CASE I.2.3 PASSED" << endl ;
  
  // various scenarios to check eligibility for Ladies
  if ( BookingCategory::Ladies::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/06/2020"), "Female", 
        "123456789012", "Jane"), Date::CreateDate("01/01/2022")) == true )
    cout << "   TEST CASE I.2.4.1 PASSED" << endl ;
  
  if ( BookingCategory::Ladies::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/04/2009"), "Male", 
        "123456789012", "John"), Date::CreateDate("01/01/2022")) == true )
    cout << "   TEST CASE I.2.4.2 PASSED" << endl ;

  // various scenarios to check eligibility for Divyaang
  if ( BookingCategory::Divyaang::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/06/2020"), "Female", 
        "123456789012", "Jane"), Date::CreateDate("01/01/2022")) == false )
    cout << "   TEST CASE I.2.5 PASSED" << endl ;

  if ( BookingCategory::Divyaang::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/06/2020"), "Female", 
        "123456789012", "Jane", "", "", "", &Blind::Type()), Date::CreateDate("01/01/2022")) == true )
    cout << "   TEST CASE I.2.6 PASSED" << endl ;

  // various scenarios to check eligibility for SeniorCitizen
  if ( BookingCategory::SeniorCitizen::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/06/1964"), "Female", 
        "123456789012", "Jane"), Date::CreateDate("01/01/2022")) == false )
    cout << "   TEST CASE I.2.7.1 PASSED" << endl ;

  if ( BookingCategory::SeniorCitizen::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/06/1962"), "Male", 
        "123456789012", "John"), Date::CreateDate("01/01/2022")) == false )
    cout << "   TEST CASE I.2.7.2 PASSED" << endl ;
  
  if ( BookingCategory::SeniorCitizen::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/01/1963"), "Female", 
        "123456789012", "Jane"), Date::CreateDate("01/01/2022")) == true )
    cout << "   TEST CASE I.2.8.1 PASSED" << endl ;
  
  if ( BookingCategory::SeniorCitizen::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/01/1961"), "Male", 
        "123456789012", "John"), Date::CreateDate("01/01/2022")) == true )
    cout << "   TEST CASE I.2.8.2 PASSED" << endl ;
  
  // various scenarios to check eligibility for Tatkal
  if ( BookingCategory::Tatkal::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/06/1964"), "Female", 
        "123456789012", "Jane"), Date::CreateDate("01/12/2021")) == false )
    cout << "   TEST CASE I.2.9 PASSED" << endl ;
  
  if ( BookingCategory::Tatkal::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/06/1964"), "Female", 
        "123456789012", "Jane"), Date::CreateDate("09/04/2021")) == true )  // the date of booking must be chosen depending on the date of execution
                                                                            // of this test case (as mentioned in the testplan document) otherwise a 
                                                                            // false FAIL may occur.
    cout << "   TEST CASE I.2.10 PASSED" << endl ;
  
  // various scenarios to check eligibility for PremiumTatkal
  if ( BookingCategory::PremiumTatkal::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/06/1964"), "Female", 
        "123456789012", "Jane"), Date::CreateDate("01/12/2021")) == false )
    cout << "   TEST CASE I.2.11 PASSED" << endl ;
  
  if ( BookingCategory::PremiumTatkal::Type().IsElligible(
        Passenger::CreatePassenger(Date::CreateDate("30/06/1964"), "Female", 
        "123456789012", "Jane"), Date::CreateDate("09/04/2021")) == true )  // the date of booking must be chosen depending on the date of execution
                                                                            // of this test case (as mentioned in the testplan document) otherwise a 
                                                                            // false FAIL may occur.
    cout << "   TEST CASE I.2.12 PASSED" << endl ;

  // Call SelectBooking for one BookingCategory sub-type for various scenarios of
  // erroneous arguement values
  try // the distance between the terminal stations is not defined
  {
    BookingCategory::Ladies::Type().SelectBooking(Station::CreateStation("Mumbai"), 
    Station::CreateStation("Pune"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(), 
    Passenger::CreatePassenger(Date::CreateDate("01/01/2020"), "Male", "123456789012", "John"), 
    Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_UndefinedTerminals )
  { cout << "   TEST CASE I.2.13 PASSED" << endl ; }

  try // the date of booking is in the past
  {
    BookingCategory::Ladies::Type().SelectBooking(Station::CreateStation("Mumbai"), 
    Station::CreateStation("Delhi"), Date::CreateDate("01/01/2021"), BookingClass::ACFirstClass::Type(), 
    Passenger::CreatePassenger(Date::CreateDate("01/01/2020"), "Male", "123456789012", "John"), 
    Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_DateOfBooking )
  { cout << "   TEST CASE I.2.14.1 PASSED" << endl ; }

  try // the date of booking is today
  {
    BookingCategory::Ladies::Type().SelectBooking(Station::CreateStation("Mumbai"), 
    Station::CreateStation("Delhi"), Date::GetTodaysDate(), BookingClass::ACFirstClass::Type(), 
    Passenger::CreatePassenger(Date::CreateDate("01/01/2020"), "Male", "123456789012", "John"), 
    Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_DateOfBooking )
  { cout << "   TEST CASE I.2.14.2 PASSED" << endl ; }
  
  try // the date of booking is after one year from today
  {
    BookingCategory::Ladies::Type().SelectBooking(Station::CreateStation("Mumbai"), 
    Station::CreateStation("Delhi"), Date::CreateDate("01/12/2022"), BookingClass::ACFirstClass::Type(), 
    Passenger::CreatePassenger(Date::CreateDate("01/01/2020"), "Male", "123456789012", "John"), 
    Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_DateOfBooking )
  { cout << "   TEST CASE I.2.14.3 PASSED" << endl ; }

  try // booking class is invalid
  {
    BookingCategory::Ladies::Type().SelectBooking(Station::CreateStation("Mumbai"), 
    Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClassTypes<TestTypeBC>::Type(), 
    Passenger::CreatePassenger(Date::CreateDate("01/01/2020"), "Male", "123456789012", "John"), 
    Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_BookingClass )
  { cout << "   TEST CASE I.2.15 PASSED" << endl ; }

  try // passenger is not elligible for the specified booking category
  {
    BookingCategory::Ladies::Type().SelectBooking(Station::CreateStation("Mumbai"), 
    Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(), 
    Passenger::CreatePassenger(Date::CreateDate("01/01/2001"), "Male", "123456789012", "John"), 
    Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_Passenger )
  { cout << "   TEST CASE I.2.16 PASSED" << endl ; }

  Passenger p = Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", 
                "123456789012", "Jane", "", "", "", &Blind::Type()) ;
  
  // Use SelectBooking on all the sub-types of BookingCtaegory to test if the virtual construction idiom works, that
  // is, to check if the Booking object of the correct Booking sub-type is constructed depending on the BookingCategory sub-type

  // check for General BookingCategory
  const Booking * book1 = BookingCategory::General::Type().SelectBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), 
                      Date::CreateDate("09/04/2021"), BookingClass::ACFirstClass::Type(), p, Date::GetTodaysDate()) ;
  if ( book1->GetType() == "General" )  // check the type of the constructed Booking
    cout << "   TEST CASE I.2.17.1 PASSED" << endl ;
  delete book1 ;
  
  // check for Ladies BookingCategory
  const Booking * book2 = BookingCategory::Ladies::Type().SelectBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), 
                          Date::CreateDate("09/04/2021"), BookingClass::ACFirstClass::Type(), p, Date::GetTodaysDate()) ;
  if ( book2->GetType() == "Ladies" )  // check the type of the constructed Booking
    cout << "   TEST CASE I.2.17.2 PASSED" << endl ;
  delete book2 ;
  
  // check for SeniorCitizen BookingCategory
  const Booking * book3 = BookingCategory::SeniorCitizen::Type().SelectBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), 
                              Date::CreateDate("09/04/2021"), BookingClass::ACFirstClass::Type(), p, Date::GetTodaysDate()) ;
  if ( book3->GetType() == "Senior Citizen" )  // check the type of the constructed Booking
    cout << "   TEST CASE I.2.17.3 PASSED" << endl ;
  delete book3 ;
  
  // check for Divyaang BookingCategory
  const Booking * book4 = BookingCategory::Divyaang::Type().SelectBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), 
                            Date::CreateDate("09/04/2021"), BookingClass::ACFirstClass::Type(), p, Date::GetTodaysDate()) ;
  if ( book4->GetType() == "Divyaang" )  // check the type of the constructed Booking
    cout << "   TEST CASE I.2.17.4 PASSED" << endl ;
  delete book4 ;
  
  // check for Tatkal BookingCategory
  const Booking * book5 = BookingCategory::Tatkal::Type().SelectBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), 
                          Date::CreateDate("09/04/2021"), BookingClass::ACFirstClass::Type(), p, Date::GetTodaysDate()) ;
  if ( book5->GetType() == "Tatkal" )  // check the type of the constructed Booking
    cout << "   TEST CASE I.2.17.5 PASSED" << endl ;
  delete book5 ;
  
  // check for PremiumTatkal BookingCategory
  const Booking * book6 = BookingCategory::PremiumTatkal::Type().SelectBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), 
                          Date::CreateDate("09/04/2021"), BookingClass::ACFirstClass::Type(), p, Date::GetTodaysDate()) ;
  if ( book6->GetType() == "Premium Tatkal" )  // check the type of the constructed Booking
    cout << "   TEST CASE I.2.17.6 PASSED" << endl ;
  delete book6 ;
  
  // print a BookingCategory sub-type onto the console using the
  // overloaded output streaming operator
  cout << "   TEST CASE I.3.1 -- " << BookingCategory::General::Type() << endl ;

  // test dynamic dispatch of all the polymorphic methods
  const BookingCategory & bcGeneral = BookingCategory::General::Type() ;    // upcast the BookingCategory sub-type to the const reference of base class
  // now call the non-static member functions on this variable "bcGeneral" and match with the expected output
  if ( bcGeneral.GetName() == "General" )
    cout << "   TEST CASE I.4.1 PASSED" << endl ;
  
  if ( bcGeneral.IsElligible(Passenger::CreatePassenger(Date::CreateDate("30/06/2020"), "Male", 
        "123456789012", "John"), Date::CreateDate("01/01/2022")) == true )
    cout << "   TEST CASE I.4.2 PASSED" << endl ;
  
  const Booking * booking = bcGeneral.SelectBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), 
                      Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(), Passenger::CreatePassenger(
                      Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane"), Date::GetTodaysDate()) ;
  if ( booking->GetType() == "General" )
    cout << "   TEST CASE I.4.3 PASSED" << endl ;
  delete booking ;
}