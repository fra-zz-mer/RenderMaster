#include "lang/language.h"
#include "common/common.h"

#ifdef ENG_SHADER_PIXEL

	///////////////////////
	// PIXEL SHADER
	///////////////////////

	#ifdef ENG_INPUT_TEXCOORD
		TEXTURE2D_IN(0)
	#endif

	UNIFORM_BUFFER_BEGIN(material_parameters)
		UNIFORM(vec4, main_color)
	UNIFORM_BUFFER_END

	UNIFORM_BUFFER_BEGIN(light_parameters)
		UNIFORM(vec4, nL_world)
	UNIFORM_BUFFER_END

	MAIN_FRAG(VS_OUTPUT)
		vec4 ambient = vec4(0.1f, 0.1f, 0.1f, 0.0f);

		vec4 diffuse = main_color;

		#ifdef ENG_INPUT_NORMAL
			vec3 nN = normalize(GET_ATRRIBUTE(Normal).rgb);
			diffuse = diffuse * max(dot(nN, nL_world.rgb), 0);
		#endif

		#ifdef ENG_INPUT_TEXCOORD
			vec4 tex = TEXTURE(texture0, GET_ATRRIBUTE(TexCoord));
			tex = pow(tex, vec4(0.45f, 0.45f, 0.45f, 1.0f));
			diffuse = diffuse * tex;
		#endif

		#ifdef ENG_INPUT_COLOR
			diffuse = diffuse * GET_ATRRIBUTE(Color);
		#endif

		OUT_COLOR = diffuse + ambient;
		
		// make SRGB corection later in posteffect
		//OUT_COLOR = pow(OUT_COLOR, vec4(2.2f, 2.2f, 2.2f, 2.2f));
		
	MAIN_FRAG_END

#endif
