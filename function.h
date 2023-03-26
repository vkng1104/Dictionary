#pragma once
#include "config.h"
#include <sstream>
#include <filesystem>
#include <chrono>
#include <ctime>

/*		searching function		*/
std::vector<std::string> search(int x, std::string s, bool fl1, bool fl2);
bool isWord(std::string s);
int random();

// below are 3 functions supporting for searching a definition

std::string process_a_definition(nTrie* head, std::string res, int level, std::ifstream& fin, std::vector<std::string> def, 
								 bool& flag, std::vector<std::pair<int, std::pair<std::string, bool>>>& vec);
int MAXcompatible(std::string s, std::vector<std::string> def);
int compatible(std::string s, std::vector<std::string> def);

/*		quiz function		*/
std::vector<std::pair<std::string, std::vector<std::string>>> create_quiz(bool fl1,
                                                                          bool fl2);
// fl1: 0 for word, 1 for definition ---- fl2: 0 for Eng, 1 for Viet

std::pair<std::string, std::vector<std::string>> randomWord();
std::vector<std::string> extract_meaning(std::string s);



