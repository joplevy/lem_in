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

t_list	*ft_get_room(t_mlx *mlx, char *room)
{
	t_list	*tmp;

	tmp = mlx->f.room;
	while (tmp)
	{
		if (ft_strcmp(room, ((t_room*)(tmp->content))->name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int		ft_is_linked(t_list *r1, t_list *r2, t_list *links)
{
	t_list	*tmp;
	t_list	*rr1;
	t_list	*rr2;

	tmp = links;
	while (tmp)
	{
		rr1 = ((t_link*)(tmp->content))->r1;
		rr2 = ((t_link*)(tmp->content))->r2;
		if ((rr1 == r1 && rr2 == r2)\
			|| (rr1 == r2 && rr2 == r1))
			return (1);
		tmp = tmp->next;
	}
	ft_printf("no link betwin room %s and room %s\n", ((t_room*)(r1->content))->name, ((t_room*)(r2->content))->name);
	return (0);
}

int		ft_move(t_mlx *mlx ,char *act)
{
	int		i;
	int		f;
	char	*room;
	t_list	*rlist;
	t_list	*tmp;

	i = 1;
	f = ft_atoi(act + i);
	while (ft_isdigit(act[i]))
		i++;
	room = ft_strdup(act + i + 1);
	if (act[0] != 'L' || f <= 0 || act[i] != '-' || !(rlist = ft_get_room(mlx, room)))
	{
		free(room);
		ft_printf("wrong synthax or room name in the move %s\n", act);
		return (0);
	}
	tmp = mlx->fourms;
	while (--f > 0)
	{
		if (!(tmp->next))
		{
			ft_printf("invalid ant number on move %s\n", act);
			return (0);
		}
		tmp = tmp->next;
	}
	if (!(ft_is_linked(tmp->content, rlist, mlx->f.link)))
		return (0);
	tmp->content = rlist;
	free (room);
	return (1);
}

int		ft_new_turn(t_mlx *mlx)
{
	char	*buff;
	char	**move;
	int		i;

	if (!(get_next_line(0, &buff)))
		return(0);
	move = ft_strsplit(buff, ' ');
	i = -1;
	while (move[++i])
	{
		if (!(ft_move(mlx, move[i])))
			return (0);
		free(move[i]);
	}
	free(move);
	free(buff);
	return (1);
}

int		ft_put_turn(void *mlx)
{
	mlx_destroy_image(C_MLX->mlx, C_MLX->img);
	C_MLX->img = mlx_new_image(C_MLX->mlx, 1600, 800);
	C_MLX->p = mlx_get_data_addr(C_MLX->img, &(C_MLX->bpp), &(C_MLX->sl), \
		&(C_MLX->endian));
	ft_img_init(mlx);
	if (!(ft_new_turn(mlx)))
		return(0);
	ft_put_fourms(mlx);
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

t_list	*ft_new_fourm(t_list *start)
{
	t_list	*ret;

	if (!(ret = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	ret->content = start;
	ret->next = NULL;
	ret->content_size = sizeof(t_list*);
	return (ret);
}

t_list	*ft_init_fourms(int nb, t_list *start)
{
	int 	i;
	t_list	*ret;

	i = nb;
	ret = NULL;
	while (--i >= 0)
		ft_lstadd_back(&ret, ft_new_fourm(start));
	return (ret);
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