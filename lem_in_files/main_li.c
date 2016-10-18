/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_li.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 16:05:40 by jplevy            #+#    #+#             */
/*   Updated: 2016/10/17 19:00:34 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common_files/lem_in.h"

void	ft_print_fourm(t_fourm f)
{
	t_list	*tmp;
	t_list	*tmp1;

	tmp = f.room;
	tmp1 = f.comm;
	printf("%d\n", f.nb);
	while (tmp)
	{
		if (tmp == f.start)
			ft_putendl("##start");
		else if (tmp == f.end)
			ft_putendl("##end");
		while ((tmp1) && ((t_comm*)(tmp1->content))->room == tmp)
		{
			ft_putendl(((t_comm*)(tmp1->content))->comm);
			tmp1 = tmp1->next;
		}
		printf("%s %d %d\n", ((t_room*)(tmp->content))->name, \
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
		printf("%s-%s\n", ((t_room*)((((t_link*)(tmp->content))->r1)\
		->content))->name, ((t_room*)((((t_link*)(tmp->content))->r2)\
		->content))->name);
		tmp = tmp->next;
	}
}

int		main()
{
	t_fourm	f;

	f = ft_parse();
	if (f.nb <= 0 || !(f.start) || !(f.end) || !(f.room) || !(f.link))
		ft_error();
	ft_print_fourm(f);
	return (0);
}