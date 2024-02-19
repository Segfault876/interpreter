REM This is a comment in Nick's Basic
LET a = "asdf"
PRINT a

IF FALSE OR TRUE THEN
  PRINT "This should print"
END

IF FALSE OR FALSE THEN
  PRINT "This should not print"
END

IF FALSE AND TRUE THEN
  PRINT "This should also not print"
END

IF TRUE AND TRUE THEN
  PRINT "This should print though"
END

REM PRINT c REM <-- This should create an error when uncommented