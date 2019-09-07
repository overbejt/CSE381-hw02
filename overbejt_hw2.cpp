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
    if (pswd.is_open()) {
        cout << "the file is open" << endl;
    }
    pswd.close();
}  // End of the 'readUsers' method

/*
 * 
 */
int main(int argc, char** argv) {
    // Scrape users from passwd file
    readUsers();
    return 0;
}  // End of main

