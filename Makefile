NAME = gp #programm name

SRCS = $(shell find src -name *.c) #all .c files in src

HEADERS=$(shell find inc -name *.h) #all .h in includes

CFLAGS = -fsanitize=address -Wall -g # #flags
 
CC = gcc #complier

OBJS = $(SRCS:.c=.o) #make for each .c .o 

%.o: %.c #the rule of making -c means made an object file not an executable
	$(CC) -I./inc -c $(CFLAGS) $< -o $@ 

all : $(NAME) #alls target is our NAME 

#linking all together
$(NAME) : Makefile $(OBJS) $(HEADERS) #the deps of liniking is Makefile changes header changes and recompiling objs
	$(CC) -fsanitize=address $(OBJS) -o $(NAME)

clean : #cleaning OBJ files
	rm -rf $(OBJS)

fclean : clean #cleaning executable also
	rm $(NAME)

re : fclean all #full cleaning and rebuilding of proj

.PHONY : all re clean fclean 