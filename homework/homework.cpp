#include <string>
#include <iostream>

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
        return "Coffee<" + this->name + " , " + to_string(weight) + ">";
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
    string brand;
    unsigned weight;
    unsigned serial;

public:
    CoffeeFactory(const string &brand, unsigned weight) {
        this->brand = brand;
        this->weight = weight;
        this->serial = 0;
    }
    CoffeeFactory(const string &brand) : CoffeeFactory(brand, 25) {}

    Coffee package() {
        Coffee newCoffeePkg = Coffee(this->brand + " " + to_string(this->serial), this->weight);
        this->serial++;
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