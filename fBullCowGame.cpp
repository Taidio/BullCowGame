#pragma once
#include "fBullCowGame.h"
#include<iostream>
#include <map>
#define TMap std::map

/* This file contains functions about fBullCowGame class */

// reset a game and some variables
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "plane";
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;

	MyCurrentTry = 1;
	return;
}

// receiving a valid guess, increments, returns numer of bulls and cows
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	int32 Length = MyHiddenWord.length();
	FBullCowCount BullCowCount;

		//loop throught letter, compare them to hidden word
		//increase Bulls if right letter in right order, or Cows if right letter in wrong order
		for (int32 MHWChar = 0; MHWChar < Length; MHWChar++) 
		{
			for (int32 GChar = 0; GChar < Length; GChar++) 
			{
				if (Guess[GChar] == MyHiddenWord[MHWChar])
				{
					if (MHWChar == GChar)
					{
						BullCowCount.Bulls++;
					}
					else
					{
						BullCowCount.Cows++;
					}
				}

			}
		}

		if (BullCowCount.Bulls == Length)
		{
			bGameIsWon = true;
		}
		else
		{
			bGameIsWon = false;
		}

	return BullCowCount;
}

// constructor
FBullCowGame::FBullCowGame()
{
	Reset();
} 

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,15} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)
{
	if (Guess.length() != GetHiddenWordLength()) // if the guess is wrong length
	{	
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsLowercase(Guess)) // if the guess is not lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (!IsIsogram(Guess)) // if the guess is NOT isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else
	{
		return EGuessStatus::OK;
	}		
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) 
	{
		return true;
	}

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) //looping through all letters
	{
		Letter = tolower(Letter); //making it lowercase
		if (LetterSeen[Letter]) //if the letter is in the map, it is not isogram
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true; //adding letter to the map
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
