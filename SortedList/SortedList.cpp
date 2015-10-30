
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <list>
#include <algorithm>


using namespace std;


class NameLoc
{
private:
    string m_name;
	string m_city;
	string m_state;

public:
    NameLoc( const string &name, const string &city, const string &state )
        : m_name( name ), m_city( city ), m_state (state)
    {

    }

    string getName() const { return m_name; }
    string getCity() const { return m_city; }
    string getState() const { return m_state; }

};


bool comparebyName( const NameLoc &lhs, const NameLoc &rhs )
{
    return lhs.getName() < rhs.getName();
}

bool comparebyCity( const NameLoc &lhs, const NameLoc &rhs )
{
    return lhs.getCity() < rhs.getCity();
}

bool comparebyState( const NameLoc &lhs, const NameLoc &rhs )
{
    return lhs.getState() < rhs.getState();
}



void main()
{

	cout << "Sort by?" << endl << endl;
	cout << "(1) Name" << endl;
	cout << "(2) City" << endl;
	cout << "(3) State" << endl << endl;
	cout << ">> ";

	int	SortMethod;
	cin >> SortMethod;

	list<NameLoc> nameLocList;

	// load the list from a file
	string line;
	ifstream inFile ("test.csv");
	if (inFile.is_open())
	{
		while ( getline (inFile, line) )
		{

			istringstream iss(line);
			string name, city, state;

			getline(iss, name, ',');
			getline(iss, city, ',');
			getline(iss, state, ',');

			nameLocList.push_back(NameLoc(name, city, state));
		}
	}

	inFile.close();


	// Sort the list
	switch (SortMethod)
	{
		case 1:
		default:
			nameLocList.sort(comparebyName);
			break;
		case 2:
			nameLocList.sort(comparebyCity);
			break;
		case 3:
			nameLocList.sort(comparebyState);
			break;
	}

	
	// Write the sorted list to a file
	ofstream outFile("sorted.csv");
	
	for( list<NameLoc>::const_iterator it = nameLocList.begin(); it != nameLocList.end(); ++it )
	{
		NameLoc t = *it;

		outFile << t.getName() << "," << t.getCity() << "," << t.getState() << endl;

	}

	return;

}


