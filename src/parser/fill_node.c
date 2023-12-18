#include "minishell.h"

static int	ft_heredoc(char *limit)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		return (1); //err_msg
	pid = fork();
	if (pid < 0)
		return (1); //err_msg
	if (pid == 0)
	{
		//signal
		close(fd[0]);
		while (1)
		{
			line = readline(HEREDOC_MSG);
			if (!line || (!ft_strncmp(limit, line, ft_strlen(limit))
					&& !ft_strncmp(limit, line, ft_strlen(line))))
				exit(EXIT_SUCCESS);
			ft_putstr_fd(line, fd[1]);
			ft_putchar_fd('\n', fd[1]);
			ft_memfree(line);
		}
	}
	//signal
	return (waitpid(-1, NULL, 0), close(fd[1]), fd[0]);
}

static void	ft_redirect(t_lexer *tmp, t_parser **cmd_node)
{
	int	fd;

	fd = -1; //sobra esta asignacion
	if (tmp->type == T_REDIR_IN)
	{
		fd = open(tmp->next->data, O_RDONLY);
		(*cmd_node)->redir_in = fd;
	}
	else if (tmp->type == T_REDIR_OUT)
	{
		fd = open(tmp->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		(*cmd_node)->redir_out = fd;
	}
	else if (tmp->type == T_APPEND)
	{
		fd = open(tmp->next->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		(*cmd_node)->redir_out = fd;
	}
	else if (tmp->type == T_HEREDOC)
	{
		fd = ft_heredoc(tmp->next->data);
		(*cmd_node)->redir_in = fd;
	}
}

static void	fill_redir(t_lexer *lex, t_parser **cmd_node, int *start, int end)
{
	t_lexer	*tmp;
	int		aux;

	tmp = lex;
	while (tmp && tmp->index != *start)
		tmp = tmp->next;
	aux = *start;
	while (tmp && aux <= end)
	{
		if (tmp->type == T_REDIR_IN || tmp->type == T_REDIR_OUT
			|| tmp->type == T_APPEND || tmp->type == T_HEREDOC)
		{
			if (tmp->index == *start)
				*start += 2;
			ft_redirect(tmp, cmd_node);
		}
		tmp = tmp->next;
		aux++;
	}
}

static int	ft_len_cmd(t_lexer *tmp)
{
	int	len;

	len = 0;
	while (tmp && tmp->type == T_CMD)
	{
		len += (ft_strlen(tmp->data) + 1);
		tmp = tmp->next;
	}
	return (len);
}

static void	fill_cmd(t_lexer *tmp, t_parser **cmd_node)
{
	int	len;

	len = ft_len_cmd(tmp);
	(*cmd_node)->cmd = ft_calloc(len, sizeof(char));
	while (tmp && tmp->type == T_CMD)
	{
		ft_strlcat((*cmd_node)->cmd, tmp->data, len);
		if (tmp->next && tmp->next->type == T_CMD)
			ft_strlcat((*cmd_node)->cmd, " ", len);
		tmp = tmp->next;
	}
}

void	ft_fill_node(t_lexer *lex, t_parser **cmd_node, int start, int end)
{
	t_lexer	*tmp;

	tmp = lex;
	(*cmd_node)->redir_in = STDIN_FILENO;
	(*cmd_node)->redir_out = STDOUT_FILENO;
	fill_redir(lex, cmd_node, &start, end);
	while (tmp && tmp->index != start)
		tmp = tmp->next;
	fill_cmd(tmp, cmd_node);
}
