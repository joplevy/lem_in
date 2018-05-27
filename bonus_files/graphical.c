/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 16:03:19 by jplevy            #+#    #+#             */
/*   Updated: 2016/11/06 18:21:05 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common_files/lem_in.h"

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
			(C_MLX->p)[i] = (char)255;
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

void	ft_put_fourms(t_mlx *mlx)
{
	t_list	*tmp;
	int		pos;

	tmp = mlx->fourms;
	while (tmp)
	{
		pos = 1600 * (mlx->scale.y * ((t_room*)(((t_list*)(tmp->content))->\
			content))->y + 50 + mlx->scale.y / 2) * 4 + (mlx->scale.x * \
			((t_room*)(((t_list*)(tmp->content))->content))->x + 50 + \
			mlx->scale.x / 2) * 4;
		ft_print_cross(&(mlx->p), pos, 0x2D1E8D);
		tmp = tmp->next;
	}
}

void	ft_write_turn(char *str, void *mlx)
{
	int		i;
	int		j;

	j = 0;
	while (j <= 20)
	{
		i = -1;
		while (++i <= (int)ft_strlen(str) * 10)
			mlx_pixel_put(C_MLX->mlx, C_MLX->win, 80 + i, 110 + j, 0);
		j++;
	}
	mlx_string_put(C_MLX->mlx, C_MLX->win, 10, 110, 0xFFFFFF, "turn :");
	mlx_string_put(C_MLX->mlx, C_MLX->win, 80, 110, 0xFFFFFF, str);
}

int		ft_put_turn(void *mlx)
{
	static int	t = 0;
	char		*str;

	mlx_destroy_image(C_MLX->mlx, C_MLX->img);
	C_MLX->img = mlx_new_image(C_MLX->mlx, 1600, 800);
	C_MLX->p = mlx_get_data_addr(C_MLX->img, &(C_MLX->bpp), &(C_MLX->sl), \
		&(C_MLX->endian));
	ft_img_init(mlx);
	if (!(ft_new_turn(mlx)))
		return (0);
	ft_put_fourms(mlx);
	str = ft_itoa(++t);
	ft_write_turn(str, mlx);
	free(str);
	mlx_put_image_to_window(C_MLX->mlx, C_MLX->win, C_MLX->img, 0, 0);
	return (1);
}
