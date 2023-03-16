#include <iostream>
#include <stdlib.h>

using namespace std;

class Pawn{
bool bottom;
bool startingPosition;

Pawn () {}

  void display () {
    if (bottom) {
      cout << " ";
    } else {
    cout << " ";
      }
  }

  void move () { //write logic for how a pawn can move, figure out how to choose a piece
        if (startingPosition) {
        if (bottom) {
          
        } else {
          
        }
          } else {
          if (bottom) {
          
        } else {
          
        }
          }
    }

};

class King{
bool bottom;

King () {}

void display () {
    if (bottom) {
      cout << " ";
    } else {
    cout << " ";
      }
  }

void move () {
  if (bottom) {
    
  } else {
    
  }
}

};

//Do after Pawn and King are figured out
// class Knight{};
// class Bishop{};
// class Rook{};
// class Queen{};

//----------------------------------------------

class RegularGame{
public:
  RegularGame(int playerCount){
    players = playerCount;
    if((rand() % 1) == 1 || players == 1){ //white is bottom
      string tempArray[64] = {"br", "bn", "bb", "bq", "bk", "bb", "bn", "br"
                              "bp", "bp", "bp", "bp", "bp", "bp", "bp", "bp", 
                              "no", "no", "no", "no", "no", "no", "no", "no",
                              "no", "no", "no", "no", "no", "no", "no", "no",
                              "no", "no", "no", "no", "no", "no", "no", "no",
                              "no", "no", "no", "no", "no", "no", "no", "no",
                              "wp", "wp", "wp", "wp", "wp", "wp", "wp", "wp", 
                              "wr", "wn", "wb", "wq", "wk", "bn", "wn", "wr"};
      storeMemory(tempArray);
    }
    else {  //black is bottom
      string tempArray[64] = {"wr", "wn", "wb", "wq", "wk", "bn", "wn", "wr",
                              "wp", "wp", "wp", "wp", "wp", "wp", "wp", "wp",
                              "no", "no", "no", "no", "no", "no", "no", "no",
                              "no", "no", "no", "no", "no", "no", "no", "no",
                              "no", "no", "no", "no", "no", "no", "no", "no",
                              "no", "no", "no", "no", "no", "no", "no", "no",
                              "bp", "bp", "bp", "bp", "bp", "bp", "bp", "bp", 
                              "br", "bn", "bb", "bq", "bk", "bb", "bn", "br", };
      storeMemory(tempArray);
    }
  }

private:
  int players;
  string grid[64];

  void storeMemory(string tempGrid[64]){
    for(int i = 0; i < 64; i++){
      grid[i] = tempGrid[i];
    }
  }
};

//-----------------------------------------------

class VariantGame{
  //do this later, start with regular chess above ^^
};
