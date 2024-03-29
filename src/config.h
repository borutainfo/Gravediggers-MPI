#ifndef GRAVEDIGGERS_CONFIG_H
#define GRAVEDIGGERS_CONFIG_H

/** WORKING MODE */
#define DEBUG true

/** MAIN CONFIG */
#define MIN_NUMBER_OF_DEATHS 1
#define MAX_NUMBER_OF_DEATHS 5

#define COUNCIL_SLEEP_TIME 7
#define FUNERAL_TIME 5
#define OFFICIAL_TIME 0

/** THREADS IDS */
#define CITY_COUNCIL 0

/** MESSAGE TAGS */
#define DEATH_LIST_PUBLICATION 1
#define FUNERAL_OFFER 2
#define OFFICIAL_TOKEN 3

/** DISTRIBUTOR CONFIG */
#define MAX_ARRAY_SIZE MAX_NUMBER_OF_DEATHS
#define BROADCAST_EXCLUDED CITY_COUNCIL

#endif
