#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libpnmio/src/pnmio.h"

int width=0, height=0;
int img_colors = 3, img_type;
FILE *imgin_file, *imgout_file;
int *img_data = NULL;
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
}

void save_output_file(const char* filename)
{
    if ((imgout_file = fopen(filename, "w")) == NULL) 
    {
        fprintf(stderr, "Error: Can't create the specified output file.\n");
        exit(1);
    } 

    write_ppm_file(imgout_file, img_data, width, height, 1, 1, img_colors, enable_ascii);
}

/*
 * Function adds given value in range [-127, 127] to choosen channel of every pixel in img data matrix.
 * 
 * which_channel = (R = 1, G = 2, B = 3)
 */
void add_to_channel(int* img_data, int width, int height, int which_channel, int value)
{
    for (int i = which_channel - 1; i < width * height * 3; i += 3)
    {
        img_data[i] += value;
    }
}


int main(int argc, char **argv)
{
    if (argc == 4)
    {
        char* filename = argv[1];
        int channel = 0;
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
            fprintf(stderr, "Error: Allowed channels are R, G and B.\n");
            exit(1);
        }
        
        load_img(filename);
        add_to_channel(img_data, width, height, channel, atoi(argv[3]));

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
    }
    else
    {
        printf("Usage: ./img_process <file_path> <channel> <value>\n");
        printf("Example: ./img_process tests/img.ppm R 42\n\n");
    }

    return 0;
}
