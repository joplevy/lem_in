/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_li.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 16:05:40 by jplevy            #+#    #+#             */
/*   Updated: 2016/11/06 18:25:55 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common_files/lem_in.h"

int		main(void)
{
	t_fourm	f;

	f = ft_parse();
	if (f.nb <= 0 || !(f.start) || !(f.end) || !(f.room) || !(f.link))
		ft_error();
	ft_parcours(f.end, f);
	if (((t_room*)(f.start->content))->m == -1)
		ft_error();
	ft_print_fourm(f);
	ft_roam(f);
	return (0);
}
