#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

VectorXd CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
    /**
     * Calculate the RMSE here.
     */
    VectorXd rmse(4);
    rmse << 0, 0, 0, 0;

    if (estimations.size() != ground_truth.size() || estimations.size() == 0) {
        cout << "Invalid estimations or ground_truth data" << endl;
        return rmse;
    }

    for (int i = 0; i < estimations.size(); i++) {
        VectorXd residual = estimations[i] - ground_truth[i];
        residual = residual.array() * residual.array();
        rmse += residual;
    }

    rmse = rmse / estimations.size();

    rmse = rmse.array().sqrt();

    return rmse;
}

void PolarToCartesian(const MeasurementPackage &measurement_pack, double &px, double &py, double& v) {
    double rho = measurement_pack.raw_measurements_[0];
    double phi = measurement_pack.raw_measurements_[1];
    double rho_dot = measurement_pack.raw_measurements_[2];

    px = rho * cos(phi);
    py = rho * sin(phi);
    double vx = rho_dot * cos(phi);
    double vy = rho_dot * sin(phi);
    v = sqrt(vx* vx + vy*vy);
}

Eigen::VectorXd CartesianToPolar(const Eigen::VectorXd x) {
    VectorXd z_pred(3);

    double px = x(0);
    double py = x(1);
    double vx = x(2);
    double vy = x(3);

    double px2 = px * px;
    double py2 = py * py;
    double rho = sqrt(px2 + py2);

    double phi = atan2(py, px);

    z_pred[0] = rho;
    z_pred[1] = phi;
    z_pred[2] = (px * vx + py * vy) / rho;

    return z_pred;
}

void NormalizeAngle(double &angle) {
    while (angle < -M_PI or angle > M_PI) {
        if (angle < -M_PI) {
            angle += 2 * M_PI;
        } else {
            angle -= 2 * M_PI;
        }
    }
}
