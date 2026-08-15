#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Order {
    string order_id;
    string customer_id;
    string status;
    string timestamp;
};

// Merge function
void merge(vector<Order>& orders, int low, int mid, int high) {

    vector<Order> temp;

    int i = low;
    int j = mid + 1;

    // Compare timestamps
    while (i <= mid && j <= high) {

        if (orders[i].timestamp <= orders[j].timestamp) {
            temp.push_back(orders[i]);
            i++;
        }
        else {
            temp.push_back(orders[j]);
            j++;
        }
    }

    // Remaining elements from left
    while (i <= mid) {
        temp.push_back(orders[i]);
        i++;
    }

    // Remaining elements from right
    while (j <= high) {
        temp.push_back(orders[j]);
        j++;
    }

    // Copy back
    for (int k = 0; k < temp.size(); k++) {
        orders[low + k] = temp[k];
    }
}

// Merge Sort
void mergeSort(vector<Order>& orders, int low, int high) {

    if (low >= high)
        return;

    int mid = low + (high - low) / 2;

    mergeSort(orders, low, mid);
    mergeSort(orders, mid + 1, high);

    merge(orders, low, mid, high);
}

int main() {

    vector<Order> orders;

    // Open CSV file
    ifstream file("orders.csv");

    if (!file.is_open()) {
        cout << "File not found!" << endl;
        return 0;
    }

    string line;

    // Skip header
    getline(file, line);

    // Read dataset
    while (getline(file, line)) {

        stringstream ss(line);

        Order order;

        getline(ss, order.order_id, ',');
        getline(ss, order.customer_id, ',');
        getline(ss, order.status, ',');
        getline(ss, order.timestamp, ',');

        orders.push_back(order);
    }

    file.close();

    cout << "Total Orders: " << orders.size() << endl;

    // Apply Merge Sort
    if (!orders.empty()) {
        mergeSort(orders, 0, orders.size() - 1);
    }

    // Display output
    cout << "\n\n";
    cout << "SORTED CUSTOMER ORDERS\n";

     cout << "--------------------------------------------------------------------------------------------------------\n";

    cout << "Order ID                              Customer ID                           Status          Timestamp\n";

     cout << "--------------------------------------------------------------------------------------------------------\n";

    // Display first 10 orders
    int limit = orders.size();

    if (limit > 10)
        limit = 10;

    for (int i = 0; i < limit; i++) {

        cout << orders[i].order_id;

        // Spaces after Order ID
        for (int j = orders[i].order_id.length(); j < 38; j++)
            cout << " ";

        cout << orders[i].customer_id;

        // Spaces after Customer ID
        for (int j = orders[i].customer_id.length(); j < 38; j++)
            cout << " ";

        cout << orders[i].status;

        // Spaces after Status
        for (int j = orders[i].status.length(); j < 15; j++)
            cout << " ";

        cout << orders[i].timestamp << endl;
    }

    cout << "--------------------------------------------------------------------------------------------------------\n";

    return 0;
}