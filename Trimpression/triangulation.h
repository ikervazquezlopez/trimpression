#pragma once

#include "global.h"
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>


namespace Triangulation {


	Trimpression_Mesh triangulate_delaunay_mesh(Trimpression_Mesh in_mesh, float max_w, float max_h);

}