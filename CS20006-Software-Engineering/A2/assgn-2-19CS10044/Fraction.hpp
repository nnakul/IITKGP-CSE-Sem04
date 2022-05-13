
#include <cmath>
#include <iostream>
using namespace std ;


class Fraction {

    private :
        int numerator ;     // Data member that stores the numerator of the "Fraction" object.
                            // Kept private to ensure security and avoid data corruption.
        
        int denominator ;   // Data member that stores the denominator of the "Fraction" object.
                            // Kept private to ensure security and avoid data corruption.
        
        static const int __precision__ ;   // Data member that stores the integral value of the precision that
                                           // is used in converting double to "Fraction". Declared as a static 
                                           // data member because precision is not characteristic to a particular
                                           // instance of Fraction class but is rather a value that is used
                                           // in constructing fractions from double. It is kept private to ensure
                                           // that it is not tampered accidentally/intentionally and remains intact. 
                                           // To ensure its "const-ness" while it can be accessed by the member
                                           // functions of the class, 'const' keyword is used. This increases the 
                                           // security of this data member and ensures that even the member functions
                                           // cannot modify this value.
        
        /*
        It is a helper function that takes two integer values (first one a numerator and second the denominator)
        and reduces them to simpler values such that -- (a) the denominator is positive and (b) the greatest
        common divisor of the absolute value of numerator (>0) and denominator is 1 and (c) if numerator is
        zero, makes denominator one. It is apt to pass the int values by reference because this function is responsible
        for computing two values but it can return only one. It is far simpler to pass the un-simplified numerator 
        and denominator by reference than to build another UDT specifically to be able to return a "pair" of values.
        It is private member function because it is needed only as a "helping-hand" by other member functions tethered
        to only this class. It is a static member function because all it needs to function is two integeral values 
        (that are passed by reference), and not any 'Fraction' object to operate on or deduce from.
        */
        static void normalize ( int & , int & ) ;

    public :
        static const Fraction sc_fUnity ;   // Data member that stores the mathematical value of ONE in a
                                            // fractional form. It should obviously be a public data member
                                            // so that the "ready-made" unity-fraction can be used anywhere
                                            // outside the class. It is declared as a static data member
                                            // because it does not define the state of any instance of this
                                            // class but it still makes sense for it to be present in a namespace
                                            // dedicated to "fractions". It is obviously declared as a constant
                                            // ('const' keyword) data member because 1 is a mathematical constant.
        
        static const Fraction sc_fZero ;    // Data member that stores the mathematical value of ZERO in a
                                            // fractional form. It should obviously be a public data member
                                            // so that the "ready-made" zero-fraction can be used anywhere
                                            // outside the class. It is declared as a static data member
                                            // because it does not define the state of any instance of this
                                            // class but it still makes sense for it to be present in a namespace
                                            // dedicated to "fractions". It is obviously declared as a constant
                                            // ('const' keyword) data member because 0 is a mathematical constant.
       
        /*
        It is a constructor with two 'int' parameters to initialize the values of numerator and denominator 
        respectively. Constructors have the same name as the class' name.
        Default values of 1 are provided for each of the two parameters. It can be invoked as 
        a default constructor (without any parameters) or with one/two parameters. Constructors do not have 
        a return type (not even 'void').
        */
        Fraction ( int = 1 , int = 1 ) ;
        
        /*
        It is a constructor with one 'double' parameter. Constructors have the same name as the class' name.
        The values of numerator and denominator are initialized based on a preset 'int' precision. Constructors
        do not have a return type (not even 'void'). The 'explicit' keyword ensures that 'double' values are not
        implicitly converted to a 'Fraction' object.
        */
        explicit Fraction ( double ) ;
        
        /*
        It is a copy constructor for initializing the data members from an existing value. Constructors 
        have the same name as the class' name. It consists of one parameter of the user-defined type -- Fraction.
        The parameter is passed by reference; otherwise the call to copy constructor itself will need to use
        a copying mechanism to copy the passed parameter to the local arguement (an infinite loop of copying). 
        To avoid the risk of changing the actual parameter passed by reference, 'const' keyword is used. This 
        ensures that the state of the actual parameter stays intact. Constructors do not have a 
        return type (not even 'void').
        */
        Fraction ( const Fraction & ) ;

        /*
        It is a destructor of 'Fraction' class. Destructors always have the same name as the class' name preceeded 
        by a tilde, '~'. They do not have a return type (not even 'void'). No parameters are allowed for destructors.
        */
        ~Fraction ( ) ;
        
        /*
        This method overloads the copy assignment operator '='. The Fraction object on the RHS of the operator is 
        passed-by-reference. This is redundant (unlike in the copy constructor's signature) but it saves an extra 
        call/overhead to the copy constructor to copy the passed value to the local parameter. To avoid the risk of 
        changing the actual parameter that is passed by reference, 'const' keyword is used to make the local parameter
        a constant reference to the actual one. This ensures that the state of the actual parameter stays intact. 
        To enable the chaining of multiple assignment operations (like a = b = c = f), the object/instance on 
        which the operator method is called (LHS operand) is returned to the caller function, and therefore  
        the return type is 'Fraction'. The object is returned by reference to avoid any additional copying 
        costs. Besides, return-by-reference is legal because the object that is returned is NOT a local variable.
        */
        Fraction& operator = ( const Fraction & ) ;

        /*
        This method overloads the unary '-' operator. Since it is a unary operator, it has no
        parameters. It creates a negative copy of the 'fraction' instance on which the operator method 
        is called, i.e, -(p/q) -> (-p/q). The new instance created is returned-by-value 
        because it is a local object and hence the return type is 'Fraction'. 'const' keyword before
        the semicolon declares this operator method as a constant method. It ensures that the state of the 
        object on which the operator is performed remains intact.
        */
        Fraction operator - ( ) const ;
        
        /*
        This method overloads the unary '+' operator. Since it is a unary operator, it has no
        parameters. It creates a positive copy (esentially an object with the same state) of the 'Fraction' 
        instance on which the operator method is called, i.e, +(p/q) -> (+p/q). The new instance created is
        returned-by-value because it is a local object and hence the return type is 'Fraction'.
        'const' keyword before the semicolon declares this function as a constant method. It ensures
        that the state of the object on which the operator is performed remains intact.
        */
        Fraction operator + ( ) const ;

        /*
        This method overloads the prefix decrement '--' operator. Since it is a prefix operator, it has no
        parameters. This operator when performed on a 'Fraction' object, subtracts 1 from the fraction.
        Since it is a prefix decrement, the changes must be reflected in the object that is returned.
        In other words, let f be an instance of Fraction ( f = p/q ). "Fraction g = --f" not only changes 
        f to (p-q)/q, but also assigns g as (p-q)/q. Because the state of the instance that is returned by
        this operator method is identical to the new state attained by the object on which this operator is
        performed, this method returns the latter by-reference (notice "Fraction &") by eliminating the
        construction of another instance with the same state. Note that the object on which this method is called
        (or on which the operator is performed) can be returned by reference because it is not a local object.
        Obviously this operator is authorised to change the state of the object and hence is not declared as a
        constant operator method.
        */
        Fraction& operator -- ( ) ;

        /*
        This method overloads the prefix increment '++' operator. Since it is a prefix operator, it has no
        parameters. This operator when performed on a 'Fraction' object, adds 1 to the fraction.
        Since it is a prefix increment, the changes must be reflected in the object that is returned.
        In other words, let f be an instance of Fraction ( f = p/q ). "Fraction g = ++f" not only changes 
        f to (p+q)/q, but also assigns g as (p+q)/q. Because the state of the instance that is returned by
        this operator method is identical to the new state attained by the object on which this operator is
        performed, this method returns the latter by-reference (notice "Fraction &") by eliminating the
        construction of another instance with the same state. Note that the object on which this method is called
        (or on which the operator is performed) can be returned by reference because it is not a local object.
        Obviously this operator is authorised to change the state of the object and hence is not declared as a constant
        operator method.
        */
        Fraction& operator ++ ( ) ;

        /*
        This method overloads the postfix decrement '--' operator. Since it is a postfix operator, it must have
        an 'int' parameter. This operator when performed on a 'Fraction' object, subtracts 1 from the fraction.
        Since it is a postfix decrement, the changes must NOT be reflected in the object that is returned. In 
        other words, let f be an instance of Fraction ( f = p/q ). "Fraction g = f--", only changes f to (p-q)/q, 
        and assigns g as p/q, the former state of f. Because the state of the instance that is returned by this 
        operator method is identical to the "former" state of the object on which this operator method is called, 
        this method first creates a copy of the instance before making any changes to that, then it introduces
        necessary changes on the state of the instance (subtracts 1) whose copy was created; and finally it returns 
        the copy that is present at the old/former state of the instance. The return is by-value because the copy 
        is a local object/variable. Obviously this operator is authorised to change the state of the object and 
        hence is not declared as a constant operator method.
        */
        Fraction operator -- ( int ) ;

        /*
        This method overloads the postfix increment '++' operator. Since it is a postfix operator, it must have
        an 'int' parameter. This operator when performed on a 'Fraction' object, adds 1 to the fraction.
        Since it is a postfix increment, the changes must NOT be reflected in the object that is returned. In 
        other words, let f be an instance of Fraction ( f = p/q ). "Fraction g = f++", only changes f to (p+q)/q, 
        and assigns g as p/q, the former state of f. Because the state of the instance that is returned by this 
        operator method is identical to the "former" state of the object on which this operator method is called, 
        this method first creates a copy of the instance before making any changes to that, then it introduces
        necessary changes on the state of the instance (adds 1) whose copy was created; and finally it returns the copy that
        is present at the old/former state of the instance. The return is by-value because the copy is a local
        instance. Obviously this operator is authorised to change the state of the object and hence is not declared
        as a constant operator method.
        */
        Fraction operator ++ ( int ) ;

        /*
        This function overloads the binary addition operator '+'. This is not a member function but rather a global
        function which is a 'friend' of this class. This implies it has access to all the data members (private or
        non-private) of any instance of this class. When the operator '+' is used in an infix notation (say f1 + f2)
        this friend function is invoked -- the first operand is passed as the first paramter and the second operand as
        the second parameter. Both of them are instances of a UDT and therefore are passed-by-reference. In fact they
        are passed as a constant reference (notice the 'const' keyword) so that the actual operands in the caller
        function stay perfectly intact. The rational sum of the two parameters is computed and stored in a local
        'Fraction' instance. This result must be passed by value because it is a local variable.
        */
        friend Fraction operator + ( const Fraction & , const Fraction & ) ;

        /*
        This function overloads the binary subtraction operator '-'. This is not a member function but rather a global
        function which is a 'friend' of this class. This implies it has access to all the data members (private or
        non-private) of any instance of this class. When the operator '-' is used in an infix notation (say f1 - f2)
        this friend function is invoked -- the first operand is passed as the first paramter and the second operand as
        the second parameter. Both of them are instances of a UDT and therefore are passed-by-reference. In fact they
        are passed as a constant reference (notice the 'const' keyword) so that the actual operands in the caller
        function stay perfectly intact. The rational difference of the two parameters is computed and stored in a local
        'Fraction' instance. This result must be passed by value because it is a local variable.
        */
        friend Fraction operator - ( const Fraction & , const Fraction & ) ;

        /*
        This function overloads the binary multiplication operator '*'. This is not a member function but rather a global
        function which is a 'friend' of this class. This implies it has access to all the data members (private or
        non-private) of any instance of this class. When the operator '*' is used in an infix notation (say f1 * f2)
        this friend function is invoked -- the first operand is passed as the first paramter and the second operand as
        the second parameter. Both of them are instances of a UDT and therefore are passed-by-reference. In fact they
        are passed as a constant reference (notice the 'const' keyword) so that the actual operands in the caller
        function stay perfectly intact. The rational product of the two parameters is computed and stored in a local
        'Fraction' instance. This result must be passed by value because it is a local variable.
        */
        friend Fraction operator * ( const Fraction & , const Fraction & ) ;

        /*
        This function overloads the binary division operator '/'. This is not a member function but rather a global
        function which is a 'friend' of this class. This implies it has access to all the data members (private or
        non-private) of any instance of this class. When the operator '/' is used in an infix notation (say f1 / f2)
        this friend function is invoked -- the first operand is passed as the first paramter and the second operand as
        the second parameter. Both of them are instances of a UDT and therefore are passed-by-reference. In fact they
        are passed as a constant reference (notice the 'const' keyword) so that the actual operands in the caller
        function stay perfectly intact. The first parameter is divided by the second parameter and the result is 
        stored in a local 'Fraction' instance. This result must be passed by value because it is a local variable. The
        special case when the second operand is ZERO is not dealt and an exception is simply thrown before returning to
        the caller function.
        */
        friend Fraction operator / ( const Fraction & , const Fraction & ) ;

        /*
        This function overloads the binary modulus operator '%'. This is not a member function but rather a global
        function which is a 'friend' of this class. This implies it has access to all the data members (private or
        non-private) of any instance of this class. When the operator '%' is used in an infix notation (say f1 % f2)
        this friend function is invoked -- the first operand is passed as the first paramter and the second operand as
        the second parameter. Both of them are instances of a UDT and therefore are passed-by-reference. In fact they
        are passed as a constant reference (notice the 'const' keyword) so that the actual operands in the caller
        function stay perfectly intact. The remainder of division of the first parameter by the second parameter is 
        computed and stored in a local 'Fraction' instance. This result must be passed by value because it is a local 
        variable. The special case when the second operand is ZERO is not dealt and an exception is simply thrown before 
        returning to the caller function.
        */
        friend Fraction operator % ( const Fraction & , const Fraction & ) ;

        /*
        This method overloads the binary relational operator '=='. The Fraction object on the RHS of the operator 
        is passed-by-reference. This is redundant (unlike in the copy constructor where an infinite loop can be
        formed as a result of call-by-value) but it saves an extra call/overhead to the copy constructor to copy 
        the passed value to the local parameter. To avoid the risk of changing the actual parameter/second operand, 
        'const' keyword is used. This ensures that the state of the second operand stays intact. The Fraction object 
        on the LHS of the operator (first operand) is the object on which this operator method is called. Just like the 
        second operand, equality-check must NOT change the state of the first operand too. Therefore, a 'const' keyword is 
        added before the semicolon to declare this method as a constant method. This ensures that the state of the 
        object on which this method is called stays intact. The return type is boolean (return-by-value) -- true if both 
        the numerator and the denominator of the LHS and RHS fractions are equal and false otherwise.
        */
        bool operator == ( const Fraction & ) const ;

        /*
        This method overloads the binary relational operator '!='. The Fraction object on the RHS of the operator 
        is passed-by-reference. This is redundant (unlike in the copy constructor where an infinite loop can be
        formed as a result of call-by-value) but it saves an extra call/overhead to the copy constructor to copy 
        the passed value to the local parameter. To avoid the risk of changing the actual parameter/second
        operand, 'const' keyword is used. This ensures that the state of the second operand stays intact.
        The Fraction object on the LHS of the operator (first operand) is the object on which this operator
        method is called. Just like the second operand, inequality-check must NOT change the state of the first operand 
        too. Therefore, a 'const' keyword is added before the semicolon to declare this method as a constant
        method. This ensures that the state of the object on which this method is called stays intact. The return type
        is boolean (return-by-value) -- false if both the numerator and the denominator of the LHS and RHS fractions are
        equal and true otherwise.
        */
        bool operator != ( const Fraction & ) const ;

        /*
        This method overloads the binary relational operator '<'. The Fraction object on the RHS of the operator 
        is passed-by-reference. This is redundant (unlike in the copy constructor where an infinite loop can be
        formed as a result of call-by-value) but it saves an extra call/overhead to the copy constructor to copy 
        the passed value to the local parameter. To avoid the risk of changing the actual parameter/second
        operand, 'const' keyword is used. This ensures that the state of the second operand stays intact.
        The Fraction object on the LHS of the operator (first operand) is the object on which this operator
        method is called. Just like the second operand, is-less-than-check must NOT change the state of the first operand 
        too. Therefore, a 'const' keyword is added before the semicolon to declare this method as a constant
        method. This ensures that the state of the object on which this method is called stays intact. The return type
        is boolean (return-by-value) -- true if LHS fraction is less than RHS and false otherwise.
        */
        bool operator < ( const Fraction & ) const ;

        /*
        This method overloads the binary relational operator '<='. The Fraction object on the RHS of the operator 
        is passed-by-reference. This is redundant (unlike in the copy constructor where an infinite loop can be
        formed as a result of call-by-value) but it saves an extra call/overhead to the copy constructor to copy 
        the passed value to the local parameter. To avoid the risk of changing the actual parameter/second
        operand, 'const' keyword is used. This ensures that the state of the second operand stays intact.
        The Fraction object on the LHS of the operator (first operand) is the object on which this operator
        method is called. Just like the second operand, is-less-than-or-equal-to-check must NOT change the state of  
        the first operand too. Therefore, a 'const' keyword is added before the semicolon to declare this method as 
        a constant method. This ensures that the state of the object on which this method is called stays intact. 
        The return type is boolean (return-by-value) -- false if LHS fraction is greater than RHS and true otherwise.
        */
        bool operator <= ( const Fraction & ) const ;

        /*
        This method overloads the binary relational operator '>'. The Fraction object on the RHS of the operator 
        is passed-by-reference. This is redundant (unlike in the copy constructor where an infinite loop can be
        formed as a result of call-by-value) but it saves an extra call/overhead to the copy constructor to copy 
        the passed value to the local parameter. To avoid the risk of changing the actual parameter/second
        operand, 'const' keyword is used. This ensures that the state of the second operand stays intact.
        The Fraction object on the LHS of the operator (first operand) is the object on which this operator
        method is called. Just like the second operand, is-greater-than-check must NOT change the state of the  
        first operand too. Therefore, a 'const' keyword is added before the semicolon to declare this method as a constant
        method. This ensures that the state of the object on which this method is called stays intact. The return type
        is boolean (return-by-value) -- true if LHS fraction is more than RHS and false otherwise.
        */
        bool operator > ( const Fraction & ) const ;

        /*
        This method overloads the binary relational operator '>='. The Fraction object on the RHS of the operator 
        is passed-by-reference. This is redundant (unlike in the copy constructor where an infinite loop can be
        formed as a result of call-by-value) but it saves an extra call/overhead to the copy constructor to copy 
        the passed value to the local parameter. To avoid the risk of changing the actual parameter/second
        operand, 'const' keyword is used. This ensures that the state of the second operand stays intact.
        The Fraction object on the LHS of the operator (first operand) is the object on which this operator
        method is called. Just like the second operand, is-more-than-or-equal-to-check must NOT change the state of 
        the first operand too. Therefore, a 'const' keyword is added before the semicolon to declare this method as a constant
        method. This ensures that the state of the object on which this method is called stays intact. The return type
        is boolean (return-by-value) -- false if LHS fraction is less than RHS and true otherwise.
        */
        bool operator >= ( const Fraction & ) const ;

        /*
        This method overloads the unary logical operator '!'. Since it is a unary operator, it has no parameters.
        The 'const' keyword before the semicolon declares this method as a constant method, i.e, it ensures that
        the state of the object on which this operator method is called remains intact post-operation. The operation 
        creates a new instance of Fraction class that stores the rational inverse of the fraction object on which 
        the operator is performed (provided this fraction is NOT 0/1). Since the new instance created is a local 
        variable, it MUST be passed by-value.
        */
        Fraction operator ! ( ) const ;

        /*
        This function overloads the output operator '<<'. This is not a member function but rather a global function.
        The 'friend' keyword binds this global function to the 'Fraction' class so that it can access all the private
        members of this class. This is necessary because it can then directly access (without any "get" methods) the 
        state of an instance and print it on the console while the data members are still private. Object to write is
        passed-by-reference to prevent any copying overhead. To ensure that the state of the object is not changed by
        this global function, it is passed as "const Fraction &" (const reference). The first parameter is the ostream 
        object that is the stream to which the content is written/printed. The ostream object is passed-by-reference so
        that it can be returned by reference (local parameters/objects/variables cannot be returned by reference). The 
        ostream object should be returned by reference so as to enable chaining of output operators, like 
        "cout << f1 << f2 ;".
        */
        friend ostream & operator << ( ostream & out , const Fraction & f ) ;
        
        /*
        This function overloads the input operator '>>'. This is not a member function but rather a global function.
        The 'friend' keyword binds this global function to the 'Fraction' class so that it can access all the private
        members of this class. This is necessary because it can then directly re-assign (without any "set" methods) the 
        data members of an instance (only non-const) and change its state while the data members are still private. 
        Object to be modified is passed-by-reference to prevent any copying overhead. To ensure that the state of 
        the object can be changed by this global function, it is passed as "Fraction &" (non-const reference). The first
        parameter is the istream object that is the stream from which the values are read. The istream object is 
        passed-by-reference so that it can be returned by reference (local parameters/objects/variables cannot be 
        returned by reference). The istream object should be returned by reference so as to enable chaining of 
        input operators, like "cin >> f1 >> f2 ;".
        */
        friend istream & operator >> ( istream & in ,  Fraction & f ) ;

        /*
        This is a utility member function that returns the value of the 'precision' that is used to construct 'Fraction' objects 
        from 'double'. It is a static member function since the value it returns is a static data member. Though a non-static member
        could have also served the purpose; but for that a Fraction object would have to be especially constructed to call
        this non-static method, which would have returned a value that is not even specific to that object. 
        */
        static int precision ( ) ;
        
        /*
        This is a utility member function that computes and returns the GCD of two natural numbers, passed-by-value as the int
        parameters. The member function is static because it is required by other static member functions (like "Fraction::normalize").
        Besides, it does not perform a task specific to an object or returns a value characteristic to that object's state; therefore
        it is apt to declare it as a static member function. One should be able to get the GCD of two integeral values through this 
        function even without actually constructing an instance of Fraction class first. It just makes sense to keep this method
        in a namespace dedicated to "fractions".
        */
        static int gcd ( unsigned int , unsigned int ) ;
        
        /*
        This is a utility member function that computes and returns the LCM of two natural numbers, passed-by-value as the int
        parameters. The member function is static because it does not perform a task specific to an object or returns a value 
        characteristic to that object's state; therefore it is apt to declare it as a static member function. One should be able to get 
        the LCM of two integeral values through this function even without actually constructing an instance of Fraction class first. 
        It just makes sense to keep this method in a namespace dedicated to "fractions".
        */
        static int lcm ( unsigned int , unsigned int ) ;
} ;