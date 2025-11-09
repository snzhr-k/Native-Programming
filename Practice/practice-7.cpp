#include <iostream>
#include <string>

using namespace std;

class Bell {
public:
    Bell(unsigned times):timesRung(times){
        cout << "Bell (" << timesRung << ") created" << endl;
    }

    ~Bell(){
        cout << "Bell (" << timesRung << ") destroyed" << endl;
    }

    string makeSound() const {
        std::string result;
        for (unsigned i = 0; i < timesRung; ++i) {
            result += " rings";
        }
        return result;
    }

private:
    unsigned timesRung;
};

class Cow {
    string name;
    Bell* bell;

public:
    Cow(const string& str):name(str){
        cout << name << " created" << endl;
    }

    ~Cow() {
        cout << "Cow (" << name << ") destroyed" << endl;
    }

    Cow& operator= (const Cow& c) {
        if (this == &c) {
            return *this;
        }
        name = c.name;
        delete bell;
        bell = new Bell(*c.bell);
        return *this;
    }

    void setBell(const Bell& b) {
        delete bell;
        bell = new Bell(*b);
    }

    string makeSound() const {
        return "Makes sound: moo";
    }
};

int main() {
    Cow c("Daisy");
    cout << c.makeSound() << endl;
    return 0;
}
