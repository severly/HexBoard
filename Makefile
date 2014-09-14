# Makefile for CS 109 assignment 4
# Spring 2013

clean : main
	rm *.o

main : main.o graph.o node.o hex_board.o hex_ai.o
	g++ -o main main.o graph.o node.o hex_board.o hex_ai.o
	
main.o : main.cpp graph.h node.h hex_board.h hex_ai.h
	g++ -c main.cpp

hex_ai.o : hex_ai.cpp hex_ai.h
	g++ -c hex_ai.cpp
	
hex_board.o : hex_board.cpp hex_board.h
	g++ -c hex_board.cpp
	
graph.o : graph.cpp graph.h node.h
	g++ -c graph.cpp
	
node.o : node.cpp node.h
	g++ -c node.cpp
	