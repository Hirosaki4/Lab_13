#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // для форматованого виводу


using namespace std;

// Абстрактний клас Product
class Product {
protected:
    string name;
    double price;

public:
    Product(const string& name, double price) : name(name), price(price) {}

    virtual ~Product() {}

    // Гетери
    string getName() const { return name; }
    double getPrice() const { return price; }

    // Сетери
    void setName(const string& name) { this->name = name; }
    void setPrice(double price) { this->price = price; }

    // Абстрактний метод для кінцевої ціни
    virtual double getFinalPrice() const = 0;
};

// Інтерфейс Discountable
class Discountable {
public:
    virtual ~Discountable() {}

    // Метод для застосування знижки
    virtual double applyDiscount(double price) const = 0;
};

// Клас Book, наслідує Product та реалізує Discountable
class Book : public Product, public Discountable {
public:
    Book(const string& name, double price) : Product(name, price) {}

    // Реалізація методу applyDiscount (10% знижка)
    double applyDiscount(double price) const override {
        return price * 0.9; // 10% знижка
    }

    // Реалізація методу getFinalPrice
    double getFinalPrice() const override {
        return applyDiscount(price);
    }
};

// Клас Pen, наслідує Product та реалізує Discountable
class Pen : public Product, public Discountable {
public:
    Pen(const string& name, double price) : Product(name, price) {}

    // Реалізація методу applyDiscount (фіксована знижка 5 грн)
    double applyDiscount(double price) const override {
        if (price > 5) {
            return price - 5;
        }
        else {
            return price; // Без знижки, якщо ціна <= 5
        }
    }

    // Реалізація методу getFinalPrice
    double getFinalPrice() const override {
        return applyDiscount(price);
    }
};

// Головна функція
int main() {
    // Налаштування кодування для роботи з українською мовою


    // Створення об'єктів типу Book та Pen
    vector<Product*> products;
    products.push_back(new Book("Blue Period",300));
    products.push_back(new Book("Atomic habits",150));
    products.push_back(new Pen("Ballpoint Pen",20));
    products.push_back(new Pen("Cheap Pen",4));

    // Вивід інформації про товари
    cout << fixed << setprecision(2); // Форматування чисел
    cout << "\nName\t\t      Base Price\tFinal Price\n";
    cout << "----------------------------------------------------\n";

    for (const auto& product : products) {
        cout << product->getName() << "\t\t" << product->getPrice() << "\t\t" << product->getFinalPrice() << "\n";
    }

    // Звільнення пам'яті
    for (auto& product : products) {
        delete product;
    }

    return 0;
}
