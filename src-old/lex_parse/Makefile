default: lex_parse

lex_parse: regex.cpp list.cpp
	g++ -std=c++11 list.cpp regex.cpp -o lex_parse


clean:
	rm -rf *.o *.swp *~ a.out lex_parse
