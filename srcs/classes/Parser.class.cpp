/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:09:03 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/28 17:28:06 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.class.hpp"

/*
 ******************************* CONSTRUCTOR **********************************
 */

Parser::Parser(Scop &scop, string filename) 
: _scop(scop){
	srand(time(NULL));
	ifstream file(filename);
	
	if (!file.is_open()) {
		cerr << "Failed to open file:" << filename << endl;
		return ;
	}

	vector<Face> faces;
	vector<Vertex> vertices;
	vector<Vertex> final_vertices;

	
	string line;
	while (getline(file, line)) {
		
		// Split on spaces and store the first substring in prefix
		std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

		if (prefix == "v") {
			Vertex vertex;
			iss >> vertex.x >> vertex.y >> vertex.z;
			vertex.color = {0, 0, 0};
			vertices.push_back(vertex);
		}
		else if (prefix == "f") {
			Color color = generateColor(false);
			// Start from one vertex and draw a triangle with each pair of vertices
			
			// First store all the vertices of the face in a vector
			vector<unsigned int> faceVertices;
			vector<unsigned int> final_faceVertices;
			unsigned int vertexIndex;
			while (iss >> vertexIndex) {
				faceVertices.push_back(vertexIndex - 1);
			}

			for (int i = 0; i < faceVertices.size(); i++) {
				final_vertices.push_back({vertices[faceVertices[i]].x, vertices[faceVertices[i]].y, vertices[faceVertices[i]].z, color, vertices[faceVertices[i]].z, vertices[faceVertices[i]].y});
				final_faceVertices.push_back(final_vertices.size() - 1);
			}
			
			// Then create a triangle with each pair of vertices
			for (int i = 0; i < faceVertices.size() - 2; i++)
			{
				Face face;
				face.v1 = final_faceVertices[0];
				face.v2 = final_faceVertices[i + 1];
				face.v3 = final_faceVertices[i + 2];
				faces.push_back(face);
			}
			
		}
		else continue;
	}
	
	// For the vertices, scale them to be between -1 and 1
	
	// First, get the min and max values for each coordinate using minmax_element
	
	auto minmaxX = minmax_element(final_vertices.begin(), final_vertices.end(), [](const Vertex &a, const Vertex &b) { return a.x < b.x; });
	auto minmaxY = minmax_element(final_vertices.begin(), final_vertices.end(), [](const Vertex &a, const Vertex &b) { return a.y < b.y; });
	auto minmaxZ = minmax_element(final_vertices.begin(), final_vertices.end(), [](const Vertex &a, const Vertex &b) { return a.z < b.z; });

	auto globalMin = min(minmaxX.first->x, min(minmaxY.first->y, minmaxZ.first->z));
	auto globalMax = max(minmaxX.second->x, max(minmaxY.second->y, minmaxZ.second->z));
	
	// Then, for each vertex, substract the min value and divide by the max value 
	for (int i = 0; i < final_vertices.size(); i++) {
		final_vertices[i].x = WINDOW_MIN_DRAW + (final_vertices[i].x - globalMin) / (globalMax - globalMin) * (WINDOW_MAX_DRAW - WINDOW_MIN_DRAW);
		final_vertices[i].y = WINDOW_MIN_DRAW + (final_vertices[i].y - globalMin) / (globalMax - globalMin) * (WINDOW_MAX_DRAW - WINDOW_MIN_DRAW);
		final_vertices[i].z = WINDOW_MIN_DRAW + (final_vertices[i].z - globalMin) / (globalMax - globalMin) * (WINDOW_MAX_DRAW - WINDOW_MIN_DRAW);
	}
	
	// Finnaly, translate the final_vertices so that the center of the object is at the origin (0, 0, 0)
	minmaxX = minmax_element(final_vertices.begin(), final_vertices.end(), [](const Vertex &a, const Vertex &b) { return a.x < b.x; });
	minmaxY = minmax_element(final_vertices.begin(), final_vertices.end(), [](const Vertex &a, const Vertex &b) { return a.y < b.y; });
	minmaxZ = minmax_element(final_vertices.begin(), final_vertices.end(), [](const Vertex &a, const Vertex &b) { return a.z < b.z; });	

	float centerX = (minmaxX.first->x + minmaxX.second->x) / 2;
	float centerY = (minmaxY.first->y + minmaxY.second->y) / 2;
	float centerZ = (minmaxZ.first->z + minmaxZ.second->z) / 2;

	for (int i = 0; i < final_vertices.size(); i++) {
		final_vertices[i].x -= centerX;
		final_vertices[i].y -= centerY;
		final_vertices[i].z -= centerZ;
	}
	
	_scop.setVertices(final_vertices);
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

Color	Parser::generateColor(bool monochrome) {
	Color color;
	
	// if monochrome is true, generate a grayscale color
	if (monochrome) {
		float grey = ((float) rand() / (float) RAND_MAX * 0.6);
		color.r = grey;
		color.g = grey;
		color.b = grey;
	}
	// else generate a true color
	else {
		color.r = (float) rand() / (float) RAND_MAX;
		color.g = (float) rand() / (float) RAND_MAX;
		color.b = (float) rand() / (float) RAND_MAX;
	}
	
	return color;
}

/*
 ******************************** ACCESSOR ************************************
 */

Scop	&Parser::getScop(void) {
	return _scop;
}