
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <cmath>
#include "Booking.h"
#include "Exceptions.h"
using namespace std ;

const double Booking::sBaseFareRate = 0.5 ; // initialize based on the master data
unsigned int Booking::sNextAvailablePNR = 1 ; // initialize the PNR number to 1 -- must start sequentially from 1

// constructor of base class
Booking::Booking (  const Station & s1 , const Station & s2 , const Date & d1 , const BookingClass & bc ,
                        const BookingCategory & bcat , const Passenger & p , const Date & d2 )
            : fromStation_(s1) , toStation_(s2) , dateOfBooking_(d1) , bookingClass_(bc) , bookingCategory_(bcat) ,
              passenger_(p) , dateOfReservation_(d2) , pnr_(Booking::sNextAvailablePNR++) , fare_(0)  // initializer list
                                                                                            // give an arbitrary value to fare_ for now
{   
  #ifdef _DEBUG
    cout << "Booking CONSTRUCTED : " << pnr_ << endl ;
  #endif
}

// constructor of the derived template class
template< typename T >
BookingTypes<T>::BookingTypes (  const Station & s1 , const Station & s2 , const Date & d1 , const BookingClass & bc ,
                                    const BookingCategory & bcat , const Passenger & p , const Date & d2 )
            : Booking(s1, s2, d1, bc, bcat, p, d2)  // initilizer list -- construct the base class part
{ fare_ = this->ComputeFare() ; } // Apply business logic on the constructed Booking object to compute the fare. This call will dispatch
                                  // to the business logic of the correct Booking sub-type

// overloaded output streaming operator
ostream & operator << ( ostream & out , const Booking & booking )
{
    out << endl << " BOOKING SUCCESSFUL :" << endl ;
    // print all the details of the Booking
    out << " PNR Number = " << booking.pnr_ << endl ;
    out << " From Station = " << booking.fromStation_.GetName() << endl ;
    out << " To Station = " << booking.toStation_.GetName() << endl ;
    out << " Reservation Date = " << booking.dateOfReservation_ << endl ; // use "std::ostream &operator<<(std::ostream &, const Date &)"
    out << " Travel Date = " << booking.dateOfBooking_ << endl ; // use "std::ostream &operator<<(std::ostream &, const Date &)"
    // print details specific to the booking class
    out << " Travel Class = " << booking.bookingClass_.GetName() << endl ;
    if ( booking.bookingClass_.IsSitting() )   out << " : Mode : Sitting" << endl ;
    else    out << " : Mode : Sleeping" << endl ;
    if ( booking.bookingClass_.IsAC() )   out << " : Comfort : AC" << endl ;
    else    out << " : Comfort : Non-AC" << endl ;
    out << " : Bunks : " << booking.bookingClass_.GetNumberOfTiers() << endl ;
    if ( booking.bookingClass_.IsLuxury() )   out << " : Luxury : Yes" << endl ;
    else    out << " : Luxury : No" << endl ;
    out << " Booking Category = " << booking.bookingCategory_.GetName() << endl ;
    out << " Fare = " << booking.fare_ ;
    out << booking.passenger_ ; // std::ostream &operator<<(std::ostream &, const Passenger &)
    return out ;    // returning the 'ostream' object is important for streaming 
                    // of multiple instances chained in the same instruction
}

const Booking * Booking::CreateBooking ( const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                         const BookingClass & bc , const BookingCategory & bCat , const Passenger & p )
{
  // First of all, all the arguements have to be validated and 
  // appropriate exceptions must be thrown if any validation failure occurs
  try // check if the distance between the two terminal stations exists in the Indian Railways
  { Railways::SpecialRailways().GetDistance(sFrom, sTo) ; }
  catch(Bad_Railways_Distance)
  { throw Bad_Booking_UndefinedTerminals("Terminal stations are not connected in the Railways") ; }

  int diff = dateOfBook.GetDifferenceInDays(Date::GetTodaysDate()) ;
  if ( diff <= 0 )  // date of booking must be in future
    throw Bad_Booking_DateOfBooking("Date of booking must be after date of reservation") ;
  if ( diff > 365 ) // date of booking must be within 1 year from date of reservation, i.e., today
    throw Bad_Booking_DateOfBooking("Date of booking must be within 1 year of date of reservation") ;

  // booking category must be valid, that is, one of the 6 defined BookingCategory sub-types
  if ( &bCat != &BookingCategory::General::Type() && &bCat != &BookingCategory::Ladies::Type() &&
       &bCat != &BookingCategory::SeniorCitizen::Type() && &bCat != &BookingCategory::Divyaang::Type() &&
       &bCat != &BookingCategory::Tatkal::Type() && &bCat != &BookingCategory::PremiumTatkal::Type() )
    throw Bad_Booking_BookingCategory("Booking category must be valid") ;

  // booking class must be valid, that is, one of the 8 defined BookingClass sub-types
  if ( &bc != &BookingClass::ACFirstClass::Type() && &bc != &BookingClass::ACChairCar::Type() &&
       &bc != &BookingClass::AC2Tier::Type() && &bc != &BookingClass::AC3Tier::Type() &&
       &bc != &BookingClass::SecondSitting::Type() && &bc != &BookingClass::Sleeper::Type() && 
       &bc != &BookingClass::ExecutiveChairCar::Type() && &bc != &BookingClass::FirstClass::Type())
    throw Bad_Booking_BookingClass("Booking class must be valid") ;
  
  // lastly, passenger must be elligible for the booking category that is chosen
  if ( ! bCat.IsElligible(p, dateOfBook) )
  {
    throw Bad_Booking_Passenger("Criteria to avail the specified booking category is not satisified") ;
  }
  // if all the validation criteria is fulfilled, instantiate a Booking sub-type corresponding
  // to the specified BookingCategory sub-type. Use BookingCategory::SelectBooking method for 
  // this realization of VIRTUAL CONSTRUCTION IDIOM
  return bCat.SelectBooking(sFrom, sTo, dateOfBook, bc, p, Date::GetTodaysDate()) ;  
}

/////////////////////////////////////////////////////////////////////////////////////

// initialize static const data member
template<>
const string Booking::GeneralBooking::sBookingType = "General" ;

// implement the business fare logic for General booking sub-type
// as given in the specifications
template<> 
unsigned int Booking::GeneralBooking::ComputeFare ( ) const
{
  unsigned int d = Railways::SpecialRailways().GetDistance(fromStation_, toStation_) ;
  double baseFare = d * Booking::sBaseFareRate ;
  double loadedFare = baseFare * bookingClass_.GetLoadFactor() ;
  double withConcession = loadedFare * ( 1.00 - GeneralConcession::GetConcessionFactor() ) ;
  double withResCharge = withConcession + bookingClass_.GetReservationCharge() ;
  return round(withResCharge) ;
}

template<>
const Booking::GeneralBooking * Booking::GeneralBooking::CreateSpecialBooking (  const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                                        const BookingClass & bc , const BookingCategory & bCat , const Passenger & p , 
                                                        const Date & dateOfRes ) 
{
  // first of all, validate all the arguements as was done in Booking::SelectBooking
  try
  { Railways::SpecialRailways().GetDistance(sFrom, sTo) ; }
  catch(Bad_Railways_Distance)
  { throw Bad_Booking_UndefinedTerminals("Terminal stations are not connected in the Railways") ; }

  int diff = dateOfBook.GetDifferenceInDays(dateOfRes) ;
  if ( diff <= 0 )
    throw Bad_Booking_DateOfBooking("Date of booking must be after date of reservation") ;
  if ( diff > 365 )
    throw Bad_Booking_DateOfBooking("Date of booking must be within 1 year of date of reservation") ;

  if ( &bCat != &BookingCategory::General::Type() ) // BookingCategory sub-type must specifically match this sub-type 
    throw Bad_Booking_BookingCategory("Booking category is incompatible with the Booking sub-type") ;

  if ( &bc != &BookingClass::ACFirstClass::Type() && &bc != &BookingClass::ACChairCar::Type() &&
       &bc != &BookingClass::AC2Tier::Type() && &bc != &BookingClass::AC3Tier::Type() &&
       &bc != &BookingClass::SecondSitting::Type() && &bc != &BookingClass::Sleeper::Type() && 
       &bc != &BookingClass::ExecutiveChairCar::Type() && &bc != &BookingClass::FirstClass::Type())
    throw Bad_Booking_BookingClass("Booking class must be valid") ;

  if ( ! bCat.IsElligible(p, dateOfBook) )
  {
    throw Bad_Booking_Passenger("Criteria to avail the specified booking category is not satisified") ;
  }

  // call private constructor for this Booking sub-type and return the constructed instance
  // the last lifeline in the virtual construction idiom
  return new Booking::GeneralBooking(sFrom, sTo, dateOfBook, bc, bCat, p, dateOfRes) ;    
}

/////////////////////////////////////////////////////////////////////////////////////

// initialize static const data member
template<> 
const string Booking::LadiesBooking::sBookingType = "Ladies" ;

// implement the business fare logic for Ladies booking sub-type
// as given in the specifications
template<> 
unsigned int Booking::LadiesBooking::ComputeFare ( ) const
{
  unsigned int d = Railways::SpecialRailways().GetDistance(fromStation_, toStation_) ;
  double baseFare = d * Booking::sBaseFareRate ;
  double loadedFare = baseFare * bookingClass_.GetLoadFactor() ;
  double withConcession = loadedFare * ( 1.00 - LadiesConcession::GetConcessionFactor(passenger_) ) ; // concession factor based on the passenger information must be used
  double withResCharge = withConcession + bookingClass_.GetReservationCharge() ;
  return round(withResCharge) ;
}

template<>
const Booking::LadiesBooking * Booking::LadiesBooking::CreateSpecialBooking (  const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                                        const BookingClass & bc , const BookingCategory & bCat , const Passenger & p , 
                                                        const Date & dateOfRes ) 
{   
  // first of all, validate all the arguements as was done in Booking::SelectBooking
  try
  { Railways::SpecialRailways().GetDistance(sFrom, sTo) ; }
  catch(Bad_Railways_Distance)
  { throw Bad_Booking_UndefinedTerminals("Terminal stations are not connected in the Railways") ; }

  int diff = dateOfBook.GetDifferenceInDays(dateOfRes) ;
  if ( diff <= 0 )
    throw Bad_Booking_DateOfBooking("Date of booking must be after date of reservation") ;
  if ( diff > 365 )
    throw Bad_Booking_DateOfBooking("Date of booking must be within 1 year of date of reservation") ;

  if ( &bCat != &BookingCategory::Ladies::Type() ) // BookingCategory sub-type must specifically match this sub-type 
    throw Bad_Booking_BookingCategory("Booking category is incompatible with the Booking sub-type") ;

  if ( &bc != &BookingClass::ACFirstClass::Type() && &bc != &BookingClass::ACChairCar::Type() &&
       &bc != &BookingClass::AC2Tier::Type() && &bc != &BookingClass::AC3Tier::Type() &&
       &bc != &BookingClass::SecondSitting::Type() && &bc != &BookingClass::Sleeper::Type() && 
       &bc != &BookingClass::ExecutiveChairCar::Type() && &bc != &BookingClass::FirstClass::Type())
    throw Bad_Booking_BookingClass("Booking class must be valid") ;

  if ( ! bCat.IsElligible(p, dateOfBook) )
  {
    throw Bad_Booking_Passenger("Criteria to avail the specified booking category is not satisified") ;
  }

  // call private constructor for this Booking sub-type and return the constructed instance
  // the last lifeline in the virtual construction idiom
  return new Booking::LadiesBooking(sFrom, sTo, dateOfBook, bc, bCat, p, dateOfRes) ; 
}

/////////////////////////////////////////////////////////////////////////////////////

// initialize static const data member
template<> 
const string Booking::SeniorCitizenBooking::sBookingType = "Senior Citizen" ;

// implement the business fare logic for SeniorCitizen booking sub-type
// as given in the specifications
template<> 
unsigned int Booking::SeniorCitizenBooking::ComputeFare ( ) const
{
  unsigned int d = Railways::SpecialRailways().GetDistance(fromStation_, toStation_) ;
  double baseFare = d * Booking::sBaseFareRate ;
  double loadedFare = baseFare * bookingClass_.GetLoadFactor() ;
  double withConcession = loadedFare * ( 1.00 - SeniorCitizenConcession::GetConcessionFactor(passenger_) ) ; // concession factor based on the passenger information must be used
  double withResCharge = withConcession + bookingClass_.GetReservationCharge() ;
  return round(withResCharge) ;
}

template<>
const Booking::SeniorCitizenBooking * Booking::SeniorCitizenBooking::CreateSpecialBooking (  const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                                        const BookingClass & bc , const BookingCategory & bCat , const Passenger & p , 
                                                        const Date & dateOfRes ) 
{ 
  // first of all, validate all the arguements as was done in Booking::SelectBooking
  try
  { Railways::SpecialRailways().GetDistance(sFrom, sTo) ; }
  catch(Bad_Railways_Distance)
  { throw Bad_Booking_UndefinedTerminals("Terminal stations are not connected in the Railways") ; }

  int diff = dateOfBook.GetDifferenceInDays(dateOfRes) ;
  if ( diff <= 0 )
    throw Bad_Booking_DateOfBooking("Date of booking must be after date of reservation") ;
  if ( diff > 365 )
    throw Bad_Booking_DateOfBooking("Date of booking must be within 1 year of date of reservation") ;

  if ( &bCat != &BookingCategory::SeniorCitizen::Type() ) // BookingCategory sub-type must specifically match this sub-type 
    throw Bad_Booking_BookingCategory("Booking category is incompatible with the Booking sub-type") ;

  if ( &bc != &BookingClass::ACFirstClass::Type() && &bc != &BookingClass::ACChairCar::Type() &&
       &bc != &BookingClass::AC2Tier::Type() && &bc != &BookingClass::AC3Tier::Type() &&
       &bc != &BookingClass::SecondSitting::Type() && &bc != &BookingClass::Sleeper::Type() && 
       &bc != &BookingClass::ExecutiveChairCar::Type() && &bc != &BookingClass::FirstClass::Type())
    throw Bad_Booking_BookingClass("Booking class must be valid") ;

  if ( ! bCat.IsElligible(p, dateOfBook) )
  {
    throw Bad_Booking_Passenger("Criteria to avail the specified booking category is not satisified") ;
  }

  // call private constructor for this Booking sub-type and return the constructed instance
  // the last lifeline in the virtual construction idiom
  return new Booking::SeniorCitizenBooking(sFrom, sTo, dateOfBook, bc, bCat, p, dateOfRes) ; 
}

/////////////////////////////////////////////////////////////////////////////////////

// initialize static const data member
template<> 
const string Booking::DivyaangBooking::sBookingType = "Divyaang" ;

// implement the business fare logic for Divyaang booking sub-type
// as given in the specifications
template<> 
unsigned int Booking::DivyaangBooking::ComputeFare ( ) const
{
  unsigned int d = Railways::SpecialRailways().GetDistance(fromStation_, toStation_) ;
  double baseFare = d * Booking::sBaseFareRate ;
  double loadedFare = baseFare * bookingClass_.GetLoadFactor() ;
  double withConcession = loadedFare * ( 1.00 - DivyaangConcession::GetConcessionFactor(passenger_, bookingClass_) ) ; // concession factor based on the passenger 
                                                                                                                       // and BookingClass sub-type information must be used
  double withResCharge = withConcession + bookingClass_.GetReservationCharge() ;
  return round(withResCharge) ;
}

template<>
const Booking::DivyaangBooking * Booking::DivyaangBooking::CreateSpecialBooking (  const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                                        const BookingClass & bc , const BookingCategory & bCat , const Passenger & p , 
                                                        const Date & dateOfRes ) 
{ 
  // first of all, validate all the arguements as was done in Booking::SelectBooking
  try
  { Railways::SpecialRailways().GetDistance(sFrom, sTo) ; }
  catch(Bad_Railways_Distance)
  { throw Bad_Booking_UndefinedTerminals("Terminal stations are not connected in the Railways") ; }

  int diff = dateOfBook.GetDifferenceInDays(dateOfRes) ;
  if ( diff <= 0 )
    throw Bad_Booking_DateOfBooking("Date of booking must be after date of reservation") ;
  if ( diff > 365 )
    throw Bad_Booking_DateOfBooking("Date of booking must be within 1 year of date of reservation") ;

  if ( &bCat != &BookingCategory::Divyaang::Type() ) // BookingCategory sub-type must specifically match this sub-type 
    throw Bad_Booking_BookingCategory("Booking category is incompatible with the Booking sub-type") ;

  if ( &bc != &BookingClass::ACFirstClass::Type() && &bc != &BookingClass::ACChairCar::Type() &&
       &bc != &BookingClass::AC2Tier::Type() && &bc != &BookingClass::AC3Tier::Type() &&
       &bc != &BookingClass::SecondSitting::Type() && &bc != &BookingClass::Sleeper::Type() && 
       &bc != &BookingClass::ExecutiveChairCar::Type() && &bc != &BookingClass::FirstClass::Type())
    throw Bad_Booking_BookingClass("Booking class must be valid") ;

  if ( ! bCat.IsElligible(p, dateOfBook) )
  {
    throw Bad_Booking_Passenger("Criteria to avail the specified booking category is not satisified") ;
  }

  // call private constructor for this Booking sub-type and return the constructed instance
  // the last lifeline in the virtual construction idiom
  return new Booking::DivyaangBooking(sFrom, sTo, dateOfBook, bc, bCat, p, dateOfRes) ; 
}

/////////////////////////////////////////////////////////////////////////////////////

// initialize static const data member
template<> 
const string Booking::TatkalBooking::sBookingType = "Tatkal" ;

// implement the business fare logic for Tatkal booking sub-type
// as given in the specifications
template<> 
unsigned int Booking::TatkalBooking::ComputeFare ( ) const
{
  unsigned int d = Railways::SpecialRailways().GetDistance(fromStation_, toStation_) ;
  double baseFare = d * Booking::sBaseFareRate ;
  double loadedFare = baseFare * bookingClass_.GetLoadFactor() ;
  double tatkalCharge = 0.00 ;
  if ( d >= bookingClass_.GetMinDistanceForTatkalCharge() ) // if the distance between terminals is less than the min distance for Tatkal charge
                                                            // then no charge will be levied
  {
    double basicFarePart = loadedFare * bookingClass_.GetTatkalCharge() ;
    if ( basicFarePart > bookingClass_.GetMaxTatkalCharge() ) // tatkal charge must not be greater than the max limit
      tatkalCharge = bookingClass_.GetMaxTatkalCharge() ;
    else 
      if ( basicFarePart < bookingClass_.GetMinTatkalCharge() )  // tatkal charge must not be lesser than the min limit
        tatkalCharge = bookingClass_.GetMinTatkalCharge() ;
      else
        tatkalCharge = basicFarePart ;
  }
  double total = loadedFare + tatkalCharge + bookingClass_.GetReservationCharge() ;
  return round(total) ;
}

template<>
const Booking::TatkalBooking * Booking::TatkalBooking::CreateSpecialBooking (  const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                                        const BookingClass & bc , const BookingCategory & bCat , const Passenger & p , 
                                                        const Date & dateOfRes ) 
{   
  // first of all, validate all the arguements as was done in Booking::SelectBooking
  try
  { Railways::SpecialRailways().GetDistance(sFrom, sTo) ; }
  catch(Bad_Railways_Distance)
  { throw Bad_Booking_UndefinedTerminals("Terminal stations are not connected in the Railways") ; }

  int diff = dateOfBook.GetDifferenceInDays(dateOfRes) ;
  if ( diff <= 0 )
    throw Bad_Booking_DateOfBooking("Date of booking must be after date of reservation") ;
  if ( diff > 365 )
    throw Bad_Booking_DateOfBooking("Date of booking must be within 1 year of date of reservation") ;

  if ( &bCat != &BookingCategory::Tatkal::Type() ) // BookingCategory sub-type must specifically match this sub-type 
    throw Bad_Booking_BookingCategory("Booking category is incompatible with the Booking sub-type") ;

  if ( &bc != &BookingClass::ACFirstClass::Type() && &bc != &BookingClass::ACChairCar::Type() &&
       &bc != &BookingClass::AC2Tier::Type() && &bc != &BookingClass::AC3Tier::Type() &&
       &bc != &BookingClass::SecondSitting::Type() && &bc != &BookingClass::Sleeper::Type() && 
       &bc != &BookingClass::ExecutiveChairCar::Type() && &bc != &BookingClass::FirstClass::Type())
    throw Bad_Booking_BookingClass("Booking class must be valid") ;

  if ( ! bCat.IsElligible(p, dateOfBook) )
  {
    throw Bad_Booking_Passenger("Criteria to avail the specified booking category is not satisified") ;
  }

  // call private constructor for this Booking sub-type and return the constructed instance
  // the last lifeline in the virtual construction idiom
  return new Booking::TatkalBooking(sFrom, sTo, dateOfBook, bc, bCat, p, dateOfRes) ; 
}

/////////////////////////////////////////////////////////////////////////////////////

// initialize static const data member
template<> 
const string Booking::PremiumTatkalBooking::sBookingType = "Premium Tatkal" ;

// implement the business fare logic for PremiumTatkal booking sub-type
// as given in the specifications
template<> 
unsigned int Booking::PremiumTatkalBooking::ComputeFare ( ) const
{
  unsigned int d = Railways::SpecialRailways().GetDistance(fromStation_, toStation_) ;
  double baseFare = d * Booking::sBaseFareRate ;
  double loadedFare = baseFare * bookingClass_.GetLoadFactor() ;
  double tatkalCharge = 0.00 ;
  if ( d >= bookingClass_.GetMinDistanceForTatkalCharge() ) // if the distance between terminals is less than the min distance for Tatkal charge
                                                            // then no charge will be levied
  {
    double basicFarePart = loadedFare * bookingClass_.GetTatkalCharge() ;
    if ( basicFarePart > bookingClass_.GetMaxTatkalCharge() ) // tatkal charge must not be greater than the max limit
      tatkalCharge = bookingClass_.GetMaxTatkalCharge() ;
    else 
      if ( basicFarePart < bookingClass_.GetMinTatkalCharge() ) // tatkal charge must not be lesser than the min limit
        tatkalCharge = bookingClass_.GetMinTatkalCharge() ;
      else
        tatkalCharge = basicFarePart ;
  }
  // whatever tatkal charge is computed that is for Tatkal booking category. In PremiumTatkal booking category
  // this charge has to be doubled (according to the specifications document). Hence, a factor of 2 is multiplied
  double total = loadedFare + 2 * tatkalCharge + bookingClass_.GetReservationCharge() ;
  return round(total) ;
}

template<>
const Booking::PremiumTatkalBooking * Booking::PremiumTatkalBooking::CreateSpecialBooking (  const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                                        const BookingClass & bc , const BookingCategory & bCat , const Passenger & p , 
                                                        const Date & dateOfRes ) 
{  
  // first of all, validate all the arguements as was done in Booking::SelectBooking
  try
  { Railways::SpecialRailways().GetDistance(sFrom, sTo) ; }
  catch(Bad_Railways_Distance)
  { throw Bad_Booking_UndefinedTerminals("Terminal stations are not connected in the Railways") ; }

  int diff = dateOfBook.GetDifferenceInDays(dateOfRes) ;
  if ( diff <= 0 )
    throw Bad_Booking_DateOfBooking("Date of booking must be after date of reservation") ;
  if ( diff > 365 )
    throw Bad_Booking_DateOfBooking("Date of booking must be within 1 year of date of reservation") ;

  if ( &bCat != &BookingCategory::PremiumTatkal::Type() ) // BookingCategory sub-type must specifically match this sub-type 
    throw Bad_Booking_BookingCategory("Booking category is incompatible with the Booking sub-type") ;

  if ( &bc != &BookingClass::ACFirstClass::Type() && &bc != &BookingClass::ACChairCar::Type() &&
       &bc != &BookingClass::AC2Tier::Type() && &bc != &BookingClass::AC3Tier::Type() &&
       &bc != &BookingClass::SecondSitting::Type() && &bc != &BookingClass::Sleeper::Type() && 
       &bc != &BookingClass::ExecutiveChairCar::Type() && &bc != &BookingClass::FirstClass::Type())
    throw Bad_Booking_BookingClass("Booking class must be valid") ;

  if ( ! bCat.IsElligible(p, dateOfBook) )
  {
    throw Bad_Booking_Passenger("Criteria to avail the specified booking category is not satisified") ;
  }

  // call private constructor for this Booking sub-type and return the constructed instance
  // the last lifeline in the virtual construction idiom
  return new Booking::PremiumTatkalBooking(sFrom, sTo, dateOfBook, bc, bCat, p, dateOfRes) ; 
}

/////////////////////////////////////////////////////////////////////////////////////

// In order to model the test case of checking the erroneous
// BookingClass type, an invalid BookingClass sub-type has to be introduced
// as given in the test plan document.
struct BookClassTestType { } ;    // placeholder for the invalid static sub-type of BookingClass
// give arbitrarily any values to the static data members for this invalid sub-type
template<>  const string BookingClassTypes<BookClassTestType>::sName = "Test" ;
template<>  const double BookingClassTypes<BookClassTestType>::sLoadFactor = false ;
template<>  const bool BookingClassTypes<BookClassTestType>::sIsSitting = false ;
template<>  const bool BookingClassTypes<BookClassTestType>::sIsAC = false ;
template<>  const bool BookingClassTypes<BookClassTestType>::sIsLuxury = false ;
template<>  const unsigned int BookingClassTypes<BookClassTestType>::sNumberOfTiers = 0 ;
template<>  const double BookingClassTypes<BookClassTestType>::sReservationCharge = 0.0 ;
template<>  const double BookingClassTypes<BookClassTestType>::sTatkalCharge = 0.0 ;
template<>  const double BookingClassTypes<BookClassTestType>::sMaxTatkalCharge = 0.0 ;
template<>  const double BookingClassTypes<BookClassTestType>::sMinTatkalCharge = 0.0 ;
template<>  const unsigned int BookingClassTypes<BookClassTestType>::sMinDistanceForTatkalCharge = 0 ;

// In order to model the test case of checking the erroneous
// BookingCategory type, an invalid BookingCategory sub-type has to be introduced
// as given in the test plan document.
struct BookCatTestType { } ;    // placeholder for the invalid static sub-type of BookingCategory
template<>  const string BookingCategoryTypes<BookCatTestType>::sName = "Test" ;  // arbitrary value for the static data member
template<>
bool BookingCategoryTypes<BookCatTestType>::IsElligible ( const Passenger & p , const Date & d ) const
{ return true ; } // return arbitrarily any constant value of appropriate data type

template<>
const Booking * BookingCategoryTypes<BookCatTestType>::SelectBooking
                                        ( const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                          const BookingClass & bc , const Passenger & p , const Date & dateOfRes ) const
{ return NULL ; } // return arbitrarily any constant value of appropriate data type

// implementation of the Unit Test Plan written for Booking hierarchy
void Booking::UnitTestBookingHierarchy ( )
{
  // TEST STATIC MEMBER FUNCTIONS -- Booking::CreateBooking
  // test the various scenarios for erroneous arguement values
  try // when the distance between the terminal stations is not defined
  {
    Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Pune"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(),
    BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane")) ;
  }
  catch ( Bad_Booking_UndefinedTerminals )
  { cout << "   TEST CASE J.1.1 PASSED" << endl ; }

  try // when the date of booking is in the past
  {
    Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/01/2021"), BookingClass::ACFirstClass::Type(),
    BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane")) ;
  }
  catch ( Bad_Booking_DateOfBooking )
  { cout << "   TEST CASE J.1.2.1 PASSED" << endl ; }

  try // when the date of booking is today
  {
    Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::GetTodaysDate(), BookingClass::ACFirstClass::Type(),
    BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane")) ;
  }
  catch ( Bad_Booking_DateOfBooking )
  { cout << "   TEST CASE J.1.2.2 PASSED" << endl ; }

  try // when the date of booking is after 1 year from today
  {
    Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("04/05/2022"), BookingClass::ACFirstClass::Type(),
    BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane")) ;
  }
  catch ( Bad_Booking_DateOfBooking )
  { cout << "   TEST CASE J.1.3 PASSED" << endl ; }

  try // when the BookingCategory sub-type is invalid
  {
    Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(),
    BookingCategoryTypes<BookCatTestType>::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane")) ;
  }
  catch ( Bad_Booking_BookingCategory )
  { cout << "   TEST CASE J.1.4 PASSED" << endl ; }

  try // when the BookingClass sub-type is invalid
  {
    Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClassTypes<BookClassTestType>::Type(),
    BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane")) ;
  }
  catch ( Bad_Booking_BookingClass )
  { cout << "   TEST CASE J.1.5 PASSED" << endl ; }

  try // when the Passenger is inelligible for the specified BookingCategory
  {
    Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(),
    BookingCategory::Ladies::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Male", "123456789012", "John")) ;
  }
  catch ( Bad_Booking_Passenger )
  { cout << "   TEST CASE J.1.6 PASSED" << endl ; }

  Passenger p = Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), 
                          "Female", "123456789012", "Jane", "", "", "", &Divyaang::Blind::Type()) ; // this passenger information is consistent with all 
                                                                                                    // the BookignCategory sub-types
  
  // call Booking::CreateBooking for all the BookingCategory sub-types
  const Booking * book1 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                          BookingClass::ACFirstClass::Type(), BookingCategory::General::Type(), p) ;
  if ( book1->fromStation_.GetName() == "Mumbai" && book1->toStation_.GetName() == "Delhi" && book1->dateOfBooking_ == Date::CreateDate("01/12/2021")
       && &book1->bookingClass_ == &BookingClass::ACFirstClass::Type() && &book1->bookingCategory_ == &BookingCategory::General::Type() && book1->pnr_ == 1
       && book1->passenger_ == p && book1->dateOfReservation_ == Date::GetTodaysDate() && book1->GetType() == "General" ) // check if all the data members are
                                                                                                                          // correctly initialized
    cout << "   TEST CASE J.1.7.1 PASSED" << endl ;
  delete book1 ;

  const Booking * book2 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                          BookingClass::ACFirstClass::Type(), BookingCategory::Ladies::Type(), p) ;
  if ( book2->fromStation_.GetName() == "Mumbai" && book2->toStation_.GetName() == "Delhi" && book2->dateOfBooking_ == Date::CreateDate("01/12/2021")
       && &book2->bookingClass_ == &BookingClass::ACFirstClass::Type() && &book2->bookingCategory_ == &BookingCategory::Ladies::Type() && book2->pnr_ == 2
       && book2->passenger_ == p && book2->dateOfReservation_ == Date::GetTodaysDate() && book2->GetType() == "Ladies" ) // check if all the data members are
                                                                                                                          // correctly initialized
    cout << "   TEST CASE J.1.7.2 PASSED" << endl ;
  delete book2 ;

  const Booking * book3 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                          BookingClass::ACFirstClass::Type(), BookingCategory::SeniorCitizen::Type(), p) ;
  if ( book3->fromStation_.GetName() == "Mumbai" && book3->toStation_.GetName() == "Delhi" && book3->dateOfBooking_ == Date::CreateDate("01/12/2021")
       && &book3->bookingClass_ == &BookingClass::ACFirstClass::Type() && &book3->bookingCategory_ == &BookingCategory::SeniorCitizen::Type() && book3->pnr_ == 3
       && book3->passenger_ == p && book3->dateOfReservation_ == Date::GetTodaysDate() && book3->GetType() == "Senior Citizen" ) // check if all the data members are
                                                                                                                                // correctly initialized
    cout << "   TEST CASE J.1.7.3 PASSED" << endl ;
  delete book3 ;

  const Booking * book4 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                          BookingClass::ACFirstClass::Type(), BookingCategory::Divyaang::Type(), p) ;
  if ( book4->fromStation_.GetName() == "Mumbai" && book4->toStation_.GetName() == "Delhi" && book4->dateOfBooking_ == Date::CreateDate("01/12/2021")
       && &book4->bookingClass_ == &BookingClass::ACFirstClass::Type() && &book4->bookingCategory_ == &BookingCategory::Divyaang::Type() && book4->pnr_ == 4
       && book4->passenger_ == p && book4->dateOfReservation_ == Date::GetTodaysDate() && book4->GetType() == "Divyaang" )   // check if all the data members are
                                                                                                                              // correctly initialized
    cout << "   TEST CASE J.1.7.4 PASSED" << endl ;
  delete book4 ;

  // the date of booking here should be changed based on the date of execution 
  // of this test case and accordingly the expected output will also change as
  // mentioned in the testplan document
  const Booking * book5 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("09/04/2021"), 
                          BookingClass::ACFirstClass::Type(), BookingCategory::Tatkal::Type(), p) ;
  if ( book5->fromStation_.GetName() == "Mumbai" && book5->toStation_.GetName() == "Delhi" && book5->dateOfBooking_ == Date::CreateDate("09/04/2021")
       && &book5->bookingClass_ == &BookingClass::ACFirstClass::Type() && &book5->bookingCategory_ == &BookingCategory::Tatkal::Type() && book5->pnr_ == 5
       && book5->passenger_ == p && book5->dateOfReservation_ == Date::GetTodaysDate() && book5->GetType() == "Tatkal" )   // check if all the data members are
                                                                                                                            // correctly initialized
    cout << "   TEST CASE J.1.7.5 PASSED" << endl ;
  delete book5 ;

  // the date of booking here should be changed based on the date of execution 
  // of this test case and accordingly the expected output will also change as
  // mentioned in the testplan document
  const Booking * book6 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("09/04/2021"), 
                          BookingClass::ACFirstClass::Type(), BookingCategory::PremiumTatkal::Type(), p) ;
  if ( book6->fromStation_.GetName() == "Mumbai" && book6->toStation_.GetName() == "Delhi" && book6->dateOfBooking_ == Date::CreateDate("09/04/2021")
       && &book6->bookingClass_ == &BookingClass::ACFirstClass::Type() && &book6->bookingCategory_ == &BookingCategory::PremiumTatkal::Type() && book6->pnr_ == 6
       && book6->passenger_ == p && book6->dateOfReservation_ == Date::GetTodaysDate() && book6->GetType() == "Premium Tatkal" ) // check if all the data members are
                                                                                                                                  // correctly initialized
    cout << "   TEST CASE J.1.7.6 PASSED" << endl ;
  delete book6 ;

  // TEST NON-STATIC MEMBER FUNCTIONS -- CreateSpecialBooking
  // check for all the test scenarios for erroneous arguement values for any one Booking sub-type
  try // when the distance betweeen the terminal stations is not defined
  {
    Booking::GeneralBooking::CreateSpecialBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Pune"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(),
    BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane"), Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_UndefinedTerminals )
  { cout << "   TEST CASE J.2.1 PASSED" << endl ; }

  try // when the date of booking is in the past
  {
    Booking::GeneralBooking::CreateSpecialBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/01/2021"), BookingClass::ACFirstClass::Type(),
    BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane"), Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_DateOfBooking )
  { cout << "   TEST CASE J.2.2.1 PASSED" << endl ; }

  try // when the date of booking is today
  {
    Booking::GeneralBooking::CreateSpecialBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::GetTodaysDate(), BookingClass::ACFirstClass::Type(),
    BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane"), Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_DateOfBooking )
  { cout << "   TEST CASE J.2.2.2 PASSED" << endl ; }

  try // when the date of booking is after 1 year from today
  {
    Booking::GeneralBooking::CreateSpecialBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("04/05/2022"), BookingClass::ACFirstClass::Type(),
    BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane"), Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_DateOfBooking )
  { cout << "   TEST CASE J.2.3 PASSED" << endl ; }

  try // when the BookingCategory sub-type is invalid
  {
    Booking::GeneralBooking::CreateSpecialBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(),
    BookingCategoryTypes<BookCatTestType>::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane"), Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_BookingCategory )
  { cout << "   TEST CASE J.2.4 PASSED" << endl ; }

  try // when the BookingCategory sub-type is valid but does not match the General Booking sub-type
  {
    Booking::GeneralBooking::CreateSpecialBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(),
    BookingCategory::Ladies::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane"), Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_BookingCategory )
  { cout << "   TEST CASE J.2.5 PASSED" << endl ; }

  try // when the BookingClass sub-type is invalid
  {
    Booking::GeneralBooking::CreateSpecialBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClassTypes<BookClassTestType>::Type(),
    BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane"), Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_BookingClass )
  { cout << "   TEST CASE J.2.6 PASSED" << endl ; }

  try // when the Passenger is not eligible for the specified BookingCtegory sub-type 
  {
    Booking::LadiesBooking::CreateSpecialBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(),
    BookingCategory::Ladies::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Male", "123456789012", "John"), Date::GetTodaysDate()) ;
  }
  catch ( Bad_Booking_Passenger )
  { cout << "   TEST CASE J.2.7 PASSED" << endl ; }

  // TEST NON-STATIC MEMBER FUNCTIONS -- GetType
  const Booking * book7 = Booking::LadiesBooking::CreateSpecialBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                          BookingClass::ACFirstClass::Type(), BookingCategory::Ladies::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", 
                          "123456789012", "Jane"), Date::GetTodaysDate()) ;
  if ( book7->GetType() == "Ladies" )
    cout << "   TEST CASE J.3.1 PASSED" << endl ;
  delete book7 ;

  // TEST NON-STATIC MEMBER FUNCTIONS -- ComputeFare
  // Create Booking objects of various sub-types, with various arguements/details as given in the testplan
  // Cover all the possible scenarios and compare the fare_ attribute of each object with the golden output
  const Booking * booking1 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Male", "123456789012", "John")) ;
  const Booking * booking2 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::AC3Tier::Type(), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Male", "123456789012", "John")) ;
  const Booking * booking4 = Booking::CreateBooking(Station::CreateStation("Chennai"), Station::CreateStation("Kolkata"), Date::CreateDate("01/12/2021"), BookingClass::FirstClass::Type(), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Male", "123456789012", "John")) ;
  const Booking * booking5 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(), BookingCategory::Ladies::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Female", "123456789012", "Jane")) ;
  const Booking * booking6 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::FirstClass::Type(), BookingCategory::Ladies::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2010"), "Male", "123456789012", "Jane")) ;
  const Booking * booking7 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(), BookingCategory::SeniorCitizen::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1961"), "Female", "123456789012", "Jane")) ;
  const Booking * booking8 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(), BookingCategory::SeniorCitizen::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1959"), "Male", "123456789012", "John")) ;
  const Booking * booking9 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::AC3Tier::Type(), BookingCategory::SeniorCitizen::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1959"), "Male", "123456789012", "John")) ;
  const Booking * booking10 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(), BookingCategory::Divyaang::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Male", "123456789012", "John", "", "", "", &Divyaang::Blind::Type())) ;
  const Booking * booking11 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(), BookingCategory::Divyaang::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Male", "123456789012", "John", "", "", "", &Divyaang::TBPatients::Type())) ;
  const Booking * booking12 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), BookingClass::AC2Tier::Type(), BookingCategory::Divyaang::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Male", "123456789012", "John", "", "", "", &Divyaang::Blind::Type())) ;
  const Booking * booking13 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("09/04/2021"), BookingClass::ACFirstClass::Type(), BookingCategory::Tatkal::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Male", "123456789012", "John")) ;
  const Booking * booking14 = Booking::CreateBooking(Station::CreateStation("Chennai"), Station::CreateStation("Bangalore"), Date::CreateDate("09/04/2021"), BookingClass::ACChairCar::Type(), BookingCategory::Tatkal::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Male", "123456789012", "John")) ;
  const Booking * booking15 = Booking::CreateBooking(Station::CreateStation("Chennai"), Station::CreateStation("Bangalore"), Date::CreateDate("09/04/2021"), BookingClass::ACFirstClass::Type(), BookingCategory::Tatkal::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Male", "123456789012", "John")) ;
  const Booking * booking16 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("09/04/2021"), BookingClass::ACFirstClass::Type(), BookingCategory::PremiumTatkal::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Male", "123456789012", "John")) ;
  const Booking * booking17 = Booking::CreateBooking(Station::CreateStation("Chennai"), Station::CreateStation("Bangalore"), Date::CreateDate("09/04/2021"), BookingClass::ACChairCar::Type(), BookingCategory::PremiumTatkal::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Male", "123456789012", "John")) ;
  const Booking * booking18 = Booking::CreateBooking(Station::CreateStation("Chennai"), Station::CreateStation("Bangalore"), Date::CreateDate("09/04/2021"), BookingClass::ACFirstClass::Type(), BookingCategory::PremiumTatkal::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Male", "123456789012", "John")) ;
  // the date of booking for the last 6 here should be changed based on the date of execution 
  // of this test case as mentioned in the testplan document

  // different scenarios of fare computation for GeneralBooking sub-type
  // match with golden output
  if ( booking1->fare_ == 4763 )  cout << "   TEST CASE J.3.2.1 PASSED" << endl ;
  if ( booking2->fare_ == 1849 )  cout << "   TEST CASE J.3.2.2 PASSED" << endl ;
  if ( booking4->fare_ == 2539 )  cout << "   TEST CASE J.3.2.3 PASSED" << endl ;

  // different scenarios of fare computation for LadiesBooking sub-type
  // match with golden output
  if ( booking5->fare_ == 4763 )  cout << "   TEST CASE J.3.3.1 PASSED" << endl ;
  if ( booking6->fare_ == 2221 )  cout << "   TEST CASE J.3.3.2 PASSED" << endl ;

  // different scenarios of fare computation for SeniorCitizenBooking sub-type
  // match with golden output
  if ( booking7->fare_ == 2411 )  cout << "   TEST CASE J.3.4.1 PASSED" << endl ;
  if ( booking8->fare_ == 2882 )  cout << "   TEST CASE J.3.4.2 PASSED" << endl ;
  if ( booking9->fare_ == 1125 )  cout << "   TEST CASE J.3.4.3 PASSED" << endl ;

  // different scenarios of fare computation for DivyaangBooking sub-type
  // match with golden output
  if ( booking10->fare_ == 2411 )  cout << "   TEST CASE J.3.5.1 PASSED" << endl ;
  if ( booking11->fare_ == 4763 )  cout << "   TEST CASE J.3.5.2 PASSED" << endl ;
  if ( booking12->fare_ == 1497 )  cout << "   TEST CASE J.3.5.3 PASSED" << endl ;

  // different scenarios of fare computation for TatkalBooking sub-type
  // match with golden output
  if ( booking13->fare_ == 5263 )  cout << "   TEST CASE J.3.6.1 PASSED" << endl ;
  if ( booking14->fare_ == 515 )  cout << "   TEST CASE J.3.6.2 PASSED" << endl ;
  if ( booking15->fare_ == 1198 )  cout << "   TEST CASE J.3.6.3 PASSED" << endl ;

  // different scenarios of fare computation for PremiumTatkalBooking sub-type
  // match with golden output
  if ( booking16->fare_ == 5763 )  cout << "   TEST CASE J.3.7.1 PASSED" << endl ;
  if ( booking17->fare_ == 640 )  cout << "   TEST CASE J.3.7.2 PASSED" << endl ;
  if ( booking18->fare_ == 1198 )  cout << "   TEST CASE J.3.7.3 PASSED" << endl ;

  delete booking1 ; delete booking2 ; delete booking4 ; delete booking5 ;
  delete booking6 ; delete booking7 ; delete booking8 ; delete booking9 ;
  delete booking10 ; delete booking11 ; delete booking12 ; delete booking13 ;
  delete booking14 ; delete booking15 ; delete booking16 ; delete booking17 ;
  delete booking18 ;

  const Booking * booking19 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                              BookingClass::ACFirstClass::Type(), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), 
                              "Male", "123456789012", "John", "Jack", "Doe", "9874563210", &Divyaang::CancerPatients::Type(), "ABC987")) ;
  // print an instance of Booking sub-type onto the console using the overloaded output streaming operator
  cout << "   TEST CASE J.4.1 -- " << *booking19 << endl ;
  delete booking19 ;
  
  // test dynamic dispatch of all the polymorphic methods 
  const Booking * booking20 = Booking::LadiesBooking::CreateSpecialBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), 
                              Date::CreateDate("01/12/2021"), BookingClass::ACFirstClass::Type(), BookingCategory::Ladies::Type(), 
                              Passenger::CreatePassenger(Date::CreateDate("01/01/1956"), "Female", "123456789012", "Jane"), Date::GetTodaysDate()) ;
                                  // upcast the Booking sub-type instance to the "const Booking*"
  if ( booking20->GetType() == "Ladies" ) // call the polymorphic method 'GetType' on it
    cout << "   TEST CASE J.5.1 PASSED" << endl ;
  delete booking20 ;

  const Booking * booking21 = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                              BookingClass::ACFirstClass::Type(), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), "Male", 
                              "123456789012", "John")) ;
                              // upcast the Booking sub-type instance to the "const Booking*"
  if ( booking21->ComputeFare() == 4763 ) // call the polymorphic method 'ComputeFare' on it
    cout << "   TEST CASE J.5.2 PASSED" << endl ;
  delete booking21 ;

}
