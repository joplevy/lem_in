/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 19:00:08 by joeyplevy         #+#    #+#             */
/*   Updated: 2016/11/06 17:44:23 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*ft_new_fourm(t_list *start)
{
	t_list	*ret;

	if (!(ret = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	ret->content = start;
	ret->next = NULL;
	ret->content_size = sizeof(t_list*);
	return (ret);
}

t_list	*ft_init_fourms(int nb, t_list *start)
{
	int		i;
	t_list	*ret;

	i = nb;
	ret = NULL;
	while (--i >= 0)
		ft_lstadd_back(&ret, ft_new_fourm(start));
	return (ret);
}
