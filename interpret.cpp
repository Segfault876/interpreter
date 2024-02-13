#include <iostream>
#include <unordered_map>
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
      if (tmp->l->token.str == "TRUE"){
        interpret(tmp->r->l, scope);
      }
    }
  }

  // Return 0 if all is well
  return 0;
}