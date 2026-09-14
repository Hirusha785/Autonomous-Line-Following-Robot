# 🤖 EC6090 Autonomous Line Following Robot

## 🚀 Project Overview

This project focuses on the design and development of an **autonomous mobile robot** capable of intelligent navigation and object handling.

The robot integrates multiple robotic subsystems including **line following, obstacle avoidance, color-based object detection, and servo-controlled pick-and-place operations** using an ESP32-based embedded control system.

The system is designed to complete an autonomous navigation sequence in a controlled arena without any wireless control.

---

# ✨ Key Features

## 🛣️ Intelligent Line Following
- PID-based line tracking algorithm
- Multi-sensor IR array for accurate path detection
- Dynamic motor speed adjustment for improved stability

## 🚧 Obstacle Avoidance
- Ultrasonic distance measurement system
- Automatic obstacle detection and avoidance
- Path recovery and line re-acquisition after avoiding obstacles

## 🎨 Color-Based Object Detection
- RGB color sensing module integration
- Identification of target objects based on color information
- Decision-making based on detected object type

## 🦾 Automated Pick and Place
- Servo-controlled robotic arm mechanism
- Automatic object gripping and releasing
- Integrated object handling workflow

## ⚡ Fully Autonomous Operation
- No wireless/manual control during operation
- Real-time sensor-based decision making
- Embedded control using ESP32 microcontroller

---

# 🏗️ System Architecture

<img width="784" height="561" alt="image" src="https://github.com/user-attachments/assets/3dba1e4d-d943-4d16-b6bd-9aa72e731110" />

---

# 🔧 Hardware Components

| Component | Function |
|-----------|----------|
| ESP32 Development Board | Main microcontroller |
| Smart Car Chassis | Robot platform |
| DC Gear Motors | Robot movement |
| Motor Driver Module | Motor control |
| IR Sensor Array | Line detection |
| Ultrasonic Sensor | Distance measurement |
| RGB Color Sensor | Object color identification |
| Servo Motors | Arm and gripper control |
| Battery Pack | Power supply |

---

# 💻 Software Stack

| Category | Technology |
|----------|------------|
| Programming Language | C/C++ |
| Microcontroller Framework | ESP32 Arduino Framework |
| Development Environment | Arduino IDE / PlatformIO |
| Version Control | Git & GitHub |
| Control Algorithm | PID Controller |

---

# 🔄 System Workflow

<img width="1360" height="1872" alt="image" src="https://github.com/user-attachments/assets/660b93b7-ab08-4c2e-9565-515a6a10c06e" />

---

# 🧠 Control Implementation

## PID Line Following

The robot uses PID control to maintain accurate movement along the predefined path.

Control process:


Sensor Reading
↓
Calculate Error
↓
PID Calculation
↓
Motor Speed Correction
↓
Robot Direction Adjustment


---

## Obstacle Avoidance

The robot continuously measures distance using an ultrasonic sensor.

Process:


Measure Distance
↓
Obstacle Detected
↓
Stop Robot
↓
Execute Avoidance Path
↓
Rejoin Line


---

## Object Handling

The robot performs automated object handling:


Detect Object Color
↓
Identify Target Object
↓
Move Servo Arm
↓
Grip Object
↓
Transport Object
↓
Release Object


---

# 📊 Development Status

| Module | Status |
|--------|--------|
| Robot Mechanical Assembly | ✅ Completed |
| ESP32 Integration | ✅ Completed |
| Motor Control | ✅ Completed |
| PID Line Following | ✅ Completed |
| Obstacle Avoidance | ✅ Completed |
| Color Detection | ✅ Completed |
| Pick and Place Mechanism | ✅ Completed |
| Final Testing | 🚧 In Progress |

---

# 📸 Prototype

<img width="960" height="1280" alt="image" src="https://github.com/user-attachments/assets/baf3fda0-29bf-4b85-acfa-3b58fef69851" />
<img width="960" height="1280" alt="image" src="https://github.com/user-attachments/assets/d0da081b-bb01-4a23-9b6c-260f0b088554" />
<img width="1280" height="960" alt="image" src="https://github.com/user-attachments/assets/68fb88f2-069e-4e9a-8973-ce386d68ae59" />



---

# 👥 Team Contributions

| Member | Responsibility |
|--------|---------------|
| T.M.M. MALIK  | Hardware Design & Assembly |
| SANAS M.M. | Embedded Firmware Development & Testing |
| FERNANDO S.M.H.G. | Sensor Integration& Assembly |
| SHAPTHANA J. | Documentation & System Validation |

---

# 🔮 Future Improvements

- Advanced PID parameter tuning
- Improved mechanical stability
- Better sensor calibration
- Optimized navigation algorithm
- Wireless monitoring dashboard

---

# 📚 Academic Information

**Module:** EC6090 - Robotics and Automation  
**Project Type:** Mini Project  
**Platform:** ESP32 Autonomous Mobile Robot  

---

## ⭐ Project Highlights

✅ Autonomous navigation  
✅ Real-time sensor processing  
✅ Embedded control system  
✅ Multi-module robotics integration  
✅ Intelligent object handling  

---

<p align="center">

Developed with 🤖⚡ by the EC6090 Robotics Team

</p>
