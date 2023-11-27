/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:09:03 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/27 14:02:02 by xxxxxxx          ###   ########.fr       */
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
			// Start from one vertex and draw a triangle with each pair of vertices
			
			// First store all the vertices of the face in a vector
			vector<unsigned int> faceVertices;
			unsigned int vertexIndex;
			while (iss >> vertexIndex) {
				faceVertices.push_back(vertexIndex - 1);
			}

			// Then create a triangle with each pair of vertices
			for (int i = 0; i < faceVertices.size() - 2; i++)
			{
				Face face;
				face.v1 = faceVertices[0];
				face.v2 = faceVertices[i + 1];
				face.v3 = faceVertices[i + 2];
				faces.push_back(face);
			}			
		}
		else if (prefix == "#") {
			continue;
		}
		else {
			//Other stuff for later
		}
	}
	
	// For the vertices, scale them to be between -1 and 1
	
	// First, get the min and max values for each coordinate using minmax_element
	
	auto minmaxX = minmax_element(vertices.begin(), vertices.end(), [](const Vertex &a, const Vertex &b) { return a.x < b.x; });
	auto minmaxY = minmax_element(vertices.begin(), vertices.end(), [](const Vertex &a, const Vertex &b) { return a.y < b.y; });
	auto minmaxZ = minmax_element(vertices.begin(), vertices.end(), [](const Vertex &a, const Vertex &b) { return a.z < b.z; });

	auto globalMin = min(minmaxX.first->x, min(minmaxY.first->y, minmaxZ.first->z));
	auto globalMax = max(minmaxX.second->x, max(minmaxY.second->y, minmaxZ.second->z));
	
	// Then, for each vertex, substract the min value and divide by the max value 
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].x = WINDOW_MIN_DRAW + (vertices[i].x - globalMin) / (globalMax - globalMin) * (WINDOW_MAX_DRAW - WINDOW_MIN_DRAW);
		vertices[i].y = WINDOW_MIN_DRAW + (vertices[i].y - globalMin) / (globalMax - globalMin) * (WINDOW_MAX_DRAW - WINDOW_MIN_DRAW);
		vertices[i].z = WINDOW_MIN_DRAW + (vertices[i].z - globalMin) / (globalMax - globalMin) * (WINDOW_MAX_DRAW - WINDOW_MIN_DRAW);
	}
	
	// Finnaly, translate the vertices so that the center of the object is at the origin (0, 0, 0)
	minmaxX = minmax_element(vertices.begin(), vertices.end(), [](const Vertex &a, const Vertex &b) { return a.x < b.x; });
	minmaxY = minmax_element(vertices.begin(), vertices.end(), [](const Vertex &a, const Vertex &b) { return a.y < b.y; });
	minmaxZ = minmax_element(vertices.begin(), vertices.end(), [](const Vertex &a, const Vertex &b) { return a.z < b.z; });	

	float centerX = (minmaxX.first->x + minmaxX.second->x) / 2;
	float centerY = (minmaxY.first->y + minmaxY.second->y) / 2;
	float centerZ = (minmaxZ.first->z + minmaxZ.second->z) / 2;

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].x -= centerX;
		vertices[i].y -= centerY;
		vertices[i].z -= centerZ;
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