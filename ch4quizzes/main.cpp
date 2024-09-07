#include <iostream>

double heightFallen(double userHeight, double seconds) {
    double g{9.8};
    double endHeight{userHeight - g*seconds*seconds/2};
    if(endHeight >= 0.) {
        return endHeight;
    }
    return 0;
}

int main() {
    double userHeight{};
    std::cout << "Enter height in meters: " << '\n';
    std::cin >> userHeight;
    std::cout << "0 sec: " << heightFallen(userHeight,0) << '\n';
    std::cout << "1 sec: " << heightFallen(userHeight,1) << '\n';
    std::cout << "2 sec: " << heightFallen(userHeight,2) << '\n';
    std::cout << "3 sec: " << heightFallen(userHeight,3) << '\n';
    std::cout << "4 sec: " << heightFallen(userHeight,4) << '\n';
    std::cout << "5 sec: " << heightFallen(userHeight,5) << '\n';
    return 0;
}