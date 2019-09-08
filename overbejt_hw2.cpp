/* 
 * File:   overbejt_hw2.cpp
 * Author: Josh Overbeck
 * Class: CSE 381 Systems II
 * Assignment: Homework 2
 *
 * Created on September 7, 2019, 9:20 AM
 * Copyright (c) 2019 overbejt@miamioh.edu
 */

#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <utility>

/*
 * This is a nested class to help stick with the OOP principles.  It will serve
 * as a group object later on.
 */
class Group {
// Aliases
using GroupMembers = std::vector<int>;

// Access modifiers
private:
    // Attributes
    int gID;
    std::string grpName;
    GroupMembers members;
    
public:
    Group(){};  // Constructor
    ~Group(){};  // Destructor
    
    // Getters ----------------------
    int getGID() {
        return gID;
    }  // End of the 'getGID' method
    
    std::string getGrpName() {
        return grpName;
    }  // End of the 'getGrpName' method
    
    GroupMembers getGrpMembers() {
        return members;
    }  // End of the 'getGrpMembers' method
    
    // Setters ----------------------
    void setGID(int gID) {
        this->gID = gID;
    }  // End of the 'setGID' method
    
    void setGrpName(std::string gName) {
        grpName = gName;
    }  // End of the 'setGrpName' method
    
    void addGroupMember(int uId) {
        members.push_back(uId);
    }  // End of the 'addGroupMember' method
};  // End of the 'Group' class -----------------------------------------------

// Aliases
using namespace std;
using UsrMap = unordered_map<int, string>;
using GroupsMap = unordered_map<int, Group>;
using GroupMembers = std::vector<int>;

// Global variables
UsrMap users;
GroupsMap groups;

/*
 * This is the method that will read the passwd file and put all of the users 
 * into an unorderd map.
 */
void readUsers() {
    ifstream pswd("passwd");
    string line;
    
    if (pswd.is_open()) {
        while (getline(pswd, line)) {
            // Tokenize the line
            replace(line.begin(), line.end(), ':', ' ');
            
            // Parse out the login ID and UID
            istringstream is(line);            
            string loginId, unused;
            int uid;
            is >> loginId >> unused >> uid;            
            users.insert({uid, loginId});
//            for (auto i : users) {
//                cout << "UID: " << i.first;
//                cout << "\tlogin ID: " << i.second;
//                cout << endl;
//            }
        }
    }
    pswd.close();
}  // End of the 'readUsers' method

/**
 * This is the method that will the groups file and put all of the groups in an
 * unordered map.
 */
void readGroups() {
    ifstream grpFile("groups");
    string line;
    
    if (grpFile.is_open()) {
        while (getline(grpFile, line)) {
            // Tokenize the line
            replace(line.begin(), line.end(), ':', ' ');
            
            // Parse out the group name, GID, and users list
            istringstream is(line);            
            string grpName, unused, uid_line;
            int gid;
            is >> grpName >> unused >> gid >> uid_line;
            
            // Create a new group and initialize all the states
            Group nextGroup;
            nextGroup.setGrpName(grpName);
            nextGroup.setGID(gid);
            
            // Tokenize uid_line and add the users to the group
            replace(uid_line.begin(), uid_line.end(), ',', ' ');
//            cout << uid_line << endl;  // Debugging
            istringstream ss(uid_line); 
            int nextUsr;
            while (ss >> nextUsr) {
//                cout << nextUsr << endl;
                nextGroup.addGroupMember(nextUsr);
            }
            
            // Add the group to the map
            groups.insert({nextGroup.getGID(), nextGroup});
        }
    }
    grpFile.close();
}  // End of the 'readGroups' method

/*
 * 
 */
int main(int argc, char** argv) {
    // Scrape users from passwd file
    readUsers();
    // Scrape groups from groups file
    readGroups();
    // Testing %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//    for (auto i : groups) {
//        cout << i.first << " = " << i.second.getGrpName() << ": ";
//        GroupMembers members = i.second.getGrpMembers();
//        for (const auto j : members) {
//            auto usr = users.find(j);
//            cout << usr->second << "(" << j << ") ";
//        }
//        cout << endl;
//    }  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    // Process user input
    for (int arg = 1; arg < argc; arg++) {
        cout << argv[arg] << endl;
    }
    return 0;
}  // End of main

