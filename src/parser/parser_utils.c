#include "minishell.h"

void	ft_index(t_lexer *lex)
{
	t_lexer	*tmp;
	int		i;

	tmp = lex;
	i = 0;
	while (tmp)
	{
		tmp->index = i;
		tmp = tmp->next;
		i++;
	}
}

int	ft_count_pipes(t_lexer *lex)
{
	t_lexer	*tmp;
	int		i;

	tmp = lex;
	i = 0;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	get_last(t_lexer *lex, int start)
{
	t_lexer	*tmp;
	int		last_index;

	last_index = -1;
	tmp = lex;
	while (tmp && tmp->next)
	{
		if (tmp->type == T_PIPE && tmp->index > start)
			return (tmp->index - 1);
		tmp = tmp->next;
	}
	last_index = tmp->index;
	return (last_index);
}

void	ft_free_parserlist(t_parser **parser)
{
	t_parser	*tmp;

	while (*parser)
	{
		tmp = (*parser)->next;
		free((*parser)->cmd);
		//free((*parser)->heredoc);
		free(*parser);
		*parser = tmp;
	}
	*parser = NULL;
}
