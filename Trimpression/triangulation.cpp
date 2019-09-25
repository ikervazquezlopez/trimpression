#include "triangulation.h"

Trimpression_Mesh Triangulation::triangulate_delaunay_mesh(Trimpression_Mesh in_mesh, float max_w, float max_h)
{
	Trimpression_Mesh::VertexHandle vhandle[3];
	Trimpression_Mesh::FaceHandle fhandle;
	Trimpression_Mesh out_mesh;

	// Generate first container vertices
	vhandle[0] = out_mesh.add_vertex(Trimpression_Mesh::Point(max_w / 2, max_h * 4, 0));
	vhandle[1] = out_mesh.add_vertex(Trimpression_Mesh::Point(-max_w * 4, max_h * 4, 0));
	vhandle[2] = out_mesh.add_vertex(Trimpression_Mesh::Point(max_w * 4, -max_h * 4, 0));

	// Generate first container face
	std::vector<Trimpression_Mesh::VertexHandle>  face_vhandles;
	face_vhandles.push_back(vhandle[0]);
	face_vhandles.push_back(vhandle[1]);
	face_vhandles.push_back(vhandle[2]);
	out_mesh.add_face(face_vhandles);

	Trimpression_Mesh::FaceIter fit;

	for (fit = out_mesh.faces_begin(); fit != out_mesh.faces_end(); ++fit) {

	}

	return Trimpression_Mesh();
}
