#ifndef TOOLS_H_
#define TOOLS_H_
#include <vector>
#include "Eigen/Dense"
#include "measurement_package.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

#define EPSLION 0.00001

/**
 * A helper method to calculate RMSE.
 */
VectorXd CalculateRMSE(const vector<VectorXd> &estimations, const vector<VectorXd> &ground_truth);

void PolarToCartesian(const MeasurementPackage &measurement_pack, double &px, double &py, double &v);

Eigen::VectorXd CartesianToPolar(const Eigen::VectorXd x);

void NormalizeAngle(double &angle);

#endif /* TOOLS_H_ */
