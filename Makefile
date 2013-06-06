default: spp

all: spp samples
	
spp:
	cd src; make
	
samples:
	cd src/samples; make

clean:
	rm -rf *.o *.swp *~ obj bin
	cd src; make clean
	cd src/samples; make clean
