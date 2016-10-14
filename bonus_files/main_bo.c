/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <jplevy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/10 16:03:19 by jplevy            #+#    #+#             */
/*   Updated: 2016/10/14 17:48:16 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common_files/lem_in.h"

int		my_key_func(int keycode, void *param)
{
	if (keycode == 53 && param == 0)
		exit(0);
	return (0);
}

int		main(void)
{
	t_fourm	f;
	void	*mlx;
	void	*win;

	f = ft_parse();
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1600, 800, "lem_in graphical viem");
	mlx_pixel_put(mlx, win, 50, 100, 0x00FECE13);
	mlx_key_hook(win, my_key_func, 0);
	mlx_loop(mlx);
	// ft_putendl("bonus");
	return (0);
}