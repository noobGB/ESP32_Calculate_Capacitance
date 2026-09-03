# ESP32 Capacitance Meter

A minimal ESP32/PlatformIO sketch that estimates the capacitance of a capacitor by timing an
RC charge cycle, based on the method described in
[Norwegian Creations' Arduino capacitance meter](https://www.norwegiancreations.com/2019/08/using-a-simple-arduino-to-measure-capacitor-value/).

## How it works

Charging a capacitor `C` through a resistor `R` follows `V(t) = V_max * (1 - e^(-t/RC))`. The time
constant `T = RC` is defined as the time it takes the capacitor to reach 63.2% of the supply
voltage. The sketch:

1. Drains the capacitor by pulling the charge pin low until the ADC reads ~0.
2. Sets the charge pin high and starts a timer.
3. Polls the ADC until the reading crosses 63.2% of full scale (`647` out of `1023`, using an
   8x-downscaled ADC reading).
4. Repeats this 3 times and averages the elapsed time to get `T`.
5. Computes `C = T / R` and prints the result in µF or nF over serial.

## Hardware

| Signal | ESP32 GPIO |
|---|---|
| Capacitor voltage (analog in) | GPIO34 |
| Capacitor charge/discharge control (digital out) | GPIO32 |

Wire the capacitor under test in series with a known resistor between the charge pin and the
analog pin, with the capacitor's other leg to ground. The default resistor value in
[src/main.cpp](src/main.cpp) is set for a ~1kΩ resistor; swap `resistor_value` to match your
actual resistor for accurate readings. A larger resistor slows the charge/discharge cycle
(useful for very small capacitances) at the cost of longer measurement time.

## Build and flash

This is a [PlatformIO](https://platformio.org/) project targeting a generic `esp32dev` board.

```
pio run                # build
pio run -t upload      # flash
pio device monitor -b 115200   # view serial output
```

Serial output prints the measured charge time and the resulting capacitance every ~5 seconds.
