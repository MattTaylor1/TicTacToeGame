#ifndef _cTicTacToeGameInstance_HG_
#define _cTicTacToeGameInstance_HG_

#include <string>
#include <random>
#include <set>

// Warning C26812 : Prefer 'enum class' over 'enum' (Enum.3)
#pragma warning( disable : 26812 )


// This represents a current or past game

// The board is laid out like this, 
//  where the numbers are (row, column)
// 
//      |     |     
//  0,0 | 0,1 | 0,2
//      |     |     
// -----+-----+-----
//      |     |     
//  1,0 | 1,1 | 1,2
//      |     |     
// -----+-----+-----
//      |     |     
//  2,0 | 2,1 | 2,2
//      |     |     
//



class cTicTacToeGameInstance
{
public:

	// Note that since these are inside cTicTacToeGameInstance, 
	//	they have to use this as a scope, so:
	// 	   
	//  - cTicTacToeGameInstance::eSquareState and
	//  - cTicTacToeGameInstance::sSquare
	// 
	// 	(instead of just eSquareState and sSquare)
	// 
	// If they are *inside* of the cTicTacToeGameInstance, you don't 
	//  have to do this, since the cTicTacToeGameInstance "knows" about 
	//  the enums, but *outside* like in Mug Book or the main (or wherever)
	//  you will have to use "cTicTacToeGameInstance::" as well.

	enum eSquareState
	{
		IS_EMPTY,
		X_PLAYER,
		O_PLAYER,
		GAME_IS_OVER
	};

	struct sSquare
	{
		// See above image for details
		unsigned int row;		// 0 to 2
		unsigned int column;	// 0 to 2
		eSquareState state;
	};

	// NOTE: The default constructor is private, so can't be called
	// (see below for more details)
	cTicTacToeGameInstance(unsigned int player_X, unsigned int player_O);
	~cTicTacToeGameInstance();

	// This string is generated when created.
	// While it's not *guaranteed* to be unique, it's very unlikely there will be duplicates
	std::string getUniqueGameID(void);
	
	unsigned int getPlayer_X_SIN(void);
	unsigned int getPlayer_O_SIN(void);


	// Returns the SIN of the winner. 
	// If a draw, returns 0
	// Note: If a game is running then this is meaningless. 
	// (Note that you can get if the player was "X" or "O" from
	//  calling this and the getPlayer_SIN() methods.)
	unsigned int getWinnerSIN(void);

	// Returns true if it's an actively running game.
	bool isGameCurrentlyRunning(void);

	// This ends the game and sets the winner. 
	// Once this happens, no more moves can happen
	// 	   
	// If it's a tie or draw, then pass eSquareState::GAME_IS_OVER 
	//
	bool endGameAndDeclareWinner(eSquareState winner );
	bool getCurrentBoardState(std::vector< std::vector<sSquare> >& theBoard);
	bool updateGameInList(cTicTacToeGameInstance updatedGame);

	// This locates a piece/mark on the board. 
	// - row and column should be between 0 and 2
	// - player is an eSquareState but here is only using
	//     X_PLAYER or O_PLAYER values.
	// - errorString returns some "human readable" text if 
	//    there was an error (i.e. something to print to the screen)
	// 
	// Returns true if the piece/mark was successfully placed on the board.
	// 
	// Returns false if:
	// - The row or column is out of range. 
	// - There is a piece/mark already at that location
	// - player is not X_PLAYER or O_PLAYER
	// - Someone already won the game (so the game is over)
	// 
	// Note: If the 
	bool placePiece(unsigned int row, unsigned int column, 
					eSquareState player, std::string& errorString);


	// You can decide who starts (X or O). This can even be random if you'd like.
	// This then needs to alternate until the game is over. 
	// Once the game is over, GAME_IS_OVER is returned. 
	eSquareState whosTurnIsIt(void);

	bool printBoard(void);

private:

	// TODO: 
	// 
	//		Use any container or data structure you'd like here
	//		to hold the data for the board. 
	// 

	// Note this default constructor is private, so can't be called. 
	// This is so you can't start a game without having players defined.
	// And, you can't change the players mid-game.
	// 
	// You can still copy or assign this, since that happens through the 
	// copy and assignment constructor
	// 
	// operator=();					for GameStateA = GameStateB
	// cGameState(cGameState &A);	for GameStateA( GameStateB )
	// 	   
	// Both of these are used in the STL for moving stuff around, 
	//  so you can still call push_back(), insert(), etc.
	// (None of those actually use the default constructor)
	//
	cTicTacToeGameInstance();
	
	// These are private so they can't be written to
	// (They can only be set with the constructor)
	unsigned int m_Player_X_SIN;
	unsigned int m_Player_O_SIN;

	unsigned int m_winner_SIN;
	bool m_bGameIsCurrentlyRunning;

	

	std::vector <std::vector<sSquare>> theBoard;

	// This is a ten (10) digit alphanumeric string to identify THIS game
	// You can use this like the SIN (or primary key) to find this.
	// It's in the form letter, number, letter, number, etc.
	//  So: A1B2C3D4E5 or whatever
	// With this many digits, there's 1,188,137,600,000 unique values
	// This is set, just once, by the constructor.
	std::string m_UniqueGameID;

	// This is called exactly once, in the constructor
	// This method uses the variables below to make sure
	//	there's no duplicate (which is shockingly easy because
	//	the C+11 random, while "better" is still hot garbage.)
	std::string m_GenerateUniqueGameID(void);
	// These variables are static. More details in the cpp file.
	static std::ranlux48* m_pRandEngine;	// = NULL 
	static std::set<std::string> m_setUsedIDs;
	static unsigned int m_duplicateIDsFound;
};

#endif  //cTicTacToeGameInstance
