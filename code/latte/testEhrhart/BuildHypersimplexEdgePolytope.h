/*
 *
 *
 *  Created on: June 15, 2010
 *      Author: bedutra
 *
 *  Computes the Ehrhart poly for hypersimplices(n, k).
 */

#ifndef BUILD_HYPERSIMPLEX_EDGE_POLYTOPE_H_
#define BUILD_HYPERSIMPLEX_EDGE_POLYTOPE_H_

#include "BuildRandomPolytope.h"



using namespace std;

class BuildHypersimplexEdgePolytope: public BuildRandomPolytope
{
private:
	int numOnes; 
public:
	BuildHypersimplexEdgePolytope(int ambient_dim, int numones);
	
	//A B C D E F G H I J K L M N O P Q R S T U V W X Y Z


	void addToPoints(vector< vector<int> > &list, vector<int> currentPoint, int base, bool addCurrent = false) const;
	void buildPolymakeFile();
	
};//BuildRandomEdgePolytope



#endif /* BUILD_HYPERSIMPLEX_EDGE_POLYTOPE_H_ */
