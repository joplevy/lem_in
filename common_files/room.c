/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 17:44:51 by joeyplevy         #+#    #+#             */
/*   Updated: 2016/11/06 18:51:17 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*ft_room_init(void)
{
	t_room	*ret;

	if (!(ret = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	ret->name = NULL;
	ret->x = -1;
	ret->y = -1;
	ret->m = -1;
	return (ret);
}

t_room	*ft_new_room(char *buff)
{
	t_room	*ret;
	char	*tmp;
	int		i;
	int		j;

	ret = ft_room_init();
	i = 0;
	while (buff[i] != ' ')
		i++;
	if ((tmp = (char*)malloc(i + 1)))
	{
		j = -1;
		while (++j < i)
			tmp[j] = buff[j];
		tmp[j] = '\0';
		ret->name = tmp;
		ret->x = (ft_isnb(buff + i + 1, ' ') == 1) ? ft_atoi(buff + i) : -1;
		while (buff[++i] != ' ')
			;
		ret->y = (ft_isnb(buff + i + 1, ' ') == 1) ? ft_atoi(buff + i) : -1;
	}
	return (ret);
}

t_list	*ft_check_room(char *new, t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(new, ((t_room*)(tmp->content))->name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int		ft_get_rooms(t_fourm *fourm, char *buff, t_coord *s, t_list *c)
{
	t_list	*room;

	room = ft_lstnew(ft_new_room(buff), sizeof(t_room));
	if (ft_check_room(((t_room*)(room->content))->name, fourm->room) != NULL)
		return (0);
	ft_lstadd_back(&(fourm->room), room);
	if ((s->x == 1 && s->y == 1) || s->x > 1 || s->y > 1 || \
	(s->x == 1 && (fourm->start)) || (s->y == 1 && (fourm->end)))
		return (0);
	if (s->x == 1)
	{
		s->x = 0;
		fourm->start = room;
	}
	if (s->y == 1)
	{
		s->y = 0;
		fourm->end = room;
	}
	if (c)
	{
		ft_lstadd_back(&(fourm->comm), c);
		ft_put_comm(fourm->comm, room, 'r');
	}
	return (1);
}
