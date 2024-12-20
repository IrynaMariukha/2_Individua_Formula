#include <iostream>
#include <limits>
using namespace std;

void validateInput () {
    if (cin.fail()) {
        throw ("Invalid input");
    }
}

void check_n (int n) {
    if (n <= 1) {
        throw ("Invalid input. n must be an integer greater than 1");
    }
}

void check_b (double a, double b) {
    if (b < a) {
        throw ("Invalid input. b must be greater than a");
    }
}

void check_h (double h, double a, double b) {
    if (h < 0 && h > b - a) {
        throw ("Invalid input. Ensure h is non-negative and less than or equal to (b - a)");
    }
}

double x_less_than_6(int n, double x) { // x < 6
    double product = 1.0;
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n + 1; j++) {
            double numerator = (j * j) + (i * i);
            double denominator = (10 * x) + 1;
            if (denominator == 0) {
                cout << "Skipping due to division by 0 for x = " << x << endl;
                return -1;
            }
            sum += numerator / denominator;
        }
        product *= sum;
    }
    cout << "For x = " << x << " (x < 6), y = " << product << endl;
    return product;
}

double x_greater_equals_6(int n, double x) { // x >= 6
    double sum = 0.0; // Calculate the sum of x * i
    for (int i = 5; i < 7; i++) {
        sum += x * i;
    }
    double product = 1.0; // Calculate the product of (x - j) / (x + j)
    for (int j = 1; j < n; j++) {
        double denominator = x + j;
        if (denominator == 0) { // Check if denominator is zero (x == -j)
            cout << "Skipping due to division by 0 for x = " << x << endl;
            cout << "----------------------------------------" << endl;
            return -1;
        }
        product *= (x - j) / denominator;
    }
    cout << "For x = " << x << " (x >= 6), y = " << sum << endl;

    return sum - product;
}

double calculate_x(int n, double x) { // Main logic to calculate based on the value of x
    if (x < 6) {
        return x_less_than_6(n, x);
    }
    return x_greater_equals_6(n, x);
}

void clearInput() {
    // Clear the error flags on the input stream
    cin.clear();
    // Ignore the remaining input in the buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    char choice; // Variable to hold user choice for continuation
    do {
        cout << "***** Sigma Pi Function Calculator *****" << endl;
        cout << "The formula: \n(x < 6): Sig.i(0 ; n) * Pi.j(0; n + 1) -> ((j^2 + i^2)/(10x + 1)" << endl;
        cout << "(x >= 6): Sig.i(5;7) - Pi.j(1;n) -> ((x - j)/(x + j)" << endl;
        cout << "----------------------------------------" << endl;
        int n;
        double a, b, h;
        // CHECK N
        try {
            cout << "Enter value for n (integer > 1): ";
            cin >> n;
            validateInput();
            check_n(n);
        }
        catch (const char* exception) {
            cout << exception << endl;
            return -1;
        }
        catch (...) {
            cout << "Unknown error" << endl;
            return -2;
        }

        // CHECK A
        try {
            cout << "Enter value for a: ";
            cin >> a;
            validateInput();
        }
        catch (const char* exception) {
            cout << exception << endl;
            return -1;
        }
        catch (...) {
            cout << "Unknown error" << endl;
            return -2;
        }

        // CHECK B
        try {
            cout << "Enter value for b (b >= a): ";
            cin >> b;
            validateInput();
            check_b(a, b);
        }
        catch (const char* exception) {
            cout << exception << endl;
            return -1;
        }
        catch (...) {
            cout << "Unknown error" << endl;
            return -2;
        }

        // CHECK H
        try {
            cout << "Enter value for h (non-negative and less than or equal to b - a): ";
            cin >> h;
            validateInput();
            check_h(h, a, b);
        }
        catch (const char* exception) {
            cout << exception << endl;
            return -1;
        }
        catch (...) {
            cout << "Unknown error" << endl;
            return -2;
        }

        double totalSum = 0.0;
        if (h == 0) { // Special case: when h = 0, calculate only for x = a
            cout << "----------------------------------------" << endl;
            cout << "h = 0 detected. Only calculating for x = " << a << "." << endl;
            double result = calculate_x(n, a);
            if (result != -1) {
                totalSum = result;
            }
            else {
                cout << "----------------------------------------" << endl;
                cout << "Skipping x = " << a << " due to calculation error." << endl;
            }
        }
        else {
            // Loop over the range of x, from a to b with step size h
            for (double x = a; x <= b; x += h) {                                                    // NOLINT(*-flp30-c)
                double result = calculate_x(n, x);
                // If an error occurred (result == -1), skip this x value
                if (result == -1) {
                    cout << "----------------------------------------" << endl;
                    cout << "Skipping x = " << x << " due to error." << endl;
                    continue; // Skip this iteration
                }
                totalSum += result; // Add the result to the cumulative sum
            }
        }
        cout << "----------------------------------------" << endl;
        cout << "The total result after summing all x values is: " << totalSum << endl;
        // Ask the user if they want to run the program again
        cout << "----------------------------------------" << endl;
        cout << "Do you want to run the program again? (y/n): ";
        cin >> choice;
        cout << "----------------------------------------" << endl;
    } while (choice == 'y' || choice == 'Y'); // Continue if user chooses 'y' or 'Y'
}
