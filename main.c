// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020, STMicroelectronics - All Rights Reserved
 * Author(s): Raphaël GALLAIS-POU <raphael.gallais-pou@st.com> for STMicroelectronics.
 */

#include<stdio.h>
#include<stdlib.h>

#include "lvds.h"

int LVDS_Decode(int reg, int *bitmap)
{
/*        int bitmap[7];*/

        if (reg > 0xFFFFFFFF || reg < 0x0)
                return 1;

        printf("%08x\n", (reg << BIT_0_Pos));
        printf("%08x\n", (BIT_Mask << BIT_0_Pos));
        printf("%08x\n", ((reg << BIT_0_Pos) | (BIT_Mask << BIT_0_Pos)));
        printf("%08x\n", (((reg << BIT_0_Pos) | (BIT_Mask << BIT_0_Pos)) >> BIT_0_Pos));

        bitmap[0] = (reg << BIT_0_Pos) | (BIT_Mask << BIT_0_Pos);
        printf("OK\n");
        bitmap[1] = (reg << BIT_1_Pos) | (BIT_Mask << BIT_1_Pos);
        bitmap[2] = (reg << BIT_2_Pos) | (BIT_Mask << BIT_2_Pos);
        bitmap[3] = (reg << BIT_3_Pos) | (BIT_Mask << BIT_3_Pos);
        bitmap[4] = (reg << BIT_4_Pos) | (BIT_Mask << BIT_4_Pos);
        bitmap[5] = (reg << BIT_5_Pos) | (BIT_Mask << BIT_5_Pos);
        bitmap[6] = (reg << BIT_6_Pos) | (BIT_Mask << BIT_6_Pos);

        return 0;
}

int main(int argc, char **argv)
{
	int bitmap[7] = {0};

/*        if (argc != 2)*/
/*                return 1;*/

/*        int reg = (int)strtol(argv[1], NULL, HEX_BASE);*/
/*        printf("%d\n", reg);*/

        LVDS_Decode(0x00029062, &bitmap);

        printf("%05x %05x %05x %05x %05x %05x %05x\n",
               bitmap[0], bitmap[1], bitmap[2], bitmap[3], bitmap[4], bitmap[5], bitmap[6]);

	return 0;
}
