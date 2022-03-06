// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    // PrintLine(TEXT("The HiddenWord is: %s.\nIt is %i characters long."), *HiddenWord, HiddenWord.Len()); // Debug Line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    // if game is over then do ClearScreen() and SetupGame()
    // else check PlayerGuess
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        // Check if Input from user matches HiddenWord
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("You win!"));
            EndGame();
        }
        else
        {
            // Check if right number of characters
            if (Input.Len() != HiddenWord.Len())
            {
                PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());
                // Prompt to GuessAgain
            }

            PrintLine(TEXT("You lose!"));
            EndGame();
        }
    }

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

    
}

void UBullCowCartridge::SetupGame()
{
    // Welcome the player
    PrintLine(TEXT("Welcome to Bull Cows!"));

    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    // Prompt player for guess
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess.\nPress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("Press ENTER to continue."));

}