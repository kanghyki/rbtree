# **************************************************
# * TARGET NAME                                    *
# **************************************************
LIB_NAME = rbtree
NAME = lib$(LIB_NAME).a

# **************************************************
# * SOURCE/INCLUDE                                 *
# **************************************************
INC_PATH = ./inc
SRC_PATH = ./src
SRC = Rbtree.cpp\
			Rbnode.cpp
SRCS = $(addprefix $(SRC_PATH)/, $(SRC))
OBJS = $(SRCS:.cpp=.o)

# **************************************************
# * TEST                                           *
# **************************************************
TEST_NAME = run_test
TEST_SRC_PATH = ./test
TEST_SRC = main.c
TEST_SRCS = $(addprefix $(TEST_SRC_PATH)/, $(TEST_SRC))
TEST_OBJS = $(TEST_SRCS:.c=.o)

# **************************************************
# * VARIABLE                                       *
# **************************************************
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11
CPPFLAGS = -I $(INC_PATH)
AR = ar
ARFLAGS = -rcs
LDFLAGS = -l$(LIB_NAME) -L.

# **************************************************
# * RULE                                           *
# **************************************************
all: $(NAME)

%o: %cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

all: $(NAME)

clean:
	rm -f $(OBJS)
	rm -f $(TEST_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re:
	@make fclean
	@make all

test:
	@make $(NAME)
	@make $(TEST_NAME)

$(TEST_NAME): $(TEST_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(TEST_OBJS) -o $(TEST_NAME)

# **************************************************
# * PHONY                                          *
# **************************************************
.PHONY: all clean fclean re test
