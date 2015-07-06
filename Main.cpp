#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <string>
#include <time.h>
#include <sstream>
#include <math.h>
#include <Windows.h>
#include <direct.h>
#include <iomanip>
#include <sys/stat.h>
#include <utility>
#include <cmath>
#pragma comment(lib, "winmm.lib")
using namespace std;

void centerint(double num, int width)
{
  stringstream ss;
  ss << num;
  string str = ss.str();
  int pad = (width - str.size())/2;
  for(int i = 0; i < pad; i++)
    cout << " ";
  cout << str << endl;
}

void Exterior();
void calculations();
void Interior();
void makefile();
void openfile(vector<double>&, vector<string>&);
int checkvalid(string);
ofstream createtxt();
void intro();
double surfacearea(double, double, double, double);
double removeobs(double);
double costext(double, int, int);
void interiorcalc();
void loading();

template <typename T>
ostream & operator << (ostream &out, const vector<T> &v)
{
	size_t last = v.size() - 1;
	for (size_t i = 0; i < v.size(); i++)
	{
		out << v[i];
		if (i != last)
			out << endl;				//Use this to change what is between the Vectors (between the double quotes) Right now its 1 space between each value
	}
	return out;
}

//Global Variables
char again;
string file;
string filename;
string add;
string test1 = "yards";
string test2 = "feet";
string checkunit;
vector<double> prices;
vector<string> items;
vector<string> conjecture;
const double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
vector<int> unit;
int rep;
double length, width, height1, height2;

enum COLORS								//Just Color Names
{
	black,
	blue,
	green,
	cyan,
	red,
	magenta,
	brown,
	normal,
	darkgrey,
	lightblue,
	lightgreen,
	lightcyan,
	lightred,
	lightmagenta,
	yellow,
	white
};
ostream& operator << (ostream &textcolor, const COLORS &Color)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);			//Found on Google, to be honest
	SetConsoleTextAttribute(out, Color);				//Included in Windows.h
	return(textcolor);							//returns the name, evertime, cout is called
	//changes the test color to whatevr name was called
}

int main()
{
	intro();
	while(true)
	{
		loading();
		cout << "What is the job being done right now?\n\tE - Exterior\n\tI - Interior\n\t";
		cin >> again;
		if(again == 'e' || again == 'E')
		{
			system("CLS");
			Exterior();
			system("CLS");
		}
		if(again == 'i' || again == 'I')
		{
			system("CLS");
			Interior();
			system("CLS");
		}
	}
}

void makefile()
{
	int units;
	int result1 = MessageBox(HWND_DESKTOP, L"Would you Like to Make your own list?", L"Custom", MB_YESNO);
	switch (result1)
	{
		case IDYES:
		{
			/*
			while(true)
			{
				char choose;						//Local Char Choose
				cout << "Pick a directory (Ex. C:\\Users\\Me\\Cplusplus\\ <--- Dont forget last \\\nPress Enter to Continue with the Same Directory\n----> ";
				string directory;
				getline(cin, directory);
				struct stat dirtest;
				if (stat(directory.c_str(), &dirtest) == 0)
				{
					_chdir(directory.c_str());
					break;
				}
				else
				{
					if(directory.length() == 0)
					{
						system("CLS");
						break;
					}
					for (int x = 0; x < 5; x++)
					{
						Sleep(250);
						cout << lightblue << "\rPLEASE ENTER A VALID DIRECTORY!!";
						Sleep(250);
						cout << lightred << "\rPLEASE ENTER A VALID DIRECTORY!!";
					}
					system("CLS");
					system("COLOR 30");
					continue;
				}
		}
		*/
			int result1 = MessageBox(HWND_DESKTOP, L"Would you Like to See a List of the Text Files in the Current Directory?", L"Text Files?", MB_YESNO);
			switch (result1)
			{
				case IDYES:
				{
					system("dir *.txt /a-d /b");
					int result2 = MessageBox(HWND_DESKTOP, L"Would you like to delete all these files?", L"DELETE", MB_YESNO);
					switch (result2)
					{
					case IDYES:
					{
						int result = MessageBox(HWND_DESKTOP, L"Are You SURE??", L"Confirmation", MB_YESNO | MB_ICONWARNING);
						switch (result)
						{
						case IDYES:
							string c = "del /Q ";
							string p = "*.txt";
							system(c.append(p).c_str());
							break;
						}
					}
					}
					break;
				}
				case IDNO:
				{
					break;
				}
			}
			system("pause");
			while (true)		//Infinite Loop, Leave with breaks
			{
				system("COLOR 30");
				system("CLS");		//Clears Screen
				cout << "Please Enter the Desired Filename(Please Exclude the .txt at the end)\n[MAX LENGTH = 128]:\n----> ";
				getline(cin, filename);		//Getline allows for spaces, instead of traditional cin >>
				if (filename.length() == 0)
					getline(cin, filename);
				if (!checkvalid(filename))		//calls checkvalid on the filename
				{
					for (int x = 0; x<5; x++)
					{
						Sleep(250);
						cout << lightblue << "\rTHAT IS NOT VALID";
						Sleep(250);
						cout << lightred << "\rTHAT IS NOT VALID";
					}
					Sleep(1000);
					system("CLS");
					continue;
				}
				string directory;
				filename += ".txt";		//Adds .txt to end of string, since user was specified NOT to add .txt at end
				int result = MessageBox(HWND_DESKTOP, L"Would you like to pick a certain directory?", L"Confirmation", MB_YESNO | MB_ICONWARNING);
					switch (result)
					{
						case IDYES:
						{
							cout << "Enter the Specified Directory (Ex. C:\\Users\\Me\\)<---Please dont forget last \\\n----> ";
							getline(cin, directory);
							filename = directory + filename;
							break;
						}

						case IDNO:
						{
							break;
						}
					}
				//If they did, it will look like filename.txt.txt
				if (!filename.empty())		//If the filename is not empty
				{
					system("CLS");		//Clears Screen
					cout << "Your File is: \n" << filename << endl;	//Shows User their inputted Filename
					system("PAUSE");					//Pauses the Screen
					break;							//Leaves the Loop
				}
				else		//If the Message is empty
				{
					continue;	//Stay in the Loop
				}
			}
			ofstream of = createtxt();
			double price;
			while(true)
			{
				add.clear();
				system("CLS");
				cout << "Pick an item to add to the list.\n-->";
				getline(cin, add);
				if(add.length() == 0)
					getline(cin, add);
				cout << "Enter a price for this item.\nFormat ->Price Units\nFor Example, 12 tiles for $8.5 would be 8.5 12\n-->";
				cin >> price >> units;
				while(true)
				{
					cout << "Is this in yards or feet?\n-->";
					cin >> checkunit;
					if(checkunit.compare(test1) != 0 && checkunit.compare(test2) != 0)
					{
						for (int x = 0; x<5; x++)
						{
							Sleep(250);
							cout << lightblue << "\rTHAT IS NOT VALID";
							Sleep(250);
							cout << lightred << "\rTHAT IS NOT VALID";
						}
					Sleep(1000);
					system("COLOR 30");
					system("CLS");
					continue;
					}
					else
						break;
				}
				system("CLS");
				cout << "This is your item and price.\n-->";
				cout << add << " $" << price/units << endl;
				of << add << "/ " << price << " " << units << " " << checkunit << endl;
				cout << "Would you like to add another item? (Y/N)\n-->";
				cin >> again;
				if(again == 'y' || again == 'Y')
					continue;
				else
					break;
			}
		}
		case IDNO:
		{
			break;
		}
	}
	openfile(prices, items);
	//read from the thing, do calculations
}

void Interior()
{
	makefile();
	interiorcalc();
}

void Exterior()
{
	makefile();
	calculations();
}

int checkvalid(string filename)		//Makes sure the filename is valid (does not have special characters)
{
	for (int i = 0; i < filename.length(); i++)
	{
		if  (
			filename.at(i) == '\\'|| 
			filename.at(i) == '/' || 
			filename.at(i) == '*' || 
			filename.at(i) == '?' || 
			filename.at(i) == '"' || 
			filename.at(i) == '<' || 
			filename.at(i) == '>' || 
			filename.at(i) == '|'
			)
		{
			return 0;
		}
	}
	return 1;
}

void intro()
{ //FUNCTION (INTRO) START
	//Each system("COLOR __") changes Foreground and Background colors
	system("mode 650");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);			//Maximizes the console to fit the screen
	system("Color 1B");
	Sleep(500);
	system("CLS");
	cout << "\n\t\t\t\tThe Dream House";
	system("Color 2D");
	Sleep(500);
	system("CLS");
	cout << "\n\n\t\t\t\tThe Dream House";
	system("Color 3E");
	Sleep(500);
	system("CLS");
	cout << "\n\n\n\t\t\t\tThe Dream House";
	system("Color 4F");
	Sleep(500);
	system("CLS");
	cout << "\n\n\n\n\t\t\t\tThe Dream House";
	system("Color 5A");
	Sleep(500);
	system("CLS");
	cout << "\n\n\n\n\n\t\t\t\tThe Dream House";
	system("Color 1C");
	Sleep(500);
	system("CLS");
	system("COLOR 81");
	cout << "\n\n\n\n\n\n\t\t\t\tThe Dream House\n";
	Sleep(500);
	system("COLOR A7");
	cout << lightmagenta << "\t\t\t\tAbhishek  Patel\n";
	Sleep(500);
	system("COLOR FA");
	cout << white << "\t\t\t        Surya Venkatram\n";
	Sleep(500);
	system("COLOR B3");
	cout << lightred << "\t\t\t\t   Abby Tan\n";
	Sleep(500);
	system("COLOR 42");
	cout << lightgreen << "\t\t\t\t    Ian Li\n";
	Sleep(500);
	system("COLOR 30");
} //FUNCTION (INTRO) END

ofstream createtxt()
{ //FUNCTION (MAKE TXT FILE) START
	//****************************************************
	ofstream Stuff;				//****			Makes The Text File
	Stuff.open(filename.c_str()); //****
	//****************************************************
	return Stuff;	//Returns Location of Stuff
} //FUNCTION (MAKE TXT FILE) END

void openfile(vector<double>&prices, vector<string>&items)
{ //FUNCTION (OPEN FILE FOR READ) START
	while(true)
	{
		cout << "Pick a directory (Ex. C:\\Users\\Me\\Cplusplus\\ <--- Dont forget last \\\nPress Enter to Continue with the Same Directory\n----> ";
		string directory;
		getline(cin, directory);
		if(directory.length() == 0)
			getline(cin, directory);
		struct stat dirtest;
		if (stat(directory.c_str(), &dirtest) == 0)
		{
			_chdir(directory.c_str());
			system("CLS");
			cout << "Here is a list of all the .txt files in the Directory.\n";
			if(system("dir *.txt /b"))
			{
				cout << "\nThis Directory has no Text Files Available,\nPick a different directory.\n";
				Sleep(1500);
				system("CLS");
				continue;
			}
			break;
		}
		else
		{
			if(directory.length() == 0)
			{
				system("CLS");
				cout << "Here is a list of all the .txt files in the Directory.\n";
				if(system("dir *.txt /b"))
				{
					cout << "\nThis Directory has no Text Files Available,\nPick a different directory.\n";
					Sleep(1500);
					system("CLS");
					continue;
				}
				break;
			}
			for (int x = 0; x < 5; x++)
			{
				Sleep(250);
				cout << lightblue << "\rPLEASE ENTER A VALID DIRECTORY!!";
				Sleep(250);
				cout << lightred << "\rPLEASE ENTER A VALID DIRECTORY!!";
			}
			system("CLS");
			system("COLOR 30");
			continue;
		}
	}
	cout << "\n";
	ifstream EncodedM;
	while (true)
	{
		cout << "Please Enter the Filename of your List\n-->";
		getline(cin, file);
		if (file.length() == 0)
			getline(cin, file);
		EncodedM.open(file.c_str(), ifstream::in);
		if (file.length() == 0)
			continue;
		if (EncodedM.good())
			break;
		if (EncodedM.fail())
		{
			for (int x = 0; x<5; x++)
			{
				Sleep(250);
				cout << lightblue << "\rPLEASE ENTER A VALID FILENAME!!";
				Sleep(250);
				cout << lightred << "\rPLEASE ENTER A VALID FILENAME!!";
			}
			Sleep(1000);
			system("CLS");
			system("COLOR 30");
			cout << "Here is a list of all the .txt files in the Directory.\n";
			system("dir *.txt /a-d /b");
			cout << "\n";
			continue;
		}
	}	
	struct stat filestats;
	stat(file.c_str(), &filestats);
	printf("Last status change:       %s\n", ctime(&filestats.st_ctime));
    printf("Last file access:         %s\n", ctime(&filestats.st_atime));
    printf("Last file modification:   %s\n", ctime(&filestats.st_mtime));
	system("PAUSE");
	char read;
	string word;
	double readnumber;
	int unitss;
	string temp2;
	word.clear();
	temp2.clear();
	system("CLS");
	while(!EncodedM.eof())
	{
		while(EncodedM >> read)
		{
			if(read == '/')
			{
				EncodedM >> readnumber >> unitss >> temp2;
				prices.push_back(readnumber);
				unit.push_back(unitss);
				conjecture.push_back(temp2);
				break;
			}
			word.push_back(read);
		}
		items.push_back(word);
		word.clear();
	}
} //FUNCTION (OPEN FILE FOR READ) END

void calculations()
{
	double fcost = 0;
	vector<string> temp;
	while(true)
	{
		int b = 1111;
		while(true)
		{
			cout << "Price                                        Item\n";
			cout << "-----                                        ----\n";
			for(int i = 0; i < prices.size(); i++)
			{
				cout << setw(50) 
					 << items.at(i) 
					 << "\r" 
					 << fixed 
					 << setprecision(2) 
					 << prices.at(i) 
					 << endl;
			}
			int j = 0;
			string chitem;
			cout << "Please select the item you wish to purchase.\n-->";
			getline(cin, chitem);
			if(chitem.length() == 0)
				getline(cin, chitem);
			for(int i = 0; i < items.size(); i++)
			{
				string temp = items.at(i);
				if(items.at(i).compare(chitem) != 0)
					j++;
				else
					b = i;
			}
			if(j == items.size())
			{
				for (int x = 0; x < 5; x++)
				{
					Sleep(250);
					cout << lightblue << "\rPLEASE ENTER A VALID NAME!!";
					Sleep(250);
					cout << lightred << "\rPLEASE ENTER A VALID NAME!!";
				}
				system("CLS");
				system("COLOR 30");
				continue;
			}
			else
				break;
		}
		cout << "What are the dimensions of the house? (Enter then as L W H1 H2)\nH1 is the bottom, and H2 is the part with the triangle\n-->";
		cin >> length >> width >> height1 >> height2;
		cout << "How many times are you using the item on the house?";
		cin >> rep;
		double SA = surfacearea(length, width, height1, height2);
		double final = removeobs(SA);
		system("CLS");
		cout << "This is your final surface area: " << final << endl;
		fcost = fcost + costext(final, b, rep);
		temp.push_back(items.at(b));
		cout << "And your total cost as of now is: $" << fcost << endl;
		cout << "Would you like to add another item to your order? (Y/N)\n-->";
		cin >> again;
		if(again == 'y' || again == 'Y')
		{
			system("CLS");
			continue;
		}
		else
			break;
	}
	system("CLS");
	cout << "Your Final Subtotal is: $" << fcost << endl;
	cout << "And Your purchased items are\n--------------------------------\n";
	cout << temp;
	cout << endl;
	system("PAUSE");
}

double surfacearea(double length, double width, double height1, double height2)
{
	double temp, temp2, temp3, temp4;
	temp2 = length * height1 * 2;
	temp3 = height1 * width * 2;
	temp4 = height2 * width;
	return temp2 + temp3 + temp4;
}

double removeobs(double SA)
{
	double semiwindows;
	double windows;
	double door;
	windows = 10 * 5 * 3;
	float e = 3;
	semiwindows = 2 * pow(e,2) / 2 * PI;
	door = 7 * 4;
	double final = SA - windows - semiwindows - door;
	return final;
}

double costext(double final, int a, int rep)
{
	double c;
	double b;
	double ans;
	b = final / unit.at(a);
	c = (prices.at(a));
	b = b * rep;
	b = ceil(b);
	ans = c * b;
	return ans;
}

void interiorcalc()
{
	/*
	14 * 14 + 12 * 11 * 2 = 460
	51.1111111
	^ divided by 5
	10.22222
	10.22222 * 5 (dimensions of the roll)
	^^ * 18.95 (cheaper carpet)
	^^ * 29.95 (expensive caxerpet)
	*/
	double fcost = 0;
	double area = 0;
	vector<string> temp;
	while(true)
	{
		int b = 1111;
		while(true)
		{
			area = 0;
			cout << "Price                                        Item\n";
			cout << "-----                                        ----\n";
			for(int i = 0; i < prices.size(); i++)
			{
				cout << setw(50) 
					 << items.at(i) 
					 << "\r" 
					 << fixed 
					 << setprecision(2) 
					 << prices.at(i) 
					 << endl;
			}
			int j = 0;
			string chitem;
			cout << "Please select the item you wish to purchase.\n-->";
			getline(cin, chitem);
			if(chitem.length() == 0)
				getline(cin, chitem);
			for(int i = 0; i < items.size(); i++)
			{
				string temp = items.at(i);
				if(items.at(i).compare(chitem) != 0)
					j++;
				else
					b = i;
			}
			if(j == items.size())
			{
				for (int x = 0; x < 5; x++)
				{
					Sleep(250);
					cout << lightblue << "\rPLEASE ENTER A VALID NAME!!";
					Sleep(250);
					cout << lightred << "\rPLEASE ENTER A VALID NAME!!";
				}
				system("CLS");
				system("COLOR 30");
				continue;
			}
			else
				break;
		}
		cout << "Enter the number of rooms being done today.";
		cin >> rep;
		while(rep > 0)
		{
			cout << "Enter the dimensions of the room. (Enter as L W)\nIf the dimensions are 12 by 8, you enter 12 8\n-->";
			cin >> length >> width;
			area = area + (length * width);
			--rep;
		}
		if(conjecture.at(b) == "yards")
		{
			area = ceil(area / 9);
			if(area == 52)
				area += 3;
		}
		system("PAUSE");
		fcost = fcost + (ceil(area/unit.at(b)) * prices.at(b));
		fcost = area * prices.at(b);
		system("CLS");
		temp.push_back(items.at(b));
		cout << "The total area is: " << area << conjecture.at(b) << "\n";
		cout << "The total cost is: $" << fcost << endl;
		cout << "Would you like to add another item to your order? (Y/N)\n-->";
		cin >> again;
		if(again == 'y' || again == 'Y')
		{
			system("CLS");
			continue;
		}
		else
			break;
	}
	system("CLS");
	cout << "Your Final Subtotal is: $" << fcost << endl;
	cout << "And Your purchased items are\n--------------------------------\n";
	cout << temp;
	cout << endl;
	system("PAUSE");
}

void loading()
{
	for(int j = 0; j < 3; j++)
	{
		cout << "Please Wait";
		Sleep(100);
		for(int i = 0; i < 3; i++)
		{
			int a = i;
			while(a > 0)
			{
				cout << ".";
				Sleep(300);
				a--;
			}
		}
		cout << "\r                                    \r";
	}
}
