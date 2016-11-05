/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_li.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 16:05:40 by jplevy            #+#    #+#             */
/*   Updated: 2016/10/21 19:22:36 by joeyplevy        ###   ########.fr       */
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

t_list	*ft_get_linked_rooms(t_list *ref, t_fourm f)
{
	t_list	*ret;
	t_list	*tmp;

	tmp = f.link;
	ret = NULL;
	while (tmp)
	{
		if (((t_link*)(tmp->content))->r1 == ref)
			ft_lstadd_back(&ret, ft_new_r(((t_link*)(tmp->content))->r2));
		else if (((t_link*)(tmp->content))->r2 == ref)
			ft_lstadd_back(&ret, ft_new_r(((t_link*)(tmp->content))->r1));
		tmp = tmp->next;
	}
	return (ret);
}
 // ParcoursLargeur(Graphe G, Sommet s):
 //       f = CreerFile();
 //       f.enfiler(s);
 //       marquer(s);
 //       tant que la file est non vide
 //                s = f.defiler();
 //                afficher(s);
 //                pour tout voisin t de s dans G
 //                         si t non marqué
 //                                 f.enfiler(t);
 //                                 marquer(t);
void	ft_parcours(t_list *s, t_fourm f, t_list *bros, int i)
{
	t_list	*queue;
	t_list	*tmp;

	queue = NULL;
	ft_lstadd_back(&queue, ft_new_r(s));
	ft_lstadd_back(&queue, bros);
	tmp = queue;
	while (tmp)
	{
		if (((t_room*)(((t_list*)(tmp->content))->content))->m == -1)
		{
			((t_room*)(((t_list*)(tmp->content))->content))->m = i;
			ft_printf("room %s, dist = %d\n", ((t_room*)(((t_list*)(tmp->content))->content))->name, i);
			ft_parcours(((t_list*)(tmp->content)), f, ft_get_linked_rooms(s, f), i + 1);
		}
		tmp = tmp->next;
	}
}

int		main()
{
	t_fourm	f;

	f = ft_parse();
	ft_parcours(f.end, f, NULL, 0);
	if (f.nb <= 0 || !(f.start) || !(f.end) || !(f.room) || !(f.link))
		ft_error();
	// ft_print_fourm(f);
	return (0);
}