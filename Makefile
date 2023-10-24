NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
UNAME = $(shell uname)
INC = -I $(INC_DIR) -I $(LIBFT_DIR)/inc
LIBFT = $(LIBFT_DIR)/libft.a
RM = rm -rf

SRCS = $(SRC_DIR)/main.c\
		$(SRC_DIR)/lexer.c\
		$(SRC_DIR)/lexer_utils.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#═════════════════════════  directorios(rutas)  ═══════════════════════════════#
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc
LIBFT_DIR = inc/libft


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
	@printf "NAME  	: $(NAME)\n"
	@printf "CC	: $(CC)\n"
	@printf "CFLAGS	: $(CFLAGS)\n"
	@printf "SRCS	:$(addprefix \n\t , $(notdir $(SRCS)))\n"$

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
	@echo "$(BLUE)MINISHELL Compiling:$(END) $(notdir $<)"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	@make -sC $(LIBFT_DIR)
	@$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(INC) -lreadline  -g -o $@
	@echo "\n$(GREEN)[Compiled $(CIAN) $@ $(GREEN)successfully]\n$(END)"

.PHONY: all bonus show clean fclean re test5 test100 test500
