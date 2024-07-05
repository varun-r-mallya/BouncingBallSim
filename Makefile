OBJS = ./main.cpp
OBJ_NAME = BouncingBall
all : $(OBJS)
	clang++ -O3 $(OBJS) -w -lSDL2 -o $(OBJ_NAME)
