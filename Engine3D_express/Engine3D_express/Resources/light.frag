#version 330 core
in float distanceToLight;
in vec3 lightDirection_cameraspace;
in vec3 normal_cameraspace;

uniform sampler2D myTextureSampler;
uniform mat3x4 lightInfo;
uniform vec3 _color;

void main()
{
	//find the normalized values for the arrays?
	vec3 n = normalize(normal_cameraspace);
	vec3 l;
	
	//Cosine of the angle between the normal and the light direction,
	//clamped above 0
	float cosTheta;
	
	l = normalize(lightDirection_cameraspace);
	cosTheta = clamp( dot(n,l), 0, 1);
	
	gl_FragColor = lightInfo[1] * length(lightInfo[2].xyz) * cosTheta;
	//the distanceToLight will match up with the lightCount, so also iterate through them.
	gl_FragColor = gl_FragColor / (distanceToLight * distanceToLight);
}