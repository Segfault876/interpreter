#include <iostream>
#include <unordered_map>
#include <stack>
#include "expression.hpp"
#include "combinations.hpp"

using namespace std;
extern int stackFrame;

/* Here, only a single scope map is used. This comes with the advantage of
maximum-efficiency encapsulation and fastest-possible scope management, at the
cost of the heavy memory requirements by storing all variable values as strings */
int interpret(treeNode *root, unordered_map<string, string> &scope,
  unordered_map<string, treeNode*> subroutines = {}) {
  unordered_map<string, string> localScope = {};
  stackFrame++;

  if (stackFrame >= 2048){
    cout << "Stack overflow. Maximum frame size (2048) exceeded." << endl;
    return -1;
  }

  treeNode *tmp = root;

  while (tmp->r){
    tmp = tmp->r;

    if (tmp->token.type == PRINT) {
      if (tmp->l && ( 
        tmp->l->token.type == STRING || 
        tmp->l->token.type == NUM ||
        tmp->l->token.type == INT)){
          cout << tmp->l->token.str << endl;

      } else if (tmp->l && tmp->l->token.type == VARIABLE){
        if (localScope.find(tmp->l->token.str) == scope.end() &&
          scope.find(tmp->l->token.str) == scope.end()){
          cout << "Variable " << "\"" << tmp->l->token.str << "\"" << 
          " is undefined on line " << tmp->l->token.line << endl;
          
          return 1;
        }
        
        string s;
        if (localScope.find(tmp->l->token.str) != localScope.end()) {
          s = localScope[tmp->l->token.str];
        } else {
          s = scope[tmp->l->token.str];
        }

        s.erase(0,1);
        cout << s << endl;

      } else {
        cout << "Expected a valid argument for PRINT on line " 
          << tmp->token.line << endl;
        return 1;
      }
    } else if (tmp->token.type == LET){
      if (tmp->l){
        if (localScope.find(tmp->token.str) != scope.end()){
          cout << "Duplicate declaration of \"" << tmp->token.str << '"' 
            << " on line " << tmp->token.line << endl;
          return 1;
        }
        localScope[tmp->token.str] = tmp->l->l->token.str;

        /* The first character for any scope string will denote
        the variable type for the runtime. */
        if (tmp->l->l->token.type == INT){
          localScope[tmp->token.str].insert(0, "i");
        } else if (tmp->l->l->token.type == NUM){
          localScope[tmp->token.str].insert(0, "n");
        } else if (tmp->l->l->token.type == STRING){
          localScope[tmp->token.str].insert(0, "s");
        }

      } else {
        cout << "Expected symbol after LET on line " 
          << tmp->token.line << endl;
        return 1;
      }
    } else if (tmp->token.type == IF){
      // Evaluate the if-condition (left child node)
      int condition = evalBool(tmp->l);

      if (condition == -1){ // Return if error in expression
        return 1;
      } else if (condition == 1){ // If expression is true
        // Evaluate the l-expression of the r-hand of tmp (THEN node)
        unordered_map<string, string> newScope = combineScopes(localScope, scope);
        interpret(tmp->r->l, newScope, subroutines);
        localScope = combineScopes(scope, newScope);

      } else { // If expression is false
        treeNode *loop = tmp->r->l; // Point to child of THEN node

        while (loop){ // Search for ELSE token
          if (loop->token.type == ELSE){
            unordered_map<string, string> newScope = combineScopes(localScope, scope);
            interpret(loop->l, newScope, subroutines);
            localScope = combineScopes(newScope, localScope);
          }

          if (loop->r){
            loop = loop->r;
          } else {
            loop = NULL;
          }
        }
      }

    } else if (tmp->token.type == WHILE){
      int condition = evalBool(tmp->l);

      if (condition == -1){
        return 1;
      } 
      
      while (condition == 1){
        unordered_map<string, string> newScope = combineScopes(localScope, scope);
        interpret(tmp->r->l, newScope, subroutines);
        localScope = combineScopes(newScope, localScope);
      }
    } else if (tmp->token.type == VARIABLE){
      if (tmp->r->token.type == OPERATOR && tmp->r->token.str == "="){
        if (localScope.find(tmp->token.str) == scope.end() && 
          scope.find(tmp->token.str) == scope.end()){
          cout << "Variable " << "\"" << tmp->l->token.str << "\"" << 
          " is undefined on line " << tmp->l->token.line << endl;
          
          return 1;
        }

        /* The first character for any scope string will denote
        the variable type for the runtime. */
        if (tmp->r->l->token.type == INT){
          tmp->r->l->token.str.insert(0, "i");
        } else if (tmp->r->l->token.type == NUM){
          tmp->r->l->token.str.insert(0, "n");
        } else {
          tmp->r->l->token.str.insert(0, "s");
        }

        /* Temporarily use direct-assignment, 
         * this only works for assigning one value at a time */
        if (localScope.find(tmp->token.str) != scope.end()){
          localScope[tmp->token.str] = tmp->r->l->token.str;
        } else {
          scope[tmp->token.str] = tmp->r->l->token.str;
        }

      }
    } else if (tmp->token.type == SUB) {
      if (tmp->l) {
        if (subroutines.find(tmp->token.str) != subroutines.end()){
          cout << "Duplicate declaration of \"" << tmp->token.str << '"' 
            << " on line " << tmp->token.line << endl;
          return 1;
        }

        subroutines[tmp->token.str] = tmp->l;

      }
    } else if (tmp->token.type == GOSUB) {
      if (subroutines[tmp->token.str]) {
        unordered_map<string, string> newScope = combineScopes(localScope, scope);
        interpret(subroutines[tmp->token.str], newScope, subroutines);
        localScope = combineScopes(newScope, localScope);

      } else {

        cout << "Subroutine " << tmp->token.str << " is not declared" << endl;
        return 1;
      }
    }
  }

  stackFrame--;
  // Return 0 if all is well
  return 0;
}