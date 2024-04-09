/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:53:26 by xxxxxxx           #+#    #+#             */
/*   Updated: 2024/04/09 14:50:57 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.hpp"

extern float fov_thing;
extern bool showroom;
extern float angle;
extern float zoom;
extern float x_translate;
extern float y_translate;
extern float angleX;
extern float angleZ;
extern int color_type;
extern bool texture;
extern bool normal;

void draw(const Scop &scop)
{
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	
	// VAO = Store all the vertex attributes in the GPU's memory (VBO + EBO + vertexAttribute)
	unsigned int VAO; // Vertex Array Object	
    glGenVertexArrays(1, &VAO); //oui
    glBindVertexArray(VAO); //bind pour utiliser lui quand on a besoin d'un VAO

	// VBO = Store all the vertices in the GPU's memory
	unsigned int VBO;
    glGenBuffers(1, &VBO); //oui
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind pour utiliser lui quand on a besoin d'un VBO
    glBufferData(GL_ARRAY_BUFFER, scop.getVertices().size() * sizeof(float), &(scop.getVertices()[0]), GL_STATIC_DRAW); ///init the buffer with the vertices

	// EBO = Store all the indices (that are used to draw faces) in the GPU's memory
	unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, scop.getIndices().size() * sizeof(unsigned int), &(scop.getIndices())[0], GL_STATIC_DRAW);


	// tell OpenGL how it should interpret the vertex data (per vertex attribute)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0); // layout 0 / x y z / float type / normalize / size of each vertex / not offset
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float))); // layout 1 / r g b / float type / normalize / size of each vertex / offset of 3 floats
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float))); // layout 2 / u v / float type / normalize / size of each vertex / offset of 6 floats
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float))); // layout 3 / nr ng nb / float type / normalize / size of each vertex / offset of 8 floats
    glEnableVertexAttribArray(0); // enable the vertex attribute at location 0
	glEnableVertexAttribArray(1); // enable the vertex attribute at location 1
	glEnableVertexAttribArray(2); // enable the vertex attribute at location 2
	glEnableVertexAttribArray(3); // enable the vertex attribute at location 3
	
	// Loop until the user closes the window
    while (!glfwWindowShouldClose(scop.getWindow())) {
		if (showroom)
			angle += 0.01f;
			
		// Get the texture and send it to the shader
		glUniform1i(
			glGetUniformLocation(scop.getShaderProgram(), "isTextured"),
			texture
		);
		
		// Get the angles to send them to the shader
        glUniform1f(
            glGetUniformLocation(scop.getShaderProgram(), "angleX"),
            angleX
        );
		glUniform1f(
            glGetUniformLocation(scop.getShaderProgram(), "angleY"),
            angle
        );
		glUniform1f(
            glGetUniformLocation(scop.getShaderProgram(), "angleZ"),
            angleZ
        );

		// Get the color_type to send it to the shader
		glUniform1i(
			glGetUniformLocation(scop.getShaderProgram(), "color_type"),
			color_type
		);
		
		// Get the fov to send it to the shader
		glUniform1f(
			glGetUniformLocation(scop.getShaderProgram(), "fov_thing"),
			fov_thing
		);

		// Get the zoom to send it to the shader
		glUniform1f(
			glGetUniformLocation(scop.getShaderProgram(), "zoom"),
			zoom
		);

		// Get the x and y translation to send them to the shader
		glUniform1f(
			glGetUniformLocation(scop.getShaderProgram(), "x_translate"),
			x_translate
		);
		glUniform1f(
			glGetUniformLocation(scop.getShaderProgram(), "y_translate"),
			y_translate
		);

		// Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Draw here 
		//glDrawArrays(GL_TRIANGLES, 0, 6); // draw all triangles from indice 0 to 6
        glDrawElements(GL_TRIANGLES, scop.getIndices().size(), GL_UNSIGNED_INT, 0);
		
		// Swap front and back buffers to update the screen
        glfwSwapBuffers(scop.getWindow());
		// Poll and process events (such as key presses)
        glfwPollEvents();
    }
}