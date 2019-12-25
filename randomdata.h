#ifndef RANDOMDATA_H
#define RANDOMDATA_H

#include <random>
#include <vector>
#include <set>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <type_traits>

template <typename T>
class Random_data {
private:
public:
    Random_data()=default; // Default constructor
    ~Random_data(){} // destructor
    std::vector<T> get_random_vector(int NumberCount,T minimum, T maximum) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::vector<T> values(NumberCount);
        if (std::is_same<T, int>::value == true){
            std::uniform_int_distribution<int> dis(minimum, maximum);
            int number;
            for (int i=0; i<NumberCount; ++i) {
              number = dis(gen);
              values[i] = number;
            }
        }
        else{
            std::uniform_real_distribution<double> dis(minimum, maximum);
            double number;
            for (int i=0; i<NumberCount; ++i) {
              number = dis(gen);
              values[i] = number;
            }
      }

        return values;
    }

    std::vector<T> get_unique_random_vector(int NumberCount,T minimum, T maximum) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::set<T> values;
        if (std::is_same<T, int>::value){
            std::uniform_int_distribution<int> dis(minimum, maximum);
            while (values.size()!= NumberCount)
              values.insert(dis(gen));

          }
        else{
          std::uniform_real_distribution<double> dis(minimum, maximum);
          while (values.size()!= NumberCount)
            values.insert(dis(gen));

          }
         std::vector<T> values2(values.begin(), values.end());
        return values2;
    }

    std::vector<T> get_sorted_unique_random_vector(int NumberCount,T minimum, T maximum) {
      std::vector<T> vec = get_unique_random_vector(NumberCount, minimum, maximum);
      std::stable_sort(vec.begin(), vec.end());
      return vec;
    }

    std::unordered_map<T, std::size_t> get_unique_random_hash_table(std::vector<T> rand_vec) {

      std::unordered_map<T, std::size_t> hash_table;
      for (auto& el : rand_vec)
      {
          std::hash<T> hvalue;
          std::pair<T,std::size_t>  p(el,hvalue(el));
          hash_table.insert(p);

      }
        return hash_table;
    }
};
#endif // RANDOMDATA_H

