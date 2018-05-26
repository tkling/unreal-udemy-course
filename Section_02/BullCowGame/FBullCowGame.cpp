#pragma once
#include "FBullCowGame.h"
#include <unordered_set>
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetWordLength() const { return MyWord.length(); }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> wordLengthToMaxTries{ {3,5}, {4,6}, {5,8}, {6,10}, {7,14} };
	return wordLengthToMaxTries[MyWord.length()];
}

void FBullCowGame::Reset() {
	constexpr int MAX_TRIES = 5;
	const FString HIDDEN_WORD = "bevis";

	MyMaxTries = MAX_TRIES;
	MyWord = HIDDEN_WORD;
	MyCurrentTry = 1;
}

bool FBullCowGame::IsCorrectGuess(FString guess) const {
	return guess == MyWord;
}

int32 FBullCowGame::AdvanceCurrentTry() {
	MyCurrentTry += 1;
	return MyCurrentTry;
}

FBullCowCount FBullCowGame::ProcessGuess(FString guess) {
	FBullCowCount count = FBullCowCount();
	count.Bulls = CountBulls(guess);
	count.Cows = CountCows(guess);
	return count;
}

// a "bull" is a correct letter in the correct index
int32 FBullCowGame::CountBulls(FString guess) {
	int32 bulls = 0;
	for (int32 i = 0; i < MyWord.length(); i++) {
		if (MyWord[i] == guess[i]) {
			bulls++;
		}
	}
	return bulls;
}

// a "cow" is a correct letter in the wrong index
int32 FBullCowGame::CountCows(FString guess) {
	std::unordered_set<char> cows;
	for (int32 i = 0; i < MyWord.length(); i++) {
		bool notBull = (MyWord[i] != guess[i]);
		bool includedInMyWord = (MyWord.find(guess[i]) != FString::npos);
		bool notAlreadyCow = (cows.find(guess[i]) == cows.end());

		if (notBull && includedInMyWord && notAlreadyCow) {
			cows.insert(guess[i]);
		}
	}
	return cows.size();
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const {
	if (guess.length() != GetWordLength()) {
		return EGuessStatus::Wrong_Length;
	} else if (!IsIsogram(guess)) {
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowercase(guess)) {
		return EGuessStatus::Not_Lowercase;
	} else {
		return EGuessStatus::OK;
	}
}

// an isogram is a logological term for a word or phrase without a repeating letter.
bool FBullCowGame::IsIsogram(FString guess) const {
	TMap<char, bool> seen = {};
	for (auto letter: guess) {
		letter = tolower(letter);
		if (seen[letter] == true) { return false; }
		seen[letter] = true;
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString guess) const {
	for (auto guessLetter : guess) {
		if (guessLetter != tolower(guessLetter)) { return false; }
	}
	return true;
}
