#pragma once
#include "items.h"
#include "HeaderS.h"

const int maxTrie = 5;

class config
{
public:
    static Trie tries;
    static const std::string savedFolder;
    static active_point* active;
    static node* root;
};
