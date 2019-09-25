#include "Trimpression.h"



Trimpression::Trimpression(cv::Mat image)
{
	this->src_image = image;
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
	
}
