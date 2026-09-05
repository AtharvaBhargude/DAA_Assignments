#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Structure to store one customer order
struct Order
{
    string orderID;
    string customerName;
    string foodItem;
    string category;
    string quantity;
    string price;
    string paymentMethod;
    string orderTime;
};


// Function to parse a CSV line
vector<string> parseCSVLine(string line)
{
    vector<string> result;
    string value;
    bool insideQuotes = false;

    for (char c : line)
    {
        if (c == '"')
        {
            insideQuotes = !insideQuotes;
        }
        else if (c == ',' && !insideQuotes)
        {
            result.push_back(value);
            value = "";
        }
        else
        {
            value += c;
        }
    }

    result.push_back(value);

    return result;
}


// Merge function
void merge(vector<Order>& orders,
           vector<Order>& temp,
           int left,
           int mid,
           int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    // Compare Order Time
    while (i <= mid && j <= right)
    {
        if (orders[i].orderTime <= orders[j].orderTime)
        {
            temp[k] = orders[i];
            i++;
        }
        else
        {
            temp[k] = orders[j];
            j++;
        }

        k++;
    }

    // Copy remaining elements from left half
    while (i <= mid)
    {
        temp[k] = orders[i];
        i++;
        k++;
    }

    // Copy remaining elements from right half
    while (j <= right)
    {
        temp[k] = orders[j];
        j++;
        k++;
    }

    // Copy sorted elements back to original vector
    for (int i = left; i <= right; i++)
    {
        orders[i] = temp[i];
    }
}


// Merge Sort function
void mergeSort(vector<Order>& orders,
               vector<Order>& temp,
               int left,
               int right)
{
    // Base condition
    if (left >= right)
    {
        return;
    }

    // Find middle
    int mid = left + (right - left) / 2;

    // Sort left half
    mergeSort(orders, temp, left, mid);

    // Sort right half
    mergeSort(orders, temp, mid + 1, right);

    // Merge sorted halves
    merge(orders, temp, left, mid, right);
}


// Function to read the CSV file
vector<Order> readCSV(string filename)
{
    vector<Order> orders;

    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Error: Cannot open CSV file!" << endl;
        return orders;
    }

    string line;

    // Skip the header row
    getline(file, line);

    // Read each row
    while (getline(file, line))
    {
        vector<string> data = parseCSVLine(line);

        if (data.size() == 8)
        {
            Order order;

            order.orderID = data[0];
            order.customerName = data[1];
            order.foodItem = data[2];
            order.category = data[3];
            order.quantity = data[4];
            order.price = data[5];
            order.paymentMethod = data[6];
            order.orderTime = data[7];

            orders.push_back(order);
        }
    }

    file.close();

    return orders;
}


// Display sorted orders
void displayOrders(const vector<Order>& orders)
{
    cout << "\nOrders After Sorting by Timestamp:\n\n";

    cout << "Order ID\tCustomer Name\tOrder Time\n";
    cout << "--------------------------------------------------\n";

    // Display all orders
    for (int i = 0; i < orders.size(); i++)
    {
        cout << orders[i].orderID << "\t\t"
             << orders[i].customerName << "\t\t"
             << orders[i].orderTime
             << endl;
    }
}


int main()
{
   
    string filename = "restaurant_orders.csv";

    // Read data from CSV
    vector<Order> orders = readCSV(filename);

    // Check if data was loaded
    if (orders.empty())
    {
        cout << "No data found in the CSV file!" << endl;
        return 1;
    }

    cout << "Total Orders Loaded: "
         << orders.size() << endl;

    // Create temporary vector for Merge Sort
    vector<Order> temp(orders.size());

    // Sort orders according to Order Time
    mergeSort(
        orders,
        temp,
        0,
        orders.size() - 1
    );

    cout << "\nOrders Sorted Successfully!" << endl;

    // Display sorted orders
    displayOrders(orders);

    return 0;
}
