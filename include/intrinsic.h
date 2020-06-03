#ifndef INTRINSIC_H
#define INTRINSIC_H
#endif
#include<librealsense2/rs.hpp>

using namespace rs2;

// Class containing the intrinsics information

class Intrinsic{

public:	
	float fx,fy;
	float ppx,ppy;
	float coeffs[5];// distortion coefficients
	int width,height;

	// Constructor to form empty class
	 Intrinsic();

	// Constructor to form with rs2_intrinsics struct
//	Intrinsic(const rs2::rs2_intrinsics&);

	// Constructor with float values
	//Intrinsic(int[2] dim, float[4] focals, float[5] dist);

	
	



};
