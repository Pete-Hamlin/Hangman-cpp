# HANGMAN #

A simple terminal based Hangman game written in C++. Built on Linux. Mostly just an experimental proof of concepot, but works pretty nicely as a time killer for the bored.

## Design ##

Game is built around 2 classes which control the whole process:

* **Game_shell** - Houses each game instance. Think of it as the overhead container that governs the overall rules of the game.

* **Game_data** - Contains all the individual game logic and the necessary data to run it

The game supports playing against a human, or a CPU opponent. When playing against a CPU opponent, the game will select a word at random from the list of 1386 common English words stored in words.txt. This list can be expanded upon, however the main program will need recompiling (see Customization for details).

Playing against a human allows the other player to input a word for you to try and guess. One caveat is, the program will not spellcheck a human input word, so facerolling the keyboard is an effective way to ruin someone's day.

## Customization ##

There are 2 main 'configurable' elements, both in game.cpp. These are:

* **GAMELENGTH** - Determines number of guesses you are allowed before you lose the game, currently set to 9. Can be easily expanded to 11, by uncommenting lines 25 & 27. Larger numbers will still work, but will probably break the graphic of the gallows.

* **FILELENGTH** - You'll likely want to keep this value the same size as the number of lines in the words.txt file (you'll only really want to change it if you add extra words to the list). Making it smaller will mean the end words won't be randomly selectable. Making it higher than the file length could cause very strange behaviour, and probably crash the program.

Goes without saying, but any changes to the source code will require recompilation to take effect.

## Installation  ##

The game 'as is' can be run directly in the terminal using the binary under `bin/hangman`.

To rebuild from source, your system must be set up to compile C++11. Simply cd into `src` and hit `make`.

## Future Work ##

* Score system (vs CPU & vs Human)
* Difficulty levels (Easy, Medium, Hard)
* Dynamic FILELENGTH variable (self-updating)
* Options menu
