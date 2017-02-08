//Standard includes
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

//Private includes
#include "game.h"

//Globals


int main() {
  char restart;
  srand (time(NULL));
  Game_shell game;

  for (;;) {
    game.init();
    // After game ends, offer chance to replay
    cout << "Play again? (y/N)";
    cin >> restart;
    if(restart != 'y') {
      break;
    }
  }
  //Clean up - re-enable echo
  return 0;
}
