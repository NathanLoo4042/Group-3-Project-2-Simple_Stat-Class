#include "randomdata.h"
#include "statlist.h"
#include <iostream>

template <typename R>
void printlessstats(statlist<R> printlist)
{
    // Testing all O(1) getters except get_min, get_max, and printStat
    std::cout << "Printing statlist data: \n";
    printlist.printData();
    std::cout << "Manually checking stats:"
            << "\n\tMean: " << printlist.get_mean()
            << "\n\tMedian: " << printlist.get_median()
            << "\n\tMode: " << printlist.get_mode()
            << "\n\tStandard Deviation: " << printlist.get_SD()
            << "\n\tUnique Elements: " << printlist.length_unique()
            << "\n\tTotal Elements: " << printlist.length_total()
            << std::endl;
}

template <typename R>
void printstats(statlist<R> printlist)
{
    // Testing all O(1) getters except printStat
    std::cout << "Printing statlist data: \n";
    printlist.printData();
    std::cout << "Manually checking stats:"
            << "\nMin: " << printlist.get_min()
            << "\nMax: " << printlist.get_max()
            << "\n\tMean: " << printlist.get_mean()
            << "\n\tMedian: " << printlist.get_median()
            << "\n\tMode: " << printlist.get_mode()
            << "\n\tStandard Deviation: " << printlist.get_SD()
            << "\n\tUnique Elements: " << printlist.length_unique()
            << "\n\tTotal Elements: " << printlist.length_total()
            << std::endl;
}

int main(int argc, char const *argv[])
{
    // Testing creation of empty statlist
    std::cout << "\n**** Creating empty statlist ****\n";
    statlist<int> emptylist;
    // Testing printStat
    emptylist.printStat();
    printlessstats(emptylist);
    // Testing appending to empty statlist
    std::cout << "\n**** Testing one append ****\n";
    emptylist.append(20);
    printstats(emptylist);
    std::cout << "\n**** Testing multiple appends ****\n";
    for (int i = 0; i < 30; i++)
    {
        emptylist.append(10);
    }
    emptylist.append(15);
    emptylist.append(30);
    emptylist.append(30);
    printstats(emptylist);
    // Testing index access
    std::cout << "\n**** Testing index access ****\n";
    std::cout << "At first index " << 0 << ": " << emptylist[0]
            << "\nAt index " << 1 << ": " << emptylist[1]
            << "\nAt index " << 29 << ": " << emptylist[29]
            << "\nAt index " << 30 << ": " << emptylist[30]
            << "\nAt last index " << 33 << ": " << emptylist[33]
            << "\nAt invalid index " << 34 << ": " << emptylist[34]
            << std::endl;
    // Testing search function
    std::cout << "\n**** Testing search ****\n";
    pair<int, int> esearch10 = emptylist.search(10);
    pair<int, int> esearch11 = emptylist.search(11);
    pair<int, int> esearch20 = emptylist.search(20);
    std::cout << "Searching value " << 10 << ": " << esearch10.first << ", " << esearch10.second
            << "\nSearching value " << 20 << ": " << esearch20.first << ", " << esearch20.second
            << "\nSearching invalid value " << 11 << ": " << esearch11.first << ", " << esearch11.second
            << std::endl;
    // Testing removal from statlist
    std::cout << "\n**** Testing count removal ****\n";
    emptylist.removen(10, 29);
    printstats(emptylist);
    std::cout << "\n**** Testing element removal ****\n";
    emptylist.removen(10, 1);
    printstats(emptylist);
    std::cout << "\n**** Testing invalid removal ****\n";
    emptylist.removen(10, 1);
    printstats(emptylist);
    // Initializing randomizer
    Random_data<int> randomizer;
    // Testing creation of a very full statlist
    std::cout << "\n**** Creating very full statlist ****\n";
    std::vector<int> testtenk = randomizer.get_random_vector(10000, -50, 50);
    statlist<int> veryfulllist(testtenk);
    printstats(veryfulllist);

    return 0;
}