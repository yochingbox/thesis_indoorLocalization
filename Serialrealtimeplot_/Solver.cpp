#include "Solver.h"

int counter = 0;
int counter1 = 0;	
int counter2 = 0;

// Variable for math
float pi = 4*atan(1.0);
float g = 9.81;
float deg2pi = pi/180;
float pi2deg = 180/pi;
float dt = 0.0028; //0.02;// 6.0 / 333.0;
//float dec_const = (1+21/60)*deg2pi;
//float inc_const = -(63+50/60)*deg2pi;
// Variable for Kalman filter
float x_ini[15][1]={0,
	                0,
			        0,
				    0,
				    0,
                    0,
	                0,
			        0,
				    0,
				    0,
					0,
	                0,
			        0,
				    0,
				    0};
float xx[15][1];
float x_new[15][1];

float zeros3x12[3][12];
float zeros3x9[3][9];
float zeros3x6[3][6];

float eye3_3[3][3]={0.001, 0, 0,
	                0, 0.001, 0,
				    0, 0, 0.001};
float eye3_2[3][3]={0.01, 0, 0,
	                0, 0.01, 0,
				    0, 0, 0.01};
float eye3_4[3][3]={0.0001, 0, 0,
	                0, 0.0001, 0,
				    0, 0, 0.0001};
float eye3_1[3][3]={0.1, 0, 0,
	                0, 0.1, 0,
				    0, 0, 0.1};
float eye3_p2[3][3]={2, 0, 0,
	                  0, 2, 0,
				      0, 0, 2};
float eye3[3][3]={1, 0, 0,
	               0, 1, 0,
				   0, 0, 1};


float P_ini[15][15];
float P[15][15];
float P_new[15][15];
float Q[15][15];

//////compass 3D/////////
float R[9][9];
float H[9][15];
float m[9][1];
/////////////////////////////

//Calculation of initial conditions
float acc_ini[n_INI][3];
float mag_ini[n_INI][3];
float gyr_ini[n_INI][3];
float X_ini[9][n_INI];
float Y_ini[9]; 
float d_ini[9][1];
float d_med[9][med_L];
float d_cal[9][1];
int start[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int start_med[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
int start_C = 0;
int start_CT = 0;
int start_T = 0;
int ena_ini = 0;

float EUL[3];
float EUL_ini[n_INI][3];
float EUL_ini_TP[3][n_INI];
float Orien[3][1];
float Gyro_ini[3];
float Gyro_ini_tp[3][n_INI];
float Orienini[3][1];
float C_b2n[3][3];
float Magf_ini[n_INI];
float Mth_ini[n_INI];
float Magfini;
float Hthini;
float Mthini;

//Memeory allocation for Sensor data
float acc_raw[3];
float gyr_raw[3];
float mag_b[3][1];
float mag_b_TP[3][1];
float accf;
float gyrf;
float magf;
int C1 = 0;
int C3 = 0;
int C_total[2];
int C_total_m[med_L];
int C_total_n[(med_L+1)/2];
int C_median_I[med_L];
int C_median_O[med_L];
int ena_med = 0;
float acc_b[3][1];
float acc_n[3][1];
float gyr[3];
float S_ang[3][3];
float S_angdt[3][3];
float eye3mSang[3][3];
float eye3pSang[3][3];
float inveye3mSang[3][3];
float C_b2n_change[3][3];
float C_b2n_m[3][3];
float C_b2n_m_TP[3][3];
float mag_n[3][1];
float ang_mag;
float Orien_m[3][1];
float Orien_mag[3];

/*
float B[3][1] = {0.4409,
	             0.0104,
				 -0.8975};
*/


float B[3][1] = {1,
	             0,
				 0};

float mag_b_r[3][1];
float mag_b_r_TP[3];
float Orien_mag_r[3];
float Orien_comp[3];
float Mth;
float Hth;
float delta_orien1[3][1];
float SN[3];
int N1 = 0;
int N2 = 0;
int N3 = 0;
int ena_ori = 0;
int ena_ori1 = 0;
int ena_C = 0;
float delta_orien2 = 0;
int cont1;
int cont2;
float acc_n_ng[3][1];
float v[3] = {0,0,0};
float p[3] = {0,0,0};
//float orien_res[3] = { 0, 0, 0 };
float v_m[3] = {0,0,0};
float p_m[3] = {0,0,0};

float G[3][1] = {0,
	              0,
				  g};
float acc_n_ngdt[3];
float v_mdt[3];

float posi[3][1];
float velo[3][1];
float S_orien[3][3];
float eye3mSori[3][3];
float eye3pSori[3][3];
float inveye3mSori[3][3];
float C_b2n_change_new[3][3];
//float d;
//float A[1968][9];
//int row = 0;
//int col = 0;

float Orien_temp[NN];
int ena_ori_temp = 0;
int counter_temp = 0;
int cont1_temp = 0;
int cont2_temp = 0;

float gyr_bias[3][1];
float gyr_bias1[3][1];
float accf_ini;
int counter_ini=0;
float gyrsum[3][n_INI];
float gyrx[n_INI];
float gyrx2[n_INI];
float gyrxy[3][n_INI];
float gyrxm=0;
float gyrym[3]={0,0,0};
float gyrx2m=0;
float gyrxym[3]={0,0,0};
float gyrxmm=0;
float gyrymm[3]={0,0,0};

int counter1_ini=0;
float gyrsum1[3][n_INI1];
float gyrx1[n_INI1];
float gyrx21[n_INI1];
float gyrxy1[3][n_INI1];
float gyrxm1=0;
float gyrym1[3]={0,0,0};
float gyrx2m1=0;
float gyrxym1[3]={0,0,0};
float gyrxmm1=0;
float gyrymm1[3]={0,0,0};

float Mthm_ini=0;
float EULms_ini[3]={0,0,0};
float EULmc_ini[3]={0,0,0};
int id1 = 0; 
int id2 = 0; 
int id3 = 0; 
int cont_c = 0;

void Solverini()
{
	//----------Calculation Initialization---------------------
	for (int j_x = 0; j_x<15; j_x++){
		xx[j_x][0] = x_ini[j_x][0];
	}

	//set initial value of matrices
	zeros(3, 12, (float*)zeros3x12);
	zeros(3, 9, (float*)zeros3x9);
	zeros(3, 6, (float*)zeros3x6);
	zeros(7, 1, (float*)m);

	zero(15, (float*)P_ini);
	zero(15, (float*)P);

	//////compass 3D/////////
	zero(9, (float*)R);
	zeros(9, 15, (float*)H);
	for (int ii = 0; ii<3; ii++){
		for (int jj = 0; jj<3; jj++){
            P_ini[ii][jj] = eye3_2[ii][jj];
            P[ii][jj] = eye3_2[ii][jj];
            Q[ii][jj] = eye3_3[ii][jj];

			//////compass 3D/////////
            R[ii][jj] = eye3_2[ii][jj];
			H[ii][jj] = eye3[ii][jj];
			//////////////////////////
			P_ini[ii + 3][jj + 3] = eye3_2[ii][jj];
			P[ii + 3][jj + 3] = eye3_2[ii][jj];

			//////compass 3D/////////
			R[ii + 3][jj + 3] = eye3_1[ii][jj];
			R[ii + 6][jj + 6] = eye3_3[ii][jj];
			H[ii + 3][jj + 3] = eye3[ii][jj];
			H[ii + 6][jj + 9] = eye3[ii][jj];
			//////////////////////////

			P_ini[ii + 6][jj + 6] = eye3_3[ii][jj];
			P[ii + 6][jj + 6] = eye3_3[ii][jj];
			P_ini[ii + 9][jj + 9] = eye3_3[ii][jj];
			P[ii + 9][jj + 9] = eye3_3[ii][jj];
            Q[ii + 9][jj + 9] = eye3_4[ii][jj];
			P_ini[ii + 12][jj + 12] = eye3_2[ii][jj];
			P[ii + 12][jj + 12] = eye3_2[ii][jj];
		}
	}
    R[0][0] = 1;
    R[1][1] = 1;
    R[2][2] = 100;
    Q[2][2] = 0.0001;
	//---------------------------------------------------
}


void ComputeSolution(float* sensordata, int meas_num, float v_res[3], float p_res[3], float orien_res[3], float acc_res[3])
{
	int i = meas_num;
	//dt = 5_DataRate * dt_default;
	if (i <= n_INI - 1 && ena_ini == 0){
		for (int lp = 0; lp<9; lp++){
			//X_ini[lp][i] = (*_MeasurementVector)[i]->Data[lp];
			//X_ini[lp][i] = A[i][lp];
			X_ini[lp][i] = sensordata[lp];
			d_ini[lp][0] = X_ini[lp][i];
		}
		accf_ini = sqrt(pow(d_ini[0][0], 2) + pow(d_ini[1][0], 2) + pow(d_ini[2][0], 2));
		if (accf_ini<g*1.03 && accf_ini>g*0.97){

			acc_ini[counter_ini][0] = d_ini[0][0];
			acc_ini[counter_ini][1] = d_ini[1][0];
			acc_ini[counter_ini][2] = d_ini[2][0];
			gyr_ini[counter_ini][0] = d_ini[3][0];
			gyr_ini[counter_ini][1] = d_ini[4][0];
			gyr_ini[counter_ini][2] = d_ini[5][0];
			mag_ini[counter_ini][0] = d_ini[6][0];
			mag_ini[counter_ini][1] = d_ini[7][0];
			mag_ini[counter_ini][2] = d_ini[8][0];
			if (counter_ini == 0){
				gyrsum[0][counter_ini] = gyr_ini[counter_ini][0];
				gyrsum[1][counter_ini] = gyr_ini[counter_ini][1];
				gyrsum[2][counter_ini] = gyr_ini[counter_ini][2];
			}
			else{
				gyrsum[0][counter_ini] = gyrsum[0][counter_ini - 1] + gyr_ini[counter_ini][0];
				gyrsum[1][counter_ini] = gyrsum[1][counter_ini - 1] + gyr_ini[counter_ini][1];
				gyrsum[2][counter_ini] = gyrsum[2][counter_ini - 1] + gyr_ini[counter_ini][2];
			}
			gyrx[counter_ini] = counter_ini + 1;
			gyrx2[counter_ini] = (counter_ini + 1)*(counter_ini + 1);

			gyrxy[0][counter_ini] = gyrx[counter_ini] * gyrsum[0][counter_ini];
			gyrxy[1][counter_ini] = gyrx[counter_ini] * gyrsum[1][counter_ini];
			gyrxy[2][counter_ini] = gyrx[counter_ini] * gyrsum[2][counter_ini];

			//calculate the euler angles for initialization
			orien_mag_std((float*)acc_ini[counter_ini], (float*)mag_ini[counter_ini], EUL);
			EUL_ini[counter_ini][0] = EUL[0];
			EUL_ini[counter_ini][1] = EUL[1];
			EUL_ini[counter_ini][2] = EUL[2];

			Mth_ini[counter_ini] = acc_ini[counter_ini][0] * mag_ini[counter_ini][0] + acc_ini[counter_ini][1] * mag_ini[counter_ini][1] + acc_ini[counter_ini][2] * mag_ini[counter_ini][2];
			gyrym[0] = gyrym[0] + gyrsum[0][counter_ini];
			gyrym[1] = gyrym[1] + gyrsum[1][counter_ini];
			gyrym[2] = gyrym[2] + gyrsum[2][counter_ini];

			Mthm_ini = Mthm_ini + Mth_ini[counter_ini];
			EULms_ini[0] = EULms_ini[0] + sin(EUL[0]);
			EULms_ini[1] = EULms_ini[1] + sin(EUL[1]);
			EULms_ini[2] = EULms_ini[2] + sin(EUL[2]);
			EULmc_ini[0] = EULmc_ini[0] + cos(EUL[0]);
			EULmc_ini[1] = EULmc_ini[1] + cos(EUL[1]);
			EULmc_ini[2] = EULmc_ini[2] + cos(EUL[2]);
			gyrxm = gyrxm + gyrx[counter_ini];
			gyrx2m = gyrx2m + gyrx2[counter_ini];
			gyrxym[0] = gyrxym[0] + gyrxy[0][counter_ini];
			gyrxym[1] = gyrxym[1] + gyrxy[1][counter_ini];
			gyrxym[2] = gyrxym[2] + gyrxy[2][counter_ini];
			counter_ini++;
		}
		if (i == n_INI - 1){
			gyrxmm = gyrxm / (counter_ini);
			gyrymm[0] = gyrym[0] / (counter_ini);
			gyrymm[1] = gyrym[1] / (counter_ini);
			gyrymm[2] = gyrym[2] / (counter_ini);

			Mthini = Mthm_ini / (counter_ini);

			Orien[0][0] = atan2(EULms_ini[0], EULmc_ini[0]);
			Orien[1][0] = atan2(EULms_ini[1], EULmc_ini[1]);
			Orien[2][0] = atan2(EULms_ini[2], EULmc_ini[2]);
			Orienini[0][0] = Orien[0][0];
			Orienini[1][0] = Orien[1][0];
			Orienini[2][0] = Orien[2][0];
			//bias calculation
			gyr_bias[0][0] = (gyrxym[0] - gyrxm*gyrymm[0]) / (gyrx2m - gyrxm*gyrxmm);
			gyr_bias[1][0] = (gyrxym[1] - gyrxm*gyrymm[1]) / (gyrx2m - gyrxm*gyrxmm);
			gyr_bias[2][0] = (gyrxym[2] - gyrxm*gyrymm[2]) / (gyrx2m - gyrxm*gyrxmm);
			DCM_calcu(Orienini, C_b2n);
			for (int lpp = 0; lpp<9; lpp++){
				d_ini[lpp][0] = X_ini[lpp][start[lpp]];
			}
			ena_ini = 1;
		}
	}
	else{
		for (int lppp = 0; lppp<9; lppp++){
			X_ini[lppp][start[lppp]] = sensordata[lppp];
			d_ini[lppp][0] = X_ini[lppp][start[lppp]];
			start[lppp] = (start[lppp] + 1) % n_INI;
		}
	}

	if (ena_ini == 1){
		accf = sqrt(pow(d_ini[0][0], 2) + pow(d_ini[1][0], 2) + pow(d_ini[2][0], 2));
		gyrf = sqrt(pow(d_ini[3][0] - Gyro_ini[0], 2) + pow(d_ini[4][0] - Gyro_ini[1], 2) + pow(d_ini[5][0] - Gyro_ini[2], 2));
        if (gyrf < 60 * deg2pi){
			C3 = 1;
		}
		else{
			C3 = 0;
		}
		if (accf>9 && accf<11){
			C1 = 1;
		}
		else{
			C1 = 0;
		}

		if (counter2 <= med_L && ena_med == 0){
			counter2++;
			C_total_m[counter2 - 1] = C1 & C3;
			for (int lp_med = 0; lp_med<9; lp_med++){
				d_med[lp_med][(counter2 - 1)] = d_ini[lp_med][0];
			}
			if (counter2 == med_L){
				for (int i_med = 0; i_med<med_L; i_med++){
					C_median_I[i_med] = C_total_m[i_med];
				}
				medianfilter((element*)C_median_I, (element*)C_median_O, med_L, med_L);
				for (int j_med = 0; j_med<(med_L + 1) / 2; j_med++){
					C_total_n[j_med] = C_median_O[j_med];
				}
				for (int lpp_med = 0; lpp_med<9; lpp_med++){
					d_cal[lpp_med][0] = d_med[lpp_med][start_med[lpp_med]];
				}
				ena_med = 1;
			}
		}
		else{
			C_total_m[start_C] = C1 & C3;
			start_C = (start_C + 1) % med_L;
			for (int ii_med = 0; ii_med<med_L; ii_med++){
				C_median_I[ii_med] = C_total_m[(start_C + ii_med) % med_L];
			}
			medianfilter((element*)C_median_I, (element*)C_median_O, med_L, med_L);

			C_total_n[start_CT] = C_median_O[(med_L - 1) / 2];
			start_CT = (start_CT + 1) % ((med_L + 1) / 2);
			for (int lppp_med = 0; lppp_med<9; lppp_med++){
				d_med[lppp_med][start_med[lppp_med]] = d_ini[lppp_med][0];
				start_med[lppp_med] = (start_med[lppp_med] + 1) % med_L;
				d_cal[lppp_med][0] = d_med[lppp_med][start_med[lppp_med]];
			}
		}

		if (ena_med == 1){
			if (counter <= N){
				counter++;
			}
			C_total[start_T] = C_total_n[start_CT];
			start_T = (start_T + 1) % 2;

			acc_raw[0] = d_cal[0][0];
			acc_raw[1] = d_cal[1][0];
			acc_raw[2] = d_cal[2][0];
			accf = sqrt(pow(acc_raw[0], 2) + pow(acc_raw[1], 2) + pow(acc_raw[2], 2));
			gyr_raw[0] = d_cal[3][0] - gyr_bias[0][0];
			gyr_raw[1] = d_cal[4][0] - gyr_bias[1][0];
			gyr_raw[2] = d_cal[5][0] - gyr_bias[2][0];
			gyrf = sqrt(pow(gyr_raw[0], 2) + pow(gyr_raw[1], 2) + pow(gyr_raw[2], 2));
			mag_b[0][0] = d_cal[6][0];
			mag_b[1][0] = d_cal[7][0];
			mag_b[2][0] = d_cal[8][0];
			magf = sqrt(pow(mag_b[0][0], 2) + pow(mag_b[1][0], 2) + pow(mag_b[2][0], 2));



            gyr[0] = gyr_raw[0] - xx[3][0];
            gyr[1] = gyr_raw[1] - xx[4][0];
            gyr[2] = gyr_raw[2] - xx[5][0];
            acc_b[0][0] = acc_raw[0];// -xx[12][0];
            acc_b[1][0] = acc_raw[1];// -xx[13][0];
            acc_b[2][0] = acc_raw[2];// -xx[14][0];

			// Calculation of S_ang
			S_ang[0][0] = 0;
			S_ang[0][1] = -gyr[2];
			S_ang[0][2] = gyr[1];
			S_ang[1][0] = gyr[2];
			S_ang[1][1] = 0;
			S_ang[1][2] = -gyr[0];
			S_ang[2][0] = -gyr[1];
			S_ang[2][1] = gyr[0];
			S_ang[2][2] = 0;

			S_angdt[0][0] = 0;
			S_angdt[0][1] = -gyr[2] * dt;
			S_angdt[0][2] = gyr[1] * dt;
			S_angdt[1][0] = gyr[2] * dt;
			S_angdt[1][1] = 0;
			S_angdt[1][2] = -gyr[0] * dt;
			S_angdt[2][0] = -gyr[1] * dt;
			S_angdt[2][1] = gyr[0] * dt;
			S_angdt[2][2] = 0;

			MatrixSub((float*)eye3_p2, (float*)S_angdt, 3, 3, (float*)eye3mSang);
			MatrixInvLU((float*)eye3mSang, 3, (float*)inveye3mSang);
			MatrixAdd((float*)eye3_p2, (float*)S_angdt, 3, 3, (float*)eye3pSang);

			MatrixMul((float*)eye3pSang, (float*)inveye3mSang, 3, 3, 3, (float*)C_b2n_change);
			MatrixMul((float*)C_b2n, (float*)C_b2n_change, 3, 3, 3, (float*)C_b2n_m);

			Orien_m[0][0] = atan2(C_b2n_m[2][1], C_b2n_m[2][2]);
			Orien_m[1][0] = -asin(C_b2n_m[2][0]);
			Orien_m[2][0] = atan2(C_b2n_m[1][0], C_b2n_m[0][0]);
			Orien_m[0][0] = fmod((Orien_m[0][0] * pi2deg), 360)*deg2pi;
			Orien_m[1][0] = fmod((Orien_m[1][0] * pi2deg), 360)*deg2pi;
			Orien_m[2][0] = fmod((Orien_m[2][0] * pi2deg), 360)*deg2pi;
			Orien_m[0][0] = AngCal(Orien_m[0][0]);
			Orien_m[1][0] = AngCal(Orien_m[1][0]);
			Orien_m[2][0] = AngCal(Orien_m[2][0]);
			if (Orien_m[1][0]<-pi / 2){
				Orien_m[1][0] = -Orien_m[1][0] - pi;
			}
			if (Orien_m[1][0]>pi / 2){
				Orien_m[1][0] = -Orien_m[1][0] + pi;
			}
			/*
			xx[0][0]=0;
			xx[1][0]=0;
			xx[2][0]=0;

			S_orien[0][0] = 0;
			S_orien[0][1] = xx[2][0];
			S_orien[0][2] = -xx[1][0];
			S_orien[1][0] = -xx[2][0];
			S_orien[1][1] = 0;
			S_orien[1][2] = xx[0][0];
			S_orien[2][0] = xx[1][0];
			S_orien[2][1] = -xx[0][0];
			S_orien[2][2] = 0;

			MatrixSub((float*) eye3_p2, (float*) S_orien, 3, 3, (float*) eye3mSori);
			MatrixAdd((float*) eye3_p2, (float*) S_orien, 3, 3, (float*) eye3pSori);
			MatrixInvLU((float*) eye3mSori, 3, (float*) inveye3mSori);
			MatrixMul((float*) eye3pSori, (float*) inveye3mSori, 3, 3, 3, (float*) C_b2n_change_new);
			MatrixMul((float*) C_b2n_change_new, (float*) C_b2n_m, 3, 3, 3, (float*) C_b2n);

			OrientationComputed(Orien_m[0][0], Orien_m[1][0], Orien_m[2][0]);
			*/

			MatrixMul((float*)C_b2n_m, (float*)mag_b, 3, 3, 1, (float*)mag_n);
			ang_mag = atan2(mag_n[2][0], sqrt(pow(mag_n[0][0], 2) + pow(mag_n[1][0], 2)));
			MatrixTranspose((float*)mag_b, 3, 1, (float*)mag_b_TP);
			orien_mag_std((float*)acc_b, (float*)mag_b_TP, Orien_mag);



			Orien_comp[0] = Orien_mag[0];
			Orien_comp[1] = Orien_mag[1];
			Orien_comp[2] = Orien_mag[2];

			MatrixTranspose((float*)C_b2n_m, 3, 3, (float*)C_b2n_m_TP);
			MatrixMul((float*)C_b2n_m_TP, (float*)B, 3, 3, 1, (float*)mag_b_r);
			MatrixTranspose((float*)mag_b_r, 3, 1, (float*)mag_b_r_TP);
			orien_mag_std((float*)acc_b, (float*)mag_b_r_TP, (float*)Orien_mag_r);

			Hth = acc_b[0][0] * mag_b_r[0][0] + acc_b[1][0] * mag_b_r[1][0] + acc_b[2][0] * mag_b_r[2][0];
			Mth = acc_b[0][0] * mag_b[0][0] + acc_b[1][0] * mag_b[1][0] + acc_b[2][0] * mag_b[2][0];



			//if (counter == 1){
				//Hthini = Hth;
			//}
			//else{
				//if (magf<1.1 && magf>0.9 && fabs(Hth-Hthini)>fabs(Mth-Mthini)){
				if (magf<1.1 && magf>0.9 && ang_mag<-1.1141 + 0.2 && ang_mag>-1.1141 - 0.2){
					Orien_comp[2] = Orien_mag[2];
				}
				else{
					Orien_comp[2] = Orien_mag_r[2];
				}
			//}
			//Orien_comp[counter-1][2] = Orien_mag_r[2];

			Orien_comp[0] = fmod((Orien_comp[0] * pi2deg), 360)*deg2pi;
			Orien_comp[1] = fmod((Orien_comp[1] * pi2deg), 360)*deg2pi;
			Orien_comp[2] = fmod((Orien_comp[2] * pi2deg), 360)*deg2pi;
			Orien_comp[0] = AngCal(Orien_comp[0]);
			Orien_comp[1] = AngCal(Orien_comp[1]);
			Orien_comp[2] = AngCal(Orien_comp[2]);
			if (Orien_comp[1]<-pi / 2){
				Orien_comp[1] = -Orien_comp[1] - pi;
			}
			if (Orien_comp[1]>pi / 2){
				Orien_comp[1] = -Orien_comp[1] + pi;
			}

			//OrientationComputed(Orien_comp[0], Orien_comp[1], Orien_comp[2]);

			delta_orien1[0][0] = Orien_m[0][0] - Orien_comp[0];
			delta_orien1[1][0] = Orien_m[1][0] - Orien_comp[1];
			delta_orien1[2][0] = Orien_m[2][0] - Orien_comp[2];
			delta_orien1[0][0] = fmod((delta_orien1[0][0] * pi2deg), 360)*deg2pi;
			delta_orien1[1][0] = fmod((delta_orien1[1][0] * pi2deg), 360)*deg2pi;
			delta_orien1[2][0] = fmod((delta_orien1[2][0] * pi2deg), 360)*deg2pi;
			delta_orien1[0][0] = AngCal(delta_orien1[0][0]);
			delta_orien1[1][0] = AngCal(delta_orien1[1][0]);
			delta_orien1[2][0] = AngCal(delta_orien1[2][0]);


			delta_orien2 = 0;
			if (cont_c == MM){
				cont_c = 0;
				id1 = 0;
				id2 = 0;
				counter1 = 0;
				counter_temp = 0;
				SN[0] = 0;
				SN[1] = 0;
				SN[2] = 0;
			}
			if (counter > 1){
				if ((C_total[(start_T + 1) % 2] == 1) && (C_total[start_T] == 0)){
					id1 = 1;
					id2 = 1;
				}
			}
			if (id2 == 1){
				id2 = 0;
				SN[counter1] = cont_c;
				cont_c = 0;
				if (counter1 == 2){
					id3 = 1;
				}
				counter1 = (counter1 + 1) % 3;
			}
			if (id3 == 1){
				N1 = (counter1 - 1 + 3) % 3;
				N2 = (counter1 - 2 + 3) % 3;
				N3 = (counter1 - 3 + 3) % 3;
				cont1 = counter_temp - (SN[N1] + SN[N2]);
				cont2 = counter_temp - SN[N1];
				cont1_temp = (cont1 + NN) % NN;
				cont2_temp = (cont2 + NN) % NN;
				delta_orien2 = Orien_m[2][0] - (Orien_temp[cont1_temp] + Orien_temp[cont2_temp]) / 2;
			}
			if (fabs(delta_orien2) >= 4 * deg2pi){
				delta_orien2 = 0;
			}
            delta_orien2 = 0;

			MatrixMul((float*)C_b2n_m, (float*)acc_b, 3, 3, 1, (float*)acc_n);
			MatrixSub((float*)acc_n, (float*)G, 3, 1, (float*)acc_n_ng);
            acc_res[0] = acc_n_ng[0][0];
            acc_res[1] = acc_n_ng[1][0];
            acc_res[2] = acc_n_ng[2][0];

			acc_n_ngdt[0] = acc_n_ng[0][0] * dt;
			acc_n_ngdt[1] = acc_n_ng[1][0] * dt;
			acc_n_ngdt[2] = acc_n_ng[2][0] * dt;
			MatrixAdd((float*)v, (float*)acc_n_ngdt, 1, 3, (float*)v_m);
			v_mdt[0] = v_m[0] * dt;
			v_mdt[1] = v_m[1] * dt;
			v_mdt[2] = v_m[2] * dt;
			MatrixAdd((float*)p, (float*)v_mdt, 1, 3, (float*)p_m);
			//CTotalComputed(C_total[(counter + 1) % 2]);
			if (C_total[(counter + 1) % 2] == 1){ //Plot this
				m[0][0] = delta_orien1[0][0];
				m[1][0] = delta_orien1[1][0];
                m[2][0] = delta_orien2;// + delta_orien1[2][0];//0;//delta_orien2 + delta_orien1[2][0];
				m[3][0] = gyr[0];
				m[4][0] = gyr[1];
				m[5][0] = gyr[2];
				m[6][0] = v_m[0];
				m[7][0] = v_m[1];
				m[8][0] = v_m[2];

				/////gyr bias update//////
                if (accf<g*1.03 && accf>g*0.97){
				if (counter1_ini==0){
				gyrsum1[0][counter1_ini] = gyr[0];
				gyrsum1[1][counter1_ini] = gyr[1];
				gyrsum1[2][counter1_ini] = gyr[2];}
				else{
				gyrsum1[0][counter1_ini] = gyrsum1[0][counter1_ini-1]+gyr[0];
				gyrsum1[1][counter1_ini] = gyrsum1[1][counter1_ini-1]+gyr[1];
				gyrsum1[2][counter1_ini] = gyrsum1[2][counter1_ini-1]+gyr[2];}
				gyrx1[counter1_ini]=counter1_ini+1;
				gyrx21[counter1_ini]=(counter1_ini+1)*(counter1_ini+1);

				gyrxy1[0][counter1_ini]=gyrx1[counter1_ini]*gyrsum1[0][counter1_ini];
				gyrxy1[1][counter1_ini]=gyrx1[counter1_ini]*gyrsum1[1][counter1_ini];
				gyrxy1[2][counter1_ini]=gyrx1[counter1_ini]*gyrsum1[2][counter1_ini];
				gyrym1[0]=gyrym1[0]+gyrsum1[0][counter1_ini];
				gyrym1[1]=gyrym1[1]+gyrsum1[1][counter1_ini];
				gyrym1[2]=gyrym1[2]+gyrsum1[2][counter1_ini];

				gyrxm1=gyrxm1+gyrx1[counter1_ini];
				gyrx2m1=gyrx2m1+gyrx21[counter1_ini];
				gyrxym1[0]=gyrxym1[0]+gyrxy1[0][counter1_ini];
				gyrxym1[1]=gyrxym1[1]+gyrxy1[1][counter1_ini];
				gyrxym1[2]=gyrxym1[2]+gyrxy1[2][counter1_ini];
				counter1_ini++;
                }
				if (counter1_ini==n_INI1){
				gyrxmm1 = gyrxm1/(counter1_ini);
				gyrymm1[0] = gyrym1[0]/(counter1_ini);
				gyrymm1[1] = gyrym1[1]/(counter1_ini);
				gyrymm1[2] = gyrym1[2]/(counter1_ini);
				gyr_bias1[0][0] = (gyrxym1[0]-gyrxm1*gyrymm1[0])/(gyrx2m1-gyrxm1*gyrxmm1);
				gyr_bias1[1][0] = (gyrxym1[1]-gyrxm1*gyrymm1[1])/(gyrx2m1-gyrxm1*gyrxmm1);
				gyr_bias1[2][0] = (gyrxym1[2]-gyrxm1*gyrymm1[2])/(gyrx2m1-gyrxm1*gyrxmm1);
				gyr_bias[0][0] = gyr_bias[0][0] + gyr_bias1[0][0];
				gyr_bias[1][0] = gyr_bias[1][0] + gyr_bias1[1][0];
				gyr_bias[2][0] = gyr_bias[2][0] + gyr_bias1[2][0];
				counter1_ini = 0;}
				//////////////////////////////////////


			}
			else{
				m[0][0] = 0;
				m[1][0] = 0;
				m[2][0] = delta_orien2;
				m[3][0] = 0;
				m[4][0] = 0;
				m[5][0] = 0;
				m[6][0] = 0;
				m[7][0] = 0;
				m[8][0] = 0;

				counter1_ini = 0;
			}

			for (int i_x = 0; i_x<3; i_x++){
				xx[i_x][0] = x_ini[i_x][0];
				xx[i_x + 6][0] = x_ini[i_x + 6][0];
				xx[i_x + 9][0] = x_ini[i_x + 9][0];
			}

			//Kalman filtering
			if (C_total[(counter + 1) % 2] == 1){
                Kalman_filter((float*)x_new, (float*)P_new, (float*)xx, (float*)P, (float*)m, (float*)H, (float*)acc_b, (float*)C_b2n_m, (float*)Q, (float*)R, dt);
                /*
                for (int iii = 0; iii<15; iii++){
                    x_new[iii][0] = x_ini[iii][0];
                    for (int jjj = 0; jjj<15; jjj++){
                        P_new[iii][jjj] = P_ini[iii][jjj];
                    }
                }
                */
			}
			else{
				for (int iii = 0; iii<15; iii++){
					x_new[iii][0] = x_ini[iii][0];
					for (int jjj = 0; jjj<15; jjj++){
						P_new[iii][jjj] = P_ini[iii][jjj];
					}
				}
			}

            if (isnan(x_new[0][0]+x_new[1][0]+x_new[2][0])){
                for (int iii = 0; iii<15; iii++){
                    x_new[iii][0] = x_ini[iii][0];
                    for (int jjj = 0; jjj<15; jjj++){
                        P_new[iii][jjj] = P_ini[iii][jjj];
                    }
                }
            }

			for (int iii = 0; iii<15; iii++){
				xx[iii][0] = x_new[iii][0];
				for (int jjj = 0; jjj<15; jjj++){
					P[iii][jjj] = P_new[iii][jjj];
				}
			}

			posi[0][0] = p_m[0] - xx[6][0];
			posi[1][0] = p_m[1] - xx[7][0];
			posi[2][0] = p_m[2] - xx[8][0];
			velo[0][0] = v_m[0] - xx[9][0];
			velo[1][0] = v_m[1] - xx[10][0];
			velo[2][0] = v_m[2] - xx[11][0];

			//Position * pos = new Position;
			//pos->Data[0] = posi[0][0];
			//pos->Data[1] = posi[1][0];
			//pos->Data[2] = posi[2][0];
			//emit PositionComputed(pos);
			//_PositionPlotter->AddData(pos);

			v[0] = velo[0][0];
			v[1] = velo[1][0];
			v[2] = velo[2][0];

			v_res[0] = velo[0][0];
			v_res[1] = velo[1][0];
			v_res[2] = velo[2][0];

			//VelocityComputed(v[0], v[1], v[2]);

			p[0] = posi[0][0];
			p[1] = posi[1][0];
			p[2] = posi[2][0];

            p_res[0] = posi[0][0];//gyr_bias[0][0];//
            p_res[1] = posi[1][0];//gyr_bias[1][0];//
            p_res[2] = posi[2][0];//gyr_bias[2][0];//


            //xx[0][0]=0;
            //xx[1][0]=0;
            xx[2][0]=0;



			S_orien[0][0] = 0;
			S_orien[0][1] = xx[2][0];
			S_orien[0][2] = -xx[1][0];
			S_orien[1][0] = -xx[2][0];
			S_orien[1][1] = 0;
			S_orien[1][2] = xx[0][0];
			S_orien[2][0] = xx[1][0];
			S_orien[2][1] = -xx[0][0];
			S_orien[2][2] = 0;

			MatrixSub((float*)eye3_p2, (float*)S_orien, 3, 3, (float*)eye3mSori);
			MatrixAdd((float*)eye3_p2, (float*)S_orien, 3, 3, (float*)eye3pSori);
			MatrixInvLU((float*)eye3mSori, 3, (float*)inveye3mSori);
			MatrixMul((float*)eye3pSori, (float*)inveye3mSori, 3, 3, 3, (float*)C_b2n_change_new);
			MatrixMul((float*)C_b2n_change_new, (float*)C_b2n_m, 3, 3, 3, (float*)C_b2n);

			Orien[0][0] = atan2(C_b2n[2][1], C_b2n[2][2]);
			Orien[1][0] = -asin(C_b2n[2][0]);
			Orien[2][0] = atan2(C_b2n[1][0], C_b2n[0][0]);
			Orien[0][0] = fmod((Orien[0][0] * pi2deg), 360)*deg2pi;
			Orien[1][0] = fmod((Orien[1][0] * pi2deg), 360)*deg2pi;
			Orien[2][0] = fmod((Orien[2][0] * pi2deg), 360)*deg2pi;
			AngCal(Orien[0][0]);
			AngCal(Orien[1][0]);
			AngCal(Orien[2][0]);
			if (Orien[1][0]<-pi / 2){
				Orien[1][0] = -Orien[1][0] - pi;
			}
			if (Orien[1][0]>pi / 2){
				Orien[1][0] = -Orien[1][0] + pi;
			}

            if (isnan(Orien[0][0]+Orien[1][0]+Orien[2][0])){
                Orien[0][0] = Orien_m[0][0];
                Orien[1][0] = Orien_m[1][0];
                Orien[2][0] = Orien_m[2][0];
            }

            orien_res[0] = Orien[0][0];//xx[0][0];//Orien[0][0];
            orien_res[1] = Orien[1][0];//xx[1][0];//Orien[1][0];
            orien_res[2] = Orien[2][0];//xx[2][0];//Orien[2][0];


			if (id1 == 1){
				cont_c = cont_c + 1;
				Orien_temp[counter_temp] = Orien[2][0];
				counter_temp = (counter_temp + 1) % NN;
			}

            /*
            if (accf<g*1.03 && accf>g*0.97 && counter_temp>1){
			Orien[2][0]=Orien_temp[counter_temp-1];
			}
            */

			//OrientationComputed(Orien[0][0], Orien[1][0], Orien[2][0]);//Orien_mag_r[2]);//Orien[2][0]);

		}

	}
}

/*
Solver::Solver(vector<SensorData*> * meas_vec)
{
	_MeasurementVector = meas_vec;

	//----------Calculation Initialization---------------------
	for (int j_x=0; j_x<15; j_x++){
		xx[j_x][0] = x_ini[j_x][0];
	}

	//set initial value of matrices
	zeros(3, 12, (float*)zeros3x12);
    zeros(3, 9, (float*)zeros3x9);
    zeros(3, 6, (float*)zeros3x6);
	zeros(7, 1, (float*)m);
	
	zero(15, (float*)P_ini);
	zero(15, (float*)P);

	//////compass 3D/////////
	zero(9, (float*)R);
	zeros(9, 15, (float*)H);
	for (int ii=0; ii<3; ii++){
       for (int jj=0; jj<3; jj++){
            P_ini[ii][jj] = eye3_3[ii][jj];
			P[ii][jj] = eye3_3[ii][jj];
			Q[ii][jj] = eye3_4[ii][jj];

			//////compass 3D/////////
			R[ii][jj] = eye3_1[ii][jj];
			H[ii][jj] = eye3[ii][jj];
			//////////////////////////
            P_ini[ii+3][jj+3] = eye3_2[ii][jj];
			P[ii+3][jj+3] = eye3_2[ii][jj];

			//////compass 3D/////////
			R[ii+3][jj+3] = eye3_1[ii][jj];
			R[ii+6][jj+6] = eye3_3[ii][jj];
			H[ii+3][jj+3] = eye3[ii][jj];
			H[ii+6][jj+9] = eye3[ii][jj];
			//////////////////////////
			
			P_ini[ii+6][jj+6] = eye3_3[ii][jj];
			P[ii+6][jj+6] = eye3_3[ii][jj];
			P_ini[ii+9][jj+9] = eye3_3[ii][jj];
			P[ii+9][jj+9] = eye3_3[ii][jj];
			Q[ii+9][jj+9] = eye3_4[ii][jj];
			P_ini[ii+12][jj+12] = eye3_2[ii][jj];
			P[ii+12][jj+12] = eye3_2[ii][jj];
       }
    }
	R[2][2]=1;
	//---------------------------------------------------
}
*/

/*
void Solver::ComputeSolution(int meas_num)
{
	int i = meas_num;
	//dt = 5_DataRate * dt_default;
	if (i<=n_INI-1 && ena_ini == 0){
			 for (int lp=0; lp<9; lp++){
				 X_ini[lp][i] = (*_MeasurementVector)[i]->Data[lp];
			     d_ini[lp][0] = X_ini[lp][i];
			 }
			 accf_ini=sqrt(pow(d_ini[0][0],2)+pow(d_ini[1][0],2)+pow(d_ini[2][0],2));
			 if (accf_ini<g*1.03 && accf_ini>g*0.97){
				 
	             acc_ini[counter_ini][0] = d_ini[0][0];
                 acc_ini[counter_ini][1] = d_ini[1][0];
			     acc_ini[counter_ini][2] = d_ini[2][0];
		         gyr_ini[counter_ini][0] = d_ini[3][0];
			     gyr_ini[counter_ini][1] = d_ini[4][0];
		         gyr_ini[counter_ini][2] = d_ini[5][0];
			     mag_ini[counter_ini][0] = d_ini[6][0];
		         mag_ini[counter_ini][1] = d_ini[7][0];
			     mag_ini[counter_ini][2] = d_ini[8][0];
				 if (counter_ini==0){
				     gyrsum[0][counter_ini] = gyr_ini[counter_ini][0];
					 gyrsum[1][counter_ini] = gyr_ini[counter_ini][1];
					 gyrsum[2][counter_ini] = gyr_ini[counter_ini][2];}
				 else{
					 gyrsum[0][counter_ini] = gyrsum[0][counter_ini-1]+gyr_ini[counter_ini][0];
					 gyrsum[1][counter_ini] = gyrsum[1][counter_ini-1]+gyr_ini[counter_ini][1];
					 gyrsum[2][counter_ini] = gyrsum[2][counter_ini-1]+gyr_ini[counter_ini][2];}
				 gyrx[counter_ini]=counter_ini+1;
				 gyrx2[counter_ini]=(counter_ini+1)*(counter_ini+1);

				 gyrxy[0][counter_ini]=gyrx[counter_ini]*gyrsum[0][counter_ini];
				 gyrxy[1][counter_ini]=gyrx[counter_ini]*gyrsum[1][counter_ini];
				 gyrxy[2][counter_ini]=gyrx[counter_ini]*gyrsum[2][counter_ini];
                 
				 //calculate the euler angles for initialization
			     orien_mag_std((float*)acc_ini[counter_ini], (float*)mag_ini[counter_ini], EUL);
			     EUL_ini[counter_ini][0] = EUL[0];
			     EUL_ini[counter_ini][1] = EUL[1];
			     EUL_ini[counter_ini][2] = EUL[2];

			     Mth_ini[counter_ini] = acc_ini[counter_ini][0]*mag_ini[counter_ini][0]+acc_ini[counter_ini][1]*mag_ini[counter_ini][1]+acc_ini[counter_ini][2]*mag_ini[counter_ini][2];
				 gyrym[0]=gyrym[0]+gyrsum[0][counter_ini];
				 gyrym[1]=gyrym[1]+gyrsum[1][counter_ini];
                 gyrym[2]=gyrym[2]+gyrsum[2][counter_ini];

                 Mthm_ini=Mthm_ini+Mth_ini[counter_ini];
				 EULms_ini[0]=EULms_ini[0]+sin(EUL[0]);
				 EULms_ini[1]=EULms_ini[1]+sin(EUL[1]);
				 EULms_ini[2]=EULms_ini[2]+sin(EUL[2]);
				 EULmc_ini[0]=EULmc_ini[0]+cos(EUL[0]);
				 EULmc_ini[1]=EULmc_ini[1]+cos(EUL[1]);
				 EULmc_ini[2]=EULmc_ini[2]+cos(EUL[2]);
				 gyrxm=gyrxm+gyrx[counter_ini];
				 gyrx2m=gyrx2m+gyrx2[counter_ini];
				 gyrxym[0]=gyrxym[0]+gyrxy[0][counter_ini];
				 gyrxym[1]=gyrxym[1]+gyrxy[1][counter_ini];
				 gyrxym[2]=gyrxym[2]+gyrxy[2][counter_ini];
				 counter_ini++;
		     }
			 if (i == n_INI-1){
				 gyrxmm = gyrxm/(counter_ini);
				 gyrymm[0] = gyrym[0]/(counter_ini);
				 gyrymm[1] = gyrym[1]/(counter_ini);
				 gyrymm[2] = gyrym[2]/(counter_ini);

				 Mthini = Mthm_ini/(counter_ini);
				 
				 Orien[0][0] = atan2(EULms_ini[0],EULmc_ini[0]);
				 Orien[1][0] = atan2(EULms_ini[1],EULmc_ini[1]);
				 Orien[2][0] = atan2(EULms_ini[2],EULmc_ini[2]);
				 Orienini[0][0] = Orien[0][0];
				 Orienini[1][0] = Orien[1][0];
				 Orienini[2][0] = Orien[2][0];
				 //bias calculation
                 gyr_bias[0][0] = (gyrxym[0]-gyrxm*gyrymm[0])/(gyrx2m-gyrxm*gyrxmm);
				 gyr_bias[1][0] = (gyrxym[1]-gyrxm*gyrymm[1])/(gyrx2m-gyrxm*gyrxmm);
				 gyr_bias[2][0] = (gyrxym[2]-gyrxm*gyrymm[2])/(gyrx2m-gyrxm*gyrxmm);
				 DCM_calcu(Orienini, C_b2n); 
				 for (int lpp=0; lpp<9; lpp++){
				      d_ini[lpp][0] = X_ini[lpp][start[lpp]];
				 }
                 ena_ini = 1;	 
			 }
		 }
		 else{
              for (int lppp=0; lppp<9; lppp++){
				   X_ini[lppp][start[lppp]] = (*_MeasurementVector)[i]->Data[lppp];
				   d_ini[lppp][0] = X_ini[lppp][start[lppp]];
				   start[lppp]=(start[lppp]+1)%n_INI; 
			  }
		 }
		 
		 if (ena_ini == 1){   
			 accf = sqrt(pow(d_ini[0][0],2)+pow(d_ini[1][0],2)+pow(d_ini[2][0],2));
		     gyrf = sqrt(pow(d_ini[3][0]-Gyro_ini[0],2)+pow(d_ini[4][0]-Gyro_ini[1],2)+pow(d_ini[5][0]-Gyro_ini[2],2));			 
			 if (gyrf < 60*deg2pi){
				 C3 = 1;}
			 else{
				 C3 = 0;}
			 if (accf>9 && accf<11){
				 C1 = 1;}
			 else{
				 C1 = 0;}
		 
			 if (counter2 <= med_L && ena_med == 0){
				 counter2++;
				 C_total_m[counter2-1] = C1 & C3;
			     for(int lp_med=0; lp_med<9; lp_med++){
				     d_med[lp_med][(counter2-1)] = d_ini[lp_med][0];
			     }
			     if (counter2 == med_L){
				     for (int i_med=0; i_med<med_L; i_med++){
				          C_median_I[i_med] = C_total_m[i_med];
				     }
			         medianfilter((element*) C_median_I, (element*)C_median_O, med_L, med_L);
				     for (int j_med=0; j_med<(med_L+1)/2; j_med++){
				          C_total_n[j_med] = C_median_O[j_med];
				     }
					 for (int lpp_med=0; lpp_med<9; lpp_med++){
				          d_cal[lpp_med][0] = d_med[lpp_med][start_med[lpp_med]];
				     }
			         ena_med = 1;
			      }
			 }
			 else{
				 C_total_m[start_C] = C1 & C3;
				 start_C = (start_C+1)%med_L;
				 for (int ii_med=0; ii_med<med_L; ii_med++){
				      C_median_I[ii_med] = C_total_m[(start_C+ii_med)%med_L];
				 }
			     medianfilter((element*) C_median_I, (element*)C_median_O, med_L, med_L);

			     C_total_n[start_CT] = C_median_O[(med_L-1)/2];
				 start_CT=(start_CT+1)%((med_L+1)/2);
				 for (int lppp_med=0; lppp_med<9; lppp_med++){
					  d_med[lppp_med][start_med[lppp_med]] = d_ini[lppp_med][0];
					  start_med[lppp_med]=(start_med[lppp_med]+1)%med_L; 
					  d_cal[lppp_med][0] = d_med[lppp_med][start_med[lppp_med]];
				 }
			 }

			 if (ena_med == 1){
				 if (counter<=N){
		         counter++;}
				 C_total[start_T] = C_total_n[start_CT];
				 start_T=(start_T+1)%2;
				 
			     acc_raw[0]=d_cal[0][0];    
		         acc_raw[1]=d_cal[1][0];  
				 acc_raw[2]=d_cal[2][0];
				 accf = sqrt(pow(acc_raw[0],2)+pow(acc_raw[1],2)+pow(acc_raw[2],2));
				 gyr_raw[0]=d_cal[3][0] - gyr_bias[0][0];    
				 gyr_raw[1]=d_cal[4][0] - gyr_bias[1][0];
				 gyr_raw[2]=d_cal[5][0] - gyr_bias[2][0];
				 gyrf = sqrt(pow(gyr_raw[0],2)+pow(gyr_raw[1],2)+pow(gyr_raw[2],2));
				 mag_b[0][0]=d_cal[6][0];    
				 mag_b[1][0]=d_cal[7][0];  
				 mag_b[2][0]=d_cal[8][0];
				 magf = sqrt(pow(mag_b[0][0],2)+pow(mag_b[1][0],2)+pow(mag_b[2][0],2));
			 
			 
			 
				 gyr[0] = gyr_raw[0];// - xx[3][0];
				 gyr[1] = gyr_raw[1];// - xx[4][0];
				 gyr[2] = gyr_raw[2];// - xx[5][0];
				 acc_b[0][0] = acc_raw[0] - xx[12][0];
				 acc_b[1][0] = acc_raw[1] - xx[13][0];
				 acc_b[2][0] = acc_raw[2] - xx[14][0];
			 
				 // Calculation of S_ang
				 S_ang[0][0] = 0;
				 S_ang[0][1] = -gyr[2];
				 S_ang[0][2] = gyr[1];
				 S_ang[1][0] = gyr[2];
				 S_ang[1][1] = 0;
				 S_ang[1][2] = -gyr[0];
				 S_ang[2][0] = -gyr[1];
				 S_ang[2][1] = gyr[0];
				 S_ang[2][2] = 0;

				 S_angdt[0][0] = 0;
				 S_angdt[0][1] = -gyr[2]*dt;
				 S_angdt[0][2] = gyr[1]*dt;
				 S_angdt[1][0] = gyr[2]*dt;
				 S_angdt[1][1] = 0;
				 S_angdt[1][2] = -gyr[0]*dt;
				 S_angdt[2][0] = -gyr[1]*dt;
				 S_angdt[2][1] = gyr[0]*dt;
				 S_angdt[2][2] = 0;

				 MatrixSub((float*) eye3_p2, (float*) S_angdt, 3, 3, (float*) eye3mSang);
				 MatrixInvLU((float*) eye3mSang, 3, (float*) inveye3mSang);
				 MatrixAdd((float*) eye3_p2, (float*) S_angdt, 3, 3, (float*) eye3pSang);
			 
				 MatrixMul((float*) eye3pSang, (float*) inveye3mSang, 3, 3, 3, (float*) C_b2n_change);
				 MatrixMul((float*)C_b2n, (float*) C_b2n_change, 3, 3, 3, (float*) C_b2n_m);
			 
				 Orien_m[0][0] = atan2(C_b2n_m[2][1], C_b2n_m[2][2]);
				 Orien_m[1][0] = -asin(C_b2n_m[2][0]);
				 Orien_m[2][0] = atan2(C_b2n_m[1][0], C_b2n_m[0][0]);
				 Orien_m[0][0] = fmod((Orien_m[0][0]*pi2deg),360)*deg2pi;
				 Orien_m[1][0] = fmod((Orien_m[1][0]*pi2deg),360)*deg2pi;
				 Orien_m[2][0] = fmod((Orien_m[2][0]*pi2deg),360)*deg2pi;
				 Orien_m[0][0] = AngCal(Orien_m[0][0]);
				 Orien_m[1][0] = AngCal(Orien_m[1][0]);
				 Orien_m[2][0] = AngCal(Orien_m[2][0]);
				 if (Orien_m[1][0]<-pi/2){
					 Orien_m[1][0]=-Orien_m[1][0]-pi;}
				 if (Orien_m[1][0]>pi/2){
					 Orien_m[1][0]=-Orien_m[1][0]+pi;}
				
				 
				 MatrixMul((float*)C_b2n_m, (float*)mag_b, 3, 3, 1, (float*)mag_n);
				 ang_mag = atan2(mag_n[2][0], sqrt(pow(mag_n[0][0],2)+pow(mag_n[1][0],2)));
				 MatrixTranspose((float*) mag_b, 3, 1, (float*) mag_b_TP);
				 orien_mag_std((float*) acc_b, (float*) mag_b_TP, Orien_mag);
				 
				 				 
				 
				 Orien_comp[0] = Orien_mag[0];
				 Orien_comp[1] = Orien_mag[1];
				 Orien_comp[2] = Orien_mag[2];
				 				 
				 MatrixTranspose((float*)C_b2n_m, 3, 3, (float*)C_b2n_m_TP);
				 MatrixMul((float*) C_b2n_m_TP, (float*) B, 3, 3, 1, (float*) mag_b_r);
				 MatrixTranspose((float*) mag_b_r, 3, 1, (float*) mag_b_r_TP);
				 orien_mag_std((float*) acc_b, (float*) mag_b_r_TP, (float*) Orien_mag_r);
				 
				 Hth = acc_b[0][0]*mag_b_r[0][0]+acc_b[1][0]*mag_b_r[1][0]+acc_b[2][0]*mag_b_r[2][0];
				 Mth = acc_b[0][0]*mag_b[0][0]+acc_b[1][0]*mag_b[1][0]+acc_b[2][0]*mag_b[2][0];
				 
				 

				 if (counter == 1){
					 Hthini = Hth;	 
				 }
				 else{
					 //if (magf<1.1 && magf>0.9 && fabs(Hth-Hthini)>fabs(Mth-Mthini)){
			         if (magf<1.1 && magf>0.9 && ang_mag<-1.1141+0.2 && ang_mag>-1.1141-0.2){
						 Orien_comp[2] = Orien_mag[2];
					 }
					 else{
						 Orien_comp[2] = Orien_mag_r[2];
					 }
				 }
                 //Orien_comp[counter-1][2] = Orien_mag_r[2];

				 Orien_comp[0] = fmod((Orien_comp[0]*pi2deg),360)*deg2pi;
				 Orien_comp[1] = fmod((Orien_comp[1]*pi2deg),360)*deg2pi;
				 Orien_comp[2] = fmod((Orien_comp[2]*pi2deg),360)*deg2pi;
				 Orien_comp[0] = AngCal(Orien_comp[0]);
				 Orien_comp[1] = AngCal(Orien_comp[1]);
				 Orien_comp[2] = AngCal(Orien_comp[2]);
				 if (Orien_comp[1]<-pi/2){
					 Orien_comp[1]=-Orien_comp[1]-pi;}
				 if (Orien_comp[1]>pi/2){
					 Orien_comp[1]=-Orien_comp[1]+pi;}
                
				 //OrientationComputed(Orien_comp[0], Orien_comp[1], Orien_comp[2]);
				 
				 delta_orien1[0][0] = Orien_m[0][0] - Orien_comp[0];
				 delta_orien1[1][0] = Orien_m[1][0] - Orien_comp[1];
				 delta_orien1[2][0] = Orien_m[2][0] - Orien_comp[2];
				 delta_orien1[0][0] = fmod((delta_orien1[0][0]*pi2deg),360)*deg2pi;
				 delta_orien1[1][0] = fmod((delta_orien1[1][0]*pi2deg),360)*deg2pi;
				 delta_orien1[2][0] = fmod((delta_orien1[2][0]*pi2deg),360)*deg2pi;
				 delta_orien1[0][0] = AngCal(delta_orien1[0][0]);
				 delta_orien1[1][0] = AngCal(delta_orien1[1][0]);
				 delta_orien1[2][0] = AngCal(delta_orien1[2][0]);
			     
				 
				 delta_orien2 = 0;
				 if (cont_c == MM){ 
				     cont_c = 0;
					 id1 = 0;
					 id2 = 0;						
					 counter1 = 0;
					 counter_temp = 0;
					 SN[0] = 0;
					 SN[1] = 0;
					 SN[2] = 0;
				 }
				 if (counter > 1){ 
	                 if ((C_total[(start_T+1)%2] == 1) && (C_total[start_T] == 0)){ 
                         id1 = 1;
                         id2 = 1;
                     }
                 } 
                 if (id2 == 1){ 
                     id2 = 0;
                     SN[counter1] = cont_c;
                     cont_c = 0;
                     if (counter1 == 2){ 
                         id3 = 1;
                     }
                     counter1 = (counter1+1)%3;
                 }
                 if (id3 == 1){ 
                     N1= (counter1-1+3)%3;
                     N2= (counter1-2+3)%3;
                     N3= (counter1-3+3)%3;
                     cont1 = counter_temp-(SN[N1]+SN[N2]);
                     cont2 = counter_temp-SN[N1];
                     cont1_temp = (cont1+NN)%NN;
                     cont2_temp = (cont2+NN)%NN;
                     delta_orien2 = Orien_m[2][0] - (Orien_temp[cont1_temp]+Orien_temp[cont2_temp])/2;
                 }
                 if (fabs(delta_orien2)>=4*deg2pi){ 
                     delta_orien2 = 0;
                 }
				 
				 
				 MatrixMul((float*) C_b2n_m, (float*) acc_b, 3, 3, 1, (float*) acc_n);
				 MatrixSub((float*) acc_n, (float*) G, 3, 1, (float*) acc_n_ng);
				 acc_n_ngdt[0] = acc_n_ng[0][0]*dt;
				 acc_n_ngdt[1] = acc_n_ng[1][0]*dt;
				 acc_n_ngdt[2] = acc_n_ng[2][0]*dt;
				 MatrixAdd((float*) v, (float*) acc_n_ngdt, 1, 3, (float*) v_m);
				 v_mdt[0] = v_m[0]*dt;
				 v_mdt[1] = v_m[1]*dt;
				 v_mdt[2] = v_m[2]*dt;
				 MatrixAdd((float*) p, (float*) v_mdt, 1, 3, (float*) p_m);
				 CTotalComputed(C_total[(counter+1)%2]);
				 if (C_total[(counter+1)%2] == 1){ //Plot this
					 m[0][0] = delta_orien1[0][0];
					 m[1][0] = delta_orien1[1][0];
					 m[2][0] = delta_orien2;// + delta_orien1[2][0];//0;//delta_orien2 + delta_orien1[2][0];
					 m[3][0] = gyr[0];
					 m[4][0] = gyr[1];
					 m[5][0] = gyr[2];
					 m[6][0] = v_m[0];
					 m[7][0] = v_m[1];
					 m[8][0] = v_m[2];
					
				 }
				 else{
					 m[0][0] = 0;
					 m[1][0] = 0;
					 m[2][0] = delta_orien2;
					 m[3][0] = 0;
					 m[4][0] = 0;
					 m[5][0] = 0;
					 m[6][0] = 0;
					 m[7][0] = 0;
					 m[8][0] = 0;
					 
					 counter1_ini = 0;
				 }

				 for (int i_x=0; i_x<3; i_x++){
					  xx[i_x][0] = x_ini[i_x][0];
					  xx[i_x+6][0] = x_ini[i_x+6][0];
					  xx[i_x+9][0] = x_ini[i_x+9][0];
				 }
			 
			     //Kalman filtering
				 Kalman_filter((float*)x_new, (float*)P_new, (float*)xx, (float*)P, (float*)m, (float*)H, (float*)acc_b, (float*)C_b2n_m, (float*)Q, (float*)R, dt);
			
				 for (int iii=0; iii<15; iii++){
					  xx[iii][0] = x_new[iii][0];
					  for (int jjj=0; jjj<15; jjj++){
						   P[iii][jjj] = P_new[iii][jjj];
					  }
			     }
			 
				 posi[0][0] = p_m[0]-xx[6][0];
				 posi[1][0] = p_m[1]-xx[7][0];
				 posi[2][0] = p_m[2]-xx[8][0];
				 velo[0][0] = v_m[0]-xx[9][0];
				 velo[1][0] = v_m[1]-xx[10][0];
				 velo[2][0] = v_m[2]-xx[11][0];

				 Position * pos = new Position;
				 pos->Data[0] = posi[0][0];
				 pos->Data[1] = posi[1][0];
				 pos->Data[2] = posi[2][0];
				 emit PositionComputed(pos);
				 //_PositionPlotter->AddData(pos);

				 v[0] = velo[0][0];
				 v[1] = velo[1][0];
				 v[2] = velo[2][0];

				 VelocityComputed(v[0], v[1], v[2]);

				 p[0] = posi[0][0];
				 p[1] = posi[1][0];
				 p[2] = posi[2][0];
			     

				 S_orien[0][0] = 0;
				 S_orien[0][1] = xx[2][0];
				 S_orien[0][2] = -xx[1][0];
				 S_orien[1][0] = -xx[2][0];
				 S_orien[1][1] = 0;
				 S_orien[1][2] = xx[0][0];
				 S_orien[2][0] = xx[1][0];
				 S_orien[2][1] = -xx[0][0];
				 S_orien[2][2] = 0;
			 
				 MatrixSub((float*) eye3_p2, (float*) S_orien, 3, 3, (float*) eye3mSori);
				 MatrixAdd((float*) eye3_p2, (float*) S_orien, 3, 3, (float*) eye3pSori);
				 MatrixInvLU((float*) eye3mSori, 3, (float*) inveye3mSori);
				 MatrixMul((float*) eye3pSori, (float*) inveye3mSori, 3, 3, 3, (float*) C_b2n_change_new);
				 MatrixMul((float*) C_b2n_change_new, (float*) C_b2n_m, 3, 3, 3, (float*) C_b2n);
			 
				 Orien[0][0] = atan2(C_b2n[2][1], C_b2n[2][2]);
				 Orien[1][0] = -asin(C_b2n[2][0]);
				 Orien[2][0] = atan2(C_b2n[1][0], C_b2n[0][0]);
				 Orien[0][0] = fmod((Orien[0][0]*pi2deg),360)*deg2pi;
				 Orien[1][0] = fmod((Orien[1][0]*pi2deg),360)*deg2pi;
				 Orien[2][0] = fmod((Orien[2][0]*pi2deg),360)*deg2pi;
				 AngCal(Orien[0][0]);
				 AngCal(Orien[1][0]);
				 AngCal(Orien[2][0]);
				 if (Orien[1][0]<-pi/2){
					 Orien[1][0]=-Orien[1][0]-pi;}
				 if (Orien[1][0]>pi/2){
					 Orien[1][0]=-Orien[1][0]+pi;}
				 
				 if (id1 == 1){ 
					 cont_c=cont_c+1;
					 Orien_temp[counter_temp] = Orien[2][0];
				     counter_temp = (counter_temp+1)%NN;
				 }
				 

				 OrientationComputed(Orien[0][0], Orien[1][0], Orien[2][0]);//Orien_mag_r[2]);//Orien[2][0]);
				 
			 }
	     
	   }
}
*/
