#ifndef STATLIST_H
#define STATLIST_H
//statlist.h

#include <iostream>
#include <utility>
#include <vector>
#include<bits/stdc++.h>
#include <math.h>
using namespace std;

template <typename E> class statlist{
  
  private:
    double mean, mode, median, standard_dev;
    int length, total;
    vector<pair< E, int> > data;
  public:
    //constructor
    statlist() {
      mean = mode = median = standard_dev = length = total = 0;
    }

    //function to check wheter the number already exists in data
    bool exists(const E& it) {
      for(int i = 0; i < data.size(); i++) {
        if(data[i].first == it)
          return true;
      }
      return false;
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
      cout << "mean: " + mean << endl;
      cout << "mode: " + mode << endl;
      cout << "median: " + median << endl;
      cout << "standard_dev: " + standard_dev << endl;
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


    //insert
    void insert(const E& it) {
      //if element already exists increment count(pair.second)
      if(exists(it)) {
        int idx = getIndex(it);
        data[idx].second++;
        total++;
      }
      //if element doesn't exist create a new pair and add into list
      if(!exists(it)) {
        pair<E, int> p(it, 1);
        data.push_back(p);
        length++;
        total++;
      }
      //sort data by first from least to greatest
      sort(data.begin(),data.end());
      //update statistics
      updateMode();
      updateMean();
      updateSD();
    }

};

#endif
