#include "cub3D.h"

/*
    Notes:
    Distance between rays: 60 (degrees / FOV) / 320 (rays)

    Steps:
    1. Subtract 30 degrees from the player rotation angle (FOV/2)
    2. Start at column 0
    3. While (column < 320):
        * Cast a ray
        * Trace the ray until it intersects with a wall (map[i][j] == 1)
        * Record the intersection (x,y) and the distance (ray length)
        * Add the angle increment so the ray moves to the right
             -> ray_angle += 60/320
        *

*/

//void cast_ray(double ray_angle, int column_id);

//test render rays

void    render_ray(t_cubd *cub3d, t_player *player, double ray_angle, int color)
{
    t_line *line = malloc(sizeof(t_line));
    line->begin_x = MINIMAP_SCALE * player->x;
    line->begin_y = MINIMAP_SCALE * player->y;
    line->end_x = MINIMAP_SCALE * (player->x + cos(ray_angle) * RAY_LENGHT);
    line->end_y = MINIMAP_SCALE * (player->y + sin(ray_angle) * RAY_LENGHT);
    line->color = color;
    draw_line(cub3d, line);
}
void    cast_all_rays(t_cubd *cub3d, t_player *player, int color)
{
    double  ray_angle;
    int     column_id;

    ray_angle = player->rotation_angle - FOV_ANGLE / 2;
    column_id = 0;
    while (column_id < NUM_RAYS)
    {
        //cast_ray(ray_angle, column_id);
        render_ray(cub3d, cub3d->player, ray_angle, color);
        ray_angle += FOV_ANGLE / NUM_RAYS;
        column_id++;
    }
}


/*
    Distance to Wall Hit
    1. The best way is to check for horizontal and vertical
        intersections separately.
    2. 
*/