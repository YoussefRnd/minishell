NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -lreadline -L/goinfre/$(USER)/homebrew/opt/readline/lib -I/goinfre/$(USER)/homebrew/opt/readline/include
RM = rm -fr
MKDIR = mkdir -p

LIBFT = lib/Libft
LIBFT_LIB = $(LIBFT)/libft.a


OBJ_DIR = obj
INC_DIR = inc

SRCS =  $(wildcard lexer/src/*.c) $(wildcard parser/src/*.c) $(wildcard utils/src/*.c) $(wildcard builtins/src/*.c) $(wildcard exec/src/*.c) main.c 

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I builtins/inc -I lexer/inc -I parser/inc -I utils/inc -I $(LIBFT)  -c $< -o $@

$(NAME): $(LIBFT_LIB) $(OBJS)
	@echo "Building $@..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT) -lft
	@echo "$@ is ready!"

clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@echo "Cleaning $(NAME)..."
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re