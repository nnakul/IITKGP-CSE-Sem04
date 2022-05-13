
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#pragma once
#include <iostream>
#include "Railways.h"
#include "Concessions.h"
#include "BookingClass.h"
#include "BookingCategory.h"
using namespace std ;

// forward declarations of some classes
class Booking ;
class BookingCategory ;

template < typename T >
class BookingTypes ; // template class -- forward declaration

class Booking  // abstract base class
{
    protected :
        // non-static data members
        // all data members (except fare_) are const because
        // this information cannot change once a Booking is done (constructed)
        const Station fromStation_ ;
        const Station toStation_ ;
        const Date dateOfBooking_ ;
        const BookingClass & bookingClass_ ;
        const BookingCategory & bookingCategory_ ;
        const Passenger passenger_ ;
        const Date dateOfReservation_ ;
        const unsigned int pnr_ ;
        unsigned int fare_ ;    // this should naturally be non-const because it is computed after 
                                // a Booking sub-type object is constructed -- if it is const, whatever
                                // arbitrary value it holds could not be changed after construction

        // Tag types - to instantiate the template
        // Note that these names are placeholders only and are not exposed outside the class
        // Also they are put inside the class for not cluttering the global namespace
        struct GeneralType { } ;
        struct LadiesType { } ;
        struct SeniorCitizenType { } ;
        struct DivyaangType { } ;
        struct TatkalType { } ;
        struct PremiumTatkalType { } ;

        // static data members
        static const double sBaseFareRate ;     // base fare rate for all the Booking types
        static unsigned int sNextAvailablePNR ; // next available PNR -- keeps track of the number of instances of Booking constructed

    protected :
        Booking ( const Station & , const Station & , const Date & , const BookingClass & ,
                  const BookingCategory & , const Passenger & , const Date & ) ;    // constructor
    
    public :
        virtual ~Booking ( ) {   }    // destructor -- virtual/polymorphic
        // static member functions -- the first lifeline in the virtual construction idiom
        static const Booking * CreateBooking ( const Station & , const Station & , const Date & , 
                                               const BookingClass & , const BookingCategory & , const Passenger & ) ;
        // non-static member functions
        // both of them are pure-virtual/abstract
        virtual unsigned int ComputeFare ( ) const = 0 ;
        virtual string GetType ( ) const = 0 ;
        friend ostream & operator << ( ostream & , const Booking & ) ;   // overloaded output streaming operator. Useful in testing.
                                                                         // it is not a member function but rather a global function
                                                                         // that is a "friend" of Booking
        // Enumerated types - the target sub-types (6)
        typedef BookingTypes<GeneralType> GeneralBooking ;    // static sub-type of Booking -- General Booking
        typedef BookingTypes<LadiesType> LadiesBooking ;    // static sub-type of Booking -- Ladies Booking
        typedef BookingTypes<SeniorCitizenType> SeniorCitizenBooking ;    // static sub-type of Booking -- Senior Citizen Booking
        typedef BookingTypes<DivyaangType> DivyaangBooking ;    // static sub-type of Booking -- Divyaang Booking
        typedef BookingTypes<TatkalType> TatkalBooking ;    // static sub-type of Booking -- Tatkal Booking
        typedef BookingTypes<PremiumTatkalType> PremiumTatkalBooking ;    // static sub-type of Booking -- Premium Tatkal Booking
        static void UnitTestBookingHierarchy ( ) ;   // implements unit test plan written for Booking hierarchy
} ;

// specific Booking sub-types
// template class definition
template < typename T >
class BookingTypes : public Booking
{
    private :
        // static const data members
        static const string sBookingType ;  // stores the type of the Booking
        BookingTypes (  const Station & s1 , const Station & s2 , const Date & d1 , const BookingClass & bc ,
                           const BookingCategory & bcat , const Passenger & p , const Date & d2 ) ; // constructor
        Booking & operator = ( const Booking & ) { }    // block copy assignment operator
    public :
        ~BookingTypes ( ) // destructor
        {   
            #ifdef _DEBUG
                cout << "Booking DESTRUCTED : " << pnr_ << endl ;
            #endif
        }
        // non static member functions
        // override all the pure virtual member functions in the abstract base class
        unsigned int ComputeFare ( ) const ;    // algorithm to compute fare
        static const BookingTypes<T> * CreateSpecialBooking (   const Station & , const Station & , const Date &, 
                                                                const BookingClass & , const BookingCategory & , const Passenger & , 
                                                                const Date &   ) ;
        inline string GetType ( ) const ;
} ;

template < typename T >
inline string BookingTypes<T>::GetType ( ) const    // implementation of "BookingTypes<T>::GetType" as an inline function 
{   return BookingTypes<T>::sBookingType ;  }