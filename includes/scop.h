/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:35:33 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/22 15:04:51 by xxxxxxx          ###   ########.fr       */
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

 using namespace std;


 unsigned int	compileShader(const string &path, GLenum shader_type);

 void			key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


#endif