#include "data.h"
#include <fcntl.h>

char message_id[3][20] ={"USER_INFO", "SIGNAL_START", "USER_AUTH"};

void test_read() {
    char json[1024] ={ 0, };

    int nread;
    int fd = open("json_data.json", O_RDONLY);
    nread = read(fd, json, sizeof(json));
    json[nread-1] = 0;

    printf("\n%s\n", json);

    int ret =  identify_msg(json);
    printf("%d\n", ret);

}
int parse_msg(int id) {
    switch(id) {
        case 0:
            parse_userinfo();
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            fprintf(stderr, "msg parsing error\n");
            return -1;
    }
    return 0;
}


int identify_msg(char *recv) {
    cJSON *json = cJSON_Parse(recv);
    if (json  == NULL) {
        fprintf(stderr, "in identify_data parsing error\n");
        exit(-1);
    }
    for (int i = 0; i < MSG_CNT; i++) {
        char *msg_id = cJSON_GetObjectItemCaseSensitive(json, "message_id") -> valuestring;
        printf("msg_id : %s\n", msg_id);
        if (strcmp(message_id[i],msg_id) == 0) {
            return i;
        }
    

    }
    return -1; // failed
}

int parse_userinfo() {


    return 0;
}




