#pragma once

//// July 25 2017, revised on Sept 28 2017
//// Jungwon Kang

/*
//// Header for OpenCV (ver 2.4.13.2)
#include "opencv\cv.h"
#include "opencv\highgui.h"

#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/nonfree/nonfree.hpp"
*/

//// Header for OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace cv;
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class CLibTrilateration
{
public:
	CLibTrilateration();
	~CLibTrilateration();

	void	test0();
	void	test1();
	void	test2();
	void	test_accuracy_tri_num_pnt_ref4();
	void	test_accuracy_tri_num_pnt_ref4_one_sample();
	void	test_lsrec();
	void	test_rec_tri_np3();

	int		run_tri_recursive_np4(const double* Mat_pnt_ref, const double* Vec_dist_mea, const double* Vec_weight, const int Num_pnt_ref, double* Vec_out);
	void	compute_vec_w(const double* Vec_in, const int Size_vec, const double Val_thres, double* Vec_w_out);

private:
	int		_rec_tri_npX(const double* Mat_pnt_ref, const double* Vec_dist_mea, const int Num_pnt_ref, const int IDX_row_a, const int IDX_row_b, const int IDX_row_c, double* Mat_out);
	int		_rec_tri_np3(const double* Mat_pnt_ref, const double* Vec_dist_mea, const int Num_pnt_ref, double* Vec_out1, double* Vec_out2);

	void	_lsrec(const double Val_yn, const double* Vec_an, const double* Vec_x, const double* Mat_p, double* Vec_xn_out, double* Mat_pn_out);

};


// << hierarchy >>
// test_accuracy_tri_num_pnt_ref4()
//		run_tri_recursive_np4() : corresponds to [IPINTrilaterationExampleB.m]
//			_rec_tri_npX()		: corresponds to [RecTrilateration.m] (np > 3 case)
//				_rec_tri_np3()	: corresponds to [RecTrilateration.m] (np == 3 case)
//				_lsrec()		: corresponds to [lsrec.m]


