#include "token.hpp"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

/* conditionalPrecedence will take a token vector and return a
 * a tree that contains a postfix expression.
*/
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