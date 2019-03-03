#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

enum Suit {	hearts, diamonds, clubs, spades };
enum FaceValue { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };

void operator++(Suit s) { s = (Suit)((int)s + 1); }
void operator++(FaceValue f) { f = (FaceValue)((int)f + 1); }


struct Card
{
	Suit suit;
	FaceValue value;

	Card(Suit s, FaceValue f) : suit(s), value(f) {};

};


class Deck
{
private:
	stack<Card>	m_cards;	// could be an array with pointer to top card

public:

	Deck()
	{
		for (Suit s = hearts; s < spades; s++)
			for (size_t f = two; f < ace; f++)
			{
				Card newCard(s, (FaceValue)f);

				this->m_cards.push(newCard);
			}

	};


	Card drawCard()
	{
		Card nextCard = this->m_cards.top();

		this->m_cards.pop();

		return nextCard;
	}


	void shuffleDeck()
	{
		// clear all cards from this->cards
		// make stl::set of cards that will be searchable
		// draw cards at random and place on stack
	}

};

class Hand
{
private:
	vector<Card> cards;

	size_t softSum;
	size_t hardSum;
	bool bust;

public:

	Hand() : softSum(0), hardSum(0), bust(false) {};

	bool addCard(Card newCard)
	{
		this->cards.push_back(newCard);

		if (newCard.value == ace)
		{
			this->softSum += 1;
			this->hardSum += 11;
		}
		else
		{
			this->softSum += newCard.value;
			this->hardSum += newCard.value;
		}

		if ((this->hardSum > 21) && (this->softSum > 21) )
			this->bust = true;

		return this->bust;
	}

	vector<Card> showCards()
	{
		return this->cards;
	}

	void clearHand()
	{
		this->softSum = 0;
		this->hardSum = 0;
		this->bust = false;

		this->cards.clear();
	}

	size_t getHardSum()
	{
		return this->hardSum;
	}

	size_t getSoftSum()
	{
		return this->softSum;
	}

};


class BlackJack
{
private:
	Deck singleDeck;
	size_t numPlayers;

	Hand dealerHand;
	vector<Hand> playerHands;

public:

	BlackJack(size_t n) : numPlayers(n) 
	{
		Hand *newHand = new Hand[this->numPlayers];

		for (int i = 0; i < this->numPlayers; i++)
		{
			this->playerHands.push_back(newHand[i]);
		}

	};

	void shuffleDeck()
	{
		this->singleDeck.shuffleDeck();
	}

	void dealHands()
	{
		this->dealerHand.clearHand();

		for (vector<Hand>::iterator itPlayerHand = this->playerHands.begin(); itPlayerHand != this->playerHands.end(); itPlayerHand++)
			(*itPlayerHand).clearHand();


	}

};



////////////  Music Jukebox

class Song
{
private:

	char *songFilename;

	char *songName;
	char *albumName;
	char *artistName;

	size_t length;		// in seconds

public:

	char* getSongName()
	{
		return this->songName;
	}

};


class audioDevice
{
private:
	Song	*nowPlaying;

public:

	audioDevice() : nowPlaying(NULL)
	{
	};

	void playSong(Song* nextSong)
	{
		while (this->nowPlaying != NULL)
			Sleep(1000);

		this->nowPlaying = nextSong;

		// send song to device

	}

};

class Jukebox
{
private:

	static Jukebox *instance;

	audioDevice *audioPlayer;

	vector<Song*> songList;
	queue<Song*> songQ;



	Jukebox()
	{
		this->audioPlayer = new audioDevice();

		// spawn thread to run this->playSongs
	}


public:

	Jukebox* getInstance()
	{
		if (Jukebox::instance == NULL)
			this->instance = new Jukebox();

		return this->instance;
	}

	void addSong(Song* nextSong)
	{
		this->songQ.push(nextSong);
	}

	void addAlbum(vector<Song*> albumSongs)
	{
		///

	}

	char* getSongNowPlaying()
	{
		if (this->songQ.empty() == false)
		{
			return this->songQ.front()->getSongName();
		}
	}

	void displaySongs()
	{
		int c = 0;

		for (vector<Song*>::iterator itSongs = this->songList.begin(); itSongs != this->songList.end(); itSongs++, c++)
		{
			printf("%d\t%s\n", (*itSongs)->getSongName());
		}

	}

	void selectSong()
	{
		printf("Pick a song\n");
	
		size_t songID;
		scanf("%d", &songID);

		this->songQ.push(this->songList[songID]);

	}

	void playSongs()
	{

		while (1)
		{
			while (this->songQ.empty())
				Sleep(1000);

			// playSong(this->songQ.front());

			this->songQ.pop();
		}
	}
};



/////// Parking lot

/*
Are we designing a computer simulation of a parking lot or something that might track the spaces in a real parking lot like in Japan?

Should we extend it to model a parking garage with multiple levels?

Will there be a way to collect money for each space, or just a generic entry point where the driver pays to enter the lot?

Would we like a method to find the best free spaces?  Measure by proximity to exit point, or nearest attraction?
Stack - push farthest spaces on first, top-of-stack is closest space to entry point

Some spaces will be mark as handicapped

Filled spaces hold pointer to a Car class, including license plate



*/


//////// Jigsaw puzzle

/*
Classes:  Piece, Edge piece?

Pieces could keep a list of colors on the piece, comments (string) about notable features
Pieces will have a list of male/female notches that need to be matched with another piece, including a pointer to that piece (to be filled when it is matched)

Class:  Jigsaw Puzzle

Holds data structure containing all the Pieces
Start with a vector holding all the pieces (or have this come as input)

Sort corner pieces into their own array list
Sort edge pieces into their own array list
Sort middle pieces into a hashmap of arrays keyed by the comment string (main feature of the piece)

Solve puzzle:
Choose a corner piece, find the two edge pieces it matches with (do this 4 times), (will be skipped if puzzle is a circle or some odd shape)
For those edge pieces which are matched, find matches in the edge list until list is empty
Match remaining unmatched male/female knobs/notches to complete the edge around the puzzle

Go through each hashmap array and match pieces together to complete that feature

*/

enum PieceColor	{black, white, red, blue, green, yellow, orange, magenta};

class Piece
{
private:
	vector<Piece*> knobs;
	vector<Piece*> notches;

	char *featureKey;		// can be Corner, Edge, something else, or None
	PieceColor colorKey;

	bool knobsMatched;
	bool notchesMatched;
	bool fullyMatched;

public:

	Piece(size_t numKnobs, size_t numNotches, char *feature, PieceColor mainColor)
	{
		for (int i = 0; i < numKnobs; i++)
			this->knobs.push_back(NULL);

		for (int i = 0; i < numNotches; i++)
			this->notches.push_back(NULL);

		this->featureKey = new char[strlen(feature)];
		strcpy(this->featureKey, feature);

		this->colorKey = mainColor;

		this->knobsMatched = false;
		this->notchesMatched = false;
		this->fullyMatched = false;
	}

	char* getFeatureKey()
	{
		return this->featureKey;
	}

	bool isMatched()
	{
		return this->fullyMatched;
	}

	bool matchKnob(Piece* matchingNotchPiece)
	{
		for (vector<Piece*>::iterator itKnobs = this->knobs.begin(); itKnobs != this->knobs.end(); itKnobs++)
		{
			if (*itKnobs == NULL)
			{
				*itKnobs = matchingNotchPiece;

				if (itKnobs == this->knobs.end() - 1)
					this->knobsMatched = true;

				return true;
			}
		}

		return false;	// No available unmatch knobs
	}

	bool matchNotch(Piece* matchingKnobPiece)
	{
		for (vector<Piece*>::iterator itNotches = this->notches.begin(); itNotches != this->notches.end(); itNotches++)
		{
			if (*itNotches == NULL)
			{
				*itNotches = matchingKnobPiece;
				return true;
			}
		}

		return false;
	}


};



class JigsawPuzzle
{
private:

	unordered_map<string, vector<Piece*>>	hashPieces;

	bool puzzleSolved;

	size_t numPieces;
	size_t numMatchedPieces;

public:

	JigsawPuzzle(vector<Piece*>& pieceList)
	{
		this->sortPieces(pieceList);

		this->puzzleSolved = false;
		this->numMatchedPieces = 0;
	}

	void sortPieces(vector<Piece*>& pieceList)
	{
		for (vector<Piece*>::iterator itPieces = pieceList.begin(); itPieces != pieceList.end(); itPieces++)
		{
			string feature((*itPieces)->getFeatureKey());

			if (this->hashPieces.find(feature) == this->hashPieces.end())
			{
				this->hashPieces[feature] = vector<Piece*>();
			}

			this->hashPieces[feature].push_back(*itPieces);

			this->numPieces++;
		}
	}

	bool fitsWith(Piece* p1, Piece* p2)
	{
		bool fitted = false;

		return fitted;
	}

	void solvePuzzle()
	{
		vector<Piece*>::iterator itCorners = this->hashPieces["Corner"].begin();

		while (itCorners != this->hashPieces["Corner"].end())
		{
			vector<Piece*>::iterator itEdges = this->hashPieces["Edge"].begin();

			while (itEdges != this->hashPieces["Edge"].end())
			{
				if (this->fitsWith(*itCorners, *itEdges))
				{
					if ((*itEdges)->isMatched())
						// sort to the back of the array and keep record of unmatched Edges
						// or swap with end of array and pop to another array 

						if ((*itCorners)->isMatched())
							break;
				}

				itEdges++;
			}

			itCorners++;
		}

		vector<Piece*>::iterator itBaseEdge = this->hashPieces["Edge"].begin();

		while (itBaseEdge != this->hashPieces["Edge"].end())
		{
			// assume Edge list contains only unmatched Edges

			vector<Piece*>::iterator itEdges = itBaseEdge++;

			while (itEdges != this->hashPieces["Edge"].end())
			{
				if (this->fitsWith(*itBaseEdge, *itEdges))
				{
					if ((*itEdges)->isMatched());
					// swap out of array

					if ((*itBaseEdge)->isMatched())
						break;
				}

				itEdges++;
			}

			itBaseEdge++;
		}
	}

};


#define KEYS 16

template<typename T> class HashMap
{
private:

	vector<list<pair<string, T>>> listVector;

	size_t computeHash(string& inputKey)
	{
		unsigned __int64 hashValue = inputKey[0];

		for (size_t i = 1; i < inputKey.length(); i++)
			hashValue *= (unsigned __int64)inputKey[i];

		size_t keyLength = 64;

		while (keyLength > 4)
		{
			keyLength >>= 1;

			unsigned __int64 upperBits = hashValue >> keyLength;
			unsigned __int64 lowerBits = hashValue & (((unsigned __int64)1 << keyLength) - 1);

			hashValue = upperBits ^ lowerBits;
		}

		return (size_t)hashValue;
	}

	bool foundKey(size_t keyValue, string& inputKey)
	{
		list<pair<string, T>>::const_iterator itList = this->listVector[keyValue].begin();

		while (itList != this->listVector[keyValue].end())
		{
			if (get<0>(*itList) == inputKey)
				return true;

			itList++;
		}

		return false;
	}

public:


	HashMap()
	{
		for (int i = 0; i < KEYS; i++)
			this->listVector.push_back(list<pair<string, T>>());

	}


	size_t addKey(string keyString, T value)
	{
		size_t keyValue = this->computeHash(keyString);

		if (this->foundKey(keyValue, keyString) == false)
		{
			this->listVector[keyValue].push_back(make_pair(keyString, value));
		}
		else
			printf("%s already present\n", keyString);

		return keyValue;
	}

	T getValue(string keyString)
	{
		size_t keyValue = this->computeHash(keyString);

		list<pair<string, T>>::const_iterator itList = this->listVector[keyValue].begin();

		while (itList != this->listVector[keyValue].end())
		{
			if (get<0>(*itList) == keyString)
				return get<1>(*itList);

			itList++;
		}

		printf("Key not found\n");

		return NULL;
	}


};

int main()
{

	HashMap<int> stringMap;

	size_t key;
	key = stringMap.addKey("string", 1);
	key = stringMap.addKey("dog", 2);
	key = stringMap.addKey("swimsuit", 3);

	int value = stringMap.getValue("string");
	value = stringMap.getValue("strings");

	//key = stringMap.addKey("quantum");
	//key = stringMap.addKey("books");
	//key = stringMap.addKey("facetious");
	//key = stringMap.addKey("facetiously");
	//key = stringMap.addKey("bastard");
	//key = stringMap.addKey("bastards");

}