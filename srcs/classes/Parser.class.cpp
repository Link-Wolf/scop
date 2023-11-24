/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:09:03 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/24 16:49:56 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.class.hpp"

/*
 ******************************* CONSTRUCTOR **********************************
 */

Parser::Parser(Scop &scop, string filename) 
: _scop(scop){
	ifstream file(filename);
	
	if (!file.is_open()) {
		cerr << "Failed to open file:" << filename << endl;
		return ;
	}

	vector<Face> faces;
	vector<Vertex> vertices;
	
	string line;
	while (getline(file, line)) {
		
		// Split on spaces and store the first substring in prefix
		std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

		if (prefix == "v") {
			Vertex vertex;
			iss >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		}
		else if (prefix == "f") {
			Face face;
			iss >> face.v1 >> face.v2 >> face.v3;
			faces.push_back(face);
		}
		else if (prefix == "#") {
			continue;
		}
		else {
			//Other stuff for later
		}
	}
	_scop.setVertices(vertices);
	_scop.setIndices(faces);
	
	_check = 0;
}

/*
 ******************************* DESTRUCTOR ***********************************
 */

Parser::~Parser(void) {
	;	
}

/*
 ******************************** METHODS *************************************
 */

void	Parser::parse(string filename) {
	
}

bool	Parser::check(void) {
	return _check;
}

/*
 ******************************** ACCESSOR ************************************
 */

Scop	&Parser::getScop(void) {
	return _scop;
}