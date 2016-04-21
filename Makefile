RM	=	rm -vf
CXX	=	g++ -g

NAME	=	INF34207_TP3

SRC	=	./source/Thread.cpp \
		./source/Mutex.cpp

OBJ	=	$(SRC:.cpp=.o)

LDFLAGS		+=	-lpthread -std=c++11
CXXFLAGS	+=	-I./include $(LDFLAGS)

$(NAME):	$(OBJ)
		$(CXX) -c ./tests/main1.cpp -o ./tests/main1.o
		$(CXX) $(OBJ) ./tests/main1.o -o $(NAME)_test1 $(LDFLAGS)
		$(CXX) -c ./tests/main2.cpp -o ./tests/main2.o
		$(CXX) $(OBJ) ./tests/main2.o -o $(NAME)_test2 $(LDFLAGS)

all:		$(NAME)

clean:
		@$(RM) $(OBJ)

fclean:		clean
		@$(RM) $(NAME)_test1
		@$(RM) $(NAME)_test2

re:		fclean all

.PHONY:		clean fclean all re
