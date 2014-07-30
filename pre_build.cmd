cls

del  bin\oberonc.exe

del  source\scanner\scanner_lex.cpp

del  source\parser\yy_parser.cpp
del  source\parser\yy_parser.h
del  source\parser\yy_parser.output

cd source/parser
bison -t --report=solved --warnings=error yy_parser.y --output=yy_parser.cpp --defines=yy_parser.h


cd ../scanner
flex -oscanner_lex.cpp -i scanner_lex.l

pause 
