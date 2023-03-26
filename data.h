#pragma once
#include <sstream>
#include "function.h"
#include "algorithm.h"
#include "HeaderS.h"

int processMeaning(std::string s); // all cases with meaning: n.  v.  adj.  adv.  abbr.  adv. & prep.  prep.

void processDatabase1(); // EngEngraw.txt
void processDatabase2(); // EngVietraw.txt

void loadData(Trie& trie, std::string file, std::string language);
void loadData2(Trie& trie, std::string file, std::string language);

bool isEmpty_file(std::string file);
void initialize();

// reset data
void resetData();
