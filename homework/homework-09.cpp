#if defined(NDEBUG)
#undef NDEBUG
#endif // defined(NDEBUG)

#include <cassert>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Animal {
  string species;

public:
  Animal(const string& species) : species(species) { }

  virtual ~Animal() = default;

  virtual void print(ostream& os) const {
    os << "Animal: " << species << "\n";
  }

  virtual Animal* clone() const {
    return new Animal(*this);
  }
};

class Cat : public Animal {
  string name;
public:
  Cat(const string& name) : Animal("Cat"), name(name) { }

  void print(ostream& os) const override {
    os << "Cat: " << name << "\n";
  }

  Animal* clone() const override {
    return new Cat(*this);
  }
};

class Employee {
  string id;
  string name;
public:
  Employee(const string& id, const string& name) : id(id), name(name) { }

  const string& getName() const {
    return name;
  }

  const string& getId() const {
    return id;
  }

  operator string() const {
    return id + " " + name;
  }
};

struct EmployeeComp {
  bool operator()(const shared_ptr<Employee>& e1, const shared_ptr<Employee>& e2) const {
    return e1->getId() < e2->getId();
  }
};

class Shelter {
  //unique_ptr<vector<Animal*>> animals;
  vector<unique_ptr<Animal>> animals;
  set<shared_ptr<Employee>, EmployeeComp> employees;
public:

  Shelter() = default;
  //Shelter() : animals(make_unique<vector<Animal*> >()) { }

  Shelter(const Shelter& shelter) {
    for (const auto& a : shelter.animals)
      animals.emplace_back(a->clone());

    employees = shelter.employees;
  }

  Shelter& operator=(Shelter& shelter) {
    if (this == &shelter)
      return *this;

    animals.clear();
    for (auto& a : shelter.animals)
      animals.emplace_back(a->clone());

    employees = shelter.employees;
    return *this;
  }

  Shelter& add(shared_ptr<Employee> ptr) {
    employees.insert(ptr);
    return *this;
  }

  shared_ptr<Employee> getEmployee(const string& id) const {
    for (const auto& e : employees) {
      if (e->getId() == id) {
        return e;
      }
    }
    return nullptr;
  }


  void add(const Animal& animal) {
    animals.push_back(unique_ptr<Animal>(animal.clone()));
  }

  void add(unique_ptr<Animal> animal) {
    if (animal)
      animals.push_back(move(animal));
  }

  Animal* getAnimal(unsigned i) {
    if (i <= animals.size())
      return animals[i].get();
    return nullptr;
  }

  friend ostream& operator<<(ostream& os, const Shelter& s) {
    os << "Animals:\n";
    for (auto &a : s.animals)
      a->print(os);

    os << "Employees:\n";
    for (auto e : s.employees)
      os << string(*e) << endl;

    return os;
  }
};


// Ez alatt ne legyen mar feladat implementacio!
#ifndef TEST_BIRO

int main() {

  Shelter shelter;

  {
    shared_ptr<Employee> john(new Employee("id1", "John"));
    shelter.add(john);

    cout << "Shelter: add(shared_ptr<Employee>), get(const string&)" << endl;
    shared_ptr<Employee> id1 = shelter.getEmployee("id1");
    assert(id1 != nullptr);
    if (id1.get()) {
      string sId1 = *id1;
      cout << sId1 << endl;
      assert(sId1 == "id1 John");
    }
  }

  {
    cout << "Shelter: add(shared_ptr<Employee>), get(const string&)" << endl;
    shared_ptr<Employee> id_null = shelter.getEmployee("John");
    assert(id_null == nullptr);
  }

  {
    shared_ptr<Employee> tom(new Employee("id0", "Tom"));
    shared_ptr<Employee> peter(new Employee("id2", "Peter"));
    shelter.add(tom).add(peter);

    stringstream ss;
    ss << shelter;
    string s = ss.str();
    cout << endl << "Shelter add(shared_ptr<Employee>), stream operator" << endl;
    cout << s << endl;
    assert(s == "Animals:\nEmployees:\nid0 Tom\nid1 John\nid2 Peter\n");
  }

  {
    Cat cat("Tom");
    shelter.add(cat);
    cout << endl << "Shelter add(const Animal&), getAnimal(unsigned)" << endl;
    Animal* a = shelter.getAnimal(0);
    assert(a != nullptr);
    if (a) {
      stringstream ss;
      a->print(ss);
      string s = ss.str();
      cout << s << endl;
      assert(s == "Cat: Tom\n");
    }
  }

  {
    cout << endl << "Shelter add(const Animal&), getAnimal(unsigned) - nullptr check" << endl;
    Animal* a = shelter.getAnimal(1);
    assert(a == nullptr);
  }

  {
    cout << endl << "Shelter add(unique_ptr<Animal>), getAnimal(unsigned)" << endl;
    unique_ptr<Animal> garfield(new Cat("Garfield"));
    shelter.add(move(garfield));
    Animal* a = shelter.getAnimal(1);
    assert(a != nullptr);
    if (a) {
      stringstream ss;
      a->print(ss);
      string s = ss.str();
      cout << s << endl;
      assert(s == "Cat: Garfield\n");
    }
  }


  {
    cout << endl << "Shelter add(unique_ptr<Animal>), getAnimal(unsigned)" << endl;

    shelter.add(make_unique<Cat>("KitKat"));
    Animal* a = shelter.getAnimal(2);
    assert(a != nullptr);
    if (a) {
      stringstream ss;
      a->print(ss);
      string s = ss.str();
      cout << s << endl;
      assert(s == "Cat: KitKat\n");
    }
  }


  {
    cout << endl << "Shelter copy const." << endl;
    Shelter shelter_copy(shelter);
    shelter_copy.add(make_unique<Animal>("dog"));
    Animal* a = shelter.getAnimal(3);
    assert(a != nullptr);

    stringstream ss1;
    ss1 << shelter;
    string orig = ss1.str();
    stringstream ss2;
    ss2 << shelter_copy;
    string copy = ss2.str();
    assert(copy == orig + "Animal: dog\n");
  }

  {
    cout << endl << "Shelter operator=" << endl;
    Shelter shelter_copy;
    shelter_copy = shelter;
    shelter_copy.add(make_unique<Animal>("fish"));
    Animal* a = shelter.getAnimal(3);
    assert(a != nullptr);

    stringstream ss1;
    ss1 << shelter;
    string orig = ss1.str();
    stringstream ss2;
    ss2 << shelter_copy;
    string copy = ss2.str();
    assert(copy == orig + "Animal: fish\n");
  }
}

#endif
