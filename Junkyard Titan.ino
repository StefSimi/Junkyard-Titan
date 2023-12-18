#include "LedControl.h"  // Include LedControl library for controlling the LED matrix
#include <EEPROM.h>
//Pin declaration
const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;
const int playerXPin = A0;
const int playerYPin = A1;
const int bulletXPin = A2;
const int bulletYPin = A3;
//const int buttonPin = 6;
const int leftSwitchPin = 0;
const int rightSwitchPin = 2;
const int buzzerPin = 3;
const int seedPin = 3;  //A pin that is not connected to anything, used as a seed for the random function

const int lcdBrightnessPin = 6;
const int lcdBrightnessModifier = 50;
int lcdBrightness = 3;

const float initialX = 1;  //Initial player position
const float initialY = 8;
const int initialScore = 0;

//Frame control logic
const int frameDelay = 1000 / 60;  // 60 FPS
unsigned long previousFrameMillis;
unsigned long currentMillis;

//Joystick logic
const float velocity = 0.064;
const int deadZone = 350;
const int bulletDeadZone = 250;
const int middle = 512;

bool soundOn = true;

bool running = false;
bool win = false;

bool makeCoinSound = false;
bool makeLaserSound = false;
bool makeExplosionSound = false;
bool makeWinSound = false;
bool makeLoseSound = false;
byte laserSoundCounter = 0;
byte explosionSoundCounter = 0;
byte winSoundCounter = 0;
byte loseSoundCounter = 0;
byte coinSoundCounter = 0;

bool levelUpAnimation = false;
byte levelUpCounter = 0;
byte levelUpDelay = 180;

unsigned long soundMillis;

char aboutString[] = "  Junkyard Titan made by Stefan Simion Github.com/StefSimi  ";
char howToString[] = "  Use left joystick to move, use right joystick to shoot. Hold both joysticks down to sell the items in your inventory. If you get enough points you can move to the next level  ";
const int aboutMenuSize = 3;
int aboutIndex = 0;
int scrollCounter = 16;

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);  // Create an LedControl object to manage the LED matrix
byte matrixBrightness = 2;                                 // Variable to set the brightness level of the matrix

float currentX = 5;
float currentY = 5;

byte hudCounter = 0;
long score = 0;
bool highscore = 0;

#define MATRIX_BRIGHTNESS_BYTE 0
#define LCD_BRIGHTNESS_BYTE 2
#define NAME_BYTE 4
#define HIGHSCORE_BYTE 20
#define HIGHSCORE_NAMES_BYTE 40
#define STOP_BYTE 55

long highscores[3];
char highscoreNames[3][4];

bool paused = false;
byte lastRightSwitchReading;
unsigned long lastRightSwitchDebounceTime;
byte rightSwitchButtonState;
byte rightSwitchRequest;


#define UP_STATE 0
#define DOWN_STATE 1
#define LEFT_STATE 2
#define RIGHT_STATE 3
#define IDLE_STATE 4

#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#define TWELVE 12
#define FIFTEEN 15
#define THIRTY_FRAMES 30

//An array would have been more efficient ngl
bool upMenuInput = false;
bool downMenuInput = false;
bool leftMenuInput = false;
bool rightMenuInput = false;


//Menu logic
#define MAIN_MENU_START 0
#define MAIN_MENU_HIGHSCORES 1
#define MAIN_MENU_NAME 2
#define MAIN_MENU_SETTINGS 3
#define MAIN_MENU_HOWTO 4
#define MAIN_MENU_ABOUT 5

#define SETTINGS_LCD_BRIGHTNESS 0
#define SETTINGS_MAT_BRIGHTNESS 1
#define SETTINGS_SOUND_TOGGLE 2
#define SETTINGS_BACK 3

#define HIGHSCORES_RESET 3
#define HIGHSCORES_BACK 4

byte lastSwitchReading;
unsigned long lastSwitchDebounceTime;
byte switchButtonState;
byte switchRequest;

int codeToExecute;
byte currentNameIndex = 0;


#define LCD_BRIGHTNESS 0
#define MAT_BRIGHTNESS 1
#define CHANGE_NAME 2
#define ABOUT_CODE 3
#define HOWTO_CODE 4

int joystickState = IDLE_STATE;
const int joystickRange = 1024;
const int joystickBuffer = 150;
const unsigned long joystickTimeBuffer = 400;
unsigned long joystickMillis;
const int numberOfOptions = 5;
const int numberOfColumns = 16;

const byte matrixSize = 16;  // Size of the LED matrix
const byte physicalMatrixSize = 8;

//Blink logic
byte playerFrameCounter = 0;
const byte playerOnInterval = 45;
const byte playerOffInterval = 15;
bool playerBlinkState = 0;
byte bulletFrameCounter = 0;
const byte bulletOnInterval = 10;
const byte bulletOffInterval = 10;
bool bulletBlinkState = 0;
const byte wallOnInterval = 30;
const byte wallOffInterval = 15;
bool wallBlinkState = 0;
byte wallFrameCounter;

const int initialWallDelay = 500;
int wallMoveFrameDelay = 500;
const int wallDelayModifier = 45;
int wallMoveFrameCounter = 0;

int currentLevel = 0;
int levelScoreRequirements[6] = { 250, 600, 1500, 5000, 8000, 15000 };
const byte prices[9] = { 0, 5, 10, 20, 35, 55, 80, 120, 175 };
bool levelUp = false;
//int wallDelays[5]={450,375,300,225,150};


int wallIndex = 0;

//Bullet logic
const int bulletDelay = 60;
int bulletCounter = 0;
bool bulletFired = 0;
float bulletCurrentX;
float bulletCurrentY;
float bulletXVel;
float bulletYVel;

//Explosion logic
bool explosion = false;
byte explosionCounter = 0;
int explosionX;
int explosionY;



int aboutLineNumber = 1;
int iCursor = 0;

byte reading;
unsigned long debounceDelay = 100;

bool channelSound = false;
bool channeling = false;
const int channelDuration = 120;
int channelCounter = 0;



#define LOSE_IMAGE 0
#define WIN_IMAGE 1
#define SETTINGS_IMAGE 2
#define HOME_IMAGE 3
#define HIGHSCORE_IMAGE 4

#define BULLET_VELOCITY_MODIFIER 6000
#define HALF 0.5
#define EXPLOSION_DURATION 60
#define SCORE_PER_KILL 100
#define SCORE_LOSS 250
#define TWO 2



#define FRAME_1 1
#define FRAME_4 4
#define FRAME_7 7
#define FRAME_16 16
#define FREQUENCY_900 900
#define FREQUENCY_1000 1000
#define FREQUENCY_1200 1200
#define FREQUENCY_1500 1500


#define LASER_SOUND_DURATION 50
#define EXPLOSION_SOUND_DURATION_1 100
#define EXPLOSION_SOUND_DURATION_2 200
#define EXPLOSION_SOUND_DURATION_3 150
#define COIN_SOUND_DURATION_1 120
#define COIN_SOUND_DURATION_2 720

#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_G5 784
#define NOTE_G4 392
#define NOTE_F4 349
#define NOTE_D4 293
#define NOTE_A3 220
#define NOTE_B5 988
#define NOTE_E6 1319

#define WIN_SOUND_DURATION_1 200
#define WIN_SOUND_DURATION_2 800

#define WIN_SOUND_DELAY_1 200
#define WIN_SOUND_DELAY_2 400
#define WIN_SOUND_DELAY_3 600
#define WIN_SOUND_DELAY_4 1400


#define LOSE_SOUND_DURATION_1 300
#define LOSE_SOUND_DURATION_2 600

#define LOSE_SOUND_DELAY_1 150
#define LOSE_SOUND_DELAY_2 300
#define LOSE_SOUND_DELAY_3 450
#define LOSE_SOUND_DELAY_4 750

#define COIN_SOUND_DURATION_1 120
#define COIN_SOUND_DURATION_2 720

#define MAIN_MENU 0
#define START_GAME 1
#define SETTINGS 2
#define HIGHSCORE 3
#define EXECUTING_CODE 4
#define ENDGAME 5

int menuState = MAIN_MENU;

unsigned long cursorMillis = 0;
const unsigned long cursorToggleDelay = 750;
bool cursorToggled = false;


const uint64_t IMAGES[] = {
  0x3c66ff9999ffff7e,  //Lose
  0x6090d016690d0106,  //Win
  0x5aff66c3c366ff5a,  //Options
  0xff81bda5a5bd81ff,  //Home screen
  0x7c18183c7ebdbd5a   //Highscore

};
const int IMAGES_LEN = sizeof(IMAGES) / 8;



enum id {
  EMPTY,
  WALL,
  PLAYER,
  ENEMY,
  BULLET
};

byte entityMatrix[matrixSize][matrixSize] = {  //Matrix used internally, for entity control and logic
  { WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL },
  { WALL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WALL }
};
bool matrix[matrixSize][matrixSize] = {  //This is the matrix used for rendering images to the LED matrix
  { 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }
};
// Array representing each row of the LED matrix as a byte

#include <LiquidCrystal.h>
const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 13;
const byte d6 = 5;
const byte d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int mainMenuSize = 6;
String mainMenuOptions[mainMenuSize] = { "Start", "Highscores", "Change Name", "Settings", "How To Play", "About" };
int mainMenuIndex = 0;

const int settingsMenuSize = 4;
String settingsMenuOptions[settingsMenuSize] = { "LCD Brightness", "Mat Brightness", "Toggle Sounds", "Back" };
int settingsMenuIndex = 0;

const int highscoreMenuSize = 5;
String highscoreMenuOptions[highscoreMenuSize];
int highscoreMenuIndex = 0;

bool needUpdate = true;

unsigned long scrollMillis;
const unsigned long scrollDelay = 300;

#define TWO_SECONDS 2000
const int matrixBrightnessModifier = 3;


int inventorySize = 4;
int inventory[4] = { 0 };
int inventoryIndex = 0;

char currentName[4];



void setup() {

  for (int i = 0; i < 3; i++) {  //Get the current highscores from EEPROM
    EEPROM.get(HIGHSCORE_BYTE + i * 4, highscores[i]);
    EEPROM.get(HIGHSCORE_NAMES_BYTE + i * 4, highscoreNames[i]);
  }


  EEPROM.get(MATRIX_BRIGHTNESS_BYTE, matrixBrightness);  //Get the current settings from EEPROM
  EEPROM.get(LCD_BRIGHTNESS_BYTE, lcdBrightness);
  EEPROM.get(NAME_BYTE, currentName);

  lcd.clear();
  lc.shutdown(0, false);                 // turn off power saving, enables display
  lc.setIntensity(0, matrixBrightness);  // sets brightness (0~15 possible values)
  lc.clearDisplay(0);

  randomSeed(analogRead(seedPin));

  pinMode(leftSwitchPin, INPUT_PULLUP);
  pinMode(rightSwitchPin, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(playerXPin, INPUT);
  pinMode(playerYPin, INPUT);
  pinMode(bulletXPin, INPUT);
  pinMode(bulletYPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(lcdBrightnessPin, OUTPUT);

  analogWrite(lcdBrightnessPin, lcdBrightness * lcdBrightnessModifier);
  lc.setIntensity(0, matrixBrightness * matrixBrightnessModifier);

  highscoreMenuOptions[HIGHSCORES_RESET] = "Reset Data";
  highscoreMenuOptions[HIGHSCORES_BACK] = "Back";

  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(ZERO, ZERO);
  lcd.print("Welcome, ");
  lcd.print(currentName);

  lcd.print(", to");
  lcd.setCursor(ONE, ONE);
  lcd.print("Junkyard Titan");

  delay(TWO_SECONDS);
  lcd.clear();



  //startGame();
}
void loop() {




  if (running) {  //While the game is running, we update the game and then render it 60 times per second (every frame)
    currentMillis = millis();
    if (currentMillis - previousFrameMillis > frameDelay) {
      lcd.setCursor(0, 0);
      // print the number of seconds since reset:

      update();
      if (!levelUpAnimation) {
        render();
      }
      previousFrameMillis = currentMillis;
    }
  } else {  //If the game is not running, we handle endgame sounds (win/lose) and display the menu again
    updateEndgameSounds();
    handleMenu();
  }
}

void update() {  //The main funciton of the game, here every other funcion is called
  if (!levelUpAnimation) {
    debounce(rightSwitchPin, lastRightSwitchReading, lastRightSwitchDebounceTime, rightSwitchButtonState, rightSwitchRequest);
    if (rightSwitchRequest) {  //We handle pausing directly in the update function because it directly influences the execution of the other functions
      paused = !paused;
      rightSwitchRequest = false;
    }
    updateHud();
    if (!paused) {
      if (!channeling) {
        updatePlayerPosition();  //The player cannot move while channeling
      }
      updateBullet();
      updateExplosion();
      if (soundOn) {
        updateSound();
      }
      updateWall();
      updateInventory();
      updateEndLevel();
    }
  } else {
    if (soundOn) {
      updateEndgameSounds();
    }
    levelUpCounter++;  //increment a counter in order to display the level up message for a set duration
    if (levelUpCounter > levelUpDelay) {
      startLevel(currentLevel);
      levelUpCounter = 0;
      levelUpAnimation = false;
    }
  }
}

void updatePlayerPosition() {

  int intCurrentX = int(currentX);
  int intCurrentY = int(currentY);
  entityMatrix[intCurrentX][intCurrentY] = EMPTY;

  int xValue = analogRead(playerXPin);  // Read X-axis value
  int yValue = analogRead(playerYPin);  // Read Y-axis value
  //For every direction, we will check if the joystick is in said direction and if the player can move there (not exiting matrix bounds colliding with an enemy or a wall)
  if (xValue > middle + deadZone && entityMatrix[intCurrentX - 1][intCurrentY] != WALL && entityMatrix[intCurrentX - 1][intCurrentY] != ENEMY && intCurrentX - 1 >= 0) {
    currentX -= velocity;
  }
  if (xValue < middle - deadZone && entityMatrix[intCurrentX + 1][intCurrentY] != WALL && entityMatrix[intCurrentX + 1][intCurrentY] != ENEMY && intCurrentX + 1 < matrixSize) {
    currentX += velocity;
  }
  if (yValue > middle + deadZone && entityMatrix[intCurrentX][intCurrentY + 1] != WALL && entityMatrix[intCurrentX][intCurrentY + 1] != ENEMY && intCurrentY + 1 < matrixSize) {
    currentY += velocity;
  }
  if (yValue < middle - deadZone && entityMatrix[intCurrentX][intCurrentY - 1] != WALL && entityMatrix[intCurrentX][intCurrentY - 1] != ENEMY && intCurrentY - 1 >= 0) {
    currentY -= velocity;
  }
  int newIntCurrentX = int(currentX);
  int newIntCurrentY = int(currentY);
  if (newIntCurrentX != intCurrentX || newIntCurrentY != intCurrentY) {  //If the player position changes, update the display matrix
    matrix[intCurrentX][intCurrentY] = false;
    matrix[newIntCurrentX][newIntCurrentY] = true;
  }
  entityMatrix[newIntCurrentX][newIntCurrentY] = PLAYER;
}

void updateBullet() {
  bulletCounter++;
  if (!bulletFired) {                       // If the bullet is not fired (we can only have 1 active bullet at a time), check if the right joystick moves in a direction enough for the bullet to be fired
    float xValue = analogRead(bulletXPin);  // Read X-axis value
    float yValue = analogRead(bulletYPin);  // Read Y-axis value
    //Similar to player movement, but checking every direction at once, to see if we need to initialize the bullet. Also make sure we are not in an explosion animation, and enough time has passed since the last bullet has been fired
    if ((xValue > middle + bulletDeadZone || xValue < middle - bulletDeadZone || yValue > middle + bulletDeadZone || yValue < middle - bulletDeadZone) && bulletCounter > bulletDelay && !explosion) {
      bulletCounter = 0;
      bulletXVel = -1 * (xValue - middle) / BULLET_VELOCITY_MODIFIER;  //*-1 because of matrix orientation
      bulletYVel = (yValue - middle) / BULLET_VELOCITY_MODIFIER;
      bulletFired = true;
      if (xValue > middle + bulletDeadZone) {  //Up
        bulletCurrentX = int(currentX) - 1;
        bulletCurrentY = int(currentY) + HALF;  //+half because we work with floating points, and converting from float to int gives the floor() value of the floating point
      }
      if (xValue < middle - bulletDeadZone) {  //Down
        bulletCurrentX = int(currentX) + 1;
        bulletCurrentY = int(currentY) + HALF;
      }
      if (yValue > middle + bulletDeadZone) {  //Right
        bulletCurrentX = int(currentX) + HALF;
        bulletCurrentY = int(currentY) + 1;
      }
      if (yValue < middle - bulletDeadZone) {  //Left
        bulletCurrentX = int(currentX) + HALF;
        bulletCurrentY = int(currentY) - 1;
      }
      if (entityMatrix[int(bulletCurrentX)][int(bulletCurrentY)] == WALL) {
        bulletFired = false;
        makeLaserSound = true;
      }
      if (entityMatrix[int(bulletCurrentX)][int(bulletCurrentY)] != WALL) {
        if (entityMatrix[int(bulletCurrentX)][int(bulletCurrentY)] == ENEMY) {  // If the bullet would spawn on an enemy, it would override it in the entity matrix, so the explosion would not trigger, so we check for this manually before spawing in the bullet
          explosion = true;
          makeExplosionSound = true;
          explosionX = int(bulletCurrentX);
          explosionY = int(bulletCurrentY);
          explosionCounter = 0;
          entityMatrix[int(bulletCurrentX)][int(bulletCurrentY)] = EMPTY;
          matrix[int(bulletCurrentX)][int(bulletCurrentY)] = false;
          bulletFired = false;
        } else {
          makeLaserSound = true;
          bulletFired = true;
          entityMatrix[int(bulletCurrentX)][int(bulletCurrentY)] = BULLET;
          matrix[int(bulletCurrentX)][int(bulletCurrentY)] = true;
        }
      }
    }

  } else {  //Very similar to player movement, we check if we can move to a new location, and then move there. The only difference is that if we go out of bounds, the bullet despawns, and if we hit an enemy, an explosion occurs
    int intBulletCurrentX = int(bulletCurrentX);
    int intBulletCurrentY = int(bulletCurrentY);
    if (entityMatrix[int(bulletCurrentX)][int(bulletCurrentY)] != WALL) {
      entityMatrix[intBulletCurrentX][intBulletCurrentY] = EMPTY;
    }

    if (bulletCurrentX + bulletXVel < 0 || bulletCurrentX + bulletXVel >= matrixSize || bulletCurrentY + bulletYVel < 0 || bulletCurrentY + bulletYVel >= matrixSize) {
      bulletFired = false;
      matrix[intBulletCurrentX][intBulletCurrentY] = false;
    } else {
      bulletCurrentX += bulletXVel;
      bulletCurrentY += bulletYVel;
      if (int(bulletCurrentX) != intBulletCurrentX || int(bulletCurrentY) != intBulletCurrentY) {  //set prev position to 0 and update the current one
        matrix[intBulletCurrentX][intBulletCurrentY] = false;
        matrix[int(bulletCurrentX)][int(bulletCurrentY)] = true;
      }
      intBulletCurrentX = int(bulletCurrentX);
      intBulletCurrentY = int(bulletCurrentY);



      if (entityMatrix[intBulletCurrentX][intBulletCurrentY] == WALL) {
        bulletFired = false;
      } else {
        if (entityMatrix[intBulletCurrentX][intBulletCurrentY] == ENEMY) {  //HIT
          explosion = true;
          makeExplosionSound = true;
          explosionX = intBulletCurrentX;
          explosionY = intBulletCurrentY;
          explosionCounter = 0;

          //EXPLOSION
          entityMatrix[intBulletCurrentX][intBulletCurrentY] = 0;
          matrix[intBulletCurrentX][intBulletCurrentY] = 0;
          bulletFired = false;


        } else {
          entityMatrix[intBulletCurrentX][intBulletCurrentY] = BULLET;
        }
      }
    }
  }
}


void updateExplosion() {
  //When an explosion occurs, we light up a 3x3 square around the explosion center. After a delay, everything is destroyed. If the player ever enters this 3x3 zone, they die.
  if (explosion) {
    byte multiplier = 1;
    explosionCounter++;
    for (int i = explosionX - 1; i <= explosionX + 1; i++) {
      for (int j = explosionY - 1; j <= explosionY + 1; j++) {
        if (i >= 0 && i < matrixSize && j >= 0 && j < matrixSize && entityMatrix[i][j] != WALL) {
          if (explosionCounter < EXPLOSION_DURATION) {
            matrix[i][j] = 1;
            if (entityMatrix[i][j] == PLAYER) {
              //DEATH
              death();
            }
          } else {


            matrix[i][j] = 0;
            if (entityMatrix[i][j] == ENEMY) {  //Once the explosion ends, the amount of dots exploded gets added tot the player's inventory
              if (inventoryIndex < inventorySize) {
                inventory[inventoryIndex]++;
              }
            }
            entityMatrix[i][j] = EMPTY;
            explosion = false;
          }
        }
        if (i == explosionX + 1 && j == explosionY + 1 && inventoryIndex < inventorySize && explosionCounter == EXPLOSION_DURATION) {  //This checks whether the for loop is ending, if so the inventory index is incremente
          inventory[inventoryIndex]++;                                                                                                 //We also increment this because the original position where the explosion occured was overridden by the bullet in the entity matrix
          inventoryIndex++;
        }
      }
    }
  }
}

void updateHud() {  //Here we update the heads up display. We do it every thirty frames, so it doesn't get too noisy
  hudCounter++;
  if (hudCounter == THIRTY_FRAMES) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Score:");
    lcd.setCursor(SEVEN, ZERO);
    lcd.print(score);

    hudCounter = 0;
    if (score > levelScoreRequirements[currentLevel]) {
      lcd.print("*");
    }
    if (paused) {
      lcd.setCursor(FIFTEEN, ZERO);
      lcd.print("P");
    }



    lcd.setCursor(ZERO, ONE);
    lcd.print("Inv:");
    lcd.setCursor(SIX, ONE);
    for (int i = 0; i < inventorySize; i++) {
      lcd.print(inventory[i]);
      lcd.print(" ");
    }
    if (channeling) {
      lcd.setCursor(FIFTEEN, ONE);
      lcd.print("+");
    }
  }
}


void updateWall() {  //Here we update the outer walls, and check if the player was caught in the "flames"

  wallMoveFrameCounter++;
  if (wallMoveFrameCounter > wallMoveFrameDelay && wallIndex < 9) {
    wallIndex++;
    for (int i = 0; i < matrixSize; i++) {
      entityMatrix[i][wallIndex] = entityMatrix[i][matrixSize - wallIndex - 1] = WALL;
      matrix[i][wallIndex] = matrix[i][matrixSize - wallIndex] = wallBlinkState;
    }
    wallMoveFrameCounter = 0;
  }
  if (!(int(currentY) > wallIndex && int(currentY < matrixSize - wallIndex - 1))) {
    death();
  }
}

void updateInventory() {  //Here we check if the player wants to sell their inventory or not
  bool leftSwitchValue = digitalRead(leftSwitchPin);
  if (!channeling) {
    //Note: removed sound from channel animation, too annoying

    /*if (channelSound) { 
      noTone(buzzerPin);
      channelSound = false;
    }*/
    if (!leftSwitchValue) {

      channeling = true;
    }
  } else {
    /*if (inventory[0]) {
      tone(buzzerPin, 900);
      channelSound = true;
    }*/
    if (leftSwitchValue) {
      channeling = false;
      channelCounter = 0;
    }
    channelCounter++;
    if (channelCounter == channelDuration) {
      noTone(buzzerPin);
      makeCoinSound = true;
      channeling = false;
      channelCounter = 0;
      //Sell Inventory;
      for (int i = 0; i < inventorySize; i++) {
        Serial.print(inventory[i]);
        score += TWO * (currentLevel + 1) * prices[inventory[i]];
        inventory[i] = 0;
      }
      Serial.println("");
      inventoryIndex = 0;
    }
  }
}

void updateEndLevel() {                                            //Handle endgame logic
  if (score > levelScoreRequirements[currentLevel] && !levelUp) {  //If the player meets the quota, the exit door will open
    levelUp = true;
    entityMatrix[0][matrixSize / 2 - 1] = entityMatrix[0][matrixSize / 2] = EMPTY;
    matrix[0][matrixSize / 2 - 1] = matrix[0][matrixSize / 2] = false;
  }
  if (levelUp) {
    if (int(currentX) == 0 && (int(currentY) == matrixSize / 2 - 1 || int(currentY) == matrixSize / 2)) {
      currentLevel++;
      levelUpAnimation = true;
      makeWinSound = true;
      displayImage(IMAGES[WIN_IMAGE]);
      lcd.clear();
      lcd.setCursor(ZERO, ZERO);
      lcd.print("Level: ");
      lcd.print(currentLevel + 1);
      lcd.setCursor(ZERO, ONE);
      lcd.print("Goal: ");
      lcd.print(levelScoreRequirements[currentLevel]);
      //startLevel(currentLevel);
    }
  }
}




void render() {
  //Here we handle the blinking logic

  ///PLAYER
  playerFrameCounter++;
  bulletFrameCounter++;
  wallFrameCounter++;


  if (playerBlinkState && playerFrameCounter > playerOnInterval) {
    playerFrameCounter = 0;
    matrix[int(currentX)][int(currentY)] = false;
    playerBlinkState = false;
  } else if (!playerBlinkState && playerFrameCounter > playerOffInterval) {
    playerFrameCounter = 0;
    matrix[int(currentX)][int(currentY)] = true;
    playerBlinkState = true;
  }


  ///BULLET
  if (bulletBlinkState && bulletFrameCounter > bulletOnInterval) {
    for (int i = 0; i < matrixSize; i++) {
      for (int j = 0; j < matrixSize; j++) {
        if (entityMatrix[i][j] == BULLET) {
          matrix[i][j] = false;
        }
      }
    }
    bulletFrameCounter = 0;
    bulletBlinkState = false;
  }
  if (!bulletBlinkState && bulletFrameCounter > bulletOffInterval) {
    for (int i = 0; i < matrixSize; i++) {
      for (int j = 0; j < matrixSize; j++) {
        if (entityMatrix[i][j] == BULLET) {
          matrix[i][j] = true;
        }
      }
    }
    bulletFrameCounter = 0;
    bulletBlinkState = true;
  }

  ///WALL
  if (wallBlinkState && wallFrameCounter > wallOnInterval) {
    for (int i = 0; i < matrixSize; i++) {
      for (int j = 0; j < matrixSize; j++) {
        if (entityMatrix[i][j] == WALL) {
          matrix[i][j] = false;
        }
      }
    }
    wallFrameCounter = 0;
    wallBlinkState = false;
  }
  if (!wallBlinkState && wallFrameCounter > wallOffInterval) {
    for (int i = 0; i < matrixSize; i++) {
      for (int j = 0; j < matrixSize; j++) {
        if (entityMatrix[i][j] == WALL) {
          matrix[i][j] = true;
        }
      }
    }
    wallFrameCounter = 0;
    wallBlinkState = true;
  }

  updateMatrix();
}

void updateMatrix() {
  int rowStart = clamp(int(currentX) - FOUR, 0, EIGHT);  //this basically provides an offset that is used to print a portion of the whole matrix
  int colStart = clamp(int(currentY) - FOUR, 0, EIGHT);  //-4 because we want our player to be in the center, 8 because 16(matrix size)-8(physical matrix size)=8
  for (int row = 0; row < physicalMatrixSize; row++) {
    for (int col = 0; col < physicalMatrixSize; col++) {
      lc.setLed(0, row, col, matrix[row + rowStart][col + colStart]);
    }
  }
}



void printEntityMatrix() {  //Function for debugging purposes
  for (int i = 0; i < matrixSize; i++) {
    for (int j = 0; j < matrixSize; j++) {
      Serial.print(entityMatrix[i][j]);
    }
    Serial.println("");
  }
  Serial.println("");
}

void displayImage(uint64_t image) {
  for (int i = 0; i < EIGHT; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      lc.setLed(0, i, j, bitRead(row, j));
    }
  }
}

void startGame() {  //This function is run when the game first starts

  lcd.clear();
  lcd.setCursor(ZERO, ZERO);
  lcd.print("Score:");
  lcd.setCursor(ZERO, ONE);
  lcd.print("Inventory:");
  lcd.setCursor(TWELVE, ONE);
  for (int i = 0; i < inventorySize; i++) {
    lcd.print(inventory[i]);
  }
  lc.shutdown(0, false);                 // turn off power saving, enables display
  lc.setIntensity(0, matrixBrightness);  // sets brightness (0~15 possible values)
  lc.clearDisplay(0);                    // Clear the matrix display
  //updateMatrix();
  //noTone(buzzerPin);
  makeExplosionSound = false;
  makeWinSound = false;
  makeLoseSound = false;
  makeLaserSound = false;
  makeCoinSound = false;

  //Reset every value back to its default one, and then start the game
  score = initialScore;
  running = true;
  bulletFired = false;
  explosion = false;
  bulletCounter = 0;
  explosionCounter = 0;
  winSoundCounter = 0;
  loseSoundCounter = 0;
  laserSoundCounter = 0;
  coinSoundCounter = 0;
  inventoryIndex = 0;
  currentLevel = 0;
  levelUpAnimation = true;
  wallMoveFrameDelay = initialWallDelay;
  for (int i = 0; i < inventorySize; i++) {
    inventory[i] = 0;
  }
  lcd.clear();
  lcd.setCursor(ZERO, ZERO);
  lcd.print("Level: ");
  lcd.print(currentLevel + 1);
  lcd.setCursor(ZERO, ONE);
  lcd.print("Goal: ");
  lcd.print(levelScoreRequirements[currentLevel]);
  displayImage(IMAGES[HOME_IMAGE]);

  startLevel(currentLevel);

  //printEntityMatrix();
}


void startLevel(int level) {  //Separate function for starting a level, because some values don't have to be reset
  for (int i = 1; i < matrixSize; i++) {
    for (int j = 1; j < matrixSize - 1; j++) {
      if (i != currentX || j != currentY) {
        int randomNumber = random(NINE - level);       //9 is just a value that felt right
        if (randomNumber == 0 || randomNumber == 1) {  // randomly generate enemies around the room
          entityMatrix[i][j] = ENEMY;
        } else {
          entityMatrix[i][j] = EMPTY;
        }

        matrix[i][j] = entityMatrix[i][j];
      }
    }
  }
  currentX = initialX;
  currentY = initialY;
  entityMatrix[int(initialX)][int(initialY)] = PLAYER;
  entityMatrix[int(initialX)][int(initialY) + 1] = matrix[int(initialX)][int(initialY) + 1] = false;

  wallMoveFrameDelay -= wallDelayModifier;
  levelUp = false;
  wallIndex = 0;
  wallMoveFrameCounter = 0;

  entityMatrix[0][matrixSize / 2 - 1] = entityMatrix[0][matrixSize / 2] = WALL;               //Close the door
  matrix[0][matrixSize / 2 - 1] = matrix[0][matrixSize / 2] = matrix[0][matrixSize / 2 - 2];  //Sync current blink status
}

void updateSound() {  //Sound that happens while the game is running, so we work with frames

  if (makeLaserSound) {
    switch (laserSoundCounter) {
      case FRAME_1:
        {
          tone(buzzerPin, FREQUENCY_1000, LASER_SOUND_DURATION);
          break;
        }
      case FRAME_4:
        {
          tone(buzzerPin, FREQUENCY_1500, LASER_SOUND_DURATION);
          makeLaserSound = false;
          laserSoundCounter = 0;
          break;
        }
      default:
        {
          break;
        }
    }
    laserSoundCounter++;
  }
  if (makeExplosionSound) {
    switch (explosionSoundCounter) {
      case FRAME_1:
        {
          tone(buzzerPin, FREQUENCY_900, EXPLOSION_SOUND_DURATION_1);
          break;
        }
      case FRAME_7:
        {
          tone(buzzerPin, FREQUENCY_1200, EXPLOSION_SOUND_DURATION_2);
          break;
        }
      case FRAME_16:
        {
          tone(buzzerPin, FREQUENCY_1000, EXPLOSION_SOUND_DURATION_3);
          makeExplosionSound = false;
          explosionSoundCounter = 0;
          break;
        }
      default:
        {
          break;
        }
    }
    explosionSoundCounter++;
  }
  if (makeCoinSound) {
    switch (coinSoundCounter) {
      case 1:
        {
          tone(buzzerPin, NOTE_B5, COIN_SOUND_DURATION_1);
          //tone(buzzerPin, NOTE_E6, 720);
          break;
        }
      case FRAME_4:
        {
          tone(buzzerPin, NOTE_E6, COIN_SOUND_DURATION_2);
          makeCoinSound = false;
          coinSoundCounter = 0;
          break;
        }
      default:
        {
          break;
        }
    }
    coinSoundCounter++;
  }
}

void updateEndgameSounds() {  //Sound that happens while the game is running, so we work with millis()
  if (makeWinSound) {
    switch (winSoundCounter) {
      case 0:
        {
          winSoundCounter++;
          tone(buzzerPin, NOTE_C5, WIN_SOUND_DURATION_1);
          break;
        }
      case 1:
        {
          if ((millis() - soundMillis) > WIN_SOUND_DELAY_1) {
            winSoundCounter++;
            tone(buzzerPin, NOTE_D5, WIN_SOUND_DURATION_1);
          }
          break;
        }
      case 2:
        {
          if ((millis() - soundMillis) > WIN_SOUND_DELAY_2) {
            winSoundCounter++;
            tone(buzzerPin, NOTE_E5, WIN_SOUND_DURATION_1);
          }
          break;
        }
      case 3:
        {
          if ((millis() - soundMillis) > WIN_SOUND_DELAY_3) {
            winSoundCounter++;
            tone(buzzerPin, NOTE_G5, WIN_SOUND_DURATION_2);
          }
          break;
        }
      case 4:
        {
          if ((millis() - soundMillis) > WIN_SOUND_DELAY_4) {
            //noTone(buzzerPin);
            makeWinSound = false;

            winSoundCounter = 0;
            needUpdate = true;
          }
          break;
        }
      default:
        {
          break;
        }
    }
  }
  if (makeLoseSound) {
    switch (loseSoundCounter) {
      case 0:
        {
          loseSoundCounter++;
          tone(buzzerPin, NOTE_G4, LOSE_SOUND_DURATION_1);
          break;
        }
      case 1:
        {
          if ((millis() - soundMillis) > LOSE_SOUND_DELAY_1) {
            loseSoundCounter++;
            tone(buzzerPin, NOTE_F4, LOSE_SOUND_DURATION_1);
          }
          break;
        }
      case 2:
        {
          if ((millis() - soundMillis) > LOSE_SOUND_DELAY_2) {
            loseSoundCounter++;
            tone(buzzerPin, NOTE_D4, LOSE_SOUND_DURATION_1);
          }
          break;
        }
      case 3:
        {
          if ((millis() - soundMillis) > LOSE_SOUND_DELAY_3) {
            loseSoundCounter++;
            tone(buzzerPin, NOTE_A3, LOSE_SOUND_DURATION_2);
          }
          break;
        }
      case 4:
        {
          if ((millis() - soundMillis) > LOSE_SOUND_DELAY_4) {
            makeLoseSound = false;
            loseSoundCounter = 0;
            needUpdate = true;
          }
          break;
        }
      default:
        {
          break;
        }
    }
  }
}
#define LONG_SIZE 4
const int numberOfHighsocres = 3;
void checkHighscore() {  //Utility function for checking if we reach a new highscore when the game ends
  if (score > highscores[0]) {
    lcd.clear();
    lcd.setCursor(ZERO, ZERO);

    lcd.print("!NEW NIGHSCORE!");
    lcd.setCursor(SIX, ONE);
    lcd.print(score);

    highscore = true;
  }
  for (int i = 0; i < numberOfHighsocres; i++) {
    if (score > highscores[i]) {
      for (int j = numberOfHighsocres - 1; j >= i; j--) {
        highscores[j] = highscores[j - 1];
        EEPROM.put(HIGHSCORE_BYTE + (j * LONG_SIZE), highscores[j - 1]);
        strcpy(highscoreNames[j], highscoreNames[j - 1]);
        EEPROM.put(HIGHSCORE_NAMES_BYTE + (j * LONG_SIZE), highscoreNames[j - 1]);
      }
      highscores[i] = score;
      EEPROM.put(HIGHSCORE_BYTE + (i * LONG_SIZE), score);

      strcpy(highscoreNames[i], currentName);
      EEPROM.put(HIGHSCORE_NAMES_BYTE + i * LONG_SIZE, currentName);
      return;
    }
  }
}



void handleMenu() {
  displayMenu();
  handleMenuInput();
}



void displayMenu() {
  //This is just a big switch case
  debounce(leftSwitchPin, lastSwitchReading, lastSwitchDebounceTime, switchButtonState, switchRequest);
  switch (menuState) {
    case MAIN_MENU:  //Main menu
      {
        displayImage(IMAGES[HOME_IMAGE]);  //Display the main menu
        if (upMenuInput) {                 //Handle scrolling through the main menu, this should have been a separate function
          if (mainMenuIndex > 0) {
            mainMenuIndex--;
            needUpdate = true;
          }
          upMenuInput = false;
        }
        if (downMenuInput) {
          if (mainMenuIndex < mainMenuSize - 1) {
            mainMenuIndex++;
            needUpdate = true;
          }
          downMenuInput = false;
        }
        if (leftMenuInput) {
          leftMenuInput = false;
        }
        if (rightMenuInput) {
          rightMenuInput = false;
        }
        if (needUpdate) {
          if (soundOn) {
            tone(buzzerPin, FREQUENCY_1500, LASER_SOUND_DURATION);
          }
          printOptions(mainMenuOptions, mainMenuSize, mainMenuIndex);
          needUpdate = false;
        }

        switch (mainMenuIndex) {
          case MAIN_MENU_START:  //Start game
            {
              if (switchRequest) {
                switchRequest = false;
                startGame();
              }
              break;
            }
          case MAIN_MENU_HIGHSCORES:  //Highscores
            {

              if (switchRequest) {
                switchRequest = false;
                needUpdate = true;
                menuState = HIGHSCORE;
                for (int i = 0; i < numberOfHighsocres; i++) {
                  highscoreMenuOptions[i] = String(highscoreNames[i]) + " " + String(highscores[i]);  //Create the highscoreMenuOptions String by combining the name and its corresponding score
                }
                highscoreMenuIndex = 0;
              }
              break;
            }
          case MAIN_MENU_NAME:  // Change name
            {
              if (switchRequest) {
                menuState = EXECUTING_CODE;
                codeToExecute = CHANGE_NAME;
                lcd.clear();
                lcd.setCursor(TWO, ZERO);
                lcd.print("CHOOSE NAME");
                lcd.setCursor(FIVE, ONE);
                lcd.print("-");
                lcd.print(currentName);
                lcd.print("-");
                lcd.setCursor(SIX, ONE);
                //lcd.cursor();
                switchRequest = false;
              }
              break;
            }
          case MAIN_MENU_SETTINGS:  //Settings
            {
              if (switchRequest) {
                switchRequest = false;
                needUpdate = true;
                menuState = SETTINGS;
              }
              break;
            }
          case MAIN_MENU_HOWTO:  //How to play
            {
              if (switchRequest) {
                switchRequest = false;
                needUpdate = true;
                menuState = EXECUTING_CODE;
                codeToExecute = HOWTO_CODE;
                iCursor = 0;
                lcd.clear();
                lcd.setCursor(TWO, ZERO);
                lcd.print("How To Play");
              }
              break;
            }
          case MAIN_MENU_ABOUT:  //About
            {
              if (switchRequest) {
                switchRequest = false;
                needUpdate = true;
                menuState = EXECUTING_CODE;
                codeToExecute = ABOUT_CODE;
                iCursor = 0;
                lcd.clear();
                lcd.setCursor(FIVE, ZERO);
                lcd.print("About");
              }
              break;
            }
          default:
            {
              break;
            }
        }


        break;
      }
    case SETTINGS:  //Settings sub-menu
      {
        displayImage(IMAGES[SETTINGS_IMAGE]);
        if (upMenuInput) {
          if (settingsMenuIndex > 0) {
            settingsMenuIndex--;
            needUpdate = true;
          }
          upMenuInput = false;
        }
        if (downMenuInput) {
          if (settingsMenuIndex < settingsMenuSize - 1) {
            settingsMenuIndex++;
            needUpdate = true;
          }
          downMenuInput = false;
        }
        if (leftMenuInput) {
          leftMenuInput = false;
        }
        if (rightMenuInput) {
          rightMenuInput = false;
        }
        if (needUpdate) {
          if (soundOn) {
            tone(buzzerPin, FREQUENCY_1500, LASER_SOUND_DURATION);
          }
          printOptions(settingsMenuOptions, settingsMenuSize, settingsMenuIndex);
          needUpdate = false;
        }
        switch (settingsMenuIndex) {
          case SETTINGS_LCD_BRIGHTNESS:  //Lcd brightness
            {
              if (switchRequest) {
                menuState = EXECUTING_CODE;
                codeToExecute = LCD_BRIGHTNESS;
                lcd.clear();
                lcd.setCursor(ONE, ZERO);
                lcd.print("LCD brightness");
                lcd.setCursor(EIGHT, ONE);
                lcd.print(lcdBrightness);
                switchRequest = false;
              }
              break;
            }
          case SETTINGS_MAT_BRIGHTNESS:  //Matrix brightness
            {
              if (switchRequest) {
                menuState = EXECUTING_CODE;
                codeToExecute = MAT_BRIGHTNESS;
                lcd.clear();
                lcd.setCursor(ONE, ZERO);
                lcd.print("Mat brightness");
                lcd.setCursor(EIGHT, ONE);
                lcd.print(matrixBrightness);
                switchRequest = false;
              }

              break;
            }
          case SETTINGS_SOUND_TOGGLE:
            {
              if (switchRequest) {
                makeExplosionSound = false;
                makeWinSound = false;
                makeLoseSound = false;
                makeLaserSound = false;
                makeCoinSound = false;
                soundOn = !soundOn;
                if (soundOn) {
                  tone(buzzerPin, FREQUENCY_1500, LASER_SOUND_DURATION);
                }
                menuState = SETTINGS;
                switchRequest = false;
              }
            }
          case SETTINGS_BACK:  //Back
            {

              if (switchRequest) {
                menuState = MAIN_MENU;
                needUpdate = true;
                switchRequest = false;
              }
              break;
            }
        }


        break;
      }
    case HIGHSCORE:  // Highscores sub-menu
      {
        displayImage(IMAGES[HIGHSCORE_IMAGE]);
        if (needUpdate) {
          if (soundOn) {
            tone(buzzerPin, FREQUENCY_1500, LASER_SOUND_DURATION);
          }
          printOptions(highscoreMenuOptions, highscoreMenuSize, highscoreMenuIndex);
          needUpdate = false;
        }
        if (upMenuInput) {
          if (highscoreMenuIndex > 0) {
            highscoreMenuIndex--;
            needUpdate = true;
          }
          upMenuInput = false;
        }
        if (downMenuInput) {
          if (highscoreMenuIndex < highscoreMenuSize - 1) {
            highscoreMenuIndex++;
            needUpdate = true;
          }
          downMenuInput = false;
        }
        if (leftMenuInput) {
          leftMenuInput = false;
        }
        if (rightMenuInput) {
          rightMenuInput = false;
        }
        switch (highscoreMenuIndex) {
          case HIGHSCORES_RESET:  //Reset highscores
            {
              if (switchRequest) {
                Serial.println("reset");
                for (int i = HIGHSCORE_BYTE; i < STOP_BYTE; i++) {
                  EEPROM.update(i, 0);
                }
                for (int i = 0; i < 3; i++) {
                  EEPROM.get(HIGHSCORE_BYTE + i * LONG_SIZE, highscores[i]);
                  EEPROM.get(HIGHSCORE_NAMES_BYTE + i * LONG_SIZE, highscoreNames[i]);
                }
                menuState = MAIN_MENU;
                needUpdate = true;
                switchRequest = false;
              }
              break;
            }
          case HIGHSCORES_BACK:  //Back
            {
              if (switchRequest) {
                menuState = MAIN_MENU;
                needUpdate = true;
                switchRequest = false;
              }
              break;
            }
          default:
            {
              if (switchRequest) {
                switchRequest = false;
              }
              break;
            }
        }


        break;
      }
    case EXECUTING_CODE:  //This is used for sub-menus that require user input
      {
        switch (codeToExecute) {
          case LCD_BRIGHTNESS:  //Lcd brightness
            {
              if (needUpdate) {
                if (soundOn) {
                  tone(buzzerPin, FREQUENCY_1500, LASER_SOUND_DURATION);
                }
                lcd.setCursor(EIGHT, ONE);
                lcd.print(lcdBrightness);
                needUpdate = false;
              }
              if (upMenuInput) {
                if (lcdBrightness < numberOfOptions) {
                  lcdBrightness++;
                  analogWrite(lcdBrightnessPin, lcdBrightness * lcdBrightnessModifier);
                  needUpdate = true;
                }
                upMenuInput = false;
              }
              if (downMenuInput) {
                if (lcdBrightness > 0) {
                  lcdBrightness--;
                  analogWrite(lcdBrightnessPin, lcdBrightness * lcdBrightnessModifier);
                  needUpdate = true;
                }
                downMenuInput = false;
              }
              if (leftMenuInput) {
                if (lcdBrightness > 0) {
                  lcdBrightness--;
                  analogWrite(lcdBrightnessPin, lcdBrightness * lcdBrightnessModifier);
                  needUpdate = true;
                }
                leftMenuInput = false;
              }
              if (rightMenuInput) {
                if (lcdBrightness < numberOfOptions) {
                  lcdBrightness++;
                  analogWrite(lcdBrightnessPin, lcdBrightness * lcdBrightnessModifier);
                  needUpdate = true;
                }
                rightMenuInput = false;
              }

              if (switchRequest) {
                menuState = SETTINGS;
                switchRequest = false;
                needUpdate = true;
                EEPROM.put(LCD_BRIGHTNESS_BYTE, lcdBrightness);
              }
              break;
            }
          case MAT_BRIGHTNESS:  //Matrix brightness
            {
              if (needUpdate) {
                if (soundOn) {
                  tone(buzzerPin, FREQUENCY_1500, LASER_SOUND_DURATION);
                }
                lcd.setCursor(EIGHT, ONE);
                lcd.print(matrixBrightness);
                needUpdate = false;
              }
              if (upMenuInput) {
                if (matrixBrightness < numberOfOptions) {
                  matrixBrightness++;
                  lc.setIntensity(0, matrixBrightness * matrixBrightnessModifier);
                  needUpdate = true;
                }
                upMenuInput = false;
              }
              if (downMenuInput) {
                if (matrixBrightness > 0) {
                  matrixBrightness--;
                  lc.setIntensity(0, matrixBrightness * matrixBrightnessModifier);
                  needUpdate = true;
                }
                downMenuInput = false;
              }
              if (leftMenuInput) {
                if (matrixBrightness > 0) {
                  matrixBrightness--;
                  lc.setIntensity(0, matrixBrightness * matrixBrightnessModifier);
                  needUpdate = true;
                }
                leftMenuInput = false;
              }
              if (rightMenuInput) {
                if (matrixBrightness < numberOfOptions) {
                  matrixBrightness++;
                  lc.setIntensity(0, matrixBrightness * matrixBrightnessModifier);
                  needUpdate = true;
                }
                rightMenuInput = false;
              }

              if (switchRequest) {
                EEPROM.put(MATRIX_BRIGHTNESS_BYTE, matrixBrightness);
                menuState = SETTINGS;
                switchRequest = false;
                needUpdate = true;
              }
              break;
            }
          case CHANGE_NAME:  //Chaning name
            {

              if (millis() - cursorMillis > cursorToggleDelay) {
                if (cursorToggled) {
                  lcd.noCursor();
                  cursorToggled = false;
                } else {
                  lcd.cursor();
                  cursorToggled = true;
                }
                cursorMillis = millis();
              }

              if (needUpdate) {
                if (soundOn) {
                  tone(buzzerPin, FREQUENCY_1500, LASER_SOUND_DURATION);
                }

                needUpdate = false;
              }
              if (upMenuInput) {
                if (currentName[currentNameIndex] == 'Z') {
                  currentName[currentNameIndex] = 'A';
                } else {
                  currentName[currentNameIndex]++;
                }
                lcd.print(currentName[currentNameIndex]);
                lcd.setCursor(SIX + currentNameIndex, ONE);
                Serial.println(currentName);
                upMenuInput = false;
              }
              if (downMenuInput) {
                if (currentName[currentNameIndex] == 'A') {
                  currentName[currentNameIndex] = 'Z';
                } else {
                  currentName[currentNameIndex]--;
                }
                lcd.print(currentName[currentNameIndex]);
                lcd.setCursor(SIX + currentNameIndex, ONE);
                Serial.println(currentName);
                downMenuInput = false;
              }
              if (leftMenuInput) {
                currentNameIndex = clamp(currentNameIndex - 1, ZERO, TWO);
                lcd.setCursor(SIX + currentNameIndex, ONE);
                //needUpdate=true;
                leftMenuInput = false;
              }
              if (rightMenuInput) {
                currentNameIndex = clamp(currentNameIndex + 1, ZERO, TWO);
                lcd.setCursor(SIX + currentNameIndex, ONE);
                rightMenuInput = false;
              }
              if (switchRequest) {
                EEPROM.put(NAME_BYTE, currentName);

                menuState = MAIN_MENU;
                switchRequest = false;
                needUpdate = true;
                lcd.noCursor();
              }
              break;
            }
          case ABOUT_CODE:  //About (requires user to press the joystick to exit)
            {
              scrollLcd(aboutString);
              if (switchRequest) {
                menuState = MAIN_MENU;
                needUpdate = true;
                switchRequest = false;
              }

              break;
            }
          case HOWTO_CODE:  //How to play
            {
              scrollLcd(howToString);
              if (switchRequest) {
                menuState = MAIN_MENU;
                needUpdate = true;
                switchRequest = false;
              }

              break;
            }
        }
        break;
      }
    case ENDGAME:  //Waits for the user to press the joystick before returning to the main manu
      {
        if (win) {
          displayImage(IMAGES[WIN_IMAGE]);
        } else {
          displayImage(IMAGES[LOSE_IMAGE]);
        }
        if (switchRequest) {
          menuState = MAIN_MENU;
          switchRequest = false;
          needUpdate = true;
        }
      }
  }
}





void printOptions(String options[], int size, int index) {  //Function used to print a string array to the lcd display. It will print 2 strings, and if it's the last string of the array, it will move a "pointer" to it
  lcd.clear();
  if (index < size - 1) {
    lcd.setCursor(0, 0);
    lcd.print(">");
    lcd.setCursor(1, 0);
    lcd.print(options[index]);
    lcd.setCursor(1, 1);
    lcd.print(options[index + 1]);
  } else {
    lcd.setCursor(1, 0);
    lcd.print(options[index - 1]);
    lcd.setCursor(0, 1);
    lcd.print(">");
    lcd.setCursor(1, 1);
    lcd.print(options[index]);
  }
}



void handleMenuInput() {
  int xValue = analogRead(A0);  // Read X-axis value
  int yValue = analogRead(A1);  // Read Y-axis value
  int coordSum = xValue + yValue;
  if ((xValue > middle - deadZone && xValue < middle + deadZone && yValue > middle - deadZone && yValue < middle + deadZone)  //check if we are in the dead zone
      || abs(xValue - yValue) < joystickBuffer                                                                                //buffer for secondary diagonal
      || abs(xValue - yValue) > joystickRange - joystickBuffer) {                                                             //buffer for main diagonal
    joystickState = IDLE_STATE;
  } else if (xValue >= yValue && coordSum > joystickRange) {  //if x > y and their sum is greater than 1023, then the joystick is in the UP position
    //UP
    if (joystickState != UP_STATE && millis() - joystickMillis > joystickTimeBuffer) {

      joystickState = UP_STATE;
      upMenuInput = true;
      joystickMillis = millis();
      //needUpdate=true;
    }
  } else if (xValue > yValue && coordSum < joystickRange) {  //if x > y and their sum is not greater than 1023, then the joystick is in the LEFT position
    //LEFT
    if (joystickState != LEFT_STATE && millis() - joystickMillis > joystickTimeBuffer) {

      joystickState = LEFT_STATE;
      leftMenuInput = true;
      joystickMillis = millis();
    }
  } else if (xValue < yValue && coordSum > joystickRange) {  //if x < y and their sum is  greater than 1023, then the joystick is in the RIGHT position
    //RIGHT
    if (joystickState != RIGHT_STATE && millis() - joystickMillis > joystickTimeBuffer) {

      joystickState = RIGHT_STATE;
      rightMenuInput = true;
      joystickMillis = millis();
    }
  } else if (xValue < yValue && coordSum < joystickRange) {  //finally, if x < y and their sum is not greater than 1023, then the joystick is in the DOWN position
    //DOWN
    if (joystickState != DOWN_STATE && millis() - joystickMillis > joystickTimeBuffer) {

      joystickState = DOWN_STATE;
      downMenuInput = true;
      joystickMillis = millis();
      //needUpdate=true;
    }
  }
}



void debounce(const int inputPin, byte &lastReading, unsigned long &lastDebounceTime, byte &buttonState, byte &request) {  //Utility function for debouncing a button
  reading = digitalRead(inputPin);
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        request = 1;
      }
    }
  }
  lastReading = reading;
}

void death() {  //code to execute when the player dies
  running = false;
  checkHighscore();
  win = false;
  menuState = ENDGAME;
  displayEndgameMessage();
  makeLoseSound = true;
  soundMillis = millis();
}

void displayEndgameMessage() {  //When the game ends, a message will be displayed on the lcd
  lcd.clear();
  lcd.setCursor(THREE, ZERO);
  if (highscore) {
    lcd.setCursor(ZERO, ZERO);
    lcd.print("!NEW NIGHSCORE!");
    highscore = false;
  } else {
    lcd.setCursor(THREE, ZERO);
    lcd.print("Final Score");
  }
  lcd.setCursor(SIX, ONE);
  lcd.print(score);
}
void scrollLcd(char str[]) {  //Function used to scroll only one line of the lcd display
  if (millis() - scrollMillis > scrollDelay) {
    Serial.println("Test");
    if (iCursor == (strlen(str) - 1)) {
      iCursor = 0;
    }
    lcd.setCursor(0, 1);
    if (iCursor < strlen(str) - numberOfColumns) {
      for (int iChar = iCursor; iChar < iCursor + numberOfColumns; iChar++) {
        lcd.print(str[iChar]);
      }
    } else {
      for (int iChar = iCursor; iChar < (strlen(str) - 1); iChar++) {
        lcd.print(str[iChar]);
      }

      for (int iChar = 0; iChar <= numberOfColumns - (strlen(str) - iCursor); iChar++) {
        lcd.print(str[iChar]);
      }
    }
    iCursor++;
    scrollMillis = millis();
  }
}

int clamp(int value, int min, int max) {  //Utility function, extremely useful
  if (value < min) {
    return min;
  }
  if (value > max) {
    return max;
  }
  return value;
}
