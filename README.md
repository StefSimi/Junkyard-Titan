# Junkyard Titan

## About

A project utilizing Arduino, created as part of the Introduction to Robotics course in the third year at the Faculty of Mathematics and Computer Science, University of Bucharest.

## Project Details 



The project is a game presented on an 8x8 LED matrix, a menu for the game displayed on an LCD, and a controller consisting of two joysticks.


<details>
<summary><h2>Gameplay</h2></summary>

## Game loop:

* You start off in a 16x16 room, although you can only view a portion of it on the matrix. You can move freely around the room, however, the left and right walls will start to close in on you. In order to escape, you have to destroy objects around the room, and sell them to obtain points. You move with the left joystick, and shoot with the right joystick. Both of these support 360 degree movement, so you can shoot and move diagonally if you want to. When you hit an object, a 3x3 explosion will occur around it. If you are caught within the explosion, you will die. After the explosion dies down, the amount of objects destroyed will be added to an inventory slot. You only have 4 inventory slots. You can press the left joystick to "channel" for a few moments, this will sell all of the items in your current inventory, and give you points. The more objects caught inside a single explosion, the more that item costs. After you meet a quota, the door to the room will open. You can directly go to the next level, or farm more items from the current room. Be careful not to remain trapped though! When you exit the room, the level ends, and a new one begins, with a higher quota, but with additional objects in the room. The item costs also increase. This gameplay loop continues until the player dies, either by getting caught within an explosion, or by getting squished by the walls if he fails to meet the quota. Most actions have sounds associated with them, so the game feels more lively. You can press the right joystick to pause the game;

## Technical details:

*  The game plays at set rate of 60 frames per second (FPS). During each frame, every entity inside of the game is updated, and then the matrix is rendered. Working at a set FPS can be very befenicial for upscaling this project, however, it also introduces multiple problems. For instance, if the player can move 1 position every frame, then it it will cross the matrix in 8 frames, which is about 133 milliseconds. To combat this, we can either update the player position every so often, which would in turn cause even more problems, or introduce floating point logic for every single entity position, which may sound complicated, but all that it does is change the positions by a little bit during each frame, and if these changes add up to an integer, then the position on the matrix changes;<br>

</details>

<details>
<summary><h2>Menu</h2></summary>

**Navigation:** Use the left joystick to move through the menu, and press it to enter a specific option

Menu layout

- Start game<br>
- Highscores <br>
  - Name 1 Score 1 <br>
  - Name 2 Score 2 <br>
  - Name 3 Score 3 <br>
  - Reset Data <br>
  - Back <br>
- Change Name<br>
- Settings<br>
  - LCD Brightness<br>
  - Matrix Brightness<br>
  - Toggle Sound<br>
  - Back <br>
- How to play<br>
- About<br>
</details>

<details>
<summary><h2>Backstory </h2></summary>
<br>

You are one of the last humans on Earth, after a nuclear apocalypse has consumed the planet. The rich have moved to space, and couldn't care less about you. However, they still need items from the ground. These can only be found in garbage dumps, as robots automatically transport objects from around the world to these squished to be incinerated, in order to clean up the planet. You can use this to your advantage: you will sneak in and grab stuff using your atomic disassembler, and instantly transport the valuables off-world for a quick buck. This, of course, comes with a pretty high risk: you are in an incineration plant, after all, and you can only enter just as the fire is about to start. You manage to talk one of the guards to let you in, but they will only let you out if you share some of the profit with them. Good luck!

</details>




<details>
<summary><h2>Project Requirements </h2></summary>

### Menu Requirements

• Menu Task: Create a menu for your game, emphasis on ‘the game. You
should scroll on the LCD with the joystick. Remember you have quite a
lot of flexibility here, but do not confuse that with a free ticket to slack
off. The menu should include the following functionality:<br>
1. Intro Message - When powering up a game, a greeting message
should be shown for a few moments.<br>
2. Should contain roughly the following categories:<br>
(a) Start game, starts the initial level of your game<br>
(b) Highscore:<br>
– Initially, we have 0.<br>
– Update it when the game is done. Highest possible score
should be achieved by starting at a higher level.<br>
– Save the top 3+ values in EEPROM with name and score.<br>
(c) Settings:<br>
– Enter name. The name should be shown in highscore. Maybe
somewhere else, as well? You decide.<br>
– LCD brightness control (mandatory, must change LED wire
that’s directly connected to 5v). Save it to eeprom.<br>
– Matrix brightness control (see function setIntesnity from the
ledControl library). Make sure to display something on the
matrix when selecting it. Save it to eeprom.<br>
– Sounds on or off. Save it to eeprom.<br>
– Extra stuff can include items specific to the game mechanics,
or other settings such as chosen theme song etc. Again, save
it to eeprom. You can even split the settings in 2: game
settings and system settings.<br>
(d) About: should include details about the creator(s) of the game.
At least game name, author and github link or user (use scrolling
text?)<br>
(e) How to play: short and informative description<br>
3. While playing the game: display all relevant info<br>
– Lives<br>
– Level<br>
– Score<br>
– Time?<br>
– Player name?<br>
– etc<br>
4. Upon game ending:<br>
(a) Screen 1: a message such as ”Congratulations on reaching level/score
X”. ”You did better than y people.” etc. Switches to screen 2
upon interaction (button press) or after a few moments.<br>
(b) Screen 2: display relevant game info: score, time, lives left etc.
Must inform player if he/she beat the highscore. This
menu should only be closed by the player, pressing a button.<br>

### Game Requirements
– Minimal components: an LCD, a joystick, a buzzer and the led
matrix.<br>
– You must add basic sounds to the game (when ”eating” food, when
dying, when finishing the level etc). Extra: add theme songs.<br>
– Each level / instance should work on 16x16 matrix. You can apply
the concept of visibility / fog of war (aka you only see 8x8 of the
total 16x16 matrix, and you discover more as you move around) or
you can use the concept of ”rooms”. Basically you will have 4 rooms
that you need to go through on each level.<br>
– It must be intuitive and fun to play.<br>
– It must make sense in the current setup.<br>
– You should have a feeling of progression in difficulty. Depending
on the dynamic of the game, this is done in the same level or with
multiple levels. You can make them progress dynamically or have
a number of fixed levels with an endgame. Try to introduce some
randomness, though.<br>
</details>

<details>
   <summary>
     <h2>Parts used
   </summary>
    -Arduino UNO board <br>
    -2 Breadboards <br>
    -1 8X8 LED Matrix <br>
    -1 MAX7219 Driver <br>
    -1 100nF capacitor<br>
    -1 10µF capacitor <br>
    -1 51KΩ Resistor <br>
    -1 Active Buzzer <br>
    -1 100Ω Resistor <br>
    -2 Joysticks <br>
    -Wires as needed <br>
    -Cardboard <br>
    -Duct tape <br>
    -1 LCD Display <br>
    -1 220Ω Resistor <br>
    -1 Potentiometer <br>
 </details>

<details>
<summary><h2>Showcase </h2></summary>

### [Code](https://github.com/StefSimi/Junkyard-Titan/blob/main/Junkyard%20Titan.ino)
### [Video](https://www.youtube.com/watch?v=XEKqY0s9G2o)


### [Fritzing Schematic](https://github.com/StefSimi/Junkyard-Titan/blob/main/Junkyard%20Titan.fzz)
### ![Fritzing schematic](https://github.com/StefSimi/Junkyard-Titan/assets/98825330/360f39c1-b4ab-4681-a96b-7c77717a85e9)


### Real-life setup:
### ![Setup](https://github.com/StefSimi/Junkyard-Titan/assets/98825330/852499ad-c17b-49ca-be5e-2f4a93962bf1)




</details>
