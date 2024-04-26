#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>
typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string &k) const
    {
        // Initialize w to zeros
        unsigned long long w[5] = {0, 0, 0, 0, 0};

        int index = k.size();
        for (int i = 4; i >= 0 && index > 0; i--)
        {                                          
            int endIndex = std::max(0, index - 6); 
            unsigned long long power = 1;          // Initialize the power of 36
            for (int j = index - 1; j >= endIndex; j--)
            {                                              
                w[i] += power * letterDigitToNumber(k[j]); 
                power *= 36;                               
            }
            index = endIndex; // Update the index for the next substring
        }

        HASH_INDEX_T result = 0;
        for (int i = 0; i < 5; i++)
        { 
            result += rValues[i] * w[i];
        }

        return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        if (std::isdigit(letter))
        {
            return letter - '0' + 26; //26-35
        }
        else
        {
            char letterCopy = std::tolower(letter);
            return letterCopy - 'a'; // 0-25
        }
    }
    
    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
