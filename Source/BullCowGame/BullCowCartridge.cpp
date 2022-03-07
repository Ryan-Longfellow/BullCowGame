// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words);

    SetupGame();
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

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    // Prompt player for guess
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess.\nPress ENTER to continue..."));

    // Debug Line
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);
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

    // If all checks pass, subtract life
    --Lives;

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
    int32 Bulls, Cows;
    GetBullCows(Guess, Bulls, Cows);

    PrintLine(TEXT("You have %i Bulls and %i Cows."), Bulls, Cows);

    PrintLine(TEXT("Guess again, you have %i lives left."), Lives);
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

void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
{
    BullCount = 0;
    CowCount = 0;

    // for every index Guess is same as index Hidden, BullCount++
    // if not a Bull was it a cow? if yes, CowCount++

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex]) 
        {
            BullCount++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                CowCount++;
            }
        }
    }
}