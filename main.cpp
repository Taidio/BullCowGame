#pragma once
#include <iostream>
#include <string>
#include "fBullCowGame.h"


using namespace std;
using int32 = int;
using FText = string;

//function prototypes
void PrintIntro();
string GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();
void GuessesLeft();

FBullCowGame BCGame; // initiate new game instance

int main()
{
	
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
	}
	while(AskToPlayAgain());

	return 0;
}

//plays a game until finish
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	// loop asking for guesse WHILE game not won
	// and while there are still tries left
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries )
	{
		FText Guess = GetValidGuess();

		// sumbit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		cout << "Bulls = " << BullCowCount.Bulls << ". Cows = " << BullCowCount.Cows; //numer of bulls and cows
		GuessesLeft(); //how many guesses user has left
	}
	return;
} 

void PrintIntro()
{
	//Introduce to the game

	cout << "Welcome to Bulls and Cows" << endl;
	cout << "        {     }" << "      " << " _____" << endl;
	cout << "        ( o o )" << "      " << "| o o |" << endl;
	cout << "        (  b  )" << "      " << "|  c  |" << endl;
	cout << "\\________\\ _ /"<< "      " << "  \\ _ /_______/" << endl;
	cout << "|        |" << "      " << "          |       |" << endl;
	cout << "| BULL   |" << "      " << "          |  COW  |" << endl;
	cout << "|________|" << "      " << "          |_______|" << endl;
	cout << "^        ^" << "      " << "          ^       ^" << endl << endl;
	cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?" << endl << endl;
}

bool AskToPlayAgain()
{
	cout << "Do you want to play again?(y/n)";
	string Response = "";
	getline(cin, Response);
	if (Response[0] == 'y' || Response[0] == 'Y')
		return true;
	else
		return false;
}

string GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	// get a guess from a player
	do{
		int32 CurrentTry = BCGame.GetCurrentTry();
		cout << "Try " << CurrentTry << " of " <<BCGame.GetMaxTries() << ". Please enter your guess: ";
		
		getline(cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess); 
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			cout << "Please enter a word without repeating letter!" <<endl ;
			break;
		case EGuessStatus::Wrong_Length:
			cout << "Please enter " << BCGame.GetHiddenWordLength() << " letter word!" <<endl ;
			break;
		case EGuessStatus::Not_Lowercase:
			cout << "Please enter lowercase word!" << endl;
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until no error
	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		cout << "You won!" << endl;
	}
	else
	{
		cout << "You lost! Good luck next time." << endl;
	}
}

void GuessesLeft() //commenting guesses left
{
	if (!BCGame.IsGameWon()) // if the game is not won
	{
		int32 GuessesLeft = BCGame.GetMaxTries() - BCGame.GetCurrentTry() + 1; // number of guesses left
		if (GuessesLeft != 1) 
		{
			cout << ". You have " << GuessesLeft << " guesses left!" << endl; // for multiple guesses it is plural "guesses"
		}
		else
		{
			cout << ". You have " << GuessesLeft << " guess left!" << endl; // for one guess it is singural "guess"
		}
	}
	else
	{
		cout << endl; // if the game is won, you do not need information about guesses left so just do one new line
	}
	return;
}