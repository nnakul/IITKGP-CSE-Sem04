
#include <iostream>
#include "Fraction.hpp"
using namespace std ;

const Fraction Fraction::sc_fUnity = Fraction(1) ;
const Fraction Fraction::sc_fZero = Fraction(0) ;
const int Fraction::__precision__ = 10000 ;

void Fraction::normalize ( int & x , int & y )
{
    if ( ! y )  exit(1) ;   // MUST IMMEDIATELY EXIT THE PROGRAM IF NORMALIZATION OF
                            // A FRACTION WITH ZERO DENOMINATOR IS TRIED !
    if ( ! x )  { y = 1 ; return ; }    //  if numerator is 0, denominator is specifically chosen to be 1
    if ( y < 0 )   { x *= -1 ; y *= -1 ; }  //  denominator must be positive
    int g = gcd(abs(x), abs(y)) ;   //  reduce the numerator and the denominator to the simplest form
    x /= g ; y /= g ;               //  by dividing them by their GCD
    return ;
}


Fraction::Fraction ( int n , int d )    //  CONSTRUCTOR -- FIRST OVERLOAD
{
    if ( ! d )  exit(1) ;   //  must NOT proceed if the denominator is 0 -- leads to UNDEFINED fraction
                            //  'exit' causes the program to terminate.
    
    if ( d != 1 )   //  no simplification needed if the denominator is already 1.

        normalize(n, d) ;   //  calls the private helper member function to reduce the numerator
                            //  and denominator to the simplest form. The changes performed in the
                            //  helper-functions's scope are reflected in this function's local variables n
                            //  and d because the parameters are passed by reference.
    
    numerator = n ; denominator = d ;   //  finally the modified values assigned to the data members of the instance.
                                        //  Now the Fraction object is perfectly initialized.
    return ;
}

Fraction::Fraction ( double doub )  //  CONSTRUCTOR -- SECOND OVERLOAD
{
    int n = (int) ( doub * __precision__ ) ;   // uses preset 'int' precision to initialize
    int d = __precision__ ;                     // the "raw" values of numerator and denoinator
    
    normalize(n, d) ;   //  n and d are brough to their simplest forms and now they can be
                        //  assigned to the instance's data members.
    
    numerator = n ; denominator = d ;   //  finally the modified values assigned to the data members of the instance.
                                        //  Now the Fraction object is perfectly initialized.
    return ;
}

Fraction::Fraction ( const Fraction & f ) : //  CONSTRUCTOR -- THIRD OVERLOAD (COPY CONSTRUCTOR)
    numerator(f.numerator) , denominator(f.denominator) // data members simply assigned in the initializer list itself
{   }   //  empty body -- no further computation required

Fraction::~Fraction ( ) // DESTRUCTOR
{
    /*
        +++ NO BODY NEEDED +++
        All data members are built-in primitive data types.
        No dynamically allocated memory associated to any instance of the class.
        No return statement.
    */
}

Fraction& Fraction::operator = ( const Fraction & f )   // OPERATOR OVERLOADING
{
    numerator = f.numerator ;       // copying the values of the data members of the RHS
    denominator = f.denominator ;   // Fraction instance to the data members of the LHS
                                    // Fraction instance.
    return *this ;  // return the instance on which the method was called 
                    // by reference to enable chaining of assignment operators
}

Fraction Fraction::operator - ( ) const     // OPERATOR OVERLOADING
{
    return Fraction(-1*numerator, denominator) ;    // constructing and returning (by value) a new Fraction
                                                    // instance which has the -ve of the numerator and same
                                                    // denominator as the instance on which the method was called.
}

Fraction Fraction::operator + ( ) const     // OPERATOR OVERLOADING
{
    return Fraction(numerator, denominator) ;   // constructing and returning (by value) a new Fraction
                                                // instance which has the same numerator and same
                                                // denominator as the instance on which the method was called.
}

Fraction& Fraction::operator -- ( )     // OPERATOR OVERLOADING
{
    numerator -= denominator ;  // subtracting 1 from a fraction means subtracting
                                // denominator from the numerator and keeping the
                                // former intact.
    normalize(numerator,denominator) ;  // the fraction needs to be re-simplified.
    return *this ;  // return the instance on which the method was called 
                    // by reference to enable chaining of assignment operators
}

Fraction& Fraction::operator ++ ( )     // OPERATOR OVERLOADING
{
    numerator += denominator ;  // adding 1 to a fraction means adding
                                // denominator to the numerator and keeping the
                                // former intact.
    normalize(numerator,denominator) ;  // the fraction needs to be re-simplified.
    return *this ;  // return the instance on which the method was called 
                    // by reference to enable chaining of assignment operators
}

Fraction Fraction::operator -- ( int )      // OPERATOR OVERLOADING
{
    Fraction f = *this ;    // copy the instance to a new object that can remember
                            // the current state of the instance
    numerator -= denominator ;  // subtracting 1 from a fraction means subtracting
                                // denominator from the numerator and keeping the
                                // former intact.
    normalize(numerator,denominator) ;  // the fraction needs to be re-simplified.
    return f ;  // return the object that remembers the old state of the instance
}

Fraction Fraction::operator ++ ( int )      // OPERATOR OVERLOADING
{
    Fraction f = *this ;    // copy the instance to a new object that can remember
                            // the current state of the instance
    numerator += denominator ;  // adding 1 to a fraction means adding
                                // denominator to the numerator and keeping the
                                // former intact.
    normalize(numerator,denominator) ;  // the fraction needs to be re-simplified.
    return f ;  // return the object that remembers the old state of the instance
}

Fraction operator + ( const Fraction & l , const Fraction & r )      // OPERATOR OVERLOADING
{
    return Fraction( l.numerator*r.denominator + r.numerator*l.denominator , 
                    l.denominator * r.denominator ) ;     // constructed a new Fraction object that stores the result
                                                        // and then is returned by value
}

Fraction operator - ( const Fraction & l , const Fraction & r )      // OPERATOR OVERLOADING
{
    return Fraction( l.numerator*r.denominator - r.numerator*l.denominator ,
                    l.denominator * r.denominator ) ;     // constructed a new Fraction object that stores the result
                                                        // and then is returned by value
}

Fraction operator * ( const Fraction & l , const Fraction & r )      // OPERATOR OVERLOADING
{
    return Fraction( l.numerator * r.numerator , l.denominator * r.denominator ) ;  // constructed a new Fraction object that stores 
                                                                                // the result and then is returned by value
}

Fraction operator / ( const Fraction & l , const Fraction & r )      // OPERATOR OVERLOADING
{
    try
    {
        if (r != Fraction::sc_fZero)      // ensure that the second operand is non-zero
            return Fraction( l.numerator * r.denominator , l.denominator * r.numerator ) ;  // constructed a new Fraction object that stores the result
                                                                                        // and then is returned by value
        else    throw 001 ;     // if the second operand is zero, throw an exception
    }
    catch ( int code )
    {
        cout << endl << " *** SECOND OPERAND OF DIVISION OPERATOR CANNOT BE ZERO ***" << endl ;
        return Fraction::sc_fZero ;   // the return type is Fraction; ZERO-fraction is arbitrarily chosen to be returned in case an exception occurs.
    }
}

Fraction operator % ( const Fraction & left , const Fraction & right )      // OPERATOR OVERLOADING
{
    try
    {
        if (right != Fraction::sc_fZero)      // ensure that the SECOND OPERAND IS NON-ZERO
        {
            Fraction res = left ;    // residue initialized to the first operand

            //  CASE 1 -- SECOND OPERAND IS POSITIVE
            if ( right > Fraction::sc_fZero )
            {
                //  CASE 1.1 -- FIRST OPERAND IS NON NEGATIVE
                if ( res >= Fraction::sc_fZero )   
                {
                    while ( res >= right )      // the second operand is iteratively subtracted from
                        res = res - right ;     // the residue while the former is not greater than the latter
                    return res ;
                }
                //  CASE 1.2 -- FIRST OPERAND IS NEGATIVE
                else
                {
                    while ( res < Fraction::sc_fZero )    // the second operand is iteratively added to the residue
                        res = res + right ;               // while the latter is negative
                    return res ;
                }
            }

            //  CASE 2 -- SECOND OPERAND IS NEGATIVE
            else
            {
                //  CASE 2.1 -- FIRST OPERAND IS NEGATIVE
                if ( res < Fraction::sc_fZero )
                {
                    while ( true )
                    {
                        Fraction t = res - right ;                  //  continue subtracting the second operand from the
                        if ( t > Fraction::sc_fZero )   break ;     //  residue as long as the residue remains non-positive
                        res = t ;
                    }
                    return res ;
                }
                //  CASE 2.2 -- FIRST OPERAND IS NON NEGATIVE
                else
                {
                    while ( res > Fraction::sc_fZero )     // the second operand is iteratively added to the residue
                        res = res + right ;                // while the latter is positive
                    return res ;
                }
            }
        }

        //  CASE 3 -- SECOND OPERAND IS ZERO
        else    throw 002 ;          // if the second operand is zero, throw an exception
    }
    catch ( int code )
    {
        cout << endl << " *** SECOND OPERAND OF MODULUS OPERATOR CANNOT BE ZERO ***" << endl ;
        return Fraction::sc_fZero ;   // the return type is Fraction; ZERO-fraction is arbitrarily chosen to be returned in case an exception occurs.
    }
}

bool Fraction::operator == ( const Fraction & f ) const     // OPERATOR OVERLOADING
{
    return denominator == f.denominator && numerator == f.numerator ;   // check equality of fractions and return the boolean answer
}

bool Fraction::operator != ( const Fraction & f ) const     // OPERATOR OVERLOADING
{
    return denominator != f.denominator || numerator != f.numerator ;   // check inequality of fractions and return the boolean answer
}

bool Fraction::operator < ( const Fraction & f ) const      // OPERATOR OVERLOADING
{
    return numerator * f.denominator < denominator * f.numerator ;   // check if LHS fraction is less than RHS fraction and return the boolean answer
}

bool Fraction::operator > ( const Fraction & f ) const      // OPERATOR OVERLOADING
{
    return numerator * f.denominator > denominator * f.numerator ;  // check if LHS fraction is more than RHS fraction and return the boolean answer
}

bool Fraction::operator <= ( const Fraction & f ) const     // OPERATOR OVERLOADING
{
    return numerator * f.denominator <= denominator * f.numerator ; // check if LHS fraction is less than or equal to RHS fraction and return the boolean answer
}

bool Fraction::operator >= ( const Fraction & f ) const     // OPERATOR OVERLOADING
{
    return numerator * f.denominator >= denominator * f.numerator ; // check if LHS fraction is more than or equal to RHS fraction and return the boolean answer
}

Fraction Fraction::operator ! ( ) const     // OPERATOR OVERLOADING
{
    try
    {
        if (*this != sc_fZero)      // ensure that the operand is non-zero
            return Fraction( denominator , numerator ) ;    // return the reciprocal of the operand as a new instance (return-by-value)
        else    throw 003 ;     // if the operand is zero, throw an exception
    }
    catch ( int code )
    {
        cout << endl << " *** INVERTED FRACTION DOES NOT EXIST FOR ZERO ***" << endl ;
        return sc_fZero ;   // the return type is Fraction; ZERO-fraction is arbitrarily chosen to be returned in case an exception occurs.
    }
}

int Fraction::precision ( )     // UTILITY FUNCTION OF THE DATATYPE
{
    return __precision__ ;      // return the value of the static data member -- __precision__
}

int Fraction::gcd ( unsigned int a , unsigned int b )     // UTILITY FUNCTION OF THE DATATYPE
{
    //  ++ recursive algorithm ++
    //  Using Euclidean algorithm 
    //  The idea is, GCD of two numbers doesn’t change if 
    //  smaller number is subtracted from a bigger number. 
    if ( ! a ) return b ;   //  handling base case 1
    if ( ! b ) return a ;   //  handling base case 2
    if ( a == b ) return a ;   //  handling trivial case
    if ( a > b )    return gcd(a-b, b) ;    // breaking problem into sub-problem
    return gcd(a, b-a) ;    // breaking problem into sub-problem
}


int Fraction::lcm ( unsigned int a , unsigned int b )     // UTILITY FUNCTION OF THE DATATYPE
{
    return ( a * b ) / gcd(a, b) ;  //  uses the utility function "Fraction::gcd"
}

istream & operator >> ( istream & in ,  Fraction & f )  // OVERLOADING INPUT STREAMING OPERATOR
{
    in >> f.numerator >> f.denominator ;    // reads content on the istream object "in" and assigns to
                                            // the data members of the Fraction object
                                            // private data members accessible because of "friendship"
    Fraction::normalize(f.numerator, f.denominator) ;       // the fraction needs to be re-simplified.
    return in ;    // return the istream object to allow the chaining of input
}

ostream & operator << ( ostream & out , const Fraction & f )  // OVERLOADING OUTPUT STREAMING OPERATOR
{
    out << " " << f.numerator ;     // writes content on the ostream object "out"
                                    // private data members accessible because of "friendship"
    if ( f.denominator != 1 )   //  no need to write the denominator if it is 1 (print fraction in integeral format)
        out << " / " << f.denominator ;
    return out ;    // return the ostream object to allow the chaining of output
}

