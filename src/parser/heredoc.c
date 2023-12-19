#include "minishell.h"

static void	ft_heredoc_loop(char *limit, int fd);

int	ft_heredoc(char *limit)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		return (1); //err_msg
	pid = fork();
	if (pid < 0)
		return (1); //err_msg
	if (pid == 0)
	{
		g_signal = S_HEREDOC;
		close(fd[0]);
		ft_heredoc_loop(limit, fd[1]);
	}
	g_signal = S_HEREDOC_END;
	return (waitpid(-1, NULL, 0), close(fd[1]), fd[0]);
}

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
