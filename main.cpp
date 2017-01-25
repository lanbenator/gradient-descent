#include <iostream>
#include <math.h>
#include "Iris.h"
#include "Data.h"

using namespace std;

const int DIM = 2;

double h(double *x, double *theta, int size){
    double result = 0;
    for (int i = 0; i < size; ++i) {
        result += x[i] * theta[i];
    }
    return result;
}

double squaredError(double x[][DIM], double *y, double *theta, int size){
    double result = 0;
    for (int i = 0; i < size; ++i) {
//        cout << i << ": " << y[i] << " - " << h(x[i], theta, DIM) << endl;
        result += pow(y[i] - h(x[i], theta, DIM),2);
    }
    return result / size;
}

double updateTheta(double x[][DIM], double *y, double *theta, int thI, int size){
    double newTheta = 0;
    for (int i = 0; i < size; ++i) {
//        cout << i << ": " << y[i] << " - " << h(x[i], theta, DIM) << endl;
        newTheta += (h(x[i], theta, DIM) - y[i]) * x[i][thI];
    }
    return 0.02 * newTheta / (size);
}


int main() {
    cout << "Hello, World!" << endl;

//    int a = 10;
//    cout << a << endl;
//    int b[2] = {2,3};
//    cout << b[0] << ", " << b[1] << endl;
//    cout << *b << ", " << (*b + 1) << endl;

    int c[2][3] = {{1,2,3},{4,5,6}};
    cout << c[0][0] << c[1][2]  << endl;

    int * subarray = c[0];
    for (int i = 0; i < 3; ++i) {
        cout << subarray[i] << endl;
    }

    Iris *data = new Iris();

    double x1[2] = {1,10};
    double theta[2] = {0,0};
    cout << "h: " << h(x1, theta, 2) << endl;

//    double x[10][2] = {{1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7}, {1,8}, {1,9}, {1,10}};
//    double y[10] = {3,4,5,6,7,8,9,10,11,12};

    const int size = 150;

    double x[size][2];
    double y[size];
    for (int i = 0; i < size; ++i) {
        x[i][0] = 1;
        x[i][1] = data->data[i][0];
        y[i] = data->data[i][1];
    }

    const int iteration = 10000;
    double thetaArray[iteration][2];
    double mse = 100;

    for (int i = 0; i < iteration; ++i) {
        mse = squaredError(x, y, theta, size);
        cout << "----------------------" << endl;
        cout << "Iteration " << i << endl;
        cout << "mse: " << mse << endl;
        cout << "theta: " << theta[0] << ", " << theta[1] << endl;
        thetaArray[i][0] = theta[0];
        thetaArray[i][1] = theta[1];

        double newTheta[2];
        newTheta[0] = theta[0] - updateTheta(x,y,theta,0,size);
        newTheta[1] = theta[1] - updateTheta(x,y,theta,1,size);
        copy(begin(newTheta), end(newTheta), begin(theta));
    }

    cout << "a=matrix(c(";
    for (int j = 0; j < iteration; ++j) {
        cout << thetaArray[j][0] << "," << thetaArray[j][1] << ",";
    }
    cout << "), nrow=" << iteration << ")"<<endl;
    cout << "data=matrix(c(";
    for (int j = 0; j < size; ++j) {
        cout << data->data[j][0] << "," << data->data[j][1] << ",";
    }
    cout << "), nrow=" << size << ")";

    return 0;
}