#include "Teknshi_importer.h"
#include <iostream>

using namespace std;

Importer::Importer()
{
}

Importer::~Importer()
{
}

void Importer::setAnimation(const int index)
{
	auto* stack = scene->GetSrcObject<FbxAnimStack>(index);
	// assert(stack);
	if (!stack) return;

	animation_start = stack->LocalStart.Get().GetSecondDouble();
	animation_stop = stack->LocalStop.Get().GetSecondDouble();
	cout << "Duration:" << animation_start << "-" << animation_stop << std::endl;

	animation_time = animation_start;

	scene->SetCurrentAnimationStack(stack);
}

Mesh Importer::createMesh(FbxMesh * mesh)
{
	Mesh mesh_info;

	//vertices
	int indexCount = mesh->GetPolygonVertexCount();
	int* index = mesh->GetPolygonVertices();
	for (int i = 0; i < indexCount; ++i)
	{
		auto controlPoint = mesh->GetControlPointAt(index[i]);
		mesh_info.tri_mesh.mPositions.push_back(controlPoint[0]);
		mesh_info.tri_mesh.mPositions.push_back(controlPoint[1]);
		mesh_info.tri_mesh.mPositions.push_back(controlPoint[2]);
	}

	//nomrals
	FbxArray<FbxVector4> normals;
	mesh->GetPolygonVertexNormals(normals);

	for (int i = 0; i < normals.Size(); ++i)
	{
		const FbxVector4& n = normals[i];
		mesh_info.tri_mesh.mNormals.push_back(n[0]);
		mesh_info.tri_mesh.mNormals.push_back(n[1]);
		mesh_info.tri_mesh.mNormals.push_back(n[2]);
	}

	//UV
	FbxStringList uvsetName;
	mesh->GetUVSetNames(uvsetName);

	if (uvsetName.GetCount() > 0)
	{
		FbxArray<FbxVector2> uvsets;
		mesh->GetPolygonVertexUVs(uvsetName.GetStringAt(0), uvsets);

		for (int i = 0; i < uvsets.Size(); ++i)
		{
			const FbxVector2& uv = uvsets[i];
			mesh_info.tri_mesh.mTexCoords.push_back(uv[0]);
			mesh_info.tri_mesh.mTexCoords.push_back(uv[1]);
		}
	}

	//skinning data
	mesh_info.skin = createSkin(mesh);

	return mesh_info;
}

Skin Importer::createSkin(FbxMesh * mesh)
{
	Skin skin_info;
	skin_info.has_skins = false;

	auto skinCount = mesh->GetDeformerCount(FbxDeformer::eSkin);

	if (skinCount == 0)
	{
		cout << "No skeltal animation." << std::endl;
		return skin_info;
	}

	FbxSkin* skin = static_cast<FbxSkin*>(mesh->GetDeformer(0, FbxDeformer::eSkin));
	int clusterCount = skin->GetClusterCount();

	if (clusterCount == 0)
	{
		cout << "No cluster." << std::endl;
		return skin_info;
	}

	skin_info.has_skins = true;
	skin_info.weights.resize(mesh->GetPolygonVertexCount());

	for (auto& weights : skin_info.weights)
	{
		weights.resize(clusterCount);
		std::fill(std::begin(weights), std::end(weights), 0.0);
	}

	skin_info.base_inv.resize(clusterCount);

	int vtx_indexCount = mesh->GetPolygonVertexCount();
	int* vtx_index = mesh->GetPolygonVertices();

	for (int i = 0; i < clusterCount; ++i)
	{
		FbxCluster* cluster = skin->GetCluster(i);

		assert(cluster->GetLinkMode() == FbxCluster::eNormalize);

		int indexCount = cluster->GetControlPointIndicesCount();
		int* indices = cluster->GetControlPointIndices();
		double* weights = cluster->GetControlPointWeights();

		for (int j = 0; j < indexCount; ++j)
		{
			double w = weights[j];

			for (int k = 0; k < vtx_indexCount; ++k)
			{
				if (vtx_index[k] == indices[j])
				{
					skin_info.weights[k][i] = w;
				}
			}
		}
	}
	return skin_info;
}

Material Importer::createMaterial(FbxSurfaceMaterial * material)
{
  Material mat;

  glm::vec3  ambient(0.0f, 0.0f, 0.0f);
  glm::vec3  diffuse(1.0f, 1.0f, 1.0f);
  glm::vec3  emissive(0.0f, 0.0f, 0.0f);
  glm::vec3  specular(0.0f, 0.0f, 0.0f);
  float shininess = 80.0f;

  {
	  FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sAmbient);
	  if (prop.IsValid())
	  {
		  const auto& color = prop.Get<FbxDouble3>();
		  ambient = glm::vec3(color[0], color[1], color[2]);
	  }
  }
  {
	  FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
	  if (prop.IsValid())
	  {
		  const auto& color = prop.Get<FbxDouble3>();
		  diffuse = glm::vec3(color[0], color[1], color[2]);
	  }
  }
  {
	  FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sEmissive);
	  if (prop.IsValid())
	  {
		  const auto& color = prop.Get<FbxDouble3>();
		  emissive = glm::vec3(color[0], color[1], color[2]);
	  }
  }
  {
	  FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sSpecular);
	  if (prop.IsValid())
	  {
		  const auto& color = prop.Get<FbxDouble3>();
		  specular = glm::vec3(color[0], color[1], color[2]);
	  }
  }
  {
	  FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sShininess);
	  if (prop.IsValid())
	  {
		  shininess = prop.Get<FbxDouble>();
	  }
  }

  mat.mColorAmbient = ambient;
  mat.mColorDiffuse = diffuse;
  mat.mColorSpecular = specular;
  mat.mShininess = shininess;
  mat.mColorEmission = emissive;

  //load textures todo
  mat.texture = 0;

  return mat;
}

TriMesh Importer::getDeformedTriMesh(FbxMesh * mesh, const Mesh & src_mesh, FbxAMatrix & parent_matrix, FbxTime & time)
{
	TriMesh dst_mesh = src_mesh.tri_mesh;

	FbxSkin* skin = static_cast<FbxSkin*>(mesh->GetDeformer(0, FbxDeformer::eSkin));
	int clusterCount = skin->GetClusterCount();

	std::vector<glm::mat4> matricies(clusterCount);

	FbxAMatrix inv = parent_matrix.Inverse();

	for (int i = 0; i < clusterCount; ++i)
	{
		FbxCluster* cluster = skin->GetCluster(i);

		FbxAMatrix lReferenceGlobalInitPosition;
		cluster->GetTransformMatrix(lReferenceGlobalInitPosition);

		FbxAMatrix lReferenceGeometry = GetGeometry(mesh->GetNode());
		lReferenceGlobalInitPosition *= lReferenceGeometry;

		FbxAMatrix lClusterGlobalInitPosition;
		cluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);

		FbxNode* node = cluster->GetLink();
		FbxAMatrix lClusterGlobalCurrentPosition = node->EvaluateGlobalTransform(time);

		FbxAMatrix lClusterRelativeInitPosition = lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;
		FbxAMatrix lClusterRelativeCurrentPositionInverse = inv * lClusterGlobalCurrentPosition;

		matricies[i] = getMatrix44(lClusterRelativeCurrentPositionInverse * lClusterRelativeInitPosition);
	}

	const auto& src_vtx = src_mesh.tri_mesh.mPositions;
	auto& dst_vtx = dst_mesh.mPositions;
	const auto& src_norm = src_mesh.tri_mesh.mNormals;
	auto& dst_norm = dst_mesh.mNormals;

	//for (size_t i = 0; i < src_mesh.skin.weights.size(); ++i)
	//{
	//	glm::mat4 m = matricies[0] * src_mesh.skin.weights[i][0];
	//	for (int j = 1; j < clusterCount; ++j)
	//	{
	//		if (src_mesh.skin.weights[i][j] == 0.0) continue;

	//		m += matricies[j] * src_mesh.skin.weights[i][j];
	//	}

	//	dst_vtx[i] = m.transformPoint(src_vtx[i]);
	//	if (src_mesh.tri_mesh.hasNormals()) dst_norm[i] = m.transformVec(src_norm[i]);
	//}
}

const TriMesh & Importer::getTriMesh(FbxMesh * mesh, Mesh & src_mesh, FbxAMatrix & parent_matix, FbxTime & time)
{
	// TODO: insert return statement here
}

void Importer::draw(FbxNode * node, FbxTime & time)
{
}
