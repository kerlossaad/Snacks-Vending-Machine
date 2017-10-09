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

ifstream in_file ("in.5", ios::in);
ofstream out_file ("out.5", ios::out);

using namespace std;

class EASIER_VENDING{
   public:      // public interfaces for this class
	EASIER_VENDING(string); // constructor
		// example: EASIER_VENDING CS102("CS 102 Monday Section", 10);

	void PRINT_MENU(); // a method

	void BUY_MULTI_ITEM(); // another method

private:
	// private functions:
	int CHECK_USER_ENTRY(string, int); // func to check user entry for items and money
	int CHECK_CODE(int); // func to check user entry for item code

	// private variables:
	string NAME; // var to store name of the section
	int NOOF_ITEMS; // var to store number of items, 15 max
	int ITEM_CODE[15]; // array of integers to store codes
	string ITEM_NAME[15]; // array of strings to store names
	int ITEM_PRICE[15]; // array of integers to store prices
	int ITEM_COUNT[15]; // array of integers to store noof items in stock
};

EASIER_VENDING::EASIER_VENDING(string s)
{
	int i;
	NAME = s;

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
}

void
EASIER_VENDING::PRINT_MENU()
{
	int i;

 	cout << " WELCOME TO "  << NAME << endl;
	cout << "   \tCODE\tITEM\t\tPRICE" << endl;
//	cout << "   1234567890123456789012345678901234567" << endl;
	cout << "   =====================================" << endl;
 	out_file << " WELCOME TO "  << NAME << endl;
	out_file << "   \tCODE\tITEM\t\tPRICE" << endl;
	out_file << "   =====================================" << endl;
	for(i = 0; i < NOOF_ITEMS; i++)
	{
		if (i%2 == 0)
		{
			cout << " /\\\t";
			out_file << " /\\\t";
		}
		else
		{
			cout << " \\/\t";
			out_file << " \\/\t";
		}
		cout << ITEM_CODE[i] << "\t" << ITEM_NAME[i] << "\t" 
				<< ITEM_PRICE[i] ;
		out_file << ITEM_CODE[i] << "\t" << ITEM_NAME[i] << "\t" 
				<< ITEM_PRICE[i] ;
		if (i%2 == 0)
		{
			cout << "\t/\\\t" << endl;
			out_file << "\t/\\\t" << endl;
		}
		else
		{
			cout << "\t\\/\t" << endl;
			out_file << "\t\\/\t" << endl;
		}
	}
	cout << "   =====================================" << endl;
	out_file << "   =====================================" << endl;
}

void
EASIER_VENDING::BUY_MULTI_ITEM()
{
	int i;
	int USER_ENTRY_MONEY = 0;
	int USER_ENTRY_NOOF_ITEM_TO_BUY = 0;
	int USER_ENTRY_CODE = 0;
	int ITEM_INDEX = -1;
	int ITEM_CHECK_RESULT = 0;
	int MONEY_CHECK_RESULT = 0;
	int MONEY_LEFT = 0;

 	cout << " HOW MANY ITEMS WOULD YOU LIKE TO PURCHASE? (MAX 4)" << endl;
 	out_file << " HOW MANY ITEMS WOULD YOU LIKE TO PURCHASE? (MAX 4)" << endl;
	cin >> USER_ENTRY_NOOF_ITEM_TO_BUY;
	ITEM_CHECK_RESULT = CHECK_USER_ENTRY("ITEMS", USER_ENTRY_NOOF_ITEM_TO_BUY);

	if (ITEM_CHECK_RESULT == 1)
	{
 		cout << " ENTER YOUR MONEY (MAX $10)" << endl;
 		out_file << " ENTER YOUR MONEY (MAX $10)" << endl;
		cin >> USER_ENTRY_MONEY;
		MONEY_CHECK_RESULT = CHECK_USER_ENTRY("MONEY", USER_ENTRY_MONEY);
		if(MONEY_CHECK_RESULT == 1)
		{
			MONEY_LEFT = USER_ENTRY_MONEY;
			for(i = 0; i < USER_ENTRY_NOOF_ITEM_TO_BUY && MONEY_LEFT > 0; i++)
			{
				cout << " YOU HAVE " << USER_ENTRY_NOOF_ITEM_TO_BUY - i 
						<< " CHOICES AND " << MONEY_LEFT << " DOLLARS" << endl;
				out_file << " YOU HAVE " << USER_ENTRY_NOOF_ITEM_TO_BUY - i 
						<< " CHOICES AND " << MONEY_LEFT << " DOLLARS" << endl;
 				cout << " ENTER YOUR CHOICE" << endl;
 				out_file << " ENTER YOUR CHOICE" << endl;
				cin >> USER_ENTRY_CODE;
				ITEM_INDEX = CHECK_CODE(USER_ENTRY_CODE);
				if (ITEM_INDEX == -1)
				{
					cout << " YOU SELECTED " << USER_ENTRY_CODE << endl;
					cout << " SORRY, THERE IS NO SUCH ITEM" << endl;
					out_file << " YOU SELECTED " << USER_ENTRY_CODE << endl;
					out_file << " SORRY, THERE IS NO SUCH ITEM" << endl;
				}
				else if (ITEM_INDEX == -2)
				{
					cout << " SORRY, WE ARE OUT OF "<< USER_ENTRY_CODE << endl;
					out_file << " SORRY, WE ARE OUT OF "<< USER_ENTRY_CODE << endl;
				}
				else 
				{
					if (MONEY_LEFT < ITEM_PRICE[ITEM_INDEX]) 
					{
						cout << " YOU DON'T HAVE ENOUGH MONEY FOR " << ITEM_NAME[ITEM_INDEX] << endl;
						out_file << " YOU DON'T HAVE ENOUGH MONEY FOR " << ITEM_NAME[ITEM_INDEX] << endl;
					}
					else 
					{
						MONEY_LEFT = MONEY_LEFT - ITEM_PRICE[ITEM_INDEX];
						ITEM_COUNT[ITEM_INDEX]--;

						cout << " ENJOY YOUR " << ITEM_NAME[ITEM_INDEX] << endl;
						out_file << " ENJOY YOUR " << ITEM_NAME[ITEM_INDEX] << endl;
					}
				}
			} // end of for loop

			if (MONEY_LEFT > 0)
			{
				cout << " HERE IS YOUR CHANGE OF " << MONEY_LEFT << " USD" << endl;
				cout << " THANK YOU FOR USING " << NAME << endl;
				out_file << " HERE IS YOUR CHANGE OF " << MONEY_LEFT << " USD" << endl;
				out_file << " THANK YOU FOR USING " << NAME << endl;
			}
			if (MONEY_LEFT == 0)
			{
				cout << " YOU USED EXACT CHANGE" << endl;
				cout << " THANK YOU FOR USING " << NAME << endl;
				out_file << " YOU USED EXACT CHANGE" << endl;
				out_file << " THANK YOU FOR USING " << NAME << endl;
			}
		} // end of if(MONEY_CHECK_RESULT == 1)
		else 
		{
			cout << " " << USER_ENTRY_MONEY << " IS NOT A VALID ENTRY" << endl;
			out_file << " " << USER_ENTRY_MONEY << " IS NOT A VALID ENTRY" << endl;
		}
	} //end of if (ITEM_CHECK_RESULT == 1)
	else 
	{
		cout << " " << USER_ENTRY_NOOF_ITEM_TO_BUY << " IS NOT A VALID ENTRY" << endl;
		out_file << " " << USER_ENTRY_NOOF_ITEM_TO_BUY << " IS NOT A VALID ENTRY" << endl;
	}
}

// FUNCTION: CHECK_USER_ENTRY(strin s, int INPUT)
// Input parameter INPUT: ITEMS or MONEY
// Description: Check if INPUT is legal
// 		if s is ITEMS 
// 			return 1 if legal
// 			return -1 if not legal
// 		else if s is MONEY 
// 			return 1 if legal
// 			return -1 if not legal
int
EASIER_VENDING::CHECK_USER_ENTRY(string s, int INPUT)
{
	if (s == "ITEMS")
	{
		if (INPUT > 4 || INPUT < 1)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
	if (s == "MONEY")
	{
		if (INPUT > 10 || INPUT < 1)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}
}

// FUNCTION: CHECK_CODE(int INPUT)
// Input parameter INPUT: item code entered by user
// Description: Check if INPUT is legal
// 		return the item index if there is such an item and not out of stock
// 		return -2 if there is such an item and but out of stock
// 		return -1 if no such item
int
EASIER_VENDING::CHECK_CODE(int INPUT)
{
	int i;
	int FOUND = 0; // var to hold search result
	int FOUND_POS = 0; // var to hold position of found item 
	// search if item exists
	for (i = 0; i < NOOF_ITEMS && FOUND == 0; i++)
	{
		if (ITEM_CODE[i] == INPUT)
		{
			FOUND = 1;
			FOUND_POS = i;
		}
		else {}
	}
	if(FOUND == 1)
	{
		if (ITEM_COUNT[FOUND_POS] > 0)
		{
			return FOUND_POS;
		}
		else
		{
			return -2;
		}
	}
	else
	{
		return -1;
	}
}
