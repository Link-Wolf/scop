/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scop.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:55:28 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/24 16:36:30 by xxxxxxx          ###   ########.fr       */
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
		Scop(const Scop &src);
		~Scop();

		Scop	&operator=(const Scop &rhs);
		
		GLFWwindow				*getWindow(void) const;		
		const unsigned int			getShaderProgram(void) const;
		const unsigned int			getVBO(void) const;
		const unsigned int			getVAO(void) const;
		const unsigned int			getEBO(void) const;
		const vector<float>			getVertices(void) const;
		const vector<unsigned int>	getIndices(void) const;

		void			setVertices(vector<struct Vertex> vertices);
		void			setIndices(vector<struct Face> indices);
		
		bool			check(void);
		void			addShaderProgram(void);
};

#endif