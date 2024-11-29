#include "pch.h"
#include "CppUnitTest.h"
#include "OPPPO_1.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VehicleTests
{
    TEST_CLASS(VehicleTests)
    {
    public:
        TEST_METHOD(TestTruck)
        {
            Truck truck(5000, 300, "USA");
            Assert::AreEqual(std::string("Truck: Payload Capacity = 5000 kg, Engine Power = 300 HP, Country = USA"), truck.getInfo());

            Assert::IsTrue(truck.matchesCondition("payload", ">", 4000));
            Assert::IsFalse(truck.matchesCondition("power", "<", 250));
            Assert::IsTrue(truck.matchesConditionCountry("country", "==", "USA"));
        }

        TEST_METHOD(TestBus)
        {
            Bus bus(50, 200, "Germany");
            Assert::AreEqual(std::string("Bus: Seating Capacity = 50, Engine Power = 200 HP, Country = Germany"), bus.getInfo());

            Assert::IsTrue(bus.matchesCondition("seats", ">", 40));
            Assert::IsFalse(bus.matchesCondition("power", "<", 150));
            Assert::IsTrue(bus.matchesConditionCountry("country", "==", "Germany"));
        }

        TEST_METHOD(TestCar)
        {
            Car car(4, 220, 150, "Japan");
            Assert::AreEqual(std::string("Car: Doors = 4, Max Speed = 220 km/h, Engine Power = 150 HP, Country = Japan"), car.getInfo());

            Assert::IsTrue(car.matchesCondition("speed", "<", 250));
            Assert::IsFalse(car.matchesCondition("doors", "==", 5));
            Assert::IsTrue(car.matchesConditionCountry("country", "==", "Japan"));
        }

        TEST_METHOD(TestContainer)
        {
            Container container;
            Truck* truck = new Truck(5000, 300, "USA");
            Bus* bus = new Bus(50, 200, "Germany");
            Car* car = new Car(4, 220, 150, "Japan");

            container.addVehicle(truck);
            container.addVehicle(bus);
            container.addVehicle(car);

            std::ostringstream oss;
            std::streambuf* originalCout = std::cout.rdbuf(oss.rdbuf());

            container.print();

            std::cout.rdbuf(originalCout);
            Assert::IsTrue(oss.str().find("Truck: Payload Capacity = 5000 kg") != std::string::npos);
            Assert::IsTrue(oss.str().find("Bus: Seating Capacity = 50") != std::string::npos);
            Assert::IsTrue(oss.str().find("Car: Doors = 4") != std::string::npos);

            container.removeVehicles("payload > 6000"); // Should not remove anything
            std::ostringstream ossAfterRemove;
            std::cout.rdbuf(ossAfterRemove.rdbuf());
            container.print();
            Assert::IsTrue(ossAfterRemove.str().find("Truck: Payload Capacity = 5000 kg") != std::string::npos); // Still should be there

            container.removeVehicles("seats < 60"); // Should remove bus
            std::ostringstream ossAfterBusRemove;
            std::cout.rdbuf(ossAfterBusRemove.rdbuf());
            container.print();
            Assert::IsTrue(ossAfterBusRemove.str().find("Bus: Seating Capacity = 50") == std::string::npos); // Bus should be removed

            container.removeVehicles("country == Japan");
            Assert::IsTrue(ossAfterBusRemove.str().find("Car: Doors = 4") != std::string::npos); // Car should still be there

            // Cleanup
            container.~Container(); // Manually destroy the container to delete vehicles.
        }
    };
}

