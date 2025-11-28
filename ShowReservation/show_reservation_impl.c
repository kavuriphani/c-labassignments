#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "show_reservation.h"

/* replace '|' and newlines */
void show_sanitize(char *s) {
    for (; *s; ++s) {
        if (*s == '|' || *s == '\n' || *s == '\r') *s = '-';
    }
}

void show_flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) ;
}

bool show_save_reservation(const ShowReservation *r) {
    FILE *f = fopen(SHOW_RES_FILE, "a");
    if (!f) return false;
    /* format: theatre|date|show_time|movie|fare|seat */
    fprintf(f, "%s|%s|%c|%s|%.2f|%d\n",
            r->theatre, r->date, r->show_time, r->movie, r->fare, r->seat_no);
    fclose(f);
    return true;
}

void show_load_occupied(const char *theatre, const char *date, char show_time, bool occupied[]) {
    FILE *f = fopen(SHOW_RES_FILE, "r");
    if (!f) return;
    char line[512];
    while (fgets(line, sizeof line, f)) {
        char *tokens[7] = {0};
        int t = 0;
        line[strcspn(line, "\r\n")] = '\0';
        char *tok = strtok(line, "|");
        while (tok && t < 7) {
            tokens[t++] = tok;
            tok = strtok(NULL, "|");
        }
        if (t < 6) continue;
        /* tokens: 0-theatre,1-date,2-show_time,3-movie,4-fare,5-seat */
        if (strcmp(tokens[0], theatre) == 0 && strcmp(tokens[1], date) == 0 && tokens[2][0] == show_time) {
            int seat = atoi(tokens[5]);
            if (seat >= SHOW_MIN_SEAT && seat <= SHOW_MAX_SEAT) occupied[seat] = true;
        }
    }
    fclose(f);
}

void show_display_seats(const bool occupied[]) {
    int seat = SHOW_MIN_SEAT;
    printf("\nShow seat layout (X = occupied, empty = available)\n");
    for (int row = 0; seat <= SHOW_MAX_SEAT; ++row) {
        for (int c = 0; c < SHOW_SEATS_PER_ROW && seat <= SHOW_MAX_SEAT; ++c, ++seat) {
            if (occupied[seat])
                printf("%2d[X] ", seat);
            else
                printf("%2d[ ] ", seat);
        }
        printf("\n");
    }
}
