#include "pie.h"
#include <iostream>

int main() {
    ApplePie<int, 10, double> applePie(25, 5.5);
    CherryPie<int, 10> cherryPie(25);
    
    // constructor should be undefined
    // CherryPie<int, 20> cherryPie2(30, 2.5);

    // wrong template type
    // CherryPie<double, 15> cherryPie3(10);

    // wrong template type
    // ApplePie<int, 12, int> applePie2(10, 10);
}