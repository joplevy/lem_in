/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 17:46:08 by jplevy            #+#    #+#             */
/*   Updated: 2016/11/06 19:15:30 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int		ft_get_info(t_fourm *fourm, char *buff, t_coord *s, t_list **c)
{
	if (ft_strchr(buff, ' ') != NULL)
	{
		if (!(ft_get_rooms(fourm, buff, s, *c)) || (fourm->link))
			return (0);
		*c = NULL;
	}
	else if (ft_strchr(buff, '-') != NULL)
	{
		if (!(ft_get_link(fourm, buff, *c)) || !(fourm->start) \
			|| !(fourm->end))
			return (0);
		*c = NULL;
	}
	else
		return (0);
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
		if (ft_strcmp(buff, "##end") == 0)
			(s.y)++;
		if (buff[0] == '#')
			ft_lstadd_back(&c, ft_lstnew(ft_new_comm(buff), sizeof(t_comm)));
		else if (!(ft_get_info(fourm, buff, &s, &c)))
			return (0);
		free(buff);
	}
	return (1);
}

t_fourm	ft_parse(void)
{
	t_fourm	ret;
	char	*buff;

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
