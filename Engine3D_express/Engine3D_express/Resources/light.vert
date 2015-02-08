#version 330 core
in vec3 vertexPosition_modelspace;
in vec3 vertexNormal_modelspace;

out float distanceToLight;
out vec3 lightDirection_cameraspace;
out vec3 normal_cameraspace;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat3x4 lightInfo;

void main()
{
	gl_Position = (P * V) * ( M * vec4(vertexPosition_modelspace,1));
	//forwards the vertex uv from c++ to our fragment shader.
	//can the fragment shader just take this from our attribPointer?
	
	vec3 position_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;
	
	vec3 vertexPosition_cameraspace = (V * vec4(position_worldspace, 1)).xyz;
	vec3 eyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;
	
	vec3 lightPosition_cameraspace;
	
	lightPosition_cameraspace = ( V * lightInfo[0]).xyz;
	lightDirection_cameraspace = lightPosition_cameraspace + eyeDirection_cameraspace;
	
	distanceToLight = distance(position_worldspace, lightInfo[0].xyz);
	
	normal_cameraspace = (V * M * vec4(vertexNormal_modelspace, 0)).xyz; //only works if there is no scaling on the model! use its inverse transpose if so.
}