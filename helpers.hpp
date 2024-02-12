#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

// Helper functions intended for use by lexer

using namespace std;

// Helper function to determine if a string is an integer
bool isInteger(const string& str) {
  int index = 0;

  if (str.at(0) == '-'){
    index = 1;
  }

  for (int i = index; i < str.size(); i++) {
    if (!isdigit(str[i])){
      return false;
    }
  }

  return true;
}

// Helper function to determine if a string is a double
bool isDouble(const string& str) {
  int index = 0;
  bool decimalFound = false;

  if (str.at(0) == '-'){
    index = 1;
  }

  for (int i = index; i < str.size(); i++) {
    if (!isdigit(str[i])) {
      if (str[i] == '.' && !decimalFound){
        decimalFound = true;
      } else {
        return false;
      }
    }
  }

  return true;
}

bool isReserved(string word, unsigned int lineNum){
  vector<string> reservedWords = {"LET", "IF", "REM", "PRINT", "THEN"};

  if (count(reservedWords.begin(), reservedWords.end(), word)) {
    cout << '"' << word << '"' << " is a reserved word on line " 
      << lineNum << endl;

    return true;
  }

  return false;
}
