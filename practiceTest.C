//-------------------------------------------------------------------
//	practiceTest.C
//
// Warmup exam for friday
// 	Keep in Mind:
//	- Cannot assume a max # of employies
//	- Must Use Classes
//	- Strings are recomended
//-------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <fstream>
#include <cmath>

using namespace std;

// Class Definition

class Employee
{
	public:
		Employee();

		// Mutators
		void inputSSN(string inssn);
		void inputPayRate(double inPayRate);
		void inputTime(int inTime);
		void calculateSalary();
		
		// Accessor Functions
		string returnSSN();
		double returnPayRate();
		int returnTime();
		double returnSalary();
		
		// Viewing Functions
		void displaySSN();
		void displayPayRate();
		void displayTime();
		void displaySalary();

	private:
		string ssn;
		double payRate;
		int minWorked;
		double salary;
};

// Function Prototypes

void writeData(ofstream& outStream, Employee* empPointer, int numEmp);

void loadData(ifstream& inStream, Employee* empPointer, int numEmp);
void skipWhite(ifstream& inStream);
double parseDoubleField(ifstream& inStream);
int parseIntField(ifstream& inStream);
int stringlen(string inString);
int power(int x, int y);

//-------------------------------------------------------------------
//		Start of Program
//-------------------------------------------------------------------

int main()
{

	// Variable initalizations
	ifstream inStream;
	ofstream outStream;

	// NEEDED for new call
	inStream.open("employees.txt");
	int numEmp = parseIntField(inStream);
	inStream.close();
	Employee *empPointer;
	empPointer = new Employee[numEmp];

	
	// Load the data into memory
	loadData(inStream, empPointer, numEmp);

	// Write memory out to a file
	writeData(outStream, empPointer, numEmp);	
}

//-------------------------------------------------------------------
//	writeData(ofstream&, Employee*, int)
//
// Preconditions	:Takes an ofstream, a pointer to the Employee
// 			 class array, and a int for number of
// 			 employees
//
// Postconditions	:Writes out to a file "testOutput.txt" the 
// 			 contents of the Employee class array
//-------------------------------------------------------------------

void writeData(ofstream& outStream, Employee* empPointer, int numEmp)
{
	outStream.open("testOutput.txt");
	outStream.setf(ios::fixed);
	outStream.setf(ios::showpoint);
	outStream.setf(ios::left);
	outStream.precision(2);

	outStream << numEmp << endl;
	outStream.width(18);
	outStream << "SSN";
	outStream.width(18);
	outStream << "HOURLY_PAY_RATE";
	outStream.width(18);
	outStream << "MINUTES_WORKED";
	outStream.width(18);
	outStream << "SALARY" << endl;

	for (int i = 0; i < numEmp; i++)
	{
		outStream.width(18);
		outStream << empPointer->returnSSN();
		outStream.width(18);
		outStream << empPointer->returnPayRate();
		outStream.width(18);
		outStream << empPointer->returnTime();
		outStream.width(18);
		outStream << empPointer->returnSalary();
		outStream << endl;
		empPointer++;
	}
		
	outStream.close();
}

//-------------------------------------------------------------------
//	loadData(ifstream&, Employee*, int)
//
// Preconditions	:Takes an ifstream, a pointer to the Employee
// 			 array, and an int for the number of entries
//
// Postconditions	:Loads the contents of "Employees.txt" into
// 			 memory
//-------------------------------------------------------------------

void loadData(ifstream& inStream, Employee* empPointer, int numEmp)
{
	Employee *tempEmpPointer = empPointer;
	int skip = 0;
	char tempssn[13];
	
	inStream.open("employees.txt");
	while ( skip < 2)
	{
		char temp;
		inStream.get(temp);
		if (temp == '\n')
			skip++;
	}

	for ( int i = 0; i < numEmp; i++)
	{
		inStream.get(tempssn, 12);
		tempEmpPointer->inputSSN(tempssn);
		skipWhite(inStream);
		
		tempEmpPointer->
			inputPayRate(parseDoubleField(inStream));
		skipWhite(inStream);
		
		tempEmpPointer->inputTime(parseIntField(inStream));
		
		tempEmpPointer->calculateSalary();
		skipWhite(inStream);

		tempEmpPointer++;	
	}
	inStream.close();
}	

//-------------------------------------------------------------------
//	parseDoubleField(ifstream&)
//
// Preconditions	:Needs an inStream object already opened and
// 			 the current stream pointer at the BEGINNING
// 			 of the field to be parsed to an double
//
// Postconditions	:Returns a double based on the data read in 
// 			 from the file
//-------------------------------------------------------------------

double parseDoubleField(ifstream& inStream)
{
	string intList;
	string decList;
	string temp;
	int length;
	double result = 0.00;

	while ( inStream.peek() != '.' )
	{
		temp = inStream.get();
		intList = intList + temp;
	}

	inStream.get();

	while ( ! isspace( inStream.peek()) )
	{
		temp = inStream.get();
		decList = decList + temp;
	}

	length = stringlen(intList);

	for (int i = 0; i < length; i++)
	{
		double pow = power(10,length-(i+1));
		double intVers = intList[i]-48;
		result += pow*intVers;
	}

	length = stringlen(decList);

	for (int i = 0; i < length; i++)
	{
		double intVers = decList[i]-48;
		double power = pow(10.0, -(i+1));
		result += (decList[i]-48) * power;
	}

	return result;
}
	
//-------------------------------------------------------------------
//	skipWhite(ifstream&)
// 
// Preconditions	:Needs an ifstream that is open
//
// Postconditions	:Skips over the next block of white space in
// 			 the file
//-------------------------------------------------------------------

void skipWhite(ifstream& inStream)
{
	while( isspace(inStream.peek()) )
	{
		inStream.get();
	}
}

//-------------------------------------------------------------------
//	parseIntField(ifstream&)
// 
// Preconditions	:Takes an ifstream object that is open and 
// 			 the stream pointer at the BEGINNING of the 
// 			 field to be parsed to an int
//
// Postconditions	:Returns an int based on the data found in
// 			 the field the pointer began at
//-------------------------------------------------------------------
			
int parseIntField(ifstream& inStream)
{
	string intList;
	string temp;
	int length;
	int result = 0;
	
	while ( ! isspace(inStream.peek()) )
	{
		temp = inStream.get();
		intList = intList + temp;
	}

	length = stringlen(intList);
	
	for (int i = 0; i < length; i++)
	{
		int pow = power(10,length-(i+1));
		int intVers = intList[i]-48;
		result += pow*intVers;
	}
	
	return result;
}

//-------------------------------------------------------------------
//	power(int, int)
//
// Preconditions	:Takes 2 integers
//
// Postconditions	:Returns an int of value x raised to the y
// 			 NOTE: DOES NOT HANDLE -y VALUES
//-------------------------------------------------------------------

int power(int x, int y)
{
	int answer = 1;
	
	if (y != 0)
		answer = x;
	
	for (int i = 1; i < y; i++)
	{
		answer *= x;
	}
	
	return answer;
}
		
//-------------------------------------------------------------------
//	stringlen(string)
//
// Preconditions	:Takes a string data type
//
// Postconditions	:Returns an int that is the length of the 
// 			 passed string NOT-INCLUDING the \0
//-------------------------------------------------------------------

int stringlen(string inString)
{
	int i = 0;
	char check = inString[0];
	
	while ( check != '\0' )
	{
		i++;
		check = inString[i];
	}

	return i;
}

// Default constructor
Employee::Employee():ssn("No Input"), payRate(0.0), minWorked(0)
{/*Intentionally Empty*/}

// Employee Mutator Functions
void Employee::inputSSN(string inssn) { ssn = inssn; }
void Employee::inputPayRate(double inPayRate) { payRate = inPayRate; }
void Employee::inputTime(int inTime) { minWorked = inTime; }

void Employee::calculateSalary() 
{ 
	double hours = static_cast<double>(minWorked)/60.0;
	salary = payRate * hours; 
}

// Employee Accessor Functions
string Employee::returnSSN() { return(ssn); }
double Employee::returnPayRate() { return(payRate); }
int Employee::returnTime() { return(minWorked); }
double Employee::returnSalary() { return(salary); }

// Employee View (Accessor) Functions
void Employee::displaySSN() { cout << ssn; }
void Employee::displayPayRate() { cout << payRate; }
void Employee::displayTime() { cout << minWorked; }
void Employee::displaySalary() { cout << salary; }
