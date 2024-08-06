#include <iostream>

int main() {
    double celsius, fahrenheit;
    std::cout << "Digite a temperatura em Celsius: ";
    std::cin >> celsius;
    fahrenheit = 9.0 / 5.0 * celsius + 32;
    std::cout << "A temperatura em Fahrenheit é: " << fahrenheit << " ºF" << std::endl;
}