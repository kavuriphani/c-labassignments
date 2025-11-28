# C Lab Assignments

This repository contains multiple C-language lab assignments and small projects. Each subfolder is a separate assignment with its own source files, a short README, and (where provided) build scripts (`Makefile` and/or `build.bat`).

Project list (top-level folders):

- `BankTransaction` — simple bank account/transaction program.
- `BusReservation` — bus reservation system.
- `CurrencyConversion` — currency conversion example.
- `DistanceConversion` — distance/unit conversion examples.
- `ElectricityBillGenerator` — electricity bill generator sample.
- `EmployeeManagementSystem` — employee records demo.
- `LibraryManagement` — library account/transaction system.
- `MemoryConversion` — memory unit conversion examples.
- `ProductManagement` — product management demo.
- `ShowReservation` — show/theater reservation program.
- `StudentManagementSystem` — student records project.
- `UnitConversion`, `VolumeConversion`, `WeightConversion` — various unit converters.

Quick start (Windows PowerShell):

1. Open PowerShell and change to the repository root:

```powershell
cd 'C:\Projects\c-labassignments'
```

2. Build a specific assignment:

- If the folder contains `build.bat`, run it (Windows):

```powershell
cd .\BankTransaction
.\build.bat
```

- If the folder contains a `Makefile`, you can use `make` (if you have GNU Make installed):

```powershell
cd .\BankTransaction
make
```

3. Run the produced executable (usually in the same folder). Example on Windows:

```powershell
.\BankTransaction.exe
```

Notes:

- Many assignments include `README.md` files inside their folders with project-specific details (input files, expected behavior, and sample commands).
- The repository contains sample input files such as `accounts.txt`, `transactions.txt`, `reservations.txt`, and `library_transactions.txt` used by several programs.
- A `.gitignore` has been added to exclude build artifacts and IDE/editor folders (e.g. `*.exe`, `.vscode/`).

Contributing
- If you add new assignments, include a short `README.md` in the assignment folder and, if applicable, a `Makefile` or `build.bat` to ease building.

License
- No license is specified. Add a `LICENSE` file if you want to make licensing explicit.
