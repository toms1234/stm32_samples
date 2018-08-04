

#include <stdio.h>


unsigned int raw[16]=
{
    (0<<7)|(1<<6)|(1<<5)|(1<<4)|(0<<3)|(1<<2)|(1<<1)|(1<<0),//0
    (0<<7)|(0<<6)|(0<<5)|(1<<4)|(0<<3)|(1<<2)|(0<<1)|(0<<0),//1
    (1<<7)|(0<<6)|(1<<5)|(1<<4)|(0<<3)|(0<<2)|(1<<1)|(1<<0),//2
    (1<<7)|(0<<6)|(1<<5)|(1<<4)|(0<<3)|(1<<2)|(1<<1)|(0<<0),//3
    (1<<7)|(1<<6)|(0<<5)|(1<<4)|(0<<3)|(1<<2)|(0<<1)|(0<<0),//4
    (1<<7)|(1<<6)|(1<<5)|(0<<4)|(0<<3)|(1<<2)|(1<<1)|(0<<0),//5
    (1<<7)|(1<<6)|(1<<5)|(0<<4)|(0<<3)|(1<<2)|(1<<1)|(1<<0),//6
    (0<<7)|(0<<6)|(1<<5)|(1<<4)|(0<<3)|(1<<2)|(0<<1)|(0<<0),//7
    (1<<7)|(1<<6)|(1<<5)|(1<<4)|(0<<3)|(1<<2)|(1<<1)|(1<<0),//8
    (1<<7)|(1<<6)|(1<<5)|(1<<4)|(0<<3)|(1<<2)|(0<<1)|(0<<0),//9

    (0<<7)|(0<<6)|(0<<5)|(0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0),//x
    (0<<7)|(0<<6)|(0<<5)|(0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0),//x
    (0<<7)|(0<<6)|(0<<5)|(0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0),//x
    (0<<7)|(0<<6)|(0<<5)|(0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0),//x
    (0<<7)|(0<<6)|(0<<5)|(0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0),//x
    (0<<7)|(0<<6)|(0<<5)|(0<<4)|(0<<3)|(0<<2)|(0<<1)|(0<<0),//x
};




int main ( void )
{
    unsigned int ra;

    printf("static const unsigned int seven[16]=\n");
    printf("{\n");
    for(ra=0;ra<16;ra++)
    {



        printf("0x%08X,\n",raw[ra]|    (((~raw[ra])&0xFF)<<16)  );
    }
    printf("};\n");
    return(0);
}
