/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 17:46:08 by jplevy            #+#    #+#             */
/*   Updated: 2016/10/14 20:54:42 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_isnb(char *str)
{
	while (*str)
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

t_room	ft_new_room(char *buff)
{
	t_room	ret;
	int		i;

	i = 0;
	while (buff[i] != ' ')
		i++;
	ret.name = malloc(i);
	ret.name = ft_strncpy(ret.name, buff, i);
	ret.pos.x = ft_atoi(buff + i);
	while (buff[++i] != ' ')
		;
	ret.pos.y = ft_atoi(buff + i);
	return (ret);
}

void	ft_get_fourm(t_fourm *fourm)
{
	char	*buff;
	t_list	*room;
	int		s;
	int		e;
	t_list	*c;
	t_room	tr;

	ft_printf("%d\n", fourm->nb);
	s = 0;
	e = 0;
	c = NULL;
	while (get_next_line(0, &buff) && ft_strlen(buff) > 0)
	{
		if (ft_strcmp(buff, "##start") == 0)
			s = 1;
		else if (ft_strcmp(buff, "##end") == 0)
			e = 1;
		else if (buff[0] == '#')
			ft_lstadd_back(&c, ft_lstnew(buff, ft_strlen(buff)));
		else if (ft_strchr(buff, ' ') != NULL)
		{
			tr = ft_new_room(buff);
			room = ft_lstnew(&tr, sizeof(t_room));
			ft_lstadd_back(&(fourm->room), room);
			if (s == 1)
				fourm->start = room;
			if (e == 1)
				fourm->end = room;
		}
		else
			ft_putendl(buff);
		free(buff);
	}
}

t_fourm	ft_parse(void)
{
	t_fourm	ret;
	char	*buff;
	t_list	*tmp;

	ret = ft_fourm_init();
	if (get_next_line(0, &buff))
	{
		if (ft_isnb(buff))
		{
			ret.nb = ft_atoi(buff);
			ft_get_fourm(&ret);
			tmp = ret.room;
			ft_printf("start = %p, end = %p\n", ret.start, ret.end);
			while (tmp)
			{
				// ft_printf("name = %s, x = %d, y = %d, p = %p\n", ((t_room*)(tmp->content))->name, ((t_room*)(tmp->content))->pos.x, ((t_room*)(tmp->content))->pos.y, tmp);
				ft_putendl(((t_room*)(tmp->content))->name);
				tmp = tmp->next;
			}
		}
		free(buff);
	}
	return (ret);
}