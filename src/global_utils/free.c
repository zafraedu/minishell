#include "minishell.h"

void	ft_free_parserlist(t_parser **parser)
{
	t_parser	*tmp;

	while (*parser)
	{
		tmp = (*parser)->next;
		ft_memfree((*parser)->cmd);
		ft_memfree(*parser);
		*parser = tmp;
	}
	*parser = NULL;
}

void	ft_free_tokenlist(t_lexer **lexer)
{
	t_lexer	*tmp;

	while (*lexer)
	{
		tmp = (*lexer)->next;
		ft_memfree((*lexer)->data);
		ft_memfree(*lexer);
		*lexer = tmp;
	}
	*lexer = NULL;
}

void	ft_free_list(t_env **list)
{
	t_env	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		ft_memfree((*list)->var_name);
		ft_memfree((*list)->value_var);
		ft_memfree((*list));
		*list = tmp;
	}
	*list = NULL;
}
