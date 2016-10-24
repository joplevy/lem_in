/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 16:03:19 by jplevy            #+#    #+#             */
/*   Updated: 2016/10/24 03:48:30 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common_files/lem_in.h"
#include <float.h>
#include <math.h>

void	ft_print_cross(char **p, int pos, int col)
{
	(*p)[pos] = (col & 0xFF);
	(*p)[pos + 1] = (col & 0xFF00) >> 8;
	(*p)[pos + 2] = (col & 0xFF0000) >> 16;
	(*p)[pos + 3] = 0;
	(*p)[pos - 1601 * 4] = (col & 0xFF);
	(*p)[pos + 1 - 1601 * 4] = (col & 0xFF00) >> 8;
	(*p)[pos + 2 - 1601 * 4] = (col & 0xFF0000) >> 16;
	(*p)[pos + 3 - 1601 * 4] = 0;
	(*p)[pos - 1599 * 4] = (col & 0xFF);
	(*p)[pos + 1 - 1599 * 4] = (col & 0xFF00) >> 8;
	(*p)[pos + 2 - 1599 * 4] = (col & 0xFF0000) >> 16;
	(*p)[pos + 3 - 1599 * 4] = 0;
	(*p)[pos + 1599 * 4] = (col & 0xFF);
	(*p)[pos + 1 + 1599 * 4] = (col & 0xFF00) >> 8;
	(*p)[pos + 2 + 1599 * 4] = (col & 0xFF0000) >> 16;
	(*p)[pos + 3 + 1599 * 4] = 0;
	(*p)[pos + 1601 * 4] = (col & 0xFF);
	(*p)[pos + 1 + 1601 * 4] = (col & 0xFF00) >> 8;
	(*p)[pos + 2 + 1601 * 4] = (col & 0xFF0000) >> 16;
	(*p)[pos + 3 + 1601 * 4] = 0;
}

void	ft_img_init(void *mlx)
{
	int		i;
	int		pos;
	t_list	*tmp;
	int		color;

	i = -1;
	while (++i < 1600 * 800 * 4)
		if ((i + 1) % 4 == 0)
			(C_MLX->p)[i] = 255;
	tmp = C_MLX->f.room;
	while (tmp)
	{
		if (tmp == C_MLX->f.start)
			color = 0x9acd32;
		else if (tmp == C_MLX->f.end)
			color = 0xb4120f;
		else
			color = 0xfece13;
		pos = 1600 * (C_MLX->scale.y * ((t_room*)(tmp->content))->y \
			+ 50 + C_MLX->scale.y / 2) * 4 + (C_MLX->scale.x * \
			((t_room*)(tmp->content))->x + 50 + C_MLX->scale.x / 2) * 4;
		ft_print_cross(&(C_MLX->p), pos, color);
		tmp = tmp->next;
	}
}

int		ft_put_turn(void *mlx)
{
	mlx_destroy_image(C_MLX->mlx, C_MLX->img);
	C_MLX->img = mlx_new_image(C_MLX->mlx, 1600, 800);
	C_MLX->p = mlx_get_data_addr(C_MLX->img, &(C_MLX->bpp), &(C_MLX->sl), \
		&(C_MLX->endian));
	ft_img_init(mlx);
	mlx_put_image_to_window(C_MLX->mlx, C_MLX->win, C_MLX->img, 0, 0);
	return (1);
}

int		my_key_func(int keycode, void *param)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 124)
		if (!(ft_put_turn(param)))
			exit(0);
	return (0);
}

t_list	*ft_init_fourms(int nb, t_list *start)
{
	int 	i;
	t_list	*ret;

	i = nb;
	ret = NULL;
	while (--i >= 0)
		ft_lstadd_back(&ret, ft_lstnew(start, sizeof(t_list *)));
	return (ret);
}

void	ft_put_fourms(t_mlx *mlx)
{
	t_list	*tmp;
	int		pos;

	tmp = mlx->fourms;
	while (tmp)
	{
		pos = 1600 * (mlx->scale.y * ((t_room*)(((t_list*)(tmp->content))->content))->y \
			+ 50 + mlx->scale.y / 2) * 4 + (mlx->scale.x * \
			((t_room*)(((t_list*)(tmp->content))->content))->x + 50 + mlx->scale.x / 2) * 4;
		ft_print_cross(&(mlx->p), pos, 0xc0392b);
		tmp = tmp->next;
	}
}

int		main(void)
{
	t_mlx	mlx;

	mlx.f = ft_parse();
	if (mlx.f.nb <= 0 || !(mlx.f.start) || !(mlx.f.end) || !(mlx.f.room) || !(mlx.f.link) \
		|| ft_get_doubles(mlx.f.room) == 1)
		ft_error();
	mlx.scale = ft_get_scale(mlx.f.room);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1600, 800, "lem_in graphical viem");
	ft_init_map(mlx.mlx, mlx.win, mlx.f, mlx.scale);	
	mlx.img = mlx_new_image(mlx.mlx, 1600, 800);
	mlx.p = mlx_get_data_addr(mlx.img, &(mlx.bpp), &(mlx.sl), &(mlx.endian));
	mlx.fourms = ft_init_fourms(mlx.f.nb, mlx.f.start);
	ft_img_init(&mlx);
	ft_put_fourms(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_key_hook(mlx.win, my_key_func, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}