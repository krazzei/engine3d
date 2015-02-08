#version 330 core
in vec2 vertexUV;

uniform sampler2D myTextureSampler;
uniform vec3 _color;

void main()
{
	//assign texture color, and material color.
	gl_FragColor = texture(myTextureSampler, vertexUV);
	gl_FragColor = vec4(gl_FragColor.xyz * _color.xyz, gl_FragColor.a);
}