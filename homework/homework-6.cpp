#include <cassert>
#include <iostream>
#include <string>

// WORK HERE!
class IlluminatedOrnament {
  unsigned int brightness;
  bool is_turned;

public:
  IlluminatedOrnament(unsigned int brightness, bool is_turned):brightness(brightness), is_turned(is_turned){}
  IlluminatedOrnament() : brightness(0), is_turned(false){}

  bool isTurnedOn() const {return is_turned;}
  unsigned int getBrightness() const {return isTurnedOn() ? brightness : 0;}

  IlluminatedOrnament& operator++() {
    is_turned = true;
    return *this;
  }
  IlluminatedOrnament& operator--() {
    is_turned = true;
    return *this;
  }
};

class SmallChristmasTree {
  std::string type;
  IlluminatedOrnament* top_ornament = nullptr;

public:
  SmallChristmasTree(const std::string& type) : type(type) {}
  SmallChristmasTree(const std::string& type, IlluminatedOrnament* top_ornament) : type(type), top_ornament(top_ornament){}
  SmallChristmasTree() : type("pine") {}

  const std::string& getTreeType() const {return this->type;}
  IlluminatedOrnament* getTopOrnament() const {return top_ornament ? nullptr : top_ornamen;}

  ornamentPlacement(IlluminatedOrnament& ornament) {
    //make a copy of the ornament, and not refer to the given ornament
    //the principle is the one who creates a dynamic object is responsible for cleaning him out of memor in the end
  }

};
//DO NOT WRITE ANY CODE BELOW THIS LINE
#ifndef TEST_BIRO
#define LINE_INFO "Line: " << __LINE__ << ": "

int main() {
  {
    std::cout << "# IlluminatedOrnament - default" << std::endl;

    const IlluminatedOrnament vd;
    const unsigned brightness = vd.getBrightness();
    const bool turnedOn = vd.isTurnedOn();

    std::cout << LINE_INFO << "brightness: " << brightness << std::endl;
    std::cout << LINE_INFO << "turnedOn: " << turnedOn << std::endl;
    assert(brightness == 0);
    assert(!turnedOn);
    std::cout << std::endl;
  }

  {
    std::cout << "# IlluminatedOrnament - brightness arg." << std::endl;

    const IlluminatedOrnament vd2(50);
    const unsigned brightness = vd2.getBrightness();
    const bool turnedOn = vd2.isTurnedOn();

    std::cout << LINE_INFO << "brightness: " << brightness << std::endl;
    std::cout << LINE_INFO << "turnedOn: " << turnedOn << std::endl;
    assert(brightness == 0);
    assert(!turnedOn);
    std::cout << std::endl;
  }

  {
    std::cout << "# IlluminatedOrnament - turning (++/--)" << std::endl;

    IlluminatedOrnament vd(20);
    IlluminatedOrnament& ref = ++vd;
    (void)ref;
    {
      std::cout << LINE_INFO << "after ++" << std::endl;
      const unsigned brightness = vd.getBrightness();
      const bool turnedOn = vd.isTurnedOn();

      std::cout << LINE_INFO << "brightness: " << brightness << std::endl;
      std::cout << LINE_INFO << "turnedOn: " << turnedOn << std::endl;
      assert(brightness == 20);
      assert(turnedOn);
    }

    IlluminatedOrnament& ref2 = --vd;
    (void)ref2;
    {
      std::cout << "after --" << std::endl;
      const unsigned brightness = vd.getBrightness();
      const bool turnedOn = vd.isTurnedOn();

      std::cout << LINE_INFO << "brightness: " << brightness << std::endl;
      std::cout << LINE_INFO << "turnedOn: " << turnedOn << std::endl;
      assert(brightness == 0);
      assert(!turnedOn);
    }
    std::cout << std::endl;
  }

  {
    std::cout << "# SmallChristmasTree - default" << std::endl;

    SmallChristmasTree tree;
    const std::string tipus = tree.getTreeType();
    const IlluminatedOrnament* ornament = tree.getTopOrnament();

    std::cout << LINE_INFO << "type: " << tipus << std::endl;
    std::cout << LINE_INFO << "ornament: " << ornament << std::endl;
    assert(tipus == "pine");
    assert(ornament == nullptr);
    std::cout << std::endl;
  }

  {
    std::cout << "# SmallChristmasTree - type arg." << std::endl;

    SmallChristmasTree tree2("cedrus");
    const std::string tipus = tree2.getTreeType();
    const IlluminatedOrnament* ornament = tree2.getTopOrnament();

    std::cout << LINE_INFO << "type: " << tipus << std::endl;
    std::cout << LINE_INFO << "ornament: " << ornament << std::endl;
    assert(tipus == "cedrus");
    assert(ornament == nullptr);
    std::cout << std::endl;
  }

  {
    std::cout << "# SmallChristmasTree - ornament placement" << std::endl;

    SmallChristmasTree tree;
    {
      {
        const IlluminatedOrnament vd;
        tree.ornamentPlacement(vd);
      }

      const IlluminatedOrnament* ornament = tree.getTopOrnament();
      std::cout << LINE_INFO << "ornament: " << ornament << std::endl;
      assert(ornament != nullptr);

      const unsigned brightness = ornament->getBrightness();
      std::cout << LINE_INFO << "brightness: " << brightness << std::endl;
      assert(brightness == 0);
    }
    {
      {
        IlluminatedOrnament vd2(20);
        ++vd2;
        tree.ornamentPlacement(vd2);
      }

      const IlluminatedOrnament* ornament = tree.getTopOrnament();
      std::cout << LINE_INFO << "ornament: " << ornament << std::endl;
      assert(ornament != nullptr);

      const unsigned brightness = ornament->getBrightness();
      std::cout << LINE_INFO << "brightness: " << brightness << std::endl;
      assert(brightness == 20);
    }
    std::cout << std::endl;
  }

  {
    std::cout << "# SmallChristmasTree - turnOn/turnOff" << std::endl;
    SmallChristmasTree tree;
    const IlluminatedOrnament vd2(20);

    tree.ornamentPlacement(vd2);
    tree.turnOn();
    {
      std::cout << "after turnOn()" << std::endl;
      const IlluminatedOrnament* ornament = tree.getTopOrnament();
      std::cout << LINE_INFO << "ornament: " << ornament << std::endl;
      assert(ornament != nullptr);

      const bool turnedOn = ornament->isTurnedOn();
      std::cout << LINE_INFO << "turnedOn: " << turnedOn << std::endl;
      assert(turnedOn == true);
    }

    tree.turnOff();
    {
      std::cout << "after turnOff()" << std::endl;
      const IlluminatedOrnament* ornament = tree.getTopOrnament();
      std::cout << LINE_INFO << "ornament: " << ornament << std::endl;
      assert(ornament != nullptr);

      const bool turnedOn = ornament->isTurnedOn();
      std::cout << LINE_INFO << "turnedOn: " << turnedOn << std::endl;
      assert(turnedOn == false);
    }
    std::cout << std::endl;
  }

 {
    std::cout << "# SmallChristmasTree - getBrightness" << std::endl;

    SmallChristmasTree tree;

    std::cout << "before putting on the ornament" << std::endl;
    {
      const unsigned brightness = tree.getBrightness();
      std::cout << LINE_INFO << "brightness: " << brightness << std::endl;
      assert(brightness == 0);
    }

    {
      IlluminatedOrnament vd2(20);
      ++vd2; //turnOn
      tree.ornamentPlacement(vd2);
    }

    std::cout << "after putting on the ornament" << std::endl;
    {
      const unsigned brightness = tree.getBrightness();
      std::cout << LINE_INFO << "brightness: " << brightness << std::endl;
      assert(brightness == 20);
    }
  }

  return 0;
}

#endif
