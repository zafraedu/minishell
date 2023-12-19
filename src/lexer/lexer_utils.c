#include "minishell.h"

int	get_type(char *str, int i)
{
	if (str[i] == '|')
		return (T_PIPE);
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (T_APPEND);
		return (T_REDIR_OUT);
	}
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (T_HEREDOC);
		return (T_REDIR_IN);
	}
	return (T_GENERAL);
}

void	lexer_add_type(t_lexer **lexer, int type)
{
	t_lexer	*current;

	current = *lexer;
	while (current->next != NULL)
		current = current->next;
	current->type = type;
}

void	ft_add_token(t_lexer **lexer, char *input, int i, int size)
{
	t_lexer	*new;
	t_lexer	*current;

	new = ft_calloc(1, sizeof(t_lexer));
	new->data = ft_substr(input, i, size);
	new->next = NULL;
	if (*lexer == NULL)
		*lexer = new;
	else
	{
		current = *lexer;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

char	*ft_find(char *str, t_shell *msh)
{
	t_env	*tmp;

	tmp = msh->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var_name, str))
			return (tmp->value_var);
		tmp = tmp->next;
	}
	return (NULL);
}
