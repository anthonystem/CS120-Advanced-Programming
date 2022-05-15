# Large-Project-astem-mdhodges

## Space Ace
This is a 2D graphics based game made using OpenGL and GLUT. Survive as long as possible as swarms of enemy ships come from all around to try and take down your spaceship.

### Author: Anthony Stem

## Setup, Requirements, & Files
This program is written in *C++14* and uses OpenGL and GLUT.

The following files are required to be present in the same directory in order to run this program and be able to play successfully:
* **graphics.cpp**
* **graphics.h**
* **shape.cpp**
* **shape.h**
* **circle.cpp**
* **circle.h**
* **Character.cpp**
* **Character.h**
* **User.cpp**
* **User.h**
* **Bullet.cpp**
* **Bullet.h**
* **Enemy.cpp**
* **Enemy.h**
* **Ability.cpp**
* **Ability.h**
* **Coin.cpp**
* **Coin.h**

The file **high_score.txt** is the save file for the game. It should be present within the directory as well.


## How to Play
When you launch the program, you will be prompted to press the key *'s'* to start playing. While you are in the main menu, you will see the high score in the bottom-left corner, the title in the top-center, and the user's spaceship in the middle of the screen. Additionally, little stars will come down simulating movement for the spaceship. You can click anywhere on the game screen with your mouse to shoot bullets in the direction your mouse is pointing.

After you press *'s'* to start, you will be brought to the difficulty selection screen. Here, you press '1' to play the Wimpy difficulty, '2' to play the Typical difficulty, and '3' to play the Hardened difficulty. The difficulty breakdown is as follows:

* **Wimpy**: Each enemy hit is 50 points. Enemies are slower and the spawn rate is slower.
* **Typical**: How the game is meant to be played. Standard spawn rate and enemy speed. Each enemy hit is 100 points.
* **Hardened**: A true challenge. Spawn rate is increased, and the enemy speed is increased as well. Each enemy hit is 200 points. Good luck if you dare try this difficulty.

Once you select a difficulty, you will immediately start the game. Your ship's health (which starts at 5) will be displayed in the top-left corner, your score will be in the top-right corner, and the game will tell you how to pause (press *'p'* to pause) in the bottom left corner. When you see enemy ships coming, point and shoot at them. The total health each ship has will be displayed in the center. The number of health an enemy has is the number of times you have to shoot it before it is destroyed (e.g. a enemy with 5 health takes 5 shots to defeat). The more health an enemy spawns with, the slower it will move. Additionally, the more health an enemy spawns with, the pinker/redder it will be. Enemies can spawn with either 1, 2, 3, 4, or 5 health. The player always starts with 5 health. Additionally, the remaining health an enemy has when it collides with your ship is how much damage it will deal. So, if, for example, an enemy with 5 health spawns, and you manage to hit it twice before it collides with your ship, it will deal 3 damage.

In addition to enemies, floating yellow coins will spawn randomly on the screen (they have a '$' sign in the center) and jitter around. Shooting one of these grants you a coin which you can save up to spend on abilities. The abilities you can choose from are listed below:

* **Double Points** - Cost: 2 Coins. Temporarily increases score multiplier to x2.
* **Health Boost** - Cost: 5 Coins. Increases the player's health by 1.
* **Mega Bullets** - Cost: 8 Coins. Temporarily increases the size of the player's bullets.
* **EMP** - Cost: 10 Coins. Temporarily freezes all enemies and stops enemy spawning.
* **Minigun** - Cost: 15 Coins. Temporarily allows the player to shoot bullets at inhumane speeds to quickly take out enemies. This ability is tough to get, but it does some serious damage.

If you want to pause the game at any time, just press *p* to stop all enemy and player movements.

After you die, a message will pop up saying you died. If you get a high score, it will tell you that there is a new high score, and it will then save the new high score to the save file *high_score.txt*.


## Additional Program Classes
### Character
**Character** An abstract class that represents a Character or element of the game which has health and interacts with the game. Extends the Circle class.

### User
**User** A class that represents a User. Extends the Character class. Holds information such as user score and high score.

### Enemy
**Enemy** A class that represents an Enemy object. Extends the Character class.

### Bullet
**Bullet** A class that represents a Bullet object. Extends the Character class.

### Coin
**Coin** A class that represents the Coin object. Extends the Character class.

### Ability
**Ability** A class that manages and stores the abilities.

## Known Bugs
There are no known compiler, runtime, or logic bugs in this program.

## Concepts
This project uses the many concepts from module 2 and module 4. 
## Module 2
* The Character class holds the parent relation for the Bullet class, the Coin class, the Enemy class, and the User class
* The Shape class holds parent relation for the Circle class
## Module 4
* We used GLUT concepts and OpenGL concepts
* Graphics window

## Operating Systems
This project has been run on both macOS and Windows operating systems.

## Installations
No installations are needed to run this project.
