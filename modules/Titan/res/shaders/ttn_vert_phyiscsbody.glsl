#version 410

//mesh data from c++ program
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;

//mesh data to pass to the frag shader
layout(location = 0) out vec3 outPos;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out vec2 outUV;
layout(location = 3) out vec3 outColor;


//model, view, projection matrix
uniform mat4 MVP;

void main() {
	//calculate the position
	vec4 newPos = MVP * vec4(inPos, 1.0);

	//pass data onto the frag shader
	outPos = newPos.xyz;
	outNormal = inNormal;
	outUV = inUV;
	outColor = vec3(1, 1, 1);

	//set the position of the vertex
	gl_Position = newPos;
}