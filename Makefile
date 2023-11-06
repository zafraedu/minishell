NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
UNAME = $(shell uname)
INC = -I$(INC_DIR) -I$(LIBFT_DIR)/inc
LIBS = $(LIBFT_DIR)/libft.a -lreadline
RM = rm -rf

ifeq ($(UNAME), Darwin)
	INC += -I/opt/vagrant/embedded/include
	LIBS += -L/opt/vagrant/embedded/lib
endif

SRCS = $(SRC_DIR)/main.c\
		$(SRC_DIR)/builtins/built.c\
		$(SRC_DIR)/builtins/ft_cd.c\
		$(SRC_DIR)/builtins/ft_echo.c\
		$(SRC_DIR)/builtins/ft_pwd.c\
		$(SRC_DIR)/builtins/ft_env.c\
		$(SRC_DIR)/builtins/ft_exit.c\
		$(SRC_DIR)/exec/signal.c\
		$(SRC_DIR)/parser/lexer_utils.c\
		$(SRC_DIR)/parser/lexer.c\
		$(SRC_DIR)/parser/parser.c\
		$(SRC_DIR)/parser/treat_tokens.c\

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#═════════════════════════  directorios(rutas)  ═══════════════════════════════#
SRC_DIR = src
OBJ_DIR = obj

INC_DIR = inc
LIBFT_DIR = $(INC_DIR)/libft

#══════════════════════════════  Colors  ══════════════════════════════════════#
RED		= \033[31;1m
GREEN	= \033[32;1m
CIAN	= \033[36m
BLUE	= \033[1;38;5;27m
YELLOW	= \033[33m;1m
WHITE	= \033[37;1m
U_LINE	= \033[4m
END 	= \033[0m

#═══════════════════════════════  ARGS   ══════════════════════════════════════#
all: $(NAME)

show:
	@printf "OS	: $(UNAME)\n"
	@printf "NAME  	: $(NAME)\n"
	@printf "CC	: $(CC)\n"
	@printf "CFLAGS	: $(CFLAGS)\n"
	@printf "SRCS	:$(addprefix \n\t , $(notdir $(SRCS)))\n"

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -sC $(LIBFT_DIR)
	@echo "\n$(GREEN)[Cleaned $(CIAN) '$(NAME) objects' $(GREEN)successfully]\n$(END)"

fclean: clean
	@make fclean -sC $(LIBFT_DIR)
	@$(RM) minishell
	@echo "$(GREEN)[Removed $(CIAN)'$(NAME)' $(GREEN)successfully]\n$(END)"

re: fclean all

#══════════════════════════════  Normas  ══════════════════════════════════════#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/exec
	@mkdir -p $(OBJ_DIR)/global_utils
	@mkdir -p $(OBJ_DIR)/parser
	@echo "$(BLUE)MINISHELL Compiling:$(END) $(notdir $<)"
	@$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@make -sC $(LIBFT_DIR)
	@$(CC) $(OBJS) $(CFLAGS) $(INC) $(LIBS) -g -o $@
	@echo "\n$(GREEN)[Compiled $(CIAN) $@ $(GREEN)successfully]\n$(END)"

.PHONY: all bonus show clean fclean re

#-fsanitize=address
