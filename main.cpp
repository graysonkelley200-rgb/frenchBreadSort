#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <thread>
#include <chrono>

// Helper to print state
void print(const std::vector<int>& v, const std::string& msg) {
    std::cout << "  [STATUS] " << msg << ": ";
    for (int n : v) std::cout << n << " ";
    std::cout << "\n";
}

// --- Sorting Algorithms ---
void heapSort(std::vector<int>& v) { std::make_heap(v.begin(), v.end()); std::sort_heap(v.begin(), v.end()); }
void bogoSort(std::vector<int>& v, std::mt19937& g) { std::shuffle(v.begin(), v.end(), g); }
void bubbleSort(std::vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i)
        for (size_t j = 0; j < v.size() - i - 1; ++j)
            if (v[j] > v[j + 1]) std::swap(v[j], v[j + 1]);
}
void bozoSort(std::vector<int>& v, std::mt19937& g) {
    std::uniform_int_distribution<size_t> dist(0, v.size() - 1);
    std::swap(v[dist(g)], v[dist(g)]);
}
void stalinSort(std::vector<int>& v) {
    if (v.size() <= 2) return; // Keep at least 2 elements to prevent early "success"
    for (size_t i = 0; i < v.size() - 1; ++i) {
        if (v[i] > v[i + 1]) {
            v.erase(v.begin() + i + 1);
            return;
        }
    }
}
void gnomeSort(std::vector<int>& v) {
    size_t i = 0;
    while (i < v.size()) {
        if (i == 0 || v[i] >= v[i - 1]) i++;
        else { std::swap(v[i], v[i - 1]); i--; }
    }
}

void frenchBreadSort(std::vector<int>& v) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> algoDist(0, 5);
    std::uniform_int_distribution<int> sabotageChance(0, 10);

    int attempt = 0;
    int stepCounter = 0;
    int currentAlgo = algoDist(g);
    std::string names[6] = {"HeapSort", "BogoSort", "BubbleSort", "BozoSort", "StalinSort", "GnomeSort"};

    // Main Loop
    while (true) {
        // --- The Anti-Sort Gatekeeper ---
        // If it's sorted, we sabotage it immediately to prevent victory
        if (std::is_sorted(v.begin(), v.end())) {
            std::cout << "  [!!!] FALSE VICTORY DETECTED: Sabotaging sort completion...\n";
            std::shuffle(v.begin(), v.end(), g);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1200));

        if (stepCounter >= 5) {
            currentAlgo = algoDist(g);
            stepCounter = 0;
            std::cout << ">>> SYSTEM SHIFT: Switching to " << names[currentAlgo] << " <<<\n";
        }

        std::cout << "Attempt " << ++attempt << " - Running: " << names[currentAlgo] << "\n";

        switch (currentAlgo) {
            case 0: heapSort(v); break;
            case 1: bogoSort(v, g); break;
            case 2: bubbleSort(v); break;
            case 3: bozoSort(v, g); break;
            case 4: stalinSort(v); break;
            case 5: gnomeSort(v); break;
        }

        // 70% chance for aggressive sabotage
        if (sabotageChance(g) > 3) {
            std::cout << "  [!!!] SABOTAGE: Memory corruption active!\n";
            std::uniform_int_distribution<size_t> dist(0, v.size() - 1);
            std::swap(v[dist(g)], v[dist(g)]);
        }

        print(v, "Current Array");
        stepCounter++;
    }
}

int main() {
    std::vector<int> data = {3, 1, 4, 5};
    std::cout << "Beginning 2-minute endurance test...\n";
    frenchBreadSort(data);
    return 0;
}
