#include <iostream>
#include <string>
#include <algorithm>
#include <set>


using namespace std;

class Directory;

class FSElement {
    Directory* parent;
    string name;

public:
    FSElement(Directory* parent, string name) : parent(parent), name(name) {}
    virtual ~FSElement() = default;

    Directory* getParent() const {return parent;}
    const string& getName() const {return name;}

    string getFullPath() {
        //returns the full path of the given element, separated by the "/" character
    }

    class Comparison {
    public:
        bool operator()(const FSElement* f1, const FSElement* f2) const {
            return f1->name < f2->name;
        }
    };

    virtual void rm () = 0;

};

class File : public FSElement {
    string content;

public:
    File(const string& name, Directory* parent, const string& content = "") :
        FSElement(parent, name), content(content) {}

    void setContent(const string& content){this->content = content;}
    const string& getContent() const {return content;}

    void rm() override {

    }

};

class Directory : public FSElement {
    set<FSElement*, FSElement::Comparison> elements;
    static Directory* root;

public:
    static Directory* getRootPtr() {}
    static Directory& getRoot() {}

    operator/(){}

    operator& () {}

    operator >> () {}

    void ls(std::ostream& os) const {}

    void cp(FSElement* element) const {}

    void rm() override {}

};