# Show Reservation (Movie) - C

This is a simple movie/show reservation program.

Features
- Seats numbered 1 to 50.
- Persistent storage in `show_reservations.txt`.
- Prevents double-booking for the same theatre/date/show time.
- Displays seat layout with 10 seats per row; occupied seats marked `X`.

Build & run (PowerShell)
```powershell
gcc -g ShowReservation.c show_reservation_impl.c -o ShowReservation.exe
.\ShowReservation.exe
```

Usage
- Choose `1` to book tickets: enter theatre, date, show time (N/F/S), movie title, number of tickets, and fare per ticket. Pick seats one by one.
- Choose `2` to display seats for a theatre/date/time.
- Choose `3` to exit.
