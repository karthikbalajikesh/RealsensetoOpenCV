#include"intrinsic.h"

Intrinsic::Intrinsic():fx(0),fy(0),ppx(0),ppy(0),width(640),height(480){

	for(int i=0;i<5;i++){

	coeffs[i] = 0;

	}

}
/*
Intrinsic::Intrinsic(const rs2_intrinsics &data){

	fx = data.fx;
	fy = data.fy;
	ppx = data.ppx;
	ppy = data.ppy;
	width = data.width;
	height = data.height;
	coeffs = data.coeffs;

}*/
