LET a = 1
PRINT a

SUB changeA
  PRINT "a"
  GOSUB changeA
END

SUB dontChangeA
  LET a = 3
END

GOSUB dontChangeA
PRINT a

GOSUB changeA