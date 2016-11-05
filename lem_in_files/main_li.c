/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_li.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 16:05:40 by jplevy            #+#    #+#             */
/*   Updated: 2016/11/05 22:26:11 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common_files/lem_in.h"

void	ft_print_fourm(t_fourm f)
{
	t_list	*tmp;
	t_list	*tmp1;

	tmp = f.room;
	tmp1 = f.comm;
	ft_printf("%d\n", f.nb);
	while (tmp)
	{
		while ((tmp1) && ((t_comm*)(tmp1->content))->room == tmp)
		{
			ft_putendl(((t_comm*)(tmp1->content))->comm);
			tmp1 = tmp1->next;
		}
		ft_printf("%s %d %d\n", ((t_room*)(tmp->content))->name, \
			((t_room*)(tmp->content))->x, ((t_room*)(tmp->content))->y);
		tmp = tmp->next;
	}
	tmp = f.link;
	while (tmp)
	{
			while ((tmp1) && ((t_comm*)(tmp1->content))->link == tmp)
			{
				ft_putendl(((t_comm*)(tmp1->content))->comm);
				tmp1 = tmp1->next;
			}
		ft_printf("%s-%s\n", ((t_room*)((((t_link*)(tmp->content))->r1)\
		->content))->name, ((t_room*)((((t_link*)(tmp->content))->r2)\
		->content))->name);
		tmp = tmp->next;
	}
}

t_list	*ft_new_r(t_list *r)
{
	t_list	*ret;

	if (!(ret = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	ret->content = r;
	ret->next = NULL;
	ret->content_size = sizeof(t_list*);
	return (ret);
}

t_list	*ft_get_childs(t_list *ref, t_fourm f, int i)
{
	t_list	*ret;
	t_list	*tmp;

	tmp = f.link;
	ret = NULL;
	while (tmp)
	{
		if (((t_link*)(tmp->content))->r1 == ref && ((t_room*)((t_list*)((((t_link*)(tmp->content))->r2))->content))->m == -1)
		{
			((t_room*)((t_list*)((((t_link*)(tmp->content))->r2))->content))->m = i;
			ft_lstadd_back(&ret, ft_new_r(((t_link*)(tmp->content))->r2));
		}
		else if (((t_link*)(tmp->content))->r2 == ref && ((t_room*)((t_list*)((((t_link*)(tmp->content))->r1))->content))->m == -1)
		{
			((t_room*)((t_list*)((((t_link*)(tmp->content))->r1))->content))->m = i;
			ft_lstadd_back(&ret, ft_new_r(((t_link*)(tmp->content))->r1));
		}
		tmp = tmp->next;
	}
	return (ret);
}

void	ft_parcours(t_list *s, t_fourm f)
{
	t_list	*queue;
	t_list	*tmp;
	t_list	*bros;

	queue = NULL;
	ft_lstadd_back(&queue, ft_new_r(s));
	tmp = queue;
	while (tmp)
	{
		if (tmp == queue)
			((t_room*)(((t_list*)(tmp->content))->content))->m = 0;
		bros = ft_get_childs(((t_list*)(tmp->content)), f, ((t_room*)(((t_list*)(tmp->content))->content))->m + 1);
		ft_lstadd_back(&queue, bros);
		tmp = tmp->next;
	}
}

int		ft_is_arrived(t_fourm f, t_list *ants)
{
	t_list	*tmp;

	tmp = ants;
	while (tmp)
	{
		if (tmp->content != f.end)
		{
			return (0);
		}
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
		((t_room*)((t_list*)((((t_link*)(tmp->content))->r2))->content))->m == ((t_room*)(ref->content))->m - 1)
			ft_lstadd_back(&ret, ft_new_r(((t_link*)(tmp->content))->r2));
		else if (((t_link*)(tmp->content))->r2 == ref && \
		((t_room*)((t_list*)((((t_link*)(tmp->content))->r1))->content))->m == ((t_room*)(ref->content))->m - 1)
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
		if (((t_list*)(tmp->content))->content == ((t_list*)(room->content))->content)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int 	ft_ant_move(t_fourm f, t_list *ants, int i, int nb)
{
	t_list	*child;
	t_list	*tmp;
	t_list	*ant;
	int		j;

	// ft_putnbr(nb);
	ant = ants;
	j = nb;
	while (--j > 0)
		ant = ant->next;
	if (((t_list*)(ant->content)) == f.end)
		return (0);
	// ft_putendl(((t_room*)(((t_list*)(ant->content))->content))->name);
	child = ft_get_possible(((t_list*)(ant->content)), f);
	tmp = child;
	while (tmp)
	{
		if (ft_is_free(tmp, ants, f))
		{
			ant->content = tmp->content;
			// ((t_list*)(ant->content))->content = ((t_list*)(tmp->content))->content;
			ft_putchar((i > 0) ? ' ' : '\n');
			ft_printf("L%d-%s ", nb, ((t_room*)(((t_list*)(tmp->content))->content))->name);
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
	while (ft_is_arrived(f, ants)!= 1)
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

int		main()
{
	t_fourm	f;

	f = ft_parse();
	if (f.nb <= 0 || !(f.start) || !(f.end) || !(f.room) || !(f.link))
		ft_error();
	ft_parcours(f.end, f);
	if (((t_room*)(f.start->content))->m == -1)
		ft_error();
	ft_print_fourm(f);
	ft_roam(f);
	return (0);
}