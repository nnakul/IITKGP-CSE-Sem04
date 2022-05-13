
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#pragma once
#include <iostream>
#include <string>
#include "Passenger.h"
#include "Booking.h"
using namespace std ;

class Booking ; // forward declaration of Booking abstract base class

template < typename T >
class BookingCategoryTypes ; // template class -- forward declaration

class BookingCategory  // abstract base class
{
    private :
        // Tag types - to instantiate the template
        // Note that these names are placeholders only and are not exposed outside the class
        // Also they are put inside the class for not cluttering the global namespace
        struct GeneralType { } ;
        struct LadiesType { } ;
        struct SeniorCitizenType { } ;
        struct DivyaangType { } ;
        struct TatkalType { } ;
        struct PremiumTatkalType { } ;

    protected :
        BookingCategory ( ) {   }   // constructor
        virtual ~BookingCategory ( ) {  }    // destructor -- virtual/polymorphic
        // const static data members
        static const unsigned int sMaxAgeMalesForLadies ;   // maximum age for Males to qualify for Ladies booking category
        static const unsigned int sMinAgeMalesForSenCit ;   // minimum age for Males to qualify for SeniorCitizen booking category
        static const unsigned int sMinAgeFemalesForSenCit ;   // minimum age for Females to qualify for SeniorCitizen booking category
        static const unsigned int sHoursBeforeTravelForPriority ;   // number of hours before travel for which Tatkal booking category will
                                                                    // be applicable. In this application we do not bother about the exact time
                                                                    // and deal with only dates. So in this case the value is chosen as 24 hours
                                                                    // representing 1 day as given in the master data of the specifications.
    
    public :
        // non-static member functions
        // all of them pure-virtual / abstract
        virtual bool IsElligible ( const Passenger & , const Date & ) const = 0 ;
        virtual string GetName ( ) const = 0 ;
        virtual const Booking * SelectBooking ( const Station & , const Station & , const Date & , const BookingClass & , 
                                                const Passenger & , const Date & ) const = 0 ;
        friend ostream & operator << ( ostream & , const BookingCategory & ) ;  // overloaded output streaming operator. Useful in testing.
                                                                                // it is not a member function but rather a global function
                                                                                // that is a "friend" of BookingCategory
        // Enumerated types - the target sub-types (6)
        typedef BookingCategoryTypes<GeneralType> General ;    // static sub-type of BookingCategory -- General
        typedef BookingCategoryTypes<LadiesType> Ladies ;    // static sub-type of BookingCategory -- Ladies
        typedef BookingCategoryTypes<SeniorCitizenType> SeniorCitizen ;    // static sub-type of BookingCategory -- SeniorCitizen
        typedef BookingCategoryTypes<DivyaangType> Divyaang ;    // static sub-type of BookingCategory -- Divyaang
        typedef BookingCategoryTypes<TatkalType> Tatkal ;    // static sub-type of BookingCategory -- Tatkal
        typedef BookingCategoryTypes<PremiumTatkalType> PremiumTatkal ;    // static sub-type of BookingCategory -- PremiumTatkal
        static void UnitTestBookingCategoryHierarchy ( ) ;   // implements unit test plan written for BookingCategory hierarchy
} ;

// specific BookingCategory sub-types
// template class definition
template < typename T >
class BookingCategoryTypes : public BookingCategory
{
    private :
        // static const data members
        static const string sName ; // stores the name of the BookingCategory sub-type
        BookingCategoryTypes ( ) : BookingCategory() // constructor
        {  
            #ifdef _DEBUG
                cout << "BookingCategory SUB-TYPE CONSTRUCTED : " << sName << endl ;
            #endif
        }
        ~BookingCategoryTypes ( ) // destructor
        { 
            #ifdef _DEBUG
                cout << "BookingCategory SUB-TYPE DESTRUCTED : " << sName << endl ;
            #endif
        }
        BookingCategoryTypes<T> & operator = ( const BookingCategoryTypes<T> & ) const {    } // block copy assignment operator

    public :
        // singleton object -- placeholder for the respecive type
        // Meyer's implementation of a Singleton Class
        static const BookingCategoryTypes<T> & Type ( )
        {
            static const BookingCategoryTypes<T> object ;    // singleton object must be treated as a constant
            return object ;
        }
        // non static member functions
        // override all the pure virtual member functions in the abstract base class
        string GetName ( ) const ;
        bool IsElligible ( const Passenger & , const Date & ) const ;
        const Booking * SelectBooking ( const Station & , const Station & , const Date & , const BookingClass & , 
                                        const Passenger & , const Date & ) const ;
} ;

template < typename T >
inline string BookingCategoryTypes<T>::GetName ( ) const    // implementation of "BookingCategoryTypes<T>::GetName" as an inline function 
{ return BookingCategoryTypes<T>::sName ; }
