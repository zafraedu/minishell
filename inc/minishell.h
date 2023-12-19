#ifndef MINISHELL_H
# define MINISHELL_H
/*═══════════════════════════ [  VAR GLOBAL  ] ═══════════════════════════════*/

extern int	g_signal;

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
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/*═══════════════════════════ [  MACROS  ] ═══════════════════════════════════*/
//errors
# define ERR_CMD "Command not found\n" // @return Command not found
# define ERR_PIPE "Pipe error\n" // @return Pipe error
//message display
# define READLINE_MSG "\033[1;36mminishell\033[34m$> \033[0m"
# define HEREDOC_MSG "\033[1;34m> \033[0m" // @return >

/*═══════════════════════════ [  ENUMS  ] ════════════════════════════════════*/
/**
 * @enum e_signal
 *
*/
typedef enum e_signal
{
	S_BASE,
	S_HEREDOC,
	S_HEREDOC_END,
	S_SIGINT,
	S_SIGINT_CMD,
	S_CMD,
	S_CANCEL_EXEC,
	S_SIZE
}			t_signal;

/**
 * @enum e_token
 * @brief Enumeración que representa los tipos de tokens utilizados en el
 * análisis léxico.
 */
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
}			t_token;
/*══════════════════════════ [  STRUCTS  ] ═══════════════════════════════════*/
/**
 * @struct s_env
 * @brief Estructura que representa un nodo en la lista de variables de entorno.
 *
 * Esta estructura almacena información sobre una variable de entorno,
 * incluyendo su nombre, valor, y una referencia al siguiente elemento en la
 * lista.
 */
typedef struct s_env
{
	char *var_name;     // nombre de la variable
	char *value_var;    // valor de la variable
	struct s_env *next; //  siguiente elemento en la lista
}			t_env;

/**
 * @struct s_lexer
 * @brief Estructura que representa un nodo en la lista de análisis léxico.
 *
 * Esta estructura almacena información sobre un token, incluyendo su índice,
 * contenido (valor literal), un número equivalente al tipo de token (enum), y
 * una referencia al siguiente elemento en la lista.
 */
typedef struct s_lexer
{
	int index;            //  indice del token
	char *data;           //  contenido (valor literal)
	int type;             //  numero equivalente al token (enum)
	struct s_lexer *next; //  siguiente elemento en la lista
}			t_lexer;

/**
 * @struct s_parser
 * @brief Estructura que representa un nodo en la lista de análisis sintáctico.
 *
 * Esta estructura almacena información sobre un comando que será ejecutado,
 * así como configuraciones de redirección de entrada y salida, y una referencia
 * al siguiente elemento en la lista.
 */
typedef struct s_parser
{
	char *cmd;             // comando que será ejecutado
	int redir_in;          // redireccionamiento de entrada
	int redir_out;         // redireccionamiento de salida
	struct s_parser *next; //  siguiente elemento en la lista
}			t_parser;

/**
 * @struct s_shell
 * @brief Estructura que representa el estado de la shell.
 *
 * Esta estructura contiene información esencial sobre el estado de la shell,
 * incluyendo variables de entorno, argumentos del comando, nodos para el
 * análisis léxico y sintáctico, y el estado de salida.
 */
typedef struct s_shell
{
	char **paths;       // variables de entorno del sistema
	char **cmd_args;    // comando seguido de argumentos
	int count_cmd_args; // cantidad de comando + argumentos
	t_env *env;         // lista de nodos que representa `envp`
	t_lexer *lexer;     // lista de nodos que separa los tokens
	t_parser *parser;   // lista de nodos que separa los comandos
	int exit_status;    // entero que representa el estado de salida
}			t_shell;

/*═════════════════════════ [  FUNCTIONS  ] ══════════════════════════════════*/
/*-------------------------- [  bultins  ] -----------------------------------*/
// built.c

int			is_builtin(t_shell *msh);
void		ft_builtin(t_shell *msh);

// ft_cd.c

void		ft_cd(t_shell *msh);

// ft_echo.c
void		ft_echo(t_shell *msh);

// ft_env.c

void		ft_env(t_shell *shell);

// ft_exit.c

void		ft_exit(t_shell *shell);

// ft_export_utils.c

void		add_arg_to_env(char *var, t_shell *msh);

// ft_export.c

void		ft_export(t_shell *msh);

//ft_pwd.c

void		ft_pwd(t_shell *msh);

//ft_unset.c

void		ft_unset(t_shell *msh);

/*---------------------------- [  exec  ] ------------------------------------*/
//cmd_utils.c

char		*get_cmd_path(char *cmd, t_env *env);
char		**env_to_array(t_shell *info);

//ft_executer.c

void		ft_executer(t_shell *msh);

//signal.c

void		signal_init(void);

/*------------------------ [  global_utils  ] --------------------------------*/
//env_utils.c

char		*get_env_name(char *fullenv);
char		*get_env_value(char *fullenv);
void		ft_lst_env_init(t_env **env, char **envp);
t_env		*ft_lstnew_env(char *name, char *value, int alloc);
void		ft_lstadd_back_env(t_env **lst, t_env *new);

//free.c

void		ft_free_parserlist(t_parser **parser);
void		ft_free_tokenlist(t_lexer **lx);
void		ft_free_list(t_env **list);

//ft_split_shell.c

char		**ft_split_shell(t_shell *msh, char *str, char s);

/*---------------------------- [  lexer  ] -----------------------------------*/
//lexer_utils.c

int			get_type(char *str, int i);
void		lexer_add_type(t_lexer **ls, int type);
void		ft_add_token(t_lexer **lx, char *input, int i, int size);
char		*ft_find(char *str, t_shell *msh);

//lexer.c

void		ft_lexer(char *input, t_lexer **lx, int *exit_status);

//treat_tokens.c

void		treat_special(char *input, t_lexer **lx, int *i, int type);
int			treat_quotes(char *input, t_lexer **lx, int *i, int *exit_status);
void		treat_general(char *input, t_lexer **lx, int *i);

//$var_env.c

void		ft_replace(t_shell *msh);

//$var_utils.c
char		*process_env_substring(char **dollar_pos, char **sufix,
				t_shell *msh);
void		ft_erase_node(t_lexer **lexer);

/*--------------------------- [  parser  ] -----------------------------------*/
//fill_node.c

void		ft_fill_node(t_lexer *lex, t_parser **cmd_node, int start, int end);

//heredoc.c

int			ft_heredoc(char *limit);

//parser_utils.c

void		ft_index(t_lexer *lex);
int			ft_count_pipes(t_lexer *lex);
int			get_last(t_lexer *lex, int start);

//parser.c

void		ft_parser(t_parser **parser, t_lexer *lex);

#endif
