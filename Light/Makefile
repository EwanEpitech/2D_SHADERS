
##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC = \
	./Light.cpp

OBJ = $(SRC:.cpp=.o)

CXX = g++

NAME = light

CXXFLAGS = -Wall -Wextra -I ./include -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -O3

all: $(NAME)

$(NAME):   $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

debug: CXXFLAGS += -g -DDEBUG
debug: all

rebug: CXXFLAGS += -g -DDEBUG
rebug: re

run: all
	./$(NAME)

rrun: re
	./$(NAME)

tests_run:
	cd tests && make && ./tests

clean:
	rm -f $(OBJ)
	find . -name "vgcore.*" -delete || true
	find . -name "*~" -delete || true
	find . -name "\#*" -delete || true

fclean:    clean
	rm -f $(NAME)

re:        fclean all