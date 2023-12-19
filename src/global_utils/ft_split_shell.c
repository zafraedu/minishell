#include "minishell.h"

static int	ft_cwords(char *str, char s);
static int	ft_foundword(char *str, char s, int *i);
static int	ft_foundquotes(char *str, int *i);

/**
 * @brief Divide una cadena en fragmentos utilizando un delimitador y elimina
 * las comillas.
 *
 *
 * @param msh Un puntero a la estructura de la shell.
 * @param str La cadena que se va a dividir.
 * @param s El delimitador utilizado para dividir la cadena.
 * @return Un array de cadenas (fragmentos) resultante de la división.
 */
char	**ft_split_shell(t_shell *msh, char *str, char s)
{
	int		i;
	int		is;
	int		len;
	char	**split;
	char	*aux;

	i = 0;
	is = 0;
	len = 0;
	split = ft_calloc(sizeof(char *), ft_cwords(str, s) + 1);
	while (str[i])
	{
		while (str[i] == s && str[i++] != 0)
			len++;
		if (ft_foundword(str, s, &i))
		{
			aux = ft_substr(str, len, i - len);
			split[is++] = ft_strtrim(aux, "\"\'");
			ft_memfree(aux);
			len = i;
		}
		msh->count_cmd_args = is;
	}
	return (split);
}

/**
 * @brief Cuenta el número de palabras en una cadena utilizando un delimitador.
 *
 * @param str La cadena en la que contar las palabras.
 * @param s El delimitador utilizado para contar las palabras.
 * @return El número de palabras en la cadena.
 */
static int	ft_cwords(char *str, char s)
{
	int	i;
	int	nwords;

	i = 0;
	nwords = 0;
	while (str[i])
	{
		while (str[i] == s && str[i] != 0)
			i++;
		if (str[i] != 0)
			nwords += ft_foundword(str, s, &i);
		if (str[i] != 0)
			ft_foundquotes(str, &i);
	}
	return (nwords);
}

/**
 * @brief Determina si se ha encontrado una palabra en una cadena.
 *
 * @param str La cadena en la que buscar la palabra.
 * @param s El delimitador utilizado para determinar el final de la palabra.
 * @param i Un puntero al índice utilizado para recorrer la cadena y actualizar
 * la posición actual después de encontrar la palabra.
 * @return 1 si se ha encontrado una palabra, 0 en caso contrario.
 */
static int	ft_foundword(char *str, char s, int *i)
{
	if (str[*i] != s && str[*i] != 0)
	{
		while (str[*i] != 0 && str[*i] != s)
		{
			ft_foundquotes(str, i);
			*i = *i + 1;
		}
		return (1);
	}
	return (0);
}

/**
 * @brief Determina si se han encontrado comillas simples/dobles en una cadena.
 *
 * @param str La cadena en la que buscar las comillas.
 * @param i Un puntero al índice utilizado para recorrer la cadena y actualizar
 * la posición actual después de encontrar las comillas.
 * @return 1 si se han encontrado comillas, 0 en caso contrario.
 */
static int	ft_foundquotes(char *str, int *i)
{
	char	com;

	com = 0;
	if ((str[*i] == '\'' || str[*i] == '"') && str[*i] != 0)
	{
		com = str[*i];
		*i = *i + 1;
		while (str[*i] != 0 && str[*i] != com)
			*i = *i + 1;
		return (1);
	}
	return (0);
}
