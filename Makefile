all:
	cd tests; make all

%:
	cd tests; make $@
