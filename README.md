# **MIDI Controller Project** 🎵🎛️  

## **Overview**  
This project is a **custom MIDI controller** using **Arduino** and **MIDI over USB**. It features:  
✅ **Rotary encoders** for **menu navigation**  
✅ **Push buttons** for **MIDI note triggering**  
✅ **Potentiometers** for **MIDI CC control**  
✅ **Shift registers** for **button inputs and LED outputs**  
✅ **LCD display** for **user feedback**  
✅ **Multiple LED effects** (VU meter, Knight Rider, Random Sparkles, etc.)  
✅ **Custom library system** for modularity and reusability  

🔗 **Live Simulation**: [View on Wokwi](https://wokwi.com/projects/393050034647400449)  

---

## **Hardware Requirements**  
- **Arduino Board** (ATmega32U4-based, e.g., Arduino Leonardo/Micro)  
- **74HC165 Shift Register** (for button inputs)  
- **74HC595 Shift Register** (for LED outputs)  
- **Rotary Encoder** (for menu navigation)  
- **Push Buttons** (for MIDI notes and menu selection)  
- **Potentiometers** (for MIDI CC control)  
- **LCD Display** (16x2 for UI feedback)  
- **LEDs** (for VU meter & effects)  

---

## **Pin Configuration**  
### **Shift Register - Button Inputs (74HC165)**  
| Function | Pin |  
|----------|----|  
| Latch    | 10 |  
| Clock    | 9  |  
| Data     | 8  |  

### **Shift Register - LED Outputs (74HC595)**  
| Function | Pin |  
|----------|----|  
| Latch    | 3  |  
| Clock    | 9  |  
| Data     | 2  |  

### **MIDI & User Interface**  
| Component     | Pin |  
|--------------|----|  
| Encoder DT   | 20 |  
| Encoder CLK  | 21 |  
| Encoder SW   | 22 |  
| LCD Backlight| 23 |  
| Microphone   | A3 |  

---

## **Custom Library System**
This project uses **custom-built libraries** to keep the code modular and organized.

### **Library Files and Their Purpose**
| Library File | Description |
|-------------|------------|
| `MiDiLib.h` | Handles **MIDI communication** (Note ON/OFF, CC messages) |
| `MENU_.h` | **Menu system** with LCD navigation, button handling, and rotary encoder support |
| `Pot.h` | Reads **potentiometer inputs**, maps them to **MIDI CC** values |
| `Button.h` | Manages **button presses**, handles shift register inputs |
| `ShiftRegister.h` | Handles **74HC165 and 74HC595 shift registers** for input/output |
| `LED_lights.h` | Controls **LED effects** like Knight Rider, VU meter, breathing effect |
| `LCD.h` | Manages **LCD display** for showing menu, messages, and animations |
| `config.h` | Defines **configuration settings**, including **ATmega32U4 compatibility** |

---

## **Software Implementation**  
### **1️⃣ MIDI Functions (MiDiLib.cpp)**
- `noteOn(byte channel, byte pitch, byte velocity)`: Sends a **MIDI Note ON**  
- `noteOff(byte channel, byte pitch, byte velocity)`: Sends a **MIDI Note OFF**  
- `controlChange(byte channel, byte control, byte value)`: Sends a **MIDI CC message**  

### **2️⃣ Menu System (MENU_.cpp)**
- **Rotary encoder-based navigation**  
- **Sub-menus for LED, button, and potentiometer settings**  
- **"About" section with author details**  

### **3️⃣ Potentiometers (Pot.cpp)**
- Reads **16 potentiometers** via **74HC4051 multiplexers**  
- Maps values to MIDI CC (0-127)  
- Sends MIDI CC messages when values change  

### **4️⃣ Button Handling (Button.cpp)**
- Uses **shift registers (74HC165)** for input  
- Debounces button presses  
- Sends **MIDI Note ON/OFF messages**  

### **5️⃣ LED Effects (LED_lights.cpp)**
- **Persistence Pattern**  
- **Breathing Effect**  
- **VU Meter**  
- **Knight Rider Effect**  
- **Random Sparkles**  
- **Wave Effect**  

### **6️⃣ LCD Display (LCD.cpp)**
- **Shows menu items**  
- **Displays MIDI actions**  
- **Provides user feedback**  

---

## **Installation & Usage**
### **1️⃣ Upload the Code**
- Open the project in **Arduino IDE**  
- Ensure **ATmega32U4-based board** is selected  
- Install the **MIDIUSB** library (if not included)  
- Upload the sketch  

### **2️⃣ Connect the Circuit**
- Wire up **buttons, encoders, LCD, LEDs, and shift registers** as per the schematic  

### **3️⃣ Use the Controller**
- **Navigate the menu** using the rotary encoder  
- **Trigger MIDI notes** using buttons  
- **Adjust MIDI CC values** using potentiometers  
- **Customize LED effects** via menu settings  

---

## **Future Enhancements**
🔹 **Add Bluetooth MIDI** for wireless control  
🔹 **Implement an OLED Display** for a better UI  
🔹 **Integrate a Web UI** for remote configuration  
🔹 **Create a custom MIDI mapping software**  

---

## **License & Usage Restrictions**  
📌 **This project is NOT open-source.**  
📌 Unauthorized distribution, reproduction, or modification is **strictly prohibited**.  
📌 **For personal/internal use only.** Commercial use requires **explicit permission**.  

📧 **For inquiries, contact: gaurav18v.com@gmail.com**  

---

## **Author**  
👤 **Gaurav Sharma** 
