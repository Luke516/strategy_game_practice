#version 400

smooth in vec3 Normal_cameraspace;
smooth in vec2 uv;
smooth in vec3 LightDirection_cameraspace;
smooth in float distance;

uniform sampler2D myTextureSampler;

out vec4 frag_color;

void main () {
	vec3 color = texture2D( myTextureSampler, uv ).rgb;
	//vec3 color = vec3(100,0,255);
	
	// Normal of the computed fragment, in camera space
 	vec3 n = normalize( Normal_cameraspace );
 	// Direction of the light (from the fragment to the light)
 	vec3 l = normalize( LightDirection_cameraspace );
 	
	float cosTheta = clamp(dot( n,l ),0,1);
	vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * color;
	
	frag_color = vec4(color,1.0)*vec4(200,200,200,1.0)*cosTheta/(distance*distance)*0.01;
	frag_color = frag_color + MaterialAmbientColor*1;

	//frag_color = MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance);
	
}