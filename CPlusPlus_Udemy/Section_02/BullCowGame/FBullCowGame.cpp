#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return static_cast<int32>(MyHiddenWord.length()); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "posted"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lower case
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// recieves a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loops through all letters in the hidden word
	int32 WordLength = GetHiddenWordLength(); // assumiong same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				if (MHWChar == GChar)	{ // if they're in the same place
					BullCowCount.Bulls++; // increment bulls
				}
				else 
				{
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	// setup our map
	TMap<char, bool> LetterSeen;

	// loop through each letter
	for (auto Letter : Word)
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) // if letter is already mapped
		{
			return false; // not an isogram
		}
		else
		{
			LetterSeen[Letter] = true; // map letter
		}
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) // if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}

