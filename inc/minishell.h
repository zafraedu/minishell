#ifndef MINISHELL_H
# define MINISHELL_H

/*═════════════════════════════ [  LIBS  ] ═══════════════════════════════════*/
//personal libs
# include "libft/inc/libft.h"
//global libs
# include <dirent.h>
# include <fcntl.h>
# include <libgen.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
/*═══════════════════════════ [  MACROS  ] ═══════════════════════════════════*/
//errors

# define ERR_CMD "Command not found\n"
# define ERR_PIPE "Pipe error\n"

/*═══════════════════════════ [  ENUMS  ] ════════════════════════════════════*/

typedef enum e_token
{
	T_PIPE,
	T_SIZE
}			t_token;

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

/*═════════════════════════ [  FUNCTIONS  ] ══════════════════════════════════*/

#endif
