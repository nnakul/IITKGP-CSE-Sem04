
//  SOFTWARE ENGINEERING -- ASSIGNMENT O3
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Booking.h"
using namespace std ;

unsigned int Booking::sBookingPNRSerial = 1 ;     // the serial PNR number starts with 1
vector<const Booking*> Booking::sBookings = { } ; // initially there are NO instances of 'Booking' class

// intialize static constants from the data given in the assignment
const double Booking::sBaseFarePerKM = 0.5 ;
const double Booking::sACSurcharge = 50.00  ;
const double Booking::sLuxuryTaxPercent = 25.00 ;

Booking::Booking ( const Station & sFrom , const Station & sTo , const Date & date , const BookingClass & bClass , const Passenger * p )
     // initializer-list
    :   fromStation_(sFrom) , toStation_(sTo) , dateOfTravel_(date) , bookingClass_(&bClass) , passenger_(p) ,
        pnr_(sBookingPNRSerial++)      ,     bookingStatus_(true)      ,      bookingMessage_("BOOKING SUCCEEDED")
//     'Booking::sBookingPNRSerial'        This data member is always           This data member is always "BOOKING 
//      has to be incremented by 1             true for this version                 SUCCEEDED" for this version
{
    fare_ = ComputeFair() ;   // use the algorithm written in 'Booking::ComputeFair' to compute fair
    sBookings.push_back(this) ;    // push pointer to the newly constructed 'Booking' instance into the static vector 'Booking::sBookings'
}

Booking::Booking ( const Booking & b )  // copy constructor
    :   fromStation_(b.fromStation_) , toStation_(b.toStation_) , dateOfTravel_(b.dateOfTravel_) , bookingClass_(b.bookingClass_) ,
        pnr_(sBookingPNRSerial++) , bookingStatus_(b.bookingStatus_) , fare_(b.fare_) , bookingMessage_(b.bookingMessage_) , passenger_(b.passenger_)
// All data members except 'Booking::pnr_' are copied from parameter. 'Booking::pnr_' must be assigned the value of 'Booking::sBookingPNRSerial'
// and then the latter must be incremented by 1; same as before
{ sBookings.push_back(this) ;  }    // push pointer to the newly constructed 'Booking' instance into the static vector 'Booking::sBookings'

Booking & Booking::operator =  ( const Booking & b )  // overloaded copy assignment operator '='
{
     // copy all the data members, including 'Booking::pnr_'
    fromStation_ = b.fromStation_ ; toStation_ = b.toStation_ ; dateOfTravel_ = b.dateOfTravel_ ;
    bookingClass_ = b.bookingClass_ ; pnr_ = b.pnr_ , bookingStatus_ = b.bookingStatus_ , fare_ = b.fare_ ;
    bookingMessage_ = b.bookingMessage_ ; passenger_ = b.passenger_ ;
    return *this ;     // return the instance to which the parameter 
                       // is copied to enable chained assignment operations
}

int Booking::ComputeFair ( ) const
{
     // implement fare computation algorithm; same as given in the assignment
    int dist = Railways::SpecialRailways().GetDistance(fromStation_, toStation_) ;   // use public 'Railways::GetDistance' method
    double baseFare = dist * Booking::sBaseFarePerKM ; 
    double loadedFare = baseFare * ( bookingClass_->GetLoadFactor() ) ;              // use public polymorphic method 'BookingClass::GetLoadFactor'
    if ( bookingClass_->IsAC() )    loadedFare += Booking::sACSurcharge ;            // use public polymorphic method 'BookingClass::IsAC'
    if ( bookingClass_->IsLuxury() )    loadedFare *= ( 1.0 + Booking::sLuxuryTaxPercent / 100.0 ) ;     // use public polymorphic method 'BookingClass::IsLuxury'
    return round(loadedFare) ;     // return total fare rounded off to the nearest integer
}

ostream & operator << ( ostream & out , const Booking & booking ) // overloaded output streaming operator
{
     // print all the details of a 'Booking' instance
    out << endl << " " << booking.bookingMessage_ << " :" << endl ;
    out << " PNR Number = " << booking.pnr_ << endl ;
    out << " From Station = " << booking.fromStation_.GetName() << endl ;                 // use public 'Station::GetName' method
    out << " To Station = " << booking.toStation_.GetName() << endl ;                     // use public 'Station::GetName' method
    out << " Travel Date = " << booking.dateOfTravel_ << endl ;                           // use "std::ostream &operator<<(std::ostream&, const Date&)"
    out << " Travel Class = " << booking.bookingClass_->GetName() << endl ;               // use public polymorphic method 'BookingClass::GetName'
    if ( booking.bookingClass_->IsSitting() )   out << " : Mode : Sitting" << endl ;      // use public polymorphic method 'BookingClass::IsSitting'
    else    out << " : Mode : Sleeping" << endl ;
    if ( booking.bookingClass_->IsAC() )   out << " : Comfort : AC" << endl ;             // use public polymorphic method 'BookingClass::IsAC'
    else    out << " : Comfort : Non-AC" << endl ;
    out << " : Bunks : " << booking.bookingClass_->GetNumberOfTiers() << endl ;           // use public polymorphic method 'BookingClass::GetNumberOfTiers'
    if ( booking.bookingClass_->IsLuxury() )   out << " : Luxury : Yes" << endl ;         // use public polymorphic method 'BookingClass::IsLuxury'
    else    out << " : Luxury : No" << endl ;
    out << " Fare = " << booking.fare_ ;
    if ( booking.passenger_ )
    {
         out << endl << " " << "PASSENGER DETAILS" << " :" ;
         out << *(booking.passenger_) ;     // use "std::ostream &operator<<(std::ostream &, const Passenger &)"
    }   
    else  out << endl ;
    return out ;    // returning the 'ostream' object is important for streaming 
                    // of multiple instances chained in the same instruction
}


Booking::~Booking ( )    // destructor
{ sBookings.erase( find(sBookings.begin(), sBookings.end(), this) ) ;  }
// It is very important to update the static data member 'Booking::sBookings' everytime a 'Booking' instance
// is destructed, by removing the pointer to that instance from the vector.


void Booking::UnitTestBooking ( )
{
    cout << "\n\n   [ Booking::UnitTestBooking ( ) ]" << endl ;
    bool allPassed = true ;

     // TEST 1 : Check if the static constant data members were correcly initialized
     // match their values with the master data
    if ( sBaseFarePerKM != 0.5 || sACSurcharge != 50.00 || sLuxuryTaxPercent != 25.00 )
    { cout << "Static constants of the class 'Booking' do not all have the intended values" << endl ; allPassed = false ;  }

     // TEST 2 : Construction
     // construct 7 instances of 'Booking' class with different booking-classes while keeping track of the static data member 'Booking::sBookingPNRSerial'
    unsigned int pNRSerialBeforeAnything = Booking::sBookingPNRSerial ;
    Booking b1 = Booking(Station("Mumbai"), Station("Delhi"), Date(1,5,2021), BookingClassSeatNoTierAcOrdinary::SpecialBookingClass()) ;
    unsigned int pNRSerialAfterb1 = Booking::sBookingPNRSerial ;
    Booking b2 = Booking(Station("Mumbai"), Station("Delhi"), Date(1,5,2021), BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass()) ;
    unsigned int pNRSerialAfterb2 = Booking::sBookingPNRSerial ;
    Booking b3 = Booking(Station("Mumbai"), Station("Delhi"), Date(1,5,2021), BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass()) ;
    unsigned int pNRSerialAfterb3 = Booking::sBookingPNRSerial ;
    Booking b4 = Booking(Station("Mumbai"), Station("Delhi"), Date(1,5,2021), BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass()) ;
    unsigned int pNRSerialAfterb4 = Booking::sBookingPNRSerial ;
    Booking b5 = Booking(Station("Mumbai"), Station("Delhi"), Date(1,5,2021), BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass()) ;
    unsigned int pNRSerialAfterb5 = Booking::sBookingPNRSerial ;
    Booking b6 = Booking(Station("Mumbai"), Station("Delhi"), Date(1,5,2021), BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass()) ;
    unsigned int pNRSerialAfterb6 = Booking::sBookingPNRSerial ;
    Booking b7 = Booking(Station("Mumbai"), Station(Station("Delhi")), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()) ;
    unsigned int pNRSerialAfterb7 = Booking::sBookingPNRSerial ;

     // check all the attributes (except 'Booking::pnr_') of each and every instance and ensure that they assigned correctly
     // (here the overloaded relational operators for 'Station' and 'Date' come in very handy)
    if ( b1.bookingClass_ != &BookingClassSeatNoTierAcOrdinary::SpecialBookingClass()
         || b1.fromStation_ != Station("Mumbai")
         || b1.toStation_ != Station("Delhi")
         || b1.dateOfTravel_ != Date(1,5,2021) || b1.passenger_ != NULL )
    {   cout << "Booking Construction Error on Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassSeatNoTierAcOrdinary::SpecialBookingClass())" << endl ; allPassed = false ; }

    if ( b2.bookingClass_ != &BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass()
         || b2.fromStation_ != Station("Mumbai")
         || b2.toStation_ != Station("Delhi")
         || b2.dateOfTravel_ != Date(1,5,2021) || b2.passenger_ != NULL )
    {   cout << "Booking Construction Error on Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass())" << endl ; allPassed = false ; }

    if ( b3.bookingClass_ != &BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass() 
         || b3.fromStation_ != Station("Mumbai")
         || b3.toStation_ != Station("Delhi")
         || b3.dateOfTravel_ != Date(1,5,2021) || b3.passenger_ != NULL )
    {   cout << "Booking Construction Error on Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass())" << endl ; allPassed = false ; }

    if ( b4.bookingClass_ != &BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass() 
         || b4.fromStation_ != Station("Mumbai")
         || b4.toStation_ != Station("Delhi")
         || b4.dateOfTravel_ != Date(1,5,2021) || b4.passenger_ != NULL )
    {   cout << "Booking Construction Error on Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass())" << endl ; allPassed = false ; }

    if ( b5.bookingClass_ != &BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass() 
         || b5.fromStation_ != Station("Mumbai")
         || b5.toStation_ != Station("Delhi")
         || b5.dateOfTravel_ != Date(1,5,2021) || b5.passenger_ != NULL )
    {   cout << "Booking Construction Error on Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass())" << endl ; allPassed = false ; }

    if ( b6.bookingClass_ != &BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass() 
         || b6.fromStation_ != Station("Mumbai")
         || b6.toStation_ != Station("Delhi")
         || b6.dateOfTravel_ != Date(1,5,2021) || b6.passenger_ != NULL )
    {   cout << "Booking Construction Error on Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass())" << endl ; allPassed = false ; }
    
    if ( b7.bookingClass_ != &BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass() 
         || b7.fromStation_ != Station("Mumbai")
         || b7.toStation_ != Station("Delhi")
         || b7.dateOfTravel_ != Date(1,5,2021) || b7.passenger_ != NULL )
    {   cout << "Booking Construction Error on Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass())" << endl ; allPassed = false ; }
    
    // check the data member 'Booking::pnr_' of all the instances and ensure that they are properly serialized
    if ( b1.pnr_ != 1 || b2.pnr_ != 2 || b3.pnr_ != 3 || b4.pnr_ != 4 || b5.pnr_ != 5 || b6.pnr_ != 6 || b7.pnr_ != 7 )
    {   cout << "PNR numbers for the bookings are not serialized accurately by 'Booking::Booking(const Station&, const Station&, const Date&, const BookingClass&, Passenger*)'" << endl ; allPassed = false ; }

     // check the variation in the static data member 'Booking::sBookingPNRSerial' and ensure that it is 
     // incremented by 1 unit after each instantiation
    if ( pNRSerialBeforeAnything != 1 )
    { cout << "Initial value of the next-available-PNR-number is not 1" << endl ;  }
    if ( pNRSerialAfterb1 != 2 )
    { cout << "Error in incrementing the next-available-PNR-number after construction of Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassSeatNoTierAcOrdinary::SpecialBookingClass()) by 1 unit" << endl ;  allPassed = false ;  }
    if ( pNRSerialAfterb2 != 3 )
    { cout << "Error in incrementing the next-available-PNR-number after construction of Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass()) by 1 unit" << endl ;  allPassed = false ;  }
    if ( pNRSerialAfterb3 != 4 )
    { cout << "Error in incrementing the next-available-PNR-number after construction of Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass()) by 1 unit" << endl ;  allPassed = false ;  }
    if ( pNRSerialAfterb4 != 5 )
    { cout << "Error in incrementing the next-available-PNR-number after construction of Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass()) by 1 unit" << endl ;  allPassed = false ;  }
    if ( pNRSerialAfterb5 != 6 )
    { cout << "Error in incrementing the next-available-PNR-number after construction of Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass()) by 1 unit" << endl ;  allPassed = false ;  }
    if ( pNRSerialAfterb6 != 7 )
    { cout << "Error in incrementing the next-available-PNR-number after construction of Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass()) by 1 unit" << endl ;  allPassed = false ;  }
    if ( pNRSerialAfterb7 != 8 )
    { cout << "Error in incrementing the next-available-PNR-number after construction of Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()) by 1 unit" << endl ;  allPassed = false ;  }
    
    // check the static data member 'Booking::sBookings' and ensure that it was updated after every instantiation
    // check its size and match its elemnent at each and every index from 0 to 6 with the address of the corresponding instance
    if ( Booking::sBookings.size() != 7 )
    { cout << "'Booking::sBookings' does not consist of the correct number of bookings" << endl ;  allPassed = false ; }
    if ( Booking::sBookings.at(0) != & b1 )
    { cout << "Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassSeatNoTierAcOrdinary::SpecialBookingClass()) was not pushed into the vector Booking::sBookings at its corresponding serial number" << endl ;  allPassed = false ;  }
    if ( Booking::sBookings.at(1) != & b2 )
    { cout << "Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass()) was not pushed into the vector Booking::sBookings at its corresponding serial number" << endl ;  allPassed = false ;  }
    if ( Booking::sBookings.at(2) != & b3 )
    { cout << "Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass()) was not pushed into the vector Booking::sBookings at its corresponding serial number" << endl ;  allPassed = false ;  }
    if ( Booking::sBookings.at(3) != & b4 )
    { cout << "Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass()) was not pushed into the vector Booking::sBookings at its corresponding serial number" << endl ;  allPassed = false ;  }
    if ( Booking::sBookings.at(4) != & b5 )
    { cout << "Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass()) was not pushed into the vector Booking::sBookings at its corresponding serial number" << endl ;  allPassed = false ;  }
    if ( Booking::sBookings.at(5) != & b6 )
    { cout << "Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass()) was not pushed into the vector Booking::sBookings at its corresponding serial number" << endl ;  allPassed = false ;  }
    if ( Booking::sBookings.at(6) != & b7 )
    { cout << "Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()) was not pushed into the vector Booking::sBookings at its corresponding serial number" << endl ;  allPassed = false ;  }

    // TEST 3 : Copy Constructor
    Booking b8 = b1 ;
    unsigned int nextPNRAfterCopyCctor = Booking::sBookingPNRSerial ;
    vector<const Booking *> sBookingsAfterCopyCctor = Booking::sBookings ;
    // compare the attributes of the two instances 'b8' and 'b1' and ensure that all their data members are same
    // except 'Booking::pnr_' whose value for 'b8' must be the next value in a serial order, i.e, 8
    if ( b8.bookingClass_ != b1.bookingClass_
         || b1.fromStation_ != b8.fromStation_
         || b1.toStation_ != b8.toStation_
         || b1.dateOfTravel_ != b8.dateOfTravel_ 
         || b8.pnr_ != 8 || b1.fare_ != b8.fare_  
         || b1.bookingMessage_ != b8.bookingMessage_
         || b1.bookingStatus_ != b8.bookingStatus_
         || b1.passenger_ != b8.passenger_ )
    { cout << "Error in constructing an instance of 'Booking' class by copy constructor 'Booking::Booking(const Booking&)'" << endl ;  allPassed = false ; }
    // check the value of the static data member 'Booking::sBookingPNRSerial' and ensure that it was incremented by 1 after the copy-ctor constructs 'b8'
    if ( nextPNRAfterCopyCctor != 9 )
    { cout << "Copy constructor 'Booking::Booking(const Booking&)' does not increment the next-available-PNR-number by 1 unit" << endl ;  allPassed = false ; }
    // check the static data member 'Booking::sBookings' and ensure that it was updated after the copy-ctor constructed 'b8'
    // check its size and match its 8th element (index 7) with the address of the newly constructed object 'b8'
    if ( sBookingsAfterCopyCctor.size() != 8 || sBookingsAfterCopyCctor.at(7) != &b8 )
    { cout << "Copy constructor 'Booking::Booking(const Booking&)' does not correctly update the vector 'Booking::sBookings' upon instantiation" << endl ;  allPassed = false ; }

     // TEST 4 : Overloaded copy assignment operator '='
    unsigned int nextPNRBeforeCopy = Booking::sBookingPNRSerial ;       // remember the value of 'Booking::sBookingPNRSerial' before copying
    vector<const Booking *> sBookingsBeforeCopy = Booking::sBookings ;  // remember the value of 'Booking::sBookings' before copying
    b8 = b2 ;
    unsigned int nextPNRAfterCopy = Booking::sBookingPNRSerial ;           // capture the value of 'Booking::sBookingPNRSerial' after copying
    vector<const Booking *> sBookingsAfterCopy = Booking::sBookings ;      // capture the value of 'Booking::sBookings' after copying
    // compare the attributes of the two instances 'b8' and 'b2' and ensure that all their data members are same
    // (including 'Booking::pnr_')
    if ( b8.bookingClass_ != b2.bookingClass_
         || b2.fromStation_ != b8.fromStation_
         || b2.toStation_ != b8.toStation_
         || b2.dateOfTravel_ != b8.dateOfTravel_
         || b2.pnr_ != b8.pnr_ || b2.fare_ != b8.fare_  
         || b2.bookingMessage_ != b8.bookingMessage_
         || b2.bookingStatus_ != b8.bookingStatus_
         || b2.passenger_ != b8.passenger_ )
    { cout << "Error in copying an instance of 'Booking' class by copy assignment operator 'const Booking & operator=(const Booking&)'" << endl ;  allPassed = false ; }
    // ensure that the value of the static non-constant data member 'Booking::sBookingPNRSerial' stayed intact
    if ( nextPNRBeforeCopy != nextPNRAfterCopy )
    { cout << "Copy assignment operator 'const Booking & operator=(const Booking&)' wrongly increments the next-available-PNR-number" << endl ;  allPassed = false ; }
    // ensure that the value of the static non-constant data member 'Booking::sBookings' stayed intact
    if ( sBookingsBeforeCopy != sBookingsAfterCopy )
    { cout << "Copy assignment operator 'const Booking & operator=(const Booking&)' wrongly updates the vector 'Booking::sBookings' upon copying" << endl ;  allPassed = false ; }

    // TEST 5 : Test the accuracy of the value returned by 'Booking::ComputeFair' in different scenarios
    // In the first case, check the fare computation for various 'Booking' instances with constant terminal stations and variable booking-class.
    // The values assigned to the data member 'Booking::fare_' are computed by the method 'Booking::ComputeFair' in the constructor's body.
    // Match the values of this data member with the manually calculated values (the golden outputs)
    if ( b1.fare_ != 954 )
    { cout << "Fare not correctly computed for Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), & BookingClassSeatNoTierAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b2.fare_ != 362 )
    { cout << "Fare not correctly computed for Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), & BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b3.fare_ != 2776 )
    { cout << "Fare not correctly computed for Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), & BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b4.fare_ != 1497 )
    { cout << "Fare not correctly computed for Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), & BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b5.fare_ != 1809 )
    { cout << "Fare not correctly computed for Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), & BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b6.fare_ != 1316 )
    { cout << "Fare not correctly computed for Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), & BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b7.fare_ != 724 )
    { cout << "Fare not correctly computed for Booking(Station(\"Mumbai\"), Station(\"Delhi\"), Date(1,5,2021), & BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    
    // In the second case, check the fare computation for various 'Booking' instances with constant terminal stations and variable booking-class.
    // In this case, choose a different pair of terminal stations than the first case
    Booking b9 = Booking(Station("Bangalore"), Station("Chennai"), Date(1,5,2021), BookingClassSeatNoTierAcOrdinary::SpecialBookingClass()) ;
    Booking b10 = Booking(Station("Bangalore"), Station("Chennai"), Date(1,5,2021), BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass()) ;
    Booking b11 = Booking(Station("Bangalore"), Station("Chennai"), Date(1,5,2021), BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass()) ;
    Booking b12 = Booking(Station("Bangalore"), Station("Chennai"), Date(1,5,2021), BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass()) ;
    Booking b13 = Booking(Station("Bangalore"), Station("Chennai"), Date(1,5,2021), BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass()) ;
    Booking b14 = Booking(Station("Bangalore"), Station("Chennai"), Date(1,5,2021), BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass()) ;
    Booking b15 = Booking(Station("Bangalore"), Station("Chennai"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()) ;

    // Match the values of the data member 'Booking::fare_' with the manually calculated values (the golden outputs)
    if ( b9.fare_ != 269 )
    { cout << "Fare not correctly computed for Booking(Station(\"Bangalore\"), Station(\"Chennai\"), Date(1,5,2021), BookingClassSeatNoTierAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b10.fare_ != 88 )
    { cout << "Fare not correctly computed for Booking(Station(\"Bangalore\"), Station(\"Chennai\"), Date(1,5,2021), BookingClassSeatNoTierNonAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b11.fare_ != 719 )
    { cout << "Fare not correctly computed for Booking(Station(\"Bangalore\"), Station(\"Chennai\"), Date(1,5,2021), BookingClassBerthDoubleTierAcLuxury::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b12.fare_ != 400 )
    { cout << "Fare not correctly computed for Booking(Station(\"Bangalore\"), Station(\"Chennai\"), Date(1,5,2021), BookingClassBerthDoubleTierAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b13.fare_ != 438 )
    { cout << "Fare not correctly computed for Booking(Station(\"Bangalore\"), Station(\"Chennai\"), Date(1,5,2021), BookingClassBerthDoubleTierNonAcLuxury::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b14.fare_ != 356 )
    { cout << "Fare not correctly computed for Booking(Station(\"Bangalore\"), Station(\"Chennai\"), Date(1,5,2021), BookingClassBerthTripleTierAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b15.fare_ != 175 )
    { cout << "Fare not correctly computed for Booking(Station(\"Bangalore\"), Station(\"Chennai\"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }

    // In the third case, check the fare computation for various 'Booking' instances with constant booking-class and variable pair of terminal stations.
    // No need to repeat those pairs of stations that are already checked in the last two cases.
    // Note that considering only unordered pairs of stations is enough to verify the value of computed fare because 'Booking::ComputeFair' is a symmetric
    // method (since 'Railways::SpecialRailways' is a symmetric method)
    Booking b16 = Booking(Station("Mumbai"), Station("Chennai"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()) ;
    Booking b17 = Booking(Station("Kolkata"), Station("Chennai"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()) ;
    Booking b18 = Booking(Station("Mumbai"), Station("Kolkata"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()) ;
    Booking b19 = Booking(Station("Mumbai"), Station("Bangalore"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()) ;
    Booking b20 = Booking(Station("Kolkata"), Station("Delhi"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()) ;
    Booking b21 = Booking(Station("Chennai"), Station("Delhi"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()) ;
    Booking b22 = Booking(Station("Bangalore"), Station("Delhi"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()) ;
    Booking b23 = Booking(Station("Bangalore"), Station("Kolkata"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass()) ;

    // Match the values of the data member 'Booking::fare_' with the manually calculated values (the golden outputs)
    if ( b16.fare_ != 669 )
    { cout << "Fare not correctly computed for Booking(Station(\"Mumbai\"), Station(\"Chennai\"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b17.fare_ != 830 )
    { cout << "Fare not correctly computed for Booking(Station(\"Kolkata\"), Station(\"Chennai\"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b18.fare_ != 1007 )
    { cout << "Fare not correctly computed for Booking(Station(\"Mumbai\"), Station(\"Kolkata\"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b19.fare_ != 491 )
    { cout << "Fare not correctly computed for Booking(Station(\"Mumbai\"), Station(\"Bangalore\"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b20.fare_ != 736 )
    { cout << "Fare not correctly computed for Booking(Station(\"Kolkata\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b21.fare_ != 1090 )
    { cout << "Fare not correctly computed for Booking(Station(\"Chennai\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b22.fare_ != 1075 )
    { cout << "Fare not correctly computed for Booking(Station(\"Bangalore\"), Station(\"Delhi\"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }
    if ( b23.fare_ != 936 )
    { cout << "Fare not correctly computed for Booking(Station(\"Bangalore\"), Station(\"Kolkata\"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass())" << endl ;  allPassed = false ;  }

     // TEST 6 : Test overloaded output streaming operator
     // stream a single instance
    cout << b1 ;    // print a 'Booking' instance for which 'Booking::passenger_' data member is NULL
    Passenger p("Aradhya Aggarwal", "2003 6974 5522", Date(19, 3, 1995), Passenger::Gender::Female, Passenger::Category::Ladies, "8174563222") ;
    Booking b24 = Booking(Station("Bangalore"), Station("Kolkata"), Date(1,5,2021), BookingClassBerthTripleTierNonAcOrdinary::SpecialBookingClass(), &p) ;
    cout << b24 ;    // print a 'Booking' instance for which 'Booking::passenger_' data member is not NULL
    // stream a chain of instances
    cout << b2 << b3 << b9 << b10 << b11 << b16 << b17 << b18 << b24 << endl ;

     // TEST 7 : Test destructor
    unsigned int sizeStaticBookingsBeforeDtor = sBookings.size() ;    // remember the size of 'Booking::sBookings' before destructing 'b1'
    unsigned int nextPNRBeforeDtor = sBookingPNRSerial ;    // remember 'Booking::sBookingPNRSerial' before destructing 'b1'
    b1.~Booking() ;
    unsigned int sizeStaticBookingsAfterDtor = sBookings.size() ;     // capture the size of 'Booking::sBookings' after destructing 'b1'
    bool checkPresenceAfterDtor = find(sBookings.begin(), sBookings.end(), &b1) != sBookings.end() ;     // check if '&b1' is present in 'Booking::sBookings' after destructing 'b1'
    unsigned int nextPNRAfterDtor = sBookingPNRSerial ;      // capture 'Booking::sBookingPNRSerial' after destructing 'b1'
    // ensure that the size of 'Booking::sBookings' is reduced by 1 after calling the destructor and '&b1' is no
    // longer present in 'Booking::sBookings' data member.
    if ( ! ( sizeStaticBookingsBeforeDtor == sizeStaticBookingsAfterDtor + 1 && ! checkPresenceAfterDtor ) )
    { cout << "Destructor 'Booking::~Booking()' does not update 'Booking::sBookings' upon destruction" << endl ;  allPassed = false ; }
    if ( nextPNRAfterDtor != nextPNRBeforeDtor )  // ensure that value of 'Booking::sBookingPNRSerial' stayed intact
    { cout << "Destructor 'Booking::~Booking()' wrongly changes the value of 'Booking::sBookingPNRSerial' upon destruction" << endl ;  allPassed = false ; }

    if ( allPassed )
        cout << endl << " *** ALL TESTS PASSED ***" << endl ;   // to indicate that all tests have passed

}