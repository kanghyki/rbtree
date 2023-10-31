# **************************************************
# * TARGET NAME                                    *
# **************************************************

# **************************************************
# * SOURCE/INCLUDE                                 *
# **************************************************
SRC_PATH = ./src

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
CPPFLAGS = -I $(SRC_PATH)

# **************************************************
# * RULE                                           *
# **************************************************
all: test

%o: %cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(TEST_OBJS)

fclean: clean
	rm -f $(TEST_NAME)

re:
	@make fclean
	@make all

test:
	@make $(TEST_NAME)

$(TEST_NAME): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o $(TEST_NAME)

# **************************************************
# * PHONY                                          *
# **************************************************
.PHONY: all clean fclean re test
