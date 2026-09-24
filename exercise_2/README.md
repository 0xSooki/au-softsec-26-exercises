# Secure Code Review Lab: ADFMS Flight Controller

## Scenario

SkyFleet Technologies builds the **Autonomous Drone Fleet Management System (ADFMS)**,
which controls autonomous medical delivery drones. The Flight Controller module
authenticates operators, validates missions, uploads them to the drone and logs
mission activity.

Before the module is certified for deployment, you have been asked to do a
**manual security code review**. The code base is **frozen at ADFMS Version 1.0**.
Do not change it; review it as delivered.

## Files

| File | Description |
|------|-------------|
| `src/ADFMS.cpp` | The complete source code under review |
| `src/ADFMS_part1.txt` | Part 1 of the source: headers and class declarations (lines 1–280) |
| `src/ADFMS_part2.txt` | Part 2 of the source: FlightController implementation and `main()` (lines 282–538) |
| `ADFMS_v1.0_Student_Code_Review_Line_Numbered.pdf` | Line-numbered listing. **Use these line numbers in your answers.** |
| `ADFMS.exe` | Pre-built Windows binary of the same code |
| `REVIEW_TEMPLATE.md` | Template for your solutions |

## Building and running (optional)

```bash
# Linux / macOS
g++ -std=c++11 -o ADFMS src/ADFMS.cpp
./ADFMS
```

On Windows you can run `ADFMS.exe` directly, or build with MinGW using the same command.

## Your task

Review the code and identify **at least five security vulnerabilities**. For each vulnerability, answer the following questions in the `REVIEW_TEMPLATE.md`
