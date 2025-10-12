#include <cassert>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <stdexcept>
#include <vector>

// WORK HERE!

using namespace std;
class Score {
private:
    string name;
    unsigned int score;

public:
    Score(const string& name, const unsigned int score) : name(name), score(score) {}

    const string& getName() const {return this->name;}
    const unsigned int getScore() const {return this->score;}

    //string operator= (const string& name) const {return "Score(" + name + ";" + to_string(score) + ")";}
    explicit operator string () {
        return "Score(" + name + ";" + to_string(score) + ")";
    }
};

class Test {
    string name;
    const unsigned int maxScore;
    vector<Score> scores;

public:
    Test(const string& name, const unsigned int maxScore) : name(name), maxScore(maxScore) {}

    const string& getName() const {return this->name;}
    Score insert(const string& name, const unsigned int score) {
        if (score > maxScore) {
            Score newScore = Score(name, maxScore);
            scores.push_back(newScore);
            return newScore;
        }
        Score newScore = Score(name, score);
        scores.push_back(newScore);
        return newScore;
    }
    unsigned int count() const {return scores.size();}
    Score& operator [] (const unsigned int idx) {
        if (idx >= scores.size()) {throw out_of_range("incorrect index");}
        return scores[idx];
    }
    const Score& operator [] (const unsigned int idx) const {
        if (idx >= scores.size()) {throw out_of_range("incorrect index");}
        return scores[idx];
    }

    unsigned int best() const {
        unsigned int currentScore = 0;
        for (int i = 0; i < scores.size(); i++) {
            if (scores[i].getScore() > currentScore) {currentScore = scores[i].getScore();}
        }
        return currentScore;
    }

    friend ostream& operator<< (ostream& os, const Test& test) {
        string listOfScores;
        for (int i = 0; i < test.count(); i++) {
            auto var = test[i].getName();
            listOfScores += var + ",\n";
        }

        os << "Test(" <<test.getName() << ")[\n" << listOfScores << "]";
        return os;
    }

    bool operator < (const Test& other) const {
        return name < other.name;
    }

};



class Course {
    string name;
    map<string, Test> tests;

public:
    Course(const string& name) : name(name) {}

    const string& getName() const {
        return this->name;
    }

    friend const Course& operator<< (Course& course, const Test& test) {
        string testName = test.getName();
        if (course.tests.contains(testName)) { throw invalid_argument("already exists");}
        course.tests.insert({testName, test});
        return course;
    }

    unsigned int count() const {
        return tests.size();
    }

    Test& operator[] (const string& testName) {
        auto it = tests.find(testName);
        if (it == tests.end()) throw std::out_of_range("incorrect key");
        return it->second;
    }

    const Test& operator[] (const string& testName) const {
        auto it = tests.find(testName);
        if (it == tests.end()) throw std::out_of_range("incorrect key");
        return it->second;
    }

    operator unsigned int() const {
        unsigned int result = 0;
        //for (auto it = tests.begin(); it != tests.end(); it++){}
        for (const auto& [n, t] : tests) {
            result += t.best();
        }
        return result;
    }

    set<string> testNames() const {
        set<string> result;
        for (const auto& [n, t] : tests) {
            result.insert(n);
        }
        return result;
    }

    Course operator+ (const Course& other) const {
        if (this->name != other.name) {throw invalid_argument("incompatible");}
        Course combined = Course(this->name);
        for (const auto& [n,t] : this->tests) {
            combined << t;
        }
        for (const auto& [n,t] : other.tests) {
            combined << t;
        }
        return combined;
    }

    Course& operator- (const string& testName) {
        if (tests.contains(testName)) {
            tests.erase(testName);
            return *this;
        }
    }
};

#ifndef TEST_BIRO
// DO NOT WORK HERE!

int main() {
    std::cout << "# Score" << std::endl;
    {
        const unsigned score = 10;
        Score value("Test 1", score);

        const std::string& returnedName = value.getName();
        const unsigned returnedScore = value.getScore();
        std::cout << "Name=" << returnedName << " score=" << returnedScore << std::endl;
        assert(returnedName == "Test 1");
        assert(returnedScore == 10);

        const std::string converted = (std::string)value;
        std::cout << "Converted: " << converted << std::endl;
        assert(converted == "Score(Test 1;10)");
        std::cout << std::endl;
    }

    std::cout << "# Test" << std::endl;
    {
        const std::string testName = "1. Test";
        const unsigned maxScore = 30;
        Test newTest(testName, maxScore);

        const Test& constTest = newTest;

        const std::string& returnedName = constTest.getName();
        std::cout << "Test name: " << returnedName << std::endl;
        assert(returnedName == "1. Test");

        Score scoreA = newTest("Test 1", 10);
        const std::string scoreAStr = (std::string)scoreA;
        std::cout << "scoreA: " << scoreAStr << std::endl;
        assert(scoreAStr == "Score(Test 1;10)");

        Score scoreB = newTest("Test 1", 40);
        const std::string scoreBStr = (std::string)scoreB;
        std::cout << "scoreB: " << scoreBStr << std::endl;
        assert(scoreBStr == "Score(Test 1;30)");

        const unsigned scoreCount = constTest.count();
        std::cout << "Score count: " << scoreCount << std::endl;
        assert(scoreCount == 2);

        const size_t idx = 1;
        Score& indexedB = newTest[idx];
        const std::string indexedBStr = (std::string)indexedB;
        std::cout << "indexedB: " << indexedBStr << " == scoreB: " << scoreBStr << std::endl;
        assert(indexedBStr == scoreBStr);

        try {
            newTest[100];
            std::cout << "ERROR: no exception" << std::endl;
        } catch (std::out_of_range& ex) {
            std::cout << "Exception (ok): " << ex.what() << std::endl;
        } catch (std::exception& ex) {
            std::cout << "ERROR: incorrect exception" << std::endl;
        }

        const unsigned bestScore = constTest.best();
        std::cout << "Best score: " << bestScore << std::endl;
        assert(bestScore == maxScore);

        std::cout << "Print to stream" << std::endl;
        std::cout << constTest;
        std::cout << std::endl;
    }

    std::cout << "# Course" << std::endl;

    Course newCourse("NativProg");
    const Course& constCourse = newCourse;
    {
        // test data
        Test test1("1. Test", 30);
        {
            test1("Test1", 10);
            test1("Test2", 20);
        }
        Test test2("2. Test", 40);
        {
            test2("Test1", 30);
            test2("Test2", 10);
        }
        Test test3("3. Test", 30);
        {
            test3("Test1", 40);
        }

        // use test data
        newCourse << test1;
        newCourse << test2 << test3;

        try {
            newCourse << test1;
            std::cout << "ERROR: no exception" << std::endl;
            assert(false);
        } catch (std::invalid_argument& ex) {
            std::cout << "Exception type (ok): " << ex.what() << std::endl;
        } catch (std::exception& ex) {
            std::cout << "ERROR: incorrect exception type" << std::endl;
            assert(false);
        }
    }
    {
        const unsigned testCount = constCourse.count();
        std::cout << "Test count: " << testCount << std::endl;
        assert(testCount == 3);
    }
    {
        const std::string key = "1. Test";
        Test& firstTest = newCourse[key];
        std::stringstream stream;
        stream << firstTest;
        const std::string firstTestStr = stream.str();
        std::cout << firstTestStr << std::endl;
        assert(firstTestStr == "Test(1. Test)[\nScore(Test1;10),\nScore(Test2;20),\n]\n");
    }
    {
        const std::string otherKey = "3. Test";
        const Test& thirdTest = constCourse[otherKey];
        std::stringstream stream;
        stream << thirdTest;
        const std::string thirdTestStr = stream.str();
        std::cout << thirdTestStr << std::endl;
        assert(thirdTestStr == "Test(3. Test)[\nScore(Test1;30),\n]\n");
    }
    {
        const unsigned sumTests = (unsigned)constCourse;
        std::cout << "Sum of Tests: " << sumTests << std::endl;
        assert(sumTests == (20 + 30 + 30));
    }
    {
        std::set<std::string> testNames = constCourse.testNames();
        std::cout << "List of TestS: ";
        for (const std::string& name : testNames) {
            std::cout << name << ", ";
        }
        std::cout << std::endl;
        assert(testNames.contains("1. Test"));
        assert(testNames.contains("2. Test"));
        assert(testNames.contains("3. Test"));
        assert(testNames.size() == 3);
    }
    {
        Test test1("4. Test", 30);
        test1("TestA", 11);

        Course other("NativProg");
        other << test1;

        Course finalCourse = other + newCourse;
        const unsigned finalTestCount = finalCourse.count();
        std::cout << "[finalCourse] test count: " << finalTestCount << std::endl;
        assert(finalTestCount == 4);

        Course emptyCourse("NativProg");
        Course masikCourse = emptyCourse + other + newCourse;
        const unsigned masikTestCount = masikCourse.count();
        std::cout << "[masikCourse] test count: " << masikTestCount << std::endl;
        assert(masikTestCount == 4);
    }
    {
        Course nevHibas("NativProg3");
        try {
            nevHibas + newCourse;
            std::cout << "ERROR: no exception" << std::endl;
        } catch (std::invalid_argument& ex) {
            std::cout << "Exception type (ok): " << ex.what() << std::endl;
        } catch (std::exception& ex) {
            std::cout << "ERROR: incorrect exception type" << std::endl;
            assert(false);
        }
    }
    {
        Test test1("1. Test", 30);
        test1("TestA", 11);
        Course azonosTestCourse("NativProg");
        azonosTestCourse << test1;

        try {
            azonosTestCourse + newCourse;
            std::cout << "ERROR: no exception" << std::endl;
            assert(false);
        } catch (std::invalid_argument& ex) {
            std::cout << "Exception type (ok): " << ex.what() << std::endl;
        } catch (std::exception& ex) {
            std::cout << "ERROR: incorrect exception type" << std::endl;
            assert(false);
        }
    }
    {
        Course copyCourse = Course("NativProg") + newCourse;

        const std::string removeTestName = "2. Test";
        std::cout << "Test count before removal: " << newCourse.count() << std::endl;
        copyCourse -= removeTestName;

        const unsigned newCount = copyCourse.count();
        std::cout << "Test count after removal: " << newCount << std::endl;
        assert(newCount == 2);

        (copyCourse -= std::string("1. Test")) -= std::string("Incorrect Test");

        const unsigned finalCount = copyCourse.count();
        std::cout << "Test count after removing more: " << finalCount << std::endl;
    }
    {
        const unsigned limit = 20;
        const bool limitReached = newCourse >= limit;
        std::cout << "Course >= 20? " << limitReached << std::endl;
        assert(limitReached == true);
    }

    return 0;
}

#endif
