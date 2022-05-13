
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#pragma once
#include <iostream>
#include <string>
using namespace std ;

template < typename T >
class GenderTypes ; // template class -- forward declaration

class Gender    // abstract base class  
{
    private :
        const string name_ ;    // the only non-static data member
        // Tag types - to instantiate the template
        // Note that these names are placeholders only and are not exposed outside the class
        // Also they are put inside the class for not cluttering the global namespace
        struct MaleType { } ;
        struct FemaleType { } ;

    protected : 
        // constructor  
        Gender ( const string & name ) : name_(name) {   }
        virtual ~Gender ( ) {   }   // destructor -- virtual/polymorphic

    public :
        inline string GetName ( ) const ;   // non-static member function
        virtual string GetTitle ( ) const = 0 ; // pure virtual method
        inline static bool IsMale ( const Gender & ) ;  // static member function
        friend ostream & operator << ( ostream & , const Gender & ) ;  // overloaded output streaming operator. Useful in testing.
                                                                       // it is not a member function but rather a global function
                                                                       // that is a "friend" of Gender
        // Enumerated types - the target sub-types
        typedef GenderTypes<MaleType> Male ;    // static sub-type of Gender -- Male
        typedef GenderTypes<FemaleType> Female ;    // static sub-type of Gender -- Female
        static void UnitTestGenderHierarchy ( ) ;   // implements unit test plan written for Gender hierarchy
} ;

// specific Gender sub-types
// template class definition
template < typename T >
class GenderTypes : public Gender 
{
    private :
        // static const data members
        static const string sName ; 
        static const string sSalutation ;
        // constructor
        GenderTypes ( const string & name = GenderTypes<T>::sName ) : Gender(name) 
        {  
            #ifdef _DEBUG
                cout << "Gender SUB-TYPE CONSTRUCTED : " << sName << endl ;
            #endif
        }
        // destructor
        ~GenderTypes ( ) 
        { 
            #ifdef _DEBUG
                cout << "Gender SUB-TYPE DESTRUCTED : " << sName << endl ;
            #endif
        }
        GenderTypes<T> & operator = ( const GenderTypes<T> & ) const {    } // block the copy assignment operator
    
    public :
        // singleton object -- placeholder for the respecive type
        // Meyer's implementation of a Singleton Class
        static const GenderTypes<T> & Type ( )
        {
            static const GenderTypes<T> object ;    // singleton object must be treated as a constant
            return object ;
        }
        inline string GetTitle ( ) const ;  // override the pure virtual method in the abstract base class
} ;

inline bool Gender::IsMale ( const Gender & g )    // implementation of "Gender::IsMale" as an inline function
{ return &g == &Gender::Male::Type() ; }

inline string Gender::GetName ( ) const    // implementation of "Gender::GetName" as an inline function 
{  return  name_ ;  }

template<typename T>
inline string GenderTypes<T>::GetTitle ( ) const    // implementation of "GenderTypes<T>::GetTitle" as an inline function
{   return GenderTypes<T>::sSalutation ;    }
