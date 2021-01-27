# ARMImageProcessing
Simple PPM images processing implemented in ARM assembly. Provides interface for adding given value to all pixels of the image. 

## Structure

Repository consists of:
* `img.s` - file with defintion of function `add_to_channel`
* `main.c` - file consists of a program which tests the `add_to_channel` function
* `Makefile`
* `tests` - directory with images for testing purposes

## Used library
* libpnmio 

## Dependencies
* gcc
* as

## Usage
```bash
make
./img_process tests/img.ppm R 42
```
Run parameters should contain path to appropriate image file, name of channel in image (R, G or B) and value that should be added to the one existing in each pixel. Value should be in range [-127, 127]. 

Testing program loads file, runs the image processing function and saves the output file to the same directory with the same name (but with 'Y' in prefix).
