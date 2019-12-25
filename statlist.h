#ifndef STATLIST_H
#define STATLIST_H
//statlist.h

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

template <typename E> class statlist{
  
  private:
    double mean, mode, median, standard_dev;
    //length is number of unique elements, total is number of elements
    int length, total;
    vector<pair<E, int> > data;

    E &at(int index) {
      if (index <= total) {
        //If the item is anywhere in the middle, iterate past each value and keep count
        int count = index;
        for (int i = 0; i < length; i++) {
          if (data[i].second < count) {
            count -= data[i].second;
          }
          else {
            return data[i].first;
          }
        }
      }
      //For indices greater than length, return a nonexistant value
      //todo: make this a thrown exception or something
      E nonvalue = 0;
      return nonvalue;
    }

    void updateStats() {
      updateMean();
      updateMode();
      updateMedian();
      updateSD();
    }

    void updateMean() {
      double sum = 0;
      for(int i = 0; i < length; i++) {
        sum += data[i].first * data[i].second;
      }
      mean = sum/(double)total;
    }

    void updateMode() {
      int modeindex = 0;
      for(int i = 0; i < length; i++) {
        if(data[modeindex].second < data[i].second) {
          modeindex = i;
        }
      }
      mode = data[modeindex].first;
    }

    void updateMedian() {
      int half = total / 2;
      if (total == 0){
        median = 0;
      }
      else if (total % 2 == 0){
        // If the number is even, the value is the mean of two middle elements
        median = (at(half) + at(half - 1)) / 2;
      }
      else
      {
        // If the number is odd, the value is the middle element
        // Integer rounding rounds down and prevents this from getting weird
        median = at(half);
      }
    }

    void updateSD() {
      double meanDiff[total];
      int count = 0;
      //put all numbers and their counts into a single array
      //loop through pairs
      for(int i = 0; i < length; i++) {
        //loop through pair.second
        for(int j = 0; j < data[i].second; j++) {
          meanDiff[count] = data[i].first;
          count++;
        }
      }
      //subtract every number in array by the mean then square the result, then sum them up
      double squaredDiff = 0;
      for(int i = 0; i < total; i++) {
        meanDiff[i] = meanDiff[i] - mean;
        meanDiff[i] = meanDiff[i] * meanDiff[i];
        squaredDiff+= meanDiff[i];
      }
     
      //divide the sum by total to find its mean then take square root
      squaredDiff /= total;
      squaredDiff = sqrt(squaredDiff);
      standard_dev = squaredDiff;
    }

    //helper function to for sqrt, finds biggest perfect square that doesn't go over target number
    int biggestPerfectSquare(double num) {
      int i = 0;
      bool found = false;
      while(!found) {
        if((i*i) > num) { 
          found = true;
        }
        i++;
      }
      return i-1;
    }

    //function to return squareroot used for standard deviation
    double sqrt(double num) {
      double square = biggestPerfectSquare(num);
      double div = num/square;
      double avg = (div+square)/2;
      for(int i = 0; i < 10; i++) {
        div = num/avg;
        avg = (avg+div)/2;
      }
      return avg;
    }

  public:
    //empty constructor
    statlist() {
      mean = mode = median = standard_dev = length = total = 0;
    }
    
    //constructor that takes in vector input
    statlist(vector<E> input) {
      mean = mode = median = standard_dev = length = total = 0;
      for(int i = 0; i < input.size(); i++)
        append(input[i]);      
    }

    //overloading array access operator
    E &operator[](int index) {
      return at(index);
    }

    //function to check wheter the number already exists in data
    bool exists(const E& it) {
      for(int i = 0; i < data.size(); i++) {
        if(data[i].first == it)
          return true;
      }
      return false;
    }

    //search function returns a pair<int,int>
    //p.first = index, p.second = count
    pair<int,int> search(const E& it) {
      int idx = getIndex(it);
      int count;
      if(idx == -1) count = 0;
      else count = data[idx].second;
      pair<int,int> p(idx,count);
      return p;
    }

    //function to get index of number that's already in data
    int getIndex(const E& it) {
      for(int i = 0; i < data.size(); i++) {
        if(data[i].first == it) {
          return i;
        }
      }
      return -1;
    }

    //function to print out statlist
    void printStat() {
      cout << "mean: " << mean << endl;
      cout << "mode: " << mode << endl;
      cout << "median: " << median << endl;
      cout << "standard_dev: " << standard_dev << endl;
    }

    //function to print out contents in data
    void printData() {
      for(int i = 0; i < data.size(); i++) {
        cout << data[i].first << "," << data[i].second << endl;
      }
    }

    //get the max(last element)
    E get_max() {
      if(data.size()!=0) return data[length-1].first;
      try{
        if(data.size()==0){
          throw 1;
        }
      } catch(int e) {
        cout << "no maximum" << endl;
      }
      return 0;
    }

    //get min (first element)
    E get_min() {
      if(data.size()!=0)return data[0].first;
      try{
        if(data.size()==0){
          throw 1;
        }
      } catch(int e) {
        cout << "no minimum" << endl;
      }
      return 0;
    }

    double get_mode() {
      return mode;
    }

    double get_mean() {
      return mean;
    }

    double get_median() {
      return median;
    }

    double get_SD() {
      return standard_dev;
    }

    //number of unique elements
    int length_unique() {
      return length;
    }

    //count of all elements
    int length_total() {
      return total;
    }

    //append a number into data 
    void append(const E& it) {
      //if element already exists increment count(pair.second)
      if(exists(it)) {
        int idx = getIndex(it);
        data[idx].second++;
      }
      //if element doesn't exist create a new pair and add into list
      else {
        pair<E, int> p(it, 1);
        data.push_back(p);
        length++;
      }
      total++;
      //sort data by first from least to greatest
      sort(data.begin(),data.end());
      //update statistics
      updateStats();
    }

    //removes count number of elements of the value key
    void removen(const E& key, int count) {
      int index = getIndex(key);
      if (index >= 0) {
        //if the number equals the count to remove, remove that element entirely
        if (data[index].second == count) {
          data.erase(data.begin()+index);
          length--;
          total -= count;
          updateStats();
        }
        //otherwise, just remove that many from it
        else if (data[index].second > count) {
          data[index].second -= count;
          total -= count;
          updateStats();
        }
        //doesn't update if the number of data elements < count to remove
      }
    }

    //clears entire data set using method in vector class
    void empty() {
      data.clear();
      mean = mode = median = standard_dev = length = total = 0;
    }
    
};

#endif
