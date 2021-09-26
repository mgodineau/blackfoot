#version 330 core

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D img_input;

void main() {
	
	FragColor = texture(img_input, texCoord);
	
	//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}