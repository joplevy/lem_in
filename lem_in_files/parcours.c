/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcours.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 17:18:48 by jplevy            #+#    #+#             */
/*   Updated: 2016/11/06 18:36:38 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common_files/lem_in.h"

void	ft_print_links(t_list *link, t_list *tmp1)
{
	t_list	*tmp;

	tmp = link;
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
	ft_print_links(f.link, tmp1);
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
		if (((t_link*)(tmp->content))->r1 == ref && ((t_room*)((t_list*)\
		((((t_link*)(tmp->content))->r2))->content))->m == -1)
		{
			((t_room*)((t_list*)((((t_link*)(tmp->content))->r2))->content))\
			->m = i;
			ft_lstadd_back(&ret, ft_new_r(((t_link*)(tmp->content))->r2));
		}
		else if (((t_link*)(tmp->content))->r2 == ref && ((t_room*)((t_list*)\
		((((t_link*)(tmp->content))->r1))->content))->m == -1)
		{
			((t_room*)((t_list*)((((t_link*)(tmp->content))->r1))->content))\
			->m = i;
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
		bros = ft_get_childs(((t_list*)(tmp->content)), f, ((t_room*)\
		(((t_list*)(tmp->content))->content))->m + 1);
		ft_lstadd_back(&queue, bros);
		tmp = tmp->next;
	}
}
