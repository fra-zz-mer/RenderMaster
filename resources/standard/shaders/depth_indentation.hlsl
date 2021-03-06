#include "common.hlsli"
#include "vertex_post.hlsli"

#ifdef ENG_SHADER_PIXEL

Texture2D depth_in : register(t0);


float mainFS(VS_OUT fs_input, float4 screenPos : SV_Position) : SV_DEPTH
{
	float depth = depth_in.Load(int3(screenPos.xy, 0)).r;

	for (int i = 0; i < 8; i++)
	{
		float d = depth_in.Load(int3(screenPos.xy + neigbors_8[i], 0)).r;
		depth = max(d, depth);
	}
	
	return depth;
}

#endif
