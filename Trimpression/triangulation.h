#pragma once

#include "global.h"
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>


namespace Triangulation {
	std::vector<Trimpression_Mesh::VertexHandle> get_face_points(Trimpression_Mesh mesh, Trimpression_Mesh::FaceHandle fh);
	void check_delaunay(Trimpression_Mesh* out_mesh, Trimpression_Mesh::VertexHandle vh);
	Trimpression_Mesh triangulate_delaunay_mesh(Trimpression_Mesh in_mesh, float max_w, float max_h);

}