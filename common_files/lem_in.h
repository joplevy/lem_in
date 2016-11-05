/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:02:35 by joeyplevy         #+#    #+#             */
/*   Updated: 2016/10/24 03:09:37 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"
# include <stdlib.h>
# include <float.h>
# include <math.h>
# define C_MLX ((t_mlx*)(mlx))

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
	int				m;
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

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*p;
	int				bpp;
	int				sl;
	int				endian;
	t_coord			scale;
	t_fourm			f;
	t_list			*fourms;
}					t_mlx;

/*
** bonus_files
*/
/*
** 		main_bo.c
*/
int					my_key_func(int keycode, void *param);
int					ft_check_arrived(t_mlx *mlx);

/*
** 		print_rooms.c
*/
void				ft_put_rooms(void *mlx, void *win, t_coord scale, t_fourm rooms);
t_coord				ft_get_scale(t_list *rooms);
int					ft_get_doubles(t_list *rooms);

/*
** 		map.c
*/
void				ft_draw_high_line(void *mlx, void *win, t_coord p1, t_coord p2);
void				ft_draw_line(void *mlx, void *win, t_coord p1, t_coord p2);
void				ft_put_links(void *mlx, void *win, t_coord scale, t_list *links);
void				ft_init_map(void *mlx, void *win, t_fourm f, t_coord scale);

/*
** 		graphical.c
*/
void				ft_print_cross(char **p, int pos, int col);
void				ft_img_init(void *mlx);
void				ft_put_fourms(t_mlx *mlx);
void				ft_write_turn(char *str, void *mlx);
int					ft_put_turn(void *mlx);

/*
** 		moves.c
*/
t_list				*ft_get_room(t_mlx *mlx, char *room);
int					ft_is_linked(t_list *r1, t_list *r2, t_list *links);
int					ft_move(t_mlx *mlx ,char *act);
int					ft_new_turn(t_mlx *mlx);

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
void				ft_swap_point(t_coord *a, t_coord *b);

/*
** 		ant.c
*/
t_list				*ft_new_fourm(t_list *start);
t_list				*ft_init_fourms(int nb, t_list *start);

#endif