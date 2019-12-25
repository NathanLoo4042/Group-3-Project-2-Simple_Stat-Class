#include "utilities.h"
#include "statlist.h"
#include <iostream>

template <typename E>
void printstats(statlist<E> printlist)
{
    std::cout << "Printing statlist stats: \n";
    printlist.printStat();
    std::cout << "Printing statlist data: \n";
    printlist.printData();
    std::cout << "Manually checking stats:"
            << "\nMin: " << printlist.get_min()
            << "\nMax: " << printlist.get_max()
            << "\nMean: " << printlist.get_mean()
            << "\nMedian: " << printlist.get_median()
            << "\nMode: " << printlist.get_mode()
            << "\nStandard Deviation: " << printlist.get_SD()
            << "\nUnique Elements: " << printlist.length_unique()
            << "\nTotal Elements: " << printlist.length_total()
            << std::endl;
}

int main(int argc, char const *argv[])
{
    // Testing creation of statlist
    std::cout << "Creating empty statlist\n";
    statlist<double> emptylist;
    printstats(emptylist);
    return 0;
}