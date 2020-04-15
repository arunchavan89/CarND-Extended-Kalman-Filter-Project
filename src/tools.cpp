#include "tools.h"
#include <iostream>

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
   * Calculate the RMSE here.
   */
  VectorXd rmse(4);
  rmse<<0, 0, 0, 0;

  //check if estimation and ground-truth vectors are not empty
  if((estimations.size() <= 0) || (ground_truth.size() <= 0) || (estimations.size() != ground_truth.size()))
  {
     printf("Error: Either estimations or ground_truth vector is empty.!");
  }
  else
  {
     for (int i = 0; i < estimations.size(); i++)
     {
        VectorXd diff = estimations[i] - ground_truth[i];
        diff = diff.array() * diff.array();
        rmse += diff;
     }
     // : calculate the mean
     rmse = rmse/estimations.size();
     // : calculate the squared root
     //rmse = rmse.sqrt();
  }

  return rmse;
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  /**
   * Calculate a Jacobian here.
   */
  MatrixXd Hj(3,4);
  // recover state parameters
  float px = x_state(0);
  float py = x_state(1);
  float vx = x_state(2);
  float vy = x_state(3);

  // YOUR CODE HERE 
  float c1 = px*px + py*py;
  float c2 = sqrt(c1);
  float c3 = c1*c2;
  
  // check division by zero
  if (fabs(c1) < 0.0001) {
    std::cout << "CalculateJacobian () - Error - Division by Zero" << std::endl;
    return Hj;
  }
  
  // compute the Jacobian matrix
  Hj<<(px/c2), (py/c2), 0, 0,
  -(py/c1), (px/c1), 0, 0,
      py*(vx*py - vy*px)/c3, px*(px*vy - py*vx)/c3, px/c2, py/c2;
  
  return Hj;
}
