
### SOFTWARE ENGINEERING CS20006 - ASSIGNMENT O3
### Nakul Aggarwal  |   19CS10044

o   Header Files (.h files)
(1) Booking.hpp :       Definition of the class 'Booking'
(2) BookingClass.hpp :  Definition of the polymorphic heirarchy of classes rooted at 'BookingClass'
(3) Date.hpp :          Definition of the class 'Date'
(4) Passenger.hpp :     Definition of the class 'Passenger'
(5) Railways.hpp :      Definition of the class 'Railways'
(6) Station.hpp :       Definition of the class 'Station'

o   Source Files (.cpp files)
(1) Application.cpp  :   Implementation of the application test-plans (both sample test in the assignment and own test)
(2) Booking.cpp      :   Implementation of the class 'Booking' + Implementation of the unit test-plan for this class   
(3) BookingClass.cpp :   Implementation of the polymorphic heirarchy of classes rooted at 'BookingClass' +
                         Implementation of the unit test-plan for this polymorphic class heirarchy
(4) Date.cpp         :   Implementation of the class 'Date' + Implementation of the unit test-plan for this class
(5) Passenger.cpp    :   Implementation of the class 'Passenger' + Implementation of the unit test-plan for this class
(6) Railways.cpp     :   Implementation of the class 'Railways' + Implementation of the unit test-plan for this class
(7) Station.cpp      :   Implementation of the class 'Station' + Implementation of the unit test-plan for this class

o   Operating System
Windows 10

o   Compiler
g++ (MinGW.org GCC-6.3.0-1) 6.3.0

o   Compilation and Linking Commands
(First navigate to this directory on the command prompt)
(1) g++ -c Application.cpp Booking.cpp BookingClass.cpp Date.cpp Passenger.cpp Railways.cpp Station.cpp
(2) g++ -o app.exe Application.o Booking.o BookingClass.o Date.o Passenger.o Station.o Railways.o
(3) app.exe
