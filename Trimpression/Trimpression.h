#pragma once

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

typedef OpenMesh::TriMesh_ArrayKernelT<> Trimpression_Mesh;

class Trimpression
{
public:
	Trimpression();
	~Trimpression();

private:
	Trimpression_Mesh mesh;

};

