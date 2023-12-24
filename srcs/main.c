/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:22:57 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/17 12:54:26 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vars vars;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	// 키 이벤트 처리 로직
	t_info *info;
	char **map;

	info = &vars.info;
	map = vars.map.arr;
	if (key == GLFW_KEY_P)
		reset_game(&vars);
	if (vars.data.npc_talk)
		return ;
	if (key >= 0 && key <= 255)
		vars.data.keyboard[key] = 1;
	if (key == GLFW_KEY_N || key == GLFW_KEY_M)
		adjust_gamespeed(info, key);
	if (key == GLFW_KEY_SPACE)
		attack(&vars);
	if (key == GLFW_KEY_Q)
		turn_back(info);
	if (key == GLFW_KEY_B)
		open_door_tell_npc(&vars, map);
	if (key == GLFW_KEY_R)
		return_ellinia(&vars);
	if (key == GLFW_KEY_TAB)
		change_mini_map(&vars);
	return ;
}

static void	player_resurrection(t_vars *vars)
{
	reset_game(vars);
	vars->data.dead_check = 0;
}

static void	talk_npc_agree(t_vars *vars)
{
	vars->data.npc_talk = 0;
	vars->data.quest_num = 1;
	mlx_mouse_hide();
}

static void	talk_npc_negative(t_vars *vars)
{
	vars->data.npc_talk = 0;
	mlx_mouse_hide();
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	double x, y;
    glfwGetCursorPos(window, &x, &y);
	// 여기서 x와 y는 마우스 클릭 지점의 좌표입니다.
    // 이제 이 좌표를 이용하여 원하는 작업을 수행할 수 있습니다

	// 마우스 버튼 이벤트 처리 로직

	if (vars.data.dead_check && x >= 800 && x <= 860 && y >= 380 && y <= 400)
		player_resurrection(&vars);
	else if (vars.data.npc_talk && vars.data.quest_num == 0 && x >= 800 && x <= 850 && y >= 420 && y <= 435)
		talk_npc_agree(&vars);
	else if (vars.data.npc_talk && ((x >= 870 && x <= 920 && y >= 420 && y <= 435) || (x >= 435 && x <= 510 && y >= 420 && y <= 435)))
		talk_npc_negative(&vars);
	else if (button == 1 && vars.data.dead_check == 0 && !vars.data.npc_talk)
		attack(&vars);
	return ;
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	// 마우스 이동 이벤트 처리 로직
	if (vars.data.npc_talk)
		return (0);
	// vars.data.mouse_old_x = vars.data.mouse_x;
	// vars.data.mouse_old_y = vars.data.mouse_y;
	vars.data.mouse_x = xpos;
	vars.data.mouse_y = ypos;
	return ;
}

int main(int ac, char **av)
{
	// t_vars vars;

	if (ac != 2)
	{
		printf("Error\n");
		printf("Need one argument\n");
		return (RETURN_FAILURE);
	}
	init_vars(&vars);
	read_file(&vars, av[1]);

	//glfw에서는 mlx 포인터를 갖고다닐 필요 없음
	// vars.mlx = mlx_init();

	// win 포인터도 갖고다닐 필요 없을듯?
	// vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");

	// GLFW 초기화
	if (!glfwInit())
	{
		printf("Error: Failed to initialize GLFW\n");
		return (RETURN_FAILURE);
	}

	// GLFW 창 생성
	vars.g_win = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "cub3d", NULL, NULL);
	if (!vars.g_win)
	{
		printf("Error: Failed to create GLFW window\n");
		glfwTerminate();
		return (RETURN_FAILURE);
	}
	glfwMakeContextCurrent(vars.g_win);
	init_vars_info(&vars);

	// GLFW 이벤트 핸들러 등록
	glfwSetKeyCallback(vars.g_win, key_callback);
	glfwSetMouseButtonCallback(vars.g_win, mouse_button_callback);
	glfwSetCursorPosCallback(vars.g_win, cursor_position_callback);

	// 렌더링 루프 시작
	while (!glfwWindowShouldClose(vars.g_win))
	{
		// 렌더링 코드

		glfwSwapBuffers(vars.g_win);
		glfwPollEvents();

		rendering(&vars);
	}

	// GLFW 정리
	glfwTerminate();
	return (RETURN_SUCCESS);

	// mlx_hook(vars.win, KEY_PRESS, PRESS_MASK, key_press, &vars);
	// mlx_hook(vars.win, KEY_RELEASE, RELEASE_MASK, key_release, &vars);
	// mlx_hook(vars.win, MOUSE_BUTTON, BUTTON_MASK, handle_mouse_button, &vars);
	// mlx_hook(vars.win, MOUSE_MOVE, MOVE_MASK, handle_mouse_move, &vars);
	// mlx_loop_hook(vars.mlx, rendering, &vars);
	// mlx_hook(vars.win, WINDOW_DESTROY, DESTROY_MASK, exit_game, &vars);
	// mlx_loop(vars.mlx);
	// return (RETURN_SUCCESS);
}
