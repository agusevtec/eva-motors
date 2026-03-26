# Custom Drivers

## Overview

EVA Motors provides a clean hardware abstraction layer that makes adding support for new motor drivers straightforward. The driver layer is designed to be minimal, focused, and easy to implement while maintaining consistency with the rest of the library.

## Driver Interface Requirements

To create a custom driver, your class must implement one or both of the following protected methods:

| Method | Purpose | Input Range | 
|--------|---------|-------------|
| `actBipolar(signed short)` | Bidirectional control | -1000..1000 |
| `actUnipolar(unsigned short)` | Unidirectional control | 0..1000 |

## Understanding Bipolar vs Unipolar

### Bipolar Interface (`actBipolar`)

Used for devices that support both forward and reverse directions. The input range -1000..1000 represents:
- Negative values: Reverse direction (0% to 100% power)
- Zero: Stop or neutral
- Positive values: Forward direction (0% to 100% power)

Typical applications: DC motors with H-bridges, bidirectional servos

### Unipolar Interface (`actUnipolar`)

Used for devices that operate in only one direction. The input range 0..1000 represents:
- 0: Minimum output (stop or idle)
- 1000: Maximum output (full power)

Typical applications: Aircraft ESCs, pumps, fans, LEDs, linear actuators

## Custom Driver Example

Here is how to create a driver for a hypothetical motor controller:

```cpp
#ifndef MY_DRIVER_H_
#define MY_DRIVER_H_

#include <Arduino.h>

namespace evam {

/**
 * @brief Driver for hypothetical specific motor controller
 * 
 * This driver demonstrates how to wrap any motor control hardware
 * into the EVA Motors driver interface.
 */
class MyDriver {
public:
    /**
     * @brief Constructor - initialize hardware
     */
    MyDriver() {
        // Initialize your hardware here
        SpecificController.begin();
        actBipolar(0);  // Start in safe state
    }

protected:
    /**
     * @brief Bipolar control implementation
     * @param aValue Range -1000..1000
     */
    void actBipolar(signed short aValue) {
        // Constrain input to valid range
        aValue = constrain(aValue, -1000, 1000);
        
        // Convert to your hardware-specific format
        // For example: -1000..1000 to -255..255
        int scaledValue = map(aValue, -1000, 1000, -255, 255);
        
        // Send to your hardware
        SpecificController.writeSignal(scaledValue);
    }

private:
    // Your hardware-specific members
};

} // namespace evam

#endif // MY_DRIVER_H_
```

## Using Your Custom Driver

Once implemented, your driver can be used with any compatible motor wrapper:

```cpp
#include <evamDirectionalMotor.h>
#include "MyDriver.h"

// Combine your driver with EVA Motors wrappers
using MyMotor = evam::DirectionalMotor<MyDriver>;

MyMotor motor;

void setup() {
    motor.SetupRange(-1000, -200, 200, 1000);
}

void loop() {
    motor.Go(750);  // 75 percent forward
    delay(2000);
    motor.Go(-500); // 50 percent reverse
    delay(2000);
}
```

## Key Points

1. Implement only what you need – Your driver can implement one or both interfaces
2. Initialize to safe state – Always call `actBipolar(0)` or `actUnipolar(0)` in constructor
3. Constrain inputs – Use `constrain()` before mapping to hardware values
4. Keep it minimal – The driver should only translate between EVA Motors ranges and your hardware

## Contributing

If you have created a driver for a common motor controller, contributions are welcome and appreciated.

Please submit a pull request with:
- Complete driver implementation
- Clear documentation including pin connections
- Basic usage example

Your driver will help the entire community and make EVA Motors more versatile.

## Summary

Creating custom drivers in EVA Motors is straightforward:

1. Choose the appropriate interface (`actBipolar` or `actUnipolar`)
2. Implement the method with your hardware-specific logic
3. Initialize pins and set safe state in constructor
4. Use with any compatible motor wrapper

The driver layer is designed to be minimal yet flexible, making it easy to support virtually any motor controller hardware.