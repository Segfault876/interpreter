IF ( FALSE OR TRUE ) AND ( TRUE OR FALSE ) THEN
  PRINT "This should print"
ELSE
  PRINT "This should not print"
END

IF ( FALSE OR FALSE ) AND ( TRUE OR FALSE ) THEN
  PRINT "This should not print"
ELSE
  PRINT "This should also print"
END