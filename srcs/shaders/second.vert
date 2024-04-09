#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

uniform float angleX;
uniform float angleY;
uniform float angleZ;
uniform float fov_thing;
uniform float zoom;
uniform float x_translate;
uniform float y_translate;
uniform int color_type;
uniform int texture;

flat out vec3 ourColor;
out vec2 uv;

void main()
{
	mat4 projection;
	mat4 rotationX;
    mat4 rotationY;
	mat4 rotationZ;

    projection[0] = vec4(1.0, 0.0, 0.0, 0.0);
    projection[1] = vec4(0.0, 1.0, 0.0, 0.0);
    projection[2] = vec4(0.0, 0.0, 1.0, fov_thing);
	projection[3] = vec4(x_translate, y_translate, 0.0, 1.0);

    // Rotation autour de l'axe X
	rotationX[0] = vec4(1.0, 0.0, 0.0, 0.0);
	rotationX[1] = vec4(0.0, cos(angleX), -sin(angleX), 0.0);
	rotationX[2] = vec4(0.0, sin(angleX), cos(angleX), 0.0);
	rotationX[3] = vec4(0.0, 0.0, 0.0, 1.0);

	// Rotation autour de l'axe Y
	rotationY[0] = vec4(cos(angleY), 0.0, sin(angleY), 0.0);
	rotationY[1] = vec4(0.0, 1.0, 0.0, 0.0);
	rotationY[2] = vec4(-sin(angleY), 0.0, cos(angleY), 0.0);
	rotationY[3] = vec4(0.0, 0.0, 0.0, 1.0);

	// Rotation autour de l'axe Z
	rotationZ[0] = vec4(cos(angleZ), -sin(angleZ), 0.0, 0.0);
	rotationZ[1] = vec4(sin(angleZ), cos(angleZ), 0.0, 0.0);
	rotationZ[2] = vec4(0.0, 0.0, 1.0, 0.0);
	rotationZ[3] = vec4(0.0, 0.0, 0.0, 1.0);

    // Combinaison des rotations autour des axes x, y et z
	vec4 rotated = 
		rotationY * 
		rotationX * 
		rotationZ * 
		vec4(aPos.x / zoom, aPos.y / zoom, aPos.z / zoom, zoom);

	// Application de la projection
	vec4 projected = projection * rotated;
    gl_Position = projected;
	if (color_type == 0)
		ourColor = vec3(aColor.r, aColor.r, aColor.r);
	else if (color_type == 2)
		ourColor = vec3(aNormal.x, aNormal.y, aNormal.z);
	else
		ourColor = aColor;
	uv = aTexCoord;
}