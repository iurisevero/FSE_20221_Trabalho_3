#ifndef _NVS_RW_H_
#define _NVS_RW_H

int read_uint8_t_nvs(char * to_open_namespace, char * key, uint8_t * value);
int read_int8_t_nvs(char * to_open_namespace, char * key, int8_t * value);
int read_uint16_t_nvs(char * to_open_namespace, char * key, uint16_t * value);
int read_int16_t_nvs(char * to_open_namespace, char * key, int16_t * value);
int read_uint32_t_nvs(char * to_open_namespace, char * key, uint32_t * value);
int read_int32_t_nvs(char * to_open_namespace, char * key, int32_t * value);
int read_uint64_t_nvs(char * to_open_namespace, char * key, uint64_t * value);
int read_int64_t_nvs(char * to_open_namespace, char * key, int64_t * value);
int read_string_nvs(char * to_open_namespace, char * key, char * value, size_t * _size);
void write_uint8_t_nvs(char * to_open_namespace, char * key, uint8_t * value);
void write_int8_t_nvs(char * to_open_namespace, char * key, int8_t * value);
void write_uint16_t_nvs(char * to_open_namespace, char * key, uint16_t * value);
void write_int16_t_nvs(char * to_open_namespace, char * key, int16_t * value);
void write_uint32_t_nvs(char * to_open_namespace, char * key, uint32_t * value);
void write_int32_t_nvs(char * to_open_namespace, char * key, int32_t * value);
void write_uint64_t_nvs(char * to_open_namespace, char * key, uint64_t * value);
void write_int64_t_nvs(char * to_open_namespace, char * key, int64_t * value);
void write_string_nvs(char * to_open_namespace, char * key, char * value);

#endif