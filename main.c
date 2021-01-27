#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libpnmio/src/pnmio.h"

int width = 0, height = 0;
int img_colors = 3;
FILE* imgin_file;
FILE* imgout_file;
int* img_data = NULL;
char* img_data_byte = NULL;

int enable_ascii = 0;

void load_img(const char* filename)
{
    if ((imgin_file = fopen(filename, "r")) == NULL) 
    {
        fprintf(stderr, "Error: Can't open the specified input file.\n");
        exit(1);
    } 

    read_ppm_header(imgin_file, &width, &height, &img_colors, &enable_ascii);
    img_data = malloc((3 * width * height) * sizeof(int));

    read_ppm_data(imgin_file, img_data, enable_ascii);

    img_data_byte = malloc(width * height * 3);
    for (int i = 0; i < width * height * 3; ++i)
    {
        img_data_byte[i] = (char)img_data[i];
    }
}

void save_output_file(const char* filename)
{
    if ((imgout_file = fopen(filename, "w")) == NULL) 
    {
        fprintf(stderr, "Error: Can't create the specified output file.\n");
        exit(1);
    }

    for (int i = 0; i < width * height * 3; ++i)
    {
        img_data[i] = (int)img_data_byte[i];
    }

    write_ppm_file(imgout_file, img_data, width, height, 1, 1, img_colors, enable_ascii);
}


extern void add_to_channel(char* img_data, int width, int height, int which_channel, signed char value);


int main(int argc, char **argv)
{
    if (argc == 4)
    {
        char* filename = argv[1];
        int channel = 0, value_to_add = atoi(argv[3]);
        if (argv[2][0] == 'R')
        {
            channel = 1;
        }
        else if (argv[2][0] == 'G')
        {
            channel = 2;
        }
        else if (argv[2][0] == 'B')
        {
            channel = 3;
        }
        else
        {
            fprintf(stderr, "Error: R, G and B are the only allowed channels.\n");
            exit(1);
        }

        if (value_to_add < -127 || value_to_add > 127)
        {
            fprintf(stderr, "Error: Value to add should be [-127, 127].\n");
            exit(1);
        }
        
        load_img(filename);
        add_to_channel(img_data_byte, width, height, channel, (signed char)atoi(argv[3]));

        char* filename_without_dir = strrchr(filename, '/');

        if (filename_without_dir == NULL)
            filename_without_dir = filename;
        else
            ++filename_without_dir;

        char* output_filename = malloc(strlen(filename_without_dir) + 2);
        output_filename[0] = 'Y';
        output_filename[1] = '\0';

        strcat(output_filename, filename_without_dir);

        save_output_file(output_filename);
        
        free(output_filename);
        free(img_data);
        free(img_data_byte);
    }
    else
    {
        printf("Usage: ./img_process <file_path> <channel> <value>\n");
        printf("Example: ./img_process tests/img.ppm R 42\n\n");
    }

    return 0;
}
