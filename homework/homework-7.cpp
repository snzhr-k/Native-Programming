#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <set>
#include <vector>

#ifndef TRACK_INFO
#define TRACK_INFO
#endif


using namespace std;

class Directory;

class FSElement {
protected:
    Directory* parent;
    string name;

public:
    FSElement(Directory* parent, const string& name) : parent(parent), name(name) {}
    virtual ~FSElement() = default; //compiler generates default destructor

    Directory* getParent() const {return parent;}
    const string& getName() const {return name;}

    string getFullPath();

    class Comparison {
    public:
        bool operator()(const FSElement* f1, const FSElement* f2) const {
            return f1->name < f2->name;
        }
    };

    virtual void rm () = 0; //pure abstract method :: to be implemented in child classes
    virtual void ls(std::ostream&, unsigned int) const = 0;


};

class File : public FSElement {
protected:
    string content;

public:
    File(const string& name, Directory* parent, const string& content = "") :
        FSElement(parent, name), content(content) {}

    void setContent(const string& content){this->content = content;}
    const string& getContent() const {return content;}

    void ls(std::ostream& os, unsigned int depth = 0) const override {
        string ident(depth * 2, ' ');
        os << ident << getName() << " (file)\n";
    }

    void rm() override;
};

class Directory : public FSElement {
    set<FSElement*, FSElement::Comparison> elements;
    static Directory root;

    Directory(Directory& dir) = delete; //COMPLETELY deleting the option for copy constructor :)
public:
    Directory(const string& name, Directory* parent) : FSElement(parent, name) {}

    static Directory* getRootPtr(){return &root;};
    static Directory& getRoot(){return root;};

    Directory& operator / (const string& dir_name) {
        /*creates a new directory inside current directory*/
        //throw exception for an existing dir
        for (FSElement* element : elements)
            {if (element->getName() == dir_name) throw std::exception(); }

        Directory* new_dir = new Directory(dir_name, this);
        elements.insert(new_dir);
        return *new_dir;
    }

    File& operator% (const string& dir_name) {
        /*creates a new empty file inside current directory*/
        for (FSElement* element : elements) //throw exception if there already exists a file with this name
            {if (element->getName() == dir_name) throw std::exception(); }

        auto new_file = new File(dir_name, this);
        elements.insert(new_file);
        return *new_file;
    }

    Directory& operator >> (const string& dir_name) {
        /*allows traverse along directories*/
        Directory* root = getRootPtr();
        if (dir_name == "..") return (this == root) ? *root : *this->getParent(); //go to parent dir

            /*traverse through the elements of the current directory and find such dir_name*/
            for (FSElement * element : elements) {
                if (element->getName() == dir_name){
                    if (auto* d = dynamic_cast<Directory*>(element)) return *d;
                    //throw std::exception(); //not a dir
                }
            }
            throw std::exception(); //dir not found

    }

    void ls(std::ostream& os, unsigned int depth = 0) const override{
        /*lists elements recursively*/
        string indent(depth*2, ' ');
        os << indent << getName() << '\n';

        for (FSElement* element : elements) {
            if (auto* d = dynamic_cast<Directory*>(element)) {
                d->ls(os, depth+1);
            }
            else if (auto* f = dynamic_cast<File*>(element)) {
                f->ls(os, depth+1);
            }
        }
    }

    void cp(FSElement& element) {
        /*recursive copying of element, given file/directory is copied into current directory*/

        //if (element.getName() == this->getName()) {throw std::exception();}

        if (auto* file = dynamic_cast<File*>(&element)) {
            File* new_file = new File(file->getName(), this, file->getContent());
            elements.insert(new_file);
            return;
        }

        if (auto* dir = dynamic_cast<Directory*>(&element)) {
            Directory* new_dir = new Directory(dir->getName(), this);
            elements.insert(new_dir);

            for (FSElement* child : dir->elements) {
                new_dir->cp(*child);
            }

        }
    }

    void detach(FSElement* element) {elements.erase(element);}

    void rm() override {
        vector<FSElement*> snapshot(elements.begin(), elements.end());
        for (FSElement* e : snapshot) {
            e->rm(); //each child will detach itself from the set and delete itself after
        }

        if (this == getRootPtr()){return;}

        //detach this directory
        if (auto* p = getParent()) {p->detach(this);}
        delete this;
    }
};

void File::rm() {
    Directory* parent = getParent();
    if (parent){parent->detach(this);}
    delete this;
}

//SINGLETONES
Directory Directory::root("/", nullptr);

//
string FSElement::getFullPath() {
    if (this == Directory::getRootPtr()) return "/";

    std::vector<std::string> parts;
    const FSElement* cur = this;
    while (cur && cur != Directory::getRootPtr()) {
        parts.push_back(cur->getName());
        cur = cur->getParent();
    }
    std::string path = "/";
    for (auto it = parts.rbegin(); it != parts.rend(); ++it) {
        if (it != parts.rbegin()) path += "/";
        path += *it;
    }
    return path;
}



// DO NOT WRITE ANY CODE BELOW THIS LINE
#ifndef TEST_BIRO

int main() {
    Directory& root = Directory::getRoot();
    cout << "ROOT LS:" << endl;
    root.ls(std::cout);

    cout << "ADDED SUBDIRECTOIES:" << endl;
    root / "foldier 1" / "subfoldier 1";
    root / "foldier 2";


    root.ls(std::cout);
    // Directory& k2 = root / "first" / "second";
    // Directory& k4 = k2 / "third" / "fourth";
    // root / "first 2";
    // root / "first 3";
    //
    // k2 % "readme.txt";
    // k4 % "exercise.cpp";
    // k4 / "fifth";
    //
    // std::cout << "Full path" << std::endl;
    // std::cout << k2.getFullPath() << std::endl;
    // std::cout << root.getFullPath() << std::endl;
    //
    // std::cout << std::endl << "ls I." << std::endl;
    // k2.ls(std::cout);
    //
    // std::cout << std::endl << "ls I." << std::endl;
    // root.ls(std::cout);
    //
    // std::cout << std::endl << "operator >>" << std::endl;
    // Directory& second = root >> "first" >> "second";
    // std::cout << second.getName() << std::endl;
    //
    // std::cout << std::endl << "cp" << std::endl;
    // root.cp(k2);
    // root.ls(std::cout);
    //
    // std::cout << endl << "rm I." << std::endl;
    // (root >> "second").rm();
    // root.ls(std::cout);
    //
    // std::cout << endl << "rm II." << std::endl;
    // root.rm();
    // root.ls(std::cout);

    return 0;
}
#endif