default: spp

all: spp samples
	
spp:
	cd src; make
	
samples:
	cd src/samples; make

clean:
	rm -rf *.o spp *.swp *~
	rm -rf src/*.o src/spp src/*.swp src/*~
	rm -rf src/samples/*.o src/samples/*.swp src/samples/*~
