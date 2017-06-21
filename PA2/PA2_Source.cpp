//Amanda Kaufman
//Programming Assignment 2
//CISS 350
//This program acts as a command-line dating service.  It stores client information and finds matches for new clients
//based on a minimum number of common interests.

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Person.h";
#include "UnsortedType.h";
using namespace std;

//Prototypes for functions used in main()
void addNewClient(ofstream &, ofstream &, UnsortedType &, UnsortedType &);
void clearMatch(ofstream &, UnsortedType &, UnsortedType &);
void printMatches(ofstream &, UnsortedType &, UnsortedType &);
void printUnmatched(ofstream &, UnsortedType &, UnsortedType &);

int main()
{
	string command;		//String to hold the user's typed command
	int commandNum;		//Command number for switch statement

	UnsortedType men;	//List for men
	UnsortedType women;	//List for women

	//Open Dates.out for echo copy of all program input and output
	ofstream outputAll;
	outputAll.open("Dates.out", ios::out);

	//Open Clients.mf to export all new client information
	ofstream outputClients;
	outputClients.open("Clients.mf", ios::out);

	cout << "Welcome to the Command Line Dating App!\n\n";
	outputAll << "Welcome to the Command Line Dating App!\n\n";

	//Main menu and get user input
	do {
		cout << "\nPlease type one of the following commands and hit [Enter].\n";
		outputAll << "\nPlease type one of the following commands and hit [Enter].\n";
		cout << "Please note: all commands are case-sensitive.\n\n";
		outputAll << "Please note: all commands are case-sensitive.\n\n";
		cout << left << setw(12) << "NEWCLIENT: " << "Allows you to input your information as a new client.\n";
		outputAll << left << setw(12) << "NEWCLIENT: " << "Allows you to input your information as a new client.\n";
		cout << left << setw(12) << "UNMATCH: " << "Unmatches you from your current matched pair.\n";
		outputAll << left << setw(12) << "UNMATCH: " << "Unmatches you from your current matched pair.\n";
		cout << left << setw(12) << "PRINTMATCH:" << "Prints a list of all matched pairs.\n";
		outputAll << left << setw(12) << "PRINTMATCH:" << "Prints a list of all matched pairs.\n";
		cout << left << setw(12) << "PRINTFREE: " << "Prints a list of all unmatched individuals.\n";
		outputAll << left << setw(12) << "PRINTFREE: " << "Prints a list of all unmatched individuals.\n";
		cout << left << setw(12) << "QUIT: " << "Quit the program.\n\n";
		outputAll << left << setw(12) << "QUIT: " << "Quit the program.\n\n";

		getline(cin, command);
		outputAll << command << endl;

		//Convert the typed command to an integer for switch statement.
		if (command == "NEWCLIENT")
			commandNum = 0;
		else if (command == "UNMATCH")
			commandNum = 1;
		else if (command == "PRINTMATCH")
			commandNum = 2;
		else if (command == "PRINTFREE")
			commandNum = 3;
		else if (command == "QUIT")
			commandNum = 5;
		else
			commandNum = 4;

		//Take a different action depending on the command typed by the user.
		switch (commandNum)
		{
		case 0: addNewClient(outputAll, outputClients, men, women);
			break;
		case 1: clearMatch(outputAll, men, women);
			break;
		case 2: printMatches(outputAll, men, women);
			break;
		case 3: printUnmatched(outputAll, men, women);
			break;
		case 4:
			cout << "Command not found.  Please try again.\n\n";
			outputAll << "Command not found.  Please try again.\n\n";
			break;
		case 5:
			break;
		}

	} while (command != "QUIT");

	//Close the output files.
	outputAll.close();
	outputClients.close();

	return 0;
}

//Creates a new client, adds the person to the appropriate gender list, and searches the
//list of the opposite gender for a match.  If a match is found, prints the names and
//phone numbers of the matched pair.
void addNewClient(ofstream &outFile, ofstream &clientsList, UnsortedType &men, UnsortedType &women)
{
	//Create a new person object.
	Person newPerson;

	//Get information from the user to create a new client.
	newPerson.newClient(outFile, clientsList);

	//Add the new client to the appropriate list.
	if (newPerson.getGender() == 'M' || newPerson.getGender() == 'm')
		men.putItem(newPerson);
	else
		women.putItem(newPerson);

	//Search the other list for a match for the person.
	Person temp;					//Used to store the information of a match
	bool foundMatch = false;

	if (newPerson.getGender() == 'M' || newPerson.getGender() == 'm')	//If new person is a male, search the female list for a match.
	{
		for (int count = 0; count < women.getLength(); count++)
		{
			temp = women.getNextItem();

			if (newPerson.isMatch(temp))			//If the person in the list is a match for newPerson,
			{
				//Create the matched pair.
				newPerson.setMatch(temp.getName());				//Save temp's name in newPerson's match field
				temp.setMatch(newPerson.getName());				//Save newPerson's name in the temp object's match field
				men.deleteItem(newPerson);						//Delete the old version of the new person from the men list
				women.deleteItem(temp);							//Delete the old version of the compared person from the women list
				men.putItem(newPerson);							//Put the modified newPerson object back into the men list
				women.putItem(temp);							//Put the modified temp object back into the women list
				clientsList << temp.getName() << "\n\n";		//Write the name of the matched person's name to the Clients.out file as a match for newPerson

				//Output a message for the user with the match information.
				cout << "\nMatch found!\n";						
				outFile << "\nMatch found!\n";
				newPerson.printInfo(outFile);
				temp.printInfo(outFile);
				cout << endl;
				outFile << endl;

				foundMatch = true;					//Set the found match flag to true
				count = women.getLength();			//Manually set count to exit the loop once match is found
			}
		}

		//Reset currentPos in the women list
		women.resetList();
	}

	else	//If new person is a female, search the male list for a match.
	{
		for (int index = 0; index < men.getLength(); index++)
		{
			temp = men.getNextItem();

			if (newPerson.isMatch(temp))			//If the person in the list is a match for newPerson,
			{
				//Create the matched pair.
				newPerson.setMatch(temp.getName());				//Save temp's name in newPerson's match field
				temp.setMatch(newPerson.getName());				//Save newPerson's name in the temp object's match field
				women.deleteItem(newPerson);					//Delete the old version of the new person from the women list
				men.deleteItem(temp);							//Delete the old version of the compared person from the men list
				women.putItem(newPerson);						//Put the modified newPerson object back into the women list
				men.putItem(temp);								//Put the modified temp object back into the men list
				clientsList << temp.getName() << "\n\n";		//Write the name of the matched person's name to the Clients.out file as a match for newPerson

				//Output a message for the user with the match information.
				cout << "\nMatch found!\n";
				outFile << "\nMatch found!\n";
				newPerson.printInfo(outFile);
				temp.printInfo(outFile);
				cout << endl;
				outFile << endl;

				foundMatch = true;					//Set the found match flag to true
				index = men.getLength();			//Manually set count to exit the loop once match is found
			}
		}

		//Reset currentPos in the men list
		men.resetList();
	}

	//If foundMatch is still set to false, output a courtesy message for the user.
	if (!foundMatch)
	{
		cout << "\nSorry!  We didn't find that special someone for you this time,\n";
		cout << "but try again later!  There's still hope for you yet.\n\n";
		outFile << "Sorry!  We didn't find that special someone for you this time,\n";
		outFile << "but try again later!  There's still hope for you yet.\n\n";
		clientsList << "No match.\n\n";
	}

	system("pause");
}

//Clears the match of a client specified by the user.
void clearMatch(ofstream &outputAll, UnsortedType &menList, UnsortedType &womenList)
{
	string input;
	Person temp;		//For use in searching the person to be unmatched
	Person toUnmatch;	//Holds information of person to be unmatched
	bool personFound = false;

	cout << "\nWho would you like to unmatch? Enter full name: ";
	outputAll << "Who would you like to unmatch? Enter full name: ";
	getline(cin, input, '\n');
	outputAll << input << endl;

	//Process 1: Unmatch the first person.
	temp.setName(input);

	//Attempt to get the person to be unmatched from the men list.
	toUnmatch = menList.getItem(temp, personFound);

	//If the person was found here, delete the old item from the list that matches the data stored in toUnmatch.
	if (personFound)
		menList.deleteItem(toUnmatch);

	//If the person was found in the men list, the following code will not execute.
	//If the person was not found in the men list, the program proceeds to search the women list.
	if (!personFound)
	{
		toUnmatch = womenList.getItem(temp, personFound);

		//If the person was found here, delete the old item from the list that matches the data stored in toUnmatch.
		if (personFound)
			womenList.deleteItem(toUnmatch);
	}

	//If personFound is still set to false (the person was not located in the list), output an error message.
	if (!personFound)
	{
		cout << "Sorry, we could not find the person you entered in the list.\n\n";
		outputAll << "Sorry, we could not find the person you entered in the list.\n\n";

		system("pause");
	}

	//Otherwise, process the person found.
	else
	{
		//toUnmatch now holds all the information of the person to be unmatched.
		//Store the name of the person currently in the match field, for later use.
		input = toUnmatch.getMatchName();

		//Clear the match field of this object to prepare it for reinsertion into the list.
		toUnmatch.setMatch("");

		//Reinsert the node into the appropriate list.
		if (toUnmatch.getGender() == 'm' || toUnmatch.getGender() == 'M')
			menList.putItem(toUnmatch);
		else
			womenList.putItem(toUnmatch);

		//Process 2: Unmatch the person's match.
		temp.setName(input);

		//Reset the found flag to false.
		personFound = false;

		//Attempt to get the person to be unmatched from the men list.
		toUnmatch = menList.getItem(temp, personFound);

		//If the person was found here, delete the old item from the list that matches the data stored in toUnmatch.
		if (personFound)
			menList.deleteItem(toUnmatch);

		//If the person was found in the men list, the following code will not execute.
		//If the person was not found in the men list, the program proceeds to search the women list.
		if (!personFound)
		{
			toUnmatch = womenList.getItem(temp, personFound);

			//If the person was found here, delete the old item from the list that matches the data stored in toUnmatch.
			if (personFound)
				womenList.deleteItem(toUnmatch);
		}
			
		//If personFound is still set to false (the person was not located in the list), output an error message.
		if (!personFound)
		{
			cout << "Sorry, we could not find the matched person in the list.\n\n";
			outputAll << "Sorry, we could not find the matched person in the list.\n\n";

			system("pause");
		}

		//Otherwise, process the person found.
		else
		{
			//toUnmatch now holds all the information of the person to be unmatched.
			//Clear the match field of this object to prepare it for insertion into the list.
			toUnmatch.setMatch("");

			//Reinsert the node into the appropriate list.
			if (toUnmatch.getGender() == 'm' || toUnmatch.getGender() == 'M')
				menList.putItem(toUnmatch);
			else
				womenList.putItem(toUnmatch);

			cout << "Your unmatch request was successfully processed.\n\n";
			outputAll << "Your unmatch request was successfully processed.\n\n";

			system("pause");
		}
	}
}

//Prints the list of clients that are currently  matched.
void printMatches(ofstream &outputAll, UnsortedType &menList, UnsortedType &womenList)
{
	//Create temporary variables to use for retrieving items.
	Person menTemp;
	Person womenTemp;

	//Create a boolean variable to display if there are no items to show at this time.
	bool hasMatches = false;

	//Reset currentPos in both the men and women lists.
	menList.resetList();

	//Display header for list
	cout << "\nCurrent Match List:\n";
	cout << "------------------------------------------\n";
	outputAll << "\nCurrent Match List:\n";
	outputAll << "------------------------------------------\n";

	//Get each item from the men list.
	for (int index = 0; index < menList.getLength(); index++)
	{
		menTemp = menList.getNextItem();

		womenList.resetList();
		//Get each item from the women list.
		for (int count = 0; count < womenList.getLength(); count++)
		{
			womenTemp = womenList.getNextItem();
			
			//If the name field of the womenTemp object equals the match field of the menTemp object
			//AND vice versa, the pair is a match.  Output their info.
			if (menTemp.getName() == womenTemp.getMatchName() && womenTemp.getName() == menTemp.getMatchName())
			{
				hasMatches = true;
				menTemp.printInfo(outputAll);
				womenTemp.printInfo(outputAll);
				cout << endl;		//Extra line break between pairs
				outputAll << endl;	//Copy to output file
			}
		}
	}

	//If hasMatches is false, there are currently no matched pairs.  Inform the user.
	if (!hasMatches)
	{
		cout << "\nThere are currently no matched pairs.\n\n";
		outputAll << "\nThere are currently no matched pairs.\n\n";
	}


	//Reset both lists for other functions' use.
	menList.resetList();
	womenList.resetList();

	system("pause");
}

//Prints the list of single clients (not currently matched).
void printUnmatched(ofstream &outputAll, UnsortedType &menList, UnsortedType &womenList)
{
	//Reset the currentPos for both lists.
	menList.resetList();
	womenList.resetList();

	//Create a temporary Person object for holding information.
	Person temp;

	//Create boolean variables for informing the user if the list is empty.
	bool hasSingleMen = false;
	bool hasSingleWomen = false;

	//Output lists for the user.
	cout << "\nIndividuals Not Yet Matched:\n";
	outputAll << "Individuals Not Yet Matched:\n";

	//Unmatched men
	cout << "\nMen\n-------------------------------\n";
	outputAll << "Men\n-------------------------------\n";

	for (int index = 0; index < menList.getLength(); index++)
	{
		temp = menList.getNextItem();
		if (temp.getMatchName() == "")
		{
			hasSingleMen = true;
			temp.printInfo(outputAll);
		}			
	}

	//If hasSingleMen is still false, everyone is matched or there is no one in the list.
	if (!hasSingleMen)
	{
		cout << "\nThere are currently no single men. Sorry!";
		outputAll << "\nThere are currently no single men. Sorry!";
	}

	cout << endl << endl;
	outputAll << endl << endl;

	//Unmatched women
	cout << "\nWomen\n-----------------------------\n";
	outputAll << "Women\n-----------------------------\n";

	for (int index = 0; index < womenList.getLength(); index++)
	{
		temp = womenList.getNextItem();
		if (temp.getMatchName() == "")
		{
			hasSingleWomen = true;
			temp.printInfo(outputAll);
		}
	}

	//If hasSingleWomen is still false, everyone is matched or there is no one in the list.
	if (!hasSingleWomen)
	{
		cout << "\nThere are currently no single women. Sorry!";
		outputAll << "\nThere are currently no single women. Sorry!";
	}

	cout << endl << endl;
	outputAll << endl << endl;

	//Reset both lists for other functions' use.
	menList.resetList();
	womenList.resetList();
	
	system("pause");
}