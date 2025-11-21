# 🔒 Arduino RFID & Keypad Data Entry System (MFRC522 + I2C LCD)

This project implements a secure and interactive data entry terminal using an Arduino microcontroller. It combines an **RFID reader (MFRC522)** for identification and a **4x4 Keypad** for supplementary, manual data input. All interactions and data are displayed on a **16x2 I2C LCD**.

## 🚀 Features

* **RFID Tag Reading:** Instantly reads the Unique Identifier (UID) of an MFRC522 compatible tag or card.
* **Keypad Input:** Allows users to manually enter details (e.g., a PIN, quantity, or additional ID) after a successful RFID scan.
* **LCD Feedback:** Provides real-time guidance and displays the final collected data (RFID ID + Keypad Data).
* **Modular Design:** Easy to adapt for various applications like simple access control logging, inventory management, or time tracking.

## 🛠️ Components Required

| Component | Quantity | Description |
| :--- | :--- | :--- |
| **Arduino Uno** (or compatible) | 1 | The main microcontroller. |
| **MFRC522 RFID Reader** | 1 | Used for reading the RFID tags. |
| **16x2 I2C LCD Display** | 1 | For displaying prompts and data. (Commonly uses address `0x27` or `0x3F`) |
| **4x4 Keypad** | 1 | For manual data entry. |
| **Jumper Wires** | Varies | For connections. |
| **Breadboard** | 1 (Optional) | For organizing connections. |

## 🔌 Wiring Diagram

This section outlines the primary connections for the major modules.

### MFRC522 Connections (SPI)

| MFRC522 Pin | Arduino Pin | Note |
| :--- | :--- | :--- |
| **SDA (SS)** | **D10** | Chip Select (Defined as `SS_PIN`) |
| **SCK** | **D13** | SPI Clock |
| **MOSI** | **D11** | SPI Master Out Slave In |
| **MISO** | **D12** | SPI Master In Slave Out |
| **RST** | **D9** | Reset Pin (Defined as `RST_PIN`) |
| **VCC** | **3.3V** | Power |
| **GND** | **GND** | Ground |

### 16x2 I2C LCD Connections

| I2C LCD Pin | Arduino Pin |
| :--- | :--- |
| **SDA** | **A4** (or SDA pin on newer boards) |
| **SCL** | **A5** (or SCL pin on newer boards) |
| **VCC** | **5V** |
| **GND** | **GND** |

### 4x4 Keypad Connections

The Keypad uses **Digital Pins 2-8** for rows and columns.

| Keypad Pin (Rows) | Arduino Pin | Note |
| :--- | :--- | :--- |
| **R1** | **D9** | **NOTE: The original code has a conflict with MFRC522 RST pin (D9).** Please verify your component usage or change this pin. The provided code has: `{9, 8, 7, 6}` (Rows) |
| **R2** | **D8** | |
| **R3** | **D7** | |
| **R4** | **D6** | |
| **C1** | **D5** | The provided code has: `{5, 4, 3, 2}` (Columns) |
| **C2** | **D4** | |
| **C3** | **D3** | |
| **C4** | **D2** | |

## ⚙️ Library Dependencies

This project requires the following libraries to be installed in your Arduino IDE:

1.  **MFRC522:** For RFID communication.
    * *Installation:* Search for `MFRC522` by **Miguel Balboa** in the Library Manager.
2.  **LiquidCrystal I2C:** For controlling the I2C LCD.
    * *Installation:* Search for `LiquidCrystal I2C` by **Frank de Brabander** in the Library Manager.
3.  **Keypad:** For interfacing with the 4x4 keypad.
    * *Installation:* Search for `Keypad` by **Mark Stanley** and **Alexander Brevig** in the Library Manager.
4.  **SPI** and **Wire** are standard libraries and should be included by default.

## 📝 Code Overview

The code flow is as follows:

1.  **Setup:** Initializes Serial, LCD (`Scan RFID`, `Enter Details`), SPI, and the MFRC522 reader.
2.  **Loop:** Continuously checks for a new RFID card.
3.  **RFID Detected:** If a card is present, it reads the UID, displays it, and transitions to keypad mode.
4.  **Keypad Input:** Enters a `while(true)` loop, waiting for keypad presses. Input is appended to the `details` string until the **`#`** key is pressed (which acts as the ENTER/FINISH key).
5.  **Display Result:** Clears the screen and displays both the captured **RFID ID** and the **Keypad Data**.
6.  **Reset:** After a 5-second display delay, the system resets to the initial "Scan RFID" state.
