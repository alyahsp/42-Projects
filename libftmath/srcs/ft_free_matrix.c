/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 20:42:54 by angavrel          #+#    #+#             */
/*   Updated: 2017/01/22 01:47:47 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_matrix(float **m)
{
	int	i;

	i = 0;
	while (++i < 4)
	{
			free(m[i]);
			++i;
	}
	free(m);
	m = NULL;
}
