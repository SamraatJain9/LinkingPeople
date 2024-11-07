#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <limits>
#include <tuple>
#include <algorithm>

std::string toLowercase(const std::string& s);
std::vector<std::string> splitString(const std::string& s, char delimiter);
int stringToInt(const std::string& str);
int highestNumberOfConnections(const std::string& line, int& highest_number);
std::string getUsername(const std::unordered_map<std::string, std::vector<std::string>>& connections);
std::unordered_map<std::string, std::string> getProfessions(const std::string& fileName);
std::unordered_map<std::string, std::tuple<std::string, std::string>> getProfessionsWithEmail(const std::string& filename);
std::vector<std::string> getUserFriends(const std::unordered_map<std::string, std::vector<std::string>>& connections, const std::string& username);
bool askYesNoQuestion(const std::string& prompt);
void displayPeopleInUserProfession(const std::string& userProfession, const std::unordered_map<std::string, std::string>& professions);
void displayEmailsInUserProfession(const std::string& userProfession, const std::unordered_map<std::string, std::tuple<std::string, std::string>>& professionsWithEmail);
void displayProfessions(const std::vector<std::string>& professions);
std::unordered_map<std::string, std::vector<std::string>> getSkillToPeopleMap(const std::string& fileName);
void displayPeopleWithSkills(const std::unordered_map<std::string, std::vector<std::string>>& skillToPeople);
int askNumberOfNamesToDisplay(int total);
void displayNamesList(const std::vector<std::string>& names, const std::unordered_map<std::string, std::string>& professions, int count);
void searchAndDisplayConnections(const std::unordered_map<std::string, std::vector<std::string>>& connections, const std::vector<std::string>& friends, const std::string& username);
