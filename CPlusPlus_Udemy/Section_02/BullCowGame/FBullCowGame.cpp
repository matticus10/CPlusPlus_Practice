#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "ant";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

bool FBullCowGame::CheckGuessValidity(FString)
{
	return false;
}

// recieves a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// increment the turn number
	MyCurrentTry++;

	// setup a return value
	FBullCowCount BullCowCount;

	// loops through all letters in the guess
	int32 HiddentWordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddentWordLength; MHWChar++) 
	{
		char GuessLetter = Guess[MHWChar];
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < HiddentWordLength; GChar++) 
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
	return BullCowCount;
}
