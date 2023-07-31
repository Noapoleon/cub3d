/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:01 by nlegrand          #+#    #+#             */
/*   Updated: 2023/07/31 16:34:16 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// NOT THE ACTUAL PROJECT
// just testing the makefile

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	printf("hello world\n");
	ft_printf("hello world\n");

	double xpos = 9.0;
	printf("squareroot -> %lf\n", sqrt(xpos));

	void	*mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return (printf("Failed to init mlx\n"), 1);
	void	*win_ptr = NULL;
	//win_ptr = mlx_new_window(mlx_ptr, 480, 240, "hello world");
	if (win_ptr == NULL)
		return (printf("Failed to create mlx window\n"), mlx_destroy_display(mlx_ptr), free(mlx_ptr), 1); // destroy mlx_ptr
	int x, y;
	mlx_get_screen_size(mlx_ptr, &x, &y);
	printf("x -> %d && y -> %d\n", x, y);

	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	return (0);
}
