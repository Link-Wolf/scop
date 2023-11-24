/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:53:26 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/24 16:42:29 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.hpp"

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // start at 0 / x y z / float type / normalize / size of each vertex / not offset
    glEnableVertexAttribArray(0); // enable the vertex attribute at location 0
	
	// Loop until the user closes the window
    while (!glfwWindowShouldClose(scop.getWindow())) {

		// Yew
        glUniform1f(
            glGetUniformLocation(scop.getShaderProgram(), "time"),
            (float)glfwGetTime()
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