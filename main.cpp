#include "utilities.h"
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
    emptylist.append(10);
    printstats(emptylist);
    std::cout << "\n**** Testing multiple appends ****\n";
    for (int i = 0; i < 30; i++)
    {
        emptylist.append(20);
    }
    printstats(emptylist);
    // Testing creation of a very full statlist
    return 0;
}