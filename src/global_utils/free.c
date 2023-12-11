#include "minishell.h"

void	ft_free_parserlist(t_parser **parser)
{
	t_parser	*tmp;

	while (*parser)
	{
		tmp = (*parser)->next;
		ft_memfree((*parser)->cmd);
		//free((*parser)->heredoc);
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
