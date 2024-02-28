REM This is a comment in Nick's Basic
LET a = "asdf"
PRINT a

IF FALSE OR TRUE THEN
  LET c = "This should print"
  PRINT c

  REM demonstration of nested if-statement:
  IF TRUE AND TRUE THEN

    PRINT "This should print"
  END

  IF FALSE THEN
    PRINT "This should not print"
  END

END

IF FALSE AND TRUE THEN
  PRINT "This should not print"
END

a = 2

PRINT a

REM PRINT c REM <-- This should create an error when uncommented
REM PRINT a REM <-- This will always work, so long as "a" is in global

REM WHILE TRUE DO REM <-- Working while loop
REM  PRINT "AYY LMAO"
REM END