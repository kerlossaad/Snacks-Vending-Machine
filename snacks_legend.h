///////////////////////////////////////////////////////////////
// 
// I UNDERSTAND THAT COPYING PROGRAMS FROM OTHERS WILL BE 
// DEALT WITH IN ACCORDANCE WITH DISCIPLINARY RULES OF CCNY.
// 
// NAME:        
// CS102 LOGIN:   
// CUNY EMAIL:  
// 
///////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>

using namespace std;

ifstream in_file ("in.6", ios::in);
ofstream out_file ("out.6", ios::out);

using namespace std;

class VENDING_SUPERVISOR{
   public:   
	VENDING_SUPERVISOR(string, int); // constructor
		// example: VENDING_SUPERVISOR CS102("CS 102 Monday Section", -9999);

	int LOGIN(); // a method

	void ITEM_UPDATE(); // a method
	void LIST_ALL();
	void LIST_CHEAPEST();
	void LIST_SORTED();

private:
	// private functions:
	int VERIFY_PASSWORD(); // func to check supervisor password;
	int CHECK_SUPER_CODE(int, string); // func to check supervisor entry
	void PRINT_ALL(); // func to print all items

	// private variables:
	string SUPER_NAME; // var to store supervisor name
	int SUPER_PASS; // var to store supervisor password

	string NAME; // var to store name of the section
	int NOOF_ITEMS; // var to store number of items, 15 max
	int ITEM_CODE[15]; // array of integers to store codes
	string ITEM_NAME[15]; // array of strings to store names
	int ITEM_PRICE[15]; // array of integers to store prices
	int ITEM_COUNT[15]; // array of integers to store noof items in stock
};

VENDING_SUPERVISOR::VENDING_SUPERVISOR(string s, int x)
{
	int i;
	NAME = s;
	SUPER_PASS = x;

	in_file >> NOOF_ITEMS;
	for(i = 0; i < NOOF_ITEMS; i++)
	{
		in_file >> ITEM_CODE[i];
		in_file >> ITEM_NAME[i];
		in_file >> ITEM_PRICE[i];
		in_file >> ITEM_COUNT[i];
	}
 	cout << " AN OBJECT CALLED " << s << " IS CREATED" << endl;
	cout << " THERE ARE " << NOOF_ITEMS << " ITEMS IN THE VENDING MACHINE" << endl;
 	out_file << " AN OBJECT CALLED " << s << " IS CREATED" << endl;
	out_file << " THERE ARE " << NOOF_ITEMS << " ITEMS IN THE VENDING MACHINE" << endl;

	cout << " ENTER YOUR NAME" << endl;
	out_file << " ENTER YOUR NAME" << endl;
	cin >> SUPER_NAME;
 	out_file << " WELCOME SUPERVISOR " << SUPER_NAME << endl;
 	cout << " WELCOME SUPERVISOR " << SUPER_NAME << endl;
}

void
VENDING_SUPERVISOR::ITEM_UPDATE()
{
	int PASSWORD_RESULT;
	int SUPER_CODE_ENTRY;
	string SUPER_ITEM_NAME_ENTRY;
	int ITEM_INDEX;
	int SUPER_ENTRY;

	PASSWORD_RESULT = VERIFY_PASSWORD();
	if(PASSWORD_RESULT == 1)
	{
		cout << " WELCOME SUPERVISOR " << SUPER_NAME << endl;
		out_file << " WELCOME SUPERVISOR " << SUPER_NAME << endl;
		cout << " WHICH ITEM YOU WANT TO UPDATE?" << endl;
		cout << " ENTER ITEM CODE " << endl;
		out_file << " WHICH ITEM YOU WANT TO UPDATE?" << endl;
		out_file << " ENTER ITEM CODE " << endl;
		cin >> SUPER_CODE_ENTRY;
		cout << " ENTER ITEM NAME " << endl;
		out_file << " ENTER ITEM NAME " << endl;
		cin >> SUPER_ITEM_NAME_ENTRY;

		ITEM_INDEX = CHECK_SUPER_CODE(SUPER_CODE_ENTRY, SUPER_ITEM_NAME_ENTRY);
		if (ITEM_INDEX == -1)
		{
			cout << " NO SUCH ITEM" << endl;	
			out_file << " NO SUCH ITEM" << endl;	
		}
		else
		{
			cout << " CURRENTLY WE HAVE " << ITEM_COUNT[ITEM_INDEX] << " ITEMS OF " 
				<< ITEM_NAME[ITEM_INDEX] << endl;
			cout << " HOW MANY ITEMS DO YOU WANT TO ADD? (MAX 3)" << endl;
			out_file << " CURRENTLY WE HAVE " << ITEM_COUNT[ITEM_INDEX] << " ITEMS OF " 
				<< ITEM_NAME[ITEM_INDEX] << endl;
			out_file << " HOW MANY ITEMS DO YOU WANT TO ADD? (MAX 3)" << endl;
			cin >> SUPER_ENTRY;
			if (SUPER_ENTRY > 0 && SUPER_ENTRY < 4)
			{
				ITEM_COUNT[ITEM_INDEX]+= SUPER_ENTRY;
				cout << " NOW WE HAVE " << ITEM_COUNT[ITEM_INDEX] << " ITEMS OF " 
					<< ITEM_NAME[ITEM_INDEX] << endl;
				out_file << " NOW WE HAVE " << ITEM_COUNT[ITEM_INDEX] << " ITEMS OF " 
					<< ITEM_NAME[ITEM_INDEX] << endl;
			}
			else
			{
				cout << " " << SUPER_ENTRY << " WAS NOT A LEGAL ENTRY" << endl; 
				out_file << " " << SUPER_ENTRY << " WAS NOT A LEGAL ENTRY" << endl; 
			}
		}
	}
	else 
	{
		cout << " PASSWORD IS NOT CORRECT" << endl;		
		out_file << " PASSWORD IS NOT CORRECT" << endl;		
	}
}

void
VENDING_SUPERVISOR::LIST_ALL()
{
	int i, PASSWORD_RESULT, SUPER_ENTRY;

	PASSWORD_RESULT = VERIFY_PASSWORD();

	if(PASSWORD_RESULT == 1)
	{
		cout << " WELCOME SUPERVISOR " << SUPER_NAME << endl;
		cout << " YOU WANT LIST OF ALL ITEMS, CORRECT? (ENTER 1 TO CONFIRM)" << endl;
		out_file << " WELCOME SUPERVISOR " << SUPER_NAME << endl;
		out_file << " YOU WANT LIST OF ALL ITEMS, CORRECT? (ENTER 1 TO CONFIRM)" << endl;
		cin >> SUPER_ENTRY;
		if(SUPER_ENTRY == 1)
		{
			PRINT_ALL();
		}
		else
		{
			cout << " SUPERVISOR " << SUPER_NAME << " PLEASE MAKE UP YOUR MIND" << endl;
			out_file << " SUPERVISOR " << SUPER_NAME << " PLEASE MAKE UP YOUR MIND" << endl;
		}
	}
	else 
	{
		cout << " PASSWORD IS NOT CORRECT" << endl;		
		out_file << " PASSWORD IS NOT CORRECT" << endl;		
	}
}

void
VENDING_SUPERVISOR::LIST_CHEAPEST()
{
	int i, PASSWORD_RESULT, SUPER_ENTRY;
	int MIN_PRICE;

	PASSWORD_RESULT = VERIFY_PASSWORD();

	if(PASSWORD_RESULT == 1)
	{
		cout << " WELCOME SUPERVISOR " << SUPER_NAME << endl;
		cout << " YOU WANT LIST OF CHEAPEST ITEMS, CORRECT? (ENTER 1 TO CONFIRM)" << endl;
		out_file << " WELCOME SUPERVISOR " << SUPER_NAME << endl;
		out_file << " YOU WANT LIST OF CHEAPEST ITEMS, CORRECT? (ENTER 1 TO CONFIRM)" << endl;
		cin >> SUPER_ENTRY;
		if(SUPER_ENTRY == 1)
		{
			MIN_PRICE = ITEM_PRICE[0];
			// find min first
			for(i=0; i < NOOF_ITEMS; i++)
			{
				if(MIN_PRICE > ITEM_PRICE[i])
				{
					MIN_PRICE = ITEM_PRICE[i];
				}
				else{}
			}
			// now print the items whose prices equal to value of MIN
			cout << "\tCODE" 
		 			<< "\tNAME" 
		 			<< "\t\tPRICE" 
		 			<< "\tCOUNT" << endl;
			cout << "\t=====================================" << endl;
			out_file << "\tCODE" 
		 			<< "\tNAME" 
		 			<< "\t\tPRICE" 
		 			<< "\tCOUNT" << endl;
			out_file << "\t=====================================" << endl;
			for(i=0; i < NOOF_ITEMS; i++)
			{
				if(MIN_PRICE == ITEM_PRICE[i])
				{
					cout << "\t" << ITEM_CODE[i] 
			 			<< "\t" << ITEM_NAME[i] 
			 			<< "\t" << ITEM_PRICE[i] 
			 			<< "\t" << ITEM_COUNT[i] << endl;
					out_file << "\t" << ITEM_CODE[i] 
			 			<< "\t" << ITEM_NAME[i] 
			 			<< "\t" << ITEM_PRICE[i] 
			 			<< "\t" << ITEM_COUNT[i] << endl;
				}
				else{}
			}
		}
		else
		{
			cout << " SUPERVISOR " << SUPER_NAME << " PLEASE MAKE UP YOUR MIND" << endl;
			out_file << " SUPERVISOR " << SUPER_NAME << " PLEASE MAKE UP YOUR MIND" << endl;
		}
	}
	else 
	{
		cout << " PASSWORD IS NOT CORRECT" << endl;		
		out_file << " PASSWORD IS NOT CORRECT" << endl;		
	}
}

void
VENDING_SUPERVISOR::LIST_SORTED()
{
	int i, j, PASSWORD_RESULT, SUPER_ENTRY;
	int MIN, MIN_POS, MAX, MAX_POS, temp;
	string temp_string;
	string SUPER_STRING_ENTRY;

	PASSWORD_RESULT = VERIFY_PASSWORD();

	if(PASSWORD_RESULT == 1)
	{
		cout << " WELCOME SUPERVISOR " << SUPER_NAME << endl;
		cout << " YOU WANT SORTED LIST OF ITEMS, CORRECT? (ENTER 1 TO CONFIRM)" << endl;
		out_file << " WELCOME SUPERVISOR " << SUPER_NAME << endl;
		out_file << " YOU WANT SORTED LIST OF ITEMS, CORRECT? (ENTER 1 TO CONFIRM)" << endl;
		cin >> SUPER_ENTRY;
		if(SUPER_ENTRY == 1)
		{
			cout << " ENTER ASC FOR SORTING ASCENDING, DESC FOR DESCENDING ORDER" << endl;
			out_file << " ENTER ASC FOR SORTING ASCENDING, DESC FOR DESCENDING ORDER" << endl;
			cin >> SUPER_STRING_ENTRY;
			if(SUPER_STRING_ENTRY == "ASC")
			{
				// sort ascending
				for(i=0; i < NOOF_ITEMS; i++)
				{
					MIN = ITEM_CODE[i];
					MIN_POS = i;
					for(j=i; j < NOOF_ITEMS; j++)
					{
						if(MIN > ITEM_CODE[j])
						{
							MIN = ITEM_CODE[j];
							MIN_POS = j;
						}
						else{}
					}
					// swap ith items with MIN_POS items

					temp = ITEM_CODE[i];
					ITEM_CODE[i] = ITEM_CODE[MIN_POS];
					ITEM_CODE[MIN_POS] = temp;

					temp_string = ITEM_NAME[i];
					ITEM_NAME[i] = ITEM_NAME[MIN_POS];
					ITEM_NAME[MIN_POS] = temp_string;

					temp = ITEM_PRICE[i];
					ITEM_PRICE[i] = ITEM_PRICE[MIN_POS];
					ITEM_PRICE[MIN_POS] = temp;

					temp = ITEM_COUNT[i];
					ITEM_COUNT[i] = ITEM_COUNT[MIN_POS];
					ITEM_COUNT[MIN_POS] = temp;
				}
				PRINT_ALL();
			}
			else if(SUPER_STRING_ENTRY == "DESC")
			{
				// sort descending
				for(i=0; i < NOOF_ITEMS; i++)
				{
					MAX = ITEM_CODE[i];
					MAX_POS = i;
					for(j=i; j < NOOF_ITEMS; j++)
					{
						if(MAX < ITEM_CODE[j])
						{
							MAX = ITEM_CODE[j];
							MAX_POS = j;
						}
						else{}
					}
					// swap ith items with MAX_POS items

					temp = ITEM_CODE[i];
					ITEM_CODE[i] = ITEM_CODE[MAX_POS];
					ITEM_CODE[MAX_POS] = temp;

					temp_string = ITEM_NAME[i];
					ITEM_NAME[i] = ITEM_NAME[MAX_POS];
					ITEM_NAME[MAX_POS] = temp_string;

					temp = ITEM_PRICE[i];
					ITEM_PRICE[i] = ITEM_PRICE[MAX_POS];
					ITEM_PRICE[MAX_POS] = temp;

					temp = ITEM_COUNT[i];
					ITEM_COUNT[i] = ITEM_COUNT[MAX_POS];
					ITEM_COUNT[MAX_POS] = temp;
				}
				PRINT_ALL();
			}
			else
			{
				cout << " SUPERVISOR " << SUPER_NAME << " PLEASE MAKE UP YOUR MIND" << endl;
				out_file << " SUPERVISOR " << SUPER_NAME << " PLEASE MAKE UP YOUR MIND" << endl;
			}
		}
		else
		{
			cout << " SUPERVISOR " << SUPER_NAME << " PLEASE MAKE UP YOUR MIND" << endl;
			out_file << " SUPERVISOR " << SUPER_NAME << " PLEASE MAKE UP YOUR MIND" << endl;
		}
	}
	else 
	{
		cout << " PASSWORD IS NOT CORRECT" << endl;		
		out_file << " PASSWORD IS NOT CORRECT" << endl;		
	}
}

// FUNCTION: VERIFY_PASSWORD()
// Input parameter: None;
// Description: Check if suoervisor enters the correct password
// 			return 1 if correct
// 			return -1 if not correct
int
VENDING_SUPERVISOR::VERIFY_PASSWORD()
{
	int i;
	int SUPER_ENTRY;

	cout << " ENTER PASSWORD SUPERVISOR " << SUPER_NAME << endl;
	out_file << " ENTER PASSWORD SUPERVISOR " << SUPER_NAME << endl;
	cin >> SUPER_ENTRY;

	if (SUPER_PASS == SUPER_ENTRY)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// FUNCTION: PRINT_ALL()
// Input parameter: None
// Description: print all items
void
VENDING_SUPERVISOR::PRINT_ALL()
{
	int i;
	
	cout << "\tCODE" 
		 << "\tNAME" 
		 << "\t\tPRICE" 
		 << "\tCOUNT" << endl;
	cout << "\t=====================================" << endl;
	out_file << "\tCODE" 
		 << "\tNAME" 
		 << "\t\tPRICE" 
		 << "\tCOUNT" << endl;
	out_file << "\t=====================================" << endl;
	for(i=0; i < NOOF_ITEMS; i++)
	{
		cout << "\t" << ITEM_CODE[i] 
			 << "\t" << ITEM_NAME[i] 
			 << "\t" << ITEM_PRICE[i] 
			 << "\t" << ITEM_COUNT[i] << endl;
		out_file << "\t" << ITEM_CODE[i] 
			 << "\t" << ITEM_NAME[i] 
			 << "\t" << ITEM_PRICE[i] 
			 << "\t" << ITEM_COUNT[i] << endl;
	}
}

// FUNCTION: CHECK_SUPER_CODE(int INPUT, string S)
// Input parameter: integer INPUT entered by supervisor for item code
// Input parameter: string S entered by supervisor for item name
// Description: Check if an item with INPUT and S exists
// 			return item position if exists
// 			return -1 if does not exist
int
VENDING_SUPERVISOR::CHECK_SUPER_CODE(int INPUT, string S)
{
	int i;
	int FOUND = 0; // var to hold search result
	int FOUND_POS = -1; // var to hold position of found item 
	// search if item exists
	for (i = 0; i < NOOF_ITEMS && FOUND == 0; i++)
	{
		if (ITEM_CODE[i] == INPUT && ITEM_NAME[i] == S) 
		{
			FOUND = 1;
			FOUND_POS = i;
		}
		else {}
	}
	if(FOUND == 1)
	{
		return FOUND_POS;
	}
	else
	{
		return -1;
	}
}
