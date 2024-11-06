#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <map>
class Shanon 
{
    private:
        std::vector<std::string> symbols;
        std::vector<float> freq;
        std::map<std::string,std::string> codes;
        float length = 0;
        float entropy = 0;
        float surplus = 0;
    public:
        Shanon (){};
        Shanon(std::vector<std::string> _symbols, std::vector<float> _freq)
        {
            symbols = _symbols;
            freq = _freq;
        }
        int getSize()
        {
            return symbols.size();
        }
        void ShanonTwo(std::vector<std::string> _symbols, std::vector<float> _freq)
        {
            symbols.clear();
            freq.clear();
            for (auto i = 0; i < _symbols.size(); i++)
            {
                for (auto j = 0; j < _symbols.size(); j++)
                {
                    symbols.push_back(_symbols[i]+_symbols[j]);
                    freq.push_back(_freq[i]*_freq[j]);
                }
            }
        }
        void ShanonThree(std::vector<std::string> _symbols, std::vector<float> _freq)
        {
            symbols.clear();
            freq.clear();
            for (auto i = 0; i < _symbols.size(); i++)
            {
                for (auto j = 0; j < _symbols.size(); j++)
                {
                    for (auto z = 0; z < _symbols.size(); z++)
                    {
                        symbols.push_back(_symbols[i]+_symbols[j]+_symbols[z]);
                        freq.push_back(_freq[i]*_freq[j]*_freq[z]);
                    }
                }
            }
        }

        void SearchTree (std::string &branch, std::string &fullBranch, int start, int end)
        {
            double dS=0;
            double S=0;
            int i,m;
            std::string cBranch="";

            cBranch=fullBranch+branch;
            if (start==end)
            {
                std::cout << symbols[start] << " : " << cBranch << std::endl;
                codes[symbols[start]] = cBranch;
                return;
            }
            for (i=start;i<=end;i++)
                dS+=freq[i];
            dS/=2.;
            i=start+1;
            S+=freq[start];
            while (fabs(dS-(S+freq[i]))<fabs(dS-S) && (i<end))
            {
                S+=freq[i];
                i++;
            }
            std::string zero="0";
            std::string one="1";
            SearchTree(one,cBranch,start,i-1);
            SearchTree(zero,cBranch,i,end);
        }
        void PrintAll()
        {
            PrintLength();
            PrintEntropy();
            PrintSurplus();
            std::cout << std::endl;
        }
        float PrintLength()
        {
            int i =0;
            for (const auto& pair : codes)
            {
                length += freq[i++]*pair.second.size();
            }
            std::cout << "Length: " <<length << std::endl;
            return length;
        }
        float PrintEntropy()
        {
            int i =0;
            for (auto i = 0; i < freq.size(); i++)
            {
                entropy += freq[i]*log2(freq[i]); // https://en.cppreference.com/w/cpp/numeric/math/log 
            }
            entropy = -entropy;
            std::cout << "Entropy: " << (float)entropy << std::endl; 
            return entropy;
        }
        float PrintSurplus()
        {
            std::cout << "Surplus: " << float(1 - (entropy)/(fabs(log2f((float)1/freq.size())))) << std::endl;
            return (float)(1 - (entropy)/(abs(log2(1/freq.size()))));
        }

};