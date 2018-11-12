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

#define MAX_LISTENERS 5
#define NO_OF_EVENTS 10

typedef union {
    int integer;
    char character;
    char *string;
    Kata kata;
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

typedef struct {
    BroadcastListeners T[NO_OF_EVENTS];
    int N;
} BroadcastEvents;

typedef struct {
    Broadcast1PListeners T[NO_OF_EVENTS];
    int N;
} Broadcast1PEvents;

typedef struct {
    BroadcastNPListeners T[NO_OF_EVENTS];
    int N;
} BroadcastNPEvents;

typedef struct {
    f_getval T[NO_OF_EVENTS];
    int N;
} GetvalEvents;

BroadcastEvents broadcastEvents;
Broadcast1PEvents broadcast1PEvents;
BroadcastNPEvents broadcastNPEvents;
GetvalEvents getvalEvents;

void listen_event(int event, f_broadcast f);
void listen_1p_event(int event, f_broadcast_1p f);
void listen_np_event(int event, f_broadcast_np f);
void listen_getval_event(int event, f_getval f);

void publish_event(int event);
void publish_1p_event(int event, DataType data);
void publish_np_event(int event, DataType data, ...);
DataType publish_getval_event(int event);

#endif //EVENTBUSTEST_EVENTBUS_H
