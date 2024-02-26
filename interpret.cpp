#include <iostream>
#include <unordered_map>
#include <stack>
#include "token.hpp"

using namespace std;

/* Here, only a single scope map is used. This comes with the advantage of
maximum-efficiency encapsulation and fastest-possible scope management, at the
cost of the heavy memory requirements by storing all variable values as strings */
int interpret(treeNode *root, unordered_map<string, string> scope = {}){
  treeNode *tmp = root;

  while (tmp->r){
    tmp = tmp->r;

    if (tmp->token.type == PRINT){
      if (tmp->l && ( 
        tmp->l->token.type == STRING || 
        tmp->l->token.type == NUM ||
        tmp->l->token.type == INT)){
          cout << tmp->l->token.str << endl;

      } else if (tmp->l && tmp->l->token.type == VARIABLE){
        if (scope.find(tmp->l->token.str) == scope.end()){
          cout << "Variable " << "\"" << tmp->l->token.str << "\"" << 
          " is undefined on line " << tmp->l->token.line << endl;
          
          return 1;
        }

        string s = scope[tmp->l->token.str];
        s.erase(0,1);
        cout << s << endl;

      } else {
        cout << "Expected a valid argument for PRINT on line " 
          << tmp->token.line << endl;
        return 1;
      }
    } else if (tmp->token.type == LET){
      if (tmp->l){
        if (scope.find(tmp->token.str) != scope.end()){
          cout << "Duplicate declaration of \"" << tmp->token.str << '"' 
            << " on line " << tmp->token.line << endl;
          return 1;
        }
        scope[tmp->token.str] = tmp->l->l->token.str;

        /* The first character for any scope string will denote
        the variable type for the runtime. */
        if (tmp->l->l->token.type == INT){
          scope[tmp->token.str].insert(0, "i");
        } else if (tmp->l->l->token.type == NUM){
          scope[tmp->token.str].insert(0, "n");
        } else if (tmp->l->l->token.type == STRING){
          scope[tmp->token.str].insert(0, "s");
        }

      } else {
        cout << "Expected symbol after LET on line " 
          << tmp->token.line << endl;
        return 1;
      }
    } else if (tmp->token.type == IF){
      treeNode *loop = tmp->l;
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
        cout << "Invalid boolean expression on line " << tmp->token.line;
        return 1;
      }

      // If top of stack is true, run body
      if (stack.top()->token.type == TRUE){
        interpret(tmp->r->l, scope);
      }
    }
  }

  // Return 0 if all is well
  return 0;
}