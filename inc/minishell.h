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
	T_GENERAL,
	T_CMD,       // comando
	T_ARG,       // argumento del comando
	T_PIPE,      // | pipe
	T_REDIR_IN,  // < REDIR_IN
	T_INFILE,    // infile
	T_HEREDOC,   // << HEREDOC
	T_LIMITER,   // (str) para terminar de introducir datos
	T_REDIR_OUT, // > REDIR_OUT
	T_OUTFILE,   // outfile
	T_APPEND,    // >> APPEND
	T_SIZE
}					t_token;

/*══════════════════════════ [  STRUCTS  ] ═══════════════════════════════════*/

typedef struct s_lexer
{
	char *data;           //  contenido (valor literal)
	int type;             //  numero equivalente al token (enum)
	struct s_lexer *next; //  siguiente elemento en la lista
}					t_lexer;

typedef struct s_parser
{
	char *cmd;     // comando que será ejecutado
	char **args;   // argumentos que acompañan al comando
	int redir_in;  // redireccionamiento de entrada
	int redir_out; // redireccionamiento de salida
	struct s_parser	*next;
}					t_parser;

// estructura sujeta a cambios
typedef struct s_shell
{
	char			**envp;
	char **paths;     //test
	char **cmd_args;  //test
	char *cmd;        //test
	t_lexer *lexer;   // separación de tokens
	t_parser *parser; // separación de comandos
}					t_shell;

/*═════════════════════════ [  FUNCTIONS  ] ══════════════════════════════════*/
//bultins

int					is_builting(t_shell *msh);
void				ft_echo(t_shell *msh);
void				ft_pwd(void);
void				ft_env(t_shell *shell);
void				ft_exit(t_shell *shell);

//exec
//signal.c

void				sigint_handler(int sig);

//parser
//lexer_utils.c

int					get_type(char *str, int i);
void				lexer_add_type(t_lexer **ls, int type);
void				ft_add_token(t_lexer **lx, char *input, int i, int size);

//lexer.c

void				ft_lexer(char *input, t_lexer **lx);
void	ft_free_tokenlist(t_lexer **lx); //no va aqui

//parser.c

void				ft_parser(t_parser **parser, t_lexer *lex);

//treat_tokens.c

void				treat_special(char *input, t_lexer **lx, int *i, int type);
int					treat_quotes(char *input, t_lexer **lx, int *i);
void				treat_general(char *input, t_lexer **lx, int *i);

#endif
