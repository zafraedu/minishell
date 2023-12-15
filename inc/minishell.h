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

//message display

# define READLINE_MSG "\033[1;36mminishell\033[34m$> \033[0m"
# define HEREDOC_MSG "\033[1;34m> \033[0m"

/*═══════════════════════════ [  ENUMS  ] ════════════════════════════════════*/

typedef enum e_token
{
	T_GENERAL,
	T_CMD,       // comando
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

typedef struct s_env
{
	char			*var_name;
	char			*value_var;
	struct s_env	*next;
}					t_env;

typedef struct s_lexer
{
	int index;            //  indice del token
	char *data;           //  contenido (valor literal)
	int type;             //  numero equivalente al token (enum)
	struct s_lexer *next; //  siguiente elemento en la lista
}					t_lexer;

typedef struct s_parser
{
	char *cmd;     // comando que será ejecutado
	int redir_in;  // redireccionamiento de entrada
	int redir_out; // redireccionamiento de salida
	struct s_parser	*next;
}					t_parser;

// estructura sujeta a cambios
typedef struct s_shell
{
	char **envp; // no creo que haga falta
	char			**paths;
	char			**cmd_args;
	int				count_cmd_args;
	t_env			*env;
	t_lexer			*lexer;
	t_parser		*parser;
	int				exit_status;
}					t_shell;

/*═════════════════════════ [  FUNCTIONS  ] ══════════════════════════════════*/

/*-------------------------- [  bultins  ] -----------------------------------*/
//built.c

int					is_builtin(t_shell *msh);
void				ft_builtin(t_shell *msh);

//ft_cd.c

void				ft_cd(t_shell *msh);

//ft_echo.c

void				ft_echo(t_shell *msh);

//ft_env.c

void				ft_env(t_shell *shell);

//ft_exit.c

void				ft_exit(t_shell *shell);

//ft_export.c

void				ft_export(t_shell *msh);
void				add_arg_to_env(char *var, t_shell *msh);

//ft_pwd.c

void				ft_pwd(void);

//ft_unset.c

void				ft_unset(t_shell *msh);

/*---------------------------- [  exec  ] ------------------------------------*/
//cmd_utils.c

char				*get_cmd_path(char *cmd, t_env *env);

//ft_executer.c

void				ft_executer(t_shell *msh);

//signal.c

void				sigint_handler(int sig);

/*------------------------ [  global_utils  ] --------------------------------*/
//env_init.c

void				ft_lst_env_init(t_env **env, char **envp);
t_env				*ft_lstnew_env(char *name, char *value, int alloc);
void				ft_lstadd_back_env(t_env **lst, t_env *new);

//env_utils.c

char				*get_env_name(char *fullenv);
char				*get_env_value(char *fullenv);

//free.c

void				ft_free_parserlist(t_parser **parser);
void				ft_free_tokenlist(t_lexer **lx);
void				ft_free_list(t_env **list);

//ft_split_shell.c

char				**ft_split_shell(t_shell *msh, char *str, char s);

/*--------------------------- [  parser  ] -----------------------------------*/
//fill_node

void				ft_fill_node(t_lexer *lex, t_parser **cmd_node, int start,
						int end);

//parser_utils.c

void				ft_index(t_lexer *lex);
int					ft_count_pipes(t_lexer *lex);
int					get_last(t_lexer *lex, int start);

//parser.c

void				ft_parser(t_parser **parser, t_lexer *lex);

/*---------------------------- [  lexer  ] -----------------------------------*/
//lexer_utils.c

int					get_type(char *str, int i);
void				lexer_add_type(t_lexer **ls, int type);
void				ft_add_token(t_lexer **lx, char *input, int i, int size);

//lexer.c

void				ft_lexer(char *input, t_lexer **lx, int *exit_status);

//treat_tokens.c

void				treat_special(char *input, t_lexer **lx, int *i, int type);
int					treat_quotes(char *input, t_lexer **lx, int *i, int *exit_status);
void				treat_general(char *input, t_lexer **lx, int *i);

//$var_env.c

void				ft_replace(t_lexer **lexer, int *exit_status);

//$var_utils.c
void				process_env_substring(char **dollar_pos, char **str,
						char **sufix, char **env_value);
void				ft_erase_node(t_lexer **lexer);

#endif
