#include "minishell.h"

static void	ft_next_dollar_pos(char **dollar_pos, char **str, char **sufix)
{
	char	*next_dollar_pos;
	char	*next_space_pos;

	next_dollar_pos = ft_strchr(*dollar_pos + 1, '$');
	next_space_pos = ft_strchr(*dollar_pos + 1, ' ');
	if (next_dollar_pos)
	{
		if (next_space_pos && (next_dollar_pos > next_space_pos))
		{
			*str = ft_substr(*dollar_pos, 1, next_space_pos - *dollar_pos - 1);
			*sufix = ft_strdup(next_space_pos);
		}
		else
		{
			*str = ft_substr(*dollar_pos, 1, next_dollar_pos - *dollar_pos - 1);
			*sufix = ft_strdup(next_dollar_pos);
		}
	}
}

static void	ft_no_next_dollar_pos(char **dollar_pos, char **str, char **sufix)
{
	char	*next_space_pos;

	next_space_pos = ft_strchr(*dollar_pos + 1, ' ');
	if (next_space_pos)
	{
		*str = ft_substr(*dollar_pos, 1, next_space_pos - *dollar_pos - 1);
		*sufix = ft_strdup(next_space_pos);
	}
	else
	{
		*str = ft_substr(*dollar_pos, 1, ft_strlen(*dollar_pos + 1));
		*sufix = "";
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

char	*process_env_substring(char **dollar_pos, char **sufix, t_shell *msh)
{
	char	*next_dollar_pos;
	char	*env_value;
	char	*str;

	next_dollar_pos = ft_strchr(*dollar_pos + 1, '$');
	if (next_dollar_pos)
		ft_next_dollar_pos(dollar_pos, &str, sufix);
	else
		ft_no_next_dollar_pos(dollar_pos, &str, sufix);
	env_value = ft_find(str, msh); //! problema (cd src; echo $PWD)
	ft_memfree(str);
	return (env_value);
}

static t_lexer	*remove_node(t_lexer **lexer, t_lexer *tmp, t_lexer *prev)
{
	t_lexer	*next;

	next = NULL;
	if (prev == NULL)
	{
		*lexer = tmp->next;
		next = *lexer;
		ft_memfree(tmp);
	}
	else
	{
		prev->next = tmp->next;
		next = prev->next;
		ft_memfree(tmp);
	}
	return (next);
}

void	ft_erase_node(t_lexer **lexer)
{
	t_lexer	*tmp;
	t_lexer	*prev;

	tmp = *lexer;
	prev = NULL;
	while (tmp)
	{
		if (tmp->data == NULL || tmp->data[0] == '\0')
			tmp = remove_node(lexer, tmp, prev);
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
