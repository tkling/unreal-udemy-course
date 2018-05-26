#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;

void printIntro();
void playGame();
void printGameSummary(bool);
bool askToPlayAgain();
bool performAndReportGameTurn();
FText getValidGuess();
FText getErrorString(EGuessStatus);

FBullCowGame BCGame;

int main() {
	printIntro();

	do { playGame(); } 
	while ( askToPlayAgain() );

	return 0;
}

void printIntro() {
	std::cout << "Welcome to Bulls and Cows, a game for fun words." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetWordLength() << " letter isogram I'm thinking of?\n";
}

void playGame() {
	BCGame.Reset();
	while (BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) {
		bool didSomeoneWin = performAndReportGameTurn();
		if (didSomeoneWin) { printGameSummary(true); return; }
		BCGame.AdvanceCurrentTry();
	}
	printGameSummary(false);
}

bool performAndReportGameTurn() {
	FText guess = getValidGuess();
	FBullCowCount count = BCGame.ProcessGuess(guess);
	std::cout << "Bulls: " << count.Bulls << " || Cows: " << count.Cows << std::endl;
	std::cout << std::endl;

	if (BCGame.IsCorrectGuess(guess)) {
		std::cout << "You guessed correctly!" << std::endl;
		return true;
	}
	return false;
}

bool askToPlayAgain() {
	std::cout << "Do you want to play again? (y/n) ";
	FText response = "";
	getline(std::cin, response);
	return (response[0] == 'y' || response[0] == 'Y');
}

FText getValidGuess() {
	int remainingTries = BCGame.GetMaxTries() - BCGame.GetCurrentTry();
	std::cout << "\nTry " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
	FText guess = "";
	getline(std::cin, guess);
	EGuessStatus guessStatus = BCGame.CheckGuessValidity(guess);

	if (guessStatus != EGuessStatus::OK) {
		std::cout << "Invalid guess! Problem: " << getErrorString(guessStatus) << ".\n" << std::endl;
		return getValidGuess();
	}
	return guess;
}

FText getErrorString(EGuessStatus guessStatus) {
	std::stringstream message;
	switch (guessStatus) {
	case EGuessStatus::Wrong_Length: 
		message << "Wrong length, enter a " << BCGame.GetWordLength() << " letter word"; break;
	case EGuessStatus::Not_Isogram: 
		message << "Not an isogram"; break;
	case EGuessStatus::Not_Lowercase:
		message << "Not lowercase"; break;
	default: message << "No error!";
	}
	return message.str();
}

void printGameSummary(bool didWin) {
	if (didWin) {
		std::cout << "Hooray, a winner!" << std::endl;
	} else {
		std::cout << "Better luck next time :(" << std::endl;
	}
}
