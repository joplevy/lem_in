/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 16:22:39 by jplevy            #+#    #+#             */
/*   Updated: 2016/10/16 20:27:15 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <stdlib.h>
# include <stdio.h>

typedef struct		s_fourm
{
	int				nb;	
	t_list			*room;
	t_list			*comm;
	t_list			*start;
	t_list			*end;
	t_list			*link;
}					t_fourm;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
}					t_room;

typedef struct		s_comm
{
	char			*comm;
	t_list			*room;
	t_list			*link;
}					t_comm;

typedef struct		s_link
{
	t_list			*r1;
	t_list			*r2;
}					t_link;
typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;
/*
** bonus_files
*/
/*
** 		main_bo.c
*/
int					my_key_func(int keycode, void *param);

/*
** common_files
*/
/*
** 		parse.c
*/
t_fourm				ft_parse(void);

#endif