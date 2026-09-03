# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A single-sketch PlatformIO/Arduino project for ESP32 that measures capacitance by timing an
RC charge cycle. See [README.md](README.md) for the measurement method and wiring. All logic
lives in [src/main.cpp](src/main.cpp) — there is no other code to navigate.

## Commands

```
pio run                        # build
pio run -t upload              # flash to a connected ESP32
pio device monitor -b 115200   # view serial output (115200 baud, matches Serial.begin in main.cpp)
```

No test suite or linter is configured (`test/` is the empty PlatformIO scaffold directory).

## Notes for changes

- `resistor_value` in `main.cpp` must match the actual resistor wired in the circuit — it's not
  auto-detected. If changing the reference hardware setup, update both the code and the README's
  wiring table together.
- The 63.2% RC threshold (`647` against a downscaled 0–1023 range) is the standard time-constant
  definition, not an arbitrary tuning value — don't change it without changing the underlying math
  in the README.
