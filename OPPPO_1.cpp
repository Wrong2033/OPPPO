#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <locale>
#include "OPPPO_1.h"

static void printHelp() {
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


Truck::Truck(int capacity, int power, const std::string& country)
    : payloadCapacity(capacity), enginePower(power), country(country) {}

std::string  Truck::getInfo() const  {
    return "Truck: Payload Capacity = " + std::to_string(payloadCapacity) +
        " kg, Engine Power = " + std::to_string(enginePower) +
        " HP, Country = " + country;
}

bool  Truck::matchesCondition(const std::string& parameter, const std::string& sign, int value) const  {
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

bool  Truck::matchesConditionCountry(const std::string& parameter, const std::string& sign, const std::string& value) const  {
    if (parameter == "country") {
        if (sign == "==") return country == value; // Для сравнения страны
    }
    return false;
}



Bus::Bus(int capacity, int power, const std::string& country)
    : seatingCapacity(capacity), enginePower(power), country(country) {}

std::string  Bus::getInfo() const  {
    return "Bus: Seating Capacity = " + std::to_string(seatingCapacity) +
        ", Engine Power = " + std::to_string(enginePower) +
        " HP, Country = " + country;
}

bool  Bus::matchesCondition(const std::string& parameter, const std::string& sign, int value) const  {
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
bool  Bus::matchesConditionCountry(const std::string& parameter, const std::string& sign, const std::string& value) const  {
    if (parameter == "country") {
        if (sign == "==") return country == value; // Для сравнения страны
    }
}



Car::Car(int doors, int speed, int power, const std::string& country)
    : doors(doors), maxSpeed(speed), enginePower(power), country(country) {}

std::string  Car::getInfo() const  {
    return "Car: Doors = " + std::to_string(doors) +
        ", Max Speed = " + std::to_string(maxSpeed) +
        " km/h, Engine Power = " + std::to_string(enginePower) +
        " HP, Country = " + country;
}

bool  Car::matchesCondition(const std::string& parameter, const std::string& sign, int value) const  {
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
bool  Car::matchesConditionCountry(const std::string& parameter, const std::string& sign, const std::string& value) const  {
    if (parameter == "country") {
        if (sign == "==") return country == value; // Для сравнения страны
    }
}



Container::~Container() {
    for (auto vehicle : vehicles) {
        delete vehicle;
    }
}

void Container::addVehicle(Vehicle* vehicle) {
    vehicles.push_back(vehicle);
}

void Container::removeVehicles(const std::string& condition) {
    std::istringstream iss(condition);
    std::string parameter, sign;

    if (condition.find("country") != std::string::npos) {
        std::string countryValue;
        iss >> parameter >> sign >> countryValue;
        vehicles.erase(std::remove_if(vehicles.begin(), vehicles.end(),
            [&parameter, &sign, &countryValue](Vehicle* v) { return v->matchesConditionCountry(parameter, sign, countryValue); }), vehicles.end());
        return;
    }

    int value;
    iss >> parameter >> sign >> value;
    vehicles.erase(std::remove_if(vehicles.begin(), vehicles.end(),
        [&parameter, &sign, value](Vehicle* v) { return v->matchesCondition(parameter, sign, value); }), vehicles.end());
}

void Container::print() const {
    for (const auto& vehicle : vehicles) {
        std::cout << vehicle->getInfo() << std::endl;
    }
}


static void executeCommandsFromSource(Container& container, std::istream& source, bool loadCommandExecuted) {
    std::string command;

    while (std::getline(source, command)) {
        if (command.find("ADD") == 0) {
            if (command.length() > 4) {
                std::istringstream iss(command);
                std::string temp, type;
                int param1, param2;
                std::string country;

                iss >> temp >> type >> param1 >> param2 >> country;
                if (iss.fail() || country.empty()) {
                    std::cerr << "Ошибка: Неправильный формат команды ADD. Ожидается: ADD <type> <param1> <param2> <country>" << std::endl;
                }
                else {
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
            }
            else {
                std::cerr << "Ошибка: Не указаны данные для добавления транспорта." << std::endl;
            }
        }
        else if (command.find("REM") == 0) {
            if (command.length() > 4) {
                std::string condition = command.substr(4);
                std::istringstream cmdStream(condition);
                std::string parameter, sign;
                int value;

                if (condition.find("country") != std::string::npos) {
                    std::string countryValue;
                    std::istringstream countryStream(condition);
                    countryStream >> parameter >> sign >> countryValue;
                    if (parameter == "country" && sign == "==") {
                        container.removeVehicles(condition);
                    }
                    else {
                        std::cerr << "Ошибка: Неправильный формат условия для удаления по стране." << std::endl;
                    }
                }
                else if (cmdStream >> parameter >> sign >> value) {
                    if ((parameter == "payload" || parameter == "seats" || parameter == "doors" || parameter == "power" || parameter == "max_speed") &&
                        (sign == ">" || sign == "<" || sign == "==" || sign == ">=" || sign == "<=")) {
                        container.removeVehicles(condition);
                    }
                    else {
                        std::cerr << "Ошибка: Неправильный формат условия. Ожидается: <parameter> <sign> <value>" << std::endl;
                    }
                }
                else {
                    std::cerr << "Ошибка: Не указаны или указаны неверно условия для удаления транспорта." << std::endl;
                }
            }
            else {
            std::cerr << "Ошибка: Не указаны данные для удаления транспорта." << std::endl;
            }
        }
        else if (command == "PRINT") {
            container.print();
        }
        else if (command == "HELP") {
            printHelp();
        }
        else if (command.find("LOAD") == 0) {
            if (command.length() > 5) {
                loadCommandExecuted = true;
                std::string filename = command.substr(5);
                std::ifstream file(filename);
                if (file.is_open()) {
                    executeCommandsFromSource(container, file, loadCommandExecuted);
                    file.close();
                }
                else {
                    std::cerr << "Ошибка открытия файла с командами." << std::endl;
                }
                loadCommandExecuted = false; // Установить флаг, если команда LOAD выполнена
            }
            else {
                std::cerr << "Введена неверная команда: " << command << std::endl;
            }
        }
        else {
            std::cerr << "Ошибка: Не указано название файла для загрузки." << std::endl;  
        }

        // Вывод сообщения после выполнения команды, кроме LOAD
        if (!loadCommandExecuted) {
            std::cout << "Enter commands (ADD, REM, PRINT, HELP, LOAD, EXIT): ";
        }
    }
}

int main() {
    std::setlocale(LC_ALL, "ru_RU");
    Container container;
    bool loadCommandExecuted = false;

    std::cout << "Enter commands (ADD, REM, PRINT, HELP, LOAD, EXIT): ";
    executeCommandsFromSource(container, std::cin, loadCommandExecuted);

    return 0;
}

