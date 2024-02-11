#include "token.hpp"

struct TokenNode{
  Token token;
  TokenNode *next;
};

struct TokenStack{
  TokenNode *top = NULL;

  void push(Token newToken);
  void pop();
};