/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scop.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:55:31 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/23 14:47:30 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scop.class.hpp"

/*
 ******************************* CONSTRUCTOR **********************************
 */

Scop::Scop(void) {
	
	// Initialize GLFW
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return ;
    }
	
	_window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr); //Parameters: width, height, title, monitor, share
	if (!_window) {
		cerr << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return ;
	}
	
    glfwMakeContextCurrent(_window);

	// Initialize GLEW
    if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
        glfwTerminate();
        return ;
    }
	
	// Create a windowed mode window and its OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
	_fragment_shader = compileShader("srcs/shaders/first.frag", GL_FRAGMENT_SHADER);
	if (!_fragment_shader)
	{
		cerr << "Failed to compile fragment shader" << endl;
		glfwTerminate();
		return ;
	}
	_vertex_shader = compileShader("srcs/shaders/second.vert", GL_VERTEX_SHADER);
	if (!_vertex_shader)
	{
		cerr << "Failed to compile vertex shader" << endl;
		glfwTerminate();
		return ;
	}


	_vertices = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
   _indices = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };


	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	
	// VAO = Store all the vertex attributes in the GPU's memory (VBO + EBO + vertexAttribute)
	unsigned int VAO; // Vertex Array Object	
    glGenVertexArrays(1, &VAO); //oui
    glBindVertexArray(VAO); //bind pour utiliser lui quand on a besoin d'un VAO

	// VBO = Store all the vertices in the GPU's memory
	unsigned int VBO;
    glGenBuffers(1, &VBO); //oui
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind pour utiliser lui quand on a besoin d'un VBO
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), &(_vertices[0]), GL_STATIC_DRAW); ///init the buffer with the vertices

	// EBO = Store all the indices (that are used to draw faces) in the GPU's memory
	unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &(_indices)[0], GL_STATIC_DRAW);


	// tell OpenGL how it should interpret the vertex data (per vertex attribute)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // start at 0 / x y z / float type / normalize / size of each vertex / not offset
    glEnableVertexAttribArray(0); // enable the vertex attribute at location 0

	_check = 0;
}

/*
 ******************************* DESTRUCTOR ***********************************
 */

Scop::~Scop(void) {
	
}

/*
 ******************************** METHODS *************************************
 */

void	Scop::addShaderProgram(void) {
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _vertex_shader);
	glAttachShader(_shaderProgram, _fragment_shader);
	glLinkProgram(_shaderProgram);
	glDeleteShader(_fragment_shader);
	glDeleteShader(_vertex_shader);
	glUseProgram(_shaderProgram);
}

bool	Scop::check(void) {
	return _check;
}

/*
 ******************************** ACCESSOR ************************************
 */

GLFWwindow	*Scop::getWindow(void) {
	return _window;
}

unsigned int	Scop::getShaderProgram(void) {
	return _shaderProgram;
}

unsigned int	Scop::getVBO(void) {
	return _VBO;
}

unsigned int	Scop::getVAO(void) {
	return _VAO;
}

unsigned int	Scop::getEBO(void) {
	return _EBO;
}

vector<float>	Scop::getVertices(void) {
	return _vertices;
}

vector<unsigned int>	Scop::getIndices(void) {
	return _indices;
}
