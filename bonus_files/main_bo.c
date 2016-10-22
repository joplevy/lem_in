/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 16:03:19 by jplevy            #+#    #+#             */
/*   Updated: 2016/10/22 20:52:35 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common_files/lem_in.h"
#include <float.h>
#include <math.h>

void	ft_img_init(char **p)
{
	int		i;

	i = -1;
	while (++i < 1600 * 800 * 4)
		if ((i + 1) % 4 == 0)
			(*p)[i] = 255;
}

void	ft_put_turn(void *mlx)
{
	static int	i = -1;

	mlx_destroy_image(C_MLX->mlx, C_MLX->img);
	C_MLX->img = mlx_new_image(C_MLX->mlx, 1600, 800);
	C_MLX->p = mlx_get_data_addr(C_MLX->img, &(C_MLX->bpp), &(C_MLX->sl), \
		&(C_MLX->endian));
	ft_img_init(&(C_MLX->p));
	C_MLX->p[++i] = 255;
	C_MLX->p[++i] = 255;
	C_MLX->p[++i] = 255;
	C_MLX->p[++i] = 0;
	mlx_put_image_to_window(C_MLX->mlx, C_MLX->win, C_MLX->img, 0, 0);
}

int		my_key_func(int keycode, void *param)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 124)
		ft_put_turn(param);
	return (0);
}

int		main(void)
{
	t_fourm	f;
	t_mlx	mlx;

	f = ft_parse();
	if (f.nb <= 0 || !(f.start) || !(f.end) || !(f.room) || !(f.link) \
		|| ft_get_doubles(f.room) == 1)
		ft_error();
	mlx.scale = ft_get_scale(f.room);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1600, 800, "lem_in graphical viem");
	ft_init_map(mlx.mlx, mlx.win, f, mlx.scale);	
	mlx.img = mlx_new_image(mlx.mlx, 1600, 800);
	mlx.p = mlx_get_data_addr(mlx.img, &(mlx.bpp), &(mlx.sl), &(mlx.endian));
	ft_img_init(&(mlx.p));
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_key_hook(mlx.win, my_key_func, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}