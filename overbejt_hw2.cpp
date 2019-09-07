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

// Aliases
using namespace std;
using UsrMap = unordered_map<int, string>;

// Global variables
UsrMap users;

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
    
}  // End of the 'readGroups' method

/*
 * 
 */
int main(int argc, char** argv) {
    // Scrape users from passwd file
    readUsers();
    readGroups();
    return 0;
}  // End of main

