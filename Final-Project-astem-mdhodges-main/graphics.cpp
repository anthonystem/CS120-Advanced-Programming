#include "circle.h"
#include "graphics.h"
#include "Bullet.h"
#include "Enemy.h"
#include "User.h"
#include "Coin.h"
#include "Ability.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

GLdouble width, height;
int wd;
enum currentWindow {
    MENU,
    DIFFICULTY,
    GAME,
    DEATH,
    PAUSE
};
enum difficulty {
    SELECT,
    WIMPY,
    TYPICAL,
    HARDENED,
};
currentWindow curr = MENU;
difficulty difficultyChoice;
string currentAbility;
double pointMultiplier;
vector<Ability> currAbilities;
int dummyTemp = 0;
User user;
int xPos;
int yPos;
Circle userPointer;
vector<Circle> stars;
vector<Circle> deadShipParts;
vector<Bullet> bullets;
vector<Enemy> enemies;
vector<Coin> coins;
bool isHighScore;
string difficultyUserInput;
int enemySpawnRate;
int enemySpeed;


void init() {
    srand(time(0));
    width = 800;
    height = 800;

    // Set up user circle.
    user.setCenter(width / 2, height / 2);
    user.setColor(1, 1, 1, 1);
    user.setRadius(24);
    // Get user's high score from save file.
    user.fetchHighScore("../high_score.txt");

    // Set up user pointer.
    userPointer.setCenter(width / 2, height / 2);
    userPointer.setColor(1, 0, 0, 0);
    userPointer.setRadius(4);
}


/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}


/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    /*
     * Draw here
     */
    // Draw the stars on every screen.
    for (int i = 0; i < stars.size(); ++i) {
        stars[i].draw();
    }

    // Check if the current screen is MENU, GAME, DEATH, or PAUSE.
    // Certain things will be drawn or rendered based on the game screen.
    if (curr == MENU) {
        // Draw user and pointer.
        user.draw();
        userPointer.draw();

        // Draw bullets so user can shoot in the menu.
        for (int i = 0; i < bullets.size(); ++i) {
            bullets[i].draw();
        }

        // Show title.
        string title = "Space Ace";
        int red = rand() % 255 + 1;
        glColor3f(red / 255.0,1,1);
        glRasterPos2i((width / 2) - 52, 64);
        for (char &letter : title) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }

        // Tell user to press 's' to start.
        string menuOption = "Press 's' to start.";
        glColor3f(1,1,0);
        glRasterPos2i((width / 2) - 84, height - 128);
        for (char &letter : menuOption) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        // Show high score.
        string highScoreStr = "High Score: " + to_string(user.getHighScore());
        glColor3f(1,0,1);
        glRasterPos2i(16, height - 16);
        for (char &letter : highScoreStr) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
     } else if(curr == DIFFICULTY){
        // Draw user and pointer.
        user.draw();
        userPointer.draw();

        // Draw bullets so user can shoot in the menu.
        for (int i = 0; i < bullets.size(); ++i) {
            bullets[i].draw();
        }

        // Show title.
        string title = "Space Ace";
        int red = rand() % 255 + 1;
        glColor3f(red / 255.0,1,1);
        glRasterPos2i((width / 2) - 52, 64);
        for (char &letter : title) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }

        // Tell user to press 's' to start.
        string menuOption = "Select Difficulty to Start";
        glColor3f(1,1,0);
        glRasterPos2i((width / 2) - 115, height - 256);
        for (char &letter : menuOption) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
        }
        menuOption = "(1) Wimpy (2) Typical (3) Hardened";
        glRasterPos2i((width / 2) - 135, height - 230);
        for (char &letter : menuOption) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        // Show high score.
        string highScoreStr = "High Score: " + to_string(user.getHighScore());
        glColor3f(1,0,1);
        glRasterPos2i(16, height - 16);
        for (char &letter : highScoreStr) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
     }else if (curr == GAME) {
            // Draw user and pointer.
            user.draw();
            userPointer.draw();

            // Draw bullets and enemies and coins.
            for (int i = 0; i < bullets.size(); ++i) {
                bullets[i].draw();
            }
            for (int i = 0; i < enemies.size(); ++i) {
                enemies[i].draw();
            }
            for (int i = 0; i < coins.size(); ++i) {
                coins[i].draw();
            }

            // Display score and coin amount.
            string userScore;
            string userCoins;
            userScore = "Score: " + to_string(user.getScore());
            glColor3f(1, 1, 1);
            glRasterPos2i(width - 124, 24);
            for (char &letter : userScore) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            userCoins = "Coins: " + to_string(user.getCoins());
            glColor3f(1, .8, 0);
            glRasterPos2i(width - 124, 48);
            for (char &letter : userCoins) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            string message = "Special Abilities";
            glColor3f(1, 1, 1);
            glRasterPos2i(width - 250, height - 148);
            for (char &letter : message) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            string option1 = "1. Double Points (Cost: 2)";
            glColor3f(1, 1, 1);
            glRasterPos2i(width - 250, height - 124);
            for (char &letter : option1) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            string option2 = "2. Health Boost (Cost: 5)";
            glColor3f(1, 1, 1);
            glRasterPos2i(width - 250, height - 100);
            for (char &letter : option2) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            string option3 = "3. Mega Bullets (Cost: 8)";
            glColor3f(1, 1, 1);
            glRasterPos2i(width - 250, height - 76);
            for (char &letter : option3) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            string option4 = "4. EMP (Cost: 10)";
            glColor3f(1, 1, 1);
            glRasterPos2i(width - 250, height - 52);
            for (char &letter : option4) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            string option5 = "5. Minigun (Cost: 15)";
            glColor3f(1, 1, 1);
            glRasterPos2i(width - 250, height - 28);
            for (char &letter : option5) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            // Display health.
            string userHealth;
            userHealth = "Health: " + to_string(user.getHealth());
            glColor3f(1, 1, 1);
            glRasterPos2i(12, 24);
            for (char &letter : userHealth) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            // display ability
            string viewAbility = "Active Ability:";
            if(currAbilities.size() == 0 && currentAbility != "Health Boost!") {
                viewAbility += " None";
            } else {
                for (int i = 0; i < currAbilities.size(); i++) {
                    if(currAbilities[i].getCurrentAbility() == POINT_MULTIPLIER) {
                        viewAbility += " Double Points,";
                    }
                    if(currAbilities[i].getCurrentAbility() == AUTO_SHOOTER) {
                        viewAbility += " Minigun,";
                    }
                    if (currAbilities[i].getCurrentAbility() == FREEZE) {
                        viewAbility += " Freeze,";
                    }
                    if (currAbilities[i].getCurrentAbility() == MEGA_BULLETS) {
                        viewAbility += " Mega Bullets,";
                    }
                }
            }
            if(currentAbility == "Health Boost!") {
                string viewAbility = "+1 Health";
                glColor3f(1, 0, 0);
                glRasterPos2i(12, 42);
                for (char &letter : viewAbility) {
                    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
                }
                viewAbility += " None";
            }

            glColor3f(1, 1, 0);
            glRasterPos2i(16, height - 32);
            for (char &letter : viewAbility) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
        // Display pause option.

            string pauseText = "Press 'p' to pause.";
            glColor3f(1, 1, 1);
            glRasterPos2i(16, height - 16);
            for (char &letter : pauseText) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

    } else if (curr == DEATH) {
        // Draw the dead ship parts floating in space.
        for (int i = 0; i < deadShipParts.size(); ++i) {
            deadShipParts[i].draw();
        }

        // Display "You died!" on the death screen.
        string deathMessage = "You died!";
        glColor3f(1,1,1);
        glRasterPos2i((width / 2) - 64, 64);
        for (char &letter : deathMessage) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }

        // Display the user's score for that game.
        string highScoreStr = "Score: " + to_string(user.getScore());
        glColor3f(1, 1, 1);
        glRasterPos2i((width / 2) - 64, 128);
        for (char &letter : highScoreStr) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        // Print "New High Score!" if the user gets a new high score.
        if (isHighScore) {
            string newHighScoreStr = "New High Score!";
            glColor3f(1, 1, 0);
            glRasterPos2i((width / 2) - 72, 156);
            for (char &letter : newHighScoreStr) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
        }

        // Tell user to press 'm' to return to the menu.
        string menuOption = "Press 'm' to return to the menu.";
        glColor3f(1,1,0);
        glRasterPos2i((width / 2) - 124, height - 128);
        for (char &letter : menuOption) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    } else if (curr == PAUSE) {
        // Keep drawing everything, but don't move them.
        user.draw();
        userPointer.draw();
        for (int i = 0; i < bullets.size(); ++i) {
            bullets[i].draw();
        }
        for (int i = 0; i < enemies.size(); ++i) {
            enemies[i].draw();
        }
        for (int i = 0; i < coins.size(); ++i) {
            coins[i].draw();
        }
        string paused = "Paused.";
        glColor3f(1,1,1);
        glRasterPos2i((width / 2) - 36, 64);
        for (char &letter : paused) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }

        string unPause = "Press 'p' to resume.";
        glColor3f(1,1,0);
        glRasterPos2i((width / 2) - 72, 128);
        for (char &letter : unPause) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    } else {
        curr = MENU;
    }

    glFlush();  // Render now
}


// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    switch(key) {
        case 27: {
            // escape
            glutDestroyWindow(wd);
            exit(0);
        }
        case 'p': {
            if (curr == GAME) {
                curr = PAUSE;
            } else if (curr == PAUSE) {
                curr = GAME;
            }
            break;
        }
        case 's': {
            if (curr == MENU) {
                curr = DIFFICULTY;
            }
            break;
        }
        case 'm': {
            if (curr == DEATH) {
                // Set curr to MENU.
                curr = MENU;
                difficultyChoice = SELECT;
                isHighScore = false;
                user.setScore(0);

                // Reset deadShipParts.
                deadShipParts.clear();
                Circle deadShipPart;
                while (deadShipParts.size() < 10) {
                    deadShipPart.setCenter(width / 2, height / 2);
                    deadShipPart.setColor(1, 1, 1, 1);
                    deadShipPart.setRadius(rand() % 6 + 4);
                    deadShipParts.push_back(deadShipPart);
                }
            }
            break;
        }
        case '1': {
            if (curr == DIFFICULTY) {
                difficultyChoice = WIMPY;
                enemySpawnRate = 60;
                enemySpeed = 5;
                pointMultiplier = 0.5;
                curr = GAME;
                dummyTemp = 0;
                Coin coin(1, 0, 0);
                coin.setCenter(10000, 10000);
                coin.setColor(1, 0.8, 0, 1);
                coin.setRadius(24);
                coins.push_back(coin);
            }
            if (user.getCoins() >= 2) {
                user.decreaseCoins(2);
                currAbilities.push_back(Ability(200, 2, POINT_MULTIPLIER));
                pointMultiplier *= 2;
            }
            break;
        }
        case '2': {
            if (curr == DIFFICULTY) {
                difficultyChoice = TYPICAL;
                enemySpawnRate = 40;
                enemySpeed = 10;
                pointMultiplier = 1;
                curr = GAME;
                dummyTemp = 0;
                Coin coin(1, 0, 0);
                coin.setCenter(10000, 10000);
                coin.setColor(1, 0.8, 0, 1);
                coin.setRadius(24);
                coins.push_back(coin);
            }
            if (user.getCoins() >= 5) {
                user.decreaseCoins(5);
                user.increaseHealth(1);
                currentAbility = "Health Boost!";
            }
            break;
        }
        case '3': {
            if (curr == DIFFICULTY) {
                difficultyChoice = HARDENED;
                enemySpawnRate = 25;
                enemySpeed = 15;
                pointMultiplier = 2;
                curr = GAME;
                dummyTemp = 0;
                Coin coin(1, 0, 0);
                coin.setCenter(10000, 10000);
                coin.setColor(1, 0.8, 0, 1);
                coin.setRadius(24);
                coins.push_back(coin);
            }
            if (user.getCoins() >= 8) {
                user.decreaseCoins(8);
                currAbilities.push_back(Ability(200, 8, MEGA_BULLETS));
            }
            break;
        }
        case '4': {
            if (user.getCoins() >= 10) {
                user.decreaseCoins(10);
                currAbilities.push_back(Ability(200, 10, FREEZE));
            }
            break;
        }
        case '5': {
            if (user.getCoins() >= 15) {
                user.decreaseCoins(15);
                currAbilities.push_back(Ability(200, 15, AUTO_SHOOTER));
            }
            break;
        }
    }
    glutPostRedisplay();
}


void kbdUp(unsigned char key, int x, int y) {
    glutPostRedisplay();
}


void kbdS(int key, int x, int y) {
    // Change amount of red in ship on key presses.
    double red = user.getRed();
    switch(key) {
        case GLUT_KEY_DOWN:
            if (red > 0) {
                user.setColor(red - 0.1, 1, 1, 1);
            }
            break;
        case GLUT_KEY_UP:
            if (red < 1) {
                user.setColor(red + 0.1, 1, 1, 1);
            }
            break;
    }
    glutPostRedisplay();
}


void cursor(int x, int y) {
    // Draw the user pointer (red dot on the user's circle) around the user circle's radius depending on where the player
    // has their cursor.
    if (curr == GAME || curr == MENU || curr == DIFFICULTY) {
        double xVec = (x - user.getCenterX()) / sqrt(pow(x - user.getCenterX(), 2) + pow((y - user.getCenterY()), 2));
        double yVec = (y - user.getCenterY()) / sqrt(pow(x - user.getCenterX(), 2) + pow((y - user.getCenterY()), 2));
        userPointer.setCenter(user.getCenterX() + (xVec * 20), user.getCenterY() + (yVec * 20));
    }

    xPos = x;
    yPos = y;

    glutPostRedisplay();
}


// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (curr == GAME || curr == MENU || curr == DIFFICULTY) {
        // Create a bullet in the direction a user clicks.
        // If a user tries to fire in the very center of the screen, do nothing.
        // If the user tries to fire when there is 10 bullets, do nothing.
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x != (width / 2) && y != (height / 2)) {
            // Get unit vector of mouse click from user.
            double xVec = (x - (width / 2)) / sqrt(pow(x - (width / 2), 2) + pow((y - (height / 2)), 2));
            double yVec = (y - (height / 2)) / sqrt(pow(x - (width / 2), 2) + pow((y - (height / 2)), 2));

            Bullet bullet;
            if (Ability::contains(currAbilities, MEGA_BULLETS)) {
                bullet.setRadius(24);
            } else {
                bullet.setRadius(4);
            }
            bullet.setColor(1,0,0,1);
            bullet.setCenter((width / 2) + (xVec * 20), (height / 2) + (yVec * 20));
            bullet.setXVec(xVec);
            bullet.setYVec(yVec);

            bullets.push_back(bullet);
        }
    }

    glutPostRedisplay();
}


void timer(int dummy) {
    // Check if the game is not paused.
    if (curr != PAUSE) {
        // Increase dummy when the game isn't paused.
        ++dummy;

        // Fill screen with cascading stars to create moving effect (every 200 dummy).
        if (dummy % 200) {
            Circle star;
            star.setRadius(rand() % 2 + 1);
            star.setCenter(rand() % 800 + 1, 0);
            star.setColor(1,1,1,1);
            stars.push_back(star);
        }

        // Delete the stars that go off the screen.
        if (stars.size() > 0) {
            for (int i = 0; i < stars.size(); ++i) {
                // Move stars.
                stars[i].moveY(10);
                // Check if stars go off the screen.
                if (stars[i].getCenterX() > width ||
                    stars[i].getCenterX() < 0 ||
                    stars[i].getCenterY() > height ||
                    stars[i].getCenterY() < 0) {
                    stars.erase(stars.begin() + i);
                }
            }
        }

        // Move bullets.
        double xVec;
        double yVec;
        if(bullets.size() > 0) {
            // Fire the bullets!
            for(int i = 0; i < bullets.size(); ++i) {
                xVec = bullets[i].getXVec();
                yVec = bullets[i].getYVec();
                // Fire the bullet in the direction it is going.
                bullets[i].move(xVec * 10, yVec * 10);
                // Check if bullet is off the screen and delete it if it is.
                if(bullets[i].getCenterX() > width ||
                   bullets[i].getCenterX() < 0 ||
                   bullets[i].getCenterY() > height ||
                   bullets[i].getCenterY() < 0) {
                    bullets.erase(bullets.begin() + i);
                }
            }
        }
    }

    // Check if the user is still alive and the current screen is GAME.
    if (user.getHealth() > 0 && curr == GAME) {

        // Reset dummy value when you start the game.
        dummy = dummyTemp;
        ++dummy;
        dummyTemp = dummy;

        // Ability handling.
        for(int i = 0; i < currAbilities.size(); ++i) {
            if (currAbilities[i].getCurrentAbility() == MEGA_BULLETS) {
                currAbilities[i].changeTime(-1);

                if (currAbilities[i].getTime() <= 0) {
                    currAbilities.erase(currAbilities.begin() + i);
                }
            }

            if (currAbilities[i].getCurrentAbility() == AUTO_SHOOTER) {
                // Auto shoot counter.
                // Get unit vector of mouse click from user.
                double xVec = (xPos - (width / 2)) / sqrt(pow(xPos - (width / 2), 2) + pow((yPos - (height / 2)), 2));
                double yVec = (yPos - (height / 2)) / sqrt(pow(xPos - (width / 2), 2) + pow((yPos - (height / 2)), 2));

                Bullet bullet;
                if (Ability::contains(currAbilities, MEGA_BULLETS)) {
                    bullet.setRadius(24);
                } else {
                    bullet.setRadius(4);
                }
                bullet.setColor(1, 0, 0, 1);
                bullet.setCenter((width / 2) + (xVec * 20), (height / 2) + (yVec * 20));
                bullet.setXVec(xVec);
                bullet.setYVec(yVec);

                bullets.push_back(bullet);

                currAbilities[i].changeTime(-1);
                if (currAbilities[i].getTime() <= 0) {
                    currAbilities.erase(currAbilities.begin() + i);
                }
            }

            if (currAbilities[i].getCurrentAbility() == FREEZE) {
                currAbilities[i].changeTime(-1);
                if (currAbilities[i].getTime() <= 0) {
                    currAbilities.erase(currAbilities.begin() + i);
                }
            }

            if (currAbilities[i].getCurrentAbility() == POINT_MULTIPLIER) {
                currAbilities[i].changeTime(-1);
                if (currAbilities[i].getTime() <= 0) {
                    currAbilities.erase(currAbilities.begin() + i);
                    pointMultiplier /= 2.0;
                }
            }
        }
        // Check collisions.
        // Check overlap with user and bullet.
        // Bullet collisions.
        if (enemies.size() > 0) {
            double distance;
            for (int i = 0; i < bullets.size(); ++i) {
                for (int j = 0; j < enemies.size(); ++j) {
                    distance = sqrt((pow((enemies[j].getCenterX() - bullets[i].getCenterX()), 2) +
                                     pow((enemies[j].getCenterY() - bullets[i].getCenterY()), 2)));
                    // Check if collided.
                    if (distance < (enemies[j].getRadius() + bullets[i].getRadius())) {
                        enemies[j].decreaseHealth(1);
                        // Give user points!
                        user.increaseScore(100 * pointMultiplier);
                        if (enemies[j].isDead()) {
                            enemies.erase(enemies.begin() + j);
                        }
                        // Erase the bullet that hit the enemy.
                        bullets.erase(bullets.begin() + i);
                    }
                }
            }

            // User collisions.
            for (int i = 0; i < enemies.size(); ++i) {
                distance = sqrt((pow((enemies[i].getCenterX() - user.getCenterX()), 2) +
                                 pow((enemies[i].getCenterY() - user.getCenterY()), 2)));

                // Check if collided.
                if (distance < (enemies[i].getRadius() + user.getRadius())) {
                    // Decrease the player's health by the health of the enemy.
                    user.decreaseHealth(enemies[i].getHealth());
                    // Delete the enemy that was killed.
                    enemies.erase(enemies.begin() + i);
                }
            }

            // bullet collision with coins
            if (coins.size() > 0) {
                double distance;
                for (int i = 0; i < bullets.size(); ++i) {
                    for (int j = 0; j < coins.size(); ++j) {
                        distance = sqrt((pow((coins[j].getCenterX() - bullets[i].getCenterX()), 2) +
                                         pow((coins[j].getCenterY() - bullets[i].getCenterY()), 2)));
                        // Check if collided.
                        if (distance < (coins[j].getRadius() + bullets[i].getRadius())) {
                            coins[j].decreaseHealth(1);
                            // Give user points and coins!
                            user.increaseScore(100);
                            user.increaseCoins(1);
                            if (coins[j].isDead()) {
                                coins[j].move(100000,100000);
                            }
                            // Erase the bullet that hit the enemy.
                            bullets.erase(bullets.begin() + i);
                        }
                    }
                }
            }
        }

        // Move enemies if not frozen.
        if (enemies.size() > 0 && !Ability::contains(currAbilities, FREEZE)) {
            int distance;
            string enemyHealth;
            for (int i = 0; i < enemies.size(); ++i) {
                enemies[i].move(enemies[i].getXVec() * enemies[i].getVelMultiplier(),
                                enemies[i].getYVec() * enemies[i].getVelMultiplier());
            }
        }
        // Every 40 dummy, spawn a enemy.
        if (dummy % enemySpawnRate == 0 && !Ability::contains(currAbilities, FREEZE)) {
            // Generate a random number from 1 to 5 for the enemy's health.
            int health = rand() % 5 + 1;
            // Set the velMultiplier to be lower if the health of the enemy is higher (more health = slower).
            Enemy enemy(health, enemySpeed / health);
            // Get random point on circumference of circle around player (x,y)=(rcos(t),rsin(t)).
            double x, y;
            double angle = 2 * PI * (rand() % 101 + 1) / 100;
            x = (width / 2) + width * cos(angle);
            y = (height / 2) + height * sin(angle);
            enemy.setCenter(x, y);
            enemy.setRadius(24);
            enemy.setColor((enemy.getHealth() * 50) / 255.0, 0, 0.5, 1);
            vector<double> trajectory = enemy.getTrajectory(user.getCenterX(), user.getCenterY());
            enemy.setXVec(trajectory[0]);
            enemy.setYVec(trajectory[1]);
            enemies.push_back(enemy);
        }
        // for coins
        // Every 200 dummy, spawn a enemy.
        if(dummy - coins[0].getTime() == 150) {
            coins[0].move(10000,10000);
        } else if (dummy - coins[0].getTime() >= 300) {
            coins.erase(coins.begin());
        }

        if (coins.size() == 0) {
            // Generate a random number from 1 to 5 for the enemy's health.
            // Set the velMultiplier to be lower if the health of the enemy is higher (more health = slower).
            Coin coin(1, 0, dummy);
            // Get random point on circumference of circle around player (x,y)=(rcos(t),rsin(t)).
            double x, y;
            double angle = 2 * PI * (rand() % 101 + 1) / 100;
            x = (width / 2) + (rand() % 300 + 100) * cos(angle);
            y = (height / 2) + (rand() % 300 + 100) * sin(angle);
            coin.setCenter(x, y);
            coin.setColor(1, 0.8, 0, 1);
            coin.setRadius(24);
            coins.push_back(coin);
        }

        if (coins.size() > 0) {
            int randX = rand() % 20 - 10;
            int randY = rand() % 20 - 10;
            for(int i = 0; i < coins.size(); ++i) {
                coins[i].move(randX / 2.0,randY / 2.0);
            }

        }
    }

    // Check if the current screen is DEATH.
    if (curr == DEATH) {
        // Move the destroyed/dead ship parts.
        int randX, randY;
        for(int i = 0; i < deadShipParts.size(); ++i) {
            randX = rand() % 10 - 5;
            randY = rand() % 5 + 1;
            deadShipParts[i].move(randX / 2.0,randY / 2.0);
        }
    }

    // Execute the following if the user dies.
    if (user.getHealth() <= 0 && curr == GAME) {
        // Set current screen to DEATH.
        curr = DEATH;

        // Reset health & coins.
        user.setHealth(5);
        user.setCoins(0);
        coins.clear();

        // Check for new high score. Update the save file if the new score is a high score.
        if (user.getScore() > user.getHighScore()) {
            user.setHighScore(user.getScore());
            user.save("../high_score.txt");
            isHighScore = true;
        }

        // Clear the bullets and enemy vectors.
        bullets.clear();
        enemies.clear();

        // Create 10 dead ship parts for the death screen.
        Circle deadShipPart;
        while (deadShipParts.size() < 10) {
            deadShipPart.setCenter(width / 2, height / 2);
            deadShipPart.setColor(user.getRed(),1,1,1);
            deadShipPart.setRadius(rand() % 6 + 4);
            deadShipParts.push_back(deadShipPart);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}


/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Space Ace" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // handles timer
    glutTimerFunc(0, timer, 0);

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    glutKeyboardUpFunc(kbdUp);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}