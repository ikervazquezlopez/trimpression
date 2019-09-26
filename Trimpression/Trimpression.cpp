#include "Trimpression.h"
#include "triangulation.h"
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <iostream>



Trimpression::Trimpression(cv::Mat image)
{
	this->src_image = image;

	generate_initial_mesh();
}


Trimpression::~Trimpression()
{
}

void Trimpression::generate_initial_mesh()
{
	int img_rows = this->src_image.rows;
	int img_cols = this->src_image.cols;

	// Generate vertices for the mesh
	Trimpression_Mesh::VHandle vhandle;
	for (int r = 0; r < img_rows; r++) {
		for (int c = 0; r < img_cols; c++) {
			this->mesh.add_vertex(Trimpression_Mesh::Point(r, c, 0));
		}
	}
	
	// Create surface using delaunay triangulation
	this->mesh = Triangulation::triangulate_delaunay_mesh(this->mesh, img_cols, img_rows);
}


void Trimpression::write_mesh() {
	try
	{
		if (!OpenMesh::IO::write_mesh(mesh, "output.off"))
		{
			std::cerr << "Cannot write mesh to file 'output.off'" << std::endl;
		}
		std::cout << "Mesh written to file." << std::endl;
	}
	catch (std::exception & x)
	{
		std::cerr << x.what() << std::endl;
	}
}