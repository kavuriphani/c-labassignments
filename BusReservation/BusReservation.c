#include <stdio.h>
#include <string.h>
#include "bus_reservation.h"

int main(void) {
    int choice = 0;
    while (1) {
        printf("\nBus Reservation System\n");
        printf("1. Book a seat\n");
        printf("2. Display seats for a service/date\n");
        printf("3. Exit\n");
        printf("Choose option: ");
        if (scanf("%d", &choice) != 1) break;
        flush_input();

        if (choice == 1) {
            Reservation r = {0};
            printf("Enter Service number: ");
            if (scanf("%d", &r.service_no) != 1) { flush_input(); continue; }
            flush_input();

            printf("Enter Date of Journey (DD-MM-YYYY): ");
            if (!fgets(r.date, sizeof r.date, stdin)) continue;
            r.date[strcspn(r.date, "\r\n")] = '\0';

            printf("Enter Boarding place: ");
            if (!fgets(r.boarding, sizeof r.boarding, stdin)) continue;
            r.boarding[strcspn(r.boarding, "\r\n")] = '\0';

            printf("Enter Destination place: ");
            if (!fgets(r.destination, sizeof r.destination, stdin)) continue;
            r.destination[strcspn(r.destination, "\r\n")] = '\0';

            printf("Enter Passenger Name: ");
            if (!fgets(r.passenger_name, sizeof r.passenger_name, stdin)) continue;
            r.passenger_name[strcspn(r.passenger_name, "\r\n")] = '\0';

            printf("Enter Fare: ");
            if (scanf("%f", &r.fare) != 1) { flush_input(); continue; }
            flush_input();

            /* show current layout for this service/date */
            bool occupied[MAX_SEAT+1];
            for (int i = 0; i <= MAX_SEAT; ++i) occupied[i] = false;
            load_occupied(r.service_no, r.date, occupied);
            display_seats(occupied);

            while (1) {
                printf("Enter Seat number to book (%d-%d) or 0 to cancel: ", MIN_SEAT, MAX_SEAT);
                if (scanf("%d", &r.seat_no) != 1) { flush_input(); printf("Invalid input.\n"); continue; }
                flush_input();
                if (r.seat_no == 0) { printf("Booking cancelled.\n"); break; }
                if (r.seat_no < MIN_SEAT || r.seat_no > MAX_SEAT) { printf("Seat must be between %d and %d.\n", MIN_SEAT, MAX_SEAT); continue; }
                if (occupied[r.seat_no]) { printf("Seat %d is already allotted. Choose another seat.\n", r.seat_no); continue; }

                /* sanitize inputs to avoid breaking file format */
                sanitize(r.boarding); sanitize(r.destination); sanitize(r.passenger_name); sanitize(r.date);

                if (save_reservation(&r)) {
                    printf("Seat %d successfully booked for %s on %s.\n", r.seat_no, r.passenger_name, r.date);
                } else {
                    printf("Failed to save reservation.\n");
                }
                break;
            }

        } else if (choice == 2) {
            int service_no;
            char date[20];
            printf("Enter Service number: ");
            if (scanf("%d", &service_no) != 1) { flush_input(); continue; }
            flush_input();
            printf("Enter Date of Journey (DD-MM-YYYY): ");
            if (!fgets(date, sizeof date, stdin)) continue;
            date[strcspn(date, "\r\n")] = '\0';

            bool occupied[MAX_SEAT+1];
            for (int i = 0; i <= MAX_SEAT; ++i) occupied[i] = false;
            load_occupied(service_no, date, occupied);
            display_seats(occupied);

        } else if (choice == 3) {
            printf("Exiting.\n");
            break;
        } else {
            printf("Invalid option.\n");
        }
    }

    return 0;
}
