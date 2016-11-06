/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_comm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 17:48:01 by joeyplevy         #+#    #+#             */
/*   Updated: 2016/11/06 18:25:33 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link	*ft_new_link(t_list *r1, t_list *r2)
{
	t_link	*ret;

	if (!(ret = (t_link*)malloc(sizeof(t_link))))
		return (NULL);
	ret->r1 = r1;
	ret->r2 = r2;
	return (ret);
}

int		ft_get_link(t_fourm *fourm, char *buff, t_list *c)
{
	t_list	*link;
	t_list	*r1;
	t_list	*r2;
	char	*s1;
	int		i;

	i = 0;
	while (buff[i] != '-')
		i++;
	r2 = ft_check_room(buff + i + 1, fourm->room);
	if (!(s1 = ft_strsub(buff, 0, i)))
		return (0);
	r1 = ft_check_room(s1, fourm->room);
	free(s1);
	if (!r1 || !r2)
		return (0);
	link = ft_lstnew(ft_new_link(r1, r2), sizeof(t_link));
	ft_lstadd_back(&(fourm->link), link);
	if (c)
	{
		ft_lstadd_back(&(fourm->comm), c);
		ft_put_comm(fourm->comm, link, 'l');
	}
	return (1);
}

t_comm	*ft_new_comm(char *buff)
{
	t_comm	*ret;

	if (!(ret = (t_comm*)malloc(sizeof(t_comm))))
		return (NULL);
	if (!(ret->comm = ft_strdup(buff)))
		return (NULL);
	ret->room = NULL;
	ret->link = NULL;
	return (ret);
}

void	ft_put_comm(t_list *comm, t_list *l, char t)
{
	t_list *tmp;

	tmp = comm;
	while (tmp)
	{
		if (!(((t_comm*)(tmp->content))->room) && \
			!(((t_comm*)(tmp->content))->link))
		{
			if (t == 'r')
				((t_comm*)(tmp->content))->room = l;
			else
				((t_comm*)(tmp->content))->link = l;
		}
		tmp = tmp->next;
	}
}
