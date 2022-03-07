// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    // Debug Lines
    // PrintLine(TEXT("Number of possible words: %i"), Words.Num());
    // PrintLine(TEXT("Number of valid words: %i"), GetValidWords(Words).Num());
    PrintLine(TEXT("The HiddenWord is: %s.\nIt is %i characters long."), *HiddenWord, HiddenWord.Len());
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
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
        ProcessGuess(PlayerInput);
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

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    // Check if right number of characters
    if (Guess.Len() != HiddenWord.Len())
    {
        // Prompt to guess again
        PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());
        return;
    }

    // Check if Input from user matches HiddenWord
    if (Guess == HiddenWord)
    {
        ClearScreen();
        PrintLine(TEXT("You win!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);

        EndGame();
        return;
    }

    // Check if isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again,"));
        return;
    }

    // If all checks pass, subtract life and show remaining lives
    PrintLine(TEXT("Sorry, try guessing again!\nYou have %i lives left."), --Lives);

    // Check if no lives are left
    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You ran out of lives. You lose!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);

        EndGame();
        return;
    }

    // Show player Bulls and Cows
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison]) return false;
        }
    }
    
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}