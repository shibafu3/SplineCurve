#ifdef _DEBUG
//Debugモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_world300d.lib")            // opencv_core
#else
//Releaseモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_world300.lib") 
#endif
#pragma warning(disable:4996)

#include "splinecurve.hpp"
#include <iostream>
#include <vector>

#include <fstream>

#include "cvplot.hpp"

using namespace std;

int main(){

	CVPlot plt(cv::Point(1024, 1024));
	plt.XLim(-13, 13);
	plt.YLim(-13, 13);

	//vector<double> x = { 0, 1.3, 2, 3, 3.7, 4, 7, 8, 10, 11.22 };
	//vector<double> y = { 2.7, 6, 5, 6.5, 7, 4, 4, 5, 7, 6 };
	vector<double> x = { 11 * cos(0.2), 11 * cos(0.4), 11 * cos(0.6), 11 * cos(0.8), 11 * cos(1.2),  cos(1.4), 11 * cos(1.6), 1 * cos(1.8), 11 * cos(2.0), 11 * cos(2.6), 11 * cos(3) };
	vector<double> y = { 11 * sin(0.2), 11 * sin(0.4), 11 * sin(0.6), 11 * sin(0.8), 11 * sin(1.2), 1 * sin(1.4), 11 * sin(1.6), 11 * sin(1.8), 11 * sin(2.0), 11 * sin(2.6), 11 * sin(3) };
	double k0 = 0;
	double k1 = 0.01;

	SplineCurve sc(x, y, k0, k1);
	sc.CalcParamXY();

	double x1, y1;
	for (int i = 0; i < 10001; ++i){
		double n = i / 10000.0;
		sc.OutPut(x1, y1, n);
		plt.Plot(cv::Point2d(x1, y1), cv::Scalar::all(0), 1, '-', 1, 1);
	}
	for (int i = 0; i < x.size(); ++i){
		plt.Plot(cv::Point2d(x[i], y[i]), cv::Scalar::all(0), 4, 'o', 1, 1);
	}
	plt.Show();
	return 0;
}