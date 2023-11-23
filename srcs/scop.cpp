/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:03:17 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/23 14:51:27 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Scop.class.hpp"
#include "../includes/scop.hpp"

GLenum currentPolygonMode = GL_FILL;

int main(int argc, char **argv)
{
	
	
	Scop scop;	
	
	
	if (scop.check()) {
		// cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

	scop.addShaderProgram();
	
	// Set the key callback
	glfwSetKeyCallback(scop.getWindow(), key_callback);

	
	
    glUseProgram(scop.getShaderProgram());

	
	
    
	


	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // GL_FILL / GL_LINE / GL_POINT
	
	
	draw(scop);
	
		
    glDeleteProgram(scop.getShaderProgram());
	
	// Unbind VBO then VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
	
	// Terminate GLFW
	glfwTerminate();
	return 0;
}

