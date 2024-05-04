#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

// Utility functions intended for use by lexer

using namespace std;

// Utility function to determine if a string is an integer
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

// Utility function to determine if a string is a double
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
  vector<string> reservedWords = {"LET", "IF", "REM", "PRINT", "THEN", 
    "/", "(", ")", "+", "-", "*", "END", "WHILE", "TRUE", "FALSE", "DO"};

  if (count(reservedWords.begin(), reservedWords.end(), word)) {
    cout << '"' << word << '"' << " is a reserved word on line " 
      << lineNum << endl;

    return true;
  }

  return false;
}

/* Because the lexer uses spaces as a delimiter, manual
 * space insertion is needed for certain tokens. */
string correctDelimiter(string line) {
  stringstream ss(line);
  string word;
  size_t pos;

  while (ss >> word) {
    pos = line.find(word);

    if (word.at(0) == ')') {
      line.erase(pos, 1);
      line.insert(pos, " ) ");

    } else if (word.at(0) == '(') {
      line.erase(pos, 1);
      line.insert(pos, "( ");

    }

    if (word.back() == ')') {
      line.erase(pos + word.size() - 1, 1);
      line.insert(pos + word.size(), " ) ");

    } else if (word.back() == '(') {
      line.erase(pos + word.size() - 1, 1);
      line.insert(pos + word.size(), " ( ");

    }
  }

  pos = line.find('=');

  while (pos != string::npos) {
    if (line[pos + 1] && line[pos + 1] == '='){
      line.insert(pos, " ");
      line.insert(pos + 3, " ");
      pos = line.find('=', pos+3);

    } else {
      line.insert(pos, " ");
      line.insert(pos + 2, " ");
      pos = line.find('=', pos+2);
    }
  }

  ss.str(line);
  return ss.str();
}