#version 330 core
layout (location = 0) in vec3 aPos;

uniform float time;

void main()
{
	// gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	mat3 projection;
	mat3 rotationX;
    mat3 rotationY;
	mat3 rotationZ;

    projection[0] = vec3(1.0, 0.0, 0.0);
    projection[1] = vec3(0.0, 1.0, 0.0);
    projection[2] = vec3(0.0, 0.0, 1.0);

    // Rotation autour de l'axe X
	rotationX[0] = vec3(1.0, 0.0, 0.0);
	rotationX[1] = vec3(0.0, cos(time * 5), -sin(time * 5));
	rotationX[2] = vec3(0.0, sin(time * 5), cos(time * 5));

	// Rotation autour de l'axe Y
	rotationY[0] = vec3(cos(time * 3), 0.0, sin(time * 3));
	rotationY[1] = vec3(0.0, 1.0, 0.0);
	rotationY[2] = vec3(-sin(time * 3), 0.0, cos(time * 3));

	// Rotation autour de l'axe Z
	rotationZ[0] = vec3(cos(time), -sin(time), 0.0);
	rotationZ[1] = vec3(sin(time), cos(time), 0.0);
	rotationZ[2] = vec3(0.0, 0.0, 1.0);

    // Combinaison des rotations autour des axes x, y et z
	vec3 rotated = rotationZ * rotationY * rotationX * aPos;

	// Application de la projection
	vec3 projected = projection * rotated;
    gl_Position = vec4(projected.x, projected.y, projected.z, 1.0);
}