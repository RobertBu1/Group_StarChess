// Link to Star Wars ASCII art:
// http://www.ascii-art.de/ascii/s/starwars.txt
// Luca DalCanto, Spencer Wood (this file)
// Robert, Andrew, Pierce, Bridger worked on art in .txt files (we're not adding comments to those because they're .txt files...)

// libraries:
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

// classes:
#include "game.h"

using namespace std;
using namespace std::chrono_literals; // s, ms, etc. (units of time for delays)

bool wantsToPlay = true;
bool variant = false;
int players = 1;

string output;
string input;
ifstream IntroText("intro.txt");
ifstream HomeText("homescreen.txt");
ifstream InstructText("instructions.txt");
ifstream CreditText("credits.txt");
ifstream SettingText("settings.txt");

void Clear() { // for clearing console
#if defined _WIN32
  system("cls");
  // clrscr(); // including header file : conio.h
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
  system("clear");
  // std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined(__APPLE__)
  system("clear");
#endif
}

void home() {
  while (getline(HomeText, output)) {
    cout << "\n" + output << flush;
  }
  while (true) {
    int choice;
    cin >> choice;

    if (choice == 1) {
      players = 1;
      break;
    }

    else if (choice == 2) {
      players = 2;
      variant = false;
      break;
    }

    else if (choice == 3) {
      players = 2;
      variant = true;
      break;
    }

    else if (choice == 4) {
      while (getline(InstructText, output)) {
        cout << "\n" + output << flush;
      }
    }

    else if (choice == 5) {
      while (getline(CreditText, output)) {
        cout << "\n" + output << flush;
      }
    }

    else if (choice == 6) {
      while (getline(SettingText, output)) {
        
        cout << "\n" + output << flush;
       
    }

    // more to come!
  }
}
}

void gameSummary() {}


int main() { // code starts here
  
  // intro
  Clear();
  while (getline(IntroText, output)) {
    cout << "\033[38;2;<220>;<123>;<26>m" << output + "\n" << flush;
    this_thread::sleep_for(150ms);
  }

  // wait, then clear screen
  getline(cin, input);
  Clear();

  while (true) {
    home(); // homescreen
    if (!wantsToPlay) {
      break; // end console app by breaking out of loop
    }

    //Game:
    // RegularGame MyGame = RegularGame(players);

    // MyGame.displayBoard();

    Piece testPiece("PAWN", false, true);

    string output = testPiece.display(1);
    cout << output + "\n";
    
    
    // if app doesn't end (player wants to play...):
    gameSummary();
  
  }
   // Define color codes
    string red = "\033[31m";
    string green = "\033[32m";
    string yellow = "\033[33m";
    string blue = "\033[34m";
    string reset = "\033[0m";

    // Display color options
    cout << "Choose a color:\n";
    cout << red << "1. Red\n" << reset;
    cout << green << "2. Green\n" << reset;
    cout << yellow << "3. Yellow\n" << reset;
    cout << blue << "4. Blue\n" << reset;

    
      }


