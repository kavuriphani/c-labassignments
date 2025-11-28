#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "show_reservation.h"

int main(void) {
    int choice = 0;
    while (1) {
        printf("\nMovie Reservation System\n");
        printf("1. Book tickets\n");
        printf("2. Display seats for theatre/date/time\n");
        printf("3. Exit\n");
        printf("Choose option: ");
        if (scanf("%d", &choice) != 1) break;
        show_flush_input();

        if (choice == 1) {
            ShowReservation r = {0};
            printf("Enter Theatre name: ");
            if (!fgets(r.theatre, sizeof r.theatre, stdin)) continue;
            r.theatre[strcspn(r.theatre, "\r\n")] = '\0';

            printf("Enter Date of show (DD-MM-YYYY): ");
            if (!fgets(r.date, sizeof r.date, stdin)) continue;
            r.date[strcspn(r.date, "\r\n")] = '\0';

            printf("Enter Show Time (N-Noon / F-First / S-Second): ");
            int ch = getchar();
            if (ch == EOF) continue;
            r.show_time = (char)ch;
            show_flush_input();

            printf("Enter Movie Title: ");
            if (!fgets(r.movie, sizeof r.movie, stdin)) continue;
            r.movie[strcspn(r.movie, "\r\n")] = '\0';

            printf("Enter Number of Tickets: ");
            if (scanf("%d", &r.tickets) != 1) { show_flush_input(); continue; }
            show_flush_input();

            printf("Enter Fare (per ticket): ");
            if (scanf("%f", &r.fare) != 1) { show_flush_input(); continue; }
            show_flush_input();

            if (r.tickets <= 0) { printf("Number of tickets must be positive.\n"); continue; }

            bool occupied[SHOW_MAX_SEAT+1];
            for (int i = 0; i <= SHOW_MAX_SEAT; ++i) occupied[i] = false;
            show_load_occupied(r.theatre, r.date, r.show_time, occupied);
            show_display_seats(occupied);

            int to_book = r.tickets;
            while (to_book > 0) {
                printf("Enter seat number to book (or 0 to cancel): ");
                int s;
                if (scanf("%d", &s) != 1) { show_flush_input(); printf("Invalid input.\n"); continue; }
                show_flush_input();
                if (s == 0) { printf("Booking cancelled.\n"); break; }
                if (s < SHOW_MIN_SEAT || s > SHOW_MAX_SEAT) { printf("Seat must be between %d and %d.\n", SHOW_MIN_SEAT, SHOW_MAX_SEAT); continue; }
                if (occupied[s]) { printf("Seat %d is already booked. Choose another.\n", s); continue; }

                /* save one reservation line per seat */
                r.seat_no = s;
                show_sanitize(r.theatre); show_sanitize(r.date); show_sanitize(r.movie);
                if (show_save_reservation(&r)) {
                    printf("Seat %d booked.\n", s);
                    occupied[s] = true;
                    --to_book;
                } else {
                    printf("Failed to save seat %d.\n", s);
                }
            }

        } else if (choice == 2) {
            char theatre[100];
            char date[20];
            char tchar;
            printf("Enter Theatre name: ");
            if (!fgets(theatre, sizeof theatre, stdin)) continue;
            theatre[strcspn(theatre, "\r\n")] = '\0';
            printf("Enter Date of show (DD-MM-YYYY): ");
            if (!fgets(date, sizeof date, stdin)) continue;
            date[strcspn(date, "\r\n")] = '\0';
            printf("Enter Show Time (N/F/S): ");
            int c = getchar(); if (c == EOF) continue; tchar = (char)c; show_flush_input();

            bool occupied[SHOW_MAX_SEAT+1];
            for (int i = 0; i <= SHOW_MAX_SEAT; ++i) occupied[i] = false;
            show_load_occupied(theatre, date, tchar, occupied);
            show_display_seats(occupied);

        } else if (choice == 3) {
            printf("Exiting.\n");
            break;
        } else {
            printf("Invalid option.\n");
        }
    }

    return 0;
}
