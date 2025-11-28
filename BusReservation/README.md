
# Bus Reservation (C)

This program is a menu-driven bus reservation system that:

- Stores reservations persistently in `reservations.txt` (in the same folder as the executable).
- Prevents double-booking: a seat already allotted for the same service number and date cannot be booked again.
- Displays seat layout with 4 seats per row; occupied seats are marked with `X`.

Compile and run on Windows PowerShell (with `gcc` available):

```powershell
gcc -g BusReservation.c -o BusReservation.exe
.\BusReservation.exe
```

How to use:
- Choose `1` to book a seat. You will be asked for `Service number`, `Date of Journey`, `Boarding`, `Destination`, `Passenger Name`, and `Fare`.
- After entering those, the current seat layout for that service/date is shown. Enter a seat number (3–30) to book it.
- Choose `2` to display the seats for a specific `Service number` and `Date of Journey`.
- Choose `3` to exit.

Notes:
- Reservations are stored line-by-line in `reservations.txt` with the format:
	`service_no|date|boarding|destination|passenger_name|fare|seat_no`
- Inputs are sanitized to avoid breaking the file format (characters like `|` are replaced).

