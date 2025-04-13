# Airport Simulation – Multithreading with Semaphores

This program simulates an **airport scenario** involving multiple airplanes landing, parking in a hangar, and taking off using multithreading. It models shared resource access (runway and hangar) and uses thread synchronization concepts to coordinate operations.

## Problem Overview

Ten airplanes (threads) operate concurrently:
- Each airplane **lands**, **parks in a hangar**, **waits**, then **takes off**.
- A shared **runway** is used for both landing and takeoff.
- A **hangar** can accommodate a limited number of planes at once (capacity = 5).

## Synchronization

- **Runway** access is protected using a boolean flag `runwayFree`, but it's not thread-safe. A proper implementation would ideally use a mutex or semaphore.
- **Hangar** state is tracked using a `set<string>` of plane names, but also lacks locking mechanisms for safe concurrent access.
- Includes a placeholder for a `Semaphore` header (`semaphore.h`) but doesn't use semaphores explicitly in this file.

> ⚠️ Some issues like **race conditions** and **unsynchronized shared state** (e.g. `runwayFree`, `planes` set) are present. Consider using mutexes or semaphores for thread safety.

## Classes

### `Airplane`
- Simulates an airplane’s full cycle:
  1. Land (after some random wait)
  2. Wait at arrival hall
  3. Park in hangar
  4. Stay in hangar
  5. Leave hangar
  6. Wait at departure hall
  7. Take off

### `Airport`
- Coordinates landing, hangar operations, and takeoffs.
- Manages shared `runwayFree` flag and delegates hangar interactions to the `Hangar` class.

### `Hangar`
- Stores airplane names to simulate capacity.
- Manages insertion/removal of planes from a `set`.


## Compilation and execution

```bash
g++ airport.cc thread-semaphore.cpp -o airport -lpthread

./airport


