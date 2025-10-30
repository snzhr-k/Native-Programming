
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <set>

using namespace std;

class AncientAnimalException : std::exception {
public:
    const char* what() const noexcept override final {
        return "Error: ancient animal inspection!";
    }
};

class Animal {
    protected:
        string name;


    public:
        Animal(const string &s) : name(s) {}

        const string& getName() const {
            return name;
        }

        void setName(const string& newName){
            this->name = newName;
        }

        virtual string makeSound() const {
            return "Makes a sound";
        }
};

class Cow : public Animal {
    unsigned weight;
public:
    Cow(const string& name, unsigned weight)
            : Animal(name), weight(weight) {
    }

    Cow() : Cow("Mooo", 125) {
    }

    const string &getName() const {
        return name;
    }

    unsigned int getWeight() const {
        return weight;
    }

    void setWeight(unsigned int weight) {
        Cow::weight = weight;
    }

    void print() const {
        cout << "name: " << name << ", weight: " << weight << endl;
    }

    string makeSound() const {
        return Animal::makeSound() + "Moo Moo";
    }


    bool operator<(const Cow& other) const {
        return (name < other.name) || (name == other.name && weight < other.weight);
    }

    bool operator==(const Cow& other) const {
        return name == other.name && weight == other.weight;
    }

    bool operator!=(const Cow& other) const {
        return !operator==(other);
    }

    operator unsigned() const {
        return weight;
    }


    bool operator==(unsigned val) const {
        return weight == val;
    }

};

bool operator==(unsigned val, const Cow& t){
    return t.getWeight() == val;
}

/////////////

class Sheepdog : public Animal {

public:
    Sheepdog() : Animal("Bodri"){}

    string makeSound() const {
        return Animal::makeSound() + " Woof Woof";
    }
};

////////////


/////////////
class UFO {
    vector<Cow> cowek;
public:
    const vector<Cow> &getCow() const {
        return cowek;
    }

public:
    void abduct(const Cow& t) {
        if (t.getWeight() > 60) {
            cowek.push_back(t);
        }
    }

    void abduct(const Sheepdog& t) const {
        throw runtime_error(t.getName());
    }

    UFO& operator<<(const Cow& t) {
        abduct(t);
        return *this;
    }

    void operator<<(const Sheepdog& t) const {
        abduct(t);
    }

    void operator+=(const Cow& t) {
        abduct(t);
    }

    void operator+=(const Sheepdog& t) const {
        abduct(t);
    }

    void print() const {
        cout << "Abducted " << cowek.size()  << " cow(s)"<< endl;
        for(const auto& t : cowek){
            t.print();
        }
    }

    bool less(const UFO& other) const {
        return cowek.size() < other.cowek.size();
    }

    bool operator<(const UFO& other) const {
        return cowek.size() < other.cowek.size();
    }

    static bool inspect(Animal a) {
        // if (a.makeSound() == Cow().makeSound()) {
        //     return true;
        // }
        // return false;
        return a.makeSound() == Cow().makeSound();
    }

    static bool inspectRef(const Animal& a) {
        return a.makeSound() == Cow().makeSound();
    }

};

bool less(const UFO& a, const UFO& b) {
    return a.getCow().size() < b.getCow().size();
}


int main() {
    UFO ufo;
    Cow cow1("Riska", 70);
    Cow cow2("Boci", 50);
    Cow cow3("Mucika", 100);
    Cow cow4("Uff", 99);
    Cow cow5("Boo", 99);
    Cow cow6("Buendia", 909);
    Sheepdog dog;




    return 0;
}

