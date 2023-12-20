#include "minishell.h"

/**
 * @brief Procesa tokens especiales y los agrega a la lista de tokens (lexer)
 * junto con su tipo.
 *
 * Esta función procesa tokens especiales, como T_APPEND y T_HEREDOC, y los
 * agrega a la lista de tokens (lexer) junto con su tipo correspondiente.
 *
 * @param input La cadena de entrada que contiene los tokens.
 * @param lexer Un puntero al puntero inicial de la lista de tokens (lexer).
 * @param i Un puntero a la posición actual en la cadena de entrada.
 * @param type El tipo del token especial que se está procesando.
 */
void	treat_special(char *input, t_lexer **lexer, int *i, int type)
{
	if (type == T_APPEND || type == T_HEREDOC)
	{
		ft_add_token(lexer, input, *i, 2);
		lexer_add_type(lexer, type);
		(*i)++;
	}
	else
	{
		ft_add_token(lexer, input, *i, 1);
		lexer_add_type(lexer, type);
	}
	(*i)++;
}

/**
 * @brief Procesa tokens de comillas y los agrega a la lista de tokens (lexer)
 * junto con su tipo. También maneja casos de error, como comillas sin cerrar.
 *
 * @param input La cadena de entrada que contiene los tokens.
 * @param lexer Un puntero al puntero inicial de la lista de tokens (lexer).
 * @param i Un puntero a la posición actual en la cadena de entrada.
 * @param exit_status Puntero al estado de salida, que se actualiza en
 * caso de error.
 * @return 1 si las comillas están cerradas correctamente, 0 en caso de error.
 */
int	treat_quotes(char *input, t_lexer **lexer, int *i, int *exit_status)
{
	char	quote_char;
	int		j;

	quote_char = input[*i];
	j = (*i) + 1;
	while (input[j] && input[j] != quote_char)
		j++;
	if (input[j] == quote_char)
	{
		ft_add_token(lexer, input, (*i), j - (*i) + 1);
		lexer_add_type(lexer, T_GENERAL);
		(*i) = j + 1;
		return (1);
	}
	else
	{
		ft_add_token(lexer, input, (*i), j - (*i) + 1);
		lexer_add_type(lexer, T_GENERAL);
		printf("minishell: syntax error open quotes\n");
		*exit_status = 2;
		ft_free_tokenlist(lexer);
		return (0);
	}
}

/**
 * @brief Procesa tokens generales y los agrega a la lista de tokens (lexer)
 * junto con su tipo.
 *
 * @param input La cadena de entrada que contiene los tokens.
 * @param lexer Un puntero al puntero inicial de la lista de tokens (lexer).
 * @param i Un puntero a la posición actual en la cadena de entrada.
 */
void	treat_general(char *input, t_lexer **lexer, int *i)
{
	int	j;
	int	quote_char;

	j = (*i);
	while (input[j] && !ft_isspace(input[j]) && get_type(input, j) == T_GENERAL)
	{
		if (input[j] == 34 || input[j] == 39)
		{
			quote_char = input[j];
			j++;
			while (input[j] && input[j] != quote_char)
				j++;
		}
		j++;
	}
	ft_add_token(lexer, input, (*i), j - (*i));
	lexer_add_type(lexer, T_GENERAL);
	(*i) = j;
}
