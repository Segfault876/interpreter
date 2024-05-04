LET someVariable = 1

PRINT someVariable

SUB changeA
  REM Uncommenting below will change scope of someVariable
  REM LET someVariable = 1
  someVariable = 2
END

GOSUB changeA

PRINT someVariable

REM Order of boolean operations demo

IF (TRUE AND TRUE OR FALSE) THEN
  PRINT "This should print"
END

IF FALSE AND TRUE OR FALSE THEN
  PRINT "This should not print"
ELSE
  PRINT "Cant google this one!"
END