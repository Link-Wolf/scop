/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:03:17 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/17 12:43:09 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

using namespace std;

// unsigned int    compileShader(const string &path, GLenum shader_type)
// {
//     std::ifstream        file(path);
//     std::stringstream    buffer;
//     unsigned int        shader;
//     GLint success;

//     if (!file.is_open())
//         return (0);
//     buffer << file.rdbuf();
//     shader = glCreateShader(shader_type);
//     glShaderSource(shader, 1, &buffer.str().c_str(), nullptr);
//     glCompileShader(shader);

//     glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         GLchar infoLog[512];
//         glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
//         cerr << "Shader compilation error in " << path << ":\n" << infoLog << endl;
//         return 0;
//     }

//     return shader;
// }

int main(int argc, char **argv)
{
    unsigned int    vertex_shader;
    unsigned int    fragment_shader;
    unsigned int    shaderProgram;

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

    // fragment_shader = compileShader("../shaders/red.gls1", GL_COMPUTE_SHADER);
    // if (!vertex_shader)
    // {
    //     glfwTerminate();
    //     return -1;
    // }

    // shaderProgram = glCreateProgram();
    // glAttachShader(shaderProgram, fragment_shader);
    // glLinkProgram(shaderProgram);
    // glDeleteShader(fragment_shader);
    // glUseProgram(shaderProgram);


	// Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // glUniform1f(
        //     glGetUniformLocation(shaderProgram, "time"),
        //     (float)glfwGetTime()
        // );

		// Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



		//Draw here 

		
		// Swap front and back buffers to update the screen
        glfwSwapBuffers(window);
		// Poll and process events (such as key presses)
        glfwPollEvents();
    }
		
	// Terminate GLFW
    glDeleteProgram(shaderProgram);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}