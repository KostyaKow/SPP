default: spp

all: spp samples lex_parse
	
spp:
	cd src; make
	
samples:
	cd src/samples; make

lexer_parser:
	cd src/lex_parse; make

clean:
	rm -rf *.o *.swp *~ obj bin
	cd src; make clean
	cd src/samples; make clean
	cd src/lex_parse; make clean
