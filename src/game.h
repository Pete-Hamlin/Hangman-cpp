/* Main game class - this will start, manage and end the game instance. Data required for the game is stored in the Game_data class. */
class Game_shell {

  public:
    Game_shell();
    void init();
  private:
    int _attempts;
};


/* Stores all the variables and performs all the logic required for the game. Each instance will be scrapped after each round, allowing for a score system to be eventually implemented */
class Game_data {
  public:
    Game_data(int choice);
    void genWord();
    void display();
    void showAns();
    bool playerGuess();
    bool endGame();
  private:
    char _guess;
    string _partialSol;
    string _word;

    bool multiplayer;
};
