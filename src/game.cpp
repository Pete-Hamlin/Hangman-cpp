//Standard includes
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

//Private includes
#include "game.h"

//Globals
#define FILELENGTH 1386     // IF words.txt IS EDITTED, THIS VALUE MUST BE UPDATED!!
#define GAMELENGTH 9        // Can be changed to 11 if the 2 elements in stage are uncommented

// The gallows - Looks scary but just draws the acutal hangman in the terminal interface
array<string, GAMELENGTH> stage = { "",
                                    "________\n",
                                    "|\n|\n|\n|\n|\n|_______\n",
                                    "_______\n|/\n|\n|\n|\n|\n|______\n",
                                    "_______\n|/    |\n|\n|\n|\n|\n|______\n",
                                    "_______\n|/    |\n|     O\n|\n|\n|\n|______\n",
                                    "_______\n|/    |\n|     O\n|     |\n|\n|\n|______\n",
                                    //"_______\n|/    |\n|     O\n|    /|\n|\n|\n|______\n",
                                    "_______\n|/    |\n|     O\n|    /|\\\n|\n|\n|______\n",
                                    //"_______\n|/    |\n|     O\n|    /|\\\n|    /\n|\n|_______\n",
                                    "_______\n|/    |\n|     O\n|    /|\\\n|    / \\\n|\n|_______\n"
                                  };

/* Game_shell */
//Constructor
Game_shell::Game_shell() {
  _attempts = 0;
}


void Game_shell::init() {
  int options = 3;
  int select;

  _attempts = 0;
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
  while (_attempts < GAMELENGTH - 1) {
    /* Main game logic */
    session.display();
    if (session.playerGuess() != true) {
      _attempts++;
      cout << endl << stage.at(_attempts) << endl << endl;
      //cout << _attempts;        //DEBUG
    }
    if (session.endGame() == true) {
      cout << "\nCongratulations - you won!!" << endl;
      session.showAns();
      return;
    }
  }
  cout << "\nGAME OVER!!!" << endl;
  session.showAns();
}

// Constructor
Game_data::Game_data(int choice) {
  _partialSol = "";
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
  _partialSol.append(_word.size(), '.');
  //cout << _partialSol;   //DEBUG
}

// Displays current solution, incorrect guess and how badly the man has been hanged so far
void Game_data::display() {
  cout << endl;
  cout << _partialSol << endl;
  cout << "\nIncorrect guesses: ";
  for (unsigned int i = 0; i < _incorrect.size(); i++) {
      cout << _incorrect.at(i) <<", ";
  }
  cout << endl;
  return;
}

// Fires when the guessing player loses the game
void Game_data::showAns() {
  cout << "\nThe correct answer was:\n" << _word << endl;
}

// Function run on each guessing player turn
bool Game_data::playerGuess() {
  cout << "\n\nPlease guess a letter (Only the first character provided will be read):" << endl;
  cin >> _guess;
  for (unsigned int i = 0; i < _incorrect.size(); i++) {
    if (_guess == _incorrect.at(i)) {
      cout << "\nYou've already guessed that letter!" << endl;
      return true;
    }
  }
  for (unsigned int i = 0; i < _partialSol.size(); i++) {
    if (_guess == _partialSol.at(i)) {
      cout << "\nYou've already guessed that letter!" << endl;
      return true;
    }
    else if (_guess == _word.at(i)) {
      _partialSol.at(i) = _guess;
      return true;
    }
  }
  _incorrect.push_back(_guess);
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
