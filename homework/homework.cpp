import <string>;
import <iostream>;

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

    string getName() const {
        return this->name;}

    unsigned getWeight() const {
          return this->weight;}

    bool drink(unsigned amount) {
        if (this->getWeight() < amount) {return false;}
        this->weight -= amount;
        return true;
    }
};
