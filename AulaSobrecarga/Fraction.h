#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <numeric>
#include <stdexcept>

class Fraction {
   private:
    int numerator;    // Numerador da fração
    int denominator;  // Denominador da fração

   public:
    /**
     * @brief Recebe dois inteiros e cria um objeto Fraction.
     * O construtor deve simplificar a fração obtendo uma fração equivalente, mas com numerador e denominador
     * o menor possível.
     * A função garante que o denominador seja diferente de zero.
     *
     * @param numerator
     * @param denominator
     */
    Fraction(int numerator, int denominator);

    Fraction() : Fraction(1, 1) {}

    Fraction(const Fraction& other) : Fraction(other.numerator, other.denominator) {}

    /**
     * @brief Método que simplifica a fração.
     *
     */
    void reduce();

    // *** Métodos de acesso ***

    /**
     * @brief Get the Numerator object
     *
     * @return double
     */
    double getNumerator() const;

    /**
     * @brief Get the Denominator object
     *
     * @return double
     */
    double getDenominator() const;

    /**
     * @brief Set the Numerator object
     *
     * @param numerator
     */
    void setNumerator(int numerator);

    /**
     * @brief Set the Denominator object
     *
     * @param denominator
     */
    void setDenominator(int denominator);

    // *** Sobrecarga de operadores ***

    /**
     * @brief Sobrecarga do operador de inserção << para imprimir a fração.
     * @return Um objeto ostream com a fração formatada.
     *
     */
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);

    /**
     * @brief Sobrecarga do operador de extração >> para ler a fração.
     * @return Um objeto istream com a fração lida.
     *
     */
    friend std::istream& operator>>(std::istream& is, Fraction& fraction);

    /**
     * @brief Sobrecarga do operador de adição + para somar duas frações.
     * @return Uma nova fração com o resultado da soma.
     *
     */
    Fraction operator+(const Fraction& other) const;

    /**
     * @brief Sobrecarga do operador de subtração - para subtrair duas frações.
     * @return Uma nova fração com o resultado da subtração.
     *
     */
    Fraction operator-(const Fraction& other) const;

    /**
     * @brief Sobrecarga do operador de multiplicação * para multiplicar duas frações.
     * @return Uma nova fração com o resultado da multiplicação.
     *
     */
    Fraction operator*(const Fraction& other) const;

    /**
     * @brief Sobrecarga do operador de divisão / para dividir duas frações.
     * @return Uma nova fração com o resultado da divisão.
     *
     */
    Fraction operator/(const Fraction& other) const;

    /**
     * @brief Sobrecarga do operador de adição += para somar duas frações e atribuir o resultado à fração da esquerda.
     * @return A própria fração da esquerda após a soma.
     *
     */
    Fraction& operator+=(const Fraction& other);

    /**
     * @brief Sobrecarga do operador de subtração -= para subtrair duas frações e atribuir o resultado à fração da esquerda.
     * @return A própria fração da esquerda após a subtração.
     *
     */
    Fraction& operator-=(const Fraction& other);

    /**
     * @brief Sobrecarga do operador de multiplicação *= para multiplicar duas frações e atribuir o resultado à fração da esquerda.
     * @return A própria fração da esquerda após a multiplicação.
     *
     */
    Fraction& operator*=(const Fraction& other);

    /**
     * @brief Sobrecarga do operador de divisão /= para dividir duas frações e atribuir o resultado à fração da esquerda.
     * @return A própria fração da esquerda após a divisão.
     *
     */
    Fraction& operator/=(const Fraction& other);

    /**
     * @brief Sobrecarga do operador de igualdade == para comparar duas frações.
     * @return true se as frações forem iguais, false caso contrário.
     */
    bool operator==(const Fraction& other) const;

    /**
     * @brief Sobrecarga do operador de diferença != para comparar duas frações.
     * @return true se as frações forem diferentes, false caso contrário.
     */
    bool operator!=(const Fraction& other) const;

    /**
     * @brief Sobrecarga do operador de menor < para comparar duas frações.
     * @return true se a fração da esquerda for menor que a fração da direita, false caso contrário.
     *
     */
    bool operator<(const Fraction& other) const;

    /**
     * @brief Sobrecarga do operador de menor ou igual <= para comparar duas frações.
     * @return true se a fração da esquerda for menor ou igual que a fração da direita, false caso contrário.
     *
     */
    bool operator<=(const Fraction& other) const;

    /**
     * @brief Sobrecarga do operador de maior > para comparar duas frações.
     * @return true se a fração da esquerda for maior que a fração da direita, false caso contrário.
     *
     */
    bool operator>(const Fraction& other) const;

    /**
     * @brief Sobrecarga do operador de maior ou igual >= para comparar duas frações.
     * @return true se a fração da esquerda for maior ou igual que a fração da direita, false caso contrário.
     *
     */
    bool operator>=(const Fraction& other) const;
};

#endif  // FRACTION_H