	"#version 330 core\n"
		"in vec3 Color;"
		"in vec2 Texcoord;"
		"out vec4 outColor;"
		"uniform sampler2D texKitten;"
		"void main() {"
		"   outColor = texture(texKitten, Texcoord) * vec4(Color, 1.0);"
		"}";