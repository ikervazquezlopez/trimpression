#include "triangulation.h"
#include "utils.h"


std::vector<Trimpression_Mesh::VertexHandle> Triangulation::get_face_points(Trimpression_Mesh mesh, Trimpression_Mesh::FaceHandle fh) {
	Trimpression_Mesh::FaceVertexIter fvit;
	std::vector<Trimpression_Mesh::VertexHandle> face_vertices;
	for (fvit = mesh.fv_begin(fh); fvit != mesh.fv_end(fh); ++fvit) {
		Trimpression_Mesh::VertexHandle vh = mesh.vertex_handle(fvit->idx());
		face_vertices.push_back(vh);
	}
	return face_vertices;
}

void Triangulation::check_delaunay(Trimpression_Mesh *out_mesh, Trimpression_Mesh::VertexHandle vh) {
	Trimpression_Mesh::VertexOHalfedgeIter voheit;
	Trimpression_Mesh::FaceHandle fh;
	std::vector<Trimpression_Mesh::VertexHandle> check_vertices, face_vertices, tmp_vertices;
	for (voheit = out_mesh->voh_begin(vh); voheit != out_mesh->voh_end(vh); ++voheit) {
		Trimpression_Mesh::HalfedgeHandle heh = out_mesh->next_halfedge_handle(out_mesh->halfedge_handle(voheit));

		// Check if delaunay propertie holds
		face_vertices = get_face_points(*out_mesh, out_mesh->face_handle(heh));
		Trimpression_Mesh::Point p = out_mesh->point(out_mesh->opposite_he_opposite_vh(heh));
		bool in_circle = point_in_circle(p, out_mesh->point(face_vertices[0]), out_mesh->point(face_vertices[1]), out_mesh->point(face_vertices[2]));

		if (in_circle && out_mesh->is_flip_ok(out_mesh->edge_handle(heh))) {
			out_mesh->flip(out_mesh->edge_handle(heh));

			// Add vertices of the first face for rechecking
			fh = out_mesh->face_handle(heh);
			tmp_vertices = get_face_points(*out_mesh, fh);
			check_vertices.insert(check_vertices.end(), tmp_vertices.begin(), tmp_vertices.end());

			// Add vertices of the second face for rechecking
			fh = out_mesh->opposite_face_handle(heh);
			tmp_vertices = get_face_points(*out_mesh, fh);
			check_vertices.insert(check_vertices.end(), tmp_vertices.begin(), tmp_vertices.end());
		}
	}

	for (Trimpression_Mesh::VertexHandle v : check_vertices) {
		check_delaunay(out_mesh, v);
	}
}

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
	Trimpression_Mesh::VertexIter in_vit;
	Trimpression_Mesh::FaceVertexIter out_fvit;

	for (in_vit = in_mesh.vertices_begin(); in_vit != in_mesh.vertices_end(); ++in_vit) {
		Trimpression_Mesh::Point p = in_mesh.point(in_mesh.vertex_handle(in_vit->idx()));
		for (fit = out_mesh.faces_sbegin(); fit != out_mesh.faces_end(); ++fit) {
			Trimpression_Mesh::FaceHandle fh = out_mesh.face_handle(fit->idx());
			std::vector<Trimpression_Mesh::VertexHandle> face_vertices = get_face_points(out_mesh, fh);
			bool in_circle = point_in_circle(p, out_mesh.point(face_vertices[0]), out_mesh.point(face_vertices[1]), out_mesh.point(face_vertices[2]));
			if (in_circle) {
				Trimpression_Mesh::VertexHandle vh = out_mesh.split(fh, p);
				check_delaunay(&out_mesh, vh);
				break;
			}
		}
	}

	return out_mesh;
}
