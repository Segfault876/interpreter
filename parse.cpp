#include <vector>
#include <iostream>
#include "token.hpp"

using namespace std;

treeNode *parse(vector<Token> tokens){
  treeNode *root = new treeNode;
  treeNode *tmp = root;

  for (Token token : tokens){
    if (token.type == PRINT || token.type == LET){
      treeNode *newNode = new treeNode;
      newNode->l = NULL;
      newNode->r = NULL;
      newNode->token = token;

      tmp->r = newNode;
      tmp = tmp->r;
    }

    if (token.type == OPERATOR){
      if (token.str == "="){
        treeNode *newNode = new treeNode;
        newNode->l = NULL;
        newNode->r = NULL;
        newNode->token = token;

        tmp->l = newNode;
        tmp = tmp->l;
      }
    }
    
    if ((tmp->token.type == PRINT || tmp->token.type == OPERATOR ) && 
      (token.type == STRING || token.type == INT || 
        token.type == NUM || token.type == VARIABLE)){
      treeNode *newNode = new treeNode;
      newNode->l = NULL;
      newNode->r = NULL;
      newNode->token = token;

      if (tmp->l == NULL){
        tmp->l = newNode;
      }

      // Travel to right-most node of tree upon assignment
      tmp = root;
      while (tmp->r){
        tmp = tmp->r;
      }

    // Below here we will catch improper usage of variables and literals
    } else if (token.type == STRING){
        cout << "Unexpected number on line " << token.line << endl;
      return NULL;
    } else if (token.type == INT){
        cout << "Unexpected number on line " << token.line << endl;
        return NULL;
    } else if (token.type == NUM){
        cout << "Unexpected number on line " << token.line << endl;
        return NULL;
    } else if (token.type == VARIABLE){
        cout << "Invalid usage of variable on line " << token.line << endl;
        return NULL;
    }
  }

  return root;
}