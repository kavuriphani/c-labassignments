#ifndef BUS_RESERVATION_H
#define BUS_RESERVATION_H

#include <stdbool.h>

#define MIN_SEAT 3
#define MAX_SEAT 30
#define SEATS_PER_ROW 4
#define RES_FILE "reservations.txt"

typedef struct {
    int service_no;
    char boarding[50];
    char destination[50];
    char passenger_name[100];
    char date[20];
    float fare;
    int seat_no;
} Reservation;

/* utility */
void sanitize(char *s);
void flush_input(void);

/* persistence and querying */
bool save_reservation(const Reservation *r);
void load_occupied(int service_no, const char *date, bool occupied[]);

/* display */
void display_seats(const bool occupied[]);

#endif /* BUS_RESERVATION_H */
