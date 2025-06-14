# EasyInterval

A fully Metro-compatible Arduino library for non-blocking timing – with added features!

🟢 **Drop-in replacement for [Metro library](https://github.com/thomasfredericks/Metro)**
🟢 **Adds support for delta time measurements and dual-phase intervals**

---

## ✅ Why use EasyInterval?

* Fully compatible with Metro: `check()`, `expired()`, `reset()`, `interval()`, `checkCatchUp()`, `running()`
* Adds `get()` to measure time since last call
* Adds `setPhases(onTime, offTime)` for alternating blink/idle periods
* Adds `.enable()`, `.disable()` and `.isEnabled()` to control timers dynamically
* Safe for `millis()` overflow (\~49.7 days)
* Makes writing non-blocking code easy: blink LEDs, debounce buttons, periodic actions

---

## 🔄 Metro vs EasyInterval

| Feature          | Metro | EasyInterval |
| ---------------- | ----- | ------------ |
| `check()`        | ✅     | ✅            |
| `expired()`      | ✅     | ✅            |
| `interval(ms)`   | ✅     | ✅            |
| `reset()`        | ✅     | ✅            |
| `checkCatchUp()` | ✅     | ✅            |
| `running()`      | ✅     | ✅            |
| `get()`          | ❌     | ✅            |
| `setPhases()`    | ❌     | ✅            |
| `phase()`        | ❌     | ✅            |
| `enable()`       | ❌     | ✅            |
| `disable()`      | ❌     | ✅            |
| `isEnabled()`    | ❌     | ✅            |

---

## 🚀 Quick Start Example: Blink LED every 1 second

```cpp
#include <EasyInterval.h>

const int ledPin = 13;
EasyInterval blink(1000); // 1 second

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (blink.check()) {
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
}
```

---

## 🔹 Example: Dual-phase LED blinking (1s ON, 3s OFF)

```cpp
#include <EasyInterval.h>

const int ledPin = 13;
EasyInterval timer;

void setup() {
  pinMode(ledPin, OUTPUT);
  timer.setPhases(1000, 3000); // ON 1s, OFF 3s
}

void loop() {
  if (timer.check()) {
    digitalWrite(ledPin, timer.phase() == 0 ? HIGH : LOW);
  }
}
```

---

## 🔹 Example: Debounce a button

```cpp
#include <EasyInterval.h>

const int buttonPin = 2;
const int ledPin = 13;
EasyInterval debounce;
int lastState = HIGH;
bool ledState = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int state = digitalRead(buttonPin);
  if (state != lastState && debounce.get() > 50) {
    lastState = state;
    if (state == LOW) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
  }
}
```

---

## 🔹 Example: Use get() as a delta timer

```cpp
#include <EasyInterval.h>

EasyInterval deltaTimer;

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long dt = deltaTimer.get();
  Serial.print("Delta time: ");
  Serial.println(dt);
  delay(200); // simulate processing
}
```

---

## 🔹 Example: Dynamically disable and enable a timer

```cpp
#include <EasyInterval.h>

EasyInterval heartbeat(500);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (heartbeat.check()) {
    Serial.println("Heartbeat...");
  }

  // Example: stop timer after 5 seconds
  static EasyInterval timeout(5000);
  if (timeout.check()) {
    heartbeat.disable();
    Serial.println("Timer disabled");
  }

  // Later you can call:
  // heartbeat.enable();
}
```

---

## 📃 API Summary

| Method            | Description                                      |
| ----------------- | ------------------------------------------------ |
| `check()`         | Returns true if interval passed and resets timer |
| `expired()`       | Returns true if interval passed (no reset)       |
| `reset()`         | Manually reset the timer                         |
| `interval(ms)`    | Set or change the interval time                  |
| `get()`           | Returns time passed since last get/reset         |
| `checkCatchUp()`  | Keeps time aligned even if delayed               |
| `running()`       | Returns true if within current interval          |
| `setPhases(a, b)` | Enables dual-phase toggle timer                  |
| `phase()`         | Returns current phase (0 or 1)                   |
| `enable()`        | Re-enables the timer after disabling             |
| `disable()`       | Disables the timer (check/get return false/0)    |
| `isEnabled()`     | Returns whether the timer is currently enabled   |

---

## 🚫 Disabling a timer

To disable execution:

```cpp
timer.disable(); // prevents check/get from doing anything
```

To re-enable:

```cpp
timer.enable();
```

Or use a flag:

```cpp
if (timer.isEnabled() && timer.check()) {
  // only runs if enabled and interval passed
}
```

---

## 📚 License

MIT License
Copyright (c) 2025
Author: Regimantas Baublys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction...

Full license in `LICENSE` file.
