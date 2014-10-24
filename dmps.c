#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "hardware.h"
#include "drive.h"
#include "mbr.h"

static void empty_it()
{
    return;
}

int main(int argc, char **argv)
{
    unsigned int i;
    /*unsigned char buffer[HDA_SECTORSIZE];*/
    
    /* init hardware */
    if(init_hardware("hardware.ini") == 0) {
	    fprintf(stderr, "Error in hardware initialization\n");
	    exit(EXIT_FAILURE);
    }
    
    assert(sizeof(struct mbr_s) <= HDA_SECTORSIZE);

    /* Interreupt handlers */
    for(i=0; i<16; i++)
	    IRQVECTOR[i] = empty_it;

    /* Allows all IT */
    _mask(1);

    /*read_sector(0, 0, buffer);
    
    printf("\n--------------------------------------------------------------------------------\n");
    printf("Secteur 1:\n");
    for(i = 0; i < HDA_SECTORSIZE; i++)
    {
        if(i%8 == 0) {
            printf("\n");
        }
        printf("\t0x%x ",buffer[i]);
    }
    printf("\n");*/
    
    display_mbr();
    
    /*read_sector(0, 0, buffer);
  
    printf("\n--------------------------------------------------------------------------------\n");
    printf("Secteur 1:\n");
    for(i = 0; i < HDA_SECTORSIZE; i++)
    {
        if(i%8 == 0) {
            printf("\n");
        }
        printf("\t0x%x ",buffer[i]);
    }
    printf("\n");*/

    /* and exit! */
    exit(EXIT_SUCCESS);
}
