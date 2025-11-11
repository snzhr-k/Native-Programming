#include <iostream>
#include <string>

#ifndef TRACK_INFO
#define TRACK_INFO
#endif

using namespace std;

class Directory;

class FSElement {
protected:
    string name;
    Directory *parent;

    FSElement(const string& name, Directory* parent) :
      name(name), parent(parent) { }

public:
    const string& getName() const {
        return name;
    }

    const Directory* getParent() const noexcept {
        return parent;
    }

    string getFullPath() const;
};
// WORK HERE!

class File : protected FSElement {
    string content = "";
public:
    File(const string& name, Directory* parent) : FSElement(name, parent) { }
    File(const string& name, Directory* parent, const string& content) : FSElement(name, parent), content(content){}

    string& getContent() const {
        return this->content;
    }

    void setContent(const string& content) {
        this->content = content;
    }

    void rm() override {
        if (!parent){}
    }

};

class Directory {
    set<>
};


// DO NOT WRITE ANY CODE BELOW THIS LINE
#ifndef TEST_BIRO

int main() {
    Directory& root = Directory::getRoot();
    Directory& k2 = root / "first" / "second";
    Directory& k4 = k2 / "third" / "fourth";
    root / "first 2";
    root / "first 3";

    k2 % "readme.txt";
    k4 % "exercise.cpp";
    k4 / "fifth";

    std::cout << "Full path" << std::endl;
    std::cout << k2.getFullPath() << std::endl;
    std::cout << root.getFullPath() << std::endl;

    std::cout << std::endl << "ls I." << std::endl;
    k2.ls(std::cout);

    std::cout << std::endl << "ls I." << std::endl;
    root.ls(std::cout);

    std::cout << std::endl << "operator >>" << std::endl;
    Directory& second = root >> "first" >> "second";
    std::cout << second.getName() << std::endl;

    std::cout << std::endl << "cp" << std::endl;
    root.cp(k2);
    root.ls(std::cout);

    std::cout << endl << "rm I." << std::endl;
    (root >> "second").rm();
    root.ls(std::cout);

    std::cout << endl << "rm II." << std::endl;
    root.rm();
    root.ls(std::cout);

    return 0;
}
#endif
