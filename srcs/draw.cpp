/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:53:26 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/23 14:48:25 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.hpp"

void draw(Scop &scop)
{
	// Loop until the user closes the window
    while (!glfwWindowShouldClose(scop.getWindow())) {

		// Yew
        glUniform1f(
            glGetUniformLocation(scop.getShaderProgram(), "time"),
            (float)glfwGetTime()
        );

		// Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		
		//Draw here 
		//glDrawArrays(GL_TRIANGLES, 0, 6); // draw all triangles from indice 0 to 6
        glDrawElements(GL_TRIANGLES, scop.getIndices().size(), GL_UNSIGNED_INT, 0);
		
		// Swap front and back buffers to update the screen
        glfwSwapBuffers(scop.getWindow());
		// Poll and process events (such as key presses)
        glfwPollEvents();
    }
}