# r4linux
# Makefile de SEBAS

CPP  = g++
OBJ  = socketwl.o graf.o redam.o
LINKOBJ  = socketwl.o graf.o redam.o
LIBS = -lSDLmain -lSDL -s
#-lfmod -s
BIN  = r4
CFLAGS = -O2 #-fexpensive-optimizations -O3
#CFLAGS = $(INCS) -fexpensive-optimizations -O3 -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings

RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before r4 all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

socketwl.o: socketwl.cpp
	$(CPP) -c socketwl.cpp -o socketwl.o $(CFLAGS)

graf.o: graf.cpp
	$(CPP) -c graf.cpp -o graf.o $(CFLAGS)

redam.o: redam.cpp
	$(CPP) -c redam.cpp -o redam.o $(CFLAGS)

