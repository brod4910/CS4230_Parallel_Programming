CC 			:= gcc-7
CXX 		:= g++-7

CPPFLAGS +=  -fopenmp -lpthread -ltbb
WAR += -Wall
# LDFLAGS += -L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib

primes: primes.cpp
	$(CXX) $(CPPFLAGS) $(WAR) $^ -o $@ $(LDFLAGS)

dotprod: OMP_DP.cpp
	$(CXX) $(CPPFLAGS) $(WAR) $^ -o $@ $(LDFLAGS)

clean:
	@echo " "
	@echo "Cleaning..."
	@echo " "
	rm -rf *.exe *.o *.lst *.decompile *.txt .lst *.out dotprod primes
	@echo " "
	@echo "Done."
	@echo " "