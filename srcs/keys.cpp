/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:57:40 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/28 17:44:39 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.hpp"

extern GLenum currentPolygonMode;
extern float fov_thing;
extern bool showroom;
extern float zoom;
extern float x_translate;
extern float y_translate;
extern float angleX;
extern float angleZ;
extern bool monochrome;
extern bool texture;

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
	
	/* Toggle the monochrome using M */
	if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		if (monochrome)
			monochrome = false;
		else
			monochrome = true;
	}
	
	/* Add or substract to fov following + and - */
	if (key == GLFW_KEY_KP_ADD && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		fov_thing += 0.05;
	}
	else if (key == GLFW_KEY_KP_SUBTRACT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		fov_thing -= 0.05;
	}

	/* Set or unset the texture to 1 using T */
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		if (texture == true)
			texture = false;
		else
			texture = true;
	}

	/* Set or unset the showroom to 1 using R */
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		if (showroom == 1.0f)
			showroom = 0.0f;
		else
			showroom = 1.0f;
	}

	/* Make the object turn around x and z axis following wasd press/repeat */
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		angleX += 0.05;
	}
	else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		angleX -= 0.05;
	}
	else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		angleZ += 0.05;
	}
	else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		angleZ -= 0.05;
	}

	/* Add or substract to x and y translate using arrows */
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		x_translate += 0.01;
	}
	else if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		x_translate -= 0.01;
	}
	else if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		y_translate += 0.01;
	}
	else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		y_translate -= 0.01;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	/* Zoom or unzoom to fov following mouse scroll */
	if (yoffset > 0 && zoom < 10.0f)
	{
		zoom *= 1.05;
	}
	else if (yoffset < 0 && zoom > -10.0f)
	{
		zoom /= 1.05;
	}
}