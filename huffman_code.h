#pragma once
#include "huffman_tree_node.h"
#include <string>
#include <iostream>
#include <queue>
#include <map>
#include <cmath>
#include <functional>

class huffman_code
{
    private:
        huffman_node *root;
        std::map<std::string,std::string> codes;
        std::vector<float> _odds;
        float length = 0;
        float entropy = 0;
        float surplus = 0;
    public:
        huffman_code (){};
        void HuffmanWork(std::vector<std::string> symbols, std::vector<float> odds);
        void SaveCodes(huffman_node *root, std::string str)
        {
            if (!root) return;
            
            if (root->ch != "%")
            {
                codes[root->ch] = str;
            }
            SaveCodes(root->left, str + "0");
            SaveCodes(root->right, str + "1");
        }

        bool Comparator(huffman_node *left, huffman_node *right)
        {
            return (left->odds > right->odds);
        };

        void PrintCodes(std::map<std::string, std::string> codes)
        {
            for (const auto& pair : codes)
            {
                std::cout << pair.first << ": " << pair.second;
                std::cout << std::endl;

            }
        }
        float PrintLength()
        {
            int i =0;
            for (const auto& pair : codes)
            {
                length += _odds[i++]*pair.second.size();
            }
            std::cout << "Length: " <<length << std::endl;
            return length;
        }
        float PrintEntropy()
        {
            int i =0;
            for (auto i = 0; i < _odds.size(); i++)
            {
                entropy += _odds[i]*log2(_odds[i]); // https://en.cppreference.com/w/cpp/numeric/math/log 
            }
            entropy = -entropy;
            std::cout << "Entropy: " << (float)entropy << std::endl; 
            return entropy;
        }
        float PrintSurplus()
        {
            std::cout << "Surplus: " << float(1 - (entropy)/(fabs(log2f((float)1/_odds.size())))) << std::endl;
            return (float)(1 - (entropy)/(abs(log2(1/_odds.size()))));
        }
};

void huffman_code::HuffmanWork(std::vector<std::string> symbols, std::vector<float> odds)
{
    huffman_node *left, *right, *top;

    std::priority_queue<huffman_node*, std::vector<huffman_node*>, std::function<bool(huffman_node*, huffman_node*)>> result([](huffman_node* left, huffman_node* right) {return left->odds > right->odds;} ); // look comparator

    for (int i = 0; i < symbols.size(); i++)
    {
        for (int j = 0; j < symbols.size(); j++)
        {
            for (int z = 0; z < symbols.size(); z++)
            {
                huffman_node* temp = new huffman_node(symbols[i]+symbols[j]+symbols[z], odds[i]*odds[j]*odds[z]);
                _odds.push_back(odds[i]*odds[j]*odds[z]);
                result.push(temp);
            }
        }
    }

    while (result.size() != 1)
    {
        left = result.top();
        result.pop();
        right = result.top();
        result.pop();

        top = new huffman_node("%", left->odds + right->odds); // {0.22, 0.18, 0.15, 0.13, 0.13, 0.1, 0,09};
        top->left = left;
        top->right = right;
        result.push(top);

    }
    root = result.top();
    SaveCodes(root, "");
    PrintCodes(codes);
    PrintLength();
    PrintEntropy();
    PrintSurplus();
    
}