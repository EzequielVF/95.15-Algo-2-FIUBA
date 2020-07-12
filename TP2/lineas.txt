valgrind --leak-check=full  --track-origins=yes --show-reachable=yes -s ./a.out

gcc main.c pokedex.c abb.c lista.c -Wall -Werror -Wconversion -std=c99 -O0 -g
