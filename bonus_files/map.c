/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 19:00:08 by joeyplevy         #+#    #+#             */
/*   Updated: 2016/10/22 19:02:44 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common_files/lem_in.h"

void	ft_draw_high_line(void *mlx, void *win, t_coord p1, t_coord p2)
{
	float	e;
	float	f;
	int		pm;

	if (p1.y > p2.y)
		ft_swap_point(&p1, &p2);
	pm = (p2.x > p1.x) ? 1 : 0;
	f = (((double)p1.x) - ((double)p2.x)) / (((double)p1.y) - ((double)p2.y));
	while (p1.y < p2.y)
	{
		mlx_pixel_put(mlx, win, p1.x, p1.y, 0x0FECE13);
		e = e + f;
		if ((pm == 1 && e >= 0.5) || (pm == 0 && e <= -0.5))
		{
			p1.x = (pm == 1) ? p1.x + 1 : p1.x - 1;
			e = (pm == 1) ? e - 1 : e + 1;
		}
		p1.y = p1.y + 1;
	}
}

void	ft_draw_line(void *mlx, void *win, t_coord p1, t_coord p2)
{
	float	e;
	float	f;
	int		pm;

	if (p1.x > p2.x)
		ft_swap_point(&p1, &p2);
	e = 0;
	f = (((double)p1.y) - ((double)p2.y)) / (((double)p1.x) - ((double)p2.x));
	if (f <= 1 && f >= -1)
	{
		pm = (p2.y > p1.y) ? 1 : 0;
		while (p1.x < p2.x)
		{
			mlx_pixel_put(mlx, win, p1.x, p1.y, 0x0FECE13);
			e = e + f;
			if ((pm == 1 && e >= 0.5) || (pm == 0 && e <= -0.5))
			{
				p1.y = (pm == 1) ? p1.y + 1 : p1.y - 1;
				e = (pm == 1) ? e - 1 : e + 1;
			}
			p1.x = p1.x + 1;
		}
	}
	else
		ft_draw_high_line(mlx, win, p1, p2);
}

void	ft_put_links(void *mlx, void *win, t_coord scale, t_list *links)
{
	t_list	*tmp;
	t_coord	t1;
	t_coord	t2;

	tmp = links;
	while (tmp)
	{
		t1.x = 50 + scale.x / 2 + ((t_room*)((((t_link*)(tmp->content))->r1)\
		->content))->x * scale.x;
		t1.y = 50 + scale.y / 2 + ((t_room*)((((t_link*)(tmp->content))->r1)\
		->content))->y * scale.y;
		t2.x = 50 + scale.x / 2 + ((t_room*)((((t_link*)(tmp->content))->r2)\
		->content))->x * scale.x;
		t2.y = 50 + scale.y / 2 + ((t_room*)((((t_link*)(tmp->content))->r2)\
		->content))->y * scale.y;
		ft_draw_line(mlx, win, t1, t2);
		tmp = tmp->next;
	}
}

void	ft_init_map(void *mlx, void *win, t_fourm f, t_coord scale)
{
	mlx_string_put(mlx, win, 10, 10, 0x0FECE13, "room");
	mlx_string_put(mlx, win, 10, 25, 0x09acd32, "start");
	mlx_string_put(mlx, win, 10, 40, 0x0b4120f, "end");
	mlx_string_put(mlx, win, 10, 55, 0x0FFFFFF, "right : next step");
	mlx_string_put(mlx, win, 10, 70, 0x0FFFFFF, "esc : close");
	ft_put_links(mlx, win, scale, f.link);
	ft_put_rooms(mlx, win, scale, f);
}
