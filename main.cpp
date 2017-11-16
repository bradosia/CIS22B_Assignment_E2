/*
Branden Lee
CIS 22B
Fall 2017
Assignment E
Problem E1

Used Microsoft Visual Studio 2017

Car class
we use an array of pointers to Car and make
a copy of the users Car objects in the heap.
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>      // std::fstream
#include <stdio.h>
using namespace std;

/**************************************************
** Car class
**************************************************/
class Car
{
private:
	string reportingMark;
	int carNumber;
	string kind;
	bool loaded;
	string destination;
public:
	Car () { setup ("", 0, "other", false, "NONE"); } //default constructor
	Car (const Car &CarObj) { setup (CarObj.reportingMark, CarObj.carNumber, CarObj.kind, CarObj.loaded, CarObj.destination); } //copy constructor
	Car (string reportingMarkInit, int carNumberInit, string kindInit, bool loadedInit, string destinationInit) { setup (reportingMarkInit, carNumberInit, kindInit, loadedInit, destinationInit); } //other constructor
	~Car () {} // destructor
	void setup (string reportingMarkInit, int carNumberInit, string kindInit, bool loadedInit, string destinationInit);
	void output ();
	Car & Car::operator=(const Car & carB);
	friend bool Car::operator==(const Car CarObj1, const Car CarObj2);
};

/**************************************************
** FreightCar class
**************************************************/
class FreightCar : Car
{
private:
	string reportingMark;
	int carNumber;
	string kind;
	bool loaded;
	string destination;
public:
	FreightCar () { Car::setup ("", 0, "other", false, "NONE"); } //default constructor
	FreightCar (const FreightCar &CarObj) { Car::setup (CarObj.reportingMark, CarObj.carNumber, CarObj.kind, CarObj.loaded, CarObj.destination); } //copy constructor
	FreightCar (string reportingMarkInit, int carNumberInit, string kindInit, bool loadedInit, string destinationInit) { setup (reportingMarkInit, carNumberInit, kindInit, loadedInit, destinationInit); } //other constructor
	~FreightCar () {} // destructor
	FreightCar & FreightCar::operator=(const FreightCar & carB);
};

/**************************************************
** StringOfCars class
**************************************************/

class StringOfCars
{
private:
	Car **carArrayPtr;
	static const int ARRAY_SIZE = 10;
	int carCount;
public:
	StringOfCars () //default constructor
	{
		carArrayPtr = new Car*[ARRAY_SIZE];
		// set all ptrs to zero
		for (int i = 0; i < ARRAY_SIZE; i++)
			carArrayPtr[i] = 0;
		carCount = 0;
	}
	StringOfCars (const StringOfCars* &StringOfCarsObj)  //copy constructor
	{
		carArrayPtr = new Car*[ARRAY_SIZE];
		// set all ptrs to zero
		for (int i = 0; i < ARRAY_SIZE; i++)
			carArrayPtr[i] = 0;
		carCount = 0;
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			push ((*StringOfCarsObj->carArrayPtr[i]));
		}
	}
	~StringOfCars ()
	{ // destructor
		for (int i = 0; i < ARRAY_SIZE; i++)
			delete carArrayPtr[i];
		delete[] carArrayPtr;
	} // destructor

	void output ();
	void push (const Car &CarObj);
	void pop (Car &CarObj);
};

/**************************************************
** global functions, and variables
**************************************************/

void input (StringOfCars & StringOfCarsObj);

int main ()
{
	// Test the Car operator=   function. 
	cout << "TEST 1" << endl;
	Car car1 ("SP", 34567, "business", true, "Salt Lake City");
	Car car2;
	car2 = car1;
	car2.output ();
	// Test the StringOfCar push function.
	cout << "TEST 2" << endl;
	StringOfCars string1;
	input (string1);
	cout << "STRING 1" << endl;
	string1.output ();
	// Test the StringOfCars pop function. 
	cout << "TEST 3" << endl;
	Car car3;
	string1.pop (car3);
	cout << "CAR 3" << endl;
	car3.output ();
	cout << "STRING 1" << endl;
	string1.output ();
	system ("pause");
	return 0;
}

/**************************************************
** Car class method definitions
**************************************************/

/******************* Car::setup *******************
** Puts the car data into the object
**************************************************/
void Car::setup (string reportingMarkInit, int carNumberInit, string kindInit, bool loadedInit, string destinationInit)
{
	reportingMark = reportingMarkInit;
	carNumber = carNumberInit;
	kind = kindInit;
	loaded = loadedInit;
	destination = destinationInit;
}

/********************* Car::output ****************
** Prints the car data in a neat format
**************************************************/
void Car::output ()
{
	// cout << bool will output an integer
	// we create a temporary string to output the bool
	// std::boolalpha can also be used
	string loadedString = (!loaded) ? "false" : "true";
	cout << setw (16) << left << "reportingMark:" << reportingMark << endl
		<< setw (16) << left << "carNumber: " << carNumber << endl
		<< setw (16) << left << "kind: " << kind << endl
		<< setw (16) << left << "loaded: " << loadedString << endl
		<< setw (16) << left << "destination: " << destination << endl << endl;
}

/********************* operator= ******************
** operator over load for Car class assignment =
**************************************************/
Car & Car::operator=(const Car & carB)
{
	setup (carB.reportingMark, carB.carNumber, carB.kind, carB.loaded, carB.destination);

	return *this;
}

/**************************************************
** FreightCar class method definitions
**************************************************/

/***************FreightCar::setup *****************
** Puts the car data into the object
**************************************************/

/********************* operator= ******************
** operator over load for Car class assignment =
**************************************************/
FreightCar & FreightCar::operator=(const FreightCar & carB)
{
	setup (carB.reportingMark, carB.carNumber, carB.kind, carB.loaded, carB.destination);

	return *this;
}

/**************************************************
** StringOfCars class method definitions
**************************************************/

/************* StringOfCars::output ***************
** Outputs each car data. Prints "NO cars" if
** StringOfCars is empty.
**************************************************/
void StringOfCars::output ()
{
	if (carCount > 0)
	{
		for (int i = 0; i < carCount; i++)
		{
			cout << "Car #" << i + 1 << endl;
			(*carArrayPtr[i]).output ();
		}
	}
	else
	{
		cout << "NO cars" << endl;
	}
}

/*************** StringOfCars::push ***************
** Puts a Car into the StringOfCars array
**************************************************/
void StringOfCars::push (const Car &CarObj)
{
	if (carCount < ARRAY_SIZE)
	{
		carArrayPtr[carCount] = new Car (CarObj);
		carCount++;
	}
	else
	{
		cout << "string of cars is full";
		exit (EXIT_FAILURE);
	}
}

/*************** StringOfCars::pop ****************
** Removes the last Car added from the StringOfCars
** assigns removed Car to the argument
**************************************************/
void StringOfCars::pop (Car &CarObj)
{
	if (carCount > 0)
	{
		CarObj = Car ((*carArrayPtr[carCount - 1]));
		delete carArrayPtr[carCount - 1];
		carArrayPtr[carCount - 1] = 0;
		carCount--;
	}
	else
	{
		cout << "string of cars is empty";
		exit (EXIT_FAILURE);
	}
}

/**************************************************
** global function definitions
**************************************************/

/******************** operator== ******************
** operator over load for Car class comparison ==
**************************************************/
bool operator==(const Car CarObj1, const Car CarObj2)
{
	if (CarObj1.reportingMark == CarObj2.reportingMark && CarObj1.carNumber == CarObj2.carNumber&& CarObj1.kind == CarObj2.kind&& CarObj1.loaded == CarObj2.loaded&& CarObj1.destination == CarObj2.destination) { return true; }
	return false;
}

/********************* input **********************
** Reads the car data from the text file "data.txt"
** Prints data from the file
**************************************************/
void input (StringOfCars & StringOfCarsObj)
{
	string carType, reportingMarkInit, kindInit, destinationInit, loadedInit;
	int carNumberInit;
	std::fstream inputFile;
	inputFile.open ("data.txt");
	if (!inputFile)
	{
		cerr << "File could not be opened." << endl;
		exit (1);
	}
	while (inputFile.peek () != EOF)
	{
		while (inputFile.peek () == ' ')
			inputFile.get ();
		inputFile >> carType >> reportingMarkInit >> carNumberInit >> kindInit >> loadedInit;
		while (inputFile.peek () == ' ')
			inputFile.get ();
		getline (inputFile, destinationInit);
		// If the carType is not "Car", send an error message and do nothing.
		if (carType == "Car")
		{
			// If the carType is "Car", declare a Car object named temp using the constructor that takes 5 parameters.
			Car temp (reportingMarkInit, carNumberInit, kindInit, loadedInit == "true" ? true : false, destinationInit);
			StringOfCarsObj.push (temp);
		}
		// If the carType is not "Car", send an error message and do nothing.
		else cerr << "Not a car" << endl;
	}
	inputFile.close ();
}

/* Execution results
TEST 1
reportingMark:  SP
carNumber:      34567
kind:           business
loaded:         true
destination:    Salt Lake City

TEST 2
STRING 1
Car #1
reportingMark:  CN
carNumber:      819481
kind:           maintenance
loaded:         false
destination:    NONE

Car #2
reportingMark:  SLSF
carNumber:      46871
kind:           business
loaded:         true
destination:    Memphis

Car #3
reportingMark:  AOK
carNumber:      156
kind:           tender
loaded:         true
destination:    McAlester

TEST 3
CAR 3
reportingMark:  AOK
carNumber:      156
kind:           tender
loaded:         true
destination:    McAlester

STRING 1
Car #1
reportingMark:  CN
carNumber:      819481
kind:           maintenance
loaded:         false
destination:    NONE

Car #2
reportingMark:  SLSF
carNumber:      46871
kind:           business
loaded:         true
destination:    Memphis
*/