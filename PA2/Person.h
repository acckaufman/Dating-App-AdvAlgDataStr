//Amanda Kaufman
//Programming Assignment 2
//CISS 350
//This file contains the definition and implementation of the Person class.

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

//Enumerated type to determine the relationship between two instances of Person.
enum RelationType { LESS, EQUAL, GREATER };
const int MATCH_REQ_INTERESTS = 3;

class Person
{
private:
	char gender;
	string name;
	string phoneNum;
	int numInterests;
	string listOfInterests;
	string match;
public:
	//Default constructor
	Person()
	{
		//Set a default gender
		gender = 'M';

		//Initialize the name field with a blank and a comma.
		name = "";

		//Initialize the phone number to a blank.
		phoneNum = "";

		//Initialize the number of interests to 0.
		numInterests = 0;

		//Initialize the interests string to blank with a period at the end.
		listOfInterests = ("");

		//Initialize the match field to "None" and a newline at the end.
		match = "";
	}

	//Destructor
	~Person()
	{

	}

	//#######################################################################################################
	//Accessor Functions																					#
	//#######################################################################################################

	//Returns self's gender character
	char getGender()
	{
		return gender;
	}

	//Returns self's name attribute.
	string getName() const
	{
		return name;
	}

	//Returns self's phone number.
	string getPhoneNum() const
	{
		return phoneNum;
	}

	//Returns self's number of interests.
	int getNumInterests() const
	{
		return numInterests;
	}

	//Return's self's list of interests.
	string getListOfInterests() const
	{
		return listOfInterests;
	}

	//Return's self's match name.
	string getMatchName()
	{
		return match;
	}

	//Determines relationship of self to the object passed as a parameter.
	//Key for determining relationship: name field.
	//This function assumes that the object passed as a parameter has been initialized.
	RelationType comparedTo(Person otherPerson)
	{
		if (name < otherPerson.name)
			return LESS;
		else if (name > otherPerson.name)
			return GREATER;
		else
			return EQUAL;
	}

	//Returns true if the person passed to the function is a match with self, based on number of common interests.
	//Returns false if minimum requirement for matching interests is not met.
	//This function assumes that the Person object passed has already been initialized.
	bool isMatch(Person otherPerson)
	{
		int interestCount = 0;		//Accumulator for the number of matching interests
		string selfInterest;		//Temporary holder for self's interest for comparison
		string otherInterest;		//Temporary holder for the other person's interest for comparison
		stringstream selfString;
		stringstream otherString;
		selfString.str(getListOfInterests());

		for (int index = 0; index < numInterests; index++)
		{
			//Read an interest from self's list of interests, delimited by a comma,
			//and store it in the temporary selfInterest string variable
			getline(selfString, selfInterest, ',');

			otherString.str(otherPerson.getListOfInterests());

			//Read each of otherPerson's interests and compare them to the item just read from self's list.
			for (int count = 0; count < otherPerson.getNumInterests(); count++)
			{
				getline(otherString, otherInterest, ',');

				if (otherInterest == selfInterest)	//If the interest strings match, add one to the accumulator.
					interestCount++;
			}

			//Repeats for each interest in both lists.
		}

		//After going through both lists, if the accumulator holds a value of at least 3 (indicating
		//at least 3 common interests), return true, indicating this person is a match for self.
		if (interestCount >= 3)
			return true;
		else
			return false;
	}

	//#######################################################################################################
	//Print Functions																						#
	//#######################################################################################################

	//Prints name and phone number of self.
	//This function assumes that the output file exists and has already been opened.
	void printInfo(ofstream &outFile) const
	{
		cout << name << ", " << phoneNum << "\n";
		outFile << name << ", " << phoneNum << "\n";
	}

	//#######################################################################################################
	//Mutator Functions																						#
	//#######################################################################################################

	//Manually set the name field of a Person object as a string passed to the function.
	void setName(string n)
	{
		name = n;
	}

	//Manually set the match field of a Person object as a string passed to the function.
	void setMatch(string m)
	{
		match = m;
	}

	//Adds a new client.  Stores the new client info in Clients.mf and outputs all interaction with the user
	//to Dates.out.
	//This function assumes that the output files passed to it exist and have already been opened.
	void newClient(ofstream &outputAll, ofstream &outputClient)
	{
		//Temporary variables used for collecting input
		int tempInt;
		char tempChar;
		string tempString;

		//Gender
		cout << "\nEnter your gender ('M' for Male, 'F' for Female): ";
		outputAll << "Enter your gender ('M' for Male, 'F' for Female): ";
		tempChar = cin.get();
		outputAll << tempChar << "\n";
		outputClient << tempChar << " ";
		gender = tempChar;
		cin.ignore();	//Clear the keyboard buffer of newline character

		//Input validation
		while (gender != 'm' && gender != 'M' && gender != 'f' && gender != 'F')
		{
			cout << "Error! You must type either M for Male or F for Female.\n";
			outputAll << "Error! You must type either M for Male or F for Female.\n";
			cout << "Enter your gender ('M' for Male, 'F' for Female): ";
			outputAll << "Enter your gender ('M' for Male, 'F' for Female): ";
			tempChar = cin.get();
			outputAll << tempChar << "\n";
			outputClient << tempChar << " ";
			gender = tempChar;
			cin.ignore();	//Clear the keyboard buffer of newline character
		}

		//Name
		cout << "Enter your name (up to 20 characters): ";
		outputAll << "Enter your name (up to 20 characters): ";
		getline(cin, tempString, '\n');
		outputAll << tempString << "\n";
		outputClient << tempString << ", ";
		name = tempString;

		while (tempString.length() > 20)
		{
			cout << "Error! 20 characters or less.\n";
			outputAll << "Error! 20 characters or less.\n";
			cout << "Enter your name (up to 20 characters): ";
			outputAll << "Enter your name (up to 20 characters): ";
			getline(cin, tempString, '\n');
			outputAll << tempString << "\n";
			outputClient << tempString << ", ";
			name = tempString;
		}

		//Phone number
		cout << "Enter your phone number (format XXX-XXXX): ";
		outputAll << "Enter your phone number (format XXX-XXXX): ";
		getline(cin, tempString, '\n');
		outputAll << tempString << "\n";
		outputClient << tempString << " ";
		phoneNum = tempString;

		while (phoneNum.length() > 8)
		{
			cout << "Error! Limit is 7 digits with a hyphen.\n";
			outputAll << "Error! Limit is 7 digits with a hyphen.\n";
			cout << "Enter your phone number (format XXX-XXXX): ";
			outputAll << "Enter your phone number (format XXX-XXXX): ";
			getline(cin, tempString, '\n');
			outputAll << tempString << "\n";
			outputClient << tempString << " ";
			phoneNum = tempString;
		}

		//Number of interests
		cout << "How many interests would you like to enter? ";
		outputAll << "How many interests would you like to enter? ";
		cin >> tempInt;
		outputAll << tempInt << "\n";
		outputClient << tempInt << " ";
		numInterests = tempInt;
		cin.ignore();	//Clear the keyboard buffer

		//Input validation
		while (numInterests < 3 || numInterests > 10)
		{
			cout << "Error! You must input between 3 and 10 interests.\n";
			cout << "How many interests would you like to enter? ";
			outputAll << "Error! You must input between 3 and 10 interests.\n";
			outputAll << "How many interests would you like to enter? ";
			cin >> tempInt;
			outputAll << tempInt << "\n";
			outputClient << tempInt << " ";
			numInterests = tempInt;
			cin.ignore();	//Clear the keyboard buffer
		}

		//List of interests
		for (int index = 0; index < numInterests; index++)
		{
			cout << "Enter interest #" << (index + 1) << " (10 characters or less): ";
			outputAll << "\nEnter interest #" << index << " (10 characters or less): ";
			getline(cin, tempString, '\n');
			outputAll << tempString << "";

			//Input validation
			while (tempString.length() > 10)
			{
				cout << "Error! 10 characters or less.\n";
				outputAll << "Error! 10 characters or less.\n";
				cout << "Enter interest #" << (index + 1) << " (10 characters or less): ";
				outputAll << "\nEnter interest #" << index << " (10 characters or less): ";
				getline(cin, tempString, '\n');
				outputAll << tempString << "";
			}

			//Store the interest in the Clients.mf file and in the person's list of interests.
			outputClient << tempString << ",";
			listOfInterests += tempString;
			listOfInterests += ",";
		}
		outputAll << ".\n";
		outputClient << ". ";
		listOfInterests += ".";

		//User does not input his or her own match, so a separate function is created for this purpose.
	}

	//Creates a matched pair between self and another Person object.
	void makeMatch(Person matched)
	{
		match = matched.getName();	//Set the match field of self to the name of the matched person.
		match += "\n";

		matched.setMatch(name + " ");	//Set the match field of the matched person to self's name.
	}
};

