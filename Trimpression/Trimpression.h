#pragma once

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <opencv2/core.hpp>

typedef OpenMesh::TriMesh_ArrayKernelT<> Trimpression_Mesh;

class Trimpression
{
public:
	Trimpression(cv::Mat image);
	~Trimpression();

private:
	Trimpression_Mesh mesh;
	cv::Mat src_image;

	void generate_initial_mesh();
};

