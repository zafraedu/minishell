#ifndef MINISHELL_H
# define MINISHELL_H

/*═════════════════════════════ [  LIBS  ] ═══════════════════════════════════*/
//personal libs
# include "libft/inc/libft.h"
//global libs
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <libgen.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/*═══════════════════════════ [  MACROS  ] ═══════════════════════════════════*/
//errors

# define ERR_CMD "Command not found\n"
# define ERR_PIPE "Pipe error\n"

# define READLINE_MSG "\033[1;36mminishell\033[34m$> \033[0m"

/*═══════════════════════════ [  ENUMS  ] ════════════════════════════════════*/

typedef enum e_token
{
	T_PIPE,        // | pipe
	T_GREAT,       // > REDIR_OUT
	T_GREAT_GREAT, // >> APPEND
	T_LESS,        // < REDIR_IN
	T_LESS_LESS,   // << HEREDOC
	T_GENERAL,     // TEX
	T_SIZE
}					t_token;

/*══════════════════════════ [  STRUCTS  ] ═══════════════════════════════════*/

typedef struct s_lexer
{
	char			*data;
	int				type;
	struct s_lexer	*next;
}					t_lexer;

// estructura sujeta a cambios
typedef struct s_shell
{
	char			**envp;
	char			**paths;
	int				pipe_fd[2];
	int				src_fd;
	int				dst_fd;
	char			**cmd_args;
	char			*cmd;
	// pid_t			pid;
	t_lexer			*token_list;
	// int				i;
	// char			*str;
}					t_shell;

typedef struct s_parser
{
	int				redir_in;
	int				redir_out;
	struct s_parser	*next;
}					t_parser;

/*═════════════════════════ [  FUNCTIONS  ] ══════════════════════════════════*/
//parser
//lexer.c

int					is_special(char *str, int i);
void				ft_lexer(char *input, t_lexer **token_list);
int					check_syntaxis(t_lexer *node);
void				ft_free_tokenlist(t_lexer **token_list);

//lexer_utils.c

void				add_type(t_lexer **token_list, int type);
void				ft_add_token(t_lexer **token_list, char *input, int i,
						int size);
void				treat_special(char *input, t_lexer **token_list, int *i,
						int type);
int					treat_quotes(char *input, t_lexer **token_list, int *i);
void				treat_general(char *input, t_lexer **token_list, int *i);

//exec
//signal.c

void				sigint_handler(int sig);

#endif
