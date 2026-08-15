# WellSentry

### Low-Cost Smart Safety System for Borewells

WellSentry is a low-cost safety system designed to monitor unattended or improperly secured borewells and provide an early warning when the borewell becomes unsafe.

## How It Works

WellSentry uses multiple layers of protection:

**1. Cap Tamper Detection**
A vibration sensor detects movement or disturbance of the borewell cap.

**2. Fall Detection**
An ultrasonic sensor monitors the shaft and detects an object entering the monitored area.

**3. Local Alert**
The ESP32 activates a buzzer and visual indicators when an abnormal event is detected.

**4. Remote Alert**
The system can send notifications through Wi-Fi to a phone or monitoring system.

**5. Physical Protection**
A safety mesh below the opening provides a passive fall-arrest layer that does not depend on electricity, internet, or human response.

## System Flow
Cap / Shaft
↓
Sensors
↓
ESP32
↓
Detection
↓
Local + Remote Alert
↓
Physical Safety Mesh

## Prototype Components

- ESP32
- SW-420 vibration sensor
- HC-SR04 ultrasonic sensor
- Buzzer
- LEDs
- Resistors
- Safety mesh
- Breadboard and jumper wires

## What Makes WellSentry Different

Instead of depending on a single sensor or notification, WellSentry combines detection, alerting, and physical protection.

**Detect → Alert → Protect**

The physical safety layer remains useful even if an electronic alert is missed or connectivity is unavailable.

## Scalability

The current prototype is built for borewell safety, but the same basic technology can be adapted to other situations by changing the sensors, their placement, and the detection logic in the firmware.

Possible future applications include:

- Manholes
- Water tanks
- Construction openings
- Industrial pits
- Other restricted or hazardous openings

The core idea remains the same:

**Sense → Decide → Alert → Protect**

## Prototype Status

This project is currently a working prototype developed to demonstrate the concept.

Before real-world deployment, the system would require further mechanical, environmental, sensor reliability, and safety testing.

## Vision

To make unattended borewells safer through a simple, affordable, and layered safety system.

> Detect early. Alert immediately. Protect when it matters.
## Hardware Connection

![WellSentry Hardware Connection](assets/wiring_diagram.png)
