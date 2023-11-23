/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:57:40 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/23 14:34:31 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.hpp"

extern GLenum currentPolygonMode;

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
}