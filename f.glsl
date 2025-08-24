#version 440 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	//basic tile texture
	FragColor = texture(texture1,TexCoord);	
}