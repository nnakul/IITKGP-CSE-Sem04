
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#pragma once
#include <iostream>
#include <string>
using namespace std ;

template < typename T >
class BookingClassTypes ; // template class -- forward declaration

class BookingClass  // abstract base class
{
    private :
        // Tag types - to instantiate the template
        // Note that these names are placeholders only and are not exposed outside the class
        // Also they are put inside the class for not cluttering the global namespace
        struct ACFirstClassType { } ;
        struct ExecChairCarType { } ;
        struct AC2TierType { } ;
        struct FirstClassType { } ;
        struct AC3TierType { } ;
        struct ACChairCarType { } ;
        struct SleeperType { } ;
        struct SecondSittingType { } ;

    protected :
        BookingClass ( ) {   }  // constructor
        virtual ~BookingClass ( ) {   }    // destructor -- virtual/polymorphic

    public :
        // non-static member functions
        // all of them are pure-vertual/abstract
        // each one of these member functions is meant to return
        // one or the other static const data member associated with 
        // a BookingClass sub-type
        virtual double GetLoadFactor ( ) const = 0 ;
        virtual string GetName ( ) const = 0 ;
        virtual bool IsSitting ( ) const = 0 ;
        virtual bool IsAC ( ) const = 0 ;
        virtual unsigned int GetNumberOfTiers ( ) const = 0 ;
        virtual bool IsLuxury ( ) const = 0 ;
        virtual double GetReservationCharge ( ) const = 0 ;
        virtual double GetTatkalCharge ( ) const = 0 ;
        virtual double GetMaxTatkalCharge ( ) const = 0 ;
        virtual double GetMinTatkalCharge ( ) const = 0 ;
        virtual unsigned int GetMinDistanceForTatkalCharge ( ) const = 0 ;
        friend ostream & operator << ( ostream & , const BookingClass & ) ;  // overloaded output streaming operator. Useful in testing.
                                                                             // it is not a member function but rather a global function
                                                                             // that is a "friend" of BookingClass
        // Enumerated types - the target sub-types (8)
        typedef BookingClassTypes<ACFirstClassType> ACFirstClass ;    // static sub-type of BookingClass -- AC First Class
        typedef BookingClassTypes<ExecChairCarType> ExecutiveChairCar ;    // static sub-type of BookingClass -- Executive Chair Car
        typedef BookingClassTypes<AC2TierType> AC2Tier ;    // static sub-type of BookingClass -- AC 2 Tier
        typedef BookingClassTypes<FirstClassType> FirstClass ;    // static sub-type of BookingClass -- First Class
        typedef BookingClassTypes<AC3TierType> AC3Tier ;    // static sub-type of BookingClass -- AC 3 Tier
        typedef BookingClassTypes<ACChairCarType> ACChairCar ;    // static sub-type of BookingClass -- AC Chair Car
        typedef BookingClassTypes<SleeperType> Sleeper ;    // static sub-type of BookingClass -- Sleeper
        typedef BookingClassTypes<SecondSittingType> SecondSitting ;    // static sub-type of BookingClass -- Second Sitting
        static void UnitTestBookingClassHierarchy ( ) ;   // implements unit test plan written for BookingClass hierarchy
} ;

// specific BookingClass sub-types
// template class definition
template < typename T >
class BookingClassTypes : public BookingClass 
{
    private :
        // static const data members
        // all the information concerning any sub-type is stored in 
        // static data members because all the class instances of the
        // template are singleton classes
        static const string sName ;
        static const double sLoadFactor ;
        static const bool sIsSitting ;
        static const bool sIsAC ;
        static const bool sIsLuxury ;
        static const unsigned int sNumberOfTiers ;
        static const double sReservationCharge ;
        static const double sTatkalCharge ;
        static const double sMaxTatkalCharge ;
        static const double sMinTatkalCharge ;
        static const unsigned int sMinDistanceForTatkalCharge ;
        BookingClassTypes ( )   // constructor
        {  
            #ifdef _DEBUG
                cout << "BookingClass SUB-TYPE CONSTRUCTED : " << sName << endl ;
            #endif
        }
        ~BookingClassTypes ( ) // destructor
        {  
            #ifdef _DEBUG
                cout << "BookingClass SUB-TYPE DESTRUCTED : " << sName << endl ;
            #endif
        }
        BookingClassTypes<T> & operator = ( const BookingClassTypes<T> & ) const {    } // block copy assignment operator

    public :
        // singleton object -- placeholder for the respecive type
        // Meyer's implementation of a Singleton Class
        static const BookingClassTypes<T> & Type ( )
        {
            static const BookingClassTypes<T> object ;    // singleton object must be treated as a constant
            return object ;
        }
        // non static member functions
        // override all the pure virtual member functions in the abstract base class
        inline string GetName ( ) const ;
        inline double GetLoadFactor ( ) const ;
        inline bool IsSitting ( ) const ;
        inline bool IsAC ( ) const ;
        inline bool IsLuxury ( ) const ;
        inline unsigned int GetNumberOfTiers ( ) const ;
        inline double GetReservationCharge ( ) const ;
        inline double GetTatkalCharge ( ) const ;
        inline double GetMaxTatkalCharge ( ) const ;
        inline double GetMinTatkalCharge ( ) const ;
        inline unsigned int GetMinDistanceForTatkalCharge ( ) const ;
} ;

// all the non-static member functions are implemented as inline functions
// because they simply return the value of a static data member and
// no computation is done

template < typename T >
inline string BookingClassTypes<T>::GetName ( ) const  
{ return BookingClassTypes<T>::sName ; }    // return the name of the booking class

template < typename T >
inline double BookingClassTypes<T>::GetLoadFactor ( ) const  
{ return BookingClassTypes<T>::sLoadFactor ; }  // return the load factor of the booking class

template < typename T >
inline bool BookingClassTypes<T>::IsSitting ( ) const  
{ return BookingClassTypes<T>::sIsSitting ; }   // return true if the booking class is of Seat 
                                                // type and false if of Berth type

template < typename T >
inline bool BookingClassTypes<T>::IsAC ( ) const  
{ return BookingClassTypes<T>::sIsAC ; }    // return true if the booking class has AC and false otherwise

template < typename T >
inline bool BookingClassTypes<T>::IsLuxury ( ) const  
{ return BookingClassTypes<T>::sIsLuxury ; }    // return true if the booking class is luxury and false otherwise

template < typename T >
inline unsigned int BookingClassTypes<T>::GetNumberOfTiers ( ) const  
{ return BookingClassTypes<T>::sNumberOfTiers ; }   // return the no. of tiers in the booking class

template < typename T >
inline double BookingClassTypes<T>::GetReservationCharge ( ) const  
{ return BookingClassTypes<T>::sReservationCharge ; }   // return the reservation charge for the booking class

template < typename T >
inline double BookingClassTypes<T>::GetTatkalCharge ( ) const  
{ return BookingClassTypes<T>::sTatkalCharge ; }    // return the tatkal charge factor if the booking is done on Tatkal

template < typename T >
inline double BookingClassTypes<T>::GetMaxTatkalCharge ( ) const  
{ return BookingClassTypes<T>::sMaxTatkalCharge ; } // return the max tatkal overhead amount allowed for this booking class

template < typename T >
inline double BookingClassTypes<T>::GetMinTatkalCharge ( ) const  
{ return BookingClassTypes<T>::sMinTatkalCharge ; } // return the min tatkal overhead amount allowed for this booking class

template < typename T >
inline unsigned int BookingClassTypes<T>::GetMinDistanceForTatkalCharge ( ) const  
{ return BookingClassTypes<T>::sMinDistanceForTatkalCharge ; }  // return the min distance between the terminal stations that should
                                                                // be satisfied in order to levy tatkal charge

