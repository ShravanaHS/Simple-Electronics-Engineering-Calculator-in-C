# ⚡ Simple Electronics Engineering Calculator in C

### 👉 **[TRY THE LIVE WEB VERSION HERE](https://shravanahs.github.io/Simple-Electronics-Engineering-Calculator-in-C/)**  
*(Converted from C to HTML Using Lord [GPT](https://chatgpt.com/)– not a web dev, so don’t expect animations, transitions, or dark mode. It just calculates 😁)*

---

## 📌 Project Overview  
This is a **fully modular Electronics Engineering Calculator** written in **pure C**, designed for students, hobbyists, and embedded engineers.

The entire project follows a clean & industrial structure using:
- **Modular Programming**
- Separate **header (.h)** and **source (.c)** files
- **Reusable functions**
- A **main menu system**
- Done entirely in **VS Code**

This calculator covers almost every basic electronics formulas.


You can run it in the terminal OR try the **web-based version** linked above.
>   
> C code is almost perfect there might be some issues in HTML Code.

---

## 🧱 Features & Modules

### 🧮 **1. Math Module**
- Addition, subtraction, multiplication, division  
- Safe division  
- Engineering prefix support (`k, M, m, u, n, p, f`)  
- Expression solver (supports nested parentheses)

---

### ⚡ **2. Ohm’s Law Module**
- Compute **Voltage, Current, Resistance, Power**
- Handles input with prefixes (e.g., `10mA`, `5kΩ`)

---

### 🔌 **3. Resistor Module**
- Series & parallel combinations  
- Resistivity (ρL/A)  
- **Color code decoding (4/5-band)**  
- **Resistance → Color code generator**  
- **SMD code decoder (EIA-96 + 3/4-digit)**  

---

### 🔋 **4. Capacitor Module**
- Series/parallel capacitance  
- Charge (Q = CV)  
- Energy (½CV²)  
- Time constant (τ = RC)  
- Reactance (Xc = 1/2πfC)  
- SMD capacitor codes (`104`, `472`, etc.)

---

### 🧲 **5. Inductor Module**
- Series/parallel inductance  
- Energy (½LI²)  
- Time constant (τ = L/R)  
- Reactance (Xl = 2πfL)  
- SMD inductor codes (`4R7`, `101`, etc.)

---

### 🧠 **6. Digital Logic Module**
- Number system conversions (BIN, DEC, HEX, OCT)  
- Bitwise AND, OR, XOR, NOT, SHIFT  
- Rotate left/right  
- Truth table generator (1–3 inputs)  
- Flip-flop simulator (SR, D, JK)

---

### 🧮 **7. Expression Solver Module**
Supports expressions like:
```math
((45k * 33) + (22 - 21) / ((45k - 44k) * (23m + 44k)))
```

## 📚  How to Use (Beginner-Friendly Guide)

Even someone new to C can use your program.  
Here’s the simplified guide:

---

### **Step 1 — Download the Project**

**Option A — Clone using Git**
```bash
git clone https://github.com/ShravanaHS/Simple-Electronics-Engineering-Calculator-in-C.git
```
**Option B — Download ZIP:**  
- Click **Code → Download ZIP**  
- Extract the ZIP file  
- Open the extracted folder in **VS Code**

---

### Step 2 — Open in VS Code

- Launch **VS Code** or simply **terminal**
- Go to **File → Open Folder**  
- Select the project folder  
- Open the terminal inside VS Code using the shortcut: **Ctrl + ~**
>
> or simply launch **terminal** from that folder.
---

### Step 3 — Build the Program

Run this compile command in the VS Code terminal:  
```
gcc main.c math_ops.c ohms_law.c resistor_calc.c capacitor_calc.c inductor_calc.c digital_logic.c expression_eval.c -o electronics_calc -lm
```
---

### Step 4 — Run the Program

Execute the output file:  
```
./electronics_calc
```
---

### Step 5 — Use the Menu

You will see a clean main menu like:
```
==== ELECTRONICS ENGINEERING CALCULATOR ====  
1. Math Operations  
2. Ohm’s Law  
3. Resistor Calculations  
4. Capacitor Calculations  
5. Inductor Calculations  
6. Digital Logic Module  
7. Expression Solver  
0. Exit  
```
Each module contains its own sub-menu and guides you step-by-step.

---

## Demo Video
[Demo Video](https://github.com/YourUser/ShravanaHS/releases/download/v1.0.0/demovid.mp4)

<video src="demovid.mp4" controls width="600">
  Your browser does not support the video tag.
</video>


---

## Example Calculations

### Ohm’s Law  
```
Voltage = ?  
I = 20mA  
R = 10kΩ  
Result → 200 V
```
---

### Resistor Color Code  
```
Bands: Red - Violet - Yellow - Gold  
Result → 27 × 10⁴ ± 5% = 270 kΩ
```
---

### Capacitor Reactance  
```
C = 100nF  
f = 1kHz  
Result → Xc = 1.59 kΩ
```
---

### Inductor Energy  
```
L = 10mH  
I = 2A  
Result → E = 0.02 J
```
---

### Binary → Hex 
```
Input: 0b10110101  
Output: HEX: 0xB5
```
---

### Expression Solver  
```
((45k * 45) / 34.966) + (9M / 3k)  
Result → 60.913 k
```
## Conclusion

The **Simple Electronics Engineering Calculator in C** started as a small idea but evolved into a complete modular engineering toolkit.  
It is simple, fast, expandable, and written fully in **pure C**, following clean coding practices and proper file structuring (`.h` and `.c` modules).
If you found this project helpful, feel free to:
- ⭐ Star the repository  
- Share it with friends  
- Suggest improvements  
- Fork and extend the project  

Thanks for checking out the project!  

## 🙏 Special Thanks

Special thanks to **[Balaji Sir](https://www.linkedin.com/in/balajeeseshadri/)** for his great tutorials on the [Etalvis Platform](https://learn.etalvis.com/) — his explanations and teaching style inspired this entire project idea. Also, a huge thanks to the **YouTube community** for their endless practical electronics content, and to **ChatGPT** for assisting in structuring, debugging, and converting the C program into a web-based version. This project exists because of all these amazing learning resources. ⚡


