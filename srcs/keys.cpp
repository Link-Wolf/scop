/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:57:40 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/27 14:48:03 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.hpp"

extern GLenum currentPolygonMode;
extern float fov_thing;
extern bool showroom;
extern float zoom;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{	
	/* Close properly using ESCAPE */
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

	/* Switch between FILL and LINE mode using TAB */
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{
		if (currentPolygonMode == GL_FILL) {
			currentPolygonMode = GL_LINE;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			currentPolygonMode = GL_FILL;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	
	/* Add or substract to fov following + and - */
	if (key == GLFW_KEY_KP_ADD && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		fov_thing += 0.1;
	}
	else if (key == GLFW_KEY_KP_SUBTRACT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		fov_thing -= 0.1;
	}

	/* Set or unset the showroom to 1 using S */
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		if (showroom == 1.0f)
			showroom = 0.0f;
		else
			showroom = 1.0f;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	/* Zoom or unzoom to fov following mouse scroll */
	if (yoffset > 0 && zoom < 10.0f)
	{
		zoom *= 1.1;
	}
	else if (yoffset < 0 && zoom > -10.0f)
	{
		zoom /= 1.1;
	}
}