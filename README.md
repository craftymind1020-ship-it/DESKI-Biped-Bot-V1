# 2-Servo Biped Robot with Bluetooth Control and OLED Expressions

## Overview
This project is a minimal biped walking robot built using only 2 servo motors.  
Unlike typical biped robots that use multiple servos, this design focuses on achieving movement and balance with very limited hardware.

The robot can be controlled using Bluetooth commands and can display multiple facial expressions on an OLED screen.

---

## Features
- Walks forward using Bluetooth commands (example: "forward 5")
- Controlled wirelessly via mobile/serial Bluetooth app
- Displays multiple expressions on OLED screen
- Built using only 2 servos (minimal hardware design)

---

## Expressions Supported
The robot can display the following expressions:

- you are ugly(angry reaction)
- smile
- cheese
- cry
- sleep
- wake
- shoot (animation of a bullet hitting and cracking the screen)

---

## How It Works
- The robot receives commands via Bluetooth
- Based on the input:
  - It moves forward using a stepping sequence
  - Or updates the OLED display with a specific expression
- Movement is controlled by carefully timed servo angles to maintain balance

---

## Example Commands

| Command     | Action                                                         |
|-------------|----------------------------------------------------------------|
| forward 1   | Move one step forward                                          |
| forward 10  | Move multiple steps forward                                    |
| You are ugly| Show angry expression                                          |
| smile       | Show smiling face                                              |
| cheese      | Show happy expression                                          |
| cry         | Show crying face                                               |
| sleep       | Show sleeping face                                             |
| wake        | Wake up animation(also used to make it stop crying)            |
| shoot       | Bullet animation                                               |

---

## Components Used
- ESP32
- 2x Servo Motors
- OLED Display
- Jumper Wires
---

## 🔌 Wiring

### 🧠 Microcontroller
- ESP32

---

### 🤖 Servos

Each servo has **3 wires**:
- **Red → VCC (Power)**
- **Brown/Black → GND**
- **Yellow/Orange → Signal**

#### Connections:

| Servo        | Signal Pin | VCC        | GND |
|--------------|-----------|------------|-----|
| Left Servo   | GPIO 25   | External 5V | Common GND |
| Right Servo  | GPIO 26   | External 5V | Common GND |

---

### ⚠️ Servo Power (CRITICAL)

- DO NOT power servos from ESP32 5V pin ❌  
- Use an **external battery (recommended)**  

Example:
- 2x 3.7V Li-ion batteries (in series) or regulated 5V  

---

### 🔗 Common Ground (VERY IMPORTANT)

You MUST connect:
- Battery GND  
- ESP32 GND  
- Servo GND  

👉 All grounds should be connected together  

If not:
- Servos will jitter ❌  
- Robot may behave randomly ❌  

---

### 🖥️ OLED Display (I2C)

| OLED Pin | ESP32 Pin |
|----------|----------|
| VCC      | 3.3V / 5V |
| GND      | GND      |
| SDA      | GPIO 21  |
| SCL      | GPIO 22  |

- I2C Address: `0x3C`

---

### 📶 Bluetooth
- Built-in ESP32 Bluetooth used  
- No external module required  

Device Name:
ESP32_EYES

---

### 🔋 Power Summary

- Servos → External Battery  
- ESP32 → USB / Battery  
- OLED → ESP32 power  
- All grounds connected together  

---

## 🧩 Connection Summary
- Left Servo Signal → GPIO 25  
- Right Servo Signal → GPIO 26  
- Servo VCC → External 5V  
- Servo GND → Common GND  
- OLED SDA → GPIO 21  
- OLED SCL → GPIO 22  

---

## ⚠️ Important Notes
- Servos draw high current → external power is required  
- Without common GND, signals won’t work properly  
- Incorrect wiring may cause OLED failure or unstable movement  

---

## Challenges Faced
- Maintaining balance using only 2 servos
- Limited movement (no turning or backward movement yet)
- Small OLED limits visual detail
- Preventing the robot from falling while walking

---

## Future Improvements
- Add turning (left/right movement)
- Improve walking stability
- Use additional servos for better balance
- Improve OLED animations
- Add voice control or AI-based interaction

---

## Demo
https://drive.google.com/file/d/1dwXjC131IhD5XHVV8-G_h1PaHuegkTk5/view?usp=drive_link

---

## Images
<img width="1200" height="1600" alt="WhatsApp Image 2026-05-02 at 8 44 05 PM (3)" src="https://github.com/user-attachments/assets/202f7768-e95b-4d5e-97b3-b9e37eb9c936" />
<img width="1200" height="1600" alt="WhatsApp Image 2026-05-02 at 8 44 05 PM" src="https://github.com/user-attachments/assets/1e719aca-4535-44c4-9a5b-68411d72e8dd" />
<img width="1200" height="1600" alt="WhatsApp Image 2026-05-02 at 8 44 04 PM (1)" src="https://github.com/user-attachments/assets/4a20af36-72e9-4121-9549-a22ee33f8da7" />
<img width="1200" height="1600" alt="WhatsApp Image 2026-05-02 at 8 44 04 PM" src="https://github.com/user-attachments/assets/13fb5509-882f-48fa-9e8a-f9ce427d66b6" />
<img width="1200" height="1600" alt="WhatsApp Image 2026-05-02 at 8 44 05 PM (1)" src="https://github.com/user-attachments/assets/4cba5b28-6434-4c18-a6e4-c5a7a5453b83" />
<img width="1200" height="1600" alt="WhatsApp Image 2026-05-02 at 8 44 05 PM (2)" src="https://github.com/user-attachments/assets/08444543-4de9-4599-b30c-32733e7a230e" />

---

## What I Learned
- Basics of biped robot movement
- Servo control and timing
- Bluetooth communication
- Designing systems with limited hardware

---

## Conclusion
This project shows that even with minimal components (only 2 servos), it is possible to create a functional and interactive biped robot.  
It focuses on creativity, efficiency, and problem-solving under constraints.
