#include <cassert>
#include <iostream>
#include <string>

// WORK HERE!!!

using namespace std;

class Coffee {
    private:
    string name;
    unsigned int weight;

public:

    Coffee(const string &name, unsigned weight) {
        this->name = name;
        this->weight = weight;
    }
    Coffee(const string &name) : Coffee(name, 25){}
    Coffee() : Coffee("empty", 0){}

    const string& getName() const {
        return this->name;
    }

    string fullInfo() const{
        return "Coffee<" + this->name + ", " + to_string(weight) + ">";
    }

    unsigned getWeight() const {
          return this->weight;}

    bool drink(unsigned int amount) {
        if (this->getWeight() < amount) {return false;}
        this->weight -= amount;
        return true;
    }
};

class CoffeeFactory {
private:
    const string brand;
    const unsigned int weight;
    unsigned serial;

public:
    CoffeeFactory(const string &brand, unsigned weight) : brand(brand), weight(weight), serial(1){}
    CoffeeFactory(const string &brand) : brand(brand), weight(25), serial(1) {}

    Coffee package() {
        Coffee newCoffeePkg = Coffee(this->brand + " " + to_string(this->serial), this->weight);
        ++this->serial;
        return newCoffeePkg;
    }
};

class CoffeeStorage {
private:
    Coffee storage[3];

public:
    CoffeeStorage() {
        for (auto & i : storage) {
            i = Coffee();
        }
    }

    Coffee& getByIdx(const unsigned index) {
        return storage[index];
    }

    bool drink(unsigned index, unsigned amount) {
        if (index >= 3) {return false;}
        return getByIdx(index).drink(amount);
    }
};

#ifndef TEST_BIRO
#define LINE_INFO std::endl << "Line: " << __LINE__ << std::endl

int main() {
  std::cout << "# Simple tests" << std::endl;
  {
    std::cout << std::endl << "## Coffee" << std::endl;

    Coffee newCoffee("Nativ", 33);

    const std::string& name = newCoffee.getName();
    std::cout << "name: " << name << std::endl;
    assert(name == "Nativ");

    const unsigned weight = newCoffee.getWeight();
    std::cout << "weight: " << weight << std::endl;
    assert(weight == 33);

    const std::string info = newCoffee.fullInfo();
    std::cout << "info: " << info << std::endl;
    assert(info == "Coffee<Nativ, 33>");

    const bool firstDrink = newCoffee.drink(10);
    std::cout << "firstDrink: " << firstDrink << std::endl;
    assert(firstDrink == true);

    const bool secondDrink = newCoffee.drink(40);
    std::cout << "secondDrink: " << secondDrink << std::endl;
    assert(secondDrink == false);
  }

  {
    std::cout << std::endl << "## CoffeeFactory" << std::endl;
    CoffeeFactory factory("Magic", 11);

    Coffee kv1 = factory.package();
    const std::string info1 = kv1.fullInfo();
    std::cout << "info1: " << info1 << std::endl;
    assert(info1 == "Coffee<Magic 1, 11>");

    Coffee kv2 = factory.package();
    const std::string info2 = kv2.fullInfo();
    std::cout << "info2: " << info2 << std::endl;
    assert(info2 == "Coffee<Magic 2, 11>");
  }

  {
    std::cout << std::endl << "## CoffeeStorage" << std::endl;
    CoffeeStorage store;

    Coffee& empty0 = store.getByIdx(0);
    const std::string info0 = empty0.fullInfo();
    std::cout << "info0: " << info0 << std::endl;
    assert(info0 == "Coffee<empty, 0>");

    {
      Coffee newCoffee("HomeMade", 30);
      store.getByIdx(1) = newCoffee;
    }

    Coffee& storedCoffee = store.getByIdx(1);
    const std::string info1 = storedCoffee.fullInfo();
    std::cout << "info1: " << info1 << std::endl;
    assert(info1 == "Coffee<HomeMade, 30>");

    const bool invalidDrink = store.drink(30, 1);
    std::cout << "invalidDrink: " << invalidDrink << std::endl;
    assert(invalidDrink == false);

    const std::string infoAfterFailedDrink = storedCoffee.fullInfo();
    std::cout << "infoAfterFailedDrink: " << infoAfterFailedDrink << std::endl;
    assert(infoAfterFailedDrink == "Coffee<HomeMade, 30>");

    const bool firstDrink = store.drink(1, 10);
    std::cout << "firstDrink: " << firstDrink << std::endl;
    assert(firstDrink == true);

    const std::string infoAfterSuccessDrink = storedCoffee.fullInfo();
    std::cout << "infoAfterSuccessDrink: " << infoAfterSuccessDrink << std::endl;
    assert(infoAfterSuccessDrink == "Coffee<HomeMade, 20>");
  }
  return 0;
}
#endif // TEST_BIRO
