#ifndef _JSON_UTILS_H_
#define _JSON_UTILS_H_

#include "jsmn.h"

int jsoneq(const char *json, jsmntok_t *tok, const char *s);
int custom_parse(jsmntok_t * t, char * json);
int get_value_int(jsmntok_t * t, char * json, int r, char * key);
int get_value_bool(jsmntok_t * t, char * json, int r, char * key);
char * get_value_string(jsmntok_t * t, char * json, int r, char * key);
void get_response_method(char *response, char *method);
void get_response_params(char *response, char *params);

#endif