#version 400

layout(location = 0) in vec3 vertex_position_modelspace;
layout(location = 1) in vec3 vertex_normal_modelspace;
layout(location = 2) in vec2 vertex_uv;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V; 
uniform vec3 LightPosition_worldspace;
uniform vec3 lightColor;

smooth out vec2 uv;
smooth out vec3 Normal_cameraspace;
smooth out vec3 LightDirection_cameraspace;
smooth out float distance;

void main () {
    
 
	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertex_position_cameraspace = ( V * M * vec4(vertex_position_modelspace,1)).xyz;
	vec3 EyeDirection_cameraspace = vec3(0,0,0) - vertex_position_cameraspace;
 
	// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
	vec3 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
 
	// Normal of the the vertex, in camera space
	Normal_cameraspace = ( V * M * vec4(vertex_normal_modelspace,0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
   
    gl_Position = MVP*vec4 (vertex_position_modelspace, 1.0);
    //color = vec3(50,50,255); 
    uv=vertex_uv;
    
    distance = length(vertex_position_cameraspace-LightPosition_cameraspace);
}