/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:02:35 by joeyplevy         #+#    #+#             */
/*   Updated: 2016/10/18 01:45:17 by joeyplevy        ###   ########.fr       */
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
** 		print_rooms.c
*/
void				ft_put_rooms(void *mlx, void *win, t_coord scale, t_list *rooms);
t_coord				ft_get_scale(t_list *rooms);
int					ft_get_doubles(t_list *rooms);

/*
** common_files
*/
/*
** 		parse.c
*/
t_fourm				ft_parse(void);
int					ft_get_fourm(t_fourm *fourm);
t_fourm				ft_fourm_init(void);

/*
** 		room.c
*/
int					ft_get_rooms(t_fourm *fourm, char *buff, t_coord *s, t_list *c);
t_list				*ft_check_room(char *new, t_list *list);
t_room				*ft_new_room(char *buff);

/*
** 		link_comm.c
*/
int					ft_get_link(t_fourm *fourm, char *buff, t_list *c);
t_link				*ft_new_link(t_list *r1, t_list *r2);
void				ft_put_comm(t_list *comm, t_list *l, char t);
t_comm				*ft_new_comm(char *buff);

/*
** 		tools.c
*/
void				ft_error(void);
int					ft_isnb(char *str, char end);
#endif