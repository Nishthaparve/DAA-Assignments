#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    string name;
    double weight;
    double value;
    double ratio;
    bool divisible;
};

// Compare items based on value/weight ratio
bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

int main() {

    vector<Item> items = {
        {"Medicine", 10, 100, 0, false},
        {"Drinking Water", 20, 120, 0, true},
        {"Food", 30, 150, 0, true},
        {"Medical Kit", 15, 180, 0, false},
        {"Blankets", 25, 100, 0, true}
    };

    double W = 50;

    // Calculate utility per kilogram
    for (int i = 0; i < items.size(); i++) {
        items[i].ratio = items[i].value / items[i].weight;
    }

    // Sort according to utility/weight ratio
    sort(items.begin(), items.end(), compare);

    double remainingWeight = W;
    double totalValue = 0;

    cout << "RELIEF SUPPLY SELECTION\n";
    cout << "-------------------------------------------------------------\n";

    cout << "Item              Weight       Value       Ratio       Selected\n";

    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < items.size(); i++) {

        if (remainingWeight <= 0)
            break;

        // Take complete item
        if (items[i].weight <= remainingWeight) {

            remainingWeight -= items[i].weight;
            totalValue += items[i].value;

            cout << items[i].name << "          "
                 << items[i].weight << "          "
                 << items[i].value << "          "
                 << items[i].ratio << "          "
                 << items[i].weight << endl;
        }

        // Take fraction if item is divisible
        else if (items[i].divisible) {

            double fraction = remainingWeight / items[i].weight;

            double selectedValue = fraction * items[i].value;

            totalValue += selectedValue;

            cout << items[i].name << "          "
                 << remainingWeight << "          "
                 << selectedValue << "          "
                 << items[i].ratio << "          "
                 << remainingWeight << " kg (fraction)"
                 << endl;

            remainingWeight = 0;
        }

        // Cannot divide this item
        else {
            continue;
        }
    }

    cout << "-------------------------------------------------------------\n";

    cout << "Boat Capacity: " << W << " kg" << endl;
    cout << "Remaining Capacity: " << remainingWeight << " kg" << endl;
    cout << "Maximum Utility Value: " << totalValue << endl;

    return 0;
}