#include "Shanon.h"
#include "node.h"
#include <map>
#include <algorithm>
#include "huffman_code.h"
#include "huffman_tree_node.h"

int main()
{
    // Shanon
    std::string branch ="";
    std::string fullbranch ="";
    std::vector<std::string> symbols = {"a", "b", "c", "d", "e", "f", "g", "h"};
    std::vector<float> freq = {0.22, 0.18, 0.15, 0.13, 0.13, 0.09, 0.05, 0.05};

    // std::vector<float> freq3 = {0.4, 0.3, 0.2, 0.1};
    // std::vector<std::string> symbols3 = {"a", "b", "c", "d"};
    // Shanon test3(symbols3, freq3);
    // test3.SearchTree(branch, fullbranch,0, test3.getSize()-1);

    std::vector<std::string> symbols2 = {"a", "b"};
    std::vector<float> freq2 = {0.8, 0.2};
    Shanon test(symbols, freq);
    std::cout << "Shanon SearchedForOneChar: " << std::endl;
    test.SearchTree(branch, fullbranch,0, test.getSize()-1);
    test.ShanonThree(symbols2, freq2);
    std::cout << "Shanon SearchedForThreeChar: " << std::endl;
    test.SearchTree(branch, fullbranch,0, test.getSize()-1);
    test.PrintAll();

    //Huffman
    std::cout << "Huffman SearchedForThreeChar: " << std::endl;
    huffman_code hufftest;
    hufftest.HuffmanWork(symbols2, freq2);
}
