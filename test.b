LET a = 1
PRINT a

SUB changeA
  a = 2
END

SUB dontChangeA
  LET a = 3
END

GOSUB dontChangeA
PRINT a
GOSUB changeA
PRINT a