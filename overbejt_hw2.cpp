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
            istringstream ss(uid_line); 
            int nextUsr;
            while (ss >> nextUsr) {
                nextGroup.addGroupMember(nextUsr);
            }
            
            // Add the group to the map
            groups.insert({nextGroup.getGID(), nextGroup});
        }
    }
    grpFile.close();
}  // End of the 'readGroups' method

/**
 * This is a helper method to print the indicated group to the screen.
 * 
 * @param groupID  The group ID number
 */
void printGroup(int groupID) {
    // Get the group from the groups map
    Group currentGroup = groups.find(groupID)->second;
    
    // Print group ID and group name
    cout << groupID << " = " << currentGroup.getGrpName() << ":";
    
    // Grab the group members and iterate them all, printing them to the screen.
    GroupMembers members = currentGroup.getGrpMembers();
    for (const auto memberID : members) {
        auto user = users.find(memberID);
        cout << " " << user->second << "(" << memberID << ")";
    }
    cout << endl;
}  // End of the 'printGroup' method

/*
 * 
 */
int main(int argc, char** argv) {
    // Scrape users from passwd file
    readUsers();
    // Scrape groups from groups file
    readGroups();

    // Process user input
    for (int i = 1; i < argc; i++) {        
        // Grab current group from user
        int currentGroup = atoi(argv[i]);
        auto group = groups.find(currentGroup);
        
        // Check if group exists and print results
        if (group == groups.end()) {
            cout << currentGroup << " = Group not found." << endl;
        } else {
            printGroup(currentGroup);
        }
    }
    return 0;
}  // End of main

