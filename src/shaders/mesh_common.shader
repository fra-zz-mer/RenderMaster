// Constant buffer
CONSTANT_BUFFER_BEGIN(mesh_veretx)
	CONSTANT(mat4, MVP)
	CONSTANT(vec4, main_color)
#ifdef ENG_INPUT_NORMAL
	CONSTANT(mat4, NM)
	CONSTANT(vec3, nL)
#endif
CONSTANT_BUFFER_END()


// Iterpolated Attributes
#ifdef ENG_INPUT_NORMAL
ATTRIBUTE(0, vec3, Normal)
#endif
#ifdef ENG_INPUT_TEXCOORD
ATTRIBUTE(1, vec2, TexCoord)
#endif
#ifdef ENG_INPUT_COLOR
ATTRIBUTE(2, vec4, Color)
#endif
