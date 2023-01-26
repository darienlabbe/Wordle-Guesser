P3.exe : Project3.o Game.o execute.o WordInfo.o check
	g++ -o P3.exe Project3.o Game.o WordInfo.o execute.o

check : check.cpp execute.h execute.o
	g++ -g -o check check.cpp execute.o

execute.o : execute.cpp execute.h
	g++ -g -c execute.cpp

Project3.o : Project3.cpp Game.h
	g++ -g -c Project3.cpp

Game.o : Game.cpp Game.h execute.h WordInfo.h
	g++ -g -c Game.cpp

WordInfo.o : WordInfo.cpp WordInfo.h
	g++ -g -c WordInfo.cpp

clean : 
	rm -rf *.o *.gch check P3.exe

submit : Project3.cpp check.cpp README.txt
	rm -rf labbeDP3
	rm -rf labbeDP3.tgz
	mkdir labbeDP3
	cp check.cpp labbeDP3
	cp Project3.cpp labbeDP3
	cp Game.h labbeDP3
	cp Game.cpp labbeDP3
	cp WordInfo.h labbeDP3
	cp WordInfo.cpp labbeDP3
	cp makefile labbeDP3
	cp README.txt labbeDP3
	tar cfvz labbeDP3.tgz labbeDP3
	cp labbeDP3.tgz ~tiawatts/cs370drop
