#include <vector>
#include <iostream>
#include "token.hpp"

using namespace std;

treeNode *parse(vector<Token> tokens){
  treeNode *root = new treeNode;
  treeNode *tmp = root;

  for (int i = 0; i < tokens.size(); i++){
    if (tokens[i].type == IF){
      int line = tokens[i].line;
      TokenStack tStack;

      while(tokens[i].type != THEN){
        if (++i >= tokens.size()){
          cout << "Expected \"THEN\" on line " << line << endl;
          return NULL;          
        }
        
        tStack.push(tokens[i]);

      }
    }

    if (tokens[i].type == PRINT || tokens[i].type == LET){
      treeNode *newNode = new treeNode;
      newNode->l = NULL;
      newNode->r = NULL;
      newNode->token = tokens[i];

      tmp->r = newNode;
      tmp = tmp->r;
    }else if (tokens[i].type == OPERATOR){
      if (tokens[i].str == "="){
        treeNode *newNode = new treeNode;
        newNode->l = NULL;
        newNode->r = NULL;
        newNode->token = tokens[i];

        tmp->l = newNode;
        tmp = tmp->l;
      }
    }
    
    if ((tmp->token.type == PRINT || tmp->token.type == OPERATOR ) && 
      (tokens[i].type == STRING || tokens[i].type == INT || 
        tokens[i].type == NUM || tokens[i].type == VARIABLE)){
      treeNode *newNode = new treeNode;
      newNode->l = NULL;
      newNode->r = NULL;
      newNode->token = tokens[i];

      if (tmp->l == NULL){
        tmp->l = newNode;
      }

      // Travel to right-most node of tree upon assignment
      tmp = root;
      while (tmp->r){
        tmp = tmp->r;
      }

    // Below here we will catch improper usage of variables and literals
    } else if (tokens[i].type == STRING){
        cout << "Unexpected string on line " << tokens[i].line << endl;
      return NULL;
    } else if (tokens[i].type == INT){
        cout << "Unexpected integer on line " << tokens[i].line << endl;
        return NULL;
    } else if (tokens[i].type == NUM){
        cout << "Unexpected number on line " << tokens[i].line << endl;
        return NULL;
    } else if (tokens[i].type == VARIABLE){
        cout << "Invalid usage of variable on line " << tokens[i].line << endl;
        return NULL;
    }
  }

  return root;
}