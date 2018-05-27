#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetWordLength() const;
	bool IsCorrectGuess(FString) const;
	bool IsLowercase(FString) const;
	EGuessStatus CheckGuessValidity(FString) const;
	void Reset();
	int32 AdvanceCurrentTry();
	FBullCowCount ProcessGuess(FString);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyWord;
	bool IsIsogram(FString) const;
	int32 CountBulls(FString);
	int32 CountCows(FString);
};
