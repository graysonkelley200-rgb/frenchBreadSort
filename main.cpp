#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

// Global controller variables
int attempt = 0;
int currentAlgo = 0;
std::string names[6] = {"HeapSort", "BogoSort", "BubbleSort", "BozoSort", "StalinSort", "GnomeSort"};
std::mt19937 g(std::random_device{}());

// --- The "Movement Detector" ---
// Every time a number moves, this triggers a new attempt and a new algorithm
void reportChange(std::vector<int>& v) {
    attempt++;
    std::uniform_int_distribution<int> algoDist(0, 5);
    currentAlgo = algoDist(g);

    std::cout << "[ATTEMPT " << attempt << "] Movement detected! Switching to: " << names[currentAlgo] << "\n";
    std::cout << "  Status: ";
    for (int n : v) std::cout << n << " ";
    std::cout << "\n";
}

// --- Atomic Operations ---
void moveElement(std::vector<int>& v, size_t i, size_t j) {
    if (i != j) {
        std::swap(v[i], v[j]);
        reportChange(v);
    }
}

void purgeElement(std::vector<int>& v, size_t i) {
    v.erase(v.begin() + i);
    reportChange(v);
}

// --- Sorting Algorithms (Now using Atomic Ops) ---
void bogoSort(std::vector<int>& v) {
    std::uniform_int_distribution<size_t> d(0, v.size() - 1);
    moveElement(v, d(g), d(g));
}

void bubbleSort(std::vector<int>& v) {
    for (size_t i = 0; i < v.size() - 1; ++i) {
        if (v[i] > v[i + 1]) moveElement(v, i, i + 1);
    }
}

void stalinSort(std::vector<int>& v) {
    for (size_t i = 0; i < v.size() - 1; ++i) {
        if (v[i] > v[i + 1]) {
            purgeElement(v, i + 1);
            return;
        }
    }
}

void frenchBreadSort(std::vector<int>& v) {
    std::cout << "Starting high-entropy FrenchBreadSort...\n";
    while (!std::is_sorted(v.begin(), v.end())) {
        switch (currentAlgo) {
            case 0: bogoSort(v); break; // Simple move-based
            case 1: bubbleSort(v); break;
            case 2: stalinSort(v); break;
            case 3: bogoSort(v); break; // Fallback
            case 4: bubbleSort(v); break;
            case 5: stalinSort(v); break;
        }
    }
    std::cout << "SUCCESS! Sorted in " << attempt << " attempts.\n";
}

int main() {
    std::vector<int> data = {3, 1, 4, 2132, 128, 64, 54, 127};
    frenchBreadSort(data);
    return 0;
}
