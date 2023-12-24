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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // 키 이벤트 처리 로직
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    // 마우스 버튼 이벤트 처리 로직
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    // 마우스 이동 이벤트 처리 로직
}


int main(int ac, char **av)
{
	t_vars vars;

	if (ac != 2)
	{
		printf("Error\n");
		printf("Need one argument\n");
		return (RETURN_FAILURE);
	}
	init_vars(&vars);
	read_file(&vars, av[1]);

	// vars.mlx = mlx_init();
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
