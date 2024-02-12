#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "token.hpp"
#include "helpers.hpp"

using namespace std;

// Function lex takes a character pointer to the source file.
// It will then lex said code and return a Token vector.
vector<Token> lex(char *path){
  vector<string> varSymbols;
  ifstream source(path);
  vector<Token> tokens;

  // Counting line numbers is good for error reporting
  unsigned int lineNum = 0;

  if (!source.is_open()){
    cout << "Unable to open file: " << path << endl;
    return tokens;
  }

  string line;
  while (getline(source, line)) {
    lineNum++;

    istringstream ss(line);
    string word;

    // Stream through the each line by word
    while (ss >> word){
      if (word == "PRINT"){
        Token tmp;
        tmp.line = lineNum;
        tmp.type = PRINT;
        tokens.push_back(tmp);

      } else if (word.front() == '"'){
        Token tmp;
        tmp.line = lineNum;
        tmp.type = STRING;
        string str = word;

        while (word.back() != '"'){
          // Get stream position before obtaining next word
          int start = static_cast<int>(ss.tellg());

          ss >> word;

          // Get stream position after obtaining next word
          int end = static_cast<int>(ss.tellg());

          // If the string stream is pointing to the end of the line,
          // set integer end equal to total length of line.
          if (end == -1){
            end = line.length();

            if (word.back() != '"'){
              cout << "Invalid string literal on line " << lineNum << endl;
              tokens.clear();
              return tokens;
            }
          }

          // Fill string literal with otherwise-ignored spaces
          for (int i = 0; i < (end - start - word.length()); i++){
            str.append(" ");
          }

          str.append(word);
        }

        tmp.str = str.substr(1, str.length() - 2);
        tokens.push_back(tmp);

      } else if (word == "REM"){
        // Simply skip to end if remark
        while (ss >> word);

      } else if (isInteger(word) || isDouble(word)) {
        Token tmp;
        tmp.type = (isInteger(word)) ? INT : NUM;
        tmp.str = word;
        tmp.line = lineNum;
        tokens.push_back(tmp);

      } else if (word == "LET"){
        Token tmp;
        tmp.line = lineNum;
        tmp.type = LET;

        ss >> word;        
        if (isReserved(word, lineNum)){
          tokens.clear();
          return tokens;
        }

        tmp.str = word;
        tokens.push_back(tmp);

        if (!count(varSymbols.begin(), varSymbols.end(), word)){
          varSymbols.push_back(word);
        }
  
      } else if (word == "="){
        Token tmp;
        tmp.type = OPERATOR;
        tmp.str = "=";
        tmp.line = lineNum;
        tokens.push_back(tmp);               

      } else if (word == "IF"){
        Token tmp;
        tmp.type = IF;
        tmp.line = lineNum;
        tokens.push_back(tmp);

      } else if (word == "THEN"){
        Token tmp;
        tmp.type = THEN;
        tmp.line = lineNum;
        tokens.push_back(tmp);

      } else if (count(varSymbols.begin(), varSymbols.end(), word)){ 
        Token tmp;
        tmp.type = VARIABLE;
        tmp.str = word;
        tmp.line = lineNum;
        tokens.push_back(tmp);

      } else {
        cout << "Invalid token on line " << lineNum << endl;
        tokens.clear();
        return tokens;
      }
    }
  }

  source.close();

  return tokens;
}