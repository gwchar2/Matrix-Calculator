multimat: mainmat.o errorHandler.o mymat.o promptsAndPrints.o 
	gcc -g -ansi -Wall -pedantic errorHandler.o mainmat.o promptsAndPrints.o mymat.o -o multimat

mainmat.o: mainmat.c mymat.h
	gcc -ansi -Wall -pedantic -c mainmat.c -o mainmat.o

errorHandler.o: errorHandler.c mymat.h
	gcc -ansi -Wall -pedantic -c errorHandler.c -o errorHandler.o
	
mymat.o: mymat.c mymat.h
	gcc -ansi -Wall -pedantic -c mymat.c -o mymat.o

promptsAndPrints.o: promptsAndPrints.c mymat.h
	gcc -ansi -Wall -pedantic -c promptsAndPrints.c -o promptsAndPrints.o

clean:
	rm *.o output

