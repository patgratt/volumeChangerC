// Modifies the volume of an audio file
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    // needs 4 arguments as follows, if not notify user of correct usage
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open input file to ensure we can read it correctly
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // open output file to ensure that we can write to it correctly
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file

    // declare a variable of type uint8_t, which stores unsigned integers
    // that are 8 bits (1 byte), we know header is 44 bytes
    // so this is an array with a size of 44 bytes
    uint8_t header[HEADER_SIZE];
    // first parameter is a pointer to the location where we'll store
    // recall an array is really just a pointer to its first element so
    // no need for any * or &
    // second parameter is size of each object in bytes
    // 3rd paramter is count of objects (44)
    // 4th parameter is the pointer to the file we want to read
    fread(&header, HEADER_SIZE, 1, input);
    // now write the header to the output file (output is a pointer)
    fwrite(&header, HEADER_SIZE, 1, output);

    // Read samples from input file and write updated data to output file

    // declare a variable that is an array of type int16_t, which stores ints
    // that are 2 bytes in size, which is the size of the samples
    int16_t buffer;

    // while we haven't reached the end of the file
    // read from the input to the buffer, 2 bytes at a time
    // we don't need to shift over to the end of the header, it remembers
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(buffer), 1, output);
    }


    // Close files
    fclose(input);
    fclose(output);
}
