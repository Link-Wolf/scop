/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:35:33 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/12/01 13:31:27 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

// Library to manage OpenGL
 #include <GL/glew.h>

// Library to manage window and inputs
 #include <GLFW/glfw3.h>
 
 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <cstring>
 #include <cmath>

 #include "../srcs/classes/Scop.class.hpp"

 using namespace std;

 # define WINDOW_WIDTH 1200
 # define WINDOW_HEIGHT 1200
 # define WINDOW_MIN_DRAW -0.5
 # define WINDOW_MAX_DRAW 0.5

 struct Color
 {
	 float r, g, b;
 };
 
 struct Vertex
 {
	 float x, y, z;
	 struct Color color;
	 float u, v;
 };

 struct Vec3
 {
	 float x, y, z;

	Vec3 operator-(const Vec3 &v) const
	{
		return {x - v.x, y - v.y, z - v.z};
	}

	Vec3 &normalize()
	{
		float length = sqrt(x * x + y * y + z * z);
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}

	Vec3 cross(const Vec3 &v) const
	{
		return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
	}
 };

 struct Face
 {
	 unsigned int v1, v2, v3;
 };

 unsigned int	compileShader(const string &path, GLenum shader_type);

 void			key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

 void			scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

 void			draw(const Scop &scop);

#endif