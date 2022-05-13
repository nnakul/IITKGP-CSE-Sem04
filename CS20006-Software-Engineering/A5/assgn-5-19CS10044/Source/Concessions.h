
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#pragma once
#include <iostream>
#include "Passenger.h"
using namespace std ;

class Concessions   // base class
{
    protected :
        // no need to keep the constructors/destructors public
        // because in this hierarchy all data members and member
        // functions are static; therefore no instantiation would
        // be needed, neither of the base class nor of any of the
        // derived classes
        Concessions ( ) { }
        ~Concessions ( ) { }
    public :
        // implements the unit test plan written for Concessions hierarchy
        static void UnitTestConcessionsHierarchy ( ) ;
} ;

// derived class -- stores relevant information regarding 
// concessions for General booking category in form of
// static data members
class GeneralConcession : public Concessions
{
    private :
        // no need to keep the constructors/destructors public
        // because in this class all data members and member
        // functions are static; therefore no instantiation would
        // be needed
        GeneralConcession ( ) : Concessions() {   }
        ~GeneralConcession ( ) { }
        static const double sConcessionFactor ; // static data member
    public :
        static double GetConcessionFactor ( ) ; // static member function 
                                                // -- returns value of GeneralConcession::sConcessionFactor
} ;

// derived class -- stores relevant information regarding 
// concessions for Ladies booking category in form of
// static data members
class LadiesConcession : public Concessions
{
    private :
        // no need to keep the constructors/destructors public
        // because in this class all data members and member
        // functions are static; therefore no instantiation would
        // be needed
        LadiesConcession ( ) : Concessions() {   }
        ~LadiesConcession ( ) { }
        // static data members
        static const double sConcessionFactorMales ;
        static const double sConcessionFactorFemales ;
    public :
        static double GetConcessionFactor ( const Passenger & ) ; // static member function 
        // returns the value of LadiesConcession::sConcessionFactorMales or LadiesConcession::sConcessionFactorFemales
        // depending upon the gender of the Passenger passed as parameter
} ;

// derived class -- stores relevant information regarding 
// concessions for SeniorCitizen booking category in form of
// static data members
class SeniorCitizenConcession : public Concessions
{
    private :
        // no need to keep the constructors/destructors public
        // because in this class all data members and member
        // functions are static; therefore no instantiation would
        // be needed
        SeniorCitizenConcession ( ) : Concessions() {   }
        ~SeniorCitizenConcession ( ) { }
        // static data members
        static const double sConcessionFactorMales ;
        static const double sConcessionFactorFemales ;
    public :
        static double GetConcessionFactor ( const Passenger & ) ; // static member function 
        // returns the value of SeniorCitizenConcession::sConcessionFactorMales or SeniorCitizenConcession::sConcessionFactorFemales
        // depending upon the gender of the Passenger passed as parameter
} ;

// derived class -- stores relevant information regarding 
// concessions for Divyaang booking category in form of
// static data members
class DivyaangConcession : public Concessions
{
    private :
        // no need to keep the constructors/destructors public
        // because in this class all data members and member
        // functions are static; therefore no instantiation would
        // be needed
        DivyaangConcession ( ) : Concessions() {   }
        ~DivyaangConcession ( ) { }
        // no need for any static data members because all the information
        // corresponding to each of the 4 Divyaang sub-types is already stored
        // in the Divyaang hierarchy
    public :
        static double GetConcessionFactor ( const Passenger & , const BookingClass & ) ;    // static member function
        // returns the concession factor applicable to the Passenger's disability type in the
        // booking class passed as parameter
} ;