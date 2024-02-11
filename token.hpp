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
  VARIABLE
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