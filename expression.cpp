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

/* conditionalPrecedence will take postfix subtree and evaluate
 * that expression. Will return NULL incase of error. */
int evalBool(treeNode *loop){
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