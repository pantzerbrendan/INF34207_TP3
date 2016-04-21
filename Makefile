RM    = rm -vf
CXX   = g++

NAME  = INF34207_TP3

SRC   = ./source/Thread.cpp \
        ./source/Mutex.cpp
        
OBJ   = $(SRC:.cpp=.o)

CXXFLAGS  +=  -lpthread

$(NAME):  $(OBJ)
          $(CXX) ./tests/main1.cpp -o ./tests/main1.o
          $(CXX) $(OBJ) ./tests/main1.o -o $(NAME)_test1
          $(CXX) ./tests/main2.cpp -o ./tests/main2.o
          $(CXX) $(OBJ) ./tests/main2.o -o $(NAME)_test2
          
all:      $(NAME)

clean:
          @$(RM) $(OBJS)

fclean:   clean
          @$(RM) $(NAME)_test1
          @$(RM) $(NAME)_test2

re:       fclean all

.PHONY: clean fclean all re
