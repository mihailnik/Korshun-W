//bird repeller
#include "repeller.h"
// Include Tasker class from Framework to work with periodic tasks
#include "ts.h"

// TaskScheduler - Let the runner object be a global, single instance shared between object files.
extern Scheduler ts;

// Periodic task that runs every 5 sec and calls sensor publishing method
Task tRepeller(1000, TASK_FOREVER, &tskRepeller, &ts, true );

static char volume;
static char voice;


/**
*
*
 */
void tskRepeller() {
   ;;
}

/**
 * Call-back for Periodic publisher 
 * it reads (virtual) sensors and publishes values to the WebUI
 */
void setVol(char v) {
   volume = v;
}

/**
 * Call-back for Periodic publisher 
 * it reads (virtual) sensors and publishes values to the WebUI
 */
char getVol() {

   return volume ;
}

/**
 * Call-back for Periodic publisher 
 * it reads (virtual) sensors and publishes values to the WebUI
 */
void setVoi(char v) {
   voice = v;
}

/**
 * Call-back for Periodic publisher 
 * it reads (virtual) sensors and publishes values to the WebUI
 */
char getVoi() {

   return voice ;
}