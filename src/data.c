#include <data.h>

char message_id[3][20] ={"USER_INFO", "SIGNAL_START", "USER_AUTH"};

void test_read() {
    char json[1024] ={ 0, };

    int nread;
    int fd = open("json_data.json", O_RDONLY);
    nread = read(fd, json, sizeof(json));
    json[nread-1] = 0;

    //memset(recv_message, 0, sizeof(recv_message));
    recv_message = json;

    printf("\n%s\n", recv_message);

    int ret =  identify_msg();
    printf("%d\n", ret);

}

int save_img(char *filename, char *text, int size) {
    FILE *fp = fopen(filename, "w");
    
    int count = fwrite(text, size, 1, fp);
    fclose(fp);
    
    if (count == 0) {
        fprintf(stderr, "fwrite error %s\n", filename);
        return -1;
    }
    
    return 0;    
}

int identify_msg() {
    cJSON *json = cJSON_Parse(recv_message);
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

int parse_msg(int id) {
    switch(id) {
        case 0:
            printf("call parse_userinfo() and save user_image\n");
            parse_userinfo();
            //save_img(); // make user_image.jpg
            break;
        case 1:
            printf("call parse_signal() \n");
            parse_signal();
            break;
        default:
            fprintf(stderr, "msg parsing error\n");
            return -1;
    }
    return 0;
}

int parse_userinfo() {
    cJSON *json = cJSON_Parse(recv_message);
    
    user_info.message_id = cJSON_GetObjectItemCaseSensitive(json, "message_id") -> valuestring;
    cJSON *data = cJSON_GetObjectItemCaseSensitive(json, "data");
    
    user_info.name= cJSON_GetObjectItemCaseSensitive(data, "name") -> valuestring;
    user_info.image = cJSON_GetObjectItemCaseSensitive(data, "image") -> valuestring;
    user_info.length = cJSON_GetObjectItemCaseSensitive(data, "length") -> valueint;
    
    if (user_info.name != NULL) {
        char *decode_text = (char *)malloc(user_info.length);
        printf("user's name is %s\n", user_info.name);
        
        // encoding base64 and save_image
        base64_decode(user_info.image, decode_text, user_info.length); 
        if(save_img(USER_FILENAME, decode_text, user_info.length) == -1) {
            fprintf(stderr, "save_image error\n");
            return -1;
        }
        free(decode_text);
    }
    else {
        fprintf(stderr, "user info is NULL error!\n");
        return -1; // fail!
    }

    
    user_info.result = cJSON_GetObjectItemCaseSensitive(data, "result") -> valuestring;
    return 0;
}

int parse_signal() {
    cJSON *json = cJSON_Parse(recv_message);
    
    signal_start.message_id = cJSON_GetObjectItemCaseSensitive(json, "message_id") -> valuestring;
    cJSON *data = cJSON_GetObjectItemCaseSensitive(json, "data");
    
    signal_start.car_speed = cJSON_GetObjectItemCaseSensitive(data, "car_speed") ->valueint;
    
    printf("setting car_speed : %d\n", signal_start.car_speed);

    return 0;
}

int make_userauth(int val) {
    if (UserAuth == NULL)
        UserAuth = cJSON_CreateObject();
    else {
        cJSON_Delete(UserAuth);
        UserAuth = cJSON_CreateObject();
    }
    cJSON *message_id = cJSON_CreateObject();
    cJSON *data = cJSON_CreateObject();
    cJSON *result = cJSON_CreateObject();

    message_id = cJSON_CreateString("USER_AUTH");

    cJSON *tmp = cJSON_CreateObject();
    if (val == 1)
        tmp = cJSON_CreateString("success");
    else if (val == 0)
        tmp = cJSON_CreateString("fail");
    cJSON_AddItemToObject(data, "result", tmp);

    result = cJSON_CreateString("success");

    cJSON_AddItemToObject(UserAuth, "message_id", message_id);
    cJSON_AddItemToObject(UserAuth, "data", data);
    cJSON_AddItemToObject(UserAuth, "result", result);
    if (UserAuth != NULL) {
        char *string = cJSON_Print(UserAuth);
        if (string == NULL) {
            fprintf(stderr, "cJSON_Parse(UserAuth) error\n");
            return -1;
        }
        printf("making UserAuth is success\n %s\n", string);
    }
    else {
        fprintf(stderr, "UserAuth is NULL\n");
        return -1;
    }
    return 0;
}



