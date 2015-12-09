//MathGame.cpp
//
//The Math Game
//Computer Science 340
//Los Angeles Harbor College
//Written by Horacio Santoyo
//	09/04/15 - First draft
//	09/30/15 - Removed goto labels (replaced with while loops)
//	10/03/15 - Added validateUserInput() function
//	10/03/15 - Added credits() function (to display application credits)
//	10/03/15 - Added console text colors
//	10/05/15 - Misc updates
//	10/21/15 - Converted functions to pass values by reference instead of by value
//	11/02/15 - Changed saveStats function to pass variables by value

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>
#include <windows.h> //to display console text colors

using namespace std;

//Declare functions
int splash(); //Splash screen (First screen seen by user with option to continue or exit)
string user(); //Gets name from user (With input validation)
int validateUserInput(int type, string input); //User input validation
void menu(); //Draws menu
int menuChoice(); //Handles user's menu choice (With input validation)
void credits(); //Program's info
void displayStats(string name, double cash, int correct, int incorrect);//Displays the user's current score
void readStats(string &name, double &cash, int &correct, int &incorrect); //Read user's score from existing file
void saveStats(string name, double cash, int correct, int incorrect); //Saves user's score
void processAnswer(int type, double &cash, int &correct, int &incorrect );
int generateAddition(); 
int generateSubtraction();
int generateMultiplication();
int generateDivision();

const double RIGHT = .5, WRONG = .3;

int main ()
{
	//Declare variables
	string name;
	int choice, correct = 0, incorrect = 0;
	double cash = 0;

	if (splash() == 1)
	{	
		system("CLS");
		name = user();
		readStats(name, cash, correct, incorrect);
		choice = menuChoice();

		while (choice > 0)
		{
			switch(choice)
			{
				//1 = Correct answer, 2 = Incorrect Answer, 3 = Display Stats, 4 = Display credits
				case 1:
					processAnswer(1, cash, correct, incorrect);
					break;
				case 2:
					processAnswer(2, cash, correct, incorrect);
					break;
				case 3:
					displayStats(name, cash, correct, incorrect);
					break;
				case 4:
					credits();
					break;	
			}
			choice = menuChoice();
		}

		saveStats(name, cash, correct, incorrect);
	}
	cout << "Good bye!\n\n";
	system("pause");
	return(0);
}


//Splash
int splash()
{
	string input;
	int getInput = 0;

	system("CLS");

	cout << "***************************\n";
	cout << "***************************\n";
	cout << "***************************\n";
	cout << "****                   ****\n";
	cout << "****   The Math Game   ****\n";
	cout << "****        By:        ****\n";
	cout << "****  Horacio Santoyo  ****\n";
	cout << "****                   ****\n";
	cout << "***************************\n";
	cout << "***************************\n";
	cout << "***************************\n\n";

	cout << "y/Y to continue, any other key to exit\n";
	getline(cin, input);

	getInput = 1;

	while(getInput = 1)
	{
		if(input.length() == 0)
		{
			cout << "y/Y to continue, any other key to exit\n";
			getline(cin, input);
		}
		else if (input == "y" || input == "Y")
		{	
			getInput = 0;
			return(1);
		}
		else
		{
			getInput = 0;
			return(0);
		}
	}
	return (0);	
}


//Name input
string user()
{
	string name;
	int getInput;

	cout << "Enter your name and press <ENTER>: ";

	getline(cin, name);
	getInput = 1;

	while(getInput ==1)
	{
		if(validateUserInput(3,name) == 1)
		{
			cout << "\nPlease enter a valid name: ";
			getline(cin, name);
		}
		else if(validateUserInput(3,name) == 2)
		{
		    cout << "\nPlease enter only your first name: ";
			getline(cin, name);
		}
		else
		{
			getInput = 0;
		}
	}

	system("CLS");
	return(name);
}


//Menu
void menu()
{
	cout << "***** CHOOSE A PROBLEM *****\n";
	cout << "****************************\n";
	cout << "****************************\n";
	cout << "*****                  *****\n";
	cout << "*****   1. ADD         *****\n";
	cout << "*****   2. SUBTRACT    *****\n";
	cout << "*****   3. MULTIPLY    *****\n";
	cout << "*****   4. DIVIDE      *****\n";
	cout << "*****   5. STATS       *****\n";
	cout << "*****   C. CREDITS     *****\n";
	cout << "*****   N. QUIT        *****\n";
	cout << "*****                  *****\n";
	cout << "****************************\n";
	cout << "****************************\n";
	cout << "****************************\n\n";
}


//Menu choice
int menuChoice()
{
	string input;
	int choice;
	int getInput;

	menu();

	getline(cin, input);
	getInput = 1;

	while(getInput == 1)
	{
		if(validateUserInput(2,input) == 1)
		{
			cout << "Enter a valid menu option: ";
			getline(cin, input);
		}
		else
		{	
			getInput = 0;

			if (input == "n" || input == "N" || input == "n/N")
				return(0);

			choice = atoi(input.c_str());

			if (input == "c" || input == "C")
				choice = 6;

			switch (choice)
			{
				case 1:
					if (generateAddition() == 1)
						return(1); //1 = correct answer
					else
						return(2); //2 = incorrect answer
					break;
				case 2:
					if (generateSubtraction() == 1)
						return(1);
					else
						return(2);
					break;
				case 3:
					if (generateMultiplication() == 1)
						return(1);
					else
						return(2);
					break;
				case 4:
					if (generateDivision() == 1)
						return(1);
					else
						return(2);
					break;
				case 5:
					return(3);
					break;
				case 6:
					return(4);
					break;
				default:
					cout << "Enter a valid menu option: ";
					getline(cin, input);
					getInput = 1;
					break;
			}
		}
	}
	return(0);
}


//Process user's answer
void processAnswer(int type, double &cash, int &correct, int &incorrect)
{
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (type == 1)
	{	
		correct++;
		cash = cash + RIGHT;

		cout << "**********";
		SetConsoleTextAttribute(hConsole, 10);		
		cout << " RIGHT! ";
		SetConsoleTextAttribute(hConsole, 7);
		cout << "**********\n\n";
	}
	else
	{
		incorrect++;
		cash = cash - WRONG;			

		cout << "**********";
		SetConsoleTextAttribute(hConsole, 12);		
		cout << " WRONG! ";
		SetConsoleTextAttribute(hConsole, 7);
		cout << "**********\n\n";
	}
}


//Addition function
int generateAddition()
{
	system("CLS");

	unsigned seed = unsigned(time(0));
	srand(seed);

	string input;
	int getInput;
	int a = (rand() % 10) + 1;
	int b = (rand() % 10) + 1;
	double answer;
	
	cout << "*****   ADDITION   *****\n";
	cout << "************************\n";
	cout << "************************\n";
	cout << "*****              *****\n";
	cout << "***** " << right << setw(2) << a << " + " << left << setw(2) << b << " = ?  *****\n";
	cout << "*****              *****\n";
	cout << "************************\n";
	cout << "************************\n";

	getline(cin, input);
	getInput = 1;

	while(getInput == 1)
	{
		if(validateUserInput(1,input) == 1)
		{
			cout << "Enter a positive number: ";
			getline(cin, input);
		}
		else
		{
			getInput = 0;
		}
	}

	answer = atof(input.c_str());

	system("CLS");
	
	if (answer == a + b)
		return 1;
		else
		return 0;
}


//Subtraction function
int generateSubtraction()
{
	system("CLS");

	unsigned seed = unsigned(time(0));
	srand(seed);

	string input;
	int getInput;
	int a = (rand() % 10) + 1;
	int b = (rand() % 10) + 1;
	int c;
	double answer;

	if (a < b)
	{
		c = a;
		a = b;
		b = c;
	}

	cout << "***** SUBTRACTION  *****\n";
	cout << "************************\n";
	cout << "************************\n";
	cout << "*****              *****\n";
	cout << "***** "
		 << right << setw(2) << a << " - " << left << setw(2) << b << " = ?"
		 << "  *****\n";
	cout << "*****              *****\n";
	cout << "************************\n";
	cout << "************************\n";

	getline(cin, input);
	getInput = 1;

	while(getInput == 1)
	{
		if(validateUserInput(1,input) == 1)
		{
			cout << "Enter a positive number: ";
			getline(cin, input);
		}
		else
		{
			getInput = 0;
		}
	}

	answer = atof(input.c_str());

	system("CLS");

	if (answer == a - b)
		return 1;
		else
		return 0;
}


//Multiplication function
int generateMultiplication()
{
	system("CLS");

	unsigned seed = unsigned(time(0));
	srand(seed);

	string input;
	int getInput;
	int a = (rand() % 10) + 1;
	int b = (rand() % 10) + 1;
	double answer;

	cout << "*****MULTIPLICATION*****\n";
	cout << "************************\n";
	cout << "************************\n";
	cout << "*****              *****\n";
	cout << "***** "
		 << right << setw(2) << a << " x " << left << setw(2) << b << " = ?"
		 << "  *****\n";
	cout << "*****              *****\n";
	cout << "************************\n";
	cout << "************************\n";

	getline(cin, input);
	getInput = 1;

	while(getInput == 1)
	{
		if(validateUserInput(1,input) == 1)
		{
			cout << "Enter a positive number: ";
			getline(cin, input);
		}
		else
		{
			getInput = 0;
		}
	}

	answer = atof(input.c_str());

	system("CLS");

	if (answer == a * b)
		return 1;
		else
		return 0;
}


//Division function
int generateDivision()
{
	system("CLS");
	unsigned seed = unsigned(time(0));
	srand(seed);

	string input;
	int getInput;
	int a = (rand() % 50) + 1;
	int b = (rand() % 10) + 1;
	int c;
	double answer;

	if (a < b)
	{
		c = a;
		a = b;
		b = c;
	}

	a = a - (a % b);

	cout << "*****   DIVISION   *****\n";
	cout << "************************\n";
	cout << "************************\n";
	cout << "*****              *****\n";
	cout << "***** "
		 << right << setw(2) << a << " / " << left << setw(2) << b << " = ?"
		 << "  *****\n";
	cout << "*****              *****\n";
	cout << "************************\n";
	cout << "************************\n";

	getline(cin, input);
	getInput = 1;

	while(getInput == 1)
	{
		if(validateUserInput(1,input) == 1)
		{
			cout << "Enter a positive number: ";
			getline(cin, input);
		}
		else
		{
			getInput = 0;
		}
	}

	answer = atof(input.c_str());

	system("CLS");

	if (answer == a / b)
		return 1;
		else
		return 0;
}


int validateUserInput(int type, string input)
{
	//1 = number validation
	//2 = menu choice validation
	//3 = name validation

	size_t pos = input.find_first_of(" ");
	int spac = input.find(" ",0);

	switch (type)
	{
		case 1:
			if (input.find_first_not_of("0123456789.") != string::npos || input.length() == 0)
				return(1);	
			else
				return(0);				
			break;
		case 2:
			if (input.find_first_not_of("12345nNcC") != string::npos || input.length() == 0)
				return(1);
			else
				return(0);
			break;
		case 3:
			if (input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWYXZ ") != string::npos || input.length() == 0 || pos < 1)
				return(1);	
			else
			{
				if (spac > 0)
					return(2);	
				else
					return(0);	
			}
			break;
	}
	return(0);
}

//Function to read user's score from existing file
void readStats(string &name, double &cash, int &correct, int &incorrect)
{
		//If user's file exists, read saved score, otherwise use default values
		string fname = name + ".txt";
		ifstream inFile;
		inFile.open(fname.c_str());
		if (inFile)
		{
			inFile >> name;
			inFile >> correct;
			inFile >> incorrect;
			inFile >> cash;
			inFile.close();
		}
}


//Function to save user's score
void saveStats(string name, double cash, int correct, int incorrect)
{
	string fname = name + ".txt";
	ofstream outFile;
	outFile.open(fname.c_str());

	system("CLS");
	cout << "Saving score... ";

	// Write score to the file.
	outFile << name << "\n";
	outFile << correct << "\n";
	outFile << incorrect << "\n";
	outFile << cash << "\n";
	outFile.close();
	cout << " done!\n\n";
}


//Stats
void displayStats(string name, double cash, int correct, int incorrect)
{
	system("CLS");

	if (name.length() > 14)
		name = name.substr(0,12) + "...";

	name = "[" + name + "]";

	cout << "*****       STATS       *****\n";
	cout << "*****************************\n";
	cout << "*****************************\n";
	cout << "*****                   *****\n";
	cout << "***** " << left << setw(17) << name << " *****\n";
	if(cash < 10)
		cout << "***** Earnings:   $" << left << setw(5);
	else
		cout << "***** Earnings:  $" << left << setw(6);
	cout << fixed << showpoint << setprecision(2) << cash << "*****\n";
	cout << "***** Correct:   " << right << setw(3) << correct << "    *****\n";
	cout << "***** Incorrect: " << setw(3) << incorrect << "    *****\n";
	cout << "*****                   *****\n";
	cout << "*****************************\n";
	cout << "*****************************\n";
	cout << "*****************************\n\n";

	system("pause");
	system("CLS");
}


//Function to display program's credits
void credits()
{
	system("CLS");

	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned seed = unsigned(time(0));
	srand(seed);

	int x = (rand() % 2) + 1;

	SetConsoleTextAttribute(hConsole, 15);		

	switch(x)
	{
		case 1:
			cout << "              *     ,MMM8&&&.            *	\n";
			cout << "                   MMMM88&&&&&    .	\n";
			cout << "                  MMMM88&&&&&&&	\n";
			cout << "      *           MMM88&&&&&&&&	\n";
			cout << "                  MMM88&&&&&&&&	\n";
			cout << "                  'MMM88&&&&&&'	\n";
			cout << "                    'MMM8&&&'      *	\n";
			cout << "           |\\___/|	\n";
			cout << "           )     (             .              '	\n";
			cout << "          =\\     /=	\n";
			cout << "            )===(       *	\n";
			cout << "           /     \\	\n";
			cout << "           |     |	\n";
			cout << "          /       \\	\n";
			cout << "          \\       /	\n";
			cout << "   _/\\_/\\_/\\__  _/_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_/\\_	\n";
			cout << "   |  |  |  |( (  |  |  |  |  |  |  |  |  |  |	\n";
			cout << "   |  |  |  | ) ) |  |  |  |  |  |  |  |  |  |	\n";
			cout << "   |  |  |  |(_(  |  |  |  |  |  |  |  |  |  |	\n";
			cout << "    hs|  |  |  |  |  |  |  |  |  |  |  |  |  |	\n";
			break;
		case 2:	
			cout << "\n\n\n\n";
			cout << "	                         .-. \n";
			cout << "	                          \\ \\ \n";
			cout << "	                           \\ \\ \n";
			cout << "	                            | | \n";
			cout << "	                            | | \n";
			cout << "	          /\\---/\\   _,---._ | | \n";
			cout << "	         /^   ^  \\,'       `. ; \n";
			cout << "	        ( O   O   )           ; \n";
			cout << "	         `.=o=__,'            \\ \n";
			cout << "	           /         _,--.__   \\ \n";
			cout << "	          /  _ )   ,'   `-. `-. \\ \n";
			cout << "	         / ,' /  ,'        \\ \\ \\ \\ \n";
			cout << "	        / /  / ,'          (,_)(,_) \n";
			cout << "	       (,;  (,,) \n\n";
			break;                            
	}

	SetConsoleTextAttribute(hConsole, 143);			

	cout << "	The Math Game				\n";
	cout << "	Written by Horacio Santoyo		\n";
	cout << "	Computer Science 340			\n";
	cout << "	L.A. Harbor College, Fall 2015		\n";
	
	SetConsoleTextAttribute(hConsole, 7);			
	
	system("pause");
	system("CLS");
}
