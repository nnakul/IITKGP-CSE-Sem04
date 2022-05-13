
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <vector>
#include <cmath>
#include "Booking.h"
#include "Exceptions.h"
using namespace std ;

// Implementing the test application
void ApplicationTestPlan ( ) ;

int main ( )
{
    cout << "\n\n\t+++ ENTERED main +++\n" ;
    ApplicationTestPlan() ;
    cout << "\n\t+++ EXITING main +++\n\n" ;
    return 0 ;
}

// In order to model the test case of checking the erroneous
// disability type, an invalid Divyaang sub-type has to be introduced
// as given in the test plan document. 
struct AppTestDiv { } ;    // placeholder for the invalid static sub-type
// NOW DEFINE THE NECESSARY MEMBERS OF THE CLASS INSTANCE OF THE TEMPLATE WITH ARGUEMENT DivTestType
// give arbitrary values to the static const data members
template<> const string DivyaangTypes<AppTestDiv>::sName = "Invalid" ;
template<> const map<string, double> DivyaangTypes<AppTestDiv>::sConcessionFactors = { } ;
template <>
double DivyaangTypes<AppTestDiv>::GetConcessionFactor ( const BookingClass & b ) const
{ return 0.0 ; }    // return an arbitrary value

// In order to model the test case of checking the erroneous
// BookingClass type, an invalid BookingClass sub-type has to be introduced
// as given in the test plan document.
struct AppTestBookClass { } ;     // placeholder for the invalid static sub-type of BookingClass
// give arbitrarily any values to the static data members for this invalid sub-type
template<>  const string BookingClassTypes<AppTestBookClass>::sName = "Invalid" ;
template<>  const double BookingClassTypes<AppTestBookClass>::sLoadFactor = false ;
template<>  const bool BookingClassTypes<AppTestBookClass>::sIsSitting = false ;
template<>  const bool BookingClassTypes<AppTestBookClass>::sIsAC = false ;
template<>  const bool BookingClassTypes<AppTestBookClass>::sIsLuxury = false ;
template<>  const unsigned int BookingClassTypes<AppTestBookClass>::sNumberOfTiers = 0 ;
template<>  const double BookingClassTypes<AppTestBookClass>::sReservationCharge = 0.0 ;
template<>  const double BookingClassTypes<AppTestBookClass>::sTatkalCharge = 0.0 ;
template<>  const double BookingClassTypes<AppTestBookClass>::sMaxTatkalCharge = 0.0 ;
template<>  const double BookingClassTypes<AppTestBookClass>::sMinTatkalCharge = 0.0 ;
template<>  const unsigned int BookingClassTypes<AppTestBookClass>::sMinDistanceForTatkalCharge = 0 ;

// In order to model the test case of checking the erroneous
// BookingCategory type, an invalid BookingCategory sub-type has to be introduced
// as given in the test plan document.
struct AppTestBookCat { } ;    // placeholder for the invalid static sub-type of BookingCategory
template<>  const string BookingCategoryTypes<AppTestBookCat>::sName = "Invalid" ;  // arbitrary value for the static data member
template<>
bool BookingCategoryTypes<AppTestBookCat>::IsElligible ( const Passenger & p , const Date & d ) const
{ return true ; } // return arbitrarily any constant value of appropriate data type

template<>
const Booking * BookingCategoryTypes<AppTestBookCat>::SelectBooking
                                        ( const Station & sFrom , const Station & sTo , const Date & dateOfBook, 
                                          const BookingClass & bc , const Passenger & p , const Date & dateOfRes ) const
{ return NULL ; } // return arbitrarily any constant value of appropriate data type

// IMPLEMENTATION OF THE APPLICATION TEST PLAN as given in the test plan document
void ApplicationTestPlan ( )
{
    cout << "\n\t+++ WELCOME TO TEST BOOKING APPLICATION +++\n\n" ;
    vector<const Booking*> testBookings = { } ; // stores the pointers to all the constructed Booking sub-types so that they can
                                                // be deleted conviniently at the end
    vector<const BookingClass*> bookingClasses = {  // store the addresses of the singleton instances of all the BookingClass sub-types
        &BookingClass::ACFirstClass::Type(),
        &BookingClass::ExecutiveChairCar::Type(),
        &BookingClass::AC2Tier::Type(),
        &BookingClass::FirstClass::Type(),
        &BookingClass::AC3Tier::Type(),
        &BookingClass::ACChairCar::Type(),
        &BookingClass::Sleeper::Type(),
        &BookingClass::SecondSitting::Type()
    } ;

    // Create bookings exhaustively covering all the BookingClass sub-types
    for ( const BookingClass * bc : bookingClasses )
    {
        const Booking * b = Booking::CreateBooking(Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                            *bc, BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), 
                            "Male", "123456789012", "John")) ;
        testBookings.push_back(b) ;
        cout << *b ;
    }
    
    // store the names of all the Stations in the default Indian Railways
    vector<string> stationNames = { "Mumbai" , "Delhi" , "Bangalore" , "Kolkata" , "Chennai" } ;
    // Create bookings exhaustively covering all the 20 ordered pairs of distinct terminal stations
    for ( unsigned i=0 ; i<5 ; i++ )
        for ( unsigned j=i+1 ; j<5 ; j++ )
        {
            const BookingClass * bc = bookingClasses.at(rand()%8) ; // choose any arbitrary BookingClass sub-type
            const Booking * b1 = Booking::CreateBooking(Station::CreateStation(stationNames.at(i)), Station::CreateStation(stationNames.at(j)), Date::CreateDate("01/12/2021"), 
                                *bc, BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), 
                                "Male", "123456789012", "John")) ;
            testBookings.push_back(b1) ;
            cout << *b1 ;

            const Booking * b2 = Booking::CreateBooking(Station::CreateStation(stationNames.at(j)), Station::CreateStation(stationNames.at(i)), Date::CreateDate("01/09/2021"), 
                                *bc, BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), 
                                "Female", "123456789012", "Jane")) ;
            testBookings.push_back(b2) ;
            cout << *b2 ;
        }

    // Create bookings exhaustively covering all the BookingCategory sub-types and there various scenarios
    const Booking * b ;
    b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), 
                                "Male", "123456789012", "John")) ;
    testBookings.push_back(b) ;
    cout << *b ;

    b = Booking::CreateBooking( Station::CreateStation("Kolkata"), Station::CreateStation("Mumbai"), Date::CreateDate("01/12/2021"), 
                                *bookingClasses.at(rand()%8), BookingCategory::Ladies::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2011"), 
                                "Male", "123456789012", "John")) ;
    testBookings.push_back(b) ;
    cout << *b ;

    b = Booking::CreateBooking( Station::CreateStation("Delhi"), Station::CreateStation("Mumbai"), Date::CreateDate("01/12/2021"), 
                                *bookingClasses.at(rand()%8), BookingCategory::Ladies::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), 
                                "Female", "123456789012", "Jane")) ;
    testBookings.push_back(b) ;
    cout << *b ;

    b = Booking::CreateBooking( Station::CreateStation("Kolkata"), Station::CreateStation("Bangalore"), Date::CreateDate("01/12/2021"), 
                                *bookingClasses.at(rand()%8), BookingCategory::SeniorCitizen::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1960"), 
                                "Male", "123456789012", "John")) ;
    testBookings.push_back(b) ;
    cout << *b ;

    b = Booking::CreateBooking( Station::CreateStation("Kolkata"), Station::CreateStation("Chennai"), Date::CreateDate("01/12/2021"), 
                                *bookingClasses.at(rand()%8), BookingCategory::SeniorCitizen::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1961"), 
                                "Female", "123456789012", "Jane")) ;
    testBookings.push_back(b) ;
    cout << *b ;

    vector<const Divyaang*> disabilityTypes = { // store the addresses of the singleton instances of all the Divyaang sub-types
        &Divyaang::Blind::Type(),
        &Divyaang::OrthopaedicallyHandicapped::Type(),
        &Divyaang::TBPatients::Type(),
        &Divyaang::CancerPatients::Type()
    } ;

    // for Divyaang booking category, exhaustively cover all the 4 Divyaang sub-types
    for ( const Divyaang * d : disabilityTypes )
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::Divyaang::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John", "", "", "", d)) ;
        testBookings.push_back(b) ;
        cout << *b ;
    }

    // the date of booking here should be changed based on the date of execution 
    // of this test case as mentioned in the testplan document
    b = Booking::CreateBooking( Station::CreateStation("Bangalore"), Station::CreateStation("Delhi"), Date::CreateDate("10/04/2021"), 
                                *bookingClasses.at(rand()%8), BookingCategory::Tatkal::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                "Male", "123456789012", "John")) ;
    testBookings.push_back(b) ;
    cout << *b ;

    // the date of booking here should be changed based on the date of execution 
    // of this test case as mentioned in the testplan document
    b = Booking::CreateBooking( Station::CreateStation("Bangalore"), Station::CreateStation("Delhi"), Date::CreateDate("10/04/2021"), 
                                *bookingClasses.at(rand()%8), BookingCategory::PremiumTatkal::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                "Male", "123456789012", "John")) ;
    testBookings.push_back(b) ;
    cout << *b ;

    // test for various erroneous scenarios concerning the Passenger information
    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012")) ;
    }   // when none of the first and last name is given
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "12345678901", "John")) ;
    }   // when the adhaar no. has less than 12 digits
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "1234567890123", "John")) ;
    }   // when the adhaar no. has more than 12 digits
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "12345678901A", "John")) ;
    }   // when the adhaar no. has non-digits
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }
    
    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John", "", "", "987456321")) ;
    }   // when the mobile no. has less than 10 digits
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John", "", "", "98745632100")) ;
    }   // when the mobile no. has more than 10 digits
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John", "", "", "987456321A")) ;
    }   // when the mobile no. has non-digits
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2023"), 
                                    "Male", "123456789012", "John")) ;
    }   // when the date of birth is in future
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John", "", "", "", &DivyaangTypes<AppTestDiv>::Type())) ;
    }   // when the disability type is invalid
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Others", "123456789012", "John")) ;
    }   // when the specified gender is neither Male nor Female
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    // test for various erroneous scenarios concerning the Booking information
    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Pune"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John")) ;
    }   // distance between the terminal stations is not defined
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Delhi"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John")) ;
    }   // the terminal stations are not distinct
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("02/04/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John")) ;
    }   // date of booking is in past
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::GetTodaysDate(), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John")) ;
    }   // date of booking is today
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/09/2022"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John")) ;
    }   // date of booking is after 1 year from todays
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    BookingClassTypes<AppTestBookClass>::Type(), BookingCategory::General::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John")) ;
    }   // BookingClass sub-type is invalid
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Mumbai"), Station::CreateStation("Delhi"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategoryTypes<AppTestBookCat>::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John")) ;
    }   // BookingCategory sub-type is invalid
    catch ( const exception & e )
    { cout << "\n ERROR : " << e.what() << "\n\n" ; }


    // Now for eligibility, test for eligibility failure for every Booking sub-type
    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Chennai"), Station::CreateStation("Bangalore"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::Ladies::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2000"), 
                                    "Male", "123456789012", "John")) ;
    }
    catch ( const exception & e )   // elligibility failure for Ladies
    { cout << "\n ERROR : " << e.what() << " for Ladies\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Chennai"), Station::CreateStation("Bangalore"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::SeniorCitizen::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1962"), 
                                    "Male", "123456789012", "John")) ;
    }
    catch ( const exception & e )   // elligibility failure for SeniorCitizen -- when Passenger is Male
    { cout << "\n ERROR : " << e.what() << " for SeniorCitizen\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Chennai"), Station::CreateStation("Bangalore"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::SeniorCitizen::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/1964"), 
                                    "Female", "123456789012", "Jane")) ;
    }
    catch ( const exception & e )   // elligibility failure for SeniorCitizen -- when Passenger is Female
    { cout << "\n ERROR : " << e.what() << " for SeniorCitizen\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Chennai"), Station::CreateStation("Bangalore"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::Divyaang::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John")) ;
    }
    catch ( const exception & e )   // elligibility failure for Divyaang
    { cout << "\n ERROR : " << e.what() << " for Divyaang\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Chennai"), Station::CreateStation("Bangalore"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::Tatkal::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John")) ;
    }
    catch ( const exception & e )  // elligibility failure for Tatkal
    { cout << "\n ERROR : " << e.what() << " for Tatkal\n\n" ; }

    try
    {
        b = Booking::CreateBooking( Station::CreateStation("Chennai"), Station::CreateStation("Bangalore"), Date::CreateDate("01/12/2021"), 
                                    *bookingClasses.at(rand()%8), BookingCategory::PremiumTatkal::Type(), Passenger::CreatePassenger(Date::CreateDate("01/01/2019"), 
                                    "Male", "123456789012", "John")) ;
    }
    catch ( const exception & e )  // elligibility failure for PremiumTatkal
    { cout << "\n ERROR : " << e.what() << " for PremiumTatkal\n\n" ; }

    for ( const Booking * b : testBookings )    // delete all the instances Booking sub-types
    { cout << endl ; delete b ; cout << endl ; }

    cout << "\n\n\t+++ GOODBYE FROM TEST BOOKING APPLICATION +++\n" ;
    return ;
}