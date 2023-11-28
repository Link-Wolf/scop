/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:03:17 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/28 17:56:15 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/Scop.class.hpp"
#include "classes/Parser.class.hpp"
#include "../includes/scop.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../includes/stb_image.h"

GLenum currentPolygonMode = GL_FILL;
float fov_thing = 1.0f;
bool showroom = 1.0f;
float angle = 0.0f;
float angleX = 0.0f;
float angleZ = 0.0f;
float zoom = 1.0f;
float x_translate = 0.0f;
float y_translate = 0.0f;
bool monochrome = true;
bool texture = false;

int main(int argc, char **argv)
{
	//check that there is only one argument and that it is a .obj file
	if (argc != 2 || string(argv[1]).compare(string(argv[1]).size() - 4, 4, ".obj")) {
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
	
	// Set the key callback and mouse scroll callback
	glfwSetKeyCallback(scop.getWindow(), key_callback);
	glfwSetScrollCallback(scop.getWindow(), scroll_callback);

    glUseProgram(scop.getShaderProgram());

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // GL_FILL / GL_LINE / GL_POINT
	glEnable(GL_DEPTH_TEST); // So the triangles are drawn in the right order
	// glEnable(GL_CULL_FACE); // So the triangles are not transparent ? (I don't know, maybe it's the opposite) 

	/* Manage texture */

	int width, height, numChannels;
	unsigned char *img_data = stbi_load("textures/mlp.bmp", &width, &height, &numChannels, 0);

	if(!img_data)
	{
		cerr << "Failed to load texture" << endl;
		glDeleteProgram(scop.getShaderProgram());
		glfwTerminate();
		return -1;
	}
	
	GLuint texture;
	glGenTextures(1, &texture);

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load the image data into the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(scop.getShaderProgram(), "ourTexture"), 0); // Set the texture unit
	
	cout << "Controls :\n\tTAB :\t\tswitch between FILL and LINE mode\n\tM :\t\ttoggle monochrome\n\tArrows :\tmove the object\n\tMouse scroll :\tzoom in/out\n\tT :\t\ttoggle texturing\n\tR :\t\ttoggle showroom\n\t+/- :\t\tchange the reality\n\tESC :\t\tclose the window" << endl;
	
	draw(scop);
	
	stbi_image_free(img_data);
	
    glDeleteProgram(scop.getShaderProgram());
	
	// Unbind VBO then VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
	
	// Terminate GLFW
	glfwTerminate();
	return 0;
}

