#-----------------[ CMD ]-------------------
NAME	=	Rbtree	
CC		=	clang++
ifndef DEBUG
	CFLAGS	=	-Wall -Wextra -Werror -std=c++98
else
	CFLAGS	=	-g -Wall -Wextra -Werror -std=c++98
endif
RM		=	rm -f
#-----------------[ RB ]-------------------
INC		=	-I .
DIR		=	./
SRC		=	Rbtree.cpp\
			Rbnode.cpp\
			main.cpp
SRCS	=	$(addprefix $(DIR), $(SRC))
OBJS	=	$(SRCS:.cpp=.o)

%o: %cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(INC)

all: $(NAME)

debug: fclean
	@make DEBUG=1 all
	@lldb ./Rbtree

test: re
	@./Rbtree

git: fclean
	@git add .
	@git commit

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	@make fclean
	@make all

.PHONY: clean fclean re test git
