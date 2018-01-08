
.PHONY: build check help clean superclean

help:
	@echo "Makefile for CS 4230 Parallel Programming Course"
	@echo "   help       print this help documentation and exit"
	@echo "   library supported --> tbb | pthread | omp | pasl | cuda | mpi  "
	@echo "   download   fetch   the library as per option"
	@echo "   install    install the library as per option"
	@echo "   compile    build the source files as per SRC"
	@echo "   run        execute the binary file as per options"
	@echo "   superclean remove everything installed!"

ifeq "$(library)" "tbb"
DOWNLOAD_CMD=git clone https://github.com/01org/tbb.git
INSTALL_CMD=cd tbb;make -j 8
endif

download:
	$(DOWNLOAD_CMD)
	
install:
	$(INSTALL_CMD)

superclean:
	rm -rf tbb
