#ifndef SPLINECURVE_HPP
#define SPLINECURVE_HPP

#include <vector>
#include <iostream>
#include <math.h>

class SplineCurve{
	std::vector<double> na_;
	std::vector<double> nb_;
	std::vector<double> nc_;
	std::vector<double> nd_;
	std::vector<double> nh_;
	std::vector<double> nw_;

	std::vector<double> xa_;
	std::vector<double> xb_;
	std::vector<double> xc_;
	std::vector<double> xd_;
	std::vector<double> xh_;
	std::vector<double> xw_;

	std::vector<double> ya_;
	std::vector<double> yb_;
	std::vector<double> yc_;
	std::vector<double> yd_;
	std::vector<double> yh_;
	std::vector<double> yw_;

	std::vector<double> x_;
	std::vector<double> y_;

	std::vector<double> l_;

	int size;

	double k0_, k1_;



	void CalcABCD(const std::vector<double> &i_, const std::vector<double> &o_, std::vector<double> &a_, std::vector<double> &b_, std::vector<double> &c_, std::vector<double> &d_, std::vector<double> &h_, std::vector<double> &w_){
		//a
		a_ = o_;

		//h
		for (int i = 0; i < size - 1; ++i){
			h_[i] = i_[i + 1] - i_[i];
		}

		//w
		w_[0] = 0.0;
		for (int i = 1; i < size - 1; ++i){
			w_[i] = h_[i];
		}

		//c
		c_[0] = k0_;
		for (int i = 1; i < size - 1; ++i){
			c_[i] = (3 * (a_[i + 1] - a_[i]) / h_[i]) - (3 * (a_[i] - a_[i - 1]) / h_[i - 1]);
		}
		c_[size - 1] = k1_;

		double temp;
		for (int i = 1; i < size - 1; ++i){
			c_[i] = c_[i] - c_[i - 1] * h_[i];
			temp = 2 * (h_[i - 1] + h_[i]) - w_[i - 1] * h_[i - 1];
			c_[i] = c_[i] / temp;
			w_[i] = w_[i] / temp;
		}
		for (int i = size - 2; i > 0; --i){
			c_[i] = c_[i] - c_[i + 1] * w_[i];
		}

		//b
		for (int i = 0; i < size - 1; ++i){
			b_[i] = ((a_[i + 1] - a_[i]) / h_[i]) - (h_[i] * (c_[i + 1] + 2 * c_[i])) / 3;
		}

		//d
		for (int i = 0; i < size - 1; ++i){
			d_[i] = (c_[i + 1] - c_[i]) / (3 * h_[i]);
		}
	}
public:
	SplineCurve(){}
	SplineCurve(const std::vector<double> &x, const std::vector<double> &y, double k0, double k1){
		Init(x, y, k0, k1);
	}
	int Init(const std::vector<double> &x, const std::vector<double> &y, double k0, double k1){
		if (x.size() != y.size()){ return -1; }
		size = x.size();

		xa_ = std::vector<double>(size);
		xb_ = std::vector<double>(size);
		xc_ = std::vector<double>(size);
		xd_ = std::vector<double>(size);
		xh_ = std::vector<double>(size - 1);
		xw_ = std::vector<double>(size - 1);

		ya_ = std::vector<double>(size);
		yb_ = std::vector<double>(size);
		yc_ = std::vector<double>(size);
		yd_ = std::vector<double>(size);
		yh_ = std::vector<double>(size - 1);
		yw_ = std::vector<double>(size - 1);

		na_ = std::vector<double>(size);
		nb_ = std::vector<double>(size);
		nc_ = std::vector<double>(size);
		nd_ = std::vector<double>(size);
		nh_ = std::vector<double>(size - 1);
		nw_ = std::vector<double>(size - 1);

		x_ = std::vector<double>(size);
		x_ = x;
		y_ = std::vector<double>(size);
		y_ = y;

		k0_ = k0;
		k1_ = k1;

		return 0;
	}
	void CalcParam(){
		CalcABCD(x_, y_, na_, nb_, nc_, nd_, nh_, nw_);
	}
	void CalcParamXY(){
		l_ = std::vector<double>(size);
		l_[0] = 0;
		for (int i = 1; i < size; ++i){
			l_[i] = l_[i - 1] + sqrt((x_[i] - x_[i - 1]) * (x_[i] - x_[i - 1]) + (y_[i] - y_[i - 1]) * (y_[i] - y_[i - 1]));
		}

		CalcABCD(l_, x_, xa_, xb_, xc_, xd_, xh_, xw_);
		CalcABCD(l_, y_, ya_, yb_, yc_, yd_, yh_, yw_);
	}

	double OutPut(double x){
		int i;
		for (i = 0; i < na_.size() - 1; ++i){
			if ((x_[i] <= x) && (x < x_[i + 1])){ break; }
		}


		return
			na_[i] +
			nb_[i] * (x - x_[i]) +
			nc_[i] * (x - x_[i]) * (x - x_[i]) +
			nd_[i] * (x - x_[i]) * (x - x_[i]) * (x - x_[i]);
	}
	void OutPut(double &x, double &y, double t){
		int i;
		double l = t * l_[l_.size() - 1];
		for (i = 0; i < l_.size() - 1; ++i){
			if ((l_[i] <= l) && (l < l_[i + 1])){ break; }
		}


		x =
			xa_[i] +
			xb_[i] * (l - l_[i]) +
			xc_[i] * (l - l_[i]) * (l - l_[i]) +
			xd_[i] * (l - l_[i]) * (l - l_[i]) * (l - l_[i]);
		y =
			ya_[i] +
			yb_[i] * (l - l_[i]) +
			yc_[i] * (l - l_[i]) * (l - l_[i]) +
			yd_[i] * (l - l_[i]) * (l - l_[i]) * (l - l_[i]);
		return;
	}
    void OutPut(double &x, double &y, double &dx, double &dy, double &ddx, double &ddy, double &yaw, double &k, double t) {
        int i;
        double l = t * l_[l_.size() - 1];
        for (i = 0; i < l_.size() - 1; ++i) {
            if ((l_[i] <= l) && (l < l_[i + 1])) { break; }
        }


        x =
            xa_[i] +
            xb_[i] * (l - l_[i]) +
            xc_[i] * (l - l_[i]) * (l - l_[i]) +
            xd_[i] * (l - l_[i]) * (l - l_[i]) * (l - l_[i]);
        y =
            ya_[i] +
            yb_[i] * (l - l_[i]) +
            yc_[i] * (l - l_[i]) * (l - l_[i]) +
            yd_[i] * (l - l_[i]) * (l - l_[i]) * (l - l_[i]);

        dx = xb_[i] + 2 * xc_[i] * (l - l_[i]) + 3 * xd_[i] * (l - l_[i]) * (l - l_[i]);
        dy = yb_[i] + 2 * yc_[i] * (l - l_[i]) + 3 * yd_[i] * (l - l_[i]) * (l - l_[i]);

        ddx = 2 * xc_[i] + 6 * xd_[i] * (l - l_[i]);
        ddy = 2 * yc_[i] + 6 * yd_[i] * (l - l_[i]);

        yaw = atan2(dy, dx);

        k = (ddy * dx - ddx * dy) / (dx * dx + dy * dy);

        return;
    }
};

#endif