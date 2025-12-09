#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <cassert>


//===================== DO NOT TOUCH THE TEST NAMESPACE ============
//==================================================================
#ifndef TEST_BIRO
/**
 * Test namespace which should be used during the task implementations.
 * It contains jumper methods for making the testing possible.
 */
namespace test {

  /**
   * Reference implementation of accumulate(2)
   * It must be used during the test otherwise no point is given.
   * Usage: test::accumulate( ... ). All parameters are the same and behaves as the std one.
   *        ^^^^^^ this part is important. If it is missing, there is going to be an error.
   */
  template< class InputIt, class T, class BinaryOp >
  T accumulate( InputIt first, InputIt last, T init, BinaryOp op ) {
    return std::accumulate( first, last, init, op );
  }

  /**
   * Reference implementation of count_if(3)
   * It must be used during the test otherwise no point is given.
   * Usage: test::count_if( ... ). All parameters are the same and behaves as the std one.
   *        ^^^^^^ this part is important. If it is missing, there is going to be an error.
   */
  template< class InputIt, class UnaryPred >
  typename std::iterator_traits<InputIt>::difference_type
  count_if( InputIt first, InputIt last, UnaryPred p ) {
    return std::count_if(first, last, p);
  }

  /**
   * Reference implementation of transform(1)
   * It must be used during the test otherwise no point is given.
   * Usage: test::transform( ... ). All parameters are the same and behaves as the std one.
   *        ^^^^^^ this part is important. If it is missing, there is going to be an error.
   */
  template< class InputIt, class OutputIt, class UnaryOp >
  constexpr //< since C++20
  OutputIt transform( InputIt first1, InputIt last1, OutputIt d_first, UnaryOp unary_op ) {
    return std::transform( first1, last1, d_first, unary_op );
  }

  /**
   * Reference implementation of sort(3)
   * It must be used during the test otherwise no point is given.
   * Usage: test::sort( ... ). All parameters are the same and behaves as the std one.
   *        ^^^^^^ this part is important. If it is missing, there is going to be an error.
   */
  template< class RandomIt, class Compare >
  constexpr //< since C++20
  void sort( RandomIt first, RandomIt last, Compare comp ){
    std::sort(first, last, comp);
  }
};
#endif

#ifndef MY_JARAT

class Flight {
  std::string from, to;
  unsigned price;


public:
  Flight(const std::string& from, const std::string& to, unsigned price) :
          from(from), to(to),
          price(price) { }


  const std::string &getFrom() const {
    return from;
  }

  const std::string &getTo() const {
    return to;
  }

  unsigned int getPrice() const {
    return price;
  }

  void setPrice(unsigned a){
    price = a;
  }

  friend std::ostream& operator<<(std::ostream& os, const Flight& t) {
    return os << t.from << "-" << t.to << " (" << t.price << " forint)";
  }

  // WORK HERE!

};

#endif //MY_JARAT

// WORK HERE!

#ifndef TEST_BIRO

int main() {
  {
      //test flight set
      std::cout << std::endl << " --- test_flight_set ---" << std::endl << std::endl;

      std::vector<Flight> flights;
      flights.emplace_back("Budapest","Berlin", 32000);
      flights.emplace_back("Budapest","Bagdad", 86000);
      flights.emplace_back("Budapest","Berlin", 2000);
      flights.emplace_back("Tokio","Berlin", 200220);
      flights.emplace_back("Tokio","Budapest", 221000);

      std::set<Flight> halmaz = flight_set(flights);
      std::stringstream ss;
      for(auto j : halmaz){
        ss << j << std::endl;
      }

      std::string result = ss.str();
      std::cout << "The output of the first task" << std::endl << result << std::endl;
      assert(result == "Budapest-Bagdad (86000 forint)\nBudapest-Berlin (32000 forint)\nTokio-Berlin (200220 forint)\nTokio-Budapest (221000 forint)\n");


      // output
      //Budapest-Bagdad (86000 forint)
      //Budapest-Berlin (32000 forint)
      //Tokio-Berlin (200220 forint)
      //Tokio-Budapest (221000 forint)
  }

  {
    std::cout << std::endl << " --- test_cheapest ---" << std::endl << std::endl;

    std::vector<Flight> flights;
    flights.emplace_back("Budapest","Berlin", 2000);
    flights.emplace_back("Budapest","Bagdad", 86000);
    flights.emplace_back("Budapest","Berlin", 32000);
    flights.emplace_back("Tokio","Berlin", 200220);
    flights.emplace_back("Tokio","Budapest", 221000);
    flights.emplace_back("Budapest","Bagdad", 8600);
    flights.emplace_back("Tokio","Berlin", 200);
    flights.emplace_back("Tokio","Berlin", 100);

    std::map<std::string, unsigned> olcso_flights;
    cheapest(flights, olcso_flights);
    std::stringstream ss;
    for(const auto& p : olcso_flights){
      ss << p.first << " : " << p.second << std::endl;
    }

    std::string result = ss.str();
    std::cout << "The output of the second task" << std::endl << result << std::endl;
    assert(result == "BudapestBagdad : 8600\nBudapestBerlin : 2000\nTokioBerlin : 100\nTokioBudapest : 221000\n");

    // output
    //BudapestBagdad : 8600
    //BudapestBerlin : 2000
    //TokioBerlin : 100
    //TokioBudapest : 221000

  }

  {
    std::cout << std::endl << " --- count ---" << std::endl << std::endl;

    std::vector<Flight> flights;
    flights.emplace_back("Budapest","Berlin", 2000);
    flights.emplace_back("Budapest","Bagdad", 86000);
    flights.emplace_back("Budapest","Berlin", 32000);
    flights.emplace_back("Tokio","Berlin", 200220);
    flights.emplace_back("Tokio","Budapest", 221000);
    flights.emplace_back("Budapest","Bagdad", 8600);
    flights.emplace_back("Tokio","Berlin", 200);


    const unsigned result1 = count(flights, "Berlin");
    std::cout << "The output of the third task #1" << std::endl << result1 << std::endl;
    assert(result1 == 4);

    flights.emplace_back("Tokio","Berlin", 100);
    flights.emplace_back("Berlin","Moszkva", 10340);

    const unsigned result2 = count(flights, "Berlin");
    std::cout << "The output of the third task #2" << std::endl << result2 << std::endl;
    assert(result2 == 5);

    // output
    //4
    //5
  }

  {
    std::cout << std::endl << " --- filter ---" << std::endl << std::endl;

    std::vector<Flight> flights;
    flights.emplace_back("Budapest","Berlin", 2000);
    flights.emplace_back("Budapest","Bagdad", 86000);
    flights.emplace_back("Berlin","Budapest", 32000);
    flights.emplace_back("Berlin","Bagdad", 200220);
    flights.emplace_back("Berlin","Budapest", 52000);

    auto result = filter(flights, "Berlin", "Budapest");
    std::stringstream ss;
    for(const auto& j : result){
      ss << j << std::endl;
    }
    std::string sres = ss.str();
    std::cout << "The output of the fourth task #1" << std::endl << sres << std::endl << "----" << std::endl;
    assert(sres == "Berlin-Budapest (32000 forint)\nBerlin-Budapest (52000 forint)\nBudapest-Berlin (2000 forint)\n");

    result = filter(flights, "Budapest", "Berlin");
    std::stringstream ss2;
    for(const auto& j : result){
      ss2 << j << std::endl;
    }
    sres = ss2.str();
    std::cout << "The output of the fourth task #2" << std::endl << sres << std::endl;
    assert(sres == "Budapest-Berlin (2000 forint)\nBerlin-Budapest (32000 forint)\nBerlin-Budapest (52000 forint)\n");
    // output
    //Berlin-Budapest (32000 forint)
    //Berlin-Budapest (52000 forint)
    //Budapest-Berlin (2000 forint)
    //----
    //Budapest-Berlin (2000 forint)
    //Berlin-Budapest (32000 forint)
    //Berlin-Budapest (52000 forint)

  }

  {
    std::cout << std::endl << " --- fullSort ---" << std::endl << std::endl;

    std::vector<Flight> flights;
    flights.emplace_back("Budapest","Berlin", 2000);

    fullSort(flights);
    std::stringstream ss;
    for(const auto& j : flights){
      ss << j << std::endl;
    }
    std::string sres = ss.str();
    std::cout <<"The output of the fifth task #1" << std::endl << sres << std::endl;
    assert(sres == "Budapest-Berlin (2000 forint)\n");

    flights.emplace_back("Budapest","Bagdad", 86000);
    flights.emplace_back("Berlin","Budapest", 32000);
    flights.emplace_back("Berlin","Bagdad", 200220);
    flights.emplace_back("Berlin","Budapest", 52000);
    flights.emplace_back("Budapest","Bagdad", 76000);
    flights.emplace_back("Budapest","Washington", 1900);

    fullSort(flights);
    std::stringstream ss2;
    for(const auto& j : flights){
      ss2 << j << std::endl;
    }

    sres = ss2.str();
    std::cout <<"The output of the fifth task #2" << std::endl << sres << std::endl;
    assert(sres == "Budapest-Washington (1900 forint)\nBudapest-Berlin (2000 forint)\nBerlin-Budapest (32000 forint)\nBerlin-Budapest (52000 forint)\nBudapest-Bagdad (76000 forint)\nBudapest-Bagdad (86000 forint)\nBerlin-Bagdad (200220 forint)\n");


    // output
    //Budapest-Berlin (2000 forint)
    //
    //Budapest-Washington (1900 forint)
    //Budapest-Berlin (2000 forint)
    //Berlin-Budapest (32000 forint)
    //Berlin-Budapest (52000 forint)
    //Budapest-Bagdad (76000 forint)
    //Budapest-Bagdad (86000 forint)
    //Berlin-Bagdad (200220 forint)
  }


  {
    std::cout << std::endl << " --- fullCost ---" << std::endl << std::endl;

    std::vector<Flight> flights;
    flights.emplace_back("Budapest","Berlin", 2000);

    const unsigned result = fullCost(flights, 5000);

    std::cout << "Total amount of tickets with a limit of 5000:" << result << std::endl;
    assert(result == 2000);

    const unsigned result2 = fullCost(flights, 1000);
    std::cout << "Total amount of tickets with a limit of 1000:" << result2 << std::endl;
    assert(result2 == 0);

    flights.emplace_back("Budapest","Bagdad", 86000);
    flights.emplace_back("Berlin","Budapest", 32000);
    flights.emplace_back("Berlin","Bagdad", 200220);
    flights.emplace_back("Berlin","Budapest", 52000);
    flights.emplace_back("Budapest","Bagdad", 76000);
    flights.emplace_back("Budapest","Washington", 1900);

    const unsigned result3 = fullCost(flights, 80000);
    std::cout << "Total amount of tickets with a limit of 80000:" << result3 << std::endl;
    assert(result3 == 163900);

    // output
    //Total amount of tickets with a limit of  5000:2000
    //Total amount of tickets with a limit of  1000:0
    //Total amount of tickets with a limit of  80000:163900
  }


  {
    std::cout << std::endl << " --- sales ---" << std::endl << std::endl;

    std::vector<Flight> flights;
    flights.emplace_back("Budapest","Berlin", 2000);
    flights.emplace_back("Budapest","Bagdad", 86000);
    flights.emplace_back("Berlin","Budapest", 32000);
    flights.emplace_back("Berlin","Bagdad", 200220);
    flights.emplace_back("Berlin","Budapest", 52000);
    flights.emplace_back("Budapest","Bagdad", 76000);
    flights.emplace_back("Budapest","Washington", 1900);

    std::vector<Flight> results = sales(flights, 20);
    std::stringstream ss;
    for(const auto& j : results){
      ss << j << std::endl;
    }
    std::string sresult = ss.str();
    std::cout << "Output of sales task:" << std::endl << sresult << std::endl;
    assert(sresult == "Budapest-Berlin (1600 forint)\nBudapest-Bagdad (68800 forint)\nBerlin-Budapest (25600 forint)\nBerlin-Bagdad (160176 forint)\nBerlin-Budapest (41600 forint)\nBudapest-Bagdad (60800 forint)\nBudapest-Washington (1520 forint)\n");
    try{
      results = sales(flights, 200);
      assert(false);
    }catch(const std::exception& ex){
      assert(true);
    }

    // output
    //Budapest-Berlin (1600 forint)
    //Budapest-Bagdad (68800 forint)
    //Berlin-Budapest (25600 forint)
    //Berlin-Bagdad (160176 forint)
    //Berlin-Budapest (41600 forint)
    //Budapest-Bagdad (60800 forint)
    //Budapest-Washington (1520 forint)
  }


}
#endif
