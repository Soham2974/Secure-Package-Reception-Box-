# 📦 Secure Package Reception Box

## 📌 Overview
The **Secure Package Reception Box** is an **IoT-based system** designed to securely receive parcels in the absence of the recipient. It uses **STM32 microcontroller, IR Sensor, GSM module (SIM800L), and Servo Motor** for OTP-based authentication and delivery confirmation.

This project was developed as part of **Semester V Mini Project (AY 2024-25)** at **Don Bosco Institute of Technology, Mumbai**.

---

## 👨‍💻 Team Members
- Jaden Fernandes (Roll No. 19)  
- Ayush Gajbhiye (Roll No. 23)  
- **Soham Ghadigaonkar (Roll No. 27)**  
- Priyanshu Sakharkar (Roll No. 46)

---

## 🎯 Objectives
- Prevent unauthorized access to packages.  
- Send **OTP-based authentication** to recipients.  
- Notify the recipient after delivery.  
- Provide a **secure, affordable, and reliable solution** to tackle package theft.  

---

## 🛠️ Components Used
| Component          | Specification     | Qty |
|-------------------|-------------------|-----|
| IR Sensor         | Infrared Sensor   | 1   |
| GSM Module        | SIM800L           | 1   |
| Servo Motor       | MG90S             | 1   |
| STM32 MCU         | ARM Cortex-M      | 1   |

---

## ⚡ Working
1. IR sensor detects delivery personnel.  
2. GSM module sends an **OTP** to the recipient.  
3. Recipient enters OTP → Servo motor unlocks the box.  
4. Package is placed → Box locks automatically.  
5. Recipient gets **confirmation SMS**.  

---

## 📐 Circuit & Block Diagram
 `block_diagram.png/` `circuit_diagram.png/`

---

## 💻 Source Code
Source code is available in the `SEM_5.pdf/` directory.  

---



## 📚 Report
For detailed explanation, refer to the full project report:  
👉 [Secure Package Reception Box Report (PDF)](./SEM_5_.pdf)

---

## ✅ Conclusion
The project addresses the issue of **package theft (porch piracy)** with a **secure, automated, and IoT-enabled solution**.

---
## Support
For more details, connect with me on [![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/soham-ghadigaonkar-2b8827239/)
[![Discord](https://img.shields.io/badge/discord-join%20chat-7289da?logo=discord&style=for-the-badge)](https://discord.gg/soham.2974)
