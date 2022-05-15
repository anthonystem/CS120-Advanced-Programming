#include "User.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/* ----- User class implementations ----- */

// Constructor
User::User() : Character(5, 0){
    score = 0;
    highScore = 0;
}

// Destructor
User::~User() = default;


// Getters
int User::getScore() {
    return score;
}

int User::getHighScore() {
    return highScore;
}

int User::getCoins() {
    return coinAmount;
}


// Setters
void User::setScore(int score) {
    this->score = score;
}

void User::setHighScore(int highScore) {
    this->highScore = highScore;
}

void User::setCoins(int coinAmount) {
    this->coinAmount = coinAmount;
}


// Class functions.
void User::increaseScore(int scoreDelta) {
    score += scoreDelta;
}
void User::increaseCoins(int coinIncrease) {
    coinAmount += coinIncrease;
}

void User::increaseHealth(int healthDelta) {
    health += healthDelta;
}

void User::decreaseCoins(int coinDecrease) {
    coinAmount -= coinDecrease;
}

vector<double> User::getTrajectory(double x, double y) {
    // Returns {0,0} since the user does not move.
    return {0,0};
}

int User::fetchHighScore(string file) {
    fstream inputFile;
    inputFile.open(file);

    // Check if file is bad.
    if(!inputFile || inputFile.peek() == EOF) {
        cout << "### Invalid Score File. Please Fix File Then Re-Run. Exiting..." << endl;
        exit(0);
    }

    // Get the score from the file.
    string scoreStr;
    inputFile >> scoreStr;

    // Check if the score is numeric/valid. If not, exit program.
    bool invalidFile = false;
    int i = 0;
    while (i < scoreStr.length() && !invalidFile) {
        if (!isdigit(scoreStr[i])) {
            cout << "Score Contains Illegal Characters. Setting High Score to 0." << endl;
            invalidFile = true;
        }
        ++i;
    }

    if (invalidFile) {
        highScore = 0;
    } else {
        highScore = stoi(scoreStr);
    }

    inputFile.close();

    return highScore;
}

bool User::save(string file) {
    ofstream outputFile;
    outputFile.open(file);
    bool saved = false;

    if (!outputFile) {
        cout << "### Invalid Score Save File." << endl;
    } else {
        // Write score to file.
        outputFile << highScore;
        saved = true;
    }

    // Close output.
    outputFile.close();

    return saved;
}