// Luca DalCanto, Spencer Wood
//  libraries:
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <thread>
#include <algorithm>
#include <codecvt>
#include <string>
#include <codecvt>
#include <locale>
#include <vector>

using namespace std;

class Piece {
public:
  enum pieceType { BLANK, PAWN, KING, QUEEN, KNIGHT, BISHOP, ROOK };
  string output;
  bool wsquare;
  bool startingPosition = true;
  bool rebels;
  pieceType piece;
  string file;
  string fileName;

  Piece(string myPiece = "PAWN", bool onWhite = true, bool isRebel = true) {

    wsquare = onWhite;
    rebels = isRebel;
    if (myPiece == "PAWN") {
      piece = PAWN;
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
    } else if (myPiece == "BLANK") {
      piece = BLANK;
    }


    if (myPiece == "BLANK") {
      file = "ASCII_ART/blank_square.txt";
    }
    else if(isRebel){
      file = "ASCII_ART/" + myPiece + "_" + "WHITE.txt";
    }
    else{
      file = "ASCII_ART/" + myPiece + "_" + "BLACK.txt";
    }

    
  }

  string display(int lineNum, bool isSelected, bool isPossibleMove) {
    ifstream PieceFile(file);
    string formatting;
    
    if(isSelected){
      formatting += "\u001b[30m\u001b[48;5;33m";
    }
    else if(wsquare){
      formatting += "\u001b[30m\u001b[47m";
    }
    else{     
      formatting += "\u001b[37m\u001b[40m";
    }

    string tempOut;
    int currentLine = 0;
    while (getline(PieceFile, tempOut)) {
      currentLine++;
      output = tempOut;
      replace(output.begin(), output.end(), '#', ' ');//Turns '#' into ' '
      if (currentLine == lineNum) {
        if(isPossibleMove && (lineNum == 1 || lineNum == 5)){
          string box;
          if(lineNum == 1){
            box = "▀";
          }
          else{
            box = "▄";
          }
            string middle;
            middle.assign(output.begin()+1, output.end()-1);
            output = formatting + "\u001b[31m" + box + formatting + middle + "\u001b[31m" + box;
            break;
          
        }
        output = formatting + output + "\u001b[0m";
        break;
      }
    }
    
    return output;
  }

  bool isPiece(){
    return (piece != BLANK);
  }

  void setToBlank(){
    piece = BLANK;
    file = "ASCII_ART/blank_square.txt";
  }

  vector<int> getMoves(int myLoc) { // write logic for how a pawn can move
    if (piece == PAWN) {
      if(int(myLoc/8) == 1 + (5 * int(rebels))){ //if in starting position (based on row)
        return {myLoc+(8 * (1 - (2 * rebels))), myLoc+(16 * (1 - (2 * rebels)))}; //logic for switching direction based on rebel/empire pawn
      } else {
        return {myLoc+(8 * (1 - (2 * rebels)))};
      }
    } else if (piece == KING) {
      if (startingPosition) {
        return {myLoc-8, myLoc+8, myLoc-9, myLoc-7, myLoc+9, myLoc+7, myLoc-1, myLoc+1, myLoc-2, myLoc+3};
      } else {
        return {myLoc-8, myLoc+8, myLoc-9, myLoc-7, myLoc+9, myLoc+7, myLoc-1, myLoc+1};
      }
    } else if (piece == KNIGHT) {
      return {{}}
    }
    return {};
  }
};

//---------------------------------------------------------------------------------------------

class RegularGame {
public:
  RegularGame(int playerCount) {
    players = playerCount;
    if ((rand() % 1) == 1 || players == 1) { // white is bottom
      string tempArray[64] = {
         "ROOK",  "KNIGHT", "BISHOP", "QUEEN", "KING", "BISHOP", "KNIGHT", "ROOK",
         "PAWN",  "PAWN",   "PAWN",   "PAWN",  "PAWN",  "PAWN", "PAWN", "PAWN",
         "BLANK",  "BLANK", "BLANK",  "BLANK", "BLANK", "BLANK",  "BLANK", "BLANK",
         "BLANK", "BLANK",  "BLANK",  "BLANK", "BLANK", "BLANK",  "BLANK", "BLANK",  
         "BLANK", "BLANK",  "BLANK",  "BLANK", "BLANK", "BLANK",  "BLANK", "BLANK", 
         "BLANK", "BLANK",  "BLANK",  "BLANK", "BLANK", "BLANK",  "BLANK", "BLANK",  
         "PAWN",  "PAWN",  "PAWN",   "PAWN",   "PAWN",  "PAWN",  "PAWN",   "PAWN",
         "ROOK",  "KNIGHT", "BISHOP", "QUEEN", "KING", "BISHOP", "KNIGHT", "ROOK",};
      for (int i = 0; i < 64; i++) {
        //Piece tempPiece(tempArray[i], (int(i % 2) == (i % 2)), (i > 32));
        Piece tempPiece(tempArray[i], (((i % 8) - int(i / 8)) % 2) == 0, (i > 32));
        grid[i] = tempPiece;
      }
    } else { // black is bottom
      string tempArray[64] = {
         "ROOK",  "KNIGHT", "BISHOP", "QUEEN", "KING", "BISHOP", "KNIGHT", "ROOK",
         "PAWN",  "PAWN",   "PAWN",   "PAWN",  "PAWN",  "PAWN", "PAWN", "PAWN",
         "BLANK",  "BLANK", "BLANK",  "BLANK",  "BLANK", "BLANK", "BLANK", "BLANK",
         "BLANK", "BLANK",  "BLANK",  "BLANK", "BLANK", "BLANK",  "BLANK", "BLANK",  
         "BLANK", "BLANK",  "BLANK",  "BLANK", "BLANK", "BLANK",  "BLANK", "BLANK", 
         "BLANK", "BLANK",  "BLANK",  "BLANK", "BLANK", "BLANK",  "BLANK", "BLANK",  
         "PAWN",  "PAWN",  "PAWN",   "PAWN",   "PAWN",  "PAWN",  "PAWN",   "PAWN",
         "ROOK",  "KNIGHT", "BISHOP", "QUEEN", "KING",  "BISHOP", "KNIGHT","ROOK"};
      for (int i = 0; i < 64; i++) {
        Piece tempPiece(tempArray[i], (int(i % 2) == (i % 2)), (i < 32));
        grid[i] = tempPiece;
      }
    }
  }

  void displayBoard(bool showPossibleMoves, bool whiteOnBottom) {
    string tempT;
    string boardLine;
    string printResult;
    //display top of board
    for(int i = 0; i < 88; i ++){
      boardLine += " ";
    }
    for(int i = 0; i < 2; i++){
      printResult += "\u001b[40m" + boardLine + "\u001b[0m\n";
    }
    for (int i = 0 + (56*(1-(int)whiteOnBottom)); i < 64 && i >= 0; i += 8 + (-16*(1-(int)whiteOnBottom))) {
      for (int k = 1; k <= 5; k++) {
        string thisLine = "";
        tempT = "";
        int currentLine = 0;
        ifstream leftText("ASCII_ART/left_board.txt");

        //get left part of board for this line
        while (getline(leftText, tempT)) {
          currentLine++;
          if (currentLine == ((5*(i/8)) + k)) {
            thisLine = "\u001b[40m" + tempT + "\u001b[0m";
            break;
          }
        }

        //display squares in line      
        for (int l = 0 + (7*(1-(int)whiteOnBottom)); l < 8 && l >= 0; l += 1 + (-2*(1-(int)whiteOnBottom))) {
          string thisThing;
          thisThing = grid[i + l].display(k, showPossibleMoves && (i+l == currentPiece), showPossibleMoves && find(possibleMoves.begin(), possibleMoves.end(), (i+l)) != possibleMoves.end());
          thisLine += thisThing;
        }
        thisLine += "\u001b[40m    \u001b[0m";
        printResult += thisLine + "\n";
      }
    }
    ifstream bottomText("ASCII_ART/bottom_board.txt");
    printResult += "\u001b[40m" + boardLine + "\n";
    getline(bottomText, tempT);
    if(!whiteOnBottom)reverse(tempT.begin(), tempT.end());
    printResult += tempT + "\u001b[0m\n";
    cout << printResult;
  }

  bool selectPiece(string loc, bool isWhiteTurn){
    currentPiece = convertToIndex(loc);
    if (grid[currentPiece].isPiece() && (grid[currentPiece].rebels == isWhiteTurn)){
      possibleMoves = grid[currentPiece].getMoves(currentPiece);
      int i = 0;
      while(i < possibleMoves.size()){
        if((grid[possibleMoves[i]].isPiece() && grid[possibleMoves[i]].rebels == isWhiteTurn) || possibleMoves[i] > 63 || possibleMoves[i] < 0){
          possibleMoves.erase(possibleMoves.begin()+i); 
        }
        else{
          i++;
        }
      }
      return true;
    }
    currentPiece = -1; //deselect piece since it's an illegal square to move
    possibleMoves = {};
    return false;
  }

  bool movePiece(string loc){
    int destination = convertToIndex(loc);
    if(count(possibleMoves.begin(), possibleMoves.end(), destination)){
      //peform move (will capture if applicable...)
      bool targetIsWhite = grid[destination].wsquare;
      grid[destination] = grid[currentPiece];
      grid[destination].wsquare = targetIsWhite;
      grid[currentPiece].setToBlank();
      return true;
    }
    return false;
  }

private:
  Piece grid[64];
  int players;
  int currentPiece = -1; //number 0 - 63
  vector<int> possibleMoves;

  int convertToIndex(string coordinate){
    transform(coordinate.begin(), coordinate.end(), coordinate.begin(), ::toupper);
    int y = 0;
    for(int i = 1; i <= 8; i++){
      if(coordinate.find(to_string(i)) != string::npos){
        y = 8 - i;
        break;
      }
    }
    const string alphabet[8] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    int x = 0;
    for(int i = 0; i < 8; i++){
      if(coordinate.find(alphabet[i]) != string::npos){
        x = i;
        break;
      }
    }

    return (8*y) + x;
  }
};

//-----------------------------------------------

class VariantGame {
  // do this later, start with regular chess above ^^
};
