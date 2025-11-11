#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <cassert>
#include <sstream>

struct Traveller{
    std::string nev;
    unsigned tomeg;

    operator std::string() const{
        return nev + " " + std::to_string(tomeg);
    }

};


//WORK HERE!
using namespace std;
    class StargateException: public std::exception {
        string message;
        string fullMessage;

        public:
        StargateException(const string& msg):message(msg), fullMessage("Stargate error: " + msg){}

        const char* what() const noexcept override final {
            return fullMessage.c_str();
        }
    };

    class Port{
        const string address;
        bool activation_status = false;


        public:
        Port(const string& addrs):address(addrs){}

        const string& getAddress() const {return this->address;}

        virtual void operator! () {this->activation_status = !this->activation_status;}

        bool isActivated () const {return activation_status;}

        virtual string enter(const Traveller& p) {
            if (activation_status){return "Travel:" + string(p) + " Destination:" + getAddress();}
            throw std::runtime_error("inactive port");
        }
    };

class StargatePort : public Port{
    unsigned int load_capacity;

public:
    StargatePort(const string& adrs, unsigned int cp) : Port(adrs), load_capacity(cp){}

    void setCapacity(const unsigned int cp){this->load_capacity = cp;}
    unsigned int getCapacity() const {return this->load_capacity;}

    void operator!() override {
        if (load_capacity != 0) {
            Port::operator!();
        }
    }

    virtual string enter(const Traveller& p) override {
        if (!isActivated()) {throw std::runtime_error("inactive port");}
        if (p.tomeg > load_capacity){throw StargateException("over the capacity ");}

        load_capacity -= p.tomeg;
        return Port::enter(p);
    }
};

unsigned travelOrganization(const vector<Traveller>& passengers, Port& port, ostream& os) {
    unsigned int failed_count = 0;


    for (const Traveller& passenger : passengers ) {
        try {
            os << port.enter(passenger)<< '\n';
        }catch (const exception& e ){++failed_count;}
    }


    return failed_count;
}

//DO NOT WRITE ANY CODE BELOW THIS LINE
#ifndef TEST_BIRO

int main() {

    {
        const Port p("Some port");
        std::string address = p.getAddress();
        bool activated = p.isActivated();
        assert(!activated);
        assert(address == "Some port");

    }

    {
        Port p("Some port");
        bool activated = p.isActivated();
        assert(!activated);
        !p;
        activated = p.isActivated();
        assert(activated);
    }

    {
        Port p("Some port");
        !p;
        bool activated = p.isActivated();
        assert(activated);
        Traveller u{"Carlos", 100};
        std::string result = p.enter(u);
        assert(result == "Travel:Carlos 100 Destination:Some port");
    }

    {
        Port p("Some port");
        bool activated = p.isActivated();
        assert(!activated);
        Traveller u{"Carlos", 100};
        try{
            p.enter(u);
            assert(false);
        }catch(std::runtime_error&){
            assert(true);
        }
    }

    {
        StargatePort csp("Abydos01", 300);
        unsigned tomeg = csp.getCapacity();
        assert(tomeg == 300);
        csp.setCapacity(0);
        tomeg = csp.getCapacity();
        assert(tomeg == 0);
    }

    {
        StargatePort csp("Abydos01", 0);
        !csp;
        bool activated = csp.isActivated();
        assert(!activated);
    }

    {
        StargatePort csp("Abydos01", 100);
        !csp;
        Traveller u{"Carlos", 200};
        try{
            csp.enter(u);
            assert(false);
        }catch(const StargateException& csk){
            std::string result = csk.what();
            assert(result == "Stargate error: over the capacity");
            assert(csp.getCapacity() == 100);
        }
    }

    {
        StargatePort csp("Abydos01", 500);
        !csp;
        Traveller u{"Carlos", 200};
        std::string result = csp.enter(u);
        assert(result == "Travel:Carlos 200 Destination:Abydos01");
        assert(csp.getCapacity() == 300);
    }


    {
        StargatePort csp("Abydos01", 300);
        const std::vector<Traveller> passengerok = {{"Peter", 200}, {"Donald", 2}, {"Julia", 100}};
        std::ostringstream oss1;
        unsigned res = travelOrganization(passengerok, csp, oss1);
        std::string result1 = oss1.str();
        assert(result1 == "");
        assert(res == 3);

        !csp;
        std::ostringstream oss2;
        res = travelOrganization(passengerok, csp, oss2);
        std::string result2 = oss2.str();
        assert(result2 == "Travel:Peter 200 Destination:Abydos01\nTravel:Donald 2 Destination:Abydos01\n");
        assert(res == 1);
    }

    return 0;
}


#endif