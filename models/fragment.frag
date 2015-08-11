//[FRAGMENT SHADER]
#version 330 core
#extension GL_EXT_gpu_shader4 : enable

//in int gl_PrimitiveID;
 
smooth out vec4 outputColor;

uniform sampler2D inTexture;
uniform bool render_texture;
uniform bool is_selected_object;

uniform int select_array_ids[50];
uniform int focus_id;

smooth in vec3 ambient;
smooth in vec3 diffuse;
smooth in vec3 specular;

smooth in vec3 color_by_vertex;
smooth in vec2 tex;

void main()
{	
	vec3 amb, spe;
	if(gl_FrontFacing)
	{
		amb = ambient;
		spe = specular;
	}
	else
	{
		amb = 0.4 * ambient;
		spe = 0.8 * specular;
		//discard;
	}
		
	vec3 color = vec3(1.0, 1.0, 1.0);
	//if(render_texture)
	//{	
		// image is storege as blue-green-red (bgr)
		//color = texture(inTexture, tex).bgr;	
	//}
	//else
	{
		// entire object is select
		if(is_selected_object)
			color = vec3(1.0, 1.0, 1.0);
		else
		{
			if(render_texture)
			{	
				// image is storege as blue-green-red (bgr)
				color = texture(inTexture, tex).bgr;	
			}
			else
			{
				// use object color as default
				color = color_by_vertex;
			}
			
			if(focus_id == gl_PrimitiveID)
				color = vec3(1.0, 1.0, 1.0);
			else
			{
				// first element of array is the size of selected objects
				// check if has selected elements
				if(select_array_ids[0] > 0)
				{
					// find gl_PrimitiveID is in the array
					int i;
					for(i = 1; i < select_array_ids[0] + 1; i++)
					{
						if(select_array_ids[i] == gl_PrimitiveID)
						{
							color = vec3(1.0, 1.0, 1.0);
							break;
						}
					}
				}
			}
		}
	}
	
	outputColor = vec4 ((amb     * (color * 0.6)) +
						(diffuse * (color * 0.9)) +
						(spe     * (color * 0.7)), 
						1.0);
}