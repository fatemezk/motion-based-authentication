#include "sensordatahandler.h"
#include <QAccelerometerReading>
#include <QGyroscopeReading>
#include <QDateTime>
#include <QtMath>

SensorDataHandler::SensorDataHandler(QObject *parent)
    : QObject(parent),
    m_accelerometer(new QAccelerometer(this)),
    m_gyroscope(new QGyroscope(this)),
    m_timer(new QTimer(this)),
    m_kalmanFilterAccel(new KalmanFilter(0.1, 0.1, 1, 0)),
    m_kalmanFilterGyro(new KalmanFilter(0.1, 0.1, 1, 0)),
    m_distance(0.0), m_velocity(0.0), m_time(0.0), m_lastTimestamp(0)
{
    connect(m_accelerometer, &QAccelerometer::readingChanged, this, &SensorDataHandler::onAccelerometerReadingChanged);
    connect(m_gyroscope, &QGyroscope::readingChanged, this, &SensorDataHandler::onGyroscopeReadingChanged);
    connect(m_timer, &QTimer::timeout, this, [=]() {
        if (m_lastTimestamp == 0) {
            m_lastTimestamp = QDateTime::currentMSecsSinceEpoch();
        }
        qint64 currentTimestamp = QDateTime::currentMSecsSinceEpoch();
        m_time = (currentTimestamp - m_lastTimestamp) / 1000.0;
        m_lastTimestamp = currentTimestamp;

        double accel = m_kalmanFilterAccel->update(m_accelerometer->reading()->x());
        m_distance += calculateDistance(accel, m_time, m_velocity);
        m_velocity += accel * m_time;
        emit distanceChanged();
    });
}

void SensorDataHandler::start()
{
    m_accelerometer->start();
    m_gyroscope->start();
    m_timer->start(100);
}

void SensorDataHandler::stop()
{
    m_accelerometer->stop();
    m_gyroscope->stop();
    m_timer->stop();
}

void SensorDataHandler::onAccelerometerReadingChanged()
{
    QAccelerometerReading *reading = m_accelerometer->reading();
    double ax = reading->x();
    double ay = reading->y();
    double az = reading->z();

    // Update Kalman filter for each axis if needed (we are using only x for distance calculation here)
    double filteredAx = m_kalmanFilterAccel->update(ax);

    // Perform any additional processing required with the filtered accelerometer data
    // For simplicity, this example uses only the x-axis acceleration for distance calculation
}

void SensorDataHandler::onGyroscopeReadingChanged()
{
    QGyroscopeReading *reading = m_gyroscope->reading();
    double gx = reading->x();
    double gy = reading->y();
    double gz = reading->z();

    // Update Kalman filter for each axis if needed
    double filteredGx = m_kalmanFilterGyro->update(gx);
    double filteredGy = m_kalmanFilterGyro->update(gy);
    double filteredGz = m_kalmanFilterGyro->update(gz);

    // Perform any additional processing required with the filtered gyroscope data
    // For this example, we are not using gyroscope data directly in distance calculation
}

double SensorDataHandler::calculateDistance(double acceleration, double time, double initialVelocity)
{
    return 0.5 * acceleration * time * time + initialVelocity * time;
}
