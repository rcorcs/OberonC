clear

rm  bin/oberonc

rm  source/scanner/scanner_lex.cpp

rm  source/parser/yy_parser.cpp
rm  source/parser/yy_parser.h
rm  source/parser/yy_parser.output

cd source/parser
#bison -t --report=solved --warnings=error yy_parser.y --output=yy_parser.cpp --defines=yy_parser.h
bison -t --report=solved yy_parser.y --output=yy_parser.cpp --defines=yy_parser.h

cd ../scanner
flex -oscanner_lex.cpp -i scanner_lex.l

cd ../
g++ main.cpp oberonc/*.cpp global/*.cpp debugger/*.cpp debugger/debugger_implementations/*.cpp scanner/*.cpp parser/*.cpp  symbol_table/*.cpp symbol_table/identifier_category/*.cpp ast/*.cpp ast/declaration/*.cpp ast/expression/*.cpp ast/statement/*.cpp code_generator/*.cpp code_generator/intermediate/*.cpp code_generator/intermediate/instruction/*.cpp code_generator/intermediate/instruction_argument/*.cpp debugger/debugger_interfaces/* code_generator/machine/*.cpp -lfl -o ../bin/oberonc
