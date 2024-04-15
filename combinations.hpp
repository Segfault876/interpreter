#include <unordered_map>

unordered_map<string, string> combineScopes(unordered_map<string, string> localScope, 
  unordered_map<string, string> scope) {

  unordered_map<string, string> newScope;
  newScope = localScope;
  // The insert function will conveniently ignore duplicate key insertions
  localScope.insert(scope.begin(), scope.end());

  return newScope;
}