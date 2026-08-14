# WellSentry 

### Low-Cost Layered Safety System for Borewells and Hazardous Openings

WellSentry is a low-cost safety system designed to detect dangerous access or falls around unattended borewells.

Instead of relying on a single warning mechanism, WellSentry uses multiple safety layers:

**Detect → Alert → Detect Again → Physically Protect**

---

## Problem

Open, abandoned, damaged, or poorly capped borewells can become dangerous fall hazards, especially for children and animals.

A normal physical cap can fail or be displaced without anyone knowing.

WellSentry aims to provide active monitoring and a physical fallback safety layer.

---

## Our Solution

WellSentry combines:

- Cap tamper detection
- In-shaft fall detection
- Local audible alarms
- Phone notifications
- Passive physical safety mesh
- Low-cost off-the-shelf electronics

The system is designed so that safety does not depend entirely on someone noticing an alert immediately.

---

## ⚙️ How It Works

### Layer 1 — Cap Tamper Detection

A sensor mounted on the borewell cap detects shaking, displacement, or disturbance.

If the cap is disturbed:

```text
Cap disturbance
       ↓
Sensor detects movement
       ↓
ESP32
       ↓
Local alarm + phone notification

## if object enters 

Object enters shaft
       ↓
Shaft sensor detects change
       ↓
ESP32
       ↓
FALL DETECTED
       ↓
Louder alarm + phone notification

Object enters shaft
       ↓
Shaft sensor detects change
       ↓
ESP32
       ↓
FALL DETECTED
       ↓
Louder alarm + phone notification

the safety net in it catches the object 
hence evn after the network , response fails the 
physically protection is provided 

