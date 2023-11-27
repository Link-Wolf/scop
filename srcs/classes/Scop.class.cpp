/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scop.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:55:31 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/27 13:55:43 by xxxxxxx          ###   ########.fr       */
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
	
	_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "scop", nullptr, nullptr); //Parameters: width, height, title, monitor, share
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

// 	_vertices = {
//         0.0f, 0.5f, 0.0f,   	// S
//         0.0f, -0.5f, -0.5f,    	// A
//         -0.5f, -0.5f, 0.5f,		// B
//         0.5f, -0.5f, 0.5f,		// C
//     };
//    _indices = {  // note that we start from 0!
//         0, 1, 2,            // SBA
//         0, 2, 3,            // SBC
//         0, 3, 1,            // SCA
//         1, 3, 2             // ACB
//     };
	
	_check = 0;
}

Scop::Scop(const Scop &src) {
	*this = src;
}

Scop	&Scop::operator=(const Scop &rhs) {
	if (this != &rhs) {
		_check = rhs._check;
		_window = rhs._window;
		_shaderProgram = rhs._shaderProgram;
		_VBO = rhs._VBO;
		_VAO = rhs._VAO;
		_EBO = rhs._EBO;
		_fragment_shader = rhs._fragment_shader;
		_vertex_shader = rhs._vertex_shader;
		_vertices = rhs._vertices;
		_indices = rhs._indices;
	}
	return *this;
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

GLFWwindow	*Scop::getWindow(void) const {
	return _window;
}

const unsigned int	Scop::getShaderProgram(void) const {
	return _shaderProgram;
}

const unsigned int	Scop::getVBO(void) const {
	return _VBO;
}

const unsigned int	Scop::getVAO(void) const {
	return _VAO;
}

const unsigned int	Scop::getEBO(void) const {
	return _EBO;
}

const vector<float>	Scop::getVertices(void) const {
	return _vertices;
}

const vector<unsigned int>	Scop::getIndices(void) const {
	return _indices;
}

void Scop::setVertices(vector<Vertex> vertices) {
	for (unsigned int i = 0; i < vertices.size(); i++) {
		_vertices.push_back(vertices[i].x);
		_vertices.push_back(vertices[i].y);
		_vertices.push_back(vertices[i].z);
	}
}

void Scop::setIndices(vector<Face> indices) {
	for (unsigned int i = 0; i < indices.size(); i++) {
		_indices.push_back(indices[i].v1);
		_indices.push_back(indices[i].v2);
		_indices.push_back(indices[i].v3);
	}
}
