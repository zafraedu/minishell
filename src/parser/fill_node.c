#include "minishell.h"

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
	//else if (tmp->type == T_HEREDOC)
	//	(*cmd_node)->heredoc = ft_strdup(tmp->next->data);
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
			if (tmp->index == *start) //@Agustin verifica si eso funciona makina -> Debería estar bien. Modifica el start para la funcion fill_cmd
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
