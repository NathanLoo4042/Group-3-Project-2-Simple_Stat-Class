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
  public:
    //constructor
    statlist() {
      mean = mode = median = standard_dev = length = total = 0;
    }
    
    //constructor that takes in vector input
    statlist(vector<E> input) {
      mean = mode = median = standard_dev = length = total = 0;
      for(int i = 0; i < input.size(); i++)
        append(input[i]);      
    }

    //constructor that takes in array input
    statlist(E input[], int size) {
      mean = mode = median = standard_dev = length = total = 0;
      for(int i = 0; i < sizeof(input)/sizeof(input[0]); i++)
        append(input[i]); 
    }

    //overloading array access operator
    E &operator[](int index) {
      return data[index].first;
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
      return data[length-1].first;
    }

    //get min (first element)
    E get_min() {
      return data[0].first;
    }

    double get_mode() {
      return mode;
    }

    double get_mean() {
      return mean;
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
      int a = 0;
      for(int i = 0; i < length; i++) {
        if(a < data[i].second) {
          a = i;
        }
      }
      mode = data[a].first;
    }

    void updateMedian() {
      int half = total / 2;
      if (total == 0){
        median = 0;
      }
      else if (total % 2 == 0){
        // If the number is even, the value is the mean of two middle elements
        median = (data[half].first + data[half - 1].first) / 2;
      }
      else
      {
        // If the number is odd, the value is the middle element
        // Integer rounding rounds down and prevents this from getting weird
        median = data[half].first;
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

    // todo: removen (Remove N number of an element)
    // todo: empty (Clear entire data set)
    
};

#endif
