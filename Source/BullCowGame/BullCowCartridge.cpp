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
    // else check ProcessGuess
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
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
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess.\nPress ENTER to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("Press ENTER to continue."));

}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    // Check if right number of characters
    if (Guess.Len() != HiddenWord.Len())
    {
        // Prompt to guess again
        PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());
        return;
    }

    // // Check if isogram
    // if (!IsIsogram)
    // {
    //     PrintLine(TEXT("No repeating letters, guess again,"));
    // }

    // Check if Input from user matches HiddenWord
    if (Guess == HiddenWord)
    {
        ClearScreen();
        PrintLine(TEXT("You win!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);

        EndGame();
        return;
    }

    // If all checks pass, subtract life and show remaining lives
    PrintLine(TEXT("Sorry, try guessing again!\nYou have %i lives left."), --Lives);

    // Check if lives are left
    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You ran out of lives. You lose!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);

        EndGame();
        return;
    }


    // Show player Bulls and Cows
    PrintLine(TEXT("Guess again, you have %i lives left."), Lives);
    // If no show GameOver and HiddenWord
    // Check User Input
    // PlayAgain or Quit
}