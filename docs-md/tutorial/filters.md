# Filters

## Overview

Filters in EVA Motors are decorators that clean and smooth control signals before they reach the motor. They remove noise, suppress spikes, and provide predictable signal conditioning. All filters share the same `Go(value)` interface and can be stacked with behavioral decorators.

| Filter | Type | Best For |
|--------|------|----------|
| SlidingWindowDecor | Moving average | General noise reduction |
| MinmaxDecor | Morphological | Impulse noise removal |
| AdaptiveSmoothDecor | Adaptive exponential | Mixed noise with varying dynamics |

## SlidingWindowDecor – Moving Average

Simple moving average filter that computes the arithmetic mean of the last N values.

```cpp
template <class Motor, unsigned short N>
class SlidingWindowDecor : public Motor
```

**Parameters:**

- `N`: Window size (number of values to average)

**Behavior:**

- Maintains running sum of last N values
- Output = sum / N (arithmetic mean)
- Pass-through until buffer fills
- Constant delay of N/2 samples

**Methods:**

- `Go(value)` – Apply moving average

**Example:**
```cpp
// Smooth throttle with 5-sample window
using SmoothESC = evam::SlidingWindowDecor<evam::ForwardMotor<evam::PwmDriver<9>>, 5>;
SmoothESC motor;
motor.Go(500);  // Output = average of last 5 inputs
```

**Use cases:**

- General purpose noise reduction
- Pre-filtering for PID control
- Data acquisition smoothing
- Removing quantization noise

## MinmaxDecor – Morphological Filter

Advanced filter that removes both positive and negative impulse noise while preserving edges.

```cpp
template <class Motor, unsigned char N>
class MinmaxDecor : public Motor
```

**Parameters:**

- `N`: Chunk size (total buffer = N × N elements)

**Behavior:**

- Divides buffer into N chunks of N elements each
- Finds maximum and minimum in each chunk
- Computes minimax = min of chunk maximums (removes negative spikes)
- Computes maximin = max of chunk minimums (removes positive spikes)
- Output = (minimax + maximin) / 2

**Methods:**

- `Go(value)` – Apply filter (pass-through until buffer full)
- `getMinimax()` – Get current minimax value
- `getMaximin()` – Get current maximin value

**Example:**
```cpp
// Clean noisy potentiometer signal
using CleanMotor = evam::MinmaxDecor<evam::DirectionalMotor<evam::TA6586Driver<9, 10>>, 3>;
CleanMotor motor;
motor.Go(500);  // Filtered after 9 samples
```

**Use cases:**

- Removing impulse noise from potentiometers
- Cleaning encoder signals with glitches
- Radar/lidar signal conditioning
- Audio pop removal

## AdaptiveSmoothDecor – Adaptive Exponential

Exponential filter that automatically adjusts its time constant based on input rate of change.

```cpp
template <class Motor, unsigned short kMinTimeConstantMs = 10, unsigned short kMaxTimeConstantMs = 150>
class AdaptiveSmoothDecor : public Heartbeat, public Motor
```

**Requirements:**

Must call `eva::tac()` in `loop()` to drive the filter updates (inherits from `Heartbeat` with 10ms period).

**Parameters:**

- `kMinTimeConstantMs`: Fast response (5..200ms). Default: 10ms
- `kMaxTimeConstantMs`: Heavy smoothing (≥ kMinTimeConstantMs, ≤500ms). Default: 150ms

**Behavior:**

- Large input change (≥200) → fast response (min time constant)
- Small input change (≤5) → heavy smoothing (max time constant)
- Intermediate changes → linear interpolation between min and max
- Deadzone (±3) forces zero output near origin

**Methods:**

- `Go(value)` – Set target value (range -1000..1000)
- `GetCurrentTimeConstant()` – Get current smoothing amount

**Example:**
```cpp
using AdaptiveMotor = evam::AdaptiveSmoothDecor<evam::DirectionalMotor<evam::TA6586Driver<9, 10>>>;
AdaptiveMotor motor;
motor.Go(800);  // Fast response to large change
motor.Go(810);  // Heavy smoothing for small change
```

**Use cases:**

- Joystick-controlled vehicles (fast response + smooth idle)
- Camera gimbals (smooth tracking + quick moves)
- Robotic arms (precision positioning + rapid moves)
- Any system requiring both responsiveness and noise rejection

## Combining Filters

Filters can be stacked for enhanced noise rejection:

```cpp
#include <evaTac.h>
#include <evamTA6586Driver.h>
#include <evamDirectionalMotor.h>
#include <evamSlidingWindowDecor.h>
#include <evamMinmaxDecor.h>
#include <evamAdaptiveSmoothDecor.h>

using namespace eva;
using namespace evam;

// Remove impulse noise, then smooth, then adapt to dynamics
using BaseMotor = DirectionalMotor<TA6586Driver<9, 10>>;
using SpikeFilter = MinmaxDecor<BaseMotor, 3>;        // Remove spikes
using SmoothFilter = SlidingWindowDecor<SpikeFilter, 5>; // General smoothing
using SmartMotor = AdaptiveSmoothDecor<SmoothFilter>;    // Adaptive response

SmartMotor motor;

void loop() {
    eva::tac();  // Drives AdaptiveSmoothDecor
    int raw = analogRead(A0);
    int mapped = map(raw, 0, 1023, -1000, 1000);
    motor.Go(mapped);  // Triple-filtered signal
}
```

## Performance Considerations

| Filter | Memory (bytes per N) | Computation | Requires tac() |
|--------|---------------------|-------------|----------------|
| SlidingWindowDecor | 2 × N + 4 | O(1) | ❌ |
| MinmaxDecor | 2 × N + 2 × N × N | O(N²) | ❌ |
| AdaptiveSmoothDecor | 6 + 4 | O(1) | ✅ |

**Recommendations:**

- Use `SlidingWindowDecor` for general noise (lowest overhead)
- Use `MinmaxDecor` when spikes are present (N=2 or 3 usually sufficient)
- Use `AdaptiveSmoothDecor` when both fast response and smooth idle are critical
- Stack filters in order: spike removal → smoothing → adaptive behavior