/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scop.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:55:28 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/23 14:44:22 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class Scop;

#ifndef SCOP_CLASS_HPP
# define SCOP_CLASS_HPP
# include "../../includes/scop.hpp"
# include <vector>

using namespace std;

class Scop
{
	private:
		unsigned int			_check = 1;
		GLFWwindow				*_window;
		unsigned int			_shaderProgram;
		unsigned int			_VBO;
		unsigned int			_VAO;
		unsigned int			_EBO;
		unsigned int   			_fragment_shader;
		unsigned int   			_vertex_shader;
		vector<float>			_vertices;
		vector<unsigned int>	_indices;
		
	public:
		Scop();
		~Scop();
		
		GLFWwindow				*getWindow(void);
		unsigned int			getShaderProgram(void);
		unsigned int			getVBO(void);
		unsigned int			getVAO(void);
		unsigned int			getEBO(void);
		vector<float>			getVertices(void);
		vector<unsigned int>	getIndices(void);
		
		bool			check(void);
		void			addShaderProgram(void);
};

#endif