
#include <iostream>
#include <fstream>

using namespace std;

ifstream in_file ("in.4", ios::in);
ofstream out_file ("out.4", ios::out);

using namespace std;

class EASIEST_VENDING{
   public:      // public interfaces for this class
	EASIEST_VENDING(string); // constructor
		// example: EASIEST_VENDING CS102("CS 102 Monday Section", 10);

	void PRINT_MENU(); // a method

	void PURCHASE_ITEM(); // another method

private:
	// private function:
	int CHECK_MONEY(int); // function to check user entry for money
	int CHECK_CODE(int); // function to check user entry for item code

	// private variables:
	string NAME; // var to store name of the section
	int NOOF_ITEMS; // var to store number of items, 15 max
	int ITEM_CODE[15]; // array of integers to store codes
	string ITEM_NAME[15]; // array of strings to store names
	int ITEM_PRICE[15]; // array of integers to store prices
	int ITEM_COUNT[15]; // array of integers to store noof items in stock
};

EASIEST_VENDING::EASIEST_VENDING(string s)
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
 	cout << " AN OBJECT CALLED " << s << " IS CREATED." << endl;
	cout << " THERE ARE " << NOOF_ITEMS << " ITEMS IN THE VENDING MACHINE." << endl;
 	out_file << " AN OBJECT CALLED " << s << " IS CREATED." << endl;
	out_file << " THERE ARE " << NOOF_ITEMS << " ITEMS IN THE VENDING MACHINE." << endl;
}

void
EASIEST_VENDING::PRINT_MENU()
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
			cout << " /\t";
			out_file << " /\t";
		}
		else
		{
			cout << " \\\t";
			out_file << " \\\t";
		}
		cout << ITEM_CODE[i] << "\t" << ITEM_NAME[i] << "\t" 
				<< ITEM_PRICE[i] ;
		out_file << ITEM_CODE[i] << "\t" << ITEM_NAME[i] << "\t" 
				<< ITEM_PRICE[i] ;
		if (i%2 == 0)
		{
			cout << "\t\\ " << endl;
			out_file << "\t\\ " << endl;
		}
		else
		{
			cout << "\t/ " << endl;
			out_file << "\t/ " << endl;
		}
	}
	cout << "   =====================================" << endl;
	out_file << "   =====================================" << endl;
}

void
EASIEST_VENDING::PURCHASE_ITEM()
{
	int i;
	int USER_ENTRY_MONEY = 0;
	int USER_ENTRY_CODE = 0;
	int ENTRY_RETURN_VALUE = 0;
	int ITEM_INDEX = 0;
	int CHANGE = 0;

 	cout << " ENTER YOUR MONEY (MAX $10)" << endl;
 	out_file << " ENTER YOUR MONEY (MAX $10)" << endl;
	cin >> USER_ENTRY_MONEY;
	ENTRY_RETURN_VALUE = CHECK_MONEY(USER_ENTRY_MONEY);

	if (ENTRY_RETURN_VALUE == 1)
	{
 		cout << " ENTER YOUR CHOICE" << endl;
 		out_file << " ENTER YOUR CHOICE" << endl;
		cin >> USER_ENTRY_CODE;
		ITEM_INDEX = CHECK_CODE(USER_ENTRY_CODE);

		if(ITEM_INDEX != -1)
		{
			CHANGE = USER_ENTRY_MONEY - ITEM_PRICE[ITEM_INDEX];
			if (CHANGE > 0 && ITEM_COUNT[ITEM_INDEX]>0)
			{
				ITEM_COUNT[ITEM_INDEX]--;
				cout << " ENJOY YOUR " << ITEM_NAME[ITEM_INDEX] << endl;
				cout << " HERE IS YOUR CHANGE OF " << CHANGE << " USD." << endl;
				out_file << " ENJOY YOUR " << ITEM_NAME[ITEM_INDEX] << endl;
				out_file << " HERE IS YOUR CHANGE OF " << CHANGE << " USD." << endl;
			}
			else if (CHANGE == 0 && ITEM_COUNT[ITEM_INDEX]>0)
			{
				ITEM_COUNT[ITEM_INDEX]--;
				cout << " ENJOY YOUR " << ITEM_NAME[ITEM_INDEX] << endl;
				cout << " THANK YOU FOR USING EXACT CHANGE." << endl;
				out_file << " ENJOY YOUR " << ITEM_NAME[ITEM_INDEX] << endl;
				out_file << " THANK YOU FOR USING EXACT CHANGE." << endl;
			}
			else if (CHANGE >= 0 && ITEM_COUNT[ITEM_INDEX] == 0)
			{
				cout << " SORRY WE ARE OUT OF " << ITEM_NAME[ITEM_INDEX] << endl;
				cout << " HERE IS YOUR RETURN MONEY OF " << USER_ENTRY_MONEY << " USD." << endl;
				out_file << " SORRY WE ARE OUT OF " << ITEM_NAME[ITEM_INDEX] << endl;
				out_file << " HERE IS YOUR RETURN MONEY OF " << USER_ENTRY_MONEY << " USD." << endl;
			}
			else if (CHANGE < 0)
			{
				cout << " YOU DID NOT PUT ENOUGH MONEY FOR " << ITEM_NAME[ITEM_INDEX] << endl;
				cout << " HERE IS YOUR RETURN MONEY OF " << USER_ENTRY_MONEY << " USD." << endl;
				out_file << " YOU DID NOT PUT ENOUGH MONEY FOR " << ITEM_NAME[ITEM_INDEX] << endl;
				out_file << " HERE IS YOUR RETURN MONEY OF " << USER_ENTRY_MONEY << " USD." << endl;
			}
			else{}
		}
		else if (ITEM_INDEX == -1)
		{
			cout << " SORRY, NO SUCH ITEM AS " << USER_ENTRY_CODE << endl;
			cout << " HERE IS YOUR RETURN MONEY OF " << USER_ENTRY_MONEY << " USD." << endl;
			out_file << " SORRY, NO SUCH ITEM AS " << USER_ENTRY_CODE << endl;
			out_file << " HERE IS YOUR RETURN MONEY OF " << USER_ENTRY_MONEY << " USD." << endl;
		}
		else {}
	}
	else if(ENTRY_RETURN_VALUE == -1)
	{
		cout << USER_ENTRY_MONEY << " IS NOT A VALID ENTRY" << endl;
		out_file << USER_ENTRY_MONEY << " IS NOT A VALID ENTRY" << endl;
	}
	else{}
}

// FUNCTION: CHECK_MONEY(int INPUT)
// Input parameter INPUT: money entered by user
// Description: Check if INPUT is legal
// 		return 1 if legal
// 		return -1 if not legal
int
EASIEST_VENDING::CHECK_MONEY(int INPUT)
{
	if (INPUT < 1 || INPUT > 10)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

// FUNCTION: CHECK_CODE(int INPUT)
// Input parameter INPUT: item code entered by user
// Description: Check if INPUT is legal
// 		return the item index if there is such an item 
// 		return -1 if no such item
int
EASIEST_VENDING::CHECK_CODE(int INPUT)
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
		return FOUND_POS;
	}
	else
	{
		return -1;
	}
}
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

ifstream in_file ("in.4", ios::in);
ofstream out_file ("out.4", ios::out);

using namespace std;

class EASIEST_VENDING{
   public:      // public interfaces for this class
	EASIEST_VENDING(string); // constructor
		// example: EASIEST_VENDING CS102("CS 102 Monday Section", 10);

	void PRINT_MENU(); // a method

	void PURCHASE_ITEM(); // another method

private:
	// private function:
	int CHECK_MONEY(int); // function to check user entry for money
	int CHECK_CODE(int); // function to check user entry for item code

	// private variables:
	string NAME; // var to store name of the section
	int NOOF_ITEMS; // var to store number of items, 15 max
	int ITEM_CODE[15]; // array of integers to store codes
	string ITEM_NAME[15]; // array of strings to store names
	int ITEM_PRICE[15]; // array of integers to store prices
	int ITEM_COUNT[15]; // array of integers to store noof items in stock
};

EASIEST_VENDING::EASIEST_VENDING(string s)
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
 	cout << " AN OBJECT CALLED " << s << " IS CREATED." << endl;
	cout << " THERE ARE " << NOOF_ITEMS << " ITEMS IN THE VENDING MACHINE." << endl;
 	out_file << " AN OBJECT CALLED " << s << " IS CREATED." << endl;
	out_file << " THERE ARE " << NOOF_ITEMS << " ITEMS IN THE VENDING MACHINE." << endl;
}

void
EASIEST_VENDING::PRINT_MENU()
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
			cout << " /\t";
			out_file << " /\t";
		}
		else
		{
			cout << " \\\t";
			out_file << " \\\t";
		}
		cout << ITEM_CODE[i] << "\t" << ITEM_NAME[i] << "\t" 
				<< ITEM_PRICE[i] ;
		out_file << ITEM_CODE[i] << "\t" << ITEM_NAME[i] << "\t" 
				<< ITEM_PRICE[i] ;
		if (i%2 == 0)
		{
			cout << "\t\\ " << endl;
			out_file << "\t\\ " << endl;
		}
		else
		{
			cout << "\t/ " << endl;
			out_file << "\t/ " << endl;
		}
	}
	cout << "   =====================================" << endl;
	out_file << "   =====================================" << endl;
}

void
EASIEST_VENDING::PURCHASE_ITEM()
{
	int i;
	int USER_ENTRY_MONEY = 0;
	int USER_ENTRY_CODE = 0;
	int ENTRY_RETURN_VALUE = 0;
	int ITEM_INDEX = 0;
	int CHANGE = 0;

 	cout << " ENTER YOUR MONEY (MAX $10)" << endl;
 	out_file << " ENTER YOUR MONEY (MAX $10)" << endl;
	cin >> USER_ENTRY_MONEY;
	ENTRY_RETURN_VALUE = CHECK_MONEY(USER_ENTRY_MONEY);

	if (ENTRY_RETURN_VALUE == 1)
	{
 		cout << " ENTER YOUR CHOICE" << endl;
 		out_file << " ENTER YOUR CHOICE" << endl;
		cin >> USER_ENTRY_CODE;
		ITEM_INDEX = CHECK_CODE(USER_ENTRY_CODE);

		if(ITEM_INDEX != -1)
		{
			CHANGE = USER_ENTRY_MONEY - ITEM_PRICE[ITEM_INDEX];
			if (CHANGE > 0 && ITEM_COUNT[ITEM_INDEX]>0)
			{
				ITEM_COUNT[ITEM_INDEX]--;
				cout << " ENJOY YOUR " << ITEM_NAME[ITEM_INDEX] << endl;
				cout << " HERE IS YOUR CHANGE OF " << CHANGE << " USD." << endl;
				out_file << " ENJOY YOUR " << ITEM_NAME[ITEM_INDEX] << endl;
				out_file << " HERE IS YOUR CHANGE OF " << CHANGE << " USD." << endl;
			}
			else if (CHANGE == 0 && ITEM_COUNT[ITEM_INDEX]>0)
			{
				ITEM_COUNT[ITEM_INDEX]--;
				cout << " ENJOY YOUR " << ITEM_NAME[ITEM_INDEX] << endl;
				cout << " THANK YOU FOR USING EXACT CHANGE." << endl;
				out_file << " ENJOY YOUR " << ITEM_NAME[ITEM_INDEX] << endl;
				out_file << " THANK YOU FOR USING EXACT CHANGE." << endl;
			}
			else if (CHANGE >= 0 && ITEM_COUNT[ITEM_INDEX] == 0)
			{
				cout << " SORRY WE ARE OUT OF " << ITEM_NAME[ITEM_INDEX] << endl;
				cout << " HERE IS YOUR RETURN MONEY OF " << USER_ENTRY_MONEY << " USD." << endl;
				out_file << " SORRY WE ARE OUT OF " << ITEM_NAME[ITEM_INDEX] << endl;
				out_file << " HERE IS YOUR RETURN MONEY OF " << USER_ENTRY_MONEY << " USD." << endl;
			}
			else if (CHANGE < 0)
			{
				cout << " YOU DID NOT PUT ENOUGH MONEY FOR " << ITEM_NAME[ITEM_INDEX] << endl;
				cout << " HERE IS YOUR RETURN MONEY OF " << USER_ENTRY_MONEY << " USD." << endl;
				out_file << " YOU DID NOT PUT ENOUGH MONEY FOR " << ITEM_NAME[ITEM_INDEX] << endl;
				out_file << " HERE IS YOUR RETURN MONEY OF " << USER_ENTRY_MONEY << " USD." << endl;
			}
			else{}
		}
		else if (ITEM_INDEX == -1)
		{
			cout << " SORRY, NO SUCH ITEM AS " << USER_ENTRY_CODE << endl;
			cout << " HERE IS YOUR RETURN MONEY OF " << USER_ENTRY_MONEY << " USD." << endl;
			out_file << " SORRY, NO SUCH ITEM AS " << USER_ENTRY_CODE << endl;
			out_file << " HERE IS YOUR RETURN MONEY OF " << USER_ENTRY_MONEY << " USD." << endl;
		}
		else {}
	}
	else if(ENTRY_RETURN_VALUE == -1)
	{
		cout << USER_ENTRY_MONEY << " IS NOT A VALID ENTRY" << endl;
		out_file << USER_ENTRY_MONEY << " IS NOT A VALID ENTRY" << endl;
	}
	else{}
}

// FUNCTION: CHECK_MONEY(int INPUT)
// Input parameter INPUT: money entered by user
// Description: Check if INPUT is legal
// 		return 1 if legal
// 		return -1 if not legal
int
EASIEST_VENDING::CHECK_MONEY(int INPUT)
{
	if (INPUT < 1 || INPUT > 10)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

// FUNCTION: CHECK_CODE(int INPUT)
// Input parameter INPUT: item code entered by user
// Description: Check if INPUT is legal
// 		return the item index if there is such an item 
// 		return -1 if no such item
int
EASIEST_VENDING::CHECK_CODE(int INPUT)
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
		return FOUND_POS;
	}
	else
	{
		return -1;
	}
}
