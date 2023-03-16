//Link to Star Wars ASCII art:
//http://www.ascii-art.de/ascii/s/starwars.txt

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

void Clear() { //for clearing console
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


void home(){
  while (getline(HomeText, output)) {
    cout << "\n" + output << flush;
    
  }
  while(true){
    int choice;
    cin >> choice;
    
    if(choice == 1){
      players = 1;
      RegularGame MyGame = RegularGame(players);
      break;
    }

    else if(choice == 2){
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

    else if(choice == 6){
      cout << flush;
    }

    //more to come!
  }
  

}

void gameSummary(){
  
}



int main() { //code starts here

  // intro
  Clear();
  while (getline(IntroText, output)) {
    cout << output + "\n" << flush;
    this_thread::sleep_for(150ms);
  }

  // wait, then clear screen
  getline(cin, input);
  Clear();
  
  while(true){
    home(); // homescreen
    if(!wantsToPlay){
      break; //end console app by breaking out of loop
    }
    //if app doesn't end (player wants to play...):
    gameSummary();
  }
}
