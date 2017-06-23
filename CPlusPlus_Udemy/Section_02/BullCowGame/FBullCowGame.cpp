#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
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
FBullCowCount FBullCowGame::SubmitGuess(FString)
{
	// increment the turn number
	MyCurrentTry++;

	// setup a return value
	FBullCowCount BullCowCount;

	// loops through all letters in the guess
	int32 HiddentWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddentWordLength; i++) {
		// compare letters against the hidden word
		for (int32 j = 0; j < HiddentWordLength; j++) {
			// if they match
				// increment bulls if they're in the same place
				// increment cows if not
		}
	}
	return BullCowCount;
}
