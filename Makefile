CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++11
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRCS = ./src/main.cpp ./src/Tetromino.cpp ./src/grid.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = main
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LIBS)

clean:
	rm -f $(OBJS) $(EXEC)