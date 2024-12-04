#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to swap two elements
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function to place pivot element in its correct position
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    cout << "Partitioning with pivot " << pivot << " at index " << high << "\n";

    for (int j = low; j < high; j++) {
        cout << "Comparing arr[" << j << "] = " << arr[j] << " with pivot " << pivot << "\n";
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
            cout << "Swapping elements arr[" << i << "] and arr[" << j << "]: ";
            for (int k = low; k <= high; k++) {
                cout << arr[k] << " ";
            }
            cout << "\n";
        }
    }
    swap(arr[i + 1], arr[high]);
    cout << "Placing pivot in the correct position by swapping arr[" << (i + 1) << "] and arr[" << high << "]: ";
    for (int k = low; k <= high; k++) {
        cout << arr[k] << " ";
    }
    cout << "\n";

    return (i + 1);
}

// Function to select a random pivot and partition the array
int randomized_partition(int arr[], int low, int high) {
    int random_index = low + rand() % (high - low + 1);
    cout << "Randomly selecting pivot at index " << random_index << " with value " << arr[random_index] << "\n";
    swap(arr[random_index], arr[high]);
    return partition(arr, low, high);
}

// Randomized Select function to find the ith smallest element
int randomized_select(int arr[], int low, int high, int i) {
    if (low == high) {
        cout << "Only one element left: " << arr[low] << "\n";
        return arr[low];
    }

    int pivot_index = randomized_partition(arr, low, high);
    int k = pivot_index - low + 1;  // Number of elements in the left partition

    cout << "Pivot placed at index " << pivot_index << ", number of elements in left partition: " << k << "\n";

    if (i == k) {
        cout << "The " << i << "th smallest element is the pivot: " << arr[pivot_index] << "\n";
        return arr[pivot_index];
    } else if (i < k) {
        cout << "The " << i << "th smallest element is in the left subarray.\n";
        return randomized_select(arr, low, pivot_index - 1, i);
    } else {
        cout << "The " << i << "th smallest element is in the right subarray.\n";
        return randomized_select(arr, pivot_index + 1, high, i - k);
    }
}

int main() {
    srand(time(0)); // Seed for random number generation

    int arr[] = {34, 7, 23, 32, 5, 62, 32, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    // Printing  the inpit  array
    cout << "Input array: ";
    for (int j = 0; j < n; j++) {
        cout << arr[j] << " ";
    }
    cout << "\n";

    cout << "Enter the value of i (to find the ith smallest element): ";
    cin >> i;

    if (i < 1 || i > n) {
        cout << "Invalid input! i should be between 1 and " << n << ".\n";
    } else {
        int ith_smallest = randomized_select(arr, 0, n - 1, i);
        cout << "The " << i << "th smallest element is: " << ith_smallest << "\n";
    }

    return 0;
}
