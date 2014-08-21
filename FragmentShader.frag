#version 400

smooth in vec3 Normal_cameraspace;
smooth in vec2 uv;
smooth in vec3 LightDirection_cameraspace;
smooth in float distance;

uniform sampler2D myTextureSampler;
uniform float light;

out vec4 frag_color;

void main () {
	vec3 color = texture2D( myTextureSampler, uv ).rgb;

 	vec3 n = normalize( Normal_cameraspace );
 	vec3 l = normalize( LightDirection_cameraspace );
 	
	float cosTheta = clamp(dot( n,l ),0,1);
	vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * color;
	
	frag_color = vec4(color,1.0)*vec4(200,200,200,1.0)*cosTheta/(distance*distance)*0.05;
	frag_color = frag_color + MaterialAmbientColor*light;

	
}