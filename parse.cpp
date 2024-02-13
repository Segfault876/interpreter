#include <vector>
#include <iostream>
#include "token.hpp"

using namespace std;

treeNode *parse(vector<Token> &tokens){
  treeNode *root = new treeNode;
  treeNode *tmp = root;

  for (int i = 0; i < tokens.size(); i++){
    if (tokens[i].type == IF){
      treeNode *ifNode = new treeNode;
      ifNode->token = tokens[i];
      tmp->r = ifNode;
      tmp = tmp->r;

      treeNode *conditional = new treeNode;
      conditional->token.str = "TRUE";
      tmp->l = conditional;

      TokenStack tStack;

      while(tokens[i].type != THEN){
        if (++i >= tokens.size()){
          cout << "Expected \"THEN\" on line " << tmp->token.line << endl;
          return NULL;
        }
        
        tStack.push(tokens[i]);
      }

      /* Attach body of if-statment to left-leaf of the THEN token.
         Resize the vector and reset i to avoid duplicate execution */
      treeNode *thenNode = new treeNode;
      thenNode->token = tokens[i];
      tmp->r = thenNode;
      tmp = tmp->r;
      tokens = {tokens.begin() + i, tokens.end()};
      tmp->l = parse(tokens);
      i = 0;

    } else if (tokens[i].type == END){
      tokens = {tokens.begin() + i, tokens.end()};
      return root;

    } else if (tokens[i].type == PRINT || tokens[i].type == LET){
      treeNode *newNode = new treeNode;
      newNode->token = tokens[i];

      tmp->r = newNode;
      tmp = tmp->r;

    } else if (tokens[i].type == OPERATOR){
      if (tokens[i].str == "="){
        treeNode *newNode = new treeNode;
        newNode->token = tokens[i];

        tmp->l = newNode;
        tmp = tmp->l;
      }
    }
    
    /* If current node is print/operator and current token is a literal
       or a variable, create the left-hand relation */
    if ((tmp->token.type == PRINT || tmp->token.type == OPERATOR ) && 
      (tokens[i].type == STRING || tokens[i].type == INT || 
        tokens[i].type == NUM || tokens[i].type == VARIABLE) &&
        tmp->l == NULL){
      treeNode *newNode = new treeNode;
      newNode->token = tokens[i];
      tmp->l = newNode;
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