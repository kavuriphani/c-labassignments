#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bus_reservation.h"

/* sanitize string by replacing '|' and newlines */
void sanitize(char *s) {
    for (; *s; ++s) {
        if (*s == '|' || *s == '\n' || *s == '\r') *s = '-';
    }
}

/* Append reservation as a single line to file */
bool save_reservation(const Reservation *r) {
    FILE *f = fopen(RES_FILE, "a");
    if (!f) return false;
    fprintf(f, "%d|%s|%s|%s|%s|%.2f|%d\n",
            r->service_no, r->date, r->boarding, r->destination,
            r->passenger_name, r->fare, r->seat_no);
    fclose(f);
    return true;
}

/* Load reservations for given service and date, mark occupied seats */
void load_occupied(int service_no, const char *date, bool occupied[]) {
    FILE *f = fopen(RES_FILE, "r");
    if (!f) return;
    char line[512];
    while (fgets(line, sizeof line, f)) {
        int sn = 0, seat = 0;
        char *tokens[8] = {0};
        int t = 0;
        /* strip trailing newline */
        line[strcspn(line, "\r\n")] = '\0';
        /* file format: service_no|date|boarding|destination|passenger_name|fare|seat */
        char *tok = strtok(line, "|");
        while (tok && t < 8) {
            tokens[t++] = tok;
            tok = strtok(NULL, "|");
        }
        if (t < 7) continue; /* malformed line */
        sn = atoi(tokens[0]);
        /* date in tokens[1] */
        if (sn == service_no && strcmp(tokens[1], date) == 0) {
            seat = atoi(tokens[6]);
            if (seat >= MIN_SEAT && seat <= MAX_SEAT) occupied[seat] = true;
        }
    }
    fclose(f);
}

void display_seats(const bool occupied[]) {
    int seat = MIN_SEAT;
    printf("\nSeat layout (X = occupied, empty = available)\n");
    for (int row = 0; seat <= MAX_SEAT; ++row) {
        for (int c = 0; c < SEATS_PER_ROW && seat <= MAX_SEAT; ++c, ++seat) {
            if (occupied[seat])
                printf("%2d[X] ", seat);
            else
                printf("%2d[ ] ", seat);
        }
        printf("\n");
    }
}

void flush_input(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) ;
}
