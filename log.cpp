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

#include "log.h"

const char DELIMITER = ',';
const std::string FILE_NAME = "data/data.csv";
const std::string PROFESSION_FILE_NAME = "data/stat.csv";

// Utility Functions
std::string toLowercase(const std::string& s) {
    std::string lower = s;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

std::vector<std::string> splitString(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int stringToInt(const std::string& str) {
  try {
    return stoi(str);
  } catch (const std::invalid_argument& e) {
    
    return std::numeric_limits<int>::min(); 
  }
}

int highestNumberOfConnections(const std::string& line, int& highest_number) {
  std::istringstream iss(line);
  std::string field;
  
  getline(iss, field, ',');

  getline(iss, field, ',');

  int value = stringToInt(field);
  highest_number = std::max(highest_number, value);

  return value;
}

std::string getUsername(const std::unordered_map<std::string, std::vector<std::string>>& connections) {
    std::string username;
    bool isValidUsername = false;
    while (!isValidUsername) {
        std::cout << "Enter your username: ";
        std::getline(std::cin, username);
        username = toLowercase(username);
        if (connections.find(username) != connections.end()) {
            isValidUsername = true;
        } else {
            std::cout << "Username not found. Please try again." << std::endl;
        }
    }
    return username;
}

std::unordered_map<std::string, std::string> getProfessions(const std::string& fileName) {
    std::unordered_map<std::string, std::string> professions;
    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::vector<std::string> parts = splitString(line, DELIMITER);
            if (parts.size() > 1) {
                professions[toLowercase(parts[0])] = parts[1];
            }
        }
        file.close();
    } else {
        std::cout << "Error opening file" << std::endl;
    }
    return professions;
}

std::unordered_map<std::string, std::tuple<std::string, std::string>> getProfessionsWithEmail(const std::string& filename) {
    std::unordered_map<std::string, std::tuple<std::string, std::string>> professionsWithEmail;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::vector<std::string> parts = splitString(line, DELIMITER);
            if (parts.size() > 2) {
                std::string lowercaseName = toLowercase(parts[0]);
                std::string profession = parts[1];
                std::string email = parts[2];
                professionsWithEmail[lowercaseName] = make_tuple(profession, email); 
            } 
        }
        file.close();
    } else {
        std::cout << "Error opening file" << std::endl;
    }

    return professionsWithEmail;
}

std::vector<std::string> getUserFriends(const std::unordered_map<std::string, std::vector<std::string>>& connections, const std::string& username) {
    auto it = connections.find(username);
    if (it != connections.end()) {
        return it->second;
    } else {
        return {};
    }
}

bool askYesNoQuestion(const std::string& prompt) {
    std::string choice;
    std::cout << prompt << " (y/n): ";
    std::cin >> choice;
    std::cin.ignore();
    choice = toLowercase(choice);
    while (choice != "y" && choice != "n") {
        std::cout << "Invalid input. Please enter (y/n): ";
        std::cin >> choice;
        std::cin.ignore();
        choice = toLowercase(choice);
    }
    return choice == "y";
}

void displayPeopleInUserProfession (const std::string& userProfession, const std::unordered_map<std::string, std::string>& professions) {
    std::cout << "People in your profession (" << userProfession << "): " << std::endl;
    for (const auto& pair : professions) {
        if (pair.second == userProfession) {
            std::cout << "- " << pair.first << std::endl;
        }
    }
    std::cout << std::endl;
}

void displayEmailsInUserProfession(const std::string& userProfession, const std::unordered_map<std::string, std::tuple<std::string, std::string>>& professionsWithEmail) {
    std::cout << "Email addressed of people in your profession: " << std::endl;
    for (const auto& person : professionsWithEmail) {
        std::string profession = std::get<0>(person.second);
        std::string email = std::get<1>(person.second);
        if (profession == userProfession) {
            std::cout << " - " << person.first << " : " << email << std::endl;
        }
    }
    std::cout << std::endl;
}

void displayProfessions(const std::vector<std::string>& professions) {
    std::unordered_set<std::string> displayedProfessions;
    std::vector<std::string> uniqueProfessions;

    std::cout << "Professions: " << std::endl;
    for (const auto& profession : professions) {
        if (displayedProfessions.find(profession) == displayedProfessions.end()) {
            uniqueProfessions.push_back(profession);
            displayedProfessions.insert(profession);
        }
    }

    sort(uniqueProfessions.begin(), uniqueProfessions.end());

    std::cout << "Professions: " << std::endl;
    for (const auto& profession : uniqueProfessions) {
        std::cout << "- " << profession << std::endl;
    }
    std::cout << std::endl;
}

std::unordered_map<std::string, std::vector<std::string>> getSkillToPeopleMap(const std::string& fileName) {
    std::unordered_map<std::string, std::vector<std::string>> skillToPeople;
    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> parts = splitString(line, DELIMITER);
            if (parts.size() > 1) {
                std::string name = parts[0];
                std::string skill = parts[1];
                skillToPeople[toLowercase(skill)].push_back(name);
            }
        }
        file.close();
    } else {
        std::cout << "Error opening file" << std::endl;
    }
    return skillToPeople;
}

void displayPeopleWithSkills(const std::unordered_map<std::string, std::vector<std::string>>& skillToPeople) {
    std::string skill;
    while (true) {
        std::cout << "List names in skill: (type 'exit' to stop)";
        getline(std::cin, skill);
        skill = toLowercase(skill);
        if (skill == "exit") {
            break;
        }

        auto it = skillToPeople.find(skill);
        if (it != skillToPeople.end()) {
            const std::vector<std::string>& people = it->second;
            if (!people.empty()) {
                std::cout << "People with skill '" << skill << "' : " << std::endl;
                for (const auto& person : people) {
                    std::cout << "- " << person << std::endl;
                }
            } else {
                std::cout << "No people found with '" << skill << "'" << std::endl;
            }
        } else {
            std::cout << "Skill '" << skill << "' not found." << std::endl;
        }

        if (!askYesNoQuestion("Would you like to search under another skill?> ")) {
            break;
        }
    }
}

int askNumberOfNamesToDisplay(int total) {
    int count;
    std::cout << "How many names would you like to display out of " << total << "? ";
    std::cin >> count;
    std::cin.ignore();
    while (count < 1 || count > total) {
        std::cout << "Invalid input. Please enter a number between 1 and " << total << ": ";
        std::cin >> count;
        std::cin.ignore();
    }
    return count;
}

void displayNamesList(const std::vector<std::string>& names, const std::unordered_map<std::string, std::string>& professions, int count) {
    std::cout << "Displaying " << count << " out of " << names.size() << " names: " << std::endl;
    for (int i = 0; i < count && i < names.size(); ++i) {
        std::cout << "- " << names[i];
        auto it = professions.find(toLowercase(names[i]));
        if (it != professions.end()) {
            std::cout << " (" << it->second << ")";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void searchAndDisplayConnections(const std::unordered_map<std::string, std::vector<std::string>>& connections, const std::vector<std::string>& friends, const std::string& username) {
    while (true) {
        std::string input;
        std::cout << "Who do you want to find? (Type 'exit' to quit) > ";
        getline(std::cin, input);
        if (input == "exit") {
            break;
        }
        input = toLowercase(input);

        std::unordered_map<std::string, std::string> path;
        std::queue<std::string> toVisit;
        bool found = false;

        for (const auto& friendName : friends) {
            toVisit.push(toLowercase(friendName));
            path[toLowercase(friendName)] = username;
        }

        while (!toVisit.empty() && !found) {
            std::string current = toVisit.front();
            toVisit.pop();

            if (current == input) {
                std::cout << "Person Found: " << input << std::endl;
                found = true;
                break;
            }

            if (connections.find(current) != connections.end()) {
                for (const auto& friendOfFriend : connections.at(current)) {
                    std::string lowerFOF = toLowercase(friendOfFriend);
                    if (path.find(lowerFOF) == path.end()) {
                        toVisit.push(lowerFOF);
                        path[lowerFOF] = current;
                    }
                }
            }
        }

        if (found) {
            std::string current = input;
            std::cout << "Path from " << username << " to " << input << ": ";
            while (current != username) {
                std::cout << current;
                current = path[current];
                if (current != username) {
                    std::cout << " -> ";
                }
            }
            std::cout << " -> " << username << std::endl;
        } else {
            std::cout << "Name not found in your friends list or any level of your friends' connections." << std::endl;
        }

        if (!askYesNoQuestion("Would you like to search again?")) {
            break;
        }
    }
}