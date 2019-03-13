//#include "stdafx.h"
#include "LibTrilateration.h"


CLibTrilateration::CLibTrilateration()
{
}


CLibTrilateration::~CLibTrilateration()
{
}

void CLibTrilateration::test0()
{
	//// testing simple opencv

	string fname_img = "C:\\Users\\JUNGWONKANG\\Desktop\\test_img.jpg";

	Mat img = imread(fname_img, CV_LOAD_IMAGE_COLOR);
	imshow("opencv", img);
	waitKey(0);

	destroyAllWindows();
	
}

void CLibTrilateration::test1()
{
	//// testing opencv-svd
	
	double in[9] = { 1,2,3,4,5,6,7,8,9 };


	Mat mat_in(cv::Size(3, 3), CV_64FC1, in);
	Mat mat_u, mat_s, mat_v;

	SVDecomp(mat_in, mat_s, mat_u, mat_v);

	cout << mat_s << endl;
	cout << mat_u << endl;
	cout << mat_v << endl;

	printf("<<mat_s>>\n");
	printf("mat_s(0,0): %lf\n", mat_s.at<double>(0, 0));
	printf("mat_s(1,0): %lf\n", mat_s.at<double>(1, 0));
	printf("mat_s(2,0): %lf\n", mat_s.at<double>(2, 0));
	printf("\n");

	printf("<<mat_u>>\n");
	printf("mat_u(0,0): %lf\n", mat_u.at<double>(0, 0));
	printf("mat_u(1,0): %lf\n", mat_u.at<double>(1, 0));
	printf("mat_u(2,0): %lf\n", mat_u.at<double>(2, 0));
	printf("\n");
	printf("mat_u(0,1): %lf\n", mat_u.at<double>(0, 1));
	printf("mat_u(1,1): %lf\n", mat_u.at<double>(1, 1));
	printf("mat_u(2,1): %lf\n", mat_u.at<double>(2, 1));
	printf("\n");
	printf("mat_u(0,2): %lf\n", mat_u.at<double>(0, 2));
	printf("mat_u(1,2): %lf\n", mat_u.at<double>(1, 2));
	printf("mat_u(2,2): %lf\n", mat_u.at<double>(2, 2));
	printf("\n");

	printf("<<mat_v>>\n");
	printf("mat_v(0,0): %lf\n", mat_v.at<double>(0, 0));
	printf("mat_v(1,0): %lf\n", mat_v.at<double>(1, 0));
	printf("mat_v(2,0): %lf\n", mat_v.at<double>(2, 0));
	printf("\n");
	printf("mat_v(0,1): %lf\n", mat_v.at<double>(0, 1));
	printf("mat_v(1,1): %lf\n", mat_v.at<double>(1, 1));
	printf("mat_v(2,1): %lf\n", mat_v.at<double>(2, 1));
	printf("\n");
	printf("mat_v(0,2): %lf\n", mat_v.at<double>(0, 2));
	printf("mat_v(1,2): %lf\n", mat_v.at<double>(1, 2));
	printf("mat_v(2,2): %lf\n", mat_v.at<double>(2, 2));


}

void CLibTrilateration::test2()
{
	//// testing compute_vec_w()

	double vec_err[4];

	vec_err[0] = 0.287252050630289;
	vec_err[1] = 0.289466560559783;
	vec_err[2] = 0.047283924503264;
	vec_err[3] = 0.291177834528185;


	double vec_w_out[4];

	compute_vec_w(vec_err, 4, 0.3, vec_w_out);


	for (int i = 0; i < 4; i++)
	{
		printf("vec_w[%d]: (%lf)", i, vec_w_out[i]);
	}


}


void CLibTrilateration::test_accuracy_tri_num_pnt_ref4()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// testing accuracy (recursive) (num_pnt_ref = 4)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	printf("running test_accuracy_tri_num_pnt_ref4...\n");

	RNG rng(0xFFFFFFFF);

	
	int i;

	const bool b_add_noise = true;

	const int width_mat_pnt_ref = 3;	// DO NOT EDIT


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// set input
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//// set num of reference pnts being measured
	const int num_pnt_ref = 4;		// DO NOT EDIT


	//// reference pnt coordinates
	double mat_pnt_ref[4 * 3];

	mat_pnt_ref[0 * width_mat_pnt_ref + 0] = 0.0;		// row0: TD100
	mat_pnt_ref[0 * width_mat_pnt_ref + 1] = 0.0;
	mat_pnt_ref[0 * width_mat_pnt_ref + 2] = 0.6;

	mat_pnt_ref[1 * width_mat_pnt_ref + 0] = 5.0;		// row1: TD101
	mat_pnt_ref[1 * width_mat_pnt_ref + 1] = 0.0;
	mat_pnt_ref[1 * width_mat_pnt_ref + 2] = 0.9;

	mat_pnt_ref[2 * width_mat_pnt_ref + 0] = 0.0;		// row2: TD102
	mat_pnt_ref[2 * width_mat_pnt_ref + 1] = 5.0;
	mat_pnt_ref[2 * width_mat_pnt_ref + 2] = 1.2;

	mat_pnt_ref[3 * width_mat_pnt_ref + 0] = 5.0;		// row3: TD103
	mat_pnt_ref[3 * width_mat_pnt_ref + 1] = 5.0;
	mat_pnt_ref[3 * width_mat_pnt_ref + 2] = 1.8;
		// completed to set
		//		mat_pnt_ref[]
		//		num_pnt_ref



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// loop
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double x_pos_ref, y_pos_ref, z_pos_ref;
	double x_mover_gt, y_mover_gt;
	double range_gt[4];
	double range_in[4];
	double w_set_unorm[4];
	double w_set_norm[4];
	
	double mag_noise;
	double dx_temp, dy_temp, dz_temp;
	double range2_temp;

	int idx_iter;
	int idx_noise;

	const	int		totnum_iter = 1000;		// EDIT
	const	double	z_mover_gt = 2.0;		// EDIT

	double vec_mag_noise[11];

	for (i = 0; i < 11; i++)
	{
		vec_mag_noise[i] = ((double)i)*0.1;
	}


	//// variable for performance
	int    _cnt_try;
	double _err_x, _err_y, _err_z, _err_xyz;
	double _sum_err_x, _sum_err_y, _sum_err_z, _sum_err_xyz;
	double _err_x_mean, _err_y_mean, _err_z_mean, _err_xyz_mean;

	double _vec_err_x_mean_on_noise[11];
	double _vec_err_y_mean_on_noise[11];
	double _vec_err_z_mean_on_noise[11];
	double _vec_err_xyz_mean_on_noise[11];


	for(idx_noise = 0; idx_noise < 11; idx_noise++)
	{
		//// set mag_noise
		mag_noise = vec_mag_noise[idx_noise];

		//// init cnt_try
		_sum_err_x = 0.0;
		_sum_err_y = 0.0;
		_sum_err_z = 0.0;
		_sum_err_xyz = 0.0;
		_cnt_try = 0;

		printf("  mag_noise:(%.2lf)...\n", mag_noise);

		for (idx_iter = 0; idx_iter < totnum_iter; idx_iter++)
		{

			for (y_mover_gt = -5.0; y_mover_gt <= 10.0; y_mover_gt += 1.0)
			{
				for (x_mover_gt = -5.0; x_mover_gt <= 10.0; x_mover_gt += 1.0)
				{
					//// note that [x_mover_gt, y_mover_gt, z_mover_gt] are mover's pos.

					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//// compute range_gt
					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					for (i = 0; i < 4; i++)
					{
						x_pos_ref = mat_pnt_ref[i * width_mat_pnt_ref + 0];
						y_pos_ref = mat_pnt_ref[i * width_mat_pnt_ref + 1];
						z_pos_ref = mat_pnt_ref[i * width_mat_pnt_ref + 2];

						dx_temp = x_mover_gt - x_pos_ref;
						dy_temp = y_mover_gt - y_pos_ref;
						dz_temp = z_mover_gt - z_pos_ref;

						range2_temp = (dx_temp*dx_temp) + (dy_temp*dy_temp) + (dz_temp*dz_temp);
						range_gt[i] = sqrt(range2_temp);
					}
					// completed to set
					//		range_gt[]: (num_pnt_ref x 1)


					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//// set range
					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					range_in[0] = range_gt[0];
					range_in[1] = range_gt[1];
					range_in[2] = range_gt[2];
					range_in[3] = range_gt[3];


					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//// add noise
					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					double val_noise;
					double val_noise_abs;
					double val_temp_term;
					double val_temp_norm_w = 0.0;

					for (i = 0; i < 4; i++)
					{
						//// adding
						val_noise = rng.uniform(-1.0*mag_noise, mag_noise);
						range_in[i] = range_in[i] + val_noise;
						
						//// compute w_set
						val_noise_abs = val_noise;
						if (val_noise < 0.0) { val_noise_abs = -1.0*val_noise; }

						val_temp_term = (val_noise_abs / mag_noise);
						w_set_unorm[i] = 1.0 - (val_temp_term*val_temp_term);

						//// sum
						val_temp_norm_w += (w_set_unorm[i] * w_set_unorm[i]);
					}
					// completed to set
					//		range_in[]
					//		w_set_unorm[]
					//		val_temp_norm_w


					//// normalize
					double norm_w = sqrt(val_temp_norm_w);

					w_set_norm[0] = w_set_unorm[0] / norm_w;
					w_set_norm[1] = w_set_unorm[1] / norm_w;
					w_set_norm[2] = w_set_unorm[2] / norm_w;
					w_set_norm[3] = w_set_unorm[3] / norm_w;
						// completed to set
						//		w_set_norm[]


					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//// run trilateration
					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					double vec_pos_est[3];

					run_tri_recursive_np4(mat_pnt_ref, range_in, w_set_norm, num_pnt_ref, vec_pos_est);
						// completed to set
						//		vec_pos_est[]: x,y,z


					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//// show res
					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (0)
					{
						printf("== [%d] iter ==\n", idx_iter);
						printf("  pos_gt  - x:(%.4lf), y:(%.4lf), z:(%.4lf)\n", x_mover_gt, y_mover_gt, z_mover_gt);
						printf("  range_gt - [0]:(%.4lf), [1]:(%.4lf), [2]:(%.4lf), [3]:(%.4lf)\n", range_gt[0], range_gt[1], range_gt[2], range_gt[3]);
						printf("  range_in - [0]:(%.4lf), [1]:(%.4lf), [2]:(%.4lf), [3]:(%.4lf)\n", range_in[0], range_in[1], range_in[2], range_in[3]);
						printf("  d_range  - [0]:(%.4lf), [1]:(%.4lf), [2]:(%.4lf), [3]:(%.4lf)\n", (range_in[0] - range_gt[0]), (range_in[1] - range_gt[1]), (range_in[2] - range_gt[2]), (range_in[3] - range_gt[3]));
						printf("  pos_est - x:(%.4lf), y:(%.4lf), z:(%.4lf)\n", vec_pos_est[0], vec_pos_est[1], vec_pos_est[2]);
						printf("\n");
					}



					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//// compute err (for measuring performance)
					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					double x_mover_est = vec_pos_est[0];
					double y_mover_est = vec_pos_est[1];
					double z_mover_est = vec_pos_est[2];


					//// compute err
					_err_x = (x_mover_est - x_mover_gt);
					_err_y = (y_mover_est - y_mover_gt);
					_err_z = (z_mover_est - z_mover_gt);

					if ( _err_x < 0.0 ) { _err_x = -1.0*_err_x; }
					if ( _err_y < 0.0 ) { _err_y = -1.0*_err_y; }
					if ( _err_z < 0.0 ) { _err_z = -1.0*_err_z; }

					_err_xyz = (_err_x*_err_x) + (_err_y*_err_y) + (_err_z*_err_z);
					_err_xyz = sqrt( _err_xyz );


					//// update sum_err
					_sum_err_x   += _err_x;
					_sum_err_y   += _err_y;
					_sum_err_z   += _err_z;
					_sum_err_xyz += _err_xyz;


					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//// update cnt (for measuring performance)
					////////////////////////////////////////////////////////////////////////////////////////////////////////////
					_cnt_try++;
				}
			}
		} // <- idx_iter


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//// compute mean err (for measuring performance)
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		_err_x_mean   = _sum_err_x / ((double)_cnt_try);
		_err_y_mean   = _sum_err_y / ((double)_cnt_try);
		_err_z_mean   = _sum_err_z / ((double)_cnt_try);
		_err_xyz_mean = _sum_err_xyz / ((double)_cnt_try);


		_vec_err_x_mean_on_noise[idx_noise] = _err_x_mean;
		_vec_err_y_mean_on_noise[idx_noise] = _err_y_mean;
		_vec_err_z_mean_on_noise[idx_noise] = _err_z_mean;
		_vec_err_xyz_mean_on_noise[idx_noise] = _err_xyz_mean;

	} // <- idx_noise


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// print out mean err depending on noise
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (idx_noise = 0; idx_noise < 11; idx_noise++)
	{
		mag_noise = vec_mag_noise[idx_noise];

		_err_x_mean = _vec_err_x_mean_on_noise[idx_noise];
		_err_y_mean = _vec_err_y_mean_on_noise[idx_noise];
		_err_z_mean = _vec_err_z_mean_on_noise[idx_noise];
		_err_xyz_mean = _vec_err_xyz_mean_on_noise[idx_noise];

		printf(" idx_noise:[%d], mag_noise:(%.2lf) - err_x_m:(%.4lf), err_y_m:(%.4lf), err_z_m:(%.4lf), err_xyz_m:(%.4lf)\n", idx_noise, mag_noise, _err_x_mean, _err_y_mean, _err_z_mean, _err_xyz_mean);
	}


	

}


void CLibTrilateration::test_accuracy_tri_num_pnt_ref4_one_sample()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// testing accuracy (recursive) (num_pnt_ref = 4)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	printf("running test_accuracy_tri_num_pnt_ref4 (one sample)...\n");

	RNG rng(0xFFFFFFFF);


	const int width_mat_pnt_ref = 3;	// DO NOT EDIT


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// set input (UWB station pos)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//// set num of reference pnts being measured
	const int num_pnt_ref = 4;		// DO NOT EDIT

	//// reference pnt coordinates
	double mat_pnt_ref[4 * 3];

	mat_pnt_ref[0 * width_mat_pnt_ref + 0] = 0.0;		// row0: TD100
	mat_pnt_ref[0 * width_mat_pnt_ref + 1] = 0.0;
	mat_pnt_ref[0 * width_mat_pnt_ref + 2] = 0.6;

	mat_pnt_ref[1 * width_mat_pnt_ref + 0] = 5.0;		// row1: TD101
	mat_pnt_ref[1 * width_mat_pnt_ref + 1] = 0.0;
	mat_pnt_ref[1 * width_mat_pnt_ref + 2] = 1.2;

	mat_pnt_ref[2 * width_mat_pnt_ref + 0] = 0.0;		// row2: TD102
	mat_pnt_ref[2 * width_mat_pnt_ref + 1] = 5.0;
	mat_pnt_ref[2 * width_mat_pnt_ref + 2] = 0.9;

	mat_pnt_ref[3 * width_mat_pnt_ref + 0] = 5.0;		// row3: TD103
	mat_pnt_ref[3 * width_mat_pnt_ref + 1] = 5.0;
	mat_pnt_ref[3 * width_mat_pnt_ref + 2] = 1.8;
		// completed to set
		//		mat_pnt_ref[]
		//		num_pnt_ref


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// set input (Range)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double range_in[4];
	double w_set_norm[4];

	//// set range
	range_in[0] = 11.063439051961057;
	range_in[1] = 10.189295505521354;
	range_in[2] = 9.547459994442640;
	range_in[3] = 8.473599481785854;

	//// set w_set_norm
	w_set_norm[0] = 0.525560349777809;
	w_set_norm[1] = 0.430376983745016;
	w_set_norm[2] = 0.518711311844691;
	w_set_norm[3] = 0.519134419556563;



	//// set range
  //range_in[0] = 10.886501142739801;
  //range_in[1] = 12.775871161344950;
  //range_in[2] = 13.935312136941223;
  //range_in[3] = 14.950713130491113;

	//// set w_set_norm
  //w_set_norm[0] = 0.462229841142935;
  //w_set_norm[1] = 0.578928218585777;
  //w_set_norm[2] = 0.643930171779180;
  //w_set_norm[3] = 0.191153408430277;



	LARGE_INTEGER freq;
	LARGE_INTEGER t1, t2;
	double elapsedTime = 0.0;

	QueryPerformanceFrequency(&freq);		// get ticks per second
	QueryPerformanceCounter(&t1);			// start timer


	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// run trilateration
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double vec_pos_est[3];

	run_tri_recursive_np4(mat_pnt_ref, range_in, w_set_norm, num_pnt_ref, vec_pos_est);
	// completed to set
	//		vec_pos_est[]: x,y,z


	QueryPerformanceCounter(&t2);	// stop timer
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq.QuadPart;

	printf("	>> elapsedTime: %4.2lf(ms)\n", elapsedTime);



	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// compute err (for measuring performance)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double x_mover_est = vec_pos_est[0];
	double y_mover_est = vec_pos_est[1];
	double z_mover_est = vec_pos_est[2];

	printf("x_mover_est: (%.4lf)\n", x_mover_est);
	printf("y_mover_est: (%.4lf)\n", y_mover_est);
	printf("z_mover_est: (%.4lf)\n", z_mover_est);
*/


}


void CLibTrilateration::test_lsrec()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// testing lsrec()
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	double val_yn;
	double vec_an[4];
	double vec_x [4];
	double mat_p [16];

	
	val_yn = -209.756078000000;

	vec_an[0] = 1.0; 
	vec_an[1] = -34.2260000000000;
	vec_an[2] = 6.00600000000000;
	vec_an[3] = -4.34000000000000;

	vec_x[0] = 720.693061191388;
	vec_x[1] = 26.7726255260942;
	vec_x[2] = -1.33886086567982;
	vec_x[3] = 1.45843587903896;

	mat_p[0 * 4 + 0] = 1.0;		mat_p[0 * 4 + 1] = 0.0;		mat_p[0 * 4 + 2] = 0.0;		mat_p[0 * 4 + 3] = 0.0;
	mat_p[1 * 4 + 0] = 0.0;		mat_p[1 * 4 + 1] = 1.0;		mat_p[1 * 4 + 2] = 0.0;		mat_p[1 * 4 + 3] = 0.0;
	mat_p[2 * 4 + 0] = 0.0;		mat_p[2 * 4 + 1] = 0.0;		mat_p[2 * 4 + 2] = 1.0;		mat_p[2 * 4 + 3] = 0.0;
	mat_p[3 * 4 + 0] = 0.0;		mat_p[3 * 4 + 1] = 0.0;		mat_p[3 * 4 + 2] = 0.0;		mat_p[3 * 4 + 3] = 1.0;


	double vec_xn_out[4];
	double mat_pn_out[16];

	_lsrec(val_yn, vec_an, vec_x, mat_p, vec_xn_out, mat_pn_out);


}

void CLibTrilateration::test_rec_tri_np3()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// testing _rec_tri_np3
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// adopted from IPINTrilaterationExampleA.m

	printf("running test_rec_tri_np3()...\n");


	int idx_pnt;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// set input
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//// set num of reference pnts being measured
	int	num_pnt_ref = 3;


	//// reference pnt coordinates
	double* mat_pnt_ref = new double[num_pnt_ref * 3];

	mat_pnt_ref[0 * 3 + 0] = 27.297;		// row0: P37
	mat_pnt_ref[0 * 3 + 1] = -4.953;
	mat_pnt_ref[0 * 3 + 2] = 1.47;

	mat_pnt_ref[1 * 3 + 0] = 25.475;		// row1: P31
	mat_pnt_ref[1 * 3 + 1] = -6.124;
	mat_pnt_ref[1 * 3 + 2] = 2.36;

	mat_pnt_ref[2 * 3 + 0] = 22.590;		// row2: P102
	mat_pnt_ref[2 * 3 + 1] = 0.524;
	mat_pnt_ref[2 * 3 + 2] = 1.2;
	// completed to set
	//		num_pnt_ref
	//		mat_pnt_ref


	//// measured distance between current pnt and reference pnts
	double* vec_dist_mea = new double[num_pnt_ref];

	vec_dist_mea[0] = 3.851;
	vec_dist_mea[1] = 3.875;
	vec_dist_mea[2] = 3.514;



	// debug - checking mat_pnt_ref & vec_dist_mea
	if (0)
	{
		//// show mat_pnt_ref
		printf("== mat_pnt_ref ==\n");

		double x_pnt, y_pnt, z_pnt;

		for (idx_pnt = 0; idx_pnt < num_pnt_ref; idx_pnt++)
		{
			x_pnt = mat_pnt_ref[idx_pnt * 3 + 0];
			y_pnt = mat_pnt_ref[idx_pnt * 3 + 1];
			z_pnt = mat_pnt_ref[idx_pnt * 3 + 2];

			printf("idx_pnt:[%d] - x:(%lf), y:(%lf), z:(%lf)\n", idx_pnt, x_pnt, y_pnt, z_pnt);
		}


		//// show vec_dist_mea
		printf("== vec_dist_mea ==\n");

		for (idx_pnt = 0; idx_pnt < num_pnt_ref; idx_pnt++)
		{
			printf("idx_pnt:[%d] - dist_mea:(%lf)\n", idx_pnt, vec_dist_mea[idx_pnt]);
		}

	}



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// run trilateration
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double vec_pos1[4], vec_pos2[4];

	_rec_tri_np3(mat_pnt_ref, vec_dist_mea, num_pnt_ref, vec_pos1, vec_pos2);
		// completed to set
		//		vec_pos1[]: (4 x 1), (x^2+y^2+x^2), x, y, z
		//		vec_pos2[]: (4 x 1), (x^2+y^2+x^2), x, y, z


	//// debug
	if (0)
	{
		printf("== vec_pos1[] ===\n");
		printf(" [0]: (%lf)\n", vec_pos1[0]);
		printf(" [1]: (%lf)\n", vec_pos1[1]);
		printf(" [2]: (%lf)\n", vec_pos1[2]);
		printf(" [3]: (%lf)\n", vec_pos1[3]);
		printf("\n");
		printf("== vec_pos2[] ===\n");
		printf(" [0]: (%lf)\n", vec_pos2[0]);
		printf(" [1]: (%lf)\n", vec_pos2[1]);
		printf(" [2]: (%lf)\n", vec_pos2[2]);
		printf(" [3]: (%lf)\n", vec_pos2[3]);


		// <matlab result>
		// vec_pos1[]
		//	[1]: 24.3506
		//  [2]: -2.4811
		//  [3]: 1.6667

		// vec_pos2[]
		//  [1]: 24.3123
		//  [2]: -2.5205
		//  [3]: 1.5365
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// release
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	delete[] mat_pnt_ref;
	delete[] vec_dist_mea;



}

void CLibTrilateration::compute_vec_w(const double* Vec_in, const int Size_vec, const double Val_thres, double* Vec_w_out)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// convert ranging error data into weight vector 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Vec_in[]: (1 x Size_vec), ranging error from time domain UWB sensor


	int i;
	double val_err_in;
	double val_temp;
	double val_sum_w_unorm = 0.0;

	double* w_set_unorm = new double[Size_vec];
	double* w_set_norm  = new double[Size_vec];


	//// set w_set_unorm[]
	for (i = 0; i < Size_vec; i++)
	{
		val_err_in = Vec_in[i];
		val_temp = (val_err_in / Val_thres);

		if (val_temp > 1.0) { val_temp = 1.0; }

		w_set_unorm[i] = 1.0 - (val_temp*val_temp);
		val_sum_w_unorm += (w_set_unorm[i] * w_set_unorm[i]);
	}
	// completed to set
	//		w_set_unorm[]: (1 x Size_vec)
	//		val_sum_w_unorm


	//// normalize
	double norm_w = sqrt(val_sum_w_unorm);

	for (i = 0; i < Size_vec; i++)
	{
		w_set_norm[i] = (w_set_unorm[i] / norm_w);
	}
	// completed to set
	//		w_set_norm[]: (1 x Size_vec)


	//// copy for output
	for (i = 0; i < Size_vec; i++)
	{
		Vec_w_out[i] = w_set_norm[i];
	}


	//// release
	delete [] w_set_unorm;
	delete [] w_set_norm;


}


int CLibTrilateration::run_tri_recursive_np4(const double* Mat_pnt_ref, const double* Vec_dist_mea, const double* Vec_weight, const int Num_pnt_ref, double* Vec_out)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// run trilateration (recursive) (corresponding to IPINTrilaterationExampleB.m)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Note that Num_pnt_ref should be 4.

	// [Input]
	//	Mat_pnt_ref []: (Num_pnt_ref x 3), each row: x,y,z
	//	Vec_dist_mea[]: (Num_pnt_ref x 1)
	//	Vec_weight[]  : (Num_pnt_ref x 1)
	//	Num_pnt_ref   : number of reference pnts being measured
	//
	// [Output]
	//	Vec_out[]	  : (3 x 1), meaning x, y, z
	//	return -1	  : indicating error


	if (Num_pnt_ref != 4) { return -1; }


	const int width_mat_nmat0 = 4;	// (x^2+y^2+z^2), x, y, z
	const int width_mat_nmat = 4;  // (x^2+y^2+z^2), x, y, z


	int i, k;
	int ret_a, ret_b, ret_c, ret_d;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// step 0] compute mat_nmat0
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const int totnum_sol_cand = (4 * Num_pnt_ref);	// -> 16

	double* mat_nmat0		= new double [totnum_sol_cand*width_mat_nmat0];

	double* mat_nmat0_a_012 = new double [Num_pnt_ref*width_mat_nmat0];
	double* mat_nmat0_b_013 = new double [Num_pnt_ref*width_mat_nmat0];
	double* mat_nmat0_c_023 = new double [Num_pnt_ref*width_mat_nmat0];
	double* mat_nmat0_d_123 = new double [Num_pnt_ref*width_mat_nmat0];


	//// get mat_nmat0_x_xxx
	ret_a = _rec_tri_npX(Mat_pnt_ref, Vec_dist_mea, Num_pnt_ref, 0, 1, 2, mat_nmat0_a_012);
	ret_b = _rec_tri_npX(Mat_pnt_ref, Vec_dist_mea, Num_pnt_ref, 0, 1, 3, mat_nmat0_b_013);
	ret_c = _rec_tri_npX(Mat_pnt_ref, Vec_dist_mea, Num_pnt_ref, 0, 2, 3, mat_nmat0_c_023);
	ret_d = _rec_tri_npX(Mat_pnt_ref, Vec_dist_mea, Num_pnt_ref, 1, 2, 3, mat_nmat0_d_123);
		// completed to set
		//		mat_nmat0_x_xxx[]: (Num_pnt_ref x width_mat_nmat0)


	//// form mat_nmat0[]
	for (k = 0; k < width_mat_nmat0; k++)	// k: idx for width
	{
		mat_nmat0[0 * width_mat_nmat0 + k] = mat_nmat0_a_012[0 * width_mat_nmat0 + k];
		mat_nmat0[1 * width_mat_nmat0 + k] = mat_nmat0_a_012[1 * width_mat_nmat0 + k];
		mat_nmat0[2 * width_mat_nmat0 + k] = mat_nmat0_a_012[2 * width_mat_nmat0 + k];
		mat_nmat0[3 * width_mat_nmat0 + k] = mat_nmat0_a_012[3 * width_mat_nmat0 + k];

		mat_nmat0[4 * width_mat_nmat0 + k] = mat_nmat0_b_013[0 * width_mat_nmat0 + k];
		mat_nmat0[5 * width_mat_nmat0 + k] = mat_nmat0_b_013[1 * width_mat_nmat0 + k];
		mat_nmat0[6 * width_mat_nmat0 + k] = mat_nmat0_b_013[2 * width_mat_nmat0 + k];
		mat_nmat0[7 * width_mat_nmat0 + k] = mat_nmat0_b_013[3 * width_mat_nmat0 + k];

		mat_nmat0[ 8 * width_mat_nmat0 + k] = mat_nmat0_c_023[0 * width_mat_nmat0 + k];
		mat_nmat0[ 9 * width_mat_nmat0 + k] = mat_nmat0_c_023[1 * width_mat_nmat0 + k];
		mat_nmat0[10 * width_mat_nmat0 + k] = mat_nmat0_c_023[2 * width_mat_nmat0 + k];
		mat_nmat0[11 * width_mat_nmat0 + k] = mat_nmat0_c_023[3 * width_mat_nmat0 + k];

		mat_nmat0[12 * width_mat_nmat0 + k] = mat_nmat0_d_123[0 * width_mat_nmat0 + k];
		mat_nmat0[13 * width_mat_nmat0 + k] = mat_nmat0_d_123[1 * width_mat_nmat0 + k];
		mat_nmat0[14 * width_mat_nmat0 + k] = mat_nmat0_d_123[2 * width_mat_nmat0 + k];
		mat_nmat0[15 * width_mat_nmat0 + k] = mat_nmat0_d_123[3 * width_mat_nmat0 + k];
	}
	// completed to set
	//		mat_nmat0[]: (totnum_sol_cand x width_mat_nmat0)


	if (0)
	{
		printf("==== mat_nmat0 ====\n");

		for (i = 0; i < totnum_sol_cand; i++)
		{
			printf(" -- <%d>th vec --\n", i);
			printf("    [0]: %lf\n", mat_nmat0[i*width_mat_nmat0 + 0]);		// (x^2+y^2+z^2)
			printf("    [1]: %lf\n", mat_nmat0[i*width_mat_nmat0 + 1]);		// x
			printf("    [2]: %lf\n", mat_nmat0[i*width_mat_nmat0 + 2]);		// y
			printf("    [3]: %lf\n", mat_nmat0[i*width_mat_nmat0 + 3]);		// z
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// step 2] obtain mat_nmat
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const int m_mat = totnum_sol_cand;

	double* mat_nmat = new double [m_mat*width_mat_nmat];

	for (i = 0; i < m_mat; i++)
	{
		mat_nmat[i*width_mat_nmat + 0] = mat_nmat0[i*width_mat_nmat0 + 0];	// (x^2+y^2+z^2)
		mat_nmat[i*width_mat_nmat + 1] = mat_nmat0[i*width_mat_nmat0 + 1];	// x
		mat_nmat[i*width_mat_nmat + 2] = mat_nmat0[i*width_mat_nmat0 + 2];	// y
		mat_nmat[i*width_mat_nmat + 3] = mat_nmat0[i*width_mat_nmat0 + 3];	// z

		//// correct z
		if (mat_nmat0[i*width_mat_nmat0 + 3] < 0.0)
		{
			mat_nmat[i*width_mat_nmat + 3] = -1.0*mat_nmat0[i*width_mat_nmat0 + 3];
		}
	}
	// completed to set
	//		mat_nmat[]: m_mat x width_mat_nmat


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// step 3] compute error norm (corresponds to distanzen.m)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double* vec_err_norm = new double[m_mat];

	double	dist_expected2;
	double	dist_expected;
	double  dist_measured;
	double  err_norm2;
	double  err_norm2_w;
	double	sum_err_norm2;
	double  err_norm;
	double	x_nn, y_nn, z_nn;
	double  x_ref, y_ref, z_ref;

	int		i_min;
	double	err_norm_min;

	for (i = 0; i < m_mat; i++)	// i: idx for candidate
	{
		//// get xyz solution candidate
		x_nn = mat_nmat[i*width_mat_nmat + 1];
		y_nn = mat_nmat[i*width_mat_nmat + 2];
		z_nn = mat_nmat[i*width_mat_nmat + 3];


		//// compute expected distance & err_norm (= L2-norm between measured distance and expected distance)
		sum_err_norm2 = 0.0;

		for (k = 0; k < Num_pnt_ref; k++)
		{
			x_ref = Mat_pnt_ref[k * 3 + 0];
			y_ref = Mat_pnt_ref[k * 3 + 1];
			z_ref = Mat_pnt_ref[k * 3 + 2];

			//// expected distance
			dist_expected2 = ((x_nn - x_ref)*(x_nn - x_ref)) + ((y_nn - y_ref)*(y_nn - y_ref)) + ((z_nn - z_ref)*(z_nn - z_ref));
			dist_expected = sqrt(dist_expected2);

			//// measured distance
			dist_measured = Vec_dist_mea[k];

			//// sum_err_norm2
			err_norm2 = (dist_measured - dist_expected)*(dist_measured - dist_expected);
			err_norm2_w = (Vec_weight[k] * err_norm2);
			sum_err_norm2 += err_norm2_w;
		}
		// completed to set
		//		sum_err_norm2


		err_norm = sqrt(sum_err_norm2);
		vec_err_norm[i] = err_norm;
		// completed to set
		//		err_norm
		//		vec_err_norm[]


		//// check if it is min
		if (i == 0)
		{
			i_min = i;
			err_norm_min = err_norm;
		}
		else
		{
			if (err_norm < err_norm_min)
			{
				i_min = i;
				err_norm_min = err_norm;
			}
		}
	}
	// completed to set
	//		i_min
	//		err_norm_min
	//		vec_err_norm[]: (m_mat x 1)

	if (0)
	{
		printf("==== vec_err_norm ====\n");

		for (i = 0; i < m_mat; i++)
		{
			printf("    err_norm[%d]: %lf\n", i, vec_err_norm[i]);
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// step 4] choose xyz solution (with min err_norm)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Vec_out[0] = mat_nmat[i_min*width_mat_nmat + 1];	// x
	Vec_out[1] = mat_nmat[i_min*width_mat_nmat + 2];	// y
	Vec_out[2] = mat_nmat[i_min*width_mat_nmat + 3];	// z

	if (0)
	{
		printf("==== solution ====\n");
		printf("  solution(x): %lf\n", Vec_out[0]);
		printf("  solution(y): %lf\n", Vec_out[1]);
		printf("  solution(z): %lf\n", Vec_out[2]);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// release
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	delete[] mat_nmat0;
	delete[] mat_nmat0_a_012;
	delete[] mat_nmat0_b_013;
	delete[] mat_nmat0_c_023;
	delete[] mat_nmat0_d_123;
	delete[] mat_nmat;
	delete[] vec_err_norm;


	return 1;

}


int	CLibTrilateration::_rec_tri_np3(const double* Mat_pnt_ref, const double* Vec_dist_mea, const int Num_pnt_ref, double* Vec_out1, double* Vec_out2)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// do recursive trilateration (np == 3) (corresponding to RecTrilateration.m)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// [Input]
	//	Mat_pnt_ref []: (Num_pnt_ref x 3), each row: x,y,z
	//	Vec_dist_mea[]: (Num_pnt_ref x 1)
	//	Num_pnt_ref   : number of reference pnts being measured
	//
	// [Output]
	//	Vec_out1[]	  : (4 x 1), meaning (x^2+y^2+x^2), x, y, z
	//	Vec_out2[]	  : (4 x 1), meaning (x^2+y^2+x^2), x, y, z

	//	return -1	  : indicating error

	// Num_pnt_ref = np (in RecTrilateration.m)


	if (Num_pnt_ref != 3) { return -1; }


	int		i;
	int		idx_pnt;
	double	x_pnt, y_pnt, z_pnt;
	double  dist_mea;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// make mat_a & mat_b
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat mat_a(Num_pnt_ref, 4, CV_64FC1);
	Mat mat_b(Num_pnt_ref, 1, CV_64FC1);

	for (idx_pnt = 0; idx_pnt < Num_pnt_ref; idx_pnt++)
	{
		//// get
		x_pnt	 = Mat_pnt_ref [idx_pnt * 3 + 0];
		y_pnt	 = Mat_pnt_ref [idx_pnt * 3 + 1];
		z_pnt	 = Mat_pnt_ref [idx_pnt * 3 + 2];
		dist_mea = Vec_dist_mea[idx_pnt];

		//// set
		mat_a.at<double>(idx_pnt, 0) = 1.0;
		mat_a.at<double>(idx_pnt, 1) = -2.0*x_pnt;
		mat_a.at<double>(idx_pnt, 2) = -2.0*y_pnt;
		mat_a.at<double>(idx_pnt, 3) = -2.0*z_pnt;

		mat_b.at<double>(idx_pnt, 0) = (dist_mea*dist_mea) - (x_pnt*x_pnt) - (y_pnt*y_pnt) - (z_pnt*z_pnt);
	}
	// completed to set
	//		mat_a: (Num_pnt_ref x 4)
	//		mat_b: (Num_pnt_ref x 1)


	// debug - checking mat_a & mat_b
	if (0)
	{
		//// mat_a
		printf("== mat_a ==\n");

		for (idx_pnt = 0; idx_pnt < Num_pnt_ref; idx_pnt++)
		{
			printf("row[%d]: %lf, %lf, %lf, %lf\n", idx_pnt, mat_a.at<double>(idx_pnt, 0), mat_a.at<double>(idx_pnt, 1), mat_a.at<double>(idx_pnt, 2), mat_a.at<double>(idx_pnt, 3));
		}

		//// mat_b
		printf("== mat_b ==\n");

		for (idx_pnt = 0; idx_pnt < Num_pnt_ref; idx_pnt++)
		{
			printf("row[%d]: %lf\n", idx_pnt, mat_b.at<double>(idx_pnt, 0));
		}
	}


	//// compute mat_xp = mat_a(-1)*mat_b    (-> mat_xp = Xp in RecTrilateration.m)
	Mat mat_a_pinv;
	invert(mat_a, mat_a_pinv, DECOMP_SVD);

	Mat mat_xp;
	mat_xp = mat_a_pinv*mat_b;
		// completed to set 
		//		mat_xp: (4 x 1)


	// debug - checking mat_xp (= mat_a(-1)*mat_b)
	if (0)
	{
		printf("== mat_xp ==\n");

		printf("row[0]: %lf\n", mat_xp.at<double>(0, 0));
		printf("row[1]: %lf\n", mat_xp.at<double>(1, 0));
		printf("row[2]: %lf\n", mat_xp.at<double>(2, 0));
		printf("row[3]: %lf\n", mat_xp.at<double>(3, 0));
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// run
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//// set xp
	double xp[4];

	xp[0] = mat_xp.at<double>(0, 0);
	xp[1] = mat_xp.at<double>(1, 0);
	xp[2] = mat_xp.at<double>(2, 0);
	xp[3] = mat_xp.at<double>(3, 0);
		// completed to set
		//		xp[]

	// debug
	if (0) { printf("xp[0]:(%lf), xp[1]:(%lf), xp[2]:(%lf), xp[3]:(%lf)\n", xp[0], xp[1], xp[2], xp[3]); }


	//// decompose mat_a
	Mat _mat_ua, _mat_sa, _mat_va;

	SVD::compute(mat_a, _mat_sa, _mat_ua, _mat_va, SVD::FULL_UV);
	// completed to set
	//		_mat_sa, _mat_ua, _mat_va

	// debug
	if (0)
	{
		cout << _mat_sa << endl;
		cout << _mat_ua << endl;
		cout << _mat_va << endl;
	}


	//// set z_big & z_small
	double z_big[4];

	z_big[0] = _mat_va.at<double>(3, 0);
	z_big[1] = _mat_va.at<double>(3, 1);
	z_big[2] = _mat_va.at<double>(3, 2);
	z_big[3] = _mat_va.at<double>(3, 3);

	z_big[0] = z_big[0] / z_big[3];
	z_big[1] = z_big[1] / z_big[3];
	z_big[2] = z_big[2] / z_big[3];
	z_big[3] = z_big[3] / z_big[3];
	// completed to set
	//		z_big[]

	// debug
	if (0) { printf("z_big[0]:(%lf), z_big[1]:(%lf), z_big[2]:(%lf), z_big[3]:(%lf)\n", z_big[0], z_big[1], z_big[2], z_big[3]); }


	double z_small[4];		// z_small[0]: not used

	z_small[1] = z_big[1];
	z_small[2] = z_big[2];
	z_small[3] = z_big[3];
		// completed to set
		//		z_small[]


	//// compute rank(mat_a)
	double	val_s;
	double	thres_s = 0.001;
	int		rank_mat_a = 0;

	for (i = 0; i < 3; i++)
	{
		val_s = _mat_sa.at<double>(i, 0);

		if (val_s > thres_s) { rank_mat_a++; }
	}
	// completed to set
	//		rank_mat_a

	// debug
	if (0) { printf("rank_mat_a:[%d]\n", rank_mat_a); }


	if (rank_mat_a == 3)
	{
		double ca, cb, cc;

		ca = (z_small[1] * z_small[1]) + (z_small[2] * z_small[2]) + (z_small[3] * z_small[3]);
		cb = 2.0*((z_small[1] * xp[1]) + (z_small[2] * xp[2]) + (z_small[3] * xp[3])) - z_big[0];
		cc = (xp[1] * xp[1]) + (xp[2] * xp[2]) + (xp[3] * xp[3]) - xp[0];

		// debug
		if (0) { printf("ca:(%lf), cb:(%lf), cc:(%lf)\n", ca, cb, cc); }


		double val_t1, val_t2;
		double val_temp;

		val_temp = (cb*cb - 4.0*ca*cc);

		if (val_temp < 0) // trick for not having complex number
		{
			val_t1 = -1.0*cb;
			val_t2 = -1.0*cb;
		}
		else // normal case
		{
			val_t1 = -1.0*cb + sqrt(cb*cb - 4.0*ca*cc);
			val_t2 = -1.0*cb - sqrt(cb*cb - 4.0*ca*cc);
		}

		val_t1 = val_t1 / (2.0*ca);
		val_t2 = val_t2 / (2.0*ca);

		// debug
		if (0) { printf("val_t1:(%lf), val_t2:(%lf)\n", val_t1, val_t2); }


		//// set output (Vec_out1 & Vec_out2)
		Vec_out1[0] = xp[0] + val_t1*z_big[0];
		Vec_out1[1] = xp[1] + val_t1*z_big[1];
		Vec_out1[2] = xp[2] + val_t1*z_big[2];
		Vec_out1[3] = xp[3] + val_t1*z_big[3];
			// completed to set 
			//		Vec_out1[]

		Vec_out2[0] = xp[0] + val_t2*z_big[0];
		Vec_out2[1] = xp[1] + val_t2*z_big[1];
		Vec_out2[2] = xp[2] + val_t2*z_big[2];
		Vec_out2[3] = xp[3] + val_t2*z_big[3];
			// completed to set 
			//		Vec_out2[]
	}
	else
	{
		return -1;
	}


	// debug
	if (0)
	{
		printf("out1 - x:(%lf), y:(%lf), z:(%lf)\n", Vec_out1[0], Vec_out1[1], Vec_out1[2]);
		printf("out2 - x:(%lf), y:(%lf), z:(%lf)\n", Vec_out2[0], Vec_out2[1], Vec_out2[2]);
	}


	return 1;

}

int	CLibTrilateration::_rec_tri_npX(const double* Mat_pnt_ref, const double* Vec_dist_mea, const int Num_pnt_ref, const int IDX_row_a, const int IDX_row_b, const int IDX_row_c, double* Mat_out)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// do recursive trilateration (np > 3) (corresponding to RecTrilateration.m)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// [Input]
	//	Mat_pnt_ref []: (Num_pnt_ref x 3), each row: x,y,z
	//	Vec_dist_mea[]: (Num_pnt_ref x 1)
	//	Num_pnt_ref   : number of reference pnts being measured (-> Here, this should be 4.)
	//  IDX_row_a, IDX_row_b, IDX_row_c: selected rows for _rec_tri_np3()
	//
	// [Output]
	//	Mat_out[]	  : (Num_pnt_ref x 4), each row: (x^2+y^2+z^2), x, y, z
	//	return -1	  : indicating error

	// Num_pnt_ref = np (in RecTrilateration.m)


	if (Num_pnt_ref != 4) { return -1; }


	int		i, k;
	int		idx_pnt;
	double	x_pnt, y_pnt, z_pnt;
	double  dist_mea;

	const int width_mat_out = 4;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// make mat_a, mat_b & mat_a0
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//// mat_a, mat_b
	Mat mat_a(Num_pnt_ref, 4, CV_64FC1);	// (np x 4)
	Mat mat_b(Num_pnt_ref, 1, CV_64FC1);	// (np x 1)

	for (idx_pnt = 0; idx_pnt < Num_pnt_ref; idx_pnt++)
	{
		//// get
		x_pnt = Mat_pnt_ref[idx_pnt * 3 + 0];
		y_pnt = Mat_pnt_ref[idx_pnt * 3 + 1];
		z_pnt = Mat_pnt_ref[idx_pnt * 3 + 2];
		dist_mea = Vec_dist_mea[idx_pnt];

		//// set
		mat_a.at<double>(idx_pnt, 0) = 1.0;
		mat_a.at<double>(idx_pnt, 1) = -2.0*x_pnt;
		mat_a.at<double>(idx_pnt, 2) = -2.0*y_pnt;
		mat_a.at<double>(idx_pnt, 3) = -2.0*z_pnt;

		mat_b.at<double>(idx_pnt, 0) = (dist_mea*dist_mea) - (x_pnt*x_pnt) - (y_pnt*y_pnt) - (z_pnt*z_pnt);
	}
	// completed to set
	//		mat_a: (Num_pnt_ref x 4)
	//		mat_b: (Num_pnt_ref x 1)


	//// mat_a0
	Mat mat_a0(3, 4, CV_64FC1);		// 3 x 4

	for (idx_pnt = 0; idx_pnt < 3; idx_pnt++)
	{
		mat_a0.at<double>(idx_pnt, 0) = mat_a.at<double>(idx_pnt, 0);
		mat_a0.at<double>(idx_pnt, 1) = mat_a.at<double>(idx_pnt, 1);
		mat_a0.at<double>(idx_pnt, 2) = mat_a.at<double>(idx_pnt, 2);
		mat_a0.at<double>(idx_pnt, 3) = mat_a.at<double>(idx_pnt, 3);
	}
	//	completed to set
	//		mat_a0: (3 x 4)


	// debug - checking mat_a & mat_b
	if (0)
	{
		//// mat_a
		printf("== mat_a ==\n");

		for (idx_pnt = 0; idx_pnt < Num_pnt_ref; idx_pnt++)
		{
			printf("row[%d]: %lf, %lf, %lf, %lf\n", idx_pnt, mat_a.at<double>(idx_pnt, 0), mat_a.at<double>(idx_pnt, 1), mat_a.at<double>(idx_pnt, 2), mat_a.at<double>(idx_pnt, 3));
		}

		//// mat_b
		printf("== mat_b ==\n");

		for (idx_pnt = 0; idx_pnt < Num_pnt_ref; idx_pnt++)
		{
			printf("row[%d]: %lf\n", idx_pnt, mat_b.at<double>(idx_pnt, 0));
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// make mat_p10, vec_s10
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//// mat_p10
	double mat_p10[3*3];	// 3(left): number of pnts, 3(right): x,y,z

	mat_p10[0 * 3 + 0] = Mat_pnt_ref[IDX_row_a * 3 + 0];
	mat_p10[0 * 3 + 1] = Mat_pnt_ref[IDX_row_a * 3 + 1];
	mat_p10[0 * 3 + 2] = Mat_pnt_ref[IDX_row_a * 3 + 2];

	mat_p10[1 * 3 + 0] = Mat_pnt_ref[IDX_row_b * 3 + 0];
	mat_p10[1 * 3 + 1] = Mat_pnt_ref[IDX_row_b * 3 + 1];
	mat_p10[1 * 3 + 2] = Mat_pnt_ref[IDX_row_b * 3 + 2];

	mat_p10[2 * 3 + 0] = Mat_pnt_ref[IDX_row_c * 3 + 0];
	mat_p10[2 * 3 + 1] = Mat_pnt_ref[IDX_row_c * 3 + 1];
	mat_p10[2 * 3 + 2] = Mat_pnt_ref[IDX_row_c * 3 + 2];
		// completed to set
		//		mat_p10: (3x3)


	//// vec_s10
	double vec_s10[3];

	vec_s10[0] = Vec_dist_mea[IDX_row_a];
	vec_s10[1] = Vec_dist_mea[IDX_row_b];
	vec_s10[2] = Vec_dist_mea[IDX_row_c];
		// completed to set
		//		vec_s10: (1 x 3)


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// make mat_p10, vec_s10
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double vec_n01[4];
	double vec_n02[4];

	_rec_tri_np3(mat_p10, vec_s10, 3, vec_n01, vec_n02);
		// completed to set
		//		vec_n01[]: (4x1), (x^2+y^2+z^2), x, y, z
		//		vec_n02[]: (4x1), (x^2+y^2+z^2), x, y, z


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// select vec_n0[]
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Mat mat_a_t;
	transpose(mat_a, mat_a_t);
		// completed to set
		//		mat_a_t: (4 x Num_pnt_ref)

	Mat mat_a_t_a = mat_a_t*mat_a;
		// completed to set
		//		mat_a_t_a: (4 x 4)

	Mat inv_mat_a_t_a;
	invert(mat_a_t_a, inv_mat_a_t_a);
		// completed to set
		//		inv_mat_a_t_a: (4 x 4)

	Mat vec_xpdw;
	vec_xpdw = inv_mat_a_t_a*mat_a_t*mat_b;
		// completed to set
		//		vec_xpdw: (4x1)


	double xpdw[4];

	xpdw[0] = vec_xpdw.at<double>(0, 0);
	xpdw[1] = vec_xpdw.at<double>(1, 0);
	xpdw[2] = vec_xpdw.at<double>(2, 0);
	xpdw[3] = vec_xpdw.at<double>(3, 0);


	double norm_xpdw_n01 = ((xpdw[1] - vec_n01[1])*(xpdw[1] - vec_n01[1])) + ((xpdw[2] - vec_n01[2])*(xpdw[2] - vec_n01[2])) + ((xpdw[3] - vec_n01[3])*(xpdw[3] - vec_n01[3]));
	double norm_xpdw_n02 = ((xpdw[1] - vec_n02[1])*(xpdw[1] - vec_n02[1])) + ((xpdw[2] - vec_n02[2])*(xpdw[2] - vec_n02[2])) + ((xpdw[3] - vec_n02[3])*(xpdw[3] - vec_n02[3]));
		// completed to set
		//		norm_xpdw_n01, norm_xpdw_n02


	double vec_n0[4];

	if (norm_xpdw_n01 < norm_xpdw_n02)
	{
		vec_n0[0] = vec_n01[0];
		vec_n0[1] = vec_n01[1];
		vec_n0[2] = vec_n01[2];
		vec_n0[3] = vec_n01[3];
	}
	else
	{
		vec_n0[0] = vec_n02[0];
		vec_n0[1] = vec_n02[1];
		vec_n0[2] = vec_n02[2];
		vec_n0[3] = vec_n02[3];
	}
	// completed to set
	//		vec_n0[]: (4x1)


	//// set Mat_out[] (row 0)
	Mat_out[0 * width_mat_out + 0] = vec_n01[0];
	Mat_out[0 * width_mat_out + 1] = vec_n01[1];
	Mat_out[0 * width_mat_out + 2] = vec_n01[2];
	Mat_out[0 * width_mat_out + 3] = vec_n01[3];

	//// set Mat_out[] (row 1)
	Mat_out[1 * width_mat_out + 0] = vec_n02[0];
	Mat_out[1 * width_mat_out + 1] = vec_n02[1];
	Mat_out[1 * width_mat_out + 2] = vec_n02[2];
	Mat_out[1 * width_mat_out + 3] = vec_n02[3];


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double vec_x[4];
	double mat_p[4*4];

	//// set vec_x, mat_p (initial)
	vec_x[0] = vec_n0[0];
	vec_x[1] = vec_n0[1];
	vec_x[2] = vec_n0[2];
	vec_x[3] = vec_n0[3];

	mat_p[0 * 4 + 0] = 1.0;		mat_p[0 * 4 + 1] = 0.0;		mat_p[0 * 4 + 2] = 0.0;		mat_p[0 * 4 + 3] = 0.0;
	mat_p[1 * 4 + 0] = 0.0;		mat_p[1 * 4 + 1] = 1.0;		mat_p[1 * 4 + 2] = 0.0;		mat_p[1 * 4 + 3] = 0.0;
	mat_p[2 * 4 + 0] = 0.0;		mat_p[2 * 4 + 1] = 0.0;		mat_p[2 * 4 + 2] = 1.0;		mat_p[2 * 4 + 3] = 0.0;
	mat_p[3 * 4 + 0] = 0.0;		mat_p[3 * 4 + 1] = 0.0;		mat_p[3 * 4 + 2] = 0.0;		mat_p[3 * 4 + 3] = 1.0;


	double vec_an[4];
	double val_yn;
	double vec_xn[4];
	double mat_pn[4 * 4];


	for (i = 0; i < (Num_pnt_ref - 3); i++)
	{
		vec_an[0] = mat_a.at<double>((i + 3), 0);
		vec_an[1] = mat_a.at<double>((i + 3), 1);
		vec_an[2] = mat_a.at<double>((i + 3), 2);
		vec_an[3] = mat_a.at<double>((i + 3), 3);

		val_yn    = mat_b.at<double>((i + 3), 0);


		//// run lsrec
		_lsrec(val_yn, vec_an, vec_x, mat_p, vec_xn, mat_pn);
			// completed to set
			//		vec_xn: (4x1)
			//		mat_pn: (4x4)


		//// shift
		for (k = 0; k < 4; k++)
		{
			vec_x[k] = vec_xn[k];
		}

		for (k = 0; k < 16; k++)
		{
			mat_p[k] = mat_pn[k];
		}


		//// set Mat_out[] (row i+2)
		Mat_out[(i + 2) * width_mat_out + 0] = vec_xn[0];
		Mat_out[(i + 2) * width_mat_out + 1] = vec_xn[1];
		Mat_out[(i + 2) * width_mat_out + 2] = vec_xn[2];
		Mat_out[(i + 2) * width_mat_out + 3] = vec_xn[3];
	}


	//// set Mat_out[] (last row)
	int idx = (Num_pnt_ref - 1);

	Mat_out[idx * width_mat_out + 0] = xpdw[0];
	Mat_out[idx * width_mat_out + 1] = xpdw[1];
	Mat_out[idx * width_mat_out + 2] = xpdw[2];
	Mat_out[idx * width_mat_out + 3] = xpdw[3];


	return 1;


}

void CLibTrilateration::_lsrec(const double Val_yn, const double* Vec_an, const double* Vec_x, const double* Mat_p, double* Vec_xn_out, double* Mat_pn_out)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// do recursive trilateration (corresponding to RecTrilateration.m)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// [INPUT]
	//	Val_yn -> yn: (1x1)
	//	Vec_an -> An: (1x4)
	//	Vec_x -> x: (4x1)
	//	Mat_p -> P: (4x4)
	//
	// [Output]
	//	Vec_xn_out: (4x1)
	//  Mat_pn_out: (4x4)


	int i, k;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// copy data
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat val_yn(1, 1, CV_64FC1);
	Mat vec_an(1, 4, CV_64FC1);
	Mat vec_an_t(4, 1, CV_64FC1);
	Mat vec_x(4, 1, CV_64FC1);
	Mat mat_p(4, 4, CV_64FC1);
	
	//// val_yn
	val_yn.at<double>(0, 0) = Val_yn;

	//// vec_an
	vec_an.at<double>(0, 0) = Vec_an[0];
	vec_an.at<double>(0, 1) = Vec_an[1];
	vec_an.at<double>(0, 2) = Vec_an[2];
	vec_an.at<double>(0, 3) = Vec_an[3];

	//// vec_an_t
	vec_an_t.at<double>(0, 0) = Vec_an[0];
	vec_an_t.at<double>(1, 0) = Vec_an[1];
	vec_an_t.at<double>(2, 0) = Vec_an[2];
	vec_an_t.at<double>(3, 0) = Vec_an[3];

	//// vec_x
	vec_x.at<double>(0, 0) = Vec_x[0];
	vec_x.at<double>(1, 0) = Vec_x[1];
	vec_x.at<double>(2, 0) = Vec_x[2];
	vec_x.at<double>(3, 0) = Vec_x[3];

	//// mat_p
	for (i = 0; i < 4; i++)
	{
		for (k = 0; k < 4; k++)
		{
			mat_p.at<double>(i, k) = Mat_p[i*4 + k];
		}
	}	
	// completed to set
	//		val_yn: 1x1
	//		vec_an: 1x4
	//		vec_an_t: 4x1
	//		vec_x: 4x1
	//		mat_p: 4x4



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// compute mat_k
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat mat_k(4, 1, CV_64FC1);		// 4x1
	Mat mat_k_nom;
	Mat val_k_den_;
	double val_k_den;

	mat_k_nom  = mat_p*vec_an_t;						// mat_k_nom : 4x1
	val_k_den_ = vec_an*mat_p*vec_an_t;					// val_k_den_: 1x1
	val_k_den  = val_k_den_.at<double>(0, 0) + 1.0;

	mat_k.at<double>(0, 0) = mat_k_nom.at<double>(0, 0) / val_k_den;
	mat_k.at<double>(1, 0) = mat_k_nom.at<double>(1, 0) / val_k_den;
	mat_k.at<double>(2, 0) = mat_k_nom.at<double>(2, 0) / val_k_den;
	mat_k.at<double>(3, 0) = mat_k_nom.at<double>(3, 0) / val_k_den;
		// completed to set
		//		mat_k: 4x1

		if (0)
		{
			printf("==== mat_k ====\n");
			printf("  mat_k[0]: %lf\n", mat_k.at<double>(0, 0));
			printf("  mat_k[1]: %lf\n", mat_k.at<double>(1, 0));
			printf("  mat_k[2]: %lf\n", mat_k.at<double>(2, 0));
			printf("  mat_k[3]: %lf\n", mat_k.at<double>(3, 0));
		}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// compute vec_xn
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat vec_xn;		// 4x1
	Mat mat_pn;		// 4x4

	vec_xn = vec_x + mat_k*(val_yn - vec_an*vec_x);
	mat_pn = mat_p - mat_k*vec_an*mat_p;
		// completed to set
		//		vec_xn: 4x1
		//		mat_pn: 4x4

		if (0)
		{
			printf("==== vec_xn ====\n");
			printf("  vec_xn[0]: %lf\n", vec_xn.at<double>(0, 0));
			printf("  vec_xn[1]: %lf\n", vec_xn.at<double>(1, 0));
			printf("  vec_xn[2]: %lf\n", vec_xn.at<double>(2, 0));
			printf("  vec_xn[3]: %lf\n", vec_xn.at<double>(3, 0));


			printf("==== mat_pn ====\n");

			for (i = 0; i < 4; i++)
			{
				printf("  ----\n");

				for (k = 0; k < 4; k++)
				{
					printf("  mat_pn[%d][%d]:%lf\n", i, k, mat_pn.at<double>(i, k));
				}
			}
		}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// set output
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Vec_xn_out[]
	Vec_xn_out[0] = vec_xn.at<double>(0, 0);
	Vec_xn_out[1] = vec_xn.at<double>(1, 0);
	Vec_xn_out[2] = vec_xn.at<double>(2, 0);
	Vec_xn_out[3] = vec_xn.at<double>(3, 0);

	// Mat_pn_out[]
	for (i = 0; i < 4; i++)
	{
		for (k = 0; k < 4; k++)
		{
			Mat_pn_out[i * 4 + k] = mat_pn.at<double>(i, k);
		}
	}



}
