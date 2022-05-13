
### SOFTWARE ENGINEERING CS20006 - ASSIGNMENT O5
### Nakul Aggarwal  |   19CS10044

**o   Header Files (.h files)**
(01) Booking.h  --  declaration of *Booking* base class and derived *BookingTypes* template class + implementation of inline methods
(02) BookingCategory.h  --  declaration of *BookingCategory* base class and derived *BookingCategoryTypes* template class + implementation of inline methods
(03) BookingClass.h  --  declaration of *BookingClass* base class and derived *BookingClassTypes* template class + implementation of inline methods
(04) Concessions.h  --  declaration of *Concessions* base class and its *hierarchy*
(05) Date.h  --  declaration of *Date* class + implementation of inline methods
(06) Divyaang.h  --  declaration of *Divyaang* base class and derived *DivyaangTypes* template class + implementation of inline methods
(07) Exceptions.h  --  declaration and implementation of *Exceptions hierarchy*
(08) Gender.h  --  declaration of *Gender* base class and derived *GenderTypes* template class + implementation of inline methods
(09) Passenger.h  --  declaration of *Passenger* class + implementation of inline methods
(10) Railways.h  --  declaration of *Railways* class
(11) Station.h  --  declaration of *Station* class + implementation of inline methods

**o   Source Files (.cpp files)**
(01) Application.cpp  --  implementation of application test plan
(02) Booking.cpp  --  initialization of all static data members + implementation of methods / friend functions in *Booking hierarchy* + implementation of unit test plan
(03) BookingCategory.cpp  --  initialization of all static data members + implementation of methods / friend functions in *BookingCategory hierarchy* + implementation of unit test plan
(04) BookingClass.cpp  --  initialization of all static data members + implementation of methods / friend functions in *BookingClass hierarchy* + implementation of unit test plan
(05) Concessions.cpp  --  initialization of all static data members + implementation of methods / friend functions in *Concessions hierarchy* + implementation of unit test plan
(06) Date.cpp  --  initialization of all static data members + implementation of methods / friend functions in *Date* class + implementation of unit test plan
(07) Divyaang.cpp  --  initialization of all static data members + implementation of methods / friend functions in *Divyaang hierarchy* + implementation of unit test plan
(08) Gender.cpp  --  initialization of all static data members + implementation of methods / friend functions in *Gender hierarchy* + implementation of unit test plan
(09) Passenger.cpp  --  initialization of all static data members + implementation of methods / friend functions in *Passenger* class + implementation of unit test plan
(10) Railways.cpp  --  initialization of all static data members + implementation of methods / friend functions in *Railways* class + implementation of unit test plan
(11) Station.cpp  --  initialization of all static data members + implementation of methods / friend functions in *Station* class + implementation of unit test plan

**o   Operating System**
*Windows 10*

**o   Compiler**
*g++ (MinGW.org GCC-6.3.0-1) 6.3.0*

**o   Compilation and Linking Commands (Normal Build)**
*(First navigate to this directory on the command prompt)*
(1) g++ -c Application.cpp Booking.cpp BookingCategory.cpp BookingClass.cpp Concessions.cpp Date.cpp Divyaang.cpp Gender.cpp Passenger.cpp Railways.cpp Station.cpp
(2) g++ -o App.exe Application.o Booking.o BookingCategory.o BookingClass.o Concessions.o Date.o Divyaang.o Gender.o Passenger.o Railways.o Station.o
(3) App.exe

**o   Compilation and Linking Commands (Debug Build)**
*(First navigate to this directory on the command prompt)*
(1) g++ -c -D _DEBUG Application.cpp Booking.cpp BookingCategory.cpp BookingClass.cpp Concessions.cpp Date.cpp Divyaang.cpp Gender.cpp Passenger.cpp Railways.cpp Station.cpp
(2) g++ -o App.exe Application.o Booking.o BookingCategory.o BookingClass.o Concessions.o Date.o Divyaang.o Gender.o Passenger.o Railways.o Station.o
(3) App.exe
