
//  SOFTWARE ENGINEERING -- ASSIGNMENT O3
//  NAKUL AGGARWAL  |   19CS10044

#include <iostream>
#include <string>
#include <vector>
using namespace std ;

// LEVEL 0 -- root in the polymorphic hierarchy tree
// abstract class
class BookingClass
{
    protected : // data members -- "protected" so that the derived
                // classes can access them
        string name_ ;
        string remarks_ ;
        double loadFactor_ ;
        bool isLuxury_ ;
        bool isAC_ ;
        virtual ~BookingClass ( ) ; // virtual destructor to prevent "object slicing"
    public :
        static const vector<double> sLoadFactors ;  // vector storing the load factors of all the booking-classes
        
        // polymorphic member functions to enable dynamic binding
        // based on the dynamic type of the variable
        virtual double GetLoadFactor ( ) const ;
        virtual string GetName ( ) const ;
        virtual bool IsSitting ( ) const = 0 ;
        virtual bool IsAC ( ) const ;
        virtual int GetNumberOfTiers ( ) const = 0 ;
        virtual bool IsLuxury ( ) const ;
        
        // overloaded output streaming operator -- "friend" function
        friend ostream & operator << ( ostream & , const BookingClass & ) ;

        // unit test
        static void UnitTestBookingClass ( ) ;
} ;

// LEVEL 1 -- specialize on the basis of "Seat" and "Berth"
// abstract class
class BookingClassSeat : public BookingClass
{
    protected :
        virtual ~BookingClassSeat ( ) ; // virtual destructor to prevent "object slicing"
    public : 
        bool IsSitting ( ) const ;  // override 'BookingClassSeat::IsSitting' function
        static void UnitTestSeat ( ) ;  // unit test
} ;

// LEVEL 2 -- specialize on the basis of number of tiers
// abstract class
class BookingClassSeatNoTier : public BookingClassSeat
{   
    protected :
        virtual ~BookingClassSeatNoTier ( ) ; // virtual destructor to prevent "object slicing"
    public : 
        int GetNumberOfTiers ( ) const ;    // override 'BookingClassSeat::GetNumberOfTiers' function
        static void UnitTestSeatNoTier ( ) ;    // unit test
} ;

// LEVEL 3 -- most specialized form
// concrete class
class BookingClassSeatNoTierAcOrdinary : public BookingClassSeatNoTier
{
    typedef BookingClassSeatNoTierAcOrdinary BCSNTAO ;
    private :
        // static constant to store the load factor of the booking class
        static const double sLoadFactor ;
        
        // private constructor -- in order to control the number of instances of this class
        BookingClassSeatNoTierAcOrdinary ( const string & , const string & ) ;
        
        // private destructor -- It is a good idea to make a destructor of a 'singleton' class 
        // private because then the client/application code won't call the destructor by accident.
        ~BookingClassSeatNoTierAcOrdinary ( ) ;

        // it is important to block the copy assignment operator for a "singleton" class
        const BCSNTAO & operator = ( const BCSNTAO & ) const {  }
    public :
        // This method acts as an interface or mediator between the client-side/application and the
        // private constructor. The internal routine of this method takes care of instantiating this class
        // only once -- when it is called for the first time. In subsequent calls, it simply returns the
        // same instance that is constructed in the first call.
        static const BCSNTAO & SpecialBookingClass ( const string & = "AC Chair Car (CC)" , const string & = "AC chairs" ) ;
        
        // unit test
        static void UnitTestSeatNoTierAcOrdinary ( ) ;
} ;

// LEVEL 3 -- most specialized form
// concrete class
class BookingClassSeatNoTierNonAcOrdinary : public BookingClassSeatNoTier
{
    typedef BookingClassSeatNoTierNonAcOrdinary BCSNTNO ;
    private :
        // static constant to store the load factor of the booking class
        static const double sLoadFactor ;

        // private constructor -- in order to control the number of instances of this class
        BookingClassSeatNoTierNonAcOrdinary ( const string & , const string & ) ;

        // private destructor -- It is a good idea to make a destructor of a 'singleton' class 
        // private because then the client/application code won't call the destructor by accident.
        ~BookingClassSeatNoTierNonAcOrdinary ( ) ;

        // it is important to block the copy assignment operator for a "singleton" class
        const BCSNTNO & operator = ( const BCSNTNO & ) const {  }
    public :
        // This method acts as an interface or mediator between the client-side/application and the
        // private constructor. The internal routine of this method takes care of instantiating this class
        // only once -- when it is called for the first time. In subsequent calls, it simply returns the
        // same instance that is constructed in the first call.
        static const BCSNTNO & SpecialBookingClass ( const string & = "Second Sitting (2S)" , const string & = "Bench seating" ) ;

        // unit test
        static void UnitTestSeatNoTierNonAcOrdinary ( ) ;
} ;

// LEVEL 1 -- specialize on the basis of "Seat" and "Berth"
// abstract class
class BookingClassBerth : public BookingClass
{   
    protected :
        virtual ~BookingClassBerth ( ) ; // virtual destructor to prevent "object slicing"
    public : 
        bool IsSitting ( ) const ;  // override 'BookingClassSeat::IsSitting' function
        static void UnitTestBerth ( ) ;  // unit test
} ;

// LEVEL 2 -- specialize on the basis of number of tiers
// abstract class
class BookingClassBerthDoubleTier : public BookingClassBerth
{  
    protected :
        virtual ~BookingClassBerthDoubleTier ( ) ; // virtual destructor to prevent "object slicing" 
    public : 
        int GetNumberOfTiers ( ) const ;    // override 'BookingClassSeat::GetNumberOfTiers' function 
        static void UnitTestBerthDoubleTier ( ) ;   // unit test   
} ;

// LEVEL 3 -- most specialized form
// concrete class
class BookingClassBerthDoubleTierAcLuxury : public BookingClassBerthDoubleTier
{
    typedef BookingClassBerthDoubleTierAcLuxury BCBDTAL ;
    private :
        // static constant to store the load factor of the booking class
        static const double sLoadFactor ;

        // private constructor -- in order to control the number of instances of this class
        BookingClassBerthDoubleTierAcLuxury ( const string & , const string & ) ;

        // private destructor -- It is a good idea to make a destructor of a 'singleton' class 
        // private because then the client/application code won't call the destructor by accident.
        ~BookingClassBerthDoubleTierAcLuxury ( ) ;

        // it is important to block the copy assignment operator for a "singleton" class
        const BCBDTAL & operator = ( const BCBDTAL & ) const {  }
    public :
        // This method acts as an interface or mediator between the client-side/application and the
        // private constructor. The internal routine of this method takes care of instantiating this class
        // only once -- when it is called for the first time. In subsequent calls, it simply returns the
        // same instance that is constructed in the first call.
        static const BCBDTAL & SpecialBookingClass ( const string & = "AC First Class (1A)" , const string & = "AC 2 berth coupe" ) ;
        
        // unit test
        static void UnitTestBerthDoubleTierAcLuxury ( ) ;
} ;

// LEVEL 3 -- most specialized form
// concrete class
class BookingClassBerthDoubleTierAcOrdinary : public BookingClassBerthDoubleTier
{
    typedef BookingClassBerthDoubleTierAcOrdinary BCBDTAO ;
    private :
        // static constant to store the load factor of the booking class
        static const double sLoadFactor ;

        // private constructor -- in order to control the number of instances of this class
        BookingClassBerthDoubleTierAcOrdinary ( const string & , const string & ) ;

        // private destructor -- It is a good idea to make a destructor of a 'singleton' class 
        // private because then the client/application code won't call the destructor by accident.
        ~BookingClassBerthDoubleTierAcOrdinary ( ) ;

        // it is important to block the copy assignment operator for a "singleton" class
        const BCBDTAO & operator = ( const BCBDTAO & ) const {  }
    public :
        // This method acts as an interface or mediator between the client-side/application and the
        // private constructor. The internal routine of this method takes care of instantiating this class
        // only once -- when it is called for the first time. In subsequent calls, it simply returns the
        // same instance that is constructed in the first call.
        static const BCBDTAO & SpecialBookingClass ( const string & = "AC 2 Tier (2A)" , const string & = "AC 2 berth inside, 2 berth on side" ) ;
        
        // unit test
        static void UnitTestBerthDoubleTierAcOrdinary ( ) ;
} ;

// LEVEL 3 -- most specialized form
// concrete class
class BookingClassBerthDoubleTierNonAcLuxury : public BookingClassBerthDoubleTier
{
    typedef BookingClassBerthDoubleTierNonAcLuxury BCBDTNL ;
    private :
        // static constant to store the load factor of the booking class
        static const double sLoadFactor ;

        // private constructor -- in order to control the number of instances of this class
        BookingClassBerthDoubleTierNonAcLuxury ( const string & , const string & ) ;

        // private destructor -- It is a good idea to make a destructor of a 'singleton' class 
        // private because then the client/application code won't call the destructor by accident.
        ~BookingClassBerthDoubleTierNonAcLuxury ( ) ;

        // it is important to block the copy assignment operator for a "singleton" class
        const BCBDTNL & operator = ( const BCBDTNL & ) const {  }
    public :
        // This method acts as an interface or mediator between the client-side/application and the
        // private constructor. The internal routine of this method takes care of instantiating this class
        // only once -- when it is called for the first time. In subsequent calls, it simply returns the
        // same instance that is constructed in the first call.
        static const BCBDTNL & SpecialBookingClass ( const string & = "First Class (FC)" , const string & = "Non-AC 2 berth coupe" ) ;
        
        // unit test
        static void UnitTestBerthDoubleTierNonAcLuxury ( ) ;
} ;

// LEVEL 2 -- specialize on the basis of number of tiers
// abstract class
class BookingClassBerthTripleTier : public BookingClassBerth
{   
    protected :
        virtual ~BookingClassBerthTripleTier ( ) ;  // virtual destructor to prevent "object slicing"
    public : 
        int GetNumberOfTiers ( ) const ;   // override 'BookingClassSeat::GetNumberOfTiers' function
        static void UnitTestBerthTripleTier ( ) ;   // unit test   
} ;

// LEVEL 3 -- most specialized form
// concrete class
class BookingClassBerthTripleTierAcOrdinary : public BookingClassBerthTripleTier
{
    typedef BookingClassBerthTripleTierAcOrdinary BCBTTAO ;
    private :
        // static constant to store the load factor of the booking class
        static const double sLoadFactor ;

        // private constructor -- in order to control the number of instances of this class
        BookingClassBerthTripleTierAcOrdinary ( const string & , const string & ) ;

        // private destructor -- It is a good idea to make a destructor of a 'singleton' class 
        // private because then the client/application code won't call the destructor by accident.
        ~BookingClassBerthTripleTierAcOrdinary ( ) ;

        // it is important to block the copy assignment operator for a "singleton" class
        const BCBTTAO & operator = ( const BCBTTAO & ) const {  }
    public :
        // This method acts as an interface or mediator between the client-side/application and the
        // private constructor. The internal routine of this method takes care of instantiating this class
        // only once -- when it is called for the first time. In subsequent calls, it simply returns the
        // same instance that is constructed in the first call.
        static const BCBTTAO & SpecialBookingClass ( const string & = "AC 3 Tier (3A)" , const string & = "AC 3 berth inside, 2 berth onside" ) ;
        
        // unit test
        static void UnitTestBerthTripleTierAcOrdinary ( ) ;
} ;

// LEVEL 3 -- most specialized form
// concrete class
class BookingClassBerthTripleTierNonAcOrdinary : public BookingClassBerthTripleTier
{
    typedef BookingClassBerthTripleTierNonAcOrdinary BCBTTNO ;
    private :
        // static constant to store the load factor of the booking class
        static const double sLoadFactor ;

        // private constructor -- in order to control the number of instances of this class
        BookingClassBerthTripleTierNonAcOrdinary ( const string & , const string & ) ;

        // private destructor -- It is a good idea to make a destructor of a 'singleton' class 
        // private because then the client/application code won't call the destructor by accident.
        ~BookingClassBerthTripleTierNonAcOrdinary ( ) ;

        // it is important to block the copy assignment operator for a "singleton" class
        const BCBTTNO & operator = ( const BCBTTNO & ) const {  }
    public :
        // This method acts as an interface or mediator between the client-side/application and the
        // private constructor. The internal routine of this method takes care of instantiating this class
        // only once -- when it is called for the first time. In subsequent calls, it simply returns the
        // same instance that is constructed in the first call.
        static const BCBTTNO & SpecialBookingClass ( const string & = "Sleeper (SL)" , const string & = "Non-AC 3 berth inside, 2 berth onside" ) ;
        
        // unit test
        static void UnitTestBerthTripleTierNonAcOrdinary ( ) ;
} ;


/*


[ SUMMARY ]

        |-  BookingClass
            |-  BookingClassSeat
                |-  BookingClassSeatNoTier
                    |-  BookingClassSeatNoTierACOrdinary*
                    |-  BookingClassSeatNoTierNonACOrdinary*
            |-  BookingClassBerth
                |-  BookingClassBerthDoubleTier
                    |-  BookingClassBerthDoubleTierACLuxury*
                    |-  BookingClassBerthDoubleTierACOrdinary*
                    |-  BookingClassBerthDoubleTierNonACLuxury*
                |-  BookingClassBerthTripleTier
                    |-  BookingClassBerthTripleTierACOrdinary*
                    |-  BookingClassBerthTripleTierNonACOrdinary*

(* - concrete class)



[ KEY POINTS ]

(1.)    The name and remarks for the singleton instances of all the concrete booking class can be 
        passed as parameters in the first call to 'SpecialBookingClass' method (qualified by the name
        of the booking class). Though default values are chosen from the "master data" in the assignment,
        the concrete booking classes are not directly named after them. Passing name/ remarks for a booking 
        class by parameters is far better than permanently naming the classes based on the name of the 
        "Indian Booking Classes" which not only reduces readability of the code (one might not be able 
        to interpret the attributes of a class "ACChairCar" by merely reading its name, especially when a 
        foreigner is working on the client side, but attributes of the class 'BookingClassSeatNoTierAcOrdinary' 
        are clear from its name); but also reduces the flexibility of using this "polymorphic booking-class 
        hierarchy" for more other similar purposes (one might want to develop a booking system for "French 
        Railways" with same booking classes with exactly same properties on the client-side, but use French 
        names for the booking classes in place of English). If this happens, the developer will have to change
        the names of all the 7 classes, not only in this file but also in "BookingClass.cpp" file.

(2.)    The destructor is kept private in all the concrete booking classes. It is a good idea 
        to make a destructor of a 'singleton' class private because then the client/application code 
        won't call the destructor by accident. Calling the destructor would cause the singleton to 
        fail for all applications in the project as the instance would become invalid.

(3.)    In order to enable dynamic dispatch of destructor and prevent "object slicing", the destructor 
        in the base class(es) of a polymorphic hierarchy must also be made polymorphic (by using 'virtual' 
        keyword). Here there are total 6 base classes and all of them have a "protected" virtual destructor.
        The destructors in these abstract base classes are kept "protected" and not "private" like in the 
        concrete classes, because the instance of all the concrete classes have a base class object as a 
        part of their "object layout". Therefore the call to the destructor of an instance of a derived 
        class is followed by the call to the destructor of the base class. For this, the destructor of 
        the base class must actually be accessible to the derived class. Therefore, the destructors in all
        the abstract base classes are not kept "private".
        Besides, the destructors in all the abstract base classes are not kept "public" either because
        of a similar reason as given in the last key point. If the destructor of any base class is made
        public in a polymorphic hierarchy in which all leaf classes are singletons, then if it gets
        called accidently, this would destruct the base class part in the derived class instance
        causing the singleton to fail for all applications in the project as the instance would become 
        invalid.
        Therefore the best access-specifier for the destructors in the abstract base classes is protected
        which is both (1) available to the concrete derived classes and (2) private for the global scope/
        outside the hierarchy.


*/