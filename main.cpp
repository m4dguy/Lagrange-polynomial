#include "Lagrange.h"

int main()
{
    std::vector<double> xList;
    xList.push_back(-1.);
    xList.push_back(0.);
    xList.push_back(1.);
    xList.push_back(3.);
    xList.push_back(4.);

    std::vector<double> yList;
    yList.push_back(1.);
    yList.push_back(0.);
    yList.push_back(0.);
    yList.push_back(4.);
    yList.push_back(-1.);

    Lagrange<double> lag(xList, yList);

    for(double i=-2; i<5; ++i)
        std::cout << "[" << lag(i) << "] ";

    std::cout << std::endl;

    return 0;
}
