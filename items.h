#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include "algorithm.h"

const int MAX = 32;
const std::string others = "-. ',/";

int other(char x);

class nTrie
{
public:
    nTrie *next[MAX];
    bool end;
    std::string definition[3]; // def[0] = "English"; def[1] = "Vietnamese"; def[3] = phonetic
    nTrie();
    bool empty();
};

class Trie
{
public:
    nTrie *root = NULL;
    Trie();

    // function is used to check if a word is already in dictionary or not and add it into the dictionary (for add_window.ui)
    bool check_and_add(std::string s, std::string meaning, std::string phonetic, std::string type);

    // main function
    void add(std::string s, std::string meaning, std::string phonetic, std::string type);
    std::string edit(std::string s, std::string meaning, std::string phonetic, std::string type);
    bool toRemove(nTrie *f_root, std::string s, int level, int len); // len = s.length()
    std::string remove(std::string s);
    bool find(std::string s, std::vector<std::string> &related); // function supporting search
    std::vector<std::string> search(std::string s, bool fl1, bool fl2);
    void save(std::string file);
    void saveToFile(nTrie *head, std::ofstream &fout, int level, std::string file); // function supporting save function
    void load(std::string file);
    std::string separate_data(nTrie *head, std::string s, int level, std::ifstream &fin); // function supporting load function
};

// Function supporting searching a word
void meaning(std::string s, std::vector<std::string> &ans); // get the meaning of the word
void continue_to_search(nTrie *root, std::vector<std::string> &related, std::string res);
