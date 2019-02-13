#Compile the program
com:
	g++ *.cpp *.h -std=c++14 -Wall -pthread

#Run program
run:
	./a.out

#One for all command
all: com run
