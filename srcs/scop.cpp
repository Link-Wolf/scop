/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:03:17 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/24 16:50:18 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Scop.class.hpp"
#include "classes/Parser.class.hpp"
#include "../includes/scop.hpp"

GLenum currentPolygonMode = GL_FILL;

int main(int argc, char **argv)
{
	//check that there is only one argument and that it is a .obj file
	if (argc != 2 || std::string(argv[1]).compare(std::string(argv[1]).size() - 4, 4, ".obj")) {
		cerr << "Usage: ./scop <filename>.obj" << endl;
		return -1;
	}
	
	Scop scop;	
	
	if (scop.check()) {
		// cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

	Parser parser(scop, argv[1]);

	scop.addShaderProgram();
	
	// Set the key callback
	glfwSetKeyCallback(scop.getWindow(), key_callback);

    glUseProgram(scop.getShaderProgram());

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // GL_FILL / GL_LINE / GL_POINT
	glEnable(GL_DEPTH_TEST); // So the triangles are drawn in the right order
	glEnable(GL_CULL_FACE); // So the triangles are not transparent ? (I don't know, maybe it's the opposite) 
	
	// draw(parser.getScop());
	draw(scop);
	
    glDeleteProgram(scop.getShaderProgram());
	
	// Unbind VBO then VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
	
	// Terminate GLFW
	glfwTerminate();
	return 0;
}

