#include <iostream>

/*
Вариант 3. Шахниязов Ботир, 201 группа.
Рациональная (несократимая) дробь представляется парой целых чисел (a, b), где a — числитель, b —
знаменатель. Создать класс Rational для работы с рациональными дробями. Обязательно должны быть
реализованы операции:
 сложения add, (a, b) + (c, d) = (ad + bc, bd);
 вычитания sub, (a, b) – (c, d) = (ad – bc, bd);
 умножения mul, (a, b)  (c, d) = (ac, bd);
 деления div, (a, b) / (c, d) = (ad, bc);
 операции сравнения.
Должна быть реализована функция сокращения дроби reduce(), которая обязательно вызывается при
выполнении арифметических операций.
*/

class Rational
{
private:
    int numerator; //числитель
    int denominator; //знаменатель
public:
    Rational()
    {
        numerator = 0;
        denominator = 1;
    }

    Rational(int _numerator, int _denominator)
    {
        set(_numerator, _denominator);
    }

    Rational operator+(Rational b)
    {
        Rational c(this->numerator * b.denominator + this->denominator * b.numerator, this->denominator * b.denominator);
        return c;
    }
    
    Rational operator-(Rational b)
    {
        Rational c(this->numerator * b.denominator - this->denominator * b.numerator, this->denominator * b.denominator);
        return c;
    }

    Rational operator*(Rational b)
    {
        Rational c(this->numerator * b.numerator, this->denominator * b.denominator);
        return c;
    }

    Rational operator/(Rational b)
    {
        Rational c(this->numerator * b.denominator, this->denominator * b.numerator);
        return c;
    }

    int operator==(Rational b)
    {
        return (this->numerator == b.numerator && this->denominator == b.numerator) ? 1 : 0;
    }

    int operator>(Rational b)
    {
        return (this->numerator * b.denominator - this->denominator * b.numerator > 0) ? 1 : 0;
    }

    int operator<(Rational b)
    {
        return (this->numerator * b.denominator - this->denominator * b.numerator > 0) ? 0 : 1;
    }

    int get_num()
    {
        return this->numerator;
    }

    int get_den()
    {
        return this->denominator;
    }

    void set(int _numerator, int _denominator)
    {
        numerator = _numerator;
        denominator = _denominator;
    }

    int EuclideanAlgorithm(int a, int b) //алгоритм Евклида (поиск наибольшего общего кратного)
    {
        if (b == 0)
            return a;
        return EuclideanAlgorithm(b, a % b);
    }

    void reduce() //сокращение дроби
    {
        int NOK = EuclideanAlgorithm(numerator, denominator);
        while(NOK != 1)
        {
            numerator /= NOK;
            denominator /= NOK;
            NOK = EuclideanAlgorithm(numerator, denominator);
        }
        if(denominator < 0) //если знаменатель отрицателен, то "отправляем" минус в числитель
        {
            numerator *= -1;
            denominator *= -1;
        }
    }
};

void cout_menu()
{
    std::cout << "Menu\n";
    std::cout << "0. quit\n";
    std::cout << "1. print menu\n";
    std::cout << "2. input frac a\n";
    std::cout << "3. input frac b\n";
    std::cout << "4. add\n";
    std::cout << "5. sub\n";
    std::cout << "6. mul\n";
    std::cout << "7. div\n";
    std::cout << "8. equal\n";
    std::cout << "9. more\n";
    std::cout << "10. less\n";
}


int main()
{
    Rational a, b, c;
    int action=1, num, den;
    while(action != 0)
    {
        switch (action)
        {
        case 1: cout_menu(); break;
        case 2: std::cout << "a.numerator = "; std::cin >> num;
                std::cout << "a.denominator = "; std::cin >> den;
                a.set(num, den);
                break;
        case 3: 
                std::cout << "b.numerator = "; std::cin >> num;
                std::cout << "b.denominator = "; std::cin >> den;
                b.set(num, den);
                break;
        case 4: c = a + b; break;
        case 5: c = a - b; break;
        case 6: c = a * b; break;
        case 7: c = a / b; break;
        case 8: c.set(a == b, 1); break;
        case 9: c.set(a > b, 1); break;
        case 10: c.set(a < b, 1); break;
        default: break;
        }
        a.reduce(); b.reduce(); c.reduce();
        std::cout << "a=" << a.get_num() << "/" << a.get_den() << " ";
        std::cout << "b=" << b.get_num() << "/" << b.get_den() << " ";
        std::cout << "c=" << c.get_num() << "/" << c.get_den() << " \n-->";
        std::cin >> action;
    }
    return 0;
}