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

typedef enum e_token_type
{
	T_PIPE,        // | pipe
	T_GREAT,       // > REDIR_OUT
	T_GREAT_GREAT, // >> APPEND
	T_LESS,        // < REDIR_IN
	T_LESS_LESS,   // << HEREDOC
	T_GENERAL,     // TEX
	T_SIZE
}			t_token_type;

/*══════════════════════════ [  STRUCTS  ] ═══════════════════════════════════*/

// estructura sujeta a cambios
typedef struct s_pipe
{
	int		src_fd;
	int		dst_fd;
	int		pipe_fd[2];
	char	**paths;
	char	**cmd_args;
	char	*cmd;
	pid_t	pid;
	int		i;
	char	*str;

}			t_pipe;

typedef struct 		t_token
{
	char			*data;
	int				type;
	struct t_token	*next;
}					t_token;

/*═════════════════════════ [  FUNCTIONS  ] ══════════════════════════════════*/
void    ft_lexer(char *input, t_token **token_list);

#endif
