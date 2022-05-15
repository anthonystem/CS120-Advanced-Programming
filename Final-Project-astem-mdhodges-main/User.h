/**
 * A class that represents a User.
 * Extends the Character class.
 */
#ifndef USER_H
#define USER_H

#include "Character.h"
#include <fstream>
#include <string>

using std::string;

class User : public Character {
private:
    int score;
    int highScore;
    int coinAmount;
public:
    User();
    ~User();
    int getScore();
    int getHighScore();
    int getCoins();
    void setScore(int score);
    void setHighScore(int highScore);
    void setCoins(int coinAmount);
    void increaseScore(int scoreDelta);
    void increaseCoins(int coinIncrease);
    void increaseHealth(int healthDelta);
    void decreaseCoins(int coinDecrease);
    vector<double> getTrajectory(double x, double y) override;

    /**
     * Fetches the high score from the save file.
     *
     * @param file - a string; the save file holding the high score.
     * @return an integer; the high score.
     */
    int fetchHighScore(string file);

    /**
     * Saves the high score to a file.
     *
     * @param file - a string; the file the high score will be written to.
     * @return a boolean; true if the save was successful; false if not successful.
     */
    bool save(string file);
};


#endif //GRAPHICS_JEOPARDY_USER_H
