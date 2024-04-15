#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "token.hpp"

using namespace std;

vector<Token> tokenVector;
treeNode *tree;

vector<Token> lex(char *path);
treeNode* parse(vector<Token> &tokenVector, bool topLevel = false);
int interpret(treeNode *root, unordered_map<string, string> &scope, 
  unordered_map<string, treeNode*> subroutines = {});

int main(int argc, char *argv[]){
  if (argc < 2) {
    cout << "Expected path to a .b file" << endl;
  } else {
    tokenVector = lex(argv[1]);
  }

  if (!tokenVector.empty()){
    tree = parse(tokenVector, true);
  }

  if (tree != NULL){
    unordered_map<string, string> globalScope;
    return interpret(tree, globalScope);
  }

  return 1;
}