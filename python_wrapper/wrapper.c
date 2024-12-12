#include "onesdk/onesdk.h"
#include <stdio.h>
#include <unistd.h>

// Initialize the OneAgent SDK
int initialize_oneagent() {
    onesdk_result_t result = onesdk_initialize();
    if (result != ONESDK_SUCCESS) {
        printf("OneAgent SDK initialization failed with error code: %d\n", result);
        return -1;
    }
    return 0;
}

// Shutdown the OneAgent SDK
void shutdown_oneagent() {
    onesdk_shutdown();
}

void simple_trace(){
    onesdk_tracer_handle_t const tracer = onesdk_outgoingremotecalltracer_create(
        onesdk_asciistr("remote service method"),
        onesdk_asciistr("logical service name"),
        onesdk_asciistr("deployed service endpoint"),
        ONESDK_CHANNEL_TYPE_TCP_IP,           /* channel type     */
        onesdk_asciistr("localhost:12345")    /* channel endpoint, host/ip:port in case of TCP_IP */ );

        onesdk_tracer_start(tracer);
        printf("\nInside trace...\n");
        sleep(3);
        onesdk_tracer_end(tracer);
}