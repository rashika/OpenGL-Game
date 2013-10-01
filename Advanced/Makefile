CC = g++
CFLAGS = -Wall
PROG = sample1

SRCS = Game.cpp imageloader.cpp
LIBS = -lglut -lGL -lGLU -g

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -w -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
