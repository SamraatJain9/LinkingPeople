//g++ Main.cpp Log.cpp -o test

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
#include "Log.h"


const char DELIMITER = ',';
const std::string FILE_NAME = "data/data.csv";
const std::string PROFESSION_FILE_NAME = "data/stat.csv";

//Main
int main() {
    std::ifstream file(FILE_NAME);
    std::unordered_map<std::string, std::vector<std::string>> connections;
    std::vector<std::string> allNames;
    std::unordered_map<std::string, std::string> professions = getProfessions(PROFESSION_FILE_NAME);
    std::unordered_map<std::string, std::tuple<std::string, std::string>> professionsWithEmail = getProfessionsWithEmail(PROFESSION_FILE_NAME);
    int highest_number = std::numeric_limits<int>::min();
    std::string personWithMostConnections;
    std::string emailOfPersonWithMostConnections;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> parts = splitString(line, DELIMITER);
            std::string name = parts[0];
            allNames.push_back(name);
            std::vector<std::string> knows(parts.begin() + 1, parts.end());
            connections[toLowercase(name)] = knows;
            int connectionsCount = highestNumberOfConnections(line, highest_number);
            if (connectionsCount == highest_number) {
                personWithMostConnections = name;
                auto it = professionsWithEmail.find(toLowercase(name));
                if (it != professionsWithEmail.end()) {
                    emailOfPersonWithMostConnections = std::get<1>(it->second);
                }
            }
        }
        file.close();
    } else {
        std::cout << "Error opening file." << std::endl;
        return 1;
    }

    if (highest_number == std::numeric_limits<int>::min()) {
        std::cout << "Invalid data reached." << std::endl;
    } else {
        std::cout << "\nHighest number of connections is: " << highest_number << std::endl;
        std::cout << "\nUsername with most connections: " << personWithMostConnections << " - ";
        if (!emailOfPersonWithMostConnections.empty()) {
            std::cout << "Email> " << emailOfPersonWithMostConnections << std::endl;
        } else {
            std::cout << "Email not found" << std::endl;
        }
    }

    std::string username = getUsername(connections);
    auto it = professions.find(username);
    std::string userProfession;
    if (it != professions.end()) {
        userProfession = it->second;
        std::cout << "Your Profession: " << userProfession << std::endl;
    } else {
        std::cout << "Profession not listed" << std::endl;
    }

    std::vector<std::string> userFriends = getUserFriends(connections, username);

    if (userFriends.empty()) {
        std::cout << "";
    } else {
        bool foundConnection = false;
        std::cout << "Your connections are: " << std::endl;
        for (const auto& friendName : userFriends) {
            if (friendName != "0") {
                std::cout << "- " << friendName;
                auto it = professions.find(toLowercase(friendName));
                if (it != professions.end()) {
                    std::cout << " (" << it->second << ")";
                }
                std::cout << std::endl;
                foundConnection = true;
            }
        }
        if (!foundConnection) {
            std::cout << "None Found" << std::endl;
        }
    }

    bool viewPeopleInProfession = askYesNoQuestion("Would you like to view people in your profession?");
    if (viewPeopleInProfession && !userProfession.empty()) {
        displayPeopleInUserProfession(userProfession, professions);
        if (!userProfession.empty()) {
            displayEmailsInUserProfession(userProfession, professionsWithEmail);
        }
    }

    bool displayProfessionsQuestion = askYesNoQuestion("Would you like to view the Skills list?");
    if (displayProfessionsQuestion) {
        std::vector<std::string> professionList;
        for (const auto& professionPair : professions) {
            professionList.push_back(professionPair.second);
        }
        displayProfessions(professionList);

        bool displayPeopleWithSkillsQuestion = askYesNoQuestion("Would like to view names of people with skills?");
        if (displayPeopleWithSkillsQuestion) {
            std::unordered_map<std::string, std::vector<std::string>> skillToPeople = getSkillToPeopleMap(PROFESSION_FILE_NAME);
            displayPeopleWithSkills(skillToPeople);
        }
    }

    bool displayNames = askYesNoQuestion("Would you like the names list?");
    if (displayNames) {
        int count = askNumberOfNamesToDisplay(allNames.size());
        displayNamesList(allNames, professions, count);
    }

    bool searchConnections = askYesNoQuestion("Would you like to find someone?");
    if (searchConnections) {
        searchAndDisplayConnections(connections, userFriends, username);
    }

    bool lastOption = askYesNoQuestion("Would you like to enter another user's username to search for someone?");
    if (lastOption) {
        std::string usernameOther = getUsername(connections);
        auto it = professions.find(usernameOther);
        std::string userProfession;
        if (it != professions.end()) {
            userProfession = it->second;
            std::cout << "User's Profession: " << userProfession << std::endl;
        } else {
            std::cout << "Profession not listed" << std::endl;
        }

        std::vector<std::string> usernameOtherFriends = getUserFriends(connections, usernameOther);

        if (usernameOtherFriends.empty()) {
            std::cout << "";
        } else {
            bool foundConnection = false;
            std::cout << "User's connections are: " << std::endl;
            for (const auto& friendName : usernameOtherFriends) {
                if (friendName != "0") {
                    std::cout << "- " << friendName;
                    auto it = professions.find(toLowercase(friendName));
                    if (it != professions.end()) {
                        std::cout << " (" << it->second << ")";
                    }
                    std::cout << std::endl;
                    foundConnection = true;
                }
            }
            if (!foundConnection) {
                std::cout << "None Found" << std::endl;
            }
        }

        bool viewPeopleInProfession = askYesNoQuestion("Would you like to view people in the user's profession?");
        if (viewPeopleInProfession && !userProfession.empty()) {
            displayPeopleInUserProfession(userProfession, professions);
            if (!userProfession.empty()) {
                displayEmailsInUserProfession(userProfession, professionsWithEmail);
            }
        }

        bool displayProfessionsQuestion = askYesNoQuestion("Would you like to view the Skills list?");
        if (displayProfessionsQuestion) {
            std::vector<std::string> professionList;
            for (const auto& professionPair : professions) {
                professionList.push_back(professionPair.second);
            }
            displayProfessions(professionList);

            bool displayPeopleWithSkillsQuestion = askYesNoQuestion("Would like to view names of people with skills?");
            if (displayPeopleWithSkillsQuestion) {
                std::unordered_map<std::string, std::vector<std::string>> skillToPeople = getSkillToPeopleMap(PROFESSION_FILE_NAME);
                displayPeopleWithSkills(skillToPeople);
            }
        }

        bool displayNames = askYesNoQuestion("Would you like the names list?");
        if (displayNames) {
            int count = askNumberOfNamesToDisplay(allNames.size());
            displayNamesList(allNames, professions, count);
        }

        bool searchConnections = askYesNoQuestion("Would you like to find someone?");
        if (searchConnections) {
            searchAndDisplayConnections(connections, usernameOtherFriends, usernameOther);
        }
    }

    return 0;
}