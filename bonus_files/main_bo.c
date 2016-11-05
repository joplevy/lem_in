/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 16:03:19 by jplevy            #+#    #+#             */
/*   Updated: 2016/10/24 03:48:30 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common_files/lem_in.h"

int		ft_check_arrived(t_mlx *mlx)
{
	t_list	*tmp;

	tmp = mlx->fourms;
	while (tmp)
	{
		if (tmp->content != mlx->f.end)
		{
			ft_putendl("Whoops seems like some ant get lost");
			return (0);
		}
		tmp = tmp->next;
	}
	ft_putendl("Victory ! All ants on the final room !");
	return (0);
}

int		my_key_func(int keycode, void *param)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 124)
		if (!(ft_put_turn(param)))
			exit(0);
	return (0);
}

int		main(void)
{
	t_mlx	mlx;

	mlx.f = ft_parse();
	if (mlx.f.nb <= 0 || !(mlx.f.start) || !(mlx.f.end) || !(mlx.f.room) || !(mlx.f.link) \
		|| ft_get_doubles(mlx.f.room) == 1)
		ft_error();
	mlx.scale = ft_get_scale(mlx.f.room);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1600, 800, "lem_in graphical viem");
	ft_init_map(mlx.mlx, mlx.win, mlx.f, mlx.scale);	
	mlx.img = mlx_new_image(mlx.mlx, 1600, 800);
	mlx.p = mlx_get_data_addr(mlx.img, &(mlx.bpp), &(mlx.sl), &(mlx.endian));
	mlx.fourms = ft_init_fourms(mlx.f.nb, mlx.f.start);
	ft_img_init(&mlx);
	ft_put_fourms(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_key_hook(mlx.win, my_key_func, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}