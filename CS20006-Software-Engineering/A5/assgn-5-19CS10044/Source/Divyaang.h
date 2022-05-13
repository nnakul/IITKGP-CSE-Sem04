
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#pragma once
#include <iostream>
#include <map>
#include "BookingClass.h"
using namespace std ;

template < typename T >
class DivyaangTypes ; // template class -- forward declaration

class Divyaang  // abstract base class
{
    private :
        // Tag types - to instantiate the template
        // Note that these names are placeholders only and are not exposed outside the class
        // Also they are put inside the class for not cluttering the global namespace
        struct BlindType { } ;
        struct OrthoHandicapType { } ;
        struct CancerPatientsType { } ;
        struct TBPatientsType { } ;

    protected :
        Divyaang ( ) {   }  // constructor
        virtual ~Divyaang ( ) {   }    // destructor -- virtual/polymorphic

    public :
        // non-static pure virtual member functions
        virtual string GetName ( ) const = 0 ;
        virtual double GetConcessionFactor ( const BookingClass & ) const = 0 ;
        friend ostream & operator << ( ostream & , const Divyaang & ) ;  // overloaded output streaming operator. Useful in testing.
                                                                         // it is not a member function but rather a global function
                                                                         // that is a "friend" of Divyaang
        // Enumerated types - the target sub-types (4)
        typedef DivyaangTypes<BlindType> Blind ;    // static sub-type of Divyaang -- Blind
        typedef DivyaangTypes<OrthoHandicapType> OrthopaedicallyHandicapped ;    // static sub-type of Divyaang -- Orthopaedically Handicapped
        typedef DivyaangTypes<CancerPatientsType> CancerPatients ;    // static sub-type of Divyaang -- Cancer Patients
        typedef DivyaangTypes<TBPatientsType> TBPatients ;    // static sub-type of Divyaang -- TB Patients
        static void UnitTestDivyaangHierarchy ( ) ;   // implements unit test plan written for Divyaang hierarchy
} ;

// specific Divyaang sub-types
// template class definition
template < typename T >
class DivyaangTypes : public Divyaang 
{
    private :
        // static const data members
        static const string sName ; // name of the sub-type
        static const map<string, double> sConcessionFactors ;   // maps the names of the static sub-types of BookingClass to 
                                                                // their corresponding oncession factors to this aprticular Divyaang sub-type
        DivyaangTypes ( ) : Divyaang() // constructor
        {  
            #ifdef _DEBUG
                cout << "Divyaang SUB-TYPE CONSTRUCTED : " << sName << endl ;
            #endif
        }
        ~DivyaangTypes ( )  // destructor
        { 
            #ifdef _DEBUG
                cout << "Divyaang SUB-TYPE DESTRUCTED : " << sName << endl ;
            #endif
        }
        DivyaangTypes<T> & operator = ( const DivyaangTypes<T> & ) const {    } // block copy assignment operator
    
    public :
        // singleton object -- placeholder for the respecive type
        // Meyer's implementation of a Singleton Class
        static const DivyaangTypes<T> & Type ( )
        {
            static const DivyaangTypes<T> object ;    // singleton object must be treated as a constant
            return object ;
        }
        // non static member functions
        // override all the pure virtual member functions in the abstract base class
        inline string GetName ( ) const ;
        double GetConcessionFactor ( const BookingClass & ) const ;
} ;

template < typename T >
inline string DivyaangTypes<T>::GetName ( ) const    // implementation of "DivyaangTypes<T>::GetName" as an inline function 
{   return DivyaangTypes<T>::sName ;     }
