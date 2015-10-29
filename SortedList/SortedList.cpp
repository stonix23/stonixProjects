
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


bool operator<( const NameLoc &lhs, const NameLoc &rhs )
{
    return lhs.getName() < rhs.getName();
}


void main()
{

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
	nameLocList.sort();
	
	// Write the sorted list to a file
	ofstream outFile("sorted.csv");
	
	for( list<NameLoc>::const_iterator it = nameLocList.begin(); it != nameLocList.end(); ++it )
	{
		NameLoc t = *it;

		outFile << t.getName() << "," << t.getCity() << "," << t.getState() << endl;

	}

	return;

}


