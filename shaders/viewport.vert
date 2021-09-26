#version 330 core

layout (location = 0) in vec3 aPos;

out vec2 texCoord;


void main() {
	texCoord = aPos.xy * 0.5 + vec2(0.5);
	gl_Position = vec4( aPos.x, aPos.y, aPos.z, 1.0 );
}