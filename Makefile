CFLAGS = -std=c++20

mafia: mafia.cpp scan.cpp compile.cpp
	g++ $(CFLAGS) $^ -o mafia
