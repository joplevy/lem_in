/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 22:48:17 by joeyplevy         #+#    #+#             */
/*   Updated: 2016/10/21 19:58:03 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common_files/lem_in.h"

int		ft_get_doubles(t_list *rooms)
{
	t_list	*tmp;
	t_list	*tmp1;

	tmp = rooms;
	while (tmp)
	{
		tmp1 = tmp->next;
		while (tmp1)
		{
			if (((t_room*)(tmp->content))->x == ((t_room*)(tmp1->content))->x\
			&& ((t_room*)(tmp->content))->y == ((t_room*)(tmp1->content))->y)
				return (1);
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

t_coord	ft_get_scale(t_list *rooms)
{
	t_coord	max;
	t_coord	ret;
	t_list	*tmp;

	max.x = 0;
	max.y = 0;
	tmp = rooms;
	while (tmp)
	{
		if (((t_room*)(tmp->content))->x > max.x)
			max.x = ((t_room*)(tmp->content))->x;
		if (((t_room*)(tmp->content))->y > max.y)
			max.y = ((t_room*)(tmp->content))->y;
		tmp = tmp->next;
	}
	ret.x = 1500 / (max.x + 1);
	ret.y = 700 / (max.y + 1);
	return (ret);
}

void	ft_put_rooms(void *mlx, void *win, t_coord scale, t_fourm rooms)
{
	t_coord	i;
	t_coord	merge;
	t_list	*tmp;
	int		color;

	i.y = 50;
	tmp = rooms.room;
	merge.x = scale.x / 5;
	merge.y = scale.y / 5;
	while (tmp)
	{
		if (tmp == rooms.start)
			color = 0x9acd32;
		else if (tmp == rooms.end)
			color = 0xb4120f;
		else
			color = 0xfece13;
		i.y = 50 + merge.y + scale.y * ((t_room*)(tmp->content))->y;
		while (i.y < 50 - merge.y + scale
			.y * (((t_room*)(tmp->content))->y + 1))
		{
			i.x = 50 + merge.x + scale.x * ((t_room*)(tmp->content))->x;
			while (i.x++ < 50 - merge.x + scale.x * (((t_room*)(tmp->content))->x + 1))
				mlx_pixel_put(mlx, win, i.x, i.y, color);
			i.y += 1;
		}
		tmp = tmp->next;
	}
}
