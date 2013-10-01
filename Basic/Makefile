CC = g++
CFLAGS = -Wall
PROG = 201101101_Assign2

SRCS = 201101101_Assign2.cpp imageloader.cpp
LIBS = -lglut -lGL -lGLU

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
