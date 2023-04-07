// Luca DalCanto, Spencer Wood
//  libraries:
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <thread>

using namespace std;

ifstream WhitePawnText("white_pawn.txt");
ifstream BlackPawnText("pawn_black.txt");

class Piece {
public:
  enum pieceType { BLANK, PAWN, KING, QUEEN, KNIGHT, BISHOP, ROOK };
  string output;
  bool wsquare;
  bool startingPosition;
  bool rebels;
  pieceType piece;
  int currentLine = 0;
  string file;

  Piece(string myPiece = "PAWN", bool onWhite = true, bool isRebel = true) {
    wsquare = onWhite;
    rebels = isRebel;
    if (myPiece == "BLANK"){
      
    }
    if (myPiece == "PAWN") {
      piece = PAWN;
      if (rebels == true) {
        file = "pawn_white.txt";
      } else {
       file = "pawn_black.txt"; 
      }
    } else if (myPiece == "KING") {
      piece = KING;
    } else if (myPiece == "QUEEN") {
      piece = QUEEN;
    } else if (myPiece == "KNIGHT") {
      piece = KNIGHT;
    } else if (myPiece == "BISHOP") {
      piece = BISHOP;
    } else if (myPiece == "ROOK") {
      piece = ROOK;
    }
  }

  string display(int lineNum) {
    if (!rebels) {
      BlackPawnText.open("file");
    if (wsquare) {
      while (!BlackPawnText.eof()) { //Gets the line of a Black Pawn on a white square
        currentLine++;
        getline(BlackPawnText, output);
        if (currentLine == lineNum) {
          break;
        }
      } 
      // turn "#" into " "
      return output;
      cout << " ";
     } 
    
    else {
      while (!BlackPawnText.eof()) { //Gets the line of Black Pawn on a black square
        currentLine++;
        getline(BlackPawnText, output);
        if (currentLine == lineNum) {
          break;
        }
      }
      return output;
    }
    BlackPawnText.close();
    } else {
      //WhitePawnText.open("file");
    if (wsquare) { //Gets the line of white pawn on a white square
      while (!WhitePawnText.eof()) {
        currentLine++;
        getline(WhitePawnText, output);
        if (currentLine == lineNum) {
          break;
        }
      }
      // turn "#" into " "
      return output;
      cout << " ";
     } else {
      cout << "Running this stuff:";
      string tempOut;
      currentLine = 0;
      while (getline(WhitePawnText, tempOut)){
        currentLine ++;
        output = tempOut;
        if (currentLine == lineNum) {
          break;
        }
      }
      // while (!WhitePawnText.eof()) { //Gets the line of a white pawn on a black square
      //   currentLine++;
      //   getline(WhitePawnText, output);
      //   if (currentLine == lineNum) {
      //     break;
      //   }
      // }
      cout << output; //<-- for debug purposes
      return output;
    }
    WhitePawnText.close();
    }
  }

  void
  getMoves() { // write logic for how a pawn can move, figure out how to choose
               // a piece
    if (startingPosition) {

    } else {
    }
  }
};

//---------------------------------------------------------------------------------------------

class RegularGame {
public:
  RegularGame(int playerCount) {
    players = playerCount;
    if ((rand() % 1) == 1 || players == 1) { // white is bottom
      string tempArray[64] = {"ROOK", "KNIGHT", "BISHOP", "QUEEN", "KING","BISHOP","KNIGHT","ROOK",
                              "PAWN", "PAWN", "PAWN", "PAWN", "PAWN", "PAWN", "PAWN", "PAWN",
                              "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK","BLANK","BLANK",
                              "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK","BLANK","BLANK",
                              "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK","BLANK","BLANK",
                              "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK","BLANK","BLANK",
                              "PAWN", "PAWN", "PAWN", "PAWN", "PAWN", "PAWN", "PAWN", "PAWN",
                              "ROOK", "KNIGHT", "BISHOP", "QUEEN","KING","BISHOP","KNIGHT","ROOK"};
      for(int i = 0; i < 64; i++){
        Piece tempPiece(tempArray[i], (int(i % 2) == (i % 2)), (i > 32));
        grid[i] = tempPiece;
      }
    } else { // black is bottom
      string tempArray[64] = {
          "ROOK", "KNIGHT", "BISHOP", "KING", "QUEEN", "BISHOP", "KNIGHT", "ROOK",
          "PAWN", "PAWN", "PAWN", "PAWN", "PAWN", "PAWN", "PAWN", "PAWN",
          "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK",
          "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK",
          "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK",
          "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK", "BLANK",
          "PAWN", "PAWN", "PAWN", "PAWN", "PAWN", "PAWN", "PAWN", "PAWN",
          "ROOK", "KNIGHT", "BISHOP", "KING", "QUEEN", "BISHOP", "KNIGHT", "ROOK"};
      for(int i = 0; i < 64; i++){
        Piece tempPiece(tempArray[i], (int(i % 2) == (i % 2)), (i < 32));
        grid[i] = tempPiece;
      }
    }
  }

  void displayBoard() {
    for (int i = 1; i < 5; i++) {
      string thisLine = "";
      for(int i = 8; i < 16; i++){
        thisLine += grid[i].display(i); 
      }
      cout << thisLine + "\n";
    }
  }

private:
  Piece grid[64];
  int players;

  // void storeMemory(string tempGrid[64]) {
  //   for (int i = 0; i < 64; i++) {
  //     grid[i] = tempGrid[i];
  //   }
  // }
};

//-----------------------------------------------

class VariantGame {
  // do this later, start with regular chess above ^^
};
