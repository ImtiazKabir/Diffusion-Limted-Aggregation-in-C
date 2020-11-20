#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "Vector.h"
#include "mover.h"
#include <time.h>
#include <stdlib.h>
#include "global.h"

#define FPS 60.0


#define total 1000
Mover *movers[total];

int stuckIndex[total];
int length = 0;

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_TIMER *timer;

void updateStats();

int main() {
    al_init();
    al_init_primitives_addon();
    
    display = al_create_display(WIDTH, HEIGHT);
    queue = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    //!setup starts
    srand(time(NULL));
    movers[0] = createMover(WIDTH/2.0, HEIGHT/2.0);
    movers[0]->canMove = false;
    stuckIndex[length] = 0;
    ++length;
    for (int i = 1; i < total; ++i) {
        int side = rand() % 4;
        float pos = rand() / (double) RAND_MAX;
        switch(side) {
            case 0:
                movers[i] = createMover(pos * WIDTH, 0);
                break;
            case 1:
                movers[i] = createMover(WIDTH, pos * HEIGHT);
                break;
            case 2:
                movers[i] = createMover(pos * WIDTH, HEIGHT);
                break;
            case 3:
                movers[i] = createMover(0, pos * HEIGHT);
                break;
        }
    }
    //!setup ends


    bool runFrame = true;
    al_start_timer(timer);
    while (runFrame) {
        bool redraw = false;
        while (!al_is_event_queue_empty(queue)) {
            ALLEGRO_EVENT event;
            al_wait_for_event(queue, &event);
            switch (event.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    runFrame = false;
                    break;
                case ALLEGRO_EVENT_TIMER:
                    redraw = true;
                    break;
            }
        }

        if (redraw) {
            al_clear_to_color(al_map_rgb(51, 51, 51));
            for (int i = 0; i < total; ++i) {
                if(movers[i]->canMove) Mover_update(movers[i]);
                Mover_display(movers[i]);
            }
            updateStats();
            al_flip_display();
        }
    }
    
    for (int i = 0 ; i < total; ++i) {
        free(movers[i]->loc);
        free(movers[i]);
    }
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    return 0;
}



void updateStats() {
    int proxyStuck[total];
    int pl = 0;
    for (int i = 0; i < total; ++i) {
        if (!movers[i]->canMove) continue;
        for (int j = 0; j < length; ++j) {
            int z = stuckIndex[j];
            float x = movers[i]->loc->x - movers[z]->loc->x;
            float y = movers[i]->loc->y - movers[z]->loc->y;
            float r = movers[i]->r;
            if (x*x + y*y <= r*r) {
                movers[i]->canMove = false;
                proxyStuck[pl] = i;
                ++pl;
                break;
            }
        }
    }
    for (int i = 0; i < pl; ++i) {
        stuckIndex[length] = proxyStuck[i];
        ++ length;
    }
}
