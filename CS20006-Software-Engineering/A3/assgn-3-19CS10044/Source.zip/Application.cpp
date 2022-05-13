
//  SOFTWARE ENGINEERING -- ASSIGNMENT O3
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "Booking.h"
using namespace std ;


//  COMPILATION AND LINKING COMMANDS
//  g++ -c Application.cpp Booking.cpp BookingClass.cpp Date.cpp Passenger.cpp Railways.cpp Station.cpp
//  g++ -o app.exe Application.o Booking.o BookingClass.o Date.o Passenger.o Station.o Railways.o
//  app.exe


// Test Application given in Section-C of assignment
void BookingApplication ( ) ;
// Use the default "Indian Railways" as the singleton 'Railways' instance
void ApplicationTestO1 ( ) ;
// Use any custom railways as the singleton 'Railways' instance
void ApplicationTestO2 ( ) ;

int main ( )
{
  BookingApplication() ;
  return 0 ;
}

// Test Application given in Section-C of assignment
void BookingApplication ( )
{
  Booking b1 (Station("Mumbai"), Station("Delhi"), Date(15, 2, 2021), BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass()) ;
  Booking b2 (Station("Kolkata"), Station("Delhi"), Date(5, 3, 2021), BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass()) ;
  Booking b3 (Station("Mumbai"), Station("Kolkata"), Date(17, 3, 2021), BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass()) ;
  Booking b4 (Station("Mumbai"), Station("Delhi"), Date(23, 3, 2021), BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass()) ;
  Booking b5 (Station("Chennai"), Station("Delhi"), Date(25, 4, 2021), BookingClassSeatNoTierAcOrdinary::SpecialBookingClass()) ;
  Booking b6 (Station("Chennai"), Station("Kolkata"), Date(7, 5, 2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()) ;
  Booking b7 (Station("Mumbai"), Station("Delhi"), Date(19, 5, 2021), BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass()) ;
  Booking b8 (Station("Delhi"), Station("Mumbai"), Date(22, 5, 2021), BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass()) ;
  
  vector<const Booking*>::iterator it ;
  for (it = Booking::sBookings.begin(); it < Booking::sBookings.end(); ++it)
    cout << *(*it) ;
  return ;
}

// Use the default "Indian Railways" as the singleton 'Railways' instance
void ApplicationTestO1 ( )
{
  // names of all the stations in the default "Indian Railways" network
  vector<string> stationNames = { "Mumbai" , "Delhi" , "Kolkata" , "Bangalore" , "Chennai" } ;
  
  // IN THIS PART, DO NOT USE OBJECTS OF Passenger CLASS
  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassBerthDoubleTierAcLuxury" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }

  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassBerthDoubleTierAcOrdinary" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }
  
  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassBerthDoubleTierNonAcLuxury" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }
  
  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassBerthTripleTierAcOrdinary" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }

  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassSeatNoTierAcOrdinary" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassSeatNoTierAcOrdinary::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }

  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassBerthTripleTierNonAcOrdinary" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }

  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassSeatNoTierNonAcOrdinary" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }
  
  // IN THIS PART WE ALSO USE Passenger OBJECTS IN INSTANTIATING Booking
  // Construct 8 Passenger objects while trying to maintain variety in the
  // parameters (cover all values for the enumerated data types 'Passenger::Gender'
  // and 'Passenger::Category'; pass the sixth parameter for few and not for others)
  Passenger p1("Aman Bansal", "1212 4334 6101", Date(1,4,1999), Passenger::Gender::Male, Passenger::Category::General) ;
  Passenger p2("Tanu Goyal", "4916 6700 2758", Date(28, 11, 1998), Passenger::Gender::Female, Passenger::Category::Tatkaal, "8194423856") ;
  Passenger p3("Shekhar Mukherjee", "2500 3649 1211", Date(5, 7), Passenger::Gender::Male, Passenger::Category::SeniorCitizen) ;
  Passenger p4("Kaushik Rao", "1671 5233 4577", Date(14, 9, 2001), Passenger::Gender::Male, Passenger::Category::PremiumTatkaal, "7452196588") ;
  Passenger p5("Sudeshna Roy", "5306 9744 1200", Date(17,1,1992), Passenger::Gender::Female, Passenger::Category::Ladies, "9452360014") ;
  Passenger p6("Radhika Gandhi", "6317 5233 5000", Date(20, 6, 1989), Passenger::Gender::Female, Passenger::Category::Tatkaal, "7996002896") ;
  Passenger p7("Avadhesh Pratap", "7544 9877 2565", Date(31, 1, 1994), Passenger::Gender::Male, Passenger::Category::Divyaang, "8541636758") ;
  Passenger p8("Anjali Mahajan", "2003 6974 5522", Date(19, 3, 2000), Passenger::Gender::Female, Passenger::Category::General, "7236314207") ;

  // Construct 8 objects of 'Booking' class, using pointers to different 'Passenger' objects,
  // covering all the booking-classes and using variety of pairs of terminal stations.
  Booking b1 (Station("Mumbai"), Station("Delhi"), Date(15, 2, 2021), BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass(), &p1) ;
  Booking b2 (Station("Kolkata"), Station("Delhi"), Date(5, 3, 2021), BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass(), &p2) ;
  Booking b3 (Station("Bangalore"), Station("Kolkata"), Date(17, 3, 2021), BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass(), &p3) ;
  Booking b4 (Station("Mumbai"), Station("Chennai"), Date(23, 3, 2021), BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass(), &p4) ;
  Booking b5 (Station("Chennai"), Station("Delhi"), Date(25, 4, 2021), BookingClassSeatNoTierAcOrdinary::SpecialBookingClass(), &p5) ;
  Booking b6 (Station("Chennai"), Station("Kolkata"), Date(7, 5, 2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass(), &p6) ;
  Booking b7 (Station("Bangalore"), Station("Delhi"), Date(19, 5, 2021), BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass(), &p7) ;
  Booking b8 (Station("Delhi"), Station("Chennai"), Date(22, 5, 2021), BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass(), &p8) ;
  
  // Iterate over the static data member 'Booking::sBookings' and print all the 8 'Booking'
  // instances using the overloaded output streaming operator
  vector<const Booking*>::iterator it ;
  for (it = Booking::sBookings.begin(); it < Booking::sBookings.end(); ++it)
    cout << *(*it) ;
  
  return ;
}

// Use any custom railways as the singleton 'Railways' instance
void ApplicationTestO2 ( )
{
  // names of all the stations in the custom "European Railways" network
  vector<string> stationNames = { "Amsterdam" , "Berlin" , "Brussels" , "Athens" } ;
  // vector of Station objects in the "European Railways" network
  const vector<Station> stations = { Station("Amsterdam"), Station("Berlin"), Station("Brussels"), Station("Athens") } ;
  // map storing pairwise distances between stations of "European Railways"
  const map<pair<string, string>, int> pairwiseDistances = {
                                                                      { {"Amsterdam", "Berlin"}, 649 } ,
                                                                      { {"Amsterdam", "Brussels"}, 209 } ,
                                                                      { {"Amsterdam", "Athens"}, 3082 } ,
                                                                      { {"Athens", "Berlin"}, 2552 } ,
                                                                      { {"Athens", "Brussels"}, 3021 } ,
                                                                      { {"Berlin", "Brussels"}, 782 }     } ;

  // First call to "Railways::SpecialRailways". Constructs the singleton 'Railways'
  // instance with the passed parameters
  Railways::SpecialRailways(stations, pairwiseDistances) ;

  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassBerthDoubleTierAcLuxury" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }

  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassBerthDoubleTierAcOrdinary" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }
  
  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassBerthDoubleTierNonAcLuxury" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }
  
  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassBerthTripleTierAcOrdinary" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }

  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassSeatNoTierAcOrdinary" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassSeatNoTierAcOrdinary::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }

  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassBerthTripleTierNonAcOrdinary" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }

  // run double-loop to exhaustively construct all 'Booking' objects with the booking-class
  // "BookingClassSeatNoTierNonAcOrdinary" (ignoring the difference due to date of travel)
  // (Using iterator to iterate over 'stationNames' in place of bare "for" loop)
  for ( const string & sFrom : stationNames )
    for ( const string & sTo : stationNames )
    {
      if ( sFrom == sTo ) continue ;  // two terminal stations cannot be the same
      // any random date in the future
      unsigned int date = rand() % 28 + 1 ;
      unsigned int month = rand() % 9 + 4 ;
      Booking booking( Station(sFrom) , Station(sTo) , Date(date, month, 2021) , 
        BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass() ) ;  // construct
      cout << booking ;   // output stream
    }
  
  return ;
}
