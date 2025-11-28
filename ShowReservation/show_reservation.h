#ifndef SHOW_RESERVATION_H
#define SHOW_RESERVATION_H

#include <stdbool.h>

#define SHOW_MIN_SEAT 1
#define SHOW_MAX_SEAT 50
#define SHOW_SEATS_PER_ROW 10
#define SHOW_RES_FILE "show_reservations.txt"

typedef struct {
    char theatre[100];
    char date[20];
    char show_time; /* 'N'/'F'/'S' */
    char movie[100];
    int tickets;
    float fare;
    int seat_no;
} ShowReservation;

/* utilities */
void show_sanitize(char *s);
void show_flush_input(void);

/* persistence */
bool show_save_reservation(const ShowReservation *r);
void show_load_occupied(const char *theatre, const char *date, char show_time, bool occupied[]);

/* display */
void show_display_seats(const bool occupied[]);

#endif /* SHOW_RESERVATION_H */
