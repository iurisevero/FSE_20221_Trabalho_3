#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "json_utils.h"

int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

int custom_parse(jsmntok_t * t, char * json){
  int r;
  jsmn_parser p;

  jsmn_init(&p);
  r = jsmn_parse(&p, json, strlen(json), t,
                 sizeof(*t) / sizeof(t[0]));
  if (r < 0) {
    printf("Failed to parse JSON: %d\n", r);
    return 1;
  }

  /* Assume the top-level element is an object */
  if (r < 1 || t[0].type != JSMN_OBJECT) {
    printf("Object expected\n");
    return 1;
  }

  return r;
}

int get_value_int(jsmntok_t * t, char * json, int r, char * key){
    for (int i = 1; i < r; i++) {
        if(jsoneq(json, &t[i], key) == 0){
            return strtol(json + t[i + 1].start, NULL, t[i + 1].end - t[i + 1].start);
        } 
    }
    return 0;
}

int get_value_bool(jsmntok_t * t, char * json, int r, char * key){
    for (int i = 1; i < r; i++) {
        if(jsoneq(json, &t[i], key) == 0){
            char * value = strndup(json + t[i + 1].start, t[i + 1].end - t[i + 1].start);
            return (strcmp(value, "true") == 0? 1 : 0);
        } 
    }
    return 0;
}

char * get_value_string(jsmntok_t * t, char * json, int r, char * key){
    for (int i = 1; i < r; i++) {
        if(jsoneq(json, &t[i], key) == 0){
            return strndup(json + t[i + 1].start, t[i + 1].end - t[i + 1].start);
        } 
    }
    return "";
}