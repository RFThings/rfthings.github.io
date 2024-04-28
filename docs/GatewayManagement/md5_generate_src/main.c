#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <openssl/md5.h>

typedef struct
{
    char *gwEUI;
    char *pathToFile;
    char *url;
    char output_md5[33];
} gateway_info;

const char *output_index_file = "./index.tmp.txt";
const char *header = "# [Gateway EUI] [Patch MD5] [URL to the update]\n";
gateway_info gateway_list[] = {
    {gwEUI : "7276ff000f061f15", pathToFile : "./json_config/kerlink_061f15_as923_2.json", url : "https://rfthings.github.io/GatewayManagement/json_config/kerlink_061f15_as923_2.json", output_md5 : "00000000000000000000000000000000"},
    {gwEUI : "7276ff000f062d6f", pathToFile : "./json_config/kerlink_062d6f_as923_2.json", url : "https://rfthings.github.io/GatewayManagement/json_config/kerlink_062d6f_as923_2.json", output_md5 : "00000000000000000000000000000000"},
    {gwEUI : "7276ff000f062d65", pathToFile : "./json_config/kerlink_062d65_as923_2.json", url : "https://rfthings.github.io/GatewayManagement/json_config/kerlink_062d65_as923_2.json", output_md5 : "00000000000000000000000000000000"},
    {gwEUI : "7276ff000f062cf3", pathToFile : "./json_config/kerlink_062cf3_as923_2.json", url : "https://rfthings.github.io/GatewayManagement/json_config/kerlink_062cf3_as923_2.json", output_md5 : "00000000000000000000000000000000"},
    {gwEUI : "7276ff000f062cf2", pathToFile : "./json_config/kerlink_062cf2_as923_2.json", url : "https://rfthings.github.io/GatewayManagement/json_config/kerlink_062cf2_as923_2.json", output_md5 : "00000000000000000000000000000000"},
};

// ===== Global variable =====
// ===========================

int conv_to_char(unsigned int num, char *output)
{
    if (num < 10)
    {
        *output = (char)num + '0';
    }
    else if (num < 16)
    {
        *output = (char)num - 10 + 'a';
    }
    else
    {
        return -1; // Wrong input
    }

    return 0;
}

int get_md5(char *filename, char *output)
{
    unsigned char c[MD5_DIGEST_LENGTH];
    int i;
    FILE *inFile = fopen(filename, "rb");
    MD5_CTX mdContext;
    int bytes;
    unsigned char data[1024];

    if (inFile == NULL)
    {
        return -1; // Input file can't be opened
    }

    MD5_Init(&mdContext);
    while ((bytes = fread(data, 1, 1024, inFile)) != 0)
        MD5_Update(&mdContext, data, bytes);
    MD5_Final(c, &mdContext);

    memset(output, 0, 33);
    for (int i = 0; i < 16; i++)
    {
        conv_to_char((c[i] >> 4) & 0x0f, (&output[i * 2]));
        conv_to_char(c[i] & 0x0f, (&output[i * 2 + 1]));
    }

    fclose(inFile);
    return 0;
}

int main_app(void)
{
    #define FILE_WRITING_BUFFER_SIZE 1024
    char file_writing_buffer[FILE_WRITING_BUFFER_SIZE];

    int gateway_list_size = sizeof(gateway_list) / sizeof(gateway_list[0]);

    // Open file
    int fd = open(output_index_file, O_CREAT | O_WRONLY);
    if (fd == -1)
    {
        printf("ERROR: Cannot open output file\n");
        return -1;
    }

    // Write header
    write(fd, header, strlen(header));

    for (int i = 0; i < gateway_list_size; i++)
    {
        if (get_md5(gateway_list[i].pathToFile, gateway_list[i].output_md5) == 0)
        {
            printf("[%d] Gateway EUI: %s\n", i, gateway_list[i].gwEUI);
            printf("[%d] Path to File: %s\n", i, gateway_list[i].pathToFile);
            printf("[%d] URL: %s\n", i, gateway_list[i].url);
            printf("[%d] Calculated MD5: %s\n", i, gateway_list[i].output_md5);
            printf("\n\n");
        }
        else
        {
            printf("[%d] Error: Cannot open file %s\n", i, gateway_list[i].pathToFile);
            printf("\n\n");
        }

        memset(file_writing_buffer, 0, FILE_WRITING_BUFFER_SIZE);
        snprintf(file_writing_buffer, FILE_WRITING_BUFFER_SIZE, "%s %s %s\n", gateway_list[i].gwEUI, gateway_list[i].output_md5, gateway_list[i].url);
        write(fd, file_writing_buffer, strlen(file_writing_buffer));
    }

    close(fd);

    return 0;
}

int main(int argc, char **argv)
{
    printf("%d\n", argc);

    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    switch (argc)
    {
    default:
        break;
    case 1:
        return main_app();
        break;
    }

    return 0;
}
