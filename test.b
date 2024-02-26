REM This is a comment in Nick's Basic
LET a = "asdf"
PRINT a

IF FALSE OR TRUE THEN
  PRINT "This should print"

  IF TRUE OR TRUE THEN

    PRINT "AYY"
  END

  IF FALSE THEN
    PRINT "NO AYY"
  END

END

IF FALSE OR FALSE THEN
  PRINT "This should not print"
END

IF FALSE AND TRUE THEN
  PRINT "This should also not print"
END

IF TRUE AND TRUE THEN
  PRINT "This should print too"
END

REM PRINT c REM <-- This should create an error when uncommented