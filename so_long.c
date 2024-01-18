#include "./minilibx-linux/mlx.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define BASE 64
#define INT_NONE -16777216;
#define SLEEP_TIME 750
#define GRAVITY 0.05
#define VELOCITY 0.0001
#define VELOCITY_DEF 1
#define VELOCITY_MAX 1

typedef struct s_img
{
    void *img;
    char *addr;
    int width;
    int height;
    int bpp;
    int line_length;
    int endian;
} t_img;

typedef struct s_axis
{
    int x;
    int y;
} t_axis;

typedef struct s_entity_dyn
{
    int     pos_x_y[2];
    t_axis  axis;
    double  velocity_y;
    double  velocity_x;
    int     dir;
    t_img   xpm[2];
    t_img   xpm_reset;
    int     on_dir;
    int     on_thruster;
    int     clock_x;
    int     clock_y;
} t_entity_dyn;

typedef struct s_entity_stc
{
    t_axis   axis;
    t_img   xpm;
    int     on_display;

} t_entity_stc;

typedef struct s_ground
{
    t_axis   axis;
    int     size;
} t_ground;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
    t_entity_dyn player;
    t_entity_dyn spaceship;
    t_entity_stc object[4];
    int     object_find;
    int     entity_toggler;
    t_img   ground_xpm[4];
    int     ground_size;
    t_ground   ground[2];
    time_t  time_last_frame;
}				t_vars;

void    load_xpm(t_vars *vars, t_img *xpm, char *file_path)
{
    xpm->img = mlx_xpm_file_to_image(vars->mlx, file_path, &xpm->width, &xpm->height);
    xpm->addr = (char *)mlx_get_data_addr(xpm->img, &xpm->bpp, &xpm->line_length, &xpm->endian);
}

void    exit_game(t_vars *vars)
{
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
}

void    entity_dyn_render(t_vars *vars, t_entity_dyn *entity, int mode)
{
    if (mode == 0)
        mlx_put_image_to_window(vars->mlx, vars->win, entity->xpm_reset.img, entity->axis.x, entity->axis.y);
    else if (mode == 1)
        mlx_put_image_to_window(vars->mlx, vars->win, entity->xpm[entity->dir].img, entity->axis.x, entity->axis.y);
}

void    entity_stc_render(t_vars *vars, t_entity_stc *entity)
{
    int i;
    int j;
    int pixel_index;
    int color;

    for (i = 0; i < entity->xpm.height; i++)
    {
        for (j = 0; j < entity->xpm.width; j++)
        {
            pixel_index = (i * entity->xpm.line_length) + (j * (entity->xpm.bpp / 8));
            color = *(int *)(entity->xpm.addr + pixel_index);
            if (color != -16777216)
                mlx_pixel_put(vars->mlx, vars->win, entity->axis.x + j, entity->axis.y + i, color);
        }
    }
}

void    entity_dyn_move(t_vars *vars, t_entity_dyn *entity)
{
    int new_x;
    int new_y;

    new_x = entity->axis.x;
    new_y = entity->axis.y;
    if (entity->velocity_x <= VELOCITY_MAX)
        entity->velocity_x += VELOCITY;
    if (entity->on_dir && entity->dir == 0)
    {
        new_x -= (int)entity->velocity_x;
        entity->axis.x = new_x;
    }
    else if (entity->on_dir && entity->dir == 1)
    {
        new_x += (int)entity->velocity_x;
        entity->axis.x = new_x;
    }
    if (entity->on_thruster)
    {
        new_y -= (int)entity->velocity_y;
        entity->axis.y = new_y;
    }
}

int entity_dyn_gravity_collision(t_vars *vars, t_entity_dyn *entity)
{
    int i_table;
    int dist_col;

    dist_col = 0;
    i_table = vars->ground_size;
    while (--i_table > -1)
    {
        if ((vars->ground[i_table].axis.x < entity->axis.x + entity->xpm->width) && (vars->ground[i_table].axis.x + (vars->ground[i_table].size * BASE) > entity->axis.x))
        {
            if (vars->ground[i_table].axis.y > entity->axis.y)
                dist_col = vars->ground[i_table].axis.y;
        }
    }
    printf("dist col %d\n", dist_col);
    return (dist_col);
}

void    entity_dyn_gravity(t_vars *vars, t_entity_dyn *entity)
{
    int dist_col;

    if (entity->on_thruster)
        return ;
    dist_col = entity_dyn_gravity_collision(vars, entity);
    entity->velocity_y += GRAVITY;
    // ... 448 = position collision, 128 = height img
    if (entity->axis.y + entity->velocity_y < dist_col - 128)
        entity->axis.y += entity->velocity_y;
    else
    {
        entity->axis.y = (dist_col - 128);
        entity->velocity_y = VELOCITY_DEF;
    }
}

int render(void *void_vars)
{
    t_vars *vars = (t_vars*)void_vars;

	usleep(SLEEP_TIME);

    entity_dyn_render(vars, &vars->player, 0);
    entity_dyn_move(vars, &vars->player);
    entity_dyn_gravity(vars, &vars->player);
    entity_dyn_render(vars, &vars->player, 1);

    entity_dyn_render(vars, &vars->spaceship, 0);
    entity_dyn_move(vars, &vars->spaceship);
    entity_dyn_gravity(vars, &vars->spaceship);
    entity_dyn_render(vars, &vars->spaceship, 1);

    entity_stc_render(vars, &vars->object[3]);
    return (0);
}

void    entity_dyn_key_press(t_entity_dyn *entity, int type)
{
    if (type == 0)
    {
        entity->dir = 0;
        entity->on_dir = 1;
    }
    else if (type == 1)
    {
        entity->dir = 1;
        entity->on_dir = 1;
    }
    else if (type == 2)
    {
        entity->velocity_y = VELOCITY_DEF;
        entity->on_thruster = 1;
    }
}

void    entity_dyn_key_release(t_entity_dyn *entity, int type)
{
    if (type == 0 || type == 1)
    {
        entity->velocity_x = VELOCITY_DEF;
        entity->on_dir = 0;
    }
    else if (type == 2)
    {
        entity->velocity_y = VELOCITY_DEF;
        entity->on_thruster = 0;
    }
        
    printf("entity->on_thruster = %d\n", entity->on_thruster);
}

int key_press(int keycode, t_vars *vars)
{
    t_entity_dyn *entity;

    if (!vars->entity_toggler)
        entity = &vars->player;
    else
        entity = &vars->spaceship;
    printf("--------------------------press\n");
    if (keycode == 65307)
        exit_game(vars);
    else if (keycode == 65361 && !entity->on_dir)//left
        entity_dyn_key_press(entity, 0);
    else if (keycode == 65363 && !entity->on_dir)//right
        entity_dyn_key_press(entity, 1);
    else if (keycode == 65362 && vars->entity_toggler && !entity->on_thruster)//up
        entity_dyn_key_press(entity, 2);
    else if (keycode == 109)
    {
        if (vars->entity_toggler == 1)
            vars->entity_toggler = 0;
        else
            vars->entity_toggler = 1;
    }
    else if (keycode == 114)
        entity_dyn_key_release(entity, 0);
	return (0);
}

int key_release(int keycode, t_vars *vars)
{
    t_entity_dyn *entity;

    if (!vars->entity_toggler)
        entity = &vars->player;
    else
        entity = &vars->spaceship;
    printf("--------------------------release\n");
    if (keycode == 65361 && entity->on_dir)//left
        entity_dyn_key_release(entity, 0);
    else if (keycode == 65363 && entity->on_dir)//right
        entity_dyn_key_release(entity, 1);
    else if (keycode == 65362 && entity->on_thruster)//up
        entity_dyn_key_release(entity, 2);
	return (0);
}

void    init_ground(t_vars *vars)
{
    int i_table;
    int i_ground;
    int i_img;
    t_axis  axis;

    load_xpm(vars, &vars->ground_xpm[0], "./assets/static/ground1_64_64.xpm");
    load_xpm(vars, &vars->ground_xpm[1], "./assets/static/ground2_64_64.xpm");
    load_xpm(vars, &vars->ground_xpm[2], "./assets/static/ground3_64_64.xpm");
    load_xpm(vars, &vars->ground_xpm[3], "./assets/static/ground4_64_64.xpm");
    i_img = 0;
    i_table = vars->ground_size;
    while (--i_table > -1)
    {
        axis.x = vars->ground[i_table].axis.x;
        axis.y = vars->ground[i_table].axis.y;
        i_ground = vars->ground[i_table].size;
        while (--i_ground > -1)
        {
            mlx_put_image_to_window(vars->mlx, vars->win, vars->ground_xpm[i_img].img, axis.x + (i_ground * BASE), axis.y);
            if (++i_img > 3)
                i_img = 0;
        }
    }
}

void    destroy_ground(t_vars *vars)
{
    int i_img;

    i_img = -1;
    while (++i_img < 4)
        mlx_destroy_image(vars->mlx, vars->ground_xpm[i_img].img);
}

void    init_object(t_vars *vars)
{
    int i;

    i = -1;
    while (++i < 4)
    {
        load_xpm(vars, &vars->object[i].xpm, "./assets/static/warpcore_64_64.xpm");
        vars->object[i].axis.x = i*64;
        vars->object[i].axis.y = 384;
        entity_stc_render(vars, &vars->object[i]);
    }
}

void    init_player(t_vars *vars, t_entity_dyn *entity)
{
    load_xpm(vars, &entity->xpm[0], "./assets/dynamic/player_64_128_left.xpm");
    load_xpm(vars, &entity->xpm[1], "./assets/dynamic/player_64_128_right.xpm");
    load_xpm(vars, &entity->xpm_reset, "./assets/static/background_64_128.xpm");
}

void    init_spaceship(t_vars *vars, t_entity_dyn *entity)
{
    load_xpm(vars, &entity->xpm[0], "./assets/dynamic/anglerfish_128_128_left.xpm");
    load_xpm(vars, &entity->xpm[1], "./assets/dynamic/anglerfish_128_128_right.xpm");
    load_xpm(vars, &entity->xpm_reset, "./assets/static/background_128_128.xpm");
}

void    init(t_vars *vars)
{
    vars->ground[0].axis.x = 128;
    vars->ground[0].axis.y = 128;
    vars->ground[0].size = 4;
    vars->ground[1].axis.x = 0;
    vars->ground[1].axis.y = 448;
    vars->ground[1].size = 12;
    vars->ground_size = sizeof(vars->ground) / sizeof(vars->ground[0]);
    vars->entity_toggler = 0;
    vars->player.dir = 0;
    vars->player.clock_x = 0;
    vars->player.clock_y = 0;
    vars->player.velocity_x = VELOCITY_DEF;
    vars->player.velocity_y = VELOCITY_DEF;
    vars->player.on_dir = 0;
    vars->player.on_thruster = 0;
    vars->player.axis.x = 128;
    vars->player.axis.y = 0;
    vars->spaceship.dir = 0;
    vars->spaceship.clock_x = 0;
    vars->spaceship.clock_y = 0;
    vars->spaceship.velocity_x = VELOCITY_DEF;
    vars->spaceship.velocity_y = VELOCITY_DEF;
    vars->spaceship.on_dir = 0;
    vars->spaceship.on_thruster = 0;
    vars->spaceship.axis.x = 8*64;
    vars->spaceship.axis.y = 0;
    
    init_ground(vars);
    destroy_ground(vars);
    init_object(vars);
    init_player(vars, &vars->player);
    init_spaceship(vars, &vars->spaceship);
}

int main(void)
{
    t_vars vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1024, 512, "Outerwilds 2D");

	mlx_do_key_autorepeatoff(vars.mlx);
    init(&vars);
    mlx_hook(vars.win, 2, 1L<<0, key_press, &vars);
    mlx_hook(vars.win, 3, 1L<<1, key_release, &vars);
	mlx_loop_hook(vars.mlx, render, &vars);
    mlx_loop(vars.mlx);
}
/*
#include <stdio.h>

int main() {
    int myArray[] = {1, 2, 3, 4, 5};

    // Calculate the number of elements in the array
    int numberOfElements = sizeof(myArray) / sizeof(myArray[0]);

    // Print the number of elements
    printf("Number of elements in the array: %d\n", numberOfElements);

    return 0;
}*/