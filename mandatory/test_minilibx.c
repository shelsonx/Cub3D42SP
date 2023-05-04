/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minilibx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 20:12:10 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/05/03 22:03:04 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_images(t_game *game)
{
	game->wall.addr = mlx_xpm_file_to_image(
			game->mlx_ptr, PATH_IMG_WALL,
			&game->wall.width, &game->wall.height);
	game->space.addr = mlx_xpm_file_to_image(
			game->mlx_ptr, PATH_IMG_SPACE,
			&game->space.width, &game->space.height);
}

void	draw_image(t_game *game, t_image *img)
{
	mlx_put_image_to_window(game->mlx_ptr, game->window.win_ptr,
		img->addr, img->y * TILE_SIZE, img->x * TILE_SIZE);
}

void	render_image(t_game *game, t_image *image, int x, int y)
{
	image->x = x;
	image->y = y;
	draw_image(game, image);
}

int	set_wall_or_empty_color(t_rectangle *rect, char map_char)
{
	int	color_set;

	color_set = TRUE;
	if (map_char == WALL_CHAR)
		set_color_rect(rect, WHITE_PIXEL);
	else if (map_char == EMPTY_CHAR)
		set_color_rect(rect, BLACK_PIXEL);
	else
		color_set = FALSE;
	return (color_set);
}

int	render_rects(t_cubd *cub3d)
{
	int			x;
	int			y;
	t_rectangle	rect;

	y = 0;
	rect.color = 0;
	rect.width = TILE_SIZE * MINIMAP_SCALE;
	rect.height = TILE_SIZE * MINIMAP_SCALE;
	while (y < cub3d->map.dimensions.rows)
	{
		x = 0;
		while (x < cub3d->map.dimensions.columns)
		{
			if (set_wall_or_empty_color(&rect, cub3d->game->map[y][x]))
			{
				rect.x = x * TILE_SIZE * MINIMAP_SCALE;
				rect.y = y * TILE_SIZE * MINIMAP_SCALE;
				render_rect(cub3d, &rect);
			}
			x++;
		}
		y++;
	}
	return (TRUE);
}

int	game_render(t_cubd *cub3D)
{
	create_image(cub3D, &cub3D->game->img, WINDOW_WIDTH, WINDOW_HEIGHT);
	render_rects(cub3D);
	render_player(cub3D, cub3D->player);
	render_image_to_window(cub3D, &cub3D->game->img, 0, 0);
	mlx_destroy_image(cub3D->mlx_ptr, cub3D->game->img.mlx_img);
	return (TRUE);
}
