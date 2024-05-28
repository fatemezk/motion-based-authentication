#include "kalmanfilter.h"
#include <cmath>

KalmanFilter::KalmanFilter(double processNoise, double measurementNoise, double estimatedError, double initialValue)
    : processNoise(processNoise), measurementNoise(measurementNoise),
    estimatedError(estimatedError), lastEstimate(initialValue) {}

double KalmanFilter::update(double measurement)
{
    double kalmanGain = estimatedError / (estimatedError + measurementNoise);
    double currentEstimate = lastEstimate + kalmanGain * (measurement - lastEstimate);
    estimatedError = (1 - kalmanGain) * estimatedError + fabs(lastEstimate - currentEstimate) * processNoise;
    lastEstimate = currentEstimate;
    return currentEstimate;
}
