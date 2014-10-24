#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "mbr.h"
#include "drive.h"

struct mbr_s mbr;

void read_mbr()
{
    unsigned char buffer[HDA_SECTORSIZE];
    int i;
    
    read_sector(0, 0, buffer);
    
    memcpy(&mbr, buffer, sizeof(struct mbr_s));
    
    if(mbr.magic != MAGIC)
    {
        assert(mbr.magic != MAGIC);
        mbr.nb_vols = 0;
        for(i=0; i<NB_VOLS; i++)
        {
            mbr.vols[i].type = BASE;
            mbr.vols[i].nb_sec = 0;
            mbr.vols[i].prem_cyl = 0;
            mbr.vols[i].prem_sec = 0;
            mbr.vols[i].valide = 0;
        }
        mbr.magic = MAGIC;
        write_mbr();
    }
}

void write_mbr()
{
    unsigned char buffer[HDA_SECTORSIZE];
    
    assert(mbr.magic == MAGIC);
    
    memset(buffer, HDA_SECTORSIZE, 0);
    
    memcpy(buffer, &mbr, sizeof(struct mbr_s));
    
    write_sector(0, 0, buffer);
}

void display_mbr()
{
    int i;
    
    read_mbr();
    
    printf("--------------------------------------------------------------------------------\n");
    printf("MBR\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("Nb volumes: %i\n", mbr.nb_vols);
    for(i=0; i<NB_VOLS; i++)
    {
        printf("----------------------------------------\n");
        printf("Volume %i:\n", i+1);
        printf("\tType: %i\n", mbr.vols[i].type);
        printf("\tNbSec: %i\n", mbr.vols[i].nb_sec);
        printf("\tPremCyl: %i\n", mbr.vols[i].prem_cyl);
        printf("\tPremSec: %i\n", mbr.vols[i].prem_sec);
        printf("\tValide: %i\n", mbr.vols[i].valide);
    }
}
