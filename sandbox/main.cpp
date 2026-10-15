#include <string>
#include <iostream>

void downRec(int n);
long long tailRec(int n, long long acc = 1);
void upRec(int n);
bool isEven(int n);
bool isOdd(int n);
int ackermann(int m, int n);

// 1. Нисхідна рекурсія: розворот рядка на зворотному шляху
std::string reverseHead(std::string s) {
    // Базовий випадок: якщо рядок порожній або складається з 1 символу
    if (s.length() <= 1) return s;

    // Ваш код тут: потрібно викликати функцію для підрядка
    // і об'єднати результат на зворотному шляху

    auto str = s[0];
    reverseHead(s.substr(1));
    return "" + str;
}

// 2. Висхідна рекурсія (з акумулятором або прямим накопиченням):
// обробка під час спуску вниз
void reverseBody(const std::string& s, int index, std::string& acc) {
    if (index == 0) {
        index = s.length() - 1;
    }
    // Ваш код тут: додавайте символи в акумулятор під час занурення
    if (index > 0) {
        acc = acc + s[index];
        index--;
    }
}

int main() {
    // std::string original = "Recursion";
    //
    // std::cout << "Original: " << original << "\n";
    // std::cout << "Head reverse: " << reverseHead(original) << "\n"; // Має бути: noisruceR
    //
    // std::string bodyResult = "";
    // reverseBody(original, original.length() - 1, bodyResult);
    // std::cout << "Body reverse: " << bodyResult << "\n"; // Має бути: noisruceR

    int cursor = 12345;
    int *pointer = &cursor;
    int &ref = *pointer;
    // динамічні змінні, розіменування змінних
    std::cout << ref << std::endl;
    std::cout << pointer << std::endl;

    *pointer = 54321;
    *pointer = ref + 1;
    std::cout << *pointer << std::endl;
    std::cout << ref << std::endl;

    return 0;
}

int countWays(int n) {
    if (n < 0) return 0;
    if (n == 0) return 0;
    if (n == 1) return 1;

    return countWays(n - 1) + countWays(n - 2);
}

int sumOfSquares(int n) {
    if (n == 0) return 0;

    return sumOfSquares(n - 1) + n * n;
}

int rec(int first, int diff, const int n) {
    if (n == 1) return first;

    return rec(first + diff, diff, n - 1);
}

int sumDigitsTail(int n, int acc) {
    if (n == 0) return acc;

    return sumDigitsTail(n / 10, acc + n % 10);
}

// 2. Реалізуйте за допомогою НИСХІДНОЇ (Head) рекурсії (розрахунок на зворотному шляху)
int sumDigitsHead(int n) {
    if (n == 0) return 0;

    sumDigitsHead(n / 10);
    std::cout << n % 10 << std::endl;
}

// std::cout << "Hello from sandbox!" << std::endl;
//
// // Низхідна
// std::cout << "Низхідна рекурсія:" << std::endl;
// downRec(5);
// std::cout << "Хвостова рекурсія:" << std::endl;
// std::cout << tailRec(5) << std::endl;
// std::cout << "Зростаюча рекурсія:" << std::endl;
// upRec(5);
//
// std::cout << std::boolalpha;
// std::cout << isEven(4) << "\n"; // Виведе: true
// std::cout << isOdd(4) << "\n";  // Виведе: false
//
// std::cout << "Вкладена рекурсія:" << std::endl;
// std::cout << ackermann(2, 2) << std::endl;

void downRec(int n) {
    if (n == 0) return;

    downRec(n - 1); // дно
    std::cout << n << std::endl; // зворотній шлях
}

long long tailRec(int n, long long acc) {
    if (n == 0) return acc;

    return tailRec(n - 1, n * acc); // Останній рядок - хвостовий виклик
}

void upRec(int n) {
    if (n == 0) return;

    std::cout << n << std::endl; // спуск вниз
    upRec(n - 1);
}

bool isEven(int n) {
    if (n == 0) return true;
    return isOdd(n - 1);
}

bool isOdd(int n) {
    if (n == 0) return false;
    return isEven(n - 1);
}

// вкладена рекурсія
int ackermann(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return ackermann(m - 1, 1);
    } else {
        return ackermann(m - 1, ackermann(m, n - 1));
    }
}