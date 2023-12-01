/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:09:03 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/12/01 16:31:11 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.class.hpp"

/*
 ******************************* CONSTRUCTOR **********************************
 */

Parser::Parser(Scop &scop, string filename, int	width, int height) 
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

	bool parseError = false;

	
	string line;
	while (getline(file, line)) {
		
		// Split on spaces and store the first substring in prefix
		istringstream iss(line);
        string prefix;
        iss >> prefix;

		if (prefix == "v") {
			Vertex vertex;
			vertex.color = {0, 0, 0};
			vector<string> values;

			string temp;
			while (iss >> temp) {
				values.push_back(temp);
			}

			if (values.size() >= 3) {
				try {
					// Attempt to convert the first three strings to numeric values
					vertex.x = stof(values[0]);
					vertex.y = stof(values[1]);
					vertex.z = stof(values[2]);

					// Process the Vertex data
					vertices.push_back(vertex);
				} catch (const exception& e) {
					// Conversion failed: Not all values are numeric
					cerr << "Error: Conversion failed - Not enough numeric values for vertex\n";
					parseError = true;
					break;
				}
			} else {
				// Error: Not enough values in the line
				cerr << "Error: Insufficient values for vertex coordinates\n";
				parseError = true;
				break;
			}
		}
		else if (prefix == "f") {
			Color color = generateColor(false);
			// Start from one vertex and draw a triangle with each pair of vertices

			vector<string> values;

			string temp;
			while (iss >> temp) {
				values.push_back(temp);
			}

			if (values.size() < 3) {
				// Error: Not enough values in the line
				cerr << "Error: Insufficient values for face coordinates\n";
				parseError = true;
				break;
			}
			
			try {
				// First store all the vertices of the face in a vector
				vector<unsigned int> faceVertices;
				vector<unsigned int> final_faceVertices;
				unsigned int vertexIndex;

				bool localError = false;
				for (int i = 0; i < values.size(); i++) {

					// if the line contains any / characters, remove the part after the first /, including the /
					size_t pos = values[i].find("/");
					if (pos != string::npos) {
						values[i] = values[i].substr(0, pos);
					}

					// Attempt to convert the first three strings to numeric values
					vertexIndex = stoi(values[i]);
					faceVertices.push_back(vertexIndex - 1);
				}

				if (localError) {
					// Conversion failed: Not all values are numeric
					cerr << "Error: Conversion failed - Not enough numeric values for face\n";
					parseError = true;
					break;
				}

				// Calculate the u and v coordinates for each vertex so that the texture is not stretched
				// Calculate normal of the face
				if (faceVertices.size() < 3 || faceVertices[2] >= vertices.size() || faceVertices[1] >= vertices.size() || faceVertices[0] >= vertices.size()) {
					// Error: Not enough values in the line
					cerr << "Error: Insufficient values for face coordinates\n";
					parseError = true;
					break;
				}
				Vec3 v1 = {vertices[faceVertices[0]].x, vertices[faceVertices[0]].y, vertices[faceVertices[0]].z};
				Vec3 v2 = {vertices[faceVertices[1]].x, vertices[faceVertices[1]].y, vertices[faceVertices[1]].z};
				Vec3 v3 = {vertices[faceVertices[2]].x, vertices[faceVertices[2]].y, vertices[faceVertices[2]].z};
				
				Vec3 normal = (v2 - v1).cross(v3 - v1);
				
				normal = normal.normalize();
				
				for (int i = 0; i < faceVertices.size(); i++) {
					if (faceVertices[i] >= vertices.size()) {
						// Error: Not enough values in the line
						cerr << "Error: Insufficient values for face coordinates\n";
						parseError = true;
						localError = true;
						break;
					}
					float u, v;
					if (abs(normal.x) > abs(normal.y) && abs(normal.x) > abs(normal.z)) {
						u = vertices[faceVertices[i]].y;
						v = vertices[faceVertices[i]].z;
					} else if (abs(normal.y) > abs(normal.x) && abs(normal.y) > abs(normal.z)) {
						u = vertices[faceVertices[i]].x;
						v = vertices[faceVertices[i]].z;
					} else {
						u = vertices[faceVertices[i]].x;
						v = vertices[faceVertices[i]].y;
					}
					
					final_vertices.push_back({vertices[faceVertices[i]].x, vertices[faceVertices[i]].y, vertices[faceVertices[i]].z, color, u / 1, v / 1});
					final_faceVertices.push_back(final_vertices.size() - 1);
				}
				if (localError) break;
				
				// Then create a triangle with each pair of vertices
				for (int i = 0; i < faceVertices.size() - 2; i++)
				{
					if (faceVertices[i + 2] >= vertices.size() || faceVertices[i + 1] >= vertices.size() || faceVertices[i] >= vertices.size()) {
						// Error: Not enough values in the line
						cerr << "Error: Insufficient values for face coordinates\n";
						parseError = true;
						localError = true;
						break;
					}
					Face face;
					face.v1 = final_faceVertices[0];
					face.v2 = final_faceVertices[i + 1];
					face.v3 = final_faceVertices[i + 2];
					faces.push_back(face);
				}
				if (localError) break;
			} catch (const exception& e) {
				// Conversion failed: Not all values are numeric
				cerr << "Error: Conversion failed - Not enough numeric values for face\n";
				parseError = true;
				break;
			}			
		}
		else continue;
	}
	if (faces.size() == 0) {
		cerr << "Error: No faces found" << endl;
		parseError = true;
	}

	if (parseError) {
		cerr << "Error: Parsing failed" << endl;
		return ;
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