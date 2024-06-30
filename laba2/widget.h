#ifndef WIDGET_H
#define WIDGET_H

#ifndef MEDARRAY_H
#define MEDARRAY_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <QString>
#include <QDate>
#include <QMessageBox>
//med =item
//price=section
//speed=expiryDate

struct Widget {
    char model[35];
    char speed[8];
    char price[20];

    // Конструктор по умолчанию
   /* MedItem() : price(0.0), amount(0) {
        std::memset(model, 0, sizeof(model));
        std::memset(speed, 0, sizeof(speed));
        std::memset(price, 0, sizeof(price));
    }
    */
    bool operator==(const Widget& other) const {
        return std::strcmp(model, other.model) == 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Widget& item) {
        os << item.model << " " << item.speed << " " << item.price;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Widget& item) {
        is >> item.model >> item.speed >> item.price;
        return is;
    }
};

class WidgetA {
protected:
    std::vector<Widget> items;

public:
    std::vector<Widget>& GetW() {
        return items;
    }

    void WriteW(std::ostream& os) {
        for (const auto& item : items) {
            os << item << std::endl;
        }
    }

    void ReadW(std::istream& is) {
        Widget item;
        while (is >> item) {
            items.push_back(item);
        }
    }

    /*void SortMeds() {
        std::sort(meds.begin(), meds.end());
    }*/

};

#endif // MEDARRAY_H




























#endif // WIDGET_H
