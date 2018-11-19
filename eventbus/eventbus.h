/**
 * Engi's Kitchen Expansion
 * Event Bus
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file eventbus.h
 */

#ifndef EVENTBUSTEST_EVENTBUS_H
#define EVENTBUSTEST_EVENTBUS_H

#include "../adt/mesin_kata.h"
#include "events.h"
#include "../adt/obj/meja.h"

#define MAX_LISTENERS 5

typedef union {
    int integer;
    char character;
    char *string;
    Kata kata;
    Commands cmd;
    Meja meja;
    TabMeja tabMeja;
} DataType;


typedef void (*f_broadcast)();
typedef void (*f_broadcast_1p)(DataType);
typedef void (*f_broadcast_np)(DataType, ...);
typedef DataType (*f_getval)();

typedef struct {
    f_broadcast T[MAX_LISTENERS + 1];
    int N;
} BroadcastListeners;

typedef struct {
    f_broadcast_1p T[MAX_LISTENERS + 1];
    int N;
} Broadcast1PListeners;

typedef struct {
    f_broadcast_np T[MAX_LISTENERS + 1];
    int N;
} BroadcastNPListeners;

typedef union {
    BroadcastListeners broadcastListeners;
    Broadcast1PListeners broadcast1PListeners;
    BroadcastNPListeners broadcastNPListeners;
    f_getval getvalListener;
} Listeners;

typedef struct {
    Listeners T[NO_OF_EVENTS];
    int N;
} Events;

Events events;

void listen_event(Event event, f_broadcast f);
void listen_1p_event(Event event, f_broadcast_1p f);
void listen_np_event(Event event, f_broadcast_np f);
void listen_getval_event(Event event, f_getval f);

void publish_event(Event event);
void publish_1p_event(Event event, DataType data);
void publish_np_event(Event event, DataType data, ...);
DataType publish_getval_event(Event event);

#endif //EVENTBUSTEST_EVENTBUS_H
