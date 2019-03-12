#include "splinecurve.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <fstream>

using namespace std;

int main() {
    ifstream ifsx("C:/Users/0133752/Desktop/x.txt");
    ifstream ifsy("C:/Users/0133752/Desktop/y.txt");
    ofstream ofs("C:/Users/0133752/Desktop/o.csv");

    //vector<double> y = { 2.7, 6, 5, 6.5, 7, 4, 4, 5, 7, 6 };
    //vector<double> x = { 0, 1.3, 2, 3, 3.7, 4, 7, 8, 10, 11.22 };
    //vector<double> x = { 11 * cos(0.2), 11 * cos(0.4), 11 * cos(0.6), 11 * cos(0.8), 11 * cos(1.2),  cos(1.4), 11 * cos(1.6), 1 * cos(1.8), 11 * cos(2.0), 11 * cos(2.6), 11 * cos(3) };
    //vector<double> y = { 11 * sin(0.2), 11 * sin(0.4), 11 * sin(0.6), 11 * sin(0.8), 11 * sin(1.2), 1 * sin(1.4), 11 * sin(1.6), 11 * sin(1.8), 11 * sin(2.0), 11 * sin(2.6), 11 * sin(3) };


    vector<double> y;
    vector<double> x;

    string str;
    string line;
    while (!ifsx.eof()) {
        ifsx >> str;
        x.push_back(stod(str));
    }
    while (!ifsy.eof()) {
        ifsy >> str;
        y.push_back(stod(str));
    }

    double k0 = 0;
    double k1 = 0;

    cout << x.size();
    cout << y.size();
	SplineCurve sc(x, y, k0, k1);
	sc.CalcParamXY();
    
    char out[1024];
	double x1, y1, dx, dy, ddx, ddy, yaw, k;
	for (int i = 0; i < 5001; ++i){
		double n = i / 5000.0;
		sc.OutPut(x1, y1, dx, dy, ddx, ddy, yaw, k, n);
        sprintf_s(out, "%.16lf,%.16lf,%.16lf,%.16lf,%.16lf,%.16lf,%.16lf,%.16lf\n", x1, y1, dx, dy, ddx, ddy, yaw, k);
        ofs << out;
	}
	return 0;
}