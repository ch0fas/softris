# Quick script to easily compile and test the game, for dev purposes only.
#
gcc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./a.out