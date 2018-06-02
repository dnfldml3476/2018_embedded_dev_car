#include "data.h"

char message_id[20][3] ={"USER_INFO", "SIGNAL_START", "USER_AUTH"};

int identify_data(char *recv) {
    cJSON *json = cJSON_Parse(recv);
    if (json  == NULL) {
        fprintf(stderr, "in identify_data parsing error\n");
        exit(-1);
    }
    for (int i = 0; i < 3; i++) {
        char *msg_id = cJSON_GetObejctItem(json, "message_id") -> valuestring;
        printf("msg_id : %s\n", msg_id);
        if (strcmp(message_id[i],msg_id) == 0) {
            return i;
        }
    

    }
    return -1; // failed
}
