#include "minishell.h"

void	ft_next_dollar_pos(char **dollar_pos, char **str, char **sufix)
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

void	ft_no_next_dollar_pos(char **dollar_pos, char **str, char **sufix)
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

void	process_env_substring(char **dollar_pos, char **str, char **sufix,
		char **env_value)
{
	char	*next_dollar_pos;

	next_dollar_pos = ft_strchr(*dollar_pos + 1, '$');
	if (next_dollar_pos)
		ft_next_dollar_pos(dollar_pos, str, sufix);
	else
		ft_no_next_dollar_pos(dollar_pos, str, sufix);
	*env_value = getenv(*str);
	ft_memfree(*str);
}

t_lexer	*remove_node(t_lexer **lexer, t_lexer *tmp, t_lexer *prev)
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
