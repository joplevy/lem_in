/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 17:46:08 by jplevy            #+#    #+#             */
/*   Updated: 2016/10/21 19:23:28 by joeyplevy        ###   ########.fr       */
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
			if (!(ft_get_link(fourm, buff, c)) || !(fourm->start) || !(fourm->end))
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
			// tmp = ret.comm;
			// while (tmp)
			// {
			// 	ft_printf("comment : %s on link %s-%s\n", ((t_comm*)(tmp->content))->comm, ((t_room*)((((t_link*)((((t_comm*)(tmp->content))->link)->content))->r1)->content))->name, ((t_room*)((((t_link*)((((t_comm*)(tmp->content))->link)->content))->r2)->content))->name);
			// 	tmp = tmp->next;
			// }
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