RELEASE_CFLAGS	=	-W -Wall -Wextra -Werror

CXX 		= 	g++

RM		= 	rm -f

NAME		=	test

SRCS		= 	src/main.cpp \
			src/IniFileParser.cpp \
			src/IniSection.cpp

OBJS		= 	$(SRCS:.cpp=.o)

CXXFLAGS 	+= 	-std=c++14
CXXFLAGS	+=	-I./include/

all: CXXFLAGS+=$(RELEASE_CFLAGS)
all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean, re, all, fclean
