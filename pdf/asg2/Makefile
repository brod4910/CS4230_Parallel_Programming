CC 			:= gcc-7
CXX 		:= g++-7

CPPFLAGS +=  -fopenmp -lpthread
WAR += -Wall
# LDFLAGS += -L/usr/local/opt/llvm/lib -Wl,-rpath,/usr/local/opt/llvm/lib

main: main.cpp
	$(CXX) $(CPPFLAGS) $(WAR) $^ -o $@ $(LDFLAGS)

dotprod: OMP_DP.cpp
	$(CXX) $(CPPFLAGS) $(WAR) $^ -o $@ $(LDFLAGS)