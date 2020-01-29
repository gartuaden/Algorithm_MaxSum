all: mp1_20171672

CC=gcc
TARGET=mp1_20171672
OBJECT=mp1_20171672.o

mp1_20171672 : $(OBJECT) 
	$(CC) -o $(TARGET) mp1_20171672.o

main.o : main.c
	$(CC) -c -o mp1_20171672.o mp1_20171672.c

clean:
	rm *.o $(TARGET)
