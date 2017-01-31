#include <iostream>
#include <fstream>
#include <string>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

//Globals
#define FILELENGTH 1386     // Defines number of lines in wordlist file which will be checked against
#define GAMELENGTH 8

// Main game class
class Game {
  public:
    Game(int choice);
    void genWord();
    void display();
    void playerGuess();
    void playerTurn();
    //void reset();
  private:
    int turn;
    string word;
    char guess;
    string partialSol;
    bool multiplayer;
};

Game::Game(int choice) {
  turn = 0;
  if (choice == 1) {
    multiplayer = false;
  }
  else {
    multiplayer = true;
  }
}

// Generates the word to guess, either via user input or random selecting a word from words
void Game::genWord() {
  if (multiplayer) {
    cout << "\nPlayer 1 - Please provide a word for player 2 to guess:";
    cin >> word;
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
        word = line;
        //cout << line;   //DEBUG
      }
    }
  }
}

int main() {
  int select;

  srand (time(NULL));
  cout << "\n!!HANGMAN!!\n\nSelect an option:\n1.Computer Opponent\n2.Human Opponent\n3.Exit" << endl;
  cin >> select;
  Game game(select);
  game.genWord();
  return 0;
}
