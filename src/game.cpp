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
  _quit = false;
  _p1._score = 0;
  _p1._name = "Player 1";
  _p1._guess = true;
  _p2._score = 0;
  _p2._name = "Player 2";
  _guess = _p1;
  _word = _p2;
}


void Game_shell::init() {
  int options = 3;
  int select;
  // Add additional options here (Exit should always be the last option)
  cout <<   "\n!!HANGMAN!!\n\nSelect an option:" <<
            "\n1.Single Player" <<
            "\n2.Multiplayer" <<
            "\n3.Exit" << endl;
  cin >> select;
  option(select);
  //Makes sure play input is a valid option
  if (select < 1 || select > options) {
    cout << "\nPlease select a valid input option!" << endl;
    init();
  }
  else if (select == options) {
    cout << "Exiting..." << endl;
    _quit = true;
    return;
  }
}

void Game_shell::run() {
  // Main game element - ideally refactored into a seperate function at a later date
  _attempts = 0;
  Game_data session;
  if (!_multiplayer) {
      session.genWord();
  }
  else {
    session.addWord(_guess, _word);
  }
  while (_attempts < GAMELENGTH - 1) {
    /* Main game logic */
    session.display();
    if (!session.playerGuess()) {
      _attempts++;
      cout << endl << stage.at(_attempts) << endl << endl;
      //cout << _attempts;        //DEBUG
    }
    if (session.endGame()) {
      cout << "\nCongratulations " << _guess._name << "- You won!!" << endl;
      _guess._score ++;
      break;
    }
  }
  if (!session.endGame()) {
    cout << "\nGAME OVER " << _guess._name << "- You lose!!!" << endl;
    _word._score ++;
  }
  session.showAns();
  // Tidy up and prepare for next game
  if (_multiplayer) {
    playerSwitch();
  }
  playerScore();
}

void Game_shell::option(int choice) {
  // SWitch statement allows adding additional options later on
  switch(choice) {
    case 1 :
      cout << "\nSelected CPU opponent!" << endl;
      _multiplayer = false;  _word._score = 0;

      _p2._active = false;
      _word._active = false;
      break;
    case 2 :
      cout << "\nSelected human opponent!" << endl;
      _multiplayer = true;
      _p2._active = true;
      break;
    case 3:
      break;
    default :
      throw "\nUnrecognised input... Congrats, you broke it.\n";
  }
}

//Switch the active player
void Game_shell::playerSwitch() {
  if (_p1._guess == true) {
//Update scores
    _p1._score += _guess._score;
    _p2._score += _word._score;
    //Sets up for next iteration
    _p1._guess = false;
    _p2._guess = true;
    _guess = _p1;
    _word = _p2;
  }
  else {
    _p2._score += _guess._score;
    _p1._score += _word._score;
    //Sets up for next iteration
    _p2._guess = false;
    _p1._guess = true;
    _guess = _p2;
    _word = _p1;
  }
  _guess._score = 0;
  _word._score = 0;
}

void Game_shell::playerScore() {
  //For single player games, payer gains a point for guessing correctly, loses one for incorrectly guessing
  cout << endl << _p1._name << ": " << _p1._score << endl;
  if (_p2._active) {
    cout << endl << _p2._name << ": " << _p2._score << endl;
  }
}


/* Game_data */

// Constructor
Game_data::Game_data() {
  _partialSol = "";
}

// Generates the word to guess, either via user input or random selecting a word from words
void Game_data::genWord() {
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
  _partialSol.append(_word.size(), '.');
  //cout << _partialSol;   //DEBUG
}

void Game_data::addWord(Player guess, Player word) {
  HideStdinKeystrokes();
  cout << "\n"  << word._name << " - Please provide a word for " << guess._name << " to guess:";
  cin >> _word;
  ShowStdinKeystrokes();
    //cout << word;     //DEBUG
  _partialSol.append(_word.size(), '.');
  //cout << _partialSol;   //DEBUG
}

// Displays current solution, incorrect guess and how badly the man has been hanged so far
void Game_data::display() {
  cout << endl;
  cout << _partialSol << endl;
  cout << "\nIncorrect guesses: " << _incorrect.size() << endl;
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
  bool ans = false;
  for (unsigned int i = 0; i < _incorrect.size(); i++) {
    if (_guess == _incorrect.at(i)) {
      cout << "\nYou've already guessed that letter!" << endl;
    }
  }
  for (unsigned int i = 0; i < _partialSol.size(); i++) {
    if (_guess == _partialSol.at(i)) {
      cout << "\nYou've already guessed that letter!" << endl;
      ans = true;
    }
    else if (_guess == _word.at(i)) {
      _partialSol.at(i) = _guess;
      ans = true;
    }
  }
  if (ans != true) {
    _incorrect.push_back(_guess);
  }
  return ans;
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
