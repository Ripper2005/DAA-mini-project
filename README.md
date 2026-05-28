# DAA Mini Project: Bellman-Ford Algorithm

This repository contains a C implementation of the Bellman-Ford Shortest Path Algorithm with negative cycle detection, prepared as part of a 4th Semester Design and Analysis of Algorithms mini project.

## Project Title

Implementation and Analysis of the Bellman-Ford Shortest Path Algorithm with Negative Cycle Detection

## Overview

The Bellman-Ford algorithm solves the single-source shortest path problem for weighted directed graphs. Unlike Dijkstra's algorithm, Bellman-Ford can handle negative edge weights and can detect whether a negative-weight cycle is reachable from the source vertex.

This implementation:

- Reads a weighted directed graph from user input.
- Computes shortest distances from a selected source vertex.
- Reconstructs and prints shortest paths using a predecessor array.
- Detects reachable negative-weight cycles.
- Uses early termination when no relaxation occurs in a pass.
- Handles disconnected vertices by printing `INF` and `Unreachable`.

## Files

| File | Description |
|---|---|
| `bellman_ford.c` | Complete C source code for the Bellman-Ford algorithm. |

## Algorithm Features

- Language: C
- Input representation: Edge list
- Maximum vertices: 1000
- Supports negative edge weights
- Detects reachable negative-weight cycles
- Uses modular functions:
  - `readGraph()`
  - `initializeSingleSource()`
  - `bellmanFord()`
  - `printDistances()`
  - `printPath()`
  - `main()`

## Complexity Analysis

| Case | Time Complexity |
|---|---|
| Best case with early termination | `O(V + E)` |
| Average case | `O(V * E)` |
| Worst case | `O(V * E)` |

Space complexity is `O(V + E)` when edge-list storage is included. The auxiliary arrays for distance and predecessor values require `O(V)` space.

## Compilation

Use GCC to compile the program:

```bash
gcc -Wall -o bellman_ford bellman_ford.c
```

## Running the Program

```bash
./bellman_ford
```

On Windows PowerShell:

```powershell
.\bellman_ford.exe
```

## Input Format

The program expects:

1. Number of vertices `V`
2. Number of edges `E`
3. Each edge in the format `source destination weight`
4. Source vertex

Vertices are numbered from `0` to `V - 1`.

## Sample Input

```text
5
8
0 1 -1
0 2 4
1 2 3
1 3 2
1 4 2
3 2 5
3 1 1
4 3 -3
0
```

## Sample Output

```text
Vertex  Distance from Source
------  --------------------
0       0
1       -1
2       2
3       -2
4       1

Shortest paths from source 0:
Path to 0: 0
Path to 1: 0 -> 1
Path to 2: 0 -> 1 -> 2
Path to 3: 0 -> 1 -> 4 -> 3
Path to 4: 0 -> 1 -> 4
```

## Negative Cycle Example

Sample input:

```text
4
4
0 1 1
1 2 -1
2 3 -1
3 1 -1
0
```

Expected output:

```text
Negative weight cycle detected. Shortest paths are undefined.
```

## Applications

Bellman-Ford is used in:

- Distance-vector network routing protocols such as RIP.
- Currency arbitrage detection.
- Difference constraints systems.
- Traffic and navigation systems.
- Minimum-cost flow algorithms.
- AI path planning and graph-based machine learning tasks.

## Author

Harsha Vardhana M G  
USN/SRN: R24EK016
