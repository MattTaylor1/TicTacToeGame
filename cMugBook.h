#ifndef _cMugBook_HG_
#define _cMugBook_HG_

#include <vector>
#include "cPerson.h"
#include "cTicTacToeGameInstance.h"

class cMugBook
{
public:
	// Some functions how have a std::string &error being passed by reference. 
	// If the call is successful, this value is ignored by the caller. 
	// If the call fails, this should return some "printable" message indicating why.

	// You MUST implement a constructor (c'tor) and destructor (d'tor) 
	// EVEN IF IT DOESN'T ACTUALLY DO ANYTHING 
	cMugBook();
	~cMugBook();


	bool checkPostal(std::string postalCode);
	bool checkString(std::string theString);
	std::string formatString(std::string theString);
	std::string formatProvince(std::string province);

	// Returns true of the user is already there AND the values are identical
	// Returns false if data is invalid or missing
	bool addUser(cPerson* pThePerson);
	// This would call delete the pointer to the cPerson
	bool deleteUser(unsigned int SIN);

	// This will only update the data that is DIFFERENT **AND** VALID
	// In other words, the user has to exist already
	//
	//	bool updateUser(cPerson thePersonWithNewInfo);   **REMOVED**
	bool updateUserLastName(unsigned int SIN, std::string newLastName);
	bool updateUserFirstName(unsigned int SIN, std::string newFirstName);
	// The province and postal code needs to be valid
	// std::string &error returns printable reason for failure (bad province, empty field, etc.):
	// NOTE: you only have to return the 1st error, not all of them.
	// You can decide what is the "1st" thing you check.
	bool updateUserAddress(unsigned int SIN, int streetNumber, std::string streetName,
		std::string streetType, std::string streetDirection,
		std::string city, std::string province, /*Province now as enum)*/
		std::string postalCode, std::string& error);
	bool updateUserGender(unsigned int SIN, cPerson::eGenderType newGenderExpression);
	bool updateUserPhoneNumber(unsigned int SIN, unsigned char phoneNumber[13]);

	// Returns NULL if not found.
	cPerson* getUser(unsigned int SIN);

	// Returns true if it's OK.
	// Returns false if:
	//	* user doesn't exist
	//	* friend doesn't exist (or is invalid)
	//	* user and friend are the same person
	// std::string &error returns printable reason for failure:
	//	- User doesn't exist
	//	- Friend doesn't exit
	bool addFriend(unsigned int UserSIN, unsigned int FriendSIN, std::string& error);
	bool unFriend(unsigned int UserSIN, unsigned int FormerFriendSIN, std::string& error);

	// Returns false if user doesn't exit
	// vecFreindList can be zero (which is sad, but valid)
	bool getFriendList(unsigned int UsersSIN, std::vector<cPerson*>& vecFriendList);

	bool saveState(std::string fileName);
	// This will CLEAR all the present state and replace it with what's in the file
	bool loadState(std::string fileName);

	//bonus
	bool saveUser(unsigned int SIN, std::string filename);
	bool loadUser(std::string fileName);

	// ****************************************************************************
	// 	   
	// This is ALL THE SAME as with Project #3 & 4, with the *following additions*:
	// 
	// ****************************************************************************

	

	// Returns the SIN of a user not currently in a game.
	// Returns zero (0) if no user can be found.
	unsigned int findANonPlayingTicTacToeUser(void);

	// Returns the SIN of any player for "white" to play against.
	// The SIN of the "white" player is passed (so you don't return them).
	// Returns zero (0) if no user can be found.
	unsigned int findAvailableTicTacToeOpponent(unsigned int OpponentPlayerSIN);

	// Like project #3 and 4, each Tic Tac Toe game has a unique ID
	// (a string), but unlike the Chess game, this returns a pointer to that
	// created instance. 
	// Once returned, you simply need to call the methods on this returned object. 
	// When the game is done, you call updateTicTacToeGame().
	cTicTacToeGameInstance createcTicTacToeGame( unsigned int Player_X_SIN, 
												  unsigned int Player_O_SIN,
	                                              std::string &errorString );

	
	// Once the game is over (or any time, really), you can call this to 
	//  update the state that's being held inside the Mug Book. 
	// The Unique GameID (from the getUniqueGameID() method) is used to tell 
	//	if this is a "valid" game. If it is, then it gets updated inside the mug book
	//  (by copying all the data).
	// If there *isn't* an ID that matches, then return false and some error text. 
	//
	// NOTE: Since you can't change the IDs, this prevents "cheating".
	//       What this also means is that you have to keep a matching 
	//       cTicTacToeGameInstance inside MugBook. When you update, you 
	//       copy everything *but* the unique IDs (which you don't have to)
	bool updateTicTacToeGame(cTicTacToeGameInstance theGame, std::string& errorString);

	// Returns the number of games that are currently being played.
	unsigned int getNumberOfActiveTicTacToeGames(void);

	// Returns the number of games that are finished
	unsigned int getNumberOfCompletedTicTacToeGames(void);

	// Gets the total number of games this player played (currnet and past)
	// "returned" vector can be zero if they haven't played any games.
	// Returns false if there's no user with that SIN.
	unsigned int getTicTacToeGamesPlayed( unsigned int playerSIN );
	
	unsigned int getTotalTicTacToeWins( unsigned int playerSIN );
	unsigned int getTotalTicTacToeLoses( unsigned int playerSIN );

	//BONUS ROUND
	

	bool getGamesPlayed(unsigned int playerSIN, std::vector< cTicTacToeGameInstance* >& vecGamesPlayed);


private:
	// You'll need to keep a container of cTicTacToeGameInstance instances here.
	// Use whatever you'd like to do this (any STL container).
	std::vector< cPerson* > m_vecUsers;
	std::vector<cTicTacToeGameInstance> m_vecGames;
};

#endif


