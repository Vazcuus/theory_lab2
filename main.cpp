#include "Shanon.h"
#include "node.h"
#include <map>
#include <cmath>
#include <vector>
#include <algorithm>



class Shanon 
{
    private:
        std::vector<char> symbols;
        std::vector<float> freq;
        
    public:
        Shanon (){};
        Shanon (std::vector<char> _symbols, std::vector<float> _freq)
        {
            // for (size_t i = 0; i < freq.size(); i++)
            // {
            //     symbAndfreq.push_back(std::make_pair(_symbols[i], _freq[i]));
            // }
            symbols = _symbols;
            freq = _freq;
        }
        // void SortByFreq()
        // {
        //     std::sort(symbAndfreq.begin(), symbAndfreq.end(), 
        //       [](const std::pair<char, float>& a, const std::pair<char, float>& b) { return a.second > b.second; });
        // }
        // void PrintVector()
        // {
        //     for (const auto& pair : symbAndfreq) 
        //     {
        //         std::cout << pair.first << ": " << pair.second << '\n';
        //     }
        // }
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

};


int main()
{
    std::string branch ="";
    std::string fullbranch ="";
    std::vector<char> symbols = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    std::vector<float> freq = {0.22, 0.18, 0.15, 0.13, 0.13, 0.09, 0.05, 0.05};
    Shanon test(symbols, freq);
    std::cout << "Searched: " << std::endl;
    test.SearchTree(branch, fullbranch,0, 7);
}
