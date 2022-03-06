// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    // Welcome the player
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the 4 letter word")); // Magic number remove!!
    PrintLine(TEXT("Press enter to continue..."));

    SetupGame();

    // Prompt player for guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    // Checking PlayerGuess

    // Check if isogram
    // Prompt to GuessAgain
    

    // Subtract life
    // Show lives left
    // Check if lives > 0
    // If yes GuessAgain
    // If no show GameOver and HiddenWord
    // Press Enter to PlayAgain
    // Check User Input
    // PlayAgain or Quit

    // Check if Input from user matches HiddenWord
    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You win!"));
    }
    else
    {
        // Check if right number of characters
        if (Input.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("The Hidden Word is 4 characters long, try again!")); // Magic number remove!!
            // Prompt to GuessAgain
        }

        PrintLine(TEXT("You lose!"));
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("cake");
    Lives = 4;
}