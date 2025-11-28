# Electricity Bill Generator

Small interactive console program written in C to calculate monthly electricity bills for Residential and Business consumers.

## Project structure

- `ElectricityBillGenerator.c` — main C source file (interactive program)
- `ElectricityBillGenerator.exe` — compiled executable (if present)

## Purpose

The program prompts for a consumer number, consumer type (Residential or Business), previous and present meter readings, computes units consumed, applies slab-based tariffs, and prints a formatted bill/receipt.

## Build (Windows / PowerShell)

Requires a C compiler such as MinGW `gcc`.

```powershell
cd 'c:\Projects\cardealership\ElectricityBillGenerator'
gcc ElectricityBillGenerator.c -o ElectricityBillGenerator.exe
```

## Run (PowerShell)

```powershell
.\ElectricityBillGenerator.exe
```

Follow the interactive prompts. The program shows a simple menu where you choose to calculate or exit.

## Example interaction

User input is entered when prompted. Example sequence (user inputs shown after colons):

- Choice: `1`
- Consumer Number: `101`
- Consumer Type: `R`
- Previous Month Reading: `1200`
- Present Month Reading: `1285`

Sample output (trimmed):

```
===============================================
           ELECTRICITY BILL RECEIPT
===============================================
Consumer Number    : 101
Consumer Type      : Residential
Number of Units    : 85
Bill Amount (Rs.)  : 127.50
===============================================
```

## Tariff (implemented)

- Business:
  - 0–200 units: Rs. 2.00 / unit
  - 201–450 units: Rs. 3.25 / unit (for units above 200)
  - 451+ units: Rs. 5.00 / unit (for units above 450)
- Residential:
  - 0–99 units: Rs. 1.50 / unit
  - 100–249 units: Rs. 2.25 / unit (for units above 100)
  - 250+ units: Rs. 3.00 / unit (for units above 250)

## Notes & limitations

- The program expects numeric input for readings and consumer number; it uses basic `scanf` and does not fully guard against malformed (non-numeric) input.
- Present reading must be strictly greater than previous reading; otherwise the program prints an error and returns to the menu.
- Consumer type must be `R` (Residential) or `B` (Business). Input is case-insensitive.

## Suggested improvements

- Validate non-numeric input and handle `scanf` failures.
- Add unit tests (small harness) to verify slab calculations.
- Add command-line options for non-interactive runs (e.g., pass readings and type as args).

If you want, I can:

- build and run a sample execution now, or
- add input validation to the C program, or
- add a small test script that runs a few slab calculation cases.
