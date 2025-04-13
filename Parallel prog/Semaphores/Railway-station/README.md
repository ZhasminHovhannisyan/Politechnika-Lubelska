# Train Station Simulation – Multithreading with Semaphores

## Overview

This project simulates a train station with multiple platforms using C++ multithreading. Each train tries to access a preferred platform, and if it's busy, it switches to a spare platform. The simulation demonstrates basic concepts of concurrency, synchronization, and potential race conditions when multiple threads operate on shared resources.

---

##  How It Works

- **Classes:**
  - `Train`: Represents a train that runs in a separate thread. It attempts to arrive at a platform, simulates boarding/disembarking, and then departs.
  - `Platform`: Represents a train platform with an occupancy status. Each platform keeps track of whether it's empty and handles train arrivals and departures.

- **Synchronization:**
  - Each `Platform` object uses a **mutex** to protect the `empty` status from race conditions.
  - Trains perform 3 simulated trips each with randomized delays using `std::chrono` and `std::minstd_rand`.

---

##  Example Behavior

- If a platform is **available**, the train enters and departs normally.
- If a platform is **occupied**, and another train attempts to enter it without checking (i.e., missing synchronization), a "disaster" message is printed.
- After fixing the concurrency issue using `std::mutex`, trains no longer cause disasters.

---

##  Compilation

Ensure `semaphore.h` is present in the same directory.

```bash
g++ railway_station.cc semaphore.h -o train_simulation
./train_simulation
