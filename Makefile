NAME	= avm
CC		= clang++
FLAGS	= -Wall -Wextra -Werror -std=c++14

D_SRC	= ./src/
D_OBJ	= ./obj/
D_INC	= ./inc/
D_DEP	= ./dep/

SRC_F	= main.cpp AbstractVM.cpp AVMExceptions.cpp OperandFactory.cpp Instructions.cpp
SRC		= $(addprefix $(D_SRC), $(SRC_F))

OBJ		= $(SRC:$(D_SRC)%.cpp=$(D_OBJ)%.o)
DEP		= $(OBJ:$(D_OBJ)%.o=$(D_DEP)%.d)

all: createDir $(NAME)

createDir:
	@test -d $(D_OBJ) || mkdir $(D_OBJ)
	@test -d $(D_DEP) || mkdir $(D_DEP)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^ -I $(D_INC)

-include $(DEP)

$(D_OBJ)%.o: $(D_SRC)%.cpp
	$(CC) $(FLAGS) -MMD -MF $(D_DEP)$(@F:%.o=%.d) -c $< -o $@ -I $(D_INC)

clean:
	@rm -f $(OBJ) $(DEP)

fclean: clean
	@rm -f $(NAME)

re: fclean all
