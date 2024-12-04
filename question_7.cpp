#include <iostream>
#include <vector>
using namespace std;

void computeLPSArray(string pattern, vector<int> &lps) {
    int length = 0;  // Length of the previous longest prefix suffix
    int i = 1;
    lps[0] = 0;  // lps[0] is always 0

    cout << "Creating LPS array for pattern: " << pattern << "\n";
    cout << "LPS[0] = 0\n";

    while (i < pattern.size()) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            cout << "LPS[" << i << "] = " << length << " (length increased to " << length << ")\n";
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
                cout << "Mismatch at pattern[" << i << "] and pattern[" << length << "] - length updated to " << length << "\n";
            } else {
                lps[i] = 0;
                cout << "LPS[" << i << "] = 0\n";
                i++;
            }
        }
    }
}

// KMP algorithm to search for the pattern in the given text
void KMPSearch(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> lps(m);

    // Preprocess the pattern to create the LPS array
    computeLPSArray(pattern, lps);

    cout << "\nStarting KMP search for pattern: " << pattern << " in text: " << text << "\n";

    int i = 0;
    int j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            cout << "Characters match at text[" << i << "] and pattern[" << j << "] - advancing both\n";
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << i - j << "\n";
            j = lps[j - 1];
            cout << "Next comparison starts from pattern index " << j << "\n";
        } else if (i < n && pattern[j] != text[i]) {
            cout << "Mismatch at text[" << i << "] and pattern[" << j << "]\n";
            if (j != 0) {
                j = lps[j - 1];
                cout << "Pattern index updated to " << j << " based on LPS array\n";
            } else {
                cout << "Advancing text index to " << i + 1 << "\n";
                i++;
            }
        }
    }
}

int main() {
    string text = "ababcabcabababd";
    string pattern = "ababd";

    cout << "Text: " << text << "\n";
    cout << "Pattern: " << pattern << "\n";
    KMPSearch(text, pattern);

    return 0;
}
