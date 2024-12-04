#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int comparisons = 0; // Global variable to keep track of comparisons

// Function to swap two elements
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function to place pivot elment in its correct position
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    cout << "Partitioning with pivot " << pivot << " at index " << high << "\n";

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Function to select a random pivot and partition the array
int randomized_partition(int arr[], int low, int high) {
    int random_index = low + rand() % (high - low + 1);
    swap(arr[random_index], arr[high]);
    return partition(arr, low, high);
}

// Quick Sort function
void randomized_quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pivot_index = randomized_partition(arr, low, high);
        cout << "\nPivot placed at index " << pivot_index << "\n";
        randomized_quick_sort(arr, low, pivot_index - 1);
        randomized_quick_sort(arr, pivot_index + 1, high);
    }
}

int main() {
    srand(time(0)); 

    int arr[] = {34, 7, 23, 32, 5, 62, 32, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Print the input array
    cout << "Input array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    // Sort the array
    randomized_quick_sort(arr, 0, n - 1);

    // Printing  the finl sorted array
    cout << "\nSorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    cout << "Number of comparisons: " << comparisons << "\n";

    return 0;
}
