/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zafraedu <zafraedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 00:18:52 by zafraedu          #+#    #+#             */
/*   Updated: 2023/10/26 18:13:49 by zafraedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * @brief Crea una copia de un char ** y devuelve la copia
 *
 * @param array char ** a copiar
 * @return char** copiado en nueva dirección de memoria
 */
char	**ft_arraydup(char **array)
{
	char	**new_array;
	int		i;

	if (!array)
		return (NULL);
	new_array = ft_calloc(sizeof(char *), ft_arraylen(array) + 1);
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	return (new_array);
}
