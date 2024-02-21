#include "token.hpp"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

treeNode *conditionalPrecedence(vector<Token> tokens){
  treeNode *root = new treeNode;
  treeNode *tmp = root;

  stack<Token> stack;
  queue<Token> queue;

  for (int i = 0; i < tokens.size(); i++){
    if (tokens[i].type == TRUE || tokens[i].type == FALSE){
      stack.push(tokens[i]);

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

    if (!stack.empty()){
      tmp->r = new treeNode;
      tmp = tmp->r;
    }
  }

  treeNode *loop = root;
  while (loop){
    cout << "W ";

    if (loop->r){
      loop = loop->r;
    }else{
      loop = NULL;
    }
  }

  return root;
}