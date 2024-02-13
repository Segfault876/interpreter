#include "token.hpp"
#include <iostream>
#include <stack>
#include <queue>

// Reference: https://www.youtube.com/watch?v=Wz85Hiwi5MY

using namespace std;

treeNode *precedence(vector<Token> &tokens){
  treeNode *root;
  treeNode *tmp = root;

  stack<Token> stack;
  queue<Token> queue;

  for (int i = 0; i < tokens.size(); i++){
    if (tokens[i].type == OPERATOR){
      if (tokens[i].str == "("){
        stack.push(tokens[i]);

      } else if (tokens[i].str == ")"){
        while (stack.top().str != "("){
          if (stack.empty()){
            cout << "Mismatched parenthesis on line " << tokens[i].line << endl;
            return NULL;
          }

          if (stack.top().str != ")" && stack.top().str != "("){
            queue.push(stack.top());
          }
          stack.pop();
        }

      }else if (tokens[i].str == "+" || tokens[i].str == "-"){
        if (stack.top().str == "*" || stack.top().str == "/"){
          queue.push(stack.top());
          stack.pop();
          stack.push(tokens[i]);
        } else {
          queue.push(tokens[i]);
        }
      }

    } else if (tokens[i].type == NUM || tokens[i].type == INT 
    || tokens[i].type == VARIABLE){
      queue.push(tokens[i]);

    } else {
      if (!stack.empty()){
        cout << "Invalid expression on line " << tokens[i-1].line << endl;
        return NULL;
      } else {
        while (!queue.empty()){
          stack.push(queue.front());
          queue.pop();
        }

        //tokens = {tokens.begin() + i - 1, tokens.end()};
      }
    }
  }

  return root;
}