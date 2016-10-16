/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 17:46:08 by jplevy            #+#    #+#             */
/*   Updated: 2016/10/16 20:18:21 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_isnb(char *str, char end)
{
	while (*str != end)
	{
		if (!(ft_isdigit(*str)))
			return (0);
		str++;
	}
	return (1);
}

t_fourm	ft_fourm_init(void)
{
	t_fourm	ret;

	ret.nb = 0;
	ret.room = NULL;
	ret.comm = NULL;
	ret.start = NULL;
	ret.end = NULL;
	ret.link = NULL;
	return (ret);
}

t_room	*ft_new_room(char *buff)
{
	t_room	*ret;
	char	*tmp;
	int		i;
	int		j;

	if(!(ret = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	i = 0;
	ret->name = NULL;
	ret->x = -1;
	ret->y = -1;
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
	// printf("r|%p|\n", ret);
	return (ret);
}

t_comm	*ft_new_comm(char *buff)
{
	t_comm	*ret;

	if(!(ret = (t_comm*)malloc(sizeof(t_comm))) || !(ret->comm = ft_strdup(buff)))
		return (NULL);
	ret->room = NULL;
	ret->link = NULL;
	return (ret);
}

t_link	*ft_new_link(t_list *r1, t_list *r2)
{
	t_link	*ret;

	if(!(ret = (t_link*)malloc(sizeof(t_link))))
		return (NULL);
	ret->r1 = r1;
	ret->r2 = r2;
	return (ret);
}

void	ft_put_comm(t_list *comm, t_list *l, char t)
{
	t_list *tmp;

	tmp = comm;
	while (tmp)
	{
		if (!(((t_comm*)(tmp->content))->room) && !(((t_comm*)(tmp->content))->link))
		{
			if (t == 'r')
				((t_comm*)(tmp->content))->room = l;
			else
				((t_comm*)(tmp->content))->link = l;
		}
		tmp = tmp->next;
	}
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
	if ((s->x == 1 && s->y == 1) || s->x > 1 || s->y > 1)
		return (0);
	if (s->x == 1)
	{
		s->x = 0;
		if ((fourm->start))
			return (0);
		fourm->start = room;
	}
	if (s->y == 1)
	{
		s->y = 0;
		if ((fourm->end))
			return (0);
		fourm->end = room;
	}
	if (c)
	{
		ft_lstadd_back(&(fourm->comm), c);
		ft_put_comm(fourm->comm, room, 'r');
	}
	return (1);
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


int		ft_get_fourm(t_fourm *fourm)
{
	char	*buff;
	t_coord	s;
	t_list	*c;

	s.x = 0;
	s.y = 0;
	c = NULL;
	while (get_next_line(0, &buff) && ft_strlen(buff) > 0)
	{
		if (ft_strcmp(buff, "##start") == 0)
			(s.x)++;
		else if (ft_strcmp(buff, "##end") == 0)
			(s.y)++;
		else if (buff[0] == '#')
			ft_lstadd_back(&c, ft_lstnew(ft_new_comm(buff), sizeof(t_comm)));
		else if (ft_strchr(buff, ' ') != NULL)
		{
			if (!(ft_get_rooms(fourm, buff, &s, c)) || (fourm->link))
				return (0);
			c = NULL;
		}
		else if (ft_strchr(buff, '-') != NULL)
		{
			if (!(ft_get_link(fourm, buff, c)))
				return (0);
			c = NULL;
		}
		else
		{
			ft_putendl(buff);
			return (0);
		}
		free(buff);
	}
	return (1);
}

t_fourm	ft_parse(void)
{
	t_fourm	ret;
	char	*buff;
	t_list	*tmp;

	ret = ft_fourm_init();
	if (get_next_line(0, &buff))
	{
		if (ft_isnb(buff, '\0'))
		{
			ret.nb = ft_atoi(buff);
			if (ft_get_fourm(&ret) == 0)
			{
				ret.nb = -1;
				return (ret);
			}
			tmp = ret.comm;
			while (tmp)
			{
				printf("comment : %s on link %s-%s\n", ((t_comm*)(tmp->content))->comm, ((t_room*)((((t_link*)((((t_comm*)(tmp->content))->link)->content))->r1)->content))->name, ((t_room*)((((t_link*)((((t_comm*)(tmp->content))->link)->content))->r2)->content))->name);
				tmp = tmp->next;
			}
		}
		else
		{
			ret.nb = -1;
			return (ret);			
		}
		free(buff);
	}
	return (ret);
}