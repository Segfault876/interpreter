#include <iostream>
#include <stack>
#include <queue>
#include "token.hpp"

using namespace std;

/* conditionalPrecedence will take a token vector and return a
 * a tree that contains a boolean postfix expression. */
treeNode *conditionalPrecedence(vector<Token> tokens){
  treeNode *root = new treeNode;
  treeNode *tmp = root;

  stack<Token> stack;
  queue<Token> queue;

  for (int i = 0; i < tokens.size(); i++){
    if (tokens[i].type == TRUE || tokens[i].type == FALSE){
      queue.push(tokens[i]);

    } else if (tokens[i].type == OR) {
      while (!stack.empty() && (stack.top().type == OR || stack.top().type == AND)){
        queue.push(stack.top());
        stack.pop();
      }

      stack.push(tokens[i]);
    } else if (tokens[i].type == AND) {
      while (!stack.empty() && (stack.top().type == AND)){
        queue.push(stack.top());
        stack.pop();
      }

      stack.push(tokens[i]);
    } else if (tokens[i].type == OPEN_PARENTHESIS){
      stack.push(tokens[i]);   

    } else if (tokens[i].type == CLOSE_PARENTHESIS){
      while (!stack.empty() && stack.top().type != OPEN_PARENTHESIS){
        queue.push(stack.top());
        stack.pop();
      }

      if (stack.empty()){
        cout << "Unexpected closing parenthesis on line " 
          << tokens[i].line << endl;

        return NULL;
      }

      stack.pop();
    }
  }

  while (!stack.empty()){
    // There should be no open parenthesis on the stack
    if (stack.top().type == OPEN_PARENTHESIS){
      cout << "Expected closing parenthesis on line " 
        << stack.top().line << endl;

      return NULL;
    }

    queue.push(stack.top());
    stack.pop();
  }

  while (!queue.empty()){
    tmp->token = queue.front();
    queue.pop();

    if (!queue.empty()){
      tmp->r = new treeNode;
      tmp = tmp->r;
    }
  }

  return root;
}

/* numericalPrecedence will take a token vector and return a
 * a tree that contains a numerical postfix expression. */
treeNode *numericalPrecedence(vector<Token> tokens) {
  treeNode *root = new treeNode;
  treeNode *tmp = root;

  stack<Token> stack;
  queue<Token> queue;

  for (int i = 0; i < tokens.size(); i++){
    if (tokens[i].str == "="){
      cout << "Invalid assignment operator for numerical expression on line "
        << tokens[i].line << endl;
      
      return NULL;
    }

    if (tokens[i].type == INT || 
      tokens[i].type == NUM || 
      tokens[i].type == VARIABLE){
        queue.push(tokens[i]);

    } else if (tokens[i].type == OPERATOR) {
      if (tokens[i].str == "+" || tokens[i].str == "-") {
        while (!stack.empty() && (stack.top().type == OPERATOR)){
          queue.push(stack.top());
          stack.pop();
        }

        stack.push(tokens[i]);
        
      } else if (tokens[i].str == "*" || tokens[i].str == "/") {
        while (!stack.empty() && (stack.top().str == "*" || 
          stack.top().str == "/")){
            queue.push(stack.top());
            stack.pop();
        }

        stack.push(tokens[i]);
      }
    }
  }

  while (!stack.empty()){
    queue.push(stack.top());
    stack.pop();
  }

  while (!queue.empty()){
    tmp->token = queue.front();
    queue.pop();

    if (!queue.empty()){
      tmp->r = new treeNode;
      tmp = tmp->r;
    }
  }

  return root;
}

/* evalBool will take a boolean post-fix expression and interpret the result,
 * returning 1 for true, 0 for false, and -1 for error. */
int evalBool(treeNode *loop){
  stack<treeNode*> stack;
  int line = -1;

  // Evaluate post-fix expression
  while (loop) {
    if (loop->token.type == FALSE || loop->token.type == TRUE) {
      stack.push(loop);

    } else if (loop->token.type == AND && stack.size() > 1) {
      treeNode *op1, *op2;
      treeNode *newNode = new treeNode;
      op1 = stack.top();
      stack.pop();
      op2 = stack.top();
      stack.pop();

      if (op1->token.type == TRUE && op2->token.type == TRUE) {
        newNode->token.type = TRUE;
      } else {
        newNode->token.type = FALSE;           
      }
      
      stack.push(newNode); 

    } else if (loop->token.type == OR && stack.size() > 1) {
      treeNode *op1, *op2;
      treeNode *newNode = new treeNode;
      op1 = stack.top();
      stack.pop();
      op2 = stack.top();
      stack.pop();

      if (op1->token.type == TRUE || op2->token.type == TRUE) {
        newNode->token.type = TRUE;
      } else {
        newNode->token.type = FALSE;           
      }
      
      stack.push(newNode); 
    }

    if (loop->token.line) {
      line = loop->token.line;
    }

    if (loop->r){
      loop = loop->r;
    } else {
      loop = NULL;
    }
  }
  
  // Stack cannot be empty
  if (stack.empty()) {
    if (line > 0) {
      cout << "Invalid boolean expression on line " << line << endl;
    } else {
      cout << "Invalid boolean expression" << endl;
    }
    return -1;
  }

  if (stack.top()->token.type == TRUE){
    return 1;
  }

  return 0;
}

/* evalExpression will take a numerical post-fix expression and interpret the 
 * result, returning 1 for true, 0 for false, and -1 for error. */
int evalExpression(treeNode *loop){
  stack<treeNode*> stack;

  // Evaluate post-fix expression
  while (loop){
    if (loop->token.type == FALSE || loop->token.type == TRUE){
      stack.push(loop);

    } else if (loop->token.type == AND && stack.size() > 1){
      treeNode *op1, *op2;
      treeNode *newNode = new treeNode;
      op1 = stack.top();
      stack.pop();
      op2 = stack.top();
      stack.pop();

      if (op1->token.type == TRUE && op2->token.type == TRUE){
        newNode->token.type = TRUE;
      } else {
        newNode->token.type = FALSE;           
      }
      
      stack.push(newNode); 

    } else if (loop->token.type == OR && stack.size() > 1){
      treeNode *op1, *op2;
      treeNode *newNode = new treeNode;
      op1 = stack.top();
      stack.pop();
      op2 = stack.top();
      stack.pop();

      if (op1->token.type == TRUE || op2->token.type == TRUE){
        newNode->token.type = TRUE;
      } else {
        newNode->token.type = FALSE;           
      }
      
      stack.push(newNode); 

    }

    if (loop->r){
      loop = loop->r;
    } else {
      loop = NULL;
    }
  }
  
  // Stack cannot be empty
  if (stack.empty()){
    cout << "Invalid boolean expression on line " << loop->token.line;
    return -1;
  }

  if (stack.top()->token.type == TRUE){
    return 1;
  }

  return 0;
}