#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
    //check that only 1 argument was taken on the command line
    if (argc != 2)
    {
        printf("Usage: ./recover [filename]\n");
        return 1;
    }
    
    //check if file can be opened
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("could not open file \n");
        return 1;
    }
    
    //track # of jpgs found
    int jpg_counter = 0;
    
    //filename
    FILE *img = NULL;
    
    //no jpgs found yet
    int jpg_tracker = 0;
    
    //look for first jpg header
    unsigned char buffer[BUFFER_SIZE];
    
    
    while (fread(buffer, BUFFER_SIZE, 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //found start of new pic, close old one
            if (jpg_tracker == 1)
            {
                fclose(img);
            }
            else
            {
                //jpg found, give ok to open
                jpg_tracker = 1;
            }
            
            //create filename to hole ###.jpg
            char filename[8];
            //format filename
            sprintf(filename, "%03d.jpg", jpg_counter);
            //open a file w/new name
            img = fopen(filename, "a");
            
            //increase jpg_counter
            jpg_counter++;
        }
        
        //if a jpg header is found, write to the new file
        if (jpg_tracker == 1)
        {
            fwrite(&buffer, BUFFER_SIZE, 1, img);
        }
        
    }
    
    //return memory
    fclose(file);
    fclose(img);
    
    return 0;
}