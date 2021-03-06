#include "pch.h"
#include "model.h"
#include "material.h"
#include "core.h"
#include "material_manager.h"
#include "yaml.inl"
#include "mesh.h"


void Model::Copy(GameObject * original)
{
	GameObject::Copy(original);

	Model *original_model = static_cast<Model*>(original);
	meshPtr = original_model->meshPtr;
	mat_ = original_model->mat_;
}

Model::Model()
{
	type_ = OBJECT_TYPE::MODEL;
	mat_ = MAT_MAN->GetDiffuseMaterial();
}

Model::Model(StreamPtr<Mesh> mesh) : Model()
{
	meshPtr = mesh;
}

std::shared_ptr<RaytracingData> Model::GetRaytracingData(uint mat)
{
	vector<GPURaytracingTriangle>& dataIn = meshPtr.get()->GetRaytracingData()->triangles;

	if (!trianglesDataPtrWorldSpace)
	{
		trianglesDataPtrWorldSpace = shared_ptr<RaytracingData>(new RaytracingData(dataIn.size()));
		trianglesDataTransform = {};
	}

	if (memcmp(&trianglesDataTransform, &worldTransform_, sizeof(mat4)) != 0 || raytracingMaterial != mat)
	{
		raytracingMaterial = mat;

		vector<GPURaytracingTriangle>& dataOut = trianglesDataPtrWorldSpace->triangles;
		mat4 NM = worldTransform_.Inverse().Transpose();

		for (int i = 0; i < dataIn.size(); ++i)
		{
			GPURaytracingTriangle& ti = dataIn[i];
			GPURaytracingTriangle& to = dataOut[i];

			to.p0 = worldTransform_ * ti.p0;
			to.p1 = worldTransform_ * ti.p1;
			to.p2 = worldTransform_ * ti.p2;

			to.n = NM * ti.n;

			to.materialID = mat;
		}

		trianglesDataTransform = worldTransform_;
	}

	return trianglesDataPtrWorldSpace;
}

auto DLLEXPORT Model::GetMesh() -> Mesh *
{
	return meshPtr.get();
}
auto DLLEXPORT Model::GetMeshPath() -> const char *
{
	return meshPtr.path().c_str();
}

auto DLLEXPORT Model::GetWorldCenter() -> vec3
{
	vec3 center = meshPtr.isLoaded() ? meshPtr.get()->GetCenter() : vec3();
	vec4 centerWS = worldTransform_ * vec4(center);
	return (vec3)centerWS;
}

auto DLLEXPORT Model::GetTrinaglesWorldSpace(std::unique_ptr<vec3[]>& out, uint* trinaglesNum) -> void
{
}

auto DLLEXPORT Model::Clone() -> GameObject *
{
	Model *m = new Model;
	m->Copy(this);
	return m;
}

void Model::SaveYAML(void * yaml)
{
	GameObject::SaveYAML(yaml);

	YAML::Emitter *_n = static_cast<YAML::Emitter*>(yaml);
	YAML::Emitter& n = *_n;

	if (!meshPtr.path().empty())
		n << YAML::Key << "mesh" << YAML::Value << meshPtr.path();

	if (mat_)
		n << YAML::Key << "material" << YAML::Value << mat_->GetId();
}

void Model::LoadYAML(void * yaml)
{
	GameObject::LoadYAML(yaml);

	YAML::Node *_n = static_cast<YAML::Node*>(yaml);
	YAML::Node& n = *_n;

	if (n["material"])
	{
		string mat = n["material"].as<string>();
		mat_ = MAT_MAN->GetMaterial(mat.c_str());
	}
}

