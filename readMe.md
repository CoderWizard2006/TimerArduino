# Arduino Countdown Timer with Keypad and LCD ⌚⌚

## Project Overview
This project is a fully functional **countdown timer** built using an Arduino, a 16x2 I2C LCD display, and a 4x4 keypad. Users can set hours, minutes, and seconds, start, pause, and reset the timer using the keypad. The timer provides visual feedback on the LCD and alerts when the countdown reaches zero.

---

## Features
- **Time Setting Mode**: Set the timer using the numeric keys (0–9).  
- **Cursor Navigation**: Use **A** to move cursor forward and **B** to move cursor backward while setting time.  
- **Start Timer**: Press **C** to start the countdown.  
- **Pause Timer**: Press **\*** to pause/resume the countdown.  
- **Reset Timer**: Press **D** to reset the timer to 00:00:00.  
- **LCD Display**: Shows time in **HH:MM:SS** format.  
- **Timer Alert**: An LED lights up for 5 seconds when the timer reaches zero.

---

## Components Needed
- Arduino Uno (or compatible board)  
- 16x2 I2C LCD display  
- 4x4 Matrix Keypad  
- Jumper wires  
- Breadboard (optional)  
- LED (optional, connected to pin 13 for timer alert)  

---

## Wiring
### LCD
- SDA → A4 (Arduino Uno)  
- SCL → A5 (Arduino Uno)  
- VCC → 5V  
- GND → GND  

### Keypad
- Connect the 4 row pins and 4 column pins to Arduino digital pins (2–9 in this project).  

### LED
- Anode → Pin 13  
- Cathode → GND  

---

## How to Use
1. Power on the Arduino.  
2. The LCD will guide you through the instructions:  
   - Press **A** to move cursor forward.  
   - Press **B** to move cursor backward.  
   - Press **C** to start the timer.  
   - Press **D** to reset the timer.  
3. Enter the desired time using the numeric keys.  
4. Press **C** to start the countdown.  
5. Press **\*** to pause/resume the timer.  
6. When the timer reaches zero, the LED will light up for 5 seconds.  

---

## Code Structure
- **setup()**: Initializes LCD, keypad, and shows instructions.  
- **loop()**: Handles user input and runs the countdown timer.  
- **displayTime()**: Updates the LCD with the current HH:MM:SS.  
- **handleSettingMode()**: Handles time setting with cursor movement.  
- **countdown()**: Decrements time every second and triggers timer alert.

---

## Notes
- This project uses **PlatformIO** with `.cpp` files. The main file is located in the `src` folder.  
- Timer updates are handled using `millis()` to avoid blocking delays.  
- The code is modular, making it easy to extend features such as buzzer alerts, multiple presets, or different display formats.

---

## Author
**Chinmay Chitvan**

---

## License
This project is open-source and free to use for personal and educational purposes.


## Future Improvements
- Add a **buzzer** to sound when the timer reaches zero.  
- Show a **blinking cursor (`_`)** under the currently edited digit for better user experience.   
- Add **count-up mode** for stopwatch functionality.  
- Improve UI with **scrolling messages** or animations on the LCD.  