
//  SOFTWARE ENGINEERING -- ASSIGNMENT O5
//  NAKUL AGGARWAL  |   19CS10044

#pragma once
#include <iostream>
#include <exception>
using namespace std ;

// at LEVEL O1 of the hierarchy tree
class Bad_Station : public exception    
{  
    private :
        const char * description_ ; // data member -- stores the error message
    public :
        Bad_Station ( const char * x = "Bad_Station" ) throw()  // constructor
            :  description_(x) , exception()  
        {   
            #ifdef _DEBUG
                cout << "Bad_Station EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Station ( ) throw()    // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Station EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O1 of the hierarchy tree
class Bad_Railways : public exception    
{  
    protected :
        const char * description_ ;  // data member -- stores the error message
    public :
        Bad_Railways ( const char * x = "Bad_Railways" ) throw()  // constructor
            :  description_(x) , exception()  {   }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Railways ( ) throw() { }    // destructor
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Railways_NotEnoughStations : public Bad_Railways
{
    public :
        Bad_Railways_NotEnoughStations ( const char * x = "Bad_Railways_NotEnoughStations" ) throw()  // constructor
              :  Bad_Railways(x)  
        {   
            #ifdef _DEBUG
                cout << "Bad_Railways_NotEnoughStations EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Railways_NotEnoughStations ( ) throw()    // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Railways_NotEnoughStations EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Railways_DuplicateStations : public Bad_Railways
{
    public :
        Bad_Railways_DuplicateStations ( const char * x = "Bad_Railways_DuplicateStations" ) throw()
              :  Bad_Railways(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Railways_DuplicateStations EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Railways_DuplicateStations ( ) throw()    // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Railways_DuplicateStations EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Railways_DistBwSameStationsDefined : public Bad_Railways
{
    public :
        Bad_Railways_DistBwSameStationsDefined ( const char * x = "Bad_Railways_DistBwSameStationsDefined" ) throw()
              :  Bad_Railways(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Railways_DistBwSameStationsDefined EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Railways_DistBwSameStationsDefined ( ) throw()    // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Railways_DistBwSameStationsDefined EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Railways_NoDefinition : public Bad_Railways
{
    public :
        Bad_Railways_NoDefinition ( const char * x = "Bad_Railways_NoDefinition" ) throw()
              :  Bad_Railways(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Railways_NoDefinition EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Railways_NoDefinition ( ) throw()    // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Railways_NoDefinition EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Railways_RepeatedDefinition : public Bad_Railways
{
    public :
        Bad_Railways_RepeatedDefinition ( const char * x = "Bad_Railways_RepeatedDefinition" ) throw()
              :  Bad_Railways(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Railways_RepeatedDefinition EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Railways_RepeatedDefinition ( ) throw()     // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Railways_RepeatedDefinition EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Railways_Distance : public Bad_Railways
{
    public :
        Bad_Railways_Distance ( const char * x = "Bad_Railways_Distance" ) throw()
              :  Bad_Railways(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Railways_Distance EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Railways_Distance ( ) throw()    // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Railways_Distance EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;


/////////////////////////////////////////////////////////////////////

// at LEVEL O1 of the hierarchy tree
class Bad_Date : public exception    
{  
    protected :
        const char * description_ ; // data member -- stores the error message
    public :
        Bad_Date ( const char * x = "Bad_Date" ) throw()  // constructor
            :  description_(x) , exception()  {   }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Date ( ) throw() { }    // destructor
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Date_Format : public Bad_Date    
{  
    public :
        Bad_Date_Format ( const char * x = "Bad_Date_Format" ) throw()
              :  Bad_Date(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Date_Format EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Date_Format ( ) throw()    // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Date_Format EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Date_Year : public Bad_Date    
{  
    public :
        Bad_Date_Year ( const char * x = "Bad_Date_Year" ) throw()
              :  Bad_Date(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Date_Year EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Date_Year ( ) throw()     // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Date_Year EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Date_Month : public Bad_Date    
{  
    public :
        Bad_Date_Month ( const char * x = "Bad_Date_Month" ) throw()
              :  Bad_Date(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Date_Month EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Date_Month ( ) throw()     // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Date_Month EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Date_Day : public Bad_Date    
{  
    public :
        Bad_Date_Day ( const char * x = "Bad_Date_Day" ) throw()
              :  Bad_Date(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Date_Day EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Date_Day ( ) throw()     // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Date_Day EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;


/////////////////////////////////////////////////////////////////////

// at LEVEL O1 of the hierarchy tree
class Bad_Passenger : public exception    
{  
    protected :
        const char * description_ ; // data member -- stores the error message
    public :
        Bad_Passenger ( const char * x = "Bad_Passenger" ) throw()  // constructor
            :  description_(x) , exception()  {   }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Passenger ( ) throw() { }    // destructor
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Passenger_Name : public Bad_Passenger    
{  
    public :
        Bad_Passenger_Name ( const char * x = "Bad_Passenger_Name" ) throw()
              :  Bad_Passenger(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Passenger_Name EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Passenger_Name ( ) throw()     // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Passenger_Name EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Passenger_AdhaarNumber : public Bad_Passenger    
{  
    public :
        Bad_Passenger_AdhaarNumber ( const char * x = "Bad_Passenger_AdhaarNumber" ) throw()
              :  Bad_Passenger(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Passenger_AdhaarNumber EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Passenger_AdhaarNumber ( ) throw()     // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Passenger_AdhaarNumber EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Passenger_MobileNumber : public Bad_Passenger    
{  
    public :
        Bad_Passenger_MobileNumber ( const char * x = "Bad_Passenger_MobileNumber" ) throw()
              :  Bad_Passenger(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Passenger_MobileNumber EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Passenger_MobileNumber ( ) throw()     // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Passenger_MobileNumber EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Passenger_DateOfBirth : public Bad_Passenger    
{  
    public :
        Bad_Passenger_DateOfBirth ( const char * x = "Bad_Passenger_DateOfBirth" ) throw()
              :  Bad_Passenger(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Passenger_DateOfBirth EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Passenger_DateOfBirth ( ) throw()     // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Passenger_DateOfBirth EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Passenger_Gender : public Bad_Passenger    
{  
    public :
        Bad_Passenger_Gender ( const char * x = "Bad_Passenger_Gender" ) throw()
              :  Bad_Passenger(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Passenger_Gender EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Passenger_Gender ( ) throw()     // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Passenger_Gender EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Passenger_DisabilityType : public Bad_Passenger    
{  
    public :
        Bad_Passenger_DisabilityType ( const char * x = "Bad_Passenger_DisabilityType" ) throw()
              :  Bad_Passenger(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Passenger_DisabilityType EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Passenger_DisabilityType ( ) throw()     // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Passenger_DisabilityType EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;


/////////////////////////////////////////////////////////////////////

// at LEVEL O1 of the hierarchy tree
class Bad_Access : public exception    
{  
    private :
        const char * description_ ; // data member -- stores the error message
    public :
        Bad_Access ( const char * x = "Bad_Access" ) throw()  // constructor
            :  description_(x) , exception()  
        {   
            #ifdef _DEBUG
                cout << "Bad_Access EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Access ( ) throw()      // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Access EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;


/////////////////////////////////////////////////////////////////////

// at LEVEL O1 of the hierarchy tree
class Bad_Elligibility : public exception    
{  
    private :
        const char * description_ ; // data member -- stores the error message
    public :
        Bad_Elligibility ( const char * x = "Bad_Elligibility" ) throw()  // constructor
            :  description_(x) , exception()  
        {   
            #ifdef _DEBUG
                cout << "Bad_Elligibility EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Elligibility ( ) throw()      // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Elligibility EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;


/////////////////////////////////////////////////////////////////////

// at LEVEL O1 of the hierarchy tree
class Bad_Booking : public exception    
{  
    protected :
        const char * description_ ; // data member -- stores the error message
    public :
        Bad_Booking ( const char * x = "Bad_Booking" ) throw()  // constructor
            :  description_(x) , exception()  {   }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Booking ( ) throw() { }     // destructor
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Booking_UndefinedTerminals : public Bad_Booking    
{  
    public :
        Bad_Booking_UndefinedTerminals ( const char * x = "Bad_Booking_UndefinedTerminals" ) throw()
            :  Bad_Booking(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Booking_UndefinedTerminals EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Booking_UndefinedTerminals ( ) throw()      // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Booking_UndefinedTerminals EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Booking_DateOfBooking : public Bad_Booking    
{  
    public :
        Bad_Booking_DateOfBooking ( const char * x = "Bad_Booking_DateOfBooking" ) throw()
            :  Bad_Booking(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Booking_DateOfBooking EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Booking_DateOfBooking ( ) throw()      // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Booking_DateOfBooking EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Booking_BookingClass : public Bad_Booking    
{  
    public :
        Bad_Booking_BookingClass ( const char * x = "Bad_Booking_BookingClass" ) throw()
            :  Bad_Booking(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Booking_BookingClass EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Booking_BookingClass ( ) throw()      // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Booking_BookingClass EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Booking_BookingCategory : public Bad_Booking    
{  
    public :
        Bad_Booking_BookingCategory ( const char * x = "Bad_Booking_BookingCategory" ) throw()
            :  Bad_Booking(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Booking_BookingCategory EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Booking_BookingCategory ( ) throw()      // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Booking_BookingCategory EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;

// at LEVEL O2 of the hierarchy tree
class Bad_Booking_Passenger : public Bad_Booking    
{  
    public :
        Bad_Booking_Passenger ( const char * x = "Bad_Booking_Passenger" ) throw()
            :  Bad_Booking(x)    // constructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Booking_Passenger EXCEPTION CONSTRUCTED" << endl ;
            #endif
        }
        const char * what ( ) const throw() // non-static method -- returns the "const char *" data member
        { return description_ ; }
        ~Bad_Booking_Passenger ( ) throw()      // destructor
        {   
            #ifdef _DEBUG
                cout << "Bad_Booking_Passenger EXCEPTION DESTRUCTED" << endl ;
            #endif
        }
} ;


/*
The body of the destructors in all the classes was empty because there is no
need of any explicit memory management. There was no dynamic memory associated 
with any data member.
Default values are given for the srguement in the constructors for all the classes.
*/
