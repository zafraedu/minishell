#include "minishell.h"

static void	ft_add_nodes(t_parser **cmd_node, t_lexer *lex)
{
	int	start;
	int	num_pipes;
	int	i;
	int	end;

	start = 0;
	num_pipes = ft_count_pipes(lex);
	i = 0;
	while (i <= num_pipes)
	{
		end = get_last(lex, start);
		ft_fill_node(lex, cmd_node, start, end);
		if (i < num_pipes)
		{
			(*cmd_node)->next = ft_calloc(1, sizeof(t_parser));
			*cmd_node = (*cmd_node)->next;
		}
		start = end + 2;
		i++;
	}
}

static void	connect_pipes(t_parser **parser)
{
	t_parser	*current;
	int			fd[2];

	current = *parser;
	while (current->next)
	{
		pipe(fd);
		if (current->redir_out == 1)
			current->redir_out = fd[1];
		current->next->redir_in = fd[0];
		current = current->next;
	}
}

void	ft_parser(t_parser **parser, t_lexer *lex)
{
	t_parser	*cmd_node;

	if (lex == NULL)
		return ;
	ft_index(lex);
	if (*parser == NULL)
		*parser = ft_calloc(1, sizeof(t_parser));
	cmd_node = *parser;
	if (cmd_node)
		ft_add_nodes(&cmd_node, lex);
	connect_pipes(parser);
}
