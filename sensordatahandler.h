#ifndef SENSORDATAHANDLER_H
#define SENSORDATAHANDLER_H

#include <QObject>
#include <QAccelerometer>
#include <QGyroscope>
#include <QTimer>
#include "kalmanfilter.h"

class SensorDataHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double distance READ distance NOTIFY distanceChanged)

public:
    explicit SensorDataHandler(QObject *parent = nullptr);
    double distance() const { return m_distance; }

signals:
    void distanceChanged();

public slots:
    void start();
    void stop();
    void onAccelerometerReadingChanged();
    void onGyroscopeReadingChanged();

private:
    QAccelerometer *m_accelerometer;
    QGyroscope *m_gyroscope;
    QTimer *m_timer;
    KalmanFilter *m_kalmanFilterAccel;
    KalmanFilter *m_kalmanFilterGyro;
    double m_distance;
    double m_velocity;
    double m_time;
    qint64 m_lastTimestamp;

    double calculateDistance(double acceleration, double time, double initialVelocity);
};

#endif // SENSORDATAHANDLER_H
