//Amanda Kaufman
//Programming Assignment 2
//CISS 350
//This file contains the linked implementation of the UnsortedType list class in Chapter 3 of the textbook.

#pragma once
#include "Person.h";
#include <new>	//Needed to catch bad_alloc exception

//Define the NodeType structure for use in this list.
struct NodeType
{
	Person info;
	NodeType* next;
};

class UnsortedType
{
private:
	NodeType* listData;
	int length;
	NodeType* currentPos;
public:
	//Constructor initializes the length of the list and the head pointer.
	UnsortedType()
	{
		length = 0;
		listData = nullptr;
	}

	//Destructor makes the list empty, freeing up memory for other applications.
	~UnsortedType()
	{
		makeEmpty();
	}

	//Empties the list and deallocates all items.
	void makeEmpty()
	{
		NodeType *tempPtr;

		while (listData != nullptr)
		{
			tempPtr = listData;
			listData = listData->next;
			delete tempPtr;
		}

		length = 0;
	}

	//Returns true if there is no room for another Person on the free store; false otherwise.
	bool isFull() const
	{
		NodeType *location;

		try
		{
			location = new NodeType;
			delete location;
			return false;
		}
		catch (std::bad_alloc exception)
		{
			return true;
		}
	}

	//Returns the number of items in the list.
	int getLength() const
	{
		return length;
	}

	//Returns currentPos
	NodeType* getCurrentPos() const
	{
		return currentPos;
	}

	//If the object passed as a parameter matches an object in the list, matching item is returned.
	//Otherwise, object passed as a parameter is returned.
	//Note: This function assumes that the object passed to the function has been initialized.
	Person getItem(Person item, bool& found)
	{
		bool moreToSearch;
		NodeType *location;

		location = listData;
		found = false;
		moreToSearch = (location != NULL);

		while (moreToSearch && !found)
		{
			switch (item.comparedTo(location->info))
			{
			case LESS:
			case GREATER: location = location->next;
				moreToSearch = (location != NULL);
				break;
			case EQUAL: found = true;
				item = location->info;
				break;
			}
		}

		return item;
	}

	//Inserts an item into the list and increments the list length.
	void putItem(Person item)
	{
		NodeType *location;			//Declare a pointer to a node

		location = new NodeType;	//Allocate a new node
		location->info = item;		//Store the item in the node
		location->next = listData;	//Store address of first node in next field of new node
		listData = location;		//Store address of new node into external pointer
		length++;					//Increment the length of the list
	}

	//Deletes a node from the list.
	//Note: this function assumes that the object passed as a parameter exists in the list,
	//based on a matching key.  It also assumes the object passed as a parameter was initialized.
	void deleteItem(Person item)
	{
		NodeType *location = listData;
		NodeType *tempLocation;

		//Locate node to be deleted.
		//If the first node matches the parameter, delete the first node.
		if (item.comparedTo(listData->info) == EQUAL)
		{
			tempLocation = location;
			listData = listData->next;
		}
		//Otherwise, search the list for the node and delete it.
		else
		{
			while (item.comparedTo((location->next)->info) != EQUAL)
				location = location->next;

			//Once found, delete the node at location->next;
			tempLocation = location->next;	//Store address of the node to be deleted
			location->next = (location->next)->next;	//Move the pointer from the previous node to the one after
		}

		delete tempLocation;	//Delete the node
		length--;	//Decrement the length of the list
	}
	
	//Initialize current position at the start of the list.
	void resetList()
	{
		currentPos = NULL;
	}

	//Returns a copy of the next item in the list.
	//When the end of the list is reached, currentPos is reset to the beginning of the list.
	Person getNextItem()
	{
		if (currentPos == NULL)		//If currentPos is pointing to the end of the list
			currentPos = listData;	//reset it at the beginning of the list
		else
			currentPos = currentPos->next;	//Otherwise, move currentPos to the next list item
		return currentPos->info;			//Return the information stored in the next list item
	}
};

