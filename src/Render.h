#pragma once
#include "Common.h"

//
// Hight-lever render
// Based on CoreRender (GLCoreRender or DX11CoreRender)
//
class Render : public IRender
{
	ICoreRender *_pCoreRender{nullptr};
	IResourceManager *_pResMan{nullptr};
	ISceneManager *_pSceneMan{nullptr};
	IFileSystem *_fsystem{nullptr};

	WRL::ComPtr<IShaderText> _standardShader;

	WRL::ComPtr<IMesh> _axesMesh;
	WRL::ComPtr<IMesh> _axesArrowMesh;
	WRL::ComPtr<IMesh> _gridMesh;

	WRL::ComPtr<IConstantBuffer> _everyFrameParameters;

	#pragma pack(push, 4)
	struct EveryFrameParameters
	{
		vec4 main_color;
		vec4 nL;
		mat4 NM;
		mat4 MVP;
	} params;
	#pragma pack(pop)

	float _aspect{1.0f};	

	std::unordered_map<ShaderRequirement, WRL::ComPtr<IShader>, ShaderRequirement> _shaders_pool;
	
	struct TRenderMesh
	{
		ICoreMesh *mesh{nullptr};
		mat4 modelMat;
	};

	IShader* _get_shader(const ShaderRequirement &req);
	bool is_opengl();
	void _export_shader_to_file(std::list<string>& text, const string&& file);	
	void _create_render_mesh_vec(vector<TRenderMesh>& meshes);
	void _sort_meshes(vector<TRenderMesh>& meshes);

public:

	Render(ICoreRender *pCoreRender);
	~Render();

	void Init();
	void Free();
	void RenderFrame(const ICamera *pCamera);

	API PreprocessStandardShader(OUT IShader **pShader, const ShaderRequirement *shaderReq) override;
	API GetName(OUT const char **pName) override;
};

