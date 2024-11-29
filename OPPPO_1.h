#ifndef VEHICLES_H
#define VEHICLES_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Vehicle {
public:
    virtual std::string getInfo() const = 0;
    virtual bool matchesCondition(const std::string& parameter, const std::string& sign, int value) const = 0;
    virtual bool matchesConditionCountry(const std::string& parameter, const std::string& sign, const std::string& value) const = 0;
    virtual ~Vehicle() = default;
};

class Truck : public Vehicle {
private:
    int payloadCapacity;
    int enginePower;
    std::string country;

public:
    Truck(int capacity, int power, const std::string& country);
    std::string getInfo() const override;
    bool matchesCondition(const std::string& parameter, const std::string& sign, int value) const override;
    bool matchesConditionCountry(const std::string& parameter, const std::string& sign, const std::string& value) const override;
};

class Bus : public Vehicle {
private:
    int seatingCapacity;
    int enginePower;
    std::string country;

public:
    Bus(int capacity, int power, const std::string& country);
    std::string getInfo() const override;
    bool matchesCondition(const std::string& parameter, const std::string& sign, int value) const override;
    bool matchesConditionCountry(const std::string& parameter, const std::string& sign, const std::string& value) const override;
};

class Car : public Vehicle {
private:
    int doors;
    int maxSpeed;
    int enginePower;
    std::string country;

public:
    Car(int doors, int speed, int power, const std::string& country);
    std::string getInfo() const override;
    bool matchesCondition(const std::string& parameter, const std::string& sign, int value) const override;
    bool matchesConditionCountry(const std::string& parameter, const std::string& sign, const std::string& value) const override;
};

class Container {
private:
    std::vector<Vehicle*> vehicles;

public:
    ~Container();
    void addVehicle(Vehicle* vehicle);
    void removeVehicles(const std::string& condition);
    void print() const;
};

void printHelp();
void executeCommandsFromSource(Container& container, std::istream& source, bool loadCommandExecuted);

#endif // VEHICLES_H
