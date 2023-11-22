/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_shaders.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xxxxxxx <xxxxxxx@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:56:54 by xxxxxxx           #+#    #+#             */
/*   Updated: 2023/11/22 16:43:36 by xxxxxxx          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"

unsigned int    compileShader(const std::string &path, GLenum shader_type)
{
    std::ifstream        file(path);
    std::stringstream    buffer;
    unsigned int        shader;
    char*                source;
    GLint success;

    if (!file.is_open())
    {
        std::cerr << "Cannot open file " << path << std::endl;
        return (0);
    }
    buffer << file.rdbuf();
    source = strdup(buffer.str().c_str()); //manage some shit to be able to get the right type
	
    shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, nullptr); //shader, nb_source ,source, sizeof all source or null if nb = 1
    glCompileShader(shader);
    free(source);

	// Check if error in shader code
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Shader compilation error in " << path << ":\n" << infoLog << std::endl;
        return 0;
    }

    return shader;
}
