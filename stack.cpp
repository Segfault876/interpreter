#include "token.hpp"

void TokenStack::push(Token newToken){
  TokenNode *tmp = new TokenNode;
  tmp->token = newToken;
  tmp->next = top;
  this->top = tmp;
}

void TokenStack::pop(){
  TokenNode *tmp = top;
  if (top && top->next){
    this->top = top->next;
  }
  if (tmp){
    delete tmp;
  }
}