
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include <regex>
#include "Passenger.h"
#include "Exceptions.h"
using namespace std ;

// constructor
Passenger::Passenger ( const Date & d , const Gender & g , const string & an , const string & fn , const string & mn ,
                       const string & ln , const string & mob , const Divyaang * dt , const string & did )
    : dateOfBirth_(d) , gender_(g) , adhaarNumber_(an) , firstName_(fn) , middleName_(mn) ,
      lastName_(ln) , mobileNumber_(mob) , disabilityType_(dt) , disabilityID_(did) // initializer list
{   }

Passenger Passenger::CreatePassenger ( const Date & d , const string & g , const string & an , const string & fn , const string & mn ,
                                       const string & ln , const string & mob , const Divyaang * dt , const string & did )
{
    // FIRST CHECK THE VALIDITY OF ALL THE ARGUEMENTS
    // if erroneous condition is satisified, throw an exception

    if ( fn.length() == 0 && ln.length() == 0 )     // the passenger must specify atleast one of the first name and last name
        throw Bad_Passenger_Name("At least one of the First Name and Last Name must be specified") ;
    
    if ( an.length() != 12 )    // adhaar number must have exactly 12 digits
        throw Bad_Passenger_AdhaarNumber("Adhaar Number must be exactly 12 digits long") ;
    regex format("[0-9]+") ;    // regex object -- used for matching patterns
                                // this pattern describes a whole number
                                // naturally both adhaar number and mobile number must be whole numbers
    if ( ! regex_match(an, format) )    // match the pattern and see if the results are positive
        throw Bad_Passenger_AdhaarNumber("Adhaar Number must only consist of digits") ;
    
    if ( mob.length() != 0 )    // Mobile number is optional. But in case it is provided, the 
                                // constraints have to be satisfied
    {
        if ( mob.length() != 10 )   // mobile number must have exactly 10 digits
            throw Bad_Passenger_MobileNumber("Mobile Number must be exactly 10 digits long") ;
        if ( ! regex_match(mob, format) )    // match the pattern and see if the results are positive
            throw Bad_Passenger_MobileNumber("Mobile Number must only consist of digits") ;
    }

    if ( d.IsAfter(Date::GetTodaysDate()) ) // the date of birth cannot be after "today's date", i.e,
                                            // cannot be in future
        throw Bad_Passenger_DateOfBirth("Date of Birth can not be in future") ;

    // disability type is optional (can be NULL). But in case it is provided (not NULL), it must
    // be one of the 4 available disability types.
    if ( dt && dt != &Divyaang::Blind::Type() && dt != &Divyaang::OrthopaedicallyHandicapped::Type() && 
         dt != &Divyaang::CancerPatients::Type() && dt != &Divyaang::TBPatients::Type() )
        throw Bad_Passenger_DisabilityType("Invalid disability type for the Passenger") ;
    
    string copy = g ;
    // transform the gender entirely to lower-case so that case-insensitive matching
    // can be done, i.e, genders like "MaLe", "fEMaLE" etc are all valid
    transform(copy.begin(), copy.end(), copy.begin(), ::tolower) ;
    if ( copy != "male" )
        if ( copy != "female" )
            throw Bad_Passenger_Gender("Gender must be chosen between Male and Female only") ;
        else    // gender must be one of Male and Female
            return Passenger(d, Gender::Female::Type(), an, fn, mn, ln, mob, dt, did) ;
    else // this implies all the arguements are validated and a Passenger object can be constructed
        return Passenger(d, Gender::Male::Type(), an, fn, mn, ln, mob, dt, did) ;
        // return the constructed object by-value
}

// copy constructor
Passenger::Passenger ( const Passenger & p )
    : dateOfBirth_(p.dateOfBirth_) , gender_(p.gender_) , adhaarNumber_(p.adhaarNumber_) , firstName_(p.firstName_) , middleName_(p.middleName_) ,
      lastName_(p.lastName_) , mobileNumber_(p.mobileNumber_) , disabilityType_(p.disabilityType_) , disabilityID_(p.disabilityID_)
{   
    #ifdef _DEBUG
        cout << "Passenger CONSTRUCTED" << endl ;
    #endif
}

// overloaded equality check operator
// two Passenger objects are said to be "equal" if and only if
// they have the same values for all the non-static data members
bool Passenger::operator == ( const Passenger & p ) const
{
    if ( p.firstName_ != firstName_ )   return false ;
    if ( p.middleName_ != middleName_ )   return false ;
    if ( p.lastName_ != lastName_ )   return false ;
    if ( p.dateOfBirth_ != dateOfBirth_ )   return false ;
    if ( &p.gender_ != &gender_ )   return false ;
    if ( p.adhaarNumber_ != adhaarNumber_ )   return false ;
    if ( p.mobileNumber_ != mobileNumber_ )   return false ;
    if ( p.disabilityType_ != disabilityType_ )   return false ;
    if ( p.disabilityID_ != disabilityID_ )   return false ;
    return true ;
}

ostream & operator << ( ostream & out , const Passenger & p )
{
    out << endl ;
    // print all the details, in a proper format
    out << " Name = " << p.firstName_ + " " + p.middleName_ + " " + p.lastName_ << endl ;
    out << " Adhaar Card No. = " << p.adhaarNumber_ << endl ;
    out << " Date of Birth = " << p.dateOfBirth_ << endl ;  // Use "std::ostream &operator<<(std::ostream &, const Date &)"
    out << " Gender = " << p.gender_ << endl ;
    if ( p.mobileNumber_ != "" )
        out << " Mobile No. = " << p.mobileNumber_ << endl ;
    if ( p.disabilityType_ )
        out << " Disability Type = " << p.disabilityType_->GetName() << endl ;
    if ( p.disabilityID_ != "" )
        out << " Disability ID = " << p.disabilityID_ << endl ;
    out << endl ;
    return out ;    // returning the 'ostream' object is important for streaming 
                    // of multiple instances chained in the same instruction
}

// destructor
Passenger::~Passenger ( ) 
{     
    #ifdef _DEBUG
        cout << "Passenger DESTRUCTED" << endl ;
    #endif
}     // no explicit memory management needed -- no dynamically 
      // allocated memory for any data member -- hence empty body

// In order to model the test case of checking the erroneous
// disability type, an invalid Divyaang sub-type has to be introduced
// as given in the test plan document. 
struct DivTestType { } ;    // placeholder for the invalid static sub-type
// NOW DEFINE THE NECESSARY MEMBERS OF THE CLASS INSTANCE OF THE TEMPLATE WITH ARGUEMENT DivTestType
// give arbitrary values to the static const data members
template<> const string DivyaangTypes<DivTestType>::sName = "Test" ;
template<> const map<string, double> DivyaangTypes<DivTestType>::sConcessionFactors = { } ;
template <>
double DivyaangTypes<DivTestType>::GetConcessionFactor ( const BookingClass & b ) const
{ return 0.0 ; }    // return an arbitrary value

// implement the unit test plan written for Passenger
void Passenger::UnitTestPassenger ( )
{
    // CHECK ALL THE ERRONEOUS CASES
    try // try constructing a Passenger with no first and last name
    { Passenger::CreatePassenger(Date::CreateDate("16/11/2001"), "Male", "123456789012") ; }
    catch ( Bad_Passenger_Name )
    { cout << "   TEST CASE G.1.1 PASSED" << endl ; }
    
    try // try constructing a Passenger with adhaar number of length < 12
    { Passenger::CreatePassenger(Date::CreateDate("16/11/2001"), "Male", "12345678901", "John") ; }
    catch ( Bad_Passenger_AdhaarNumber )
    { cout << "   TEST CASE G.1.2.1 PASSED" << endl ; }

    try // try constructing a Passenger with adhaar number of length > 12
    { Passenger::CreatePassenger(Date::CreateDate("16/11/2001"), "Male", "1234567890123", "John") ; }
    catch ( Bad_Passenger_AdhaarNumber )
    { cout << "   TEST CASE G.1.2.2 PASSED" << endl ; }

    try // try constructing a Passenger with adhaar number having non-digit
    { Passenger::CreatePassenger(Date::CreateDate("16/11/2001"), "Male", "123456A78901", "John") ; }
    catch ( Bad_Passenger_AdhaarNumber )
    { cout << "   TEST CASE G.1.3 PASSED" << endl ; }

    try // try constructing a Passenger with mobile number of length < 10
    { Passenger::CreatePassenger(Date::CreateDate("16/11/2001"), "Male", "123456789012", "John", "", "", "999999999") ; }
    catch ( Bad_Passenger_MobileNumber )
    { cout << "   TEST CASE G.1.4.1 PASSED" << endl ; }

    try // try constructing a Passenger with mobile number of length > 10
    { Passenger::CreatePassenger(Date::CreateDate("16/11/2001"), "Male", "123456789012", "John", "", "", "99999999999") ; }
    catch ( Bad_Passenger_MobileNumber )
    { cout << "   TEST CASE G.1.4.2 PASSED" << endl ; }

    try // try constructing a Passenger with mobile number having non-digit
    { Passenger::CreatePassenger(Date::CreateDate("16/11/2001"), "Male", "123456789012", "John", "", "", "99999A9999") ; }
    catch ( Bad_Passenger_MobileNumber )
    { cout << "   TEST CASE G.1.5 PASSED" << endl ; }

    try  // try constructing a Passenger with date of birth in future
    { Passenger::CreatePassenger(Date::CreateDate("02/04/2022"), "Male", "123456789012", "John") ; }
    catch ( Bad_Passenger_DateOfBirth )
    { cout << "   TEST CASE G.1.6 PASSED" << endl ; }

    try  // try constructing a Passenger with invalid Disability type (use the invalid Divyaang sub-type)
    { Passenger::CreatePassenger(Date::CreateDate("01/01/2021"), "Male", "123456789012", "John", "", "", "", &DivyaangTypes<DivTestType>::Type()) ; }
    catch ( Bad_Passenger_DisabilityType )
    { cout << "   TEST CASE G.1.7 PASSED" << endl ; }

    try  // try constructing a Passenger with a gender other than Male and Female
    { Passenger::CreatePassenger(Date::CreateDate("01/01/2021"), "NewGender", "123456789012", "John") ; }
    catch ( Bad_Passenger_Gender )
    { cout << "   TEST CASE G.1.8 PASSED" << endl ; }

    // various test cases for valid Passenger objects
    // construct each one of them
    Passenger p1 = Passenger::CreatePassenger(Date::GetTodaysDate(), "Male", "123456789012", "John") ;
    Passenger p2 = Passenger::CreatePassenger(Date::CreateDate("01/01/2017"), "FeMaLe", "123456789012", "Jane") ;
    Passenger p3 = Passenger::CreatePassenger(Date::CreateDate("01/01/2017"), "MaLe", "123456789012", "", "", "Doe") ;
    Passenger p4 = Passenger::CreatePassenger(Date::CreateDate("01/01/2017"), "fEMaLe", "123456789012", "Jane", "", "", "9874563210") ;
    Passenger p5 = Passenger::CreatePassenger(Date::CreateDate("01/01/2017"), "Male", "123456789012", "John", "", "", "", &Divyaang::Blind::Type()) ;
    Passenger p6 = Passenger::CreatePassenger(Date::CreateDate("01/01/2017"), "mAlE", "123456789012", "John", "Jack", "Doe", "9874563210", &Divyaang::Blind::Type(), "ABC987") ;

    // now check if all the data members of these objects are correctly intiialized
    if ( p1.firstName_ == "John" && p1.middleName_ == "" && p1.lastName_ == "" && p1.dateOfBirth_ == Date::CreateDate("08/04/2021") &&  // here the expected dateOfBirth_ naturally
                                                                                                                                        // depends on the date of execution of the test plan.
                                                                                                                                        // Change the golden output accordingly otherwise it
                                                                                                                                        // might give a false FAIL
         Gender::IsMale(p1.gender_) && p1.adhaarNumber_ == "123456789012" && p1.mobileNumber_ == "" && p1.disabilityType_ == NULL && p1.disabilityID_ == "" )
         cout << "   TEST CASE G.1.9.1 PASSED" << endl ;

    if ( p2.firstName_ == "Jane" && p2.middleName_ == "" && p2.lastName_ == "" && p2.dateOfBirth_ == Date::CreateDate("01/01/2017") &&
         ! Gender::IsMale(p2.gender_) && p2.adhaarNumber_ == "123456789012" && p2.mobileNumber_ == "" && p2.disabilityType_ == NULL && p2.disabilityID_ == "" )
         cout << "   TEST CASE G.1.9.2 PASSED" << endl ;
        
    if ( p3.firstName_ == "" && p3.middleName_ == "" && p3.lastName_ == "Doe" && p3.dateOfBirth_ == Date::CreateDate("01/01/2017") &&
         Gender::IsMale(p3.gender_) && p3.adhaarNumber_ == "123456789012" && p3.mobileNumber_ == "" && p3.disabilityType_ == NULL && p3.disabilityID_ == "" )
         cout << "   TEST CASE G.1.9.3 PASSED" << endl ;

    if ( p4.firstName_ == "Jane" && p4.middleName_ == "" && p4.lastName_ == "" && p4.dateOfBirth_ == Date::CreateDate("01/01/2017") &&
         ! Gender::IsMale(p4.gender_) && p4.adhaarNumber_ == "123456789012" && p4.mobileNumber_ == "9874563210" && p4.disabilityType_ == NULL && p4.disabilityID_ == "" )
         cout << "   TEST CASE G.1.9.4 PASSED" << endl ;

    if ( p5.firstName_ == "John" && p5.middleName_ == "" && p5.lastName_ == "" && p5.dateOfBirth_ == Date::CreateDate("01/01/2017") &&
         Gender::IsMale(p5.gender_) && p5.adhaarNumber_ == "123456789012" && p5.mobileNumber_ == "" && p5.disabilityType_ == &Divyaang::Blind::Type() && p5.disabilityID_ == "" )
         cout << "   TEST CASE G.1.9.5 PASSED" << endl ;

    if ( p6.firstName_ == "John" && p6.middleName_ == "Jack" && p6.lastName_ == "Doe" && p6.dateOfBirth_ == Date::CreateDate("01/01/2017") &&
         Gender::IsMale(p6.gender_) && p6.adhaarNumber_ == "123456789012" && p6.mobileNumber_ == "9874563210" && p6.disabilityType_ == &Divyaang::Blind::Type() && p6.disabilityID_ == "ABC987" )
         cout << "   TEST CASE G.1.9.6 PASSED" << endl ;

    // testing copy constructor 
    Passenger pSource = Passenger::CreatePassenger(Date::CreateDate("01/01/2021"), "Female", "123456789012", "Jane", "John", "Doe", "9874563210", &Divyaang::Blind::Type(), "ABC123") ;
    Passenger pDest = pSource ;
    // check if all the data members of these objects are correctly intiialized
    if ( pDest.firstName_ == "Jane" && pDest.middleName_ == "John" && pDest.lastName_ == "Doe" && pDest.dateOfBirth_ == Date::CreateDate("01/01/2021") &&
         ! Gender::IsMale(pDest.gender_) && pDest.adhaarNumber_ == "123456789012" && pDest.mobileNumber_ == "9874563210" && pDest.disabilityType_ == &Divyaang::Blind::Type() && pDest.disabilityID_ == "ABC123" )
         cout << "   TEST CASE G.2.1 PASSED" << endl ;

    // print the Passenger object onto the console
    cout << "   TEST CASE G.3.1 -- " << pSource ;

    // TESTING NON-STATIC MEMBER FUNCTIONS
    // Construct Passenger objects, exhaustively covering all Gender sub-types
    Passenger p7 = Passenger::CreatePassenger(Date::CreateDate("01/01/2021"), "Female", "123456789012", "Jane") ;
    Passenger p8 = Passenger::CreatePassenger(Date::CreateDate("01/01/2021"), "Male", "123456789012", "John") ;
    if ( &p7.GetGender() == &Gender::Female::Type() )   // match the address of the returned instance with that of the
                                                        // sigleton instance of the Female Gender sub-type
        cout << "   TEST CASE G.4.1.1 PASSED" << endl ;
    if ( &p8.GetGender() == &Gender::Male::Type() )   // match the address of the returned instance with that of the
                                                      // sigleton instance of the Male Gender sub-type
        cout << "   TEST CASE G.4.1.2 PASSED" << endl ;
    
    // Construct Passenger object with an arbitrary Divyaang sub-type
    Passenger p9 = Passenger::CreatePassenger(Date::CreateDate("01/01/2021"), "Female", "123456789012", "Jane", "", "", "", &Divyaang::Blind::Type()) ;
    if ( p9.GetDisabilityType() == &Divyaang::Blind::Type() )   // match the address of the returned instance with that of the
                                                                // sigleton instance of the corresponding Divyaang sub-type
        cout << "   TEST CASE G.4.2.1 PASSED" << endl ;
    if ( p7.GetDisabilityType() == NULL )   // check if the default value of disability type was correctly initialized
        cout << "   TEST CASE G.4.2.2 PASSED" << endl ;

    Passenger p10 = Passenger::CreatePassenger(Date::CreateDate("30/11/2020"), "Female", "123456789012", "Jane") ;
    Passenger p11 = Passenger::CreatePassenger(Date::CreateDate("30/06/2020"), "Male", "123456789012", "John") ;
    Passenger p12 = Passenger::CreatePassenger(Date::CreateDate("16/11/2001"), "Male", "123456789012", "John") ;
    // call method and match with the golden output
    if ( p10.GetAge() == 0 )
        cout << "   TEST CASE G.4.3.1 PASSED" << endl ;
    if ( p11.GetAge() == 1 )
        cout << "   TEST CASE G.4.3.2 PASSED" << endl ;
    if ( p12.GetAge() == 19 )
        cout << "   TEST CASE G.4.3.3 PASSED" << endl ;
    
    // test overloaded equality check operator
    Passenger p13 = Passenger::CreatePassenger(Date::CreateDate("01/01/2021"), "Female", "123456789012", "Jane", "John", "Doe", "9874563210", &Divyaang::Blind::Type(), "ABC123") ;
    Passenger p14 = Passenger::CreatePassenger(Date::CreateDate("01/01/2021"), "Female", "123456789012", "Jane", "John", "Doe", "9874563210", &Divyaang::Blind::Type(), "ABC124") ;
    Passenger p15 = Passenger::CreatePassenger(Date::CreateDate("01/01/2021"), "Female", "123456789012", "Jane", "John", "Doe", "9874563210", &Divyaang::Blind::Type(), "ABC123") ;
    
    if ( ! ( p13 == p14 ) )
        cout << "   TEST CASE G.5.1 PASSED" << endl ;
    if ( p13 == p15 )
        cout << "   TEST CASE G.5.2 PASSED" << endl ;
}
