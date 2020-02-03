NAME = avm

OBJSRC = main.cpp VMachine.cpp OperandFactory.cpp \

OBJC = $(OBJSRC:%.cpp=srcs/%.cpp)
OBJO = $(OBJSRC:.cpp=.o)
FLAGS = -Wall -Werror -Wextra -std=c++11

%.o: srcs/%.cpp
	clang++ $(FLAGS) -o $@ -c $< -I includes

all: $(NAME)

$(NAME): $(OBJO)
	clang++ $(FLAGS) -o $(NAME) $(OBJO)

clean:
	rm -f $(OBJO)

fclean: clean
	rm -f $(NAME)

re: fclean all