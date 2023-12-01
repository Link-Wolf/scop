/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:03:17 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/12/01 13:19:17 by xxxxxxx          ###   ########.fr       */
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

	// Load the image data
	int width, height, numChannels;
	unsigned char *img_data = stbi_load("textures/kitten.bmp", &width, &height, &numChannels, 0);

	if(!img_data)
	{
		cerr << "Failed to load texture" << endl;
		glDeleteProgram(scop.getShaderProgram());
		glfwTerminate();
		return -1;
	}
	
	Parser parser(scop, argv[1], width, height);

	scop.addShaderProgram();
	
	// Set the key callback and mouse scroll callback
	glfwSetKeyCallback(scop.getWindow(), key_callback);
	glfwSetScrollCallback(scop.getWindow(), scroll_callback);

    glUseProgram(scop.getShaderProgram());

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // GL_FILL / GL_LINE / GL_POINT
	glEnable(GL_DEPTH_TEST); // So the triangles are drawn in the right order
	// glEnable(GL_CULL_FACE); // So the triangles are not transparent ? (I don't know, maybe it's the opposite) 


	/* Manage texture */
	
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
	
	cout << "\033[1m\033[37mControls :\n"
				<< "\t\033[1m\033[37mTAB :\t\t\033[0m\033[37mSwitch between FILL and LINE mode\n"
				<< "\t\033[1m\033[37mM :\t\t\033[0m\033[37mToggle monochrome in triangle mode\n"
				<< "\t\033[1m\033[37mArrows :\t\033[0m\033[37mMove the object\n" 
				<< "\t\033[1m\033[37mMouse scroll :\t\033[0m\033[37mZoom in/out\n"
				<< "\t\033[1m\033[37mT :\t\t\033[0m\033[37mToggle texturing\n"
				<< "\t\033[1m\033[37mR :\t\t\033[0m\033[37mToggle showroom\n"
				<< "\t\033[1m\033[37m+/- :\t\t\033[0m\033[37mChange the reality\n"
				<< "\t\033[1m\033[37mESC :\t\t\033[0m\033[37mClose the window\033[0m"
		<< endl;
	
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

