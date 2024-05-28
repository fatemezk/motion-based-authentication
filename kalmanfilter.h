#ifndef KALMANFILTER_H
#define KALMANFILTER_H

class KalmanFilter
{
public:
    KalmanFilter(double processNoise, double measurementNoise, double estimatedError, double initialValue);
    double update(double measurement);

private:
    double processNoise;
    double measurementNoise;
    double estimatedError;
    double lastEstimate;
};

#endif // KALMANFILTER_H
