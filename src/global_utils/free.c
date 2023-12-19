#include "minishell.h"

/**
 * @brief Libera la memoria asociada con la lista de comandos (parser).
 *
 * @param parser Puntero al puntero al inicio de la lista de comandos (parser).
 */
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

/**
 * @brief Libera la memoria asociada con la lista de tokens (lexer).
 *
 * @param lexer Puntero al puntero al inicio de la lista de tokens (lexer).
 */
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

/**
 * @brief Libera la memoria asociada con la lista de variables de entorno.
 *
 * @param list Puntero al puntero al inicio de la lista de variables de entorno.
 */
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
