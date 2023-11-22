/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:03:17 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/22 17:45:33 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

int main(int argc, char **argv)
{
	// Initialize GLFW
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return -1;
    }

	// Create a windowed mode window and its OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr); //Parameters: width, height, title, monitor, share
    if (!window) {
		cerr << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
	
	// Set the key callback
	glfwSetKeyCallback(window, key_callback);
	
	// Initialize GLEW
    if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
        glfwTerminate();
        return -1;
    }

    unsigned int fragment_shader = compileShader("shaders/first.frag", GL_FRAGMENT_SHADER);
    if (!fragment_shader)
    {
        glfwTerminate();
        return -1;
    }

	unsigned int vertex_shader = compileShader("shaders/second.vert", GL_VERTEX_SHADER);
    if (!vertex_shader)
    {
        glfwTerminate();
        return -1;
    }
	
    unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex_shader);
    glAttachShader(shaderProgram, fragment_shader);
    glLinkProgram(shaderProgram);
    glDeleteShader(fragment_shader);
	glDeleteShader(vertex_shader);
    glUseProgram(shaderProgram);



	// Gros bebe tout sale

	float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        // 1, 2, 3    // second triangle
    };
	
	
	unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
	glBindVertexArray(VAO);

	

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	

	// Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {

		// Yew
        glUniform1f(
            glGetUniformLocation(shaderProgram, "time"),
            (float)glfwGetTime()
        );

		// Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		
		//Draw here 
		glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		// Swap front and back buffers to update the screen
        glfwSwapBuffers(window);
		// Poll and process events (such as key presses)
        glfwPollEvents();
    }
		
    glDeleteProgram(shaderProgram);
	
	// Terminate GLFW
	glfwTerminate();
	return 0;
}

