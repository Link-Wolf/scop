#version 330 core
layout (location = 0) in vec3 aPos;

uniform float angle;
uniform float fov_thing;
uniform float zoom;

void main()
{
	mat4 projection;
	mat4 rotationX;
    mat4 rotationY;
	mat4 rotationZ;

    projection[0] = vec4(1.0, 0.0, 0.0, 0.0);
    projection[1] = vec4(0.0, 1.0, 0.0, 0.0);
    projection[2] = vec4(0.0, 0.0, 1.0, fov_thing);
	projection[3] = vec4(0.0, 0.0, 0.0, 1.0);

    // Rotation autour de l'axe X
	rotationX[0] = vec4(1.0, 0.0, 0.0, 0.0);
	rotationX[1] = vec4(0.0, cos(angle * 5), -sin(angle * 5), 0.0);
	rotationX[2] = vec4(0.0, sin(angle * 5), cos(angle * 5), 0.0);
	rotationX[3] = vec4(0.0, 0.0, 0.0, 1.0);

	// Rotation autour de l'axe Y
	rotationY[0] = vec4(cos(angle * 1), 0.0, sin(angle * 1), 0.0);
	rotationY[1] = vec4(0.0, 1.0, 0.0, 0.0);
	rotationY[2] = vec4(-sin(angle * 1), 0.0, cos(angle * 1), 0.0);
	rotationY[3] = vec4(0.0, 0.0, 0.0, 1.0);

	// Rotation autour de l'axe Z
	rotationZ[0] = vec4(cos(angle), -sin(angle), 0.0, 0.0);
	rotationZ[1] = vec4(sin(angle), cos(angle), 0.0, 0.0);
	rotationZ[2] = vec4(0.0, 0.0, 1.0, 0.0);
	rotationZ[3] = vec4(0.0, 0.0, 0.0, 1.0);

    // Combinaison des rotations autour des axes x, y et z
	vec4 rotated = 
		// rotationZ * 
		rotationY * 
		// rotationX * 
		vec4(aPos.x / zoom, aPos.y / zoom, aPos.z / zoom, zoom);

	// Application de la projection
	vec4 projected = projection * rotated;
    gl_Position = projected;
}