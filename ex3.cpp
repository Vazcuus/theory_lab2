#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
void get_frequencies(const std::string& text, int block_size, std::map<std::string, int>& frequencies) {
    for (size_t i = 0; i <= text.size() - block_size; i+=block_size) {
        std::string block = text.substr(i, block_size);
        if (frequencies.find(block) == frequencies.end()) {
            frequencies[block] = 0;
        }
        frequencies[block]++;
    }
}

template<typename K, typename V>
std::multimap<V, K, std::greater<int>> sort_map_by_value(std::map<K, V>& m) {
    std::multimap<V, K, std::greater<int>> mm;
    for (auto& p : m) {
        mm.insert({p.second, p.first});
    }
    return mm;
}

double calculate_entropy(const std::map<std::string, double>& probabilities) {
    double entropy = 0.0;
    for (const auto& p : probabilities) {
        entropy -= p.second * log2(p.second);
    }
    return entropy;
}

double calculate_redundancy(double max_entropy, double entropy) {
    return (max_entropy - entropy) / max_entropy;
}

int main()
{
    std::ifstream text("en_text.txt");
    std::string temp;
    std::string content;
    while(std::getline(text, temp))
    {
        content+=temp;
    }
    std::cout << content;

    std::map<std::string, int> frequencies_1, frequencies_2, frequencies_3, frequencies_4, frequencies_5;
    get_frequencies(content, 1, frequencies_1);
    get_frequencies(content, 2, frequencies_2);
    get_frequencies(content, 3, frequencies_3);
    get_frequencies(content, 4, frequencies_4);
    get_frequencies(content, 5, frequencies_5);
    
    std::vector<std::map<std::string, int>> vector_maps = {frequencies_1, frequencies_2, frequencies_3, frequencies_4, frequencies_5};
    std::cout << std::endl;
    for (int i =0; i < 5; i++)
    {
        std::cout << "Blocks of " << i+1 << ": ";
        for (const auto& pair : vector_maps[i])
        {
            std::cout << pair.first << ": " << pair.second << " ";
        }
        std::cout << std::endl;
    }
    for (int i =0; i < 5; i++)
    {
        auto sorted_map = sort_map_by_value(vector_maps[i]);
        std::cout << "Blocks of " << i+1 << ": ";
        for (const auto& pair : sorted_map)
        {
            std::cout << pair.second << ": " << pair.first << " ";
        }
        std::cout << std::endl;
    }

    std::vector<double> entropies(5);
    std::vector<std::map<std::string, double>> probability_maps(5);

    for (size_t i = 0; i < 5; ++i) {
        size_t total_length = content.size()/(i+1) - i+1 + 1;
        for (const auto& pair : vector_maps[i]) {
            probability_maps[i][pair.first] = static_cast<double>(pair.second) / total_length;
        }
        entropies[i] = calculate_entropy(probability_maps[i]);
    }

    for (size_t i = 0; i < 5; ++i) {
        std::cout << "\nLength block: " << i+1 << ", Entropy: " << entropies[i] << std::endl;
        auto sorted_map = sort_map_by_value(probability_maps[i]);
        for (auto it = sorted_map.rbegin(); it != sorted_map.rend(); ++it) {
            std::cout << it->second << ": " << it->first << std::endl;
        }
    }
    std::cout << std::endl;
    std::vector<double> redundancies(5);
    std::vector<double> max_entropies = {log2(frequencies_1.size()), log2(frequencies_2.size()), log2(frequencies_3.size()), log2(frequencies_4.size()), log2(frequencies_5.size())};  // Максимальные энтропии для блоков разной длины

    for (int i =0; i < 5; i++)
    {
        max_entropies[i] = fabs(log2l(vector_maps[i].size()));
    }
    for (size_t i = 0; i < 5; ++i) {
        redundancies[i] = calculate_redundancy(max_entropies[i], entropies[i]);
        std::cout << "Surplus for block length " << i+1 << ": " << redundancies[i] << std::endl;
    }

}