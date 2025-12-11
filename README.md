# PIC16F877A ELECTRONIC DICE GAME 🎲

This project implements a **two-player electronic dice game** using the **PIC16F877A microcontroller**, a 16x2 LCD, LEDs, and push buttons.  
The entire circuit is simulated in **Proteus 8 Professional**, and the firmware is written in **CCS C**. :contentReference[oaicite:0]{index=0}

Each player rolls the dice three times, and after all rounds are completed, the player with the highest total score wins. The LCD guides the user through the entire gameplay.

---

# GAME FLOW

1. When powered on, the LCD displays:

   **“Please Press the Start Game Button!”**

2. When the **RUN button (RC0)** is pressed:
   - A welcome animation scrolls across the LCD.
   - The message **“Press START!”** appears.

3. For each round:
   - Player 1 rolls the dice using the **START button (RA0)**.
   - Pressing START again rolls the dice for Player 2.
   - This sequence repeats for **3 total rounds**.

4. After all rounds:
   - The LCD displays each player’s dice results.
   - Then the total scores and the winner are shown.

5. At the end of the game:
   - The LCD displays **“Press RESET to Restart!”**
   - Pressing **RESET (RC1)** restarts the entire system.

---

# HARDWARE COMPONENTS

- **Microcontroller:** PIC16F877A  
- **Clock Source:** 4 MHz Crystal Oscillator  
- **Display:** 16x2 Character LCD (4-bit mode)  
- **Buttons:**  
  - RUN button → `RC0`  
  - RESET button → `RC1`  
  - START button → `RA0`  
- **LEDs:**  
  - 8 LEDs on pins `RD0–RD7` for animation effects  
- **Other Components:**  
  - 22 pF capacitors for the crystal  
  - Pull-up / Pull-down resistors  
- **Simulation Software:** Proteus 8 Professional  

LCD pin mapping used in the code:

```c
#define LCD_RS_PIN PIN_B1
#define LCD_RW_PIN PIN_B2
#define LCD_E_PIN  PIN_B0
#define LCD_D4_PIN PIN_B4
#define LCD_D5_PIN PIN_B5
#define LCD_D6_PIN PIN_B6
#define LCD_D7_PIN PIN_B7
```

# VIDEO


https://github.com/user-attachments/assets/53522989-2fc1-4911-ba90-515e4272e875


LICENSE

This project is for educational purposes.
Feel free to modify, improve, or use it in your own microcontroller applications.
