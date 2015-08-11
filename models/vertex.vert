//[VERTEX SHADER]
#version 330 core

layout(location = 0) in vec3 inVertex;
layout(location = 1) in vec2 inTextureCoord;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inColor;

uniform bool render_texture;
uniform sampler2D inTexture;
 
uniform mat4 model_view_matrix;
uniform mat4 model_view_transf_matrix;
uniform mat4 projection_matrix;
uniform mat4 normal_matrix;

uniform vec3 light_position;
uniform vec4 ambient_light;
uniform vec4 diffuse_light;
uniform vec4 specular_light;

// send to fragment shader
smooth out vec3 ambient;
smooth out vec3 diffuse;
smooth out vec3 specular;

smooth out vec3 color_by_vertex;
smooth out vec2 tex;
// end of send to fragment shader

out float gl_PointSize;

void main()
{
	// transform to the eye space
	vec4 vvertex = model_view_transf_matrix * vec4(inVertex, 1.0);
	
	// transform to the clip coordinates
	gl_Position = projection_matrix * vvertex;
	
	// need the model view matrix without object trasnformation
	// to transform the light position to the eye space
	vec4 vlight = model_view_matrix * vec4(light_position, 1.0);
	
	// transform the normal vector to eye space
	vec4 vnormal = normal_matrix * vec4(inNormal, 0.0);
	
	const float shiness = 20;
	bool is_back_face = false;
	const vec3 Em = vec3(0.1, 0.1, 0.1);
	
	// AMBIENT
	ambient = ambient_light.xyz;// * (0.6 * inColor);
	// END OF AMBIENT
	
	// DIFFUSE
	vec3 lightvec = normalize(vlight.xyz - vvertex.xyz);
	vec3 normalvec = normalize(vnormal.xyz);
	float a = dot(lightvec, normalvec);
	// if the dot is negative, need to invert (multiply by -1) to
	// calculate the back face also.
	if(a < 0) 
		a = -1 * a;
	diffuse = a * diffuse_light.xyz;// * (0.9 * inColor);
	// END OF DIFFUSE
	
	// SPECULAR
	vec3 h = normalize(lightvec + normalize(-vvertex.xyz));
	a = dot(h, normalvec);
	// if the dot is negative, need to invert (multiply by -1) to
	// calculate the back face also.
	if(a < 0) 
		a = -1 * a;
	specular = pow(a, shiness) * specular_light.xyz;// * (0.7 * inColor);
	// END OF SPECULAR
		
	// Calculate color
	if(render_texture)
		tex = inTextureCoord;
	else
		color_by_vertex = inColor + Em;
	
	gl_PointSize = 1.0 / gl_Position.w;
}