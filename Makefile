all:
	gcc -Wall -Wextra -o main main.c Vector.c mover.c global.c -lallegro -lallegro_primitives -lm