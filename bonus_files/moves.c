/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 16:03:19 by jplevy            #+#    #+#             */
/*   Updated: 2016/11/06 19:28:26 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common_files/lem_in.h"

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
	ft_printf("You killed an ant ! There is no link betwin room %s and room %s\
		\n", ((t_room*)(r1->content))->name, ((t_room*)(r2->content))->name);
	return (0);
}

t_list	*ft_check_ant_nb(t_list *fourms, int f, char *act)
{
	t_list	*tmp;

	tmp = fourms;
	while (--f > 0)
	{
		if (!(tmp->next))
		{
			ft_printf("Invalid ant number on move %s\n", act);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (tmp);
}

int		ft_move(t_mlx *mlx, char *act)
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
	if (act[0] != 'L' || f <= 0 || act[i] != '-' || \
		!(rlist = ft_get_room(mlx, room)))
	{
		free(room);
		ft_printf("wrong synthax or room name in the move %s\n", act);
		return (0);
	}
	if (!(tmp = ft_check_ant_nb(mlx->fourms, f, act)))
		return (0);
	if (!(ft_is_linked(tmp->content, rlist, mlx->f.link)))
		return (0);
	tmp->content = rlist;
	free(room);
	return (1);
}

int		ft_new_turn(t_mlx *mlx)
{
	char	*buff;
	char	**move;
	int		i;

	if (!(get_next_line(0, &buff)))
		return (ft_check_arrived(mlx));
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
