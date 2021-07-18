#include "cMugBook.h"
#include "cPerson.h"
#include "cTicTacToeGameInstance.h"
#include "sDateYMD.h"

#include <iostream>
#include <vector>
#include <string>


int main() {

	cMugBook mb;

	cPerson person1;
	cPerson person2;
	cPerson person3;
	cPerson person4;
	cPerson person5;
	cPerson person6;

	person1.SIN = 123;
	person2.SIN = 234;
	person3.SIN = 456;
	person4.SIN = 789;
	person5.SIN = 101;
	person6.SIN = 111;

	person1.first= "Bobby";
	person2.first = "Bobbert";
	person3.first = "Boberto";
	person4.first = "Robert";
	person5.first = "Robby";
	person6.first = "Rabbi Rob";

	mb.addUser(&person1);
	mb.addUser(&person2);
	mb.addUser(&person3);
	mb.addUser(&person4);
	mb.addUser(&person5);
	mb.addUser(&person6);

	std::string error = "";

	unsigned int sin1 = mb.findANonPlayingTicTacToeUser();
	unsigned int sin2 = mb.findAvailableTicTacToeOpponent(sin1);
	 
	cTicTacToeGameInstance theGame = mb.createcTicTacToeGame(sin1, sin2, error);
	unsigned int sin3 = mb.findANonPlayingTicTacToeUser();
	unsigned int sin4 = mb.findAvailableTicTacToeOpponent(sin3);

	cTicTacToeGameInstance theGame2 = mb.createcTicTacToeGame(sin3, sin4, error);

	theGame.placePiece(0, 0, theGame.whosTurnIsIt(), error);
	theGame.placePiece(0, 0, theGame.whosTurnIsIt(), error);
	theGame.placePiece(0, 0, theGame.whosTurnIsIt(), error);

	std::vector <std::vector<cTicTacToeGameInstance::sSquare>> theBoard;

	
	theGame2.getCurrentBoardState(theBoard);


	

	return 0;
}