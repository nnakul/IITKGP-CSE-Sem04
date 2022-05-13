
#   NAKUL AGGARWAL  |   19CS10044
#   PYTHON DATA SCIENCE ASSIGNMENT
#   ASSIGNMENT O3   |   QUESTION O1
#   03.02.2021 TO 17.02.2021

class Vector:
    
    def __init__ ( self , *args ) : 
        self._coords = list()
        self._dim = 0
        if not len(args) :
            self._coords = [0] * 5
            self._dim = 5
        elif isinstance ( args[0] , int ) :
            if args[0] <= 0 :
                print( "\t[ INITIALIZATION ERROR 001 : VECTOR OF NON-POSITIVE DIMENSION IS UNDEFINED ]" )
            else :
                self._coords = [0] * args[0]
                self._dim = args[0]
        else :
            try :
                check = False
                self._coords = list()
                for e in args[0] :
                    check = True
                    if not isinstance(e, int) and not isinstance(e, float) :
                        print( "\t[ INITIALIZATION ERROR 002 : VECTOR COORDINATE MUST BE A FLOAT OR AN INTEGER ]" )
                        self._coords = list()
                        self._dim = 0
                        break
                    self._coords.append(e)
                    self._dim += 1
                if not check :
                    print( "\t[ INITIALIZATION ERROR 001 : VECTOR OF NON-POSITIVE DIMENSION IS UNDEFINED ]" )
            except :
                print( "\t[ INITIALIZATION ERROR 003 : INVALID ATTEMPT TO INITIALIZE A Vector OBJECT ]" )

    
    def __len__ ( self ) :
        return self._dim

    
    def __getitem__ ( self , j ) :
        if not isinstance(j, int) :
            print( "\t[ 'GET' ERROR 001 : INVALID INDEX TYPE ]" )
            return None
        if j >= self._dim or j < 0 :
            print( "\t[ 'GET' ERROR 002 : CANNOT ACCESS A VECTOR COORDINATE OUTSIDE OF ITS DIMENSION ]" )
            return None
        return self._coords[j]

    
    def __setitem__ (self , j , val) :
        if not isinstance(val, int) and not isinstance(val, float) :
            print( "\t[ 'SET' ERROR 001 : VECTOR COORDINATE CAN ONLY BE SET TO A FLOAT OR AN INTEGER ]" )
            return None
        if not isinstance(j, int) :
            print( "\t[ 'SET' ERROR 002 : INVALID INDEX TYPE ]" )
            return None
        if j >= self._dim or j < 0 :
            print( "\t[ 'SET' ERROR 003 : CANNOT ACCESS A VECTOR COORDINATE OUTSIDE OF ITS DIMENSION ]" )
            return None
        self._coords[j] = val
        return None
    
    
    def __add__ (self , other) :
        if not isinstance(other, Vector) :
            print( "\t[ ADDITION ERROR 001 : INVALID USE OF __add__ METHOD TO ADD A Vector INSTANCE TO A NON-Vector INSTANCE ]" )
            return None
        if self._dim != len(other) :
            print( "\t[ ADDITION ERROR 002 : CANNOT ADD TWO VECTORS OF DIFFERENT DIMENSIONS ]" )
            return None
        sum = Vector(self._dim)
        for i in range(self._dim) :
            sum[i] = self[i] + other[i]
        return sum
            
    
    def __eq__ ( self , other ) :
        if not isinstance(other, Vector) :
            return False
        if self._dim != len(other) :
            return False
        for i in range(self._dim) :
            if self[i] != other[i] :
                return False
        return True
    
    
    def __ne__ ( self , other ) :
        if not isinstance(other, Vector) :
            return True
        if self._dim != len(other) :
            return True
        for i in range(self._dim) :
            if self[i] != other[i] :
                return True
        return False
    
    
    def __str__ ( self ) :
        if not self._dim :
            return 'None'
        s = '<'
        for i in range(self._dim-1) :
            s += str(self[i]) + ', '
        s += str(self[self._dim-1]) + '>'
        return s

    
    def __sub__ ( self , other ) :
        if not isinstance(other, Vector) :
            print( "\t[ SUBTRACTION ERROR 001 : INVALID USE OF __sub__ METHOD TO SUBTRACT A NON-Vector INSTANCE FROM A Vector INSTANCE ]" )
            return None
        if self._dim != len(other) :
            print( "\t[ SUBTRACTION ERROR 002 : CANNOT SUBTRACT TWO VECTORS OF DIFFERENT DIMENSIONS ]" )
            return None
        diff = Vector(self._dim)
        for i in range(self._dim) :
            diff[i] = self[i] - other[i]
        return diff
    
    
    def __neg__ ( self ) :
        v = Vector(self._dim)
        if not len(v) : return v
        for i in range(self._dim) :
            v[i] = self[i] * -1
        return v
    
    
    def __rmul__ ( self , value ) :
        if isinstance ( value , int ) or isinstance ( value , float ) :
            v = Vector(self._dim)
            for i in range(self._dim) :
                v[i] = self[i] * value
            return v
        print( "\t[ MULTIPLICATION ERROR 001 : __rmul__ METHOD CAN PERFORM MULTIPLICATION BETWEEN ONLY A Vector OBJECT AND AN int / float OBJECT ]" )
        return None
    
    
    def __mul__  ( self , other ) :
        if isinstance ( other , int ) or isinstance ( other , float ) :
            v = Vector(self._dim)
            for i in range(self._dim) :
                v[i] = self[i] * other
            return v
        elif isinstance ( other , Vector ) :
            if self._dim != len(other) :
                print( "\t[ MULTIPLICATION ERROR 002 : DOT PRODUCT OF VECTORS OF DIFFERENT DIMENSIONS CANNOT BE COMPUTED ]" )
                return None
            if not self._dim :
                return None
            dotp = 0
            for i in range(self._dim) :
                dotp += self[i] * other[i]
            return dotp
        else :
            print( "\t[ MULTIPLICATION ERROR 003 : __mul__ METHOD CAN PERFORM MULTIPLICATION BETWEEN ONLY A Vector OBJECT AND A Vector / int / float OBJECT ]" )
            return None


def askVectorInput ( prompt ) :
    s = input( prompt + ' (as a tuple/list, eg -- [1, 2, 3, 4]; or as an integer, eg -- 5) : ' )
    if s[0] == '[' or s[0] == '(' :
        if s[-2:] == ',)' : init = [ eval(s[1:-2]) ]
        elif len(s) == 2 :    init = list()
        else :  init = [ eval(x) for x in s[1:-1].split(',') ]
    else :    init = eval(s)
    return Vector(init)


def main():
    choice = 1
    while choice != 15 :
        print('\n\n\n')
        print ( "\t  1) INITIALIZATION OF A VECTOR BY INTEGER (__init__)" )
        print ( "\t  2) INITIALIZATION OF A VECTOR BY LIST/TUPLE (__init__)" )
        print ( "\t  3) ADDITION OF TWO VECTORS (__add__)" )
        print ( "\t  4) SUBTRACTION OF TWO VECTORS (__sub__)" )
        print ( "\t  5) DOT PRODUCT OF TWO VECTORS (__mul__)" )
        print ( "\t  6) SCALING A VECTOR BY AN INTEGER / FLOAT (__mul__)" )
        print ( "\t  7) SCALING A VECTOR BY AN INTEGER / FLOAT (__rmul__)" )
        print ( "\t  8) NEGATION OF A VECTOR (__neg__)" )
        print ( "\t  9) CHECKING EQUALITY OF TWO VECTORS (__eq__)" )
        print ( "\t 10) CHECKING INEQUALITY OF TWO VECTORS (__ne__)" )
        print ( "\t 11) CONVERSION OF A VECTOR INTO A STRING (__str__)" )
        print ( "\t 12) GET DIMENSION OF A VECTOR (__len__)" )
        print ( "\t 13) GET A COORDINATE OF A VECTOR  (__getitem__)" )
        print ( "\t 14) SET A COORDINATE OF A VECTOR  (__setitem__)" )
        print ( "\t 15) TERMINATE PROGRAM" )

        choice = eval(input('\n\t\t o ENTER CHOICE : '))
        if choice == 15 :   break
        print('\n\n')
        
        if choice == 1 :
            d = eval(input('  ENTER A DIMENSION : '))
            v = Vector(d)
            print( ' ' , v , 'Vector OBJECT WAS INSTANTIATED BY __init__')
            continue

        if choice == 2 :
            s = input( '  ENTER VECTOR (as a tuple/list, eg -- [1, 2, 3, 4]) : ' )
            if s[-2:] == ',)' : init = [ eval(s[1:-2]) ]
            elif len(s) == 2 :    init = list()
            else :  init = [ eval(x) for x in s[1:-1].split(',') ]
            v = Vector(init)
            print( ' ' , v , 'Vector OBJECT WAS INSTANTIATED BY __init__')
            continue
            
        if choice == 3 :
            u = askVectorInput('  ENTER FIRST VECTOR OPERAND')
            v = askVectorInput('  ENTER SECOND VECTOR OPERAND')
            z = u + v
            print('  VECTOR SUM', z , 'WAS COMPUTED BY __add__')
            continue
        
        if choice == 4 :
            u = askVectorInput('  ENTER FIRST VECTOR OPERAND')
            v = askVectorInput('  ENTER SECOND VECTOR OPERAND')
            z = u - v
            print('  VECTOR DIFFERENCE', u - v , 'WAS COMPUTED BY __sub__')
            continue
        
        if choice == 5 :
            u = askVectorInput('  ENTER FIRST VECTOR OPERAND')
            v = askVectorInput('  ENTER SECOND VECTOR OPERAND')
            z = u * v
            print('  DOT PRODUCT', z , 'WAS COMPUTED BY __mul__')
            continue
        
        if choice == 6 :
            u = askVectorInput('  ENTER A VECTOR')
            i = eval(input('  ENTER SCALING FACTOR : '))
            z = u * i
            print('  SCALED VECTOR ', z , 'WAS COMPUTED BY __mul__')
            continue
        
        if choice == 7 :
            u = askVectorInput('  ENTER A VECTOR')
            i = eval(input('  ENTER SCALING FACTOR : '))
            z = i * u
            print('  SCALED VECTOR ', z , 'WAS COMPUTED BY __rmul__')
            continue

        if choice == 8 :
            u = askVectorInput('  ENTER A VECTOR')
            z = -u
            print('  NEGATED VECTOR ', z , 'WAS COMPUTED BY __neg__')
            continue

        if choice == 9 :
            u = askVectorInput('  ENTER FIRST VECTOR OPERAND')
            v = askVectorInput('  ENTER SECOND VECTOR OPERAND')
            res = ( u == v )
            print('  EQUALITY-CHECK RESULTED IN', res , 'WAS COMPUTED BY __eq__')
            continue

        if choice == 10 :
            u = askVectorInput('  ENTER FIRST VECTOR OPERAND')
            v = askVectorInput('  ENTER SECOND VECTOR OPERAND')
            res = ( u != v )
            print('  INEQUALITY-CHECK RESULTED IN', res , 'WAS COMPUTED BY __ne__')
            continue
        
        if choice == 11 :
            u = askVectorInput('  ENTER A VECTOR')
            string = str(u)
            print('  STRING', string , 'WAS RETURNED BY __str__')
            continue
        
        if choice == 12 :
            u = askVectorInput('  ENTER A VECTOR')
            print('  DIMENSION', len(u) , 'WAS RETURNED BY __len__')
            continue

        if choice == 13 :
            u = askVectorInput('  ENTER A VECTOR')
            i = eval(input('  ENTER INDEX OF THE COORDINATE : '))
            val = u[i]
            print('  COORDINATE VALUE', val , 'WAS RETURNED BY __getitem__')
            continue

        if choice == 14 :
            u = askVectorInput('  ENTER A VECTOR')
            i = eval(input('  ENTER INDEX OF THE COORDINATE : '))
            val = eval(input('  ENTER NEW VALUE : '))
            u[i] = val
            print('  Vector OBJECT\'S STATE WAS CHANGED TO', u , 'BY __setitem__')
    
    print('\n\n\n')
        

if __name__ == '__main__':
    main()
    
