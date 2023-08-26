
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

double generateRandomDouble()
{
    return -1 + static_cast<double>(rand()) / RAND_MAX * 2;
}

std::pair<double, double> generateRandomPoint()
{
    return std::make_pair(generateRandomDouble(), generateRandomDouble());
}

bool isInsideCircle(const std::pair<double, double>& point)
{
    return pow(point.first, 2) + pow(point.second, 2) <= 1;
}

int main(int argc, char const *argv[])
{
    srand(time(0));
    const int points = 10000000;
    int pointsInside = 0;

    for (int i = 0; i < points; ++i)
        pointsInside += isInsideCircle(generateRandomPoint());

    std::cout << "Total points: " << points << std::endl;
    std::cout << "Pi approximation: " << 4 * (double)pointsInside / points << std::endl;

    return 0;
}