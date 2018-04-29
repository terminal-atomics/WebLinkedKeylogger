NAME	= keylogger

CC	= g++

RM	= rm -f

SRCS	= ./src/keylogger.cpp \
	  ./src/main.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPVERSION = -std=c++11

CPPFLAGS = -I ./inc
CPPFLAGS += -Wall -Wextra $(CPPVERSION)

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(CPPVERSION)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
