#include <cctype>
#include <string>

using namespace std;

enum Type{
  LET,
  STRING,
  NUM,
  INT,
  PRINT,
  IF,
  OPERATOR,
  VARIABLE,
  THEN
};

// Simple token structure
// TODO: Use unions to prevent
struct Token{
  Type type;
  string str;
  unsigned int line;
};

// treeNode is a binary AST, for simplicity
struct treeNode{
  Token token;
  treeNode *l;
  treeNode *r;
};

// Stacks used for constructing AST
struct TokenNode{
  Token token;
  TokenNode *next;
};

struct TokenStack{
  TokenNode *top = NULL;

  void push(Token newToken);
  void pop();
};