/* triangulate.cpp -- Compute triangulations.

   Copyright 2006 Matthias Koeppe

   This file is part of LattE.
   
   LattE is free software; you can redistribute it and/or modify it
   under the terms of the version 2 of the GNU General Public License
   as published by the Free Software Foundation.

   LattE is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with LattE; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
*/

#include <cstdlib>
#include "config.h"
#include "triangulation/triangulate.h"
#include "triangulation/RegularTriangulationWithCdd.h"
#ifdef HAVE_EXPERIMENTS
#  include "triangulation/RecursiveTriangulation.h"
#  include "triangulation/BoundaryTriangulation.h"
#endif
#if defined(HAVE_TOPCOM_LIB) || defined(HAVE_TOPCOM_BIN)
#  include "triangulation/TriangulationWithTOPCOM.h"
#endif
#include "print.h"

listCone *
triangulateCone(listCone *cone, int numOfVars,
		BarvinokParameters *params)
{
  listCone *result;
  if (numOfVars == lengthListVector(cone->rays)) {
    // Already simplicial.
    return copyCone(cone);
  }
  params->triangulate_time.start();
  switch(params->triangulation) {
  case BarvinokParameters::RegularTriangulationWithCdd:
    result = triangulate_cone_with_cdd(cone, params);
    break;
  case BarvinokParameters::SubspaceAvoidingRecursiveTriangulation:
#ifdef HAVE_EXPERIMENTS
    result = triangulate_cone_recursively_with_subspace_avoiding_facets
      (cone, params);
#else
    cerr << "SubspaceAvoidingRecursiveTriangulation not compiled in, sorry."
	 << endl;
    exit(1);
#endif
    break;
  case BarvinokParameters::SubspaceAvoidingBoundaryTriangulation:
#ifdef HAVE_EXPERIMENTS
    result = boundary_triangulation_of_cone_with_subspace_avoiding_facets
      (cone, params);
#else
    cerr << "SubspaceAvoidingBoundaryTriangulation not compiled in, sorry."
	 << endl;
    exit(1);
#endif
    break;
  case BarvinokParameters::PlacingTriangulationWithTOPCOM:
#if defined(HAVE_TOPCOM_LIB) || defined(HAVE_TOPCOM_BIN)
    result = triangulate_cone_with_TOPCOM(cone, numOfVars);
#else
    cerr << "PlacingTriangulationWithTOPCOM not compiled in, sorry."
	 << endl;
    exit(1);
#endif
    break;
  default:
    cerr << "Unknown triangulation method." << endl;
    exit(1);
  }
  params->triangulate_time.stop();
#if 1
  printListConeToFile("triangulation", result, numOfVars);
  cerr << "Printed triangulation to file `triangulation'" << endl;
#endif
  return result;
}