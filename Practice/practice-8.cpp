#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Bell {

    Bell(unsigned times) : times(times) {
        cout << "Bell (" << times << ") created" << endl;
    }

    ~Bell() {
        cout << "Bell (" << times << ") destroyed" << endl;
    }

    string makeSound() const {
        std::string result;
        for (unsigned i = 0; i < times; ++i) {
            result += " clang";
        }
        return result;
    }

private:
    unsigned times;
};

class Animal {
    string name;

public:
    Animal(const string& name) : name(name) {
        cout << name << " created" << endl;
    }

    virtual ~Animal() {
        cout << "Animal destroyed (" << name << ")" << endl;
    }

    virtual string makeSound() const {
        return "Makes sound:";
    }

    const string& getName() const {
        return name;
    }

    virtual Animal* clone(const Animal& a) {
        return new Animal(a);
    }
};



class Cow : public Animal {
    Bell* bell;
public:
    Cow(const string& str, unsigned ringCount)
        : Animal(str), bell(ringCount > 0 ? new Bell(ringCount) : nullptr) {
    }

    ~Cow() {
        cout << "Cow destroyed (" << getName() << ")" << endl;
        delete bell;
    }

    string makeSound() const override {
        string result = Animal::makeSound() + " mooo";
        if (bell) {
            result += bell->makeSound();
        }
        return result;
    }
};

class Carp : public Animal {
public:
    Carp() : Animal("Nemo") {
    }

    string makeSound() const override {
        return Animal::makeSound() + " blub-blub";
    }
};

class Saucer {
    vector<Animal*> animals;

public:
    Saucer (const Saucer& s) {
        for (Animal* a : s.animals) {
            animals.push_back(a.clone());
        }
    }

    void abduct(Animal* a) {
        animals.push_back(a);
    }

    void listen() const {
        for (const Animal* a : animals)
            cout << a->makeSound() << endl;
    }
};


int main() {
    Saucer s;
    Carp c;
    Animal* a = new Cow("Mary", 5);

    s.abduct(a);
    s.abduct(&c);

    delete a;

    return 0;
}
