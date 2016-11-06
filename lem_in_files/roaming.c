/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roaming.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 17:27:12 by jplevy            #+#    #+#             */
/*   Updated: 2016/11/06 18:39:51 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common_files/lem_in.h"

int		ft_is_arrived(t_fourm f, t_list *ants)
{
	t_list	*tmp;

	tmp = ants;
	while (tmp)
	{
		if (tmp->content != f.end)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

t_list	*ft_get_possible(t_list *ref, t_fourm f)
{
	t_list	*ret;
	t_list	*tmp;

	tmp = f.link;
	ret = NULL;
	while (tmp)
	{
		if (((t_link*)(tmp->content))->r1 == ref && \
		((t_room*)((t_list*)((((t_link*)(tmp->content))->r2))->content))->m \
		== ((t_room*)(ref->content))->m - 1)
			ft_lstadd_back(&ret, ft_new_r(((t_link*)(tmp->content))->r2));
		else if (((t_link*)(tmp->content))->r2 == ref && \
		((t_room*)((t_list*)((((t_link*)(tmp->content))->r1))->content))->m \
		== ((t_room*)(ref->content))->m - 1)
			ft_lstadd_back(&ret, ft_new_r(((t_link*)(tmp->content))->r1));
		tmp = tmp->next;
	}
	return (ret);
}

int		ft_is_free(t_list *room, t_list *ants, t_fourm f)
{
	t_list	*tmp;

	tmp = ants;
	if (((t_list*)(room->content)) == f.end)
		return (1);
	while (tmp)
	{
		if (((t_list*)(tmp->content))->content == ((t_list*)(room->content))\
		->content)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int		ft_ant_move(t_fourm f, t_list *ants, int i, int nb)
{
	t_list	*child;
	t_list	*tmp;
	t_list	*ant;
	int		j;

	ant = ants;
	j = nb;
	while (--j > 0)
		ant = ant->next;
	if (((t_list*)(ant->content)) == f.end)
		return (0);
	child = ft_get_possible(((t_list*)(ant->content)), f);
	tmp = child;
	while (tmp)
	{
		if (ft_is_free(tmp, ants, f))
		{
			ant->content = tmp->content;
			ft_putchar((i > 0) ? ' ' : '\n');
			ft_printf("L%d-%s", nb, ((t_room*)(C_LIST->content))->name);
			return (1);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	ft_roam(t_fourm f)
{
	t_list	*ants;
	t_list	*tmp;
	int		i;
	int		nb;

	ants = ft_init_fourms(f.nb, f.start);
	while (ft_is_arrived(f, ants) != 1)
	{
		i = 0;
		tmp = ants;
		nb = 0;
		while (tmp)
		{
			if (ft_ant_move(f, ants, i, ++nb))
				i++;
			tmp = tmp->next;
		}
	}
	ft_putchar('\n');
}
