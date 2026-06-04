#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// This class stores one sensor reading
class Reading
{
private:
    string sensorId;
    string type;
    double value;
    string unit;

public:
    Reading(string id, string t, double v, string u)
    {
        sensorId = id;
        type = t;
        value = v;
        unit = u;
    }

    string getSensorId()
    {
        return sensorId;
    }

    string getType()
    {
        return type;
    }

    double getValue()
    {
        return value;
    }

    string getUnit()
    {
        return unit;
    }

    void printReading()
    {
        cout << sensorId << " - " << type << ": " << value << " " << unit << endl;
    }
};

// Base class
class Sensor
{
protected:
    string sensorId;
    string location;

public:
    Sensor(string id, string loc)
    {
        sensorId = id;
        location = loc;
    }

    virtual vector<Reading> collectReadings() = 0;
    virtual bool checkAlert(vector<Reading> readings) = 0;
    virtual string getSensorType() = 0;

    string getSensorId()
    {
        return sensorId;
    }

    string getLocation()
    {
        return location;
    }
};

// Temperature sensor class
class TemperatureSensor : public Sensor
{
private:
    double highLimit;

public:
    TemperatureSensor(string id, string loc, double limit) : Sensor(id, loc)
    {
        highLimit = limit;
    }

    vector<Reading> collectReadings()
    {
        vector<Reading> readings;

        double temp = 60 + rand() % 40;

        Reading r(sensorId, "Temperature", temp, "F");
        readings.push_back(r);

        return readings;
    }

    bool checkAlert(vector<Reading> readings)
    {
        if (readings[0].getValue() > highLimit)
        {
            return true;
        }

        return false;
    }

    string getSensorType()
    {
        return "Temperature Sensor";
    }
};

// Motion sensor class
class MotionSensor : public Sensor
{
public:
    MotionSensor(string id, string loc) : Sensor(id, loc)
    {
    }

    vector<Reading> collectReadings()
    {
        vector<Reading> readings;

        double motion = rand() % 2;

        Reading r(sensorId, "Motion", motion, "0=no 1=yes");
        readings.push_back(r);

        return readings;
    }

    bool checkAlert(vector<Reading> readings)
    {
        if (readings[0].getValue() == 1)
        {
            return true;
        }

        return false;
    }

    string getSensorType()
    {
        return "Motion Sensor";
    }
};

// CO2 and CO sensor class
class CO2COSensor : public Sensor
{
private:
    double co2Limit;
    double coLimit;

public:
    CO2COSensor(string id, string loc, double c2Limit, double cLimit) : Sensor(id, loc)
    {
        co2Limit = c2Limit;
        coLimit = cLimit;
    }

    vector<Reading> collectReadings()
    {
        vector<Reading> readings;

        double co2 = 300 + rand() % 1000;
        double co = rand() % 50;

        Reading r1(sensorId, "CO2", co2, "ppm");
        Reading r2(sensorId, "CO", co, "ppm");

        readings.push_back(r1);
        readings.push_back(r2);

        return readings;
    }

    bool checkAlert(vector<Reading> readings)
    {
        if (readings[0].getValue() > co2Limit)
        {
            return true;
        }

        if (readings[1].getValue() > coLimit)
        {
            return true;
        }

        return false;
    }

    string getSensorType()
    {
        return "CO2/CO Sensor";
    }
};

// Logs the sensor readings
class DataLogger
{
public:
    void logReading(Reading r)
    {
        cout << "Logging reading: ";
        r.printReading();
    }
};

// Sends alerts
class Notifier
{
public:
    void sendAlert(string sensorId, string location)
    {
        cout << "ALERT: Sensor " << sensorId << " at " << location;
        cout << " has an unsafe reading." << endl;
    }
};

// Makes a simple report
class ReportGenerator
{
private:
    vector<Reading> allReadings;

public:
    void addReading(Reading r)
    {
        allReadings.push_back(r);
    }

    void printReport()
    {
        cout << endl;
        cout << "----- Summary Report -----" << endl;

        cout << "Total readings: " << allReadings.size() << endl;

        for (int i = 0; i < allReadings.size(); i++)
        {
            allReadings[i].printReading();
        }

        cout << "--------------------------" << endl;
    }
};

// Controller class
class Controller
{
private:
    vector<Sensor*> sensors;
    DataLogger logger;
    Notifier notifier;
    ReportGenerator report;

public:
    void addSensor(Sensor* s)
    {
        sensors.push_back(s);

        cout << "Added: " << s->getSensorType();
        cout << " at " << s->getLocation() << endl;
    }

    void runSystem()
    {
        cout << endl;
        cout << "Starting sensor monitoring..." << endl;
        cout << endl;

        for (int i = 0; i < sensors.size(); i++)
        {
            Sensor* currentSensor = sensors[i];

            vector<Reading> readings = currentSensor->collectReadings();

            for (int j = 0; j < readings.size(); j++)
            {
                logger.logReading(readings[j]);
                report.addReading(readings[j]);
            }

            if (currentSensor->checkAlert(readings))
            {
                notifier.sendAlert(currentSensor->getSensorId(), currentSensor->getLocation());
            }

            cout << endl;
        }
    }

    void makeReport()
    {
        report.printReport();
    }
};

int main()
{
    srand(time(0));

    Controller controller;

    TemperatureSensor* tempSensor = new TemperatureSensor("T100", "Room 101", 85);
    MotionSensor* motionSensor = new MotionSensor("M200", "Main Hallway");
    CO2COSensor* gasSensor = new CO2COSensor("C300", "Mechanical Room", 1000, 35);

    controller.addSensor(tempSensor);
    controller.addSensor(motionSensor);
    controller.addSensor(gasSensor);

    controller.runSystem();

    controller.makeReport();

    delete tempSensor;
    delete motionSensor;
    delete gasSensor;

    return 0;
}