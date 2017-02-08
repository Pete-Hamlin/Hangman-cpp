//Standard includes
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

//Private includes
#include "game.h"

//Globals
#define FILELENGTH 1386     // IF words.txt IS EDITTED, THIS VALUE MUST BE UPDATED!!
#define GAMELENGTH 8

/* Game_shell */
//Constructor
Game_shell::Game_shell() {
  _attempts = 0;
}


void Game_shell::init() {
  int options = 3;
  int select;
  // Add additional options here (Exit should always be the last option)
  cout <<   "\n!!HANGMAN!!\n\nSelect an option:" <<
            "\n1.Computer Opponent" <<
            "\n2.Human Opponent" <<
            "\n3.Exit" << endl;
  cin >> select;
  //Makes sure play input is a valid option
  if (select < 1 || select > options) {
    cout << "\nPlease select a valid input option!" << endl;
    init();
  }
  else if (select == options) {
    cout << "Exiting..." << endl;
    return;
  }

  // Main game element - ideally refactored into a seperate function at a later date
  Game_data session(select);
  session.genWord();
  while (_attempts < GAMELENGTH) {
    /* Main game logic */
    session.display();
    if (session.playerGuess() != true) {
      _attempts++;
      //cout << _attempts;        //DEBUG
    }
    if (session.endGame() == true) {
      cout << "Congratulations - you won!!" << endl;
      session.showAns();
      return;
    }
  }
  cout << "GAME OVER!!!" << endl;
  session.showAns();
}

// Constructor
Game_data::Game_data(int choice) {
  // SWitch statement allows adding additional options later on
  switch(choice) {
    case 1 :
      cout << "\nSelected CPU opponent!" << endl;
      multiplayer = false;
      break;
    case 2 :
      cout << "\nSelected human opponent!" << endl;
      multiplayer = true;
      break;
    default :
      throw "\nUnrecognised input... Congrats, you broke it.";
  }
}

// Generates the word to guess, either via user input or random selecting a word from words
void Game_data::genWord() {
  if (multiplayer) {
    cout << "\nPlayer 1 - Please provide a word for player 2 to guess:";
    cin >> _word;
    //cout << word;     //DEBUG
  }
  else {
    int ranNum = rand() % FILELENGTH;
    int lineNum = 0;
    string line;

    ifstream wordList("words.txt");
    while(getline(wordList, line)) {
      ++lineNum;
      if (lineNum == ranNum) {
        _word = line;
        //cout << line;   //DEBUG
      }
    }
  }
}

// Displays current solution, incorrect guess and how badly the man has been hanged so far
void Game_data::display() {
  return;
}

// Fires when the guessing player loses the game
void Game_data::showAns() {
  cout << "\nThe correct answer was:\n" << _word << endl;
}

// Function run on each guessing player turn
bool Game_data::playerGuess() {
  cout << "Please guess a letter (Only the first character provided will be read):" << endl;
  cin >> _guess;
  return false;
}

// Check if whole word has been guessed - otherwise continue
bool Game_data::endGame() {
  if (_partialSol == _word) {
    return true;
  }
  else {
    return false;
  }
}
