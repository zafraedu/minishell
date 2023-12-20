#include "minishell.h"

static void	ft_heredoc_loop(char *limit, int fd);

/**
 * @brief Ejecuta un comando heredoc para proporcionar una entrada de texto
 * hasta que se encuentre un delimitador específico.
 *
 * Esta función crea un proceso hijo para ejecutar un comando heredoc,
 * proporcionando una entrada de texto hasta que se encuentre un delimitador
 * específico. Utiliza un tubo (`pipe`) para comunicarse con el proceso hijo y
 * leer la entrada de texto desde el proceso padre.
 *
 * @param limit Puntero a la cadena que sirve como delimitador para el heredoc.
 * @return El descriptor de archivo (`fd`) que representa la entrada de texto
 * proporcionada por el heredoc.
 */
int	ft_heredoc(char *limit)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		return (ft_putendl_fd(ERR_PIPE, 2), 1);
	pid = fork();
	if (pid < 0)
		return (ft_putendl_fd(ERR_FORK, 2), 1);
	if (pid == 0)
	{
		g_signal = S_HEREDOC;
		close(fd[0]);
		ft_heredoc_loop(limit, fd[1]);
	}
	g_signal = S_HEREDOC_END;
	return (waitpid(-1, NULL, 0), close(fd[1]), fd[0]);
}

/**
 * @brief Bucle principal para la ejecución del comando heredoc, proporcionando
 * entrada de texto hasta que se encuentra un delimitador específico.
 *
 * @param limit Puntero a la cadena que sirve como delimitador para el heredoc.
 * @param fd El descriptor de archivo en el que se escribe la entrada de texto
 * proporcionada por el heredoc.
 */
static void	ft_heredoc_loop(char *limit, int fd)
{
	char	*line;

	while (1)
	{
		line = readline(HEREDOC_MSG);
		if (!line || (!ft_strncmp(limit, line, ft_strlen(limit))
				&& !ft_strncmp(limit, line, ft_strlen(line))))
			exit(EXIT_SUCCESS);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		ft_memfree(line);
	}
}
