CFLAGS = -Wall -std=c++11 -Wno-write-strings

mafia: mafia.cpp scan.cpp compile.cpp vm.cpp
	g++ $(CFLAGS) $^ -o mafia

clean:
	rm mafia
