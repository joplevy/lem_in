/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:15:32 by joeyplevy         #+#    #+#             */
/*   Updated: 2016/10/22 18:58:50 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_error(void)
{
	ft_putendl("error");
	exit (0);
}

int		ft_isnb(char *str, char end)
{
	while (*str != end && *str)
	{
		if (!(ft_isdigit(*str)))
			return (0);
		str++;
	}
	return (1);
}

void	ft_swap_point(t_coord *a, t_coord *b)
{
	t_coord	*tmp;

	tmp = malloc(sizeof(t_coord));
	tmp->x = a->x;
	tmp->y = a->y;
	a->x = b->x;
	a->y = b->y;
	b->x = tmp->x;
	b->y = tmp->y;
	free(tmp);
}
