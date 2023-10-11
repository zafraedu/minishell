/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zafraedu <zafraedu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:22:09 by ezafra-r          #+#    #+#             */
/*   Updated: 2023/10/09 00:36:17 by zafraedu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/**
 * Compara dos cadenas de caracteres.
 *
 * Esta función compara las cadenas de caracteres 's1' y 's2'. Compara cada
 * carácter de ambas cadenas hasta que encuentre una diferencia o hasta que
 * alcance el final de ambas cadenas (caracteres nulos '\0'). Devuelve un valor
 * entero que indica si 's1' es menor, igual o mayor que 's2' en función del
 * orden lexicográfico de las cadenas.
 *
 * @param s1  La primera cadena de caracteres a comparar.
 * @param s2  La segunda cadena de caracteres a comparar.
 *
 * @return Un valor entero negativo si 's1' es menor que 's2', 0 si son iguales
 * o un valor entero positivo si 's1' es mayor que 's2' en orden lexicográfico.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
