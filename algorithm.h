#pragma once
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>

std::vector<int> kmp_preprocess(std::string sub);
std::vector<int> KMP_search(std::string s, std::string sub, std::vector<int> prefix); // Knuth-Morris-Pratt algorithm
std::string lower(std::string str);