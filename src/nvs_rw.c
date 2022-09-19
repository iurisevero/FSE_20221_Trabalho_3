#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "nvs_rw.h"

#define PARTITION_NAME "NVS_data"

int read_uint8_t_nvs(char * to_open_namespace, char * key, uint8_t * value) {
    // Inicia o acesso à partição personalizada
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;
    
    // Abre o acesso à partição DadosNVS
    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READONLY, &particao_padrao_handle);

    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    else
    {
        esp_err_t res = nvs_get_u8(particao_padrao_handle, key, value);

        switch (res)
        {
        case ESP_OK:
            printf("Valor armazenado: %d\n", *(value));
            break;
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE("NVS", "Valor não encontrado");
            return -1;
        default:
            ESP_LOGE("NVS", "Erro ao acessar o NVS (%s)", esp_err_to_name(res));
            return -1;
            break;
        }
        nvs_close(particao_padrao_handle);
    }
    return 0;
}

int read_int8_t_nvs(char * to_open_namespace, char * key, int8_t * value) {
    // Inicia o acesso à partição personalizada
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;
    
    // Abre o acesso à partição DadosNVS
    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READONLY, &particao_padrao_handle);

    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    else
    {
        esp_err_t res = nvs_get_i8(particao_padrao_handle, key, value);

        switch (res)
        {
        case ESP_OK:
            printf("Valor armazenado: %d\n", *(value));
            break;
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE("NVS", "Valor não encontrado");
            return -1;
        default:
            ESP_LOGE("NVS", "Erro ao acessar o NVS (%s)", esp_err_to_name(res));
            return -1;
            break;
        }
        nvs_close(particao_padrao_handle);
    }
    return 0;
}

int read_uint16_t_nvs(char * to_open_namespace, char * key, uint16_t * value) {
    // Inicia o acesso à partição personalizada
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;
    
    // Abre o acesso à partição DadosNVS
    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READONLY, &particao_padrao_handle);

    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    else
    {
        esp_err_t res = nvs_get_u16(particao_padrao_handle, key, value);

        switch (res)
        {
        case ESP_OK:
            printf("Valor armazenado: %d\n", *(value));
            break;
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE("NVS", "Valor não encontrado");
            return -1;
        default:
            ESP_LOGE("NVS", "Erro ao acessar o NVS (%s)", esp_err_to_name(res));
            return -1;
            break;
        }
        nvs_close(particao_padrao_handle);
    }
    return 0;
}

int read_int16_t_nvs(char * to_open_namespace, char * key, int16_t * value) {
    // Inicia o acesso à partição personalizada
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;
    
    // Abre o acesso à partição DadosNVS
    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READONLY, &particao_padrao_handle);

    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    else
    {
        esp_err_t res = nvs_get_i16(particao_padrao_handle, key, value);

        switch (res)
        {
        case ESP_OK:
            printf("Valor armazenado: %d\n", *(value));
            break;
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE("NVS", "Valor não encontrado");
            return -1;
        default:
            ESP_LOGE("NVS", "Erro ao acessar o NVS (%s)", esp_err_to_name(res));
            return -1;
            break;
        }
        nvs_close(particao_padrao_handle);
    }
    return 0;
}

int read_uint32_t_nvs(char * to_open_namespace, char * key, uint32_t * value) {
    // Inicia o acesso à partição personalizada
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;
    
    // Abre o acesso à partição DadosNVS
    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READONLY, &particao_padrao_handle);

    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    else
    {
        esp_err_t res = nvs_get_u32(particao_padrao_handle, key, value);

        switch (res)
        {
        case ESP_OK:
            printf("Valor armazenado: %d\n", *(value));
            break;
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE("NVS", "Valor não encontrado");
            return -1;
        default:
            ESP_LOGE("NVS", "Erro ao acessar o NVS (%s)", esp_err_to_name(res));
            return -1;
            break;
        }
        nvs_close(particao_padrao_handle);
    }
    return 0;
}

int read_int32_t_nvs(char * to_open_namespace, char * key, int32_t * value) {
    // Inicia o acesso à partição personalizada
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;
    
    // Abre o acesso à partição DadosNVS
    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READONLY, &particao_padrao_handle);

    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    else
    {
        esp_err_t res = nvs_get_i32(particao_padrao_handle, key, value);

        switch (res)
        {
        case ESP_OK:
            printf("Valor armazenado: %d\n", *(value));
            break;
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE("NVS", "Valor não encontrado");
            return -1;
        default:
            ESP_LOGE("NVS", "Erro ao acessar o NVS (%s)", esp_err_to_name(res));
            return -1;
            break;
        }
        nvs_close(particao_padrao_handle);
    }
    return 0;
}

int read_uint64_t_nvs(char * to_open_namespace, char * key, uint64_t * value) {
    // Inicia o acesso à partição personalizada
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;
    
    // Abre o acesso à partição DadosNVS
    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READONLY, &particao_padrao_handle);

    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    else
    {
        esp_err_t res = nvs_get_u64(particao_padrao_handle, key, value);

        switch (res)
        {
        case ESP_OK:
            printf("Valor armazenado: %lld\n", *(value));
            break;
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE("NVS", "Valor não encontrado");
            return -1;
        default:
            ESP_LOGE("NVS", "Erro ao acessar o NVS (%s)", esp_err_to_name(res));
            return -1;
            break;
        }
        nvs_close(particao_padrao_handle);
    }
    return 0;
}

int read_int64_t_nvs(char * to_open_namespace, char * key, int64_t * value) {
    // Inicia o acesso à partição personalizada
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;
    
    // Abre o acesso à partição DadosNVS
    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READONLY, &particao_padrao_handle);

    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    else
    {
        esp_err_t res = nvs_get_i64(particao_padrao_handle, key, value);

        switch (res)
        {
        case ESP_OK:
            printf("Valor armazenado: %lld\n", *(value));
            break;
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE("NVS", "Valor não encontrado");
            return -1;
        default:
            ESP_LOGE("NVS", "Erro ao acessar o NVS (%s)", esp_err_to_name(res));
            return -1;
            break;
        }
        nvs_close(particao_padrao_handle);
    }
    return 0;
}

int read_string_nvs(char * to_open_namespace, char * key, char * value, size_t * _size) {
    // Inicia o acesso à partição personalizada
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;
    
    // Abre o acesso à partição DadosNVS
    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READONLY, &particao_padrao_handle);

    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    else
    {
        esp_err_t res = nvs_get_str(particao_padrao_handle, key, value, _size);

        switch (res)
        {
        case ESP_OK:
            printf("Valor armazenado: %s\n", value);
            break;
        case ESP_ERR_NOT_FOUND:
            ESP_LOGE("NVS", "Valor não encontrado");
            return -1;
        default:
            ESP_LOGE("NVS", "Erro ao acessar o NVS (%s)", esp_err_to_name(res));
            return -1;
            break;
        }
        nvs_close(particao_padrao_handle);
    }
    return 0;
}

void write_uint8_t_nvs(char * to_open_namespace, char * key, uint8_t * value) {
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;

    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READWRITE, &particao_padrao_handle);
    
    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    esp_err_t res = nvs_set_u8(particao_padrao_handle, key, *(value));
    if(res != ESP_OK)
    {
        ESP_LOGE("NVS", "Não foi possível escrever no NVS (%s)", esp_err_to_name(res));
    }
    nvs_commit(particao_padrao_handle);
    nvs_close(particao_padrao_handle);
}

void write_int8_t_nvs(char * to_open_namespace, char * key, int8_t * value) {
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;

    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READWRITE, &particao_padrao_handle);
    
    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    esp_err_t res = nvs_set_i8(particao_padrao_handle, key, *(value));
    if(res != ESP_OK)
    {
        ESP_LOGE("NVS", "Não foi possível escrever no NVS (%s)", esp_err_to_name(res));
    }
    nvs_commit(particao_padrao_handle);
    nvs_close(particao_padrao_handle);
}

void write_uint16_t_nvs(char * to_open_namespace, char * key, uint16_t * value) {
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;

    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READWRITE, &particao_padrao_handle);
    
    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    esp_err_t res = nvs_set_u16(particao_padrao_handle, key, *(value));
    if(res != ESP_OK)
    {
        ESP_LOGE("NVS", "Não foi possível escrever no NVS (%s)", esp_err_to_name(res));
    }
    nvs_commit(particao_padrao_handle);
    nvs_close(particao_padrao_handle);
}

void write_int16_t_nvs(char * to_open_namespace, char * key, int16_t * value) {
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;

    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READWRITE, &particao_padrao_handle);
    
    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    esp_err_t res = nvs_set_i16(particao_padrao_handle, key, *(value));
    if(res != ESP_OK)
    {
        ESP_LOGE("NVS", "Não foi possível escrever no NVS (%s)", esp_err_to_name(res));
    }
    nvs_commit(particao_padrao_handle);
    nvs_close(particao_padrao_handle);
}

void write_uint32_t_nvs(char * to_open_namespace, char * key, uint32_t * value) {
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;

    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READWRITE, &particao_padrao_handle);
    
    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    esp_err_t res = nvs_set_u32(particao_padrao_handle, key, *(value));
    if(res != ESP_OK)
    {
        ESP_LOGE("NVS", "Não foi possível escrever no NVS (%s)", esp_err_to_name(res));
    }
    nvs_commit(particao_padrao_handle);
    nvs_close(particao_padrao_handle);
}

void write_int32_t_nvs(char * to_open_namespace, char * key, int32_t * value) {
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;

    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READWRITE, &particao_padrao_handle);
    
    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    esp_err_t res = nvs_set_i32(particao_padrao_handle, key, *(value));
    if(res != ESP_OK)
    {
        ESP_LOGE("NVS", "Não foi possível escrever no NVS (%s)", esp_err_to_name(res));
    }
    nvs_commit(particao_padrao_handle);
    nvs_close(particao_padrao_handle);
}

void write_uint64_t_nvs(char * to_open_namespace, char * key, uint64_t * value) {
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;

    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READWRITE, &particao_padrao_handle);
    
    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    esp_err_t res = nvs_set_u64(particao_padrao_handle, key, *(value));
    if(res != ESP_OK)
    {
        ESP_LOGE("NVS", "Não foi possível escrever no NVS (%s)", esp_err_to_name(res));
    }
    nvs_commit(particao_padrao_handle);
    nvs_close(particao_padrao_handle);
}

void write_int64_t_nvs(char * to_open_namespace, char * key, int64_t * value) {
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;

    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READWRITE, &particao_padrao_handle);
    
    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    esp_err_t res = nvs_set_i64(particao_padrao_handle, key, *(value));
    if(res != ESP_OK)
    {
        ESP_LOGE("NVS", "Não foi possível escrever no NVS (%s)", esp_err_to_name(res));
    }
    nvs_commit(particao_padrao_handle);
    nvs_close(particao_padrao_handle);
}

void write_string_nvs(char * to_open_namespace, char * key, char * value) {
    ESP_ERROR_CHECK(nvs_flash_init_partition(PARTITION_NAME));

    nvs_handle particao_padrao_handle;

    esp_err_t res_nvs = nvs_open_from_partition(PARTITION_NAME, to_open_namespace, NVS_READWRITE, &particao_padrao_handle);
    
    if(res_nvs == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE("NVS", "Namespace: %s, não encontrado", to_open_namespace);
    }
    esp_err_t res = nvs_set_str(particao_padrao_handle, key, value);
    if(res != ESP_OK)
    {
        ESP_LOGE("NVS", "Não foi possível escrever no NVS (%s)", esp_err_to_name(res));
    }
    nvs_commit(particao_padrao_handle);
    nvs_close(particao_padrao_handle);
}
