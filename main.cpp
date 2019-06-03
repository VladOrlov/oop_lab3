#include <iostream>
//#include <windows.h>
#include <list>

using namespace std;

class Date {
public:
    int day, month, year;

    Date() {
        this->day = 0;
        this->month = 0;
        this->year = 0;
    }

    Date(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    virtual void Show() {
        printf("%.2d.%.2d.%.4d\r\n", day, month, year);
    }
};

class FuelType {
protected:
    const char *name;
public:
    FuelType() {
        this->name = "Íåâ³äîìå ïàëüíå";
    }

    FuelType(const char *name) {
        this->name = name;
    }

    const char *getType() {
        return (this->name);
    }

};

const FuelType AI92("AI-92");
const FuelType AI95("AI-95");
const FuelType AI98("AI-98");
const FuelType DI("Äèçåëü");
const FuelType NONE("Íåâ³äîìå ïàëüíå");


class Fuel {
protected:
    FuelType type;
    float price;
public:

    Fuel(FuelType type, float price) {
        this->type = type;
        this->price = price;
    }

    Fuel(Fuel &fuel) {
        this->type = fuel.type;
        this->price = fuel.price;
    }

    virtual void Show() {
        printf("Òèï: %s\t Ö³íà: %4.2f\r\n", type.getType(), price);
    }
};

class Operator : public Date {
protected:
    const char *surname;
    const char *name;
public:
    Operator() : Date(0, 0, 0) {
        surname = (char *) "Ïð³çâèùå";
        name = (char *) "²ì'ÿ";
    }

    Operator(const char *surname, const char *name, int day, int month, int year) : Date(day, month, year) {
        this->surname = surname;
        this->name = name;
    }

    Operator(Operator &op) : Date(op.day, op.month, op.year) {
        surname = op.surname;
        name = op.name;
    }

    void Show() override {

        printf("²íôîðìàö³ÿ ïðî îïåðàòîðà:\r\n\t²ì'ÿ: %s %s\n", surname, name);
        printf("\tÄàòà íàðîäæåííÿ: ");
        Date::Show();
    }
};

class Sale : public virtual Operator, public virtual Fuel {
public:
    double quantity;
    double sum;
    Date *date;

    void CountSum() {
        sum = quantity * price;
    }

    Sale() : Operator(), Fuel(NONE, 0) {
        quantity = 0;
        sum = 0;
        date = new Date();
    }

    Sale(Operator op, double quantity, Fuel &fuel, int day = 0, int month = 0, int year = 0) : Operator(op),
                                                                                               Fuel(fuel) {
        this->quantity = quantity;
        date = new Date(day, month, year);
    }

    Sale(const Sale &sale) : Operator(sale.surname, sale.name, sale.day, sale.month, sale.year),
                             Fuel(sale.type, sale.price) {
        quantity = sale.quantity;
        sum = sale.sum;
        date = sale.date;
    }

    void Show() override {
        printf("_______________________________________\n");
        CountSum();
        Fuel::Show();
        printf("Äàòà ïðîäàæó: ");
        date->Show();
        printf("Îáúåì = %.2fë., Ñóìà = %.2fãðí\n", quantity, sum);
        Operator::Show();
    }
};

class DayBalance : public virtual Date {
    list<Sale> sales;
public:
    DayBalance() : Date(0, 0, 0) {

    }

    DayBalance(int day, int month, int year) : Date(day, month, year) {

    }

    void Add(Sale new_sale) {
        sales.push_back(new_sale);
    }

    void Show() override {
        printf("\tCïèñîê îïåðàö³é ïðîäàæó íà ");
        Date::Show();
        list<Sale>::iterator it = sales.begin();
        for (it; it != sales.end(); ++it) {
            if (!sales.empty())
                it->Show();
        }
    }
};

int main() {
//    SetConsoleOutputCP(1251);
//    SetConsoleCP(1251);


    cout << "\n\t\t***Date.Show() ïðèêëàä:" << endl;
    Date date(1, 2, 3);
    date.Show();

    cout << endl << "\n\t\t***Fuel.Show() ïðèêëàä:" << endl;
    Fuel fuel_92(AI92, 23.4);
    Fuel fuel_95(AI95, 28.3);
    fuel_92.Show();

    cout << endl << "\n\t\t***Operator.Show() ïðèêëàä:" << endl;
    Operator op1("Ïð³çâèùå", "²ì'ÿ", 1, 2, 1993);
    Operator op2("²âàíîâ", "²âàí", 12, 12, 1987);
    op1.Show();

    cout << endl << "\n\t\t***Sale.Show() ïðèêëàä:" << endl;
    Sale sal(op1, 3.2f, fuel_92, 1, 2, 2019);
    Sale sal2(op2, 20.5f, fuel_95, 1, 2, 2019);
    sal.Show();

    cout << endl << "\n\t\t***DayBalance.Show() ïðèêëàä:" << endl;
    DayBalance db(1, 2, 2019);
    db.Add(sal);
    db.Add(sal2);
    db.Show();


    system("pause");
    return 0;
}