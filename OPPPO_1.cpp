#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <locale>

void printHelp() {
    std::ifstream file("README.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла с помощью." << std::endl;
        return;
    }

    std::string line;
    std::cout << std::endl;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    std::cout << std::endl;
    file.close();
}

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
    Truck(int capacity, int power, const std::string& country)
        : payloadCapacity(capacity), enginePower(power), country(country) {}

    std::string getInfo() const override {
        return "Truck: Payload Capacity = " + std::to_string(payloadCapacity) +
            " kg, Engine Power = " + std::to_string(enginePower) +
            " HP, Country = " + country;
    }

    bool matchesCondition(const std::string& parameter, const std::string& sign, int value) const override {
        if (parameter == "payload") {
            if (sign == ">") return payloadCapacity > value;
            if (sign == "<") return payloadCapacity < value;
            if (sign == "==") return payloadCapacity == value;
            if (sign == ">=") return payloadCapacity >= value;
            if (sign == "<=") return payloadCapacity <= value;
        }
        if (parameter == "power") {
            if (sign == ">") return enginePower > value;
            if (sign == "<") return enginePower < value;
            if (sign == "==") return enginePower == value;
            if (sign == ">=") return enginePower >= value;
            if (sign == "<=") return enginePower <= value;
        }
        return false;
    }
    bool matchesConditionCountry(const std::string& parameter, const std::string& sign, const std::string& value) const override {
        if (parameter == "country") {
            if (sign == "==") return country == value; // Для сравнения страны
        }
    }
};

class Bus : public Vehicle {
private:
    int seatingCapacity;
    int enginePower;
    std::string country;

public:
    Bus(int capacity, int power, const std::string& country)
        : seatingCapacity(capacity), enginePower(power), country(country) {}

    std::string getInfo() const override {
        return "Bus: Seating Capacity = " + std::to_string(seatingCapacity) +
            ", Engine Power = " + std::to_string(enginePower) +
            " HP, Country = " + country;
    }

    bool matchesCondition(const std::string& parameter, const std::string& sign, int value) const override {
        if (parameter == "seats") {
            if (sign == ">") return seatingCapacity > value;
            if (sign == "<") return seatingCapacity < value;
            if (sign == "==") return seatingCapacity == value;
            if (sign == ">=") return seatingCapacity >= value;
            if (sign == "<=") return seatingCapacity <= value;
        }
        if (parameter == "power") {
            if (sign == ">") return enginePower > value;
            if (sign == "<") return enginePower < value;
            if (sign == "==") return enginePower == value;
            if (sign == ">=") return enginePower >= value;
            if (sign == "<=") return enginePower <= value;
        }
        
        return false;
    }
    bool matchesConditionCountry(const std::string& parameter, const std::string& sign, const std::string& value) const override {
        if (parameter == "country") {
            if (sign == "==") return country == value; // Для сравнения страны
        }
    }
};

class Car : public Vehicle {
private:
    int doors;
    int maxSpeed;
    int enginePower;
    std::string country;

public:
    Car(int doors, int speed, int power, const std::string& country)
        : doors(doors), maxSpeed(speed), enginePower(power), country(country) {}

    std::string getInfo() const override {
        return "Car: Doors = " + std::to_string(doors) +
            ", Max Speed = " + std::to_string(maxSpeed) +
            " km/h, Engine Power = " + std::to_string(enginePower) +
            " HP, Country = " + country;
    }

    bool matchesCondition(const std::string& parameter, const std::string& sign, int value) const override {
        if (parameter == "doors") {
            if (sign == ">") return doors > value;
            if (sign == "<") return doors < value;
            if (sign == "==") return doors == value;
            if (sign == ">=") return doors >= value;
            if (sign == "<=") return doors <= value;
        }
        if (parameter == "speed") {
            if (sign == ">") return maxSpeed > value;
            if (sign == "<") return maxSpeed < value;
            if (sign == "==") return maxSpeed == value;
            if (sign == ">=") return maxSpeed >= value;
            if (sign == "<=") return maxSpeed <= value;
        }
        if (parameter == "power") {
            if (sign == ">") return enginePower > value;
            if (sign == "<") return enginePower < value;
            if (sign == "==") return enginePower == value;
            if (sign == ">=") return enginePower >= value;
            if (sign == "<=") return enginePower <= value;
        }
        return false;
    }
    bool matchesConditionCountry(const std::string& parameter, const std::string& sign, const std::string& value) const override {
        if (parameter == "country") {
            if (sign == "==") return country == value; // Для сравнения страны
        }
    }
};

class Container {
private:
    std::vector<Vehicle*> vehicles;

public:
    ~Container() {
        for (auto vehicle : vehicles) {
            delete vehicle;
        }
    }

    void addVehicle(Vehicle* vehicle) {
        vehicles.push_back(vehicle);
    }

    void removeVehicles(const std::string& condition) {
        std::istringstream iss(condition);
        std::string parameter, sign;

        // Если сравниваем по стране, обработка отдельная
        if (condition.find("country") != std::string::npos) {
            std::string countryValue;
            iss >> parameter >> sign >> countryValue;
            vehicles.erase(std::remove_if(vehicles.begin(), vehicles.end(),
                [&parameter, &sign, &countryValue](Vehicle* v) { return v->matchesConditionCountry(parameter, sign, countryValue); }), vehicles.end());
            return;
        }

        // Обработка других условий
        int value;
        iss >> parameter >> sign >> value;
        vehicles.erase(std::remove_if(vehicles.begin(), vehicles.end(),
            [&parameter, &sign, value](Vehicle* v) { return v->matchesCondition(parameter, sign, value); }), vehicles.end());
    }

    void print() const {
        for (const auto& vehicle : vehicles) {
            std::cout << vehicle->getInfo() << std::endl;
        }
    }
};

void executeCommandsFromFile(const std::string& filename, Container& container) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла с командами." << std::endl;
        return;
    }

    std::string command;
    while (std::getline(file, command)) {
        if (command.find("ADD") == 0) {
            std::istringstream iss(command);
            std::string temp, type;
            int param1, param2;
            std::string country;

            iss >> temp >> type >> param1 >> param2 >> country;
            if (type == "Truck") {
                container.addVehicle(new Truck(param1, param2, country));
            }
            else if (type == "Bus") {
                container.addVehicle(new Bus(param1, param2, country));
            }
            else if (type == "Car") {
                container.addVehicle(new Car(param1, param2, 150, country)); // Стандартная мощность для машины
            }
            else {
                std::cerr << "Некорректный ввод названия транспорта или его параметров!" << std::endl;
            }
        }
        else if (command.find("REM") == 0) {
            std::string condition = command.substr(4);
            container.removeVehicles(condition);
        }
        else if (command == "PRINT") {
            container.print();
        }
        else if (command == "HELP") {
            printHelp();
        }
        else {
            std::cerr << "Введена неверная команда: " << command << std::endl;
        }
    }

    file.close();
}

int main() {

    std::setlocale(LC_ALL, "ru_RU.UTF-8");
 //   std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    Container container;

  //  container.addVehicle(new Truck(1500, 250, "USA"));
 //   container.addVehicle(new Bus(40, 300, "Germany"));
  //  container.addVehicle(new Car(4, 180, 150, "Japan"));

    std::string command;
    while (true) {
        std::cout << "Enter command (ADD, REM, PRINT, HELP, LOAD, EXIT): ";
        std::getline(std::cin, command);
        if (command.find("LOAD") == 0) {
            std::string filename = command.substr(5);
            executeCommandsFromFile(filename, container);
        }
        else if (command.find("ADD") == 0) {
            // Example commands: ADD Truck 1500 250 USA
            std::istringstream iss(command);
            std::string temp, type;
            int param1, param2;
            std::string country;

            iss >> temp >> type >> param1 >> param2 >> country;
            if (type == "Truck") {
                container.addVehicle(new Truck(param1, param2, country));
            }
            else if (type == "Bus") {
                container.addVehicle(new Bus(param1, param2, country));
            }
            else if (type == "Car") {
                container.addVehicle(new Car(param1, param2, 150, country)); // Default power for car
            }
            else {
                std::cout << "Incorrect input of the name of the transport or its parameters!" << std::endl;
            }
        }
        else if (command.find("REM") == 0) {
            // Example condition: REM payload > 1000
            std::string condition = command.substr(4);
            container.removeVehicles(condition);
        }
        else if (command == "PRINT") {
            container.print();
        }
        else if (command == "HELP") {
            printHelp();
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            std::cout << "The wrong command was entered!!!" << std::endl;
        }
    }

    return 0;
}
