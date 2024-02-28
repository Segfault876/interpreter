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
  THEN,
  END,
  OPEN_PARENTHESIS,
  CLOSE_PARENTHESIS,
  NOT,
  AND,
  OR,
  TRUE,
  FALSE,
  WHILE,
  DO,
};

// Simple token structure
struct Token{
  Type type;
  string str;
  unsigned int line;
};

// treeNode is a binary AST, for simplicity
struct treeNode{
  Token token;
  treeNode *l = NULL;
  treeNode *r = NULL;
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