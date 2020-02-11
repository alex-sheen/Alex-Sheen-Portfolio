#include <stdio.h>
#include <stdlib.h>
#include "hw4_provided.h"
#include "hw4.h"

int main()
{
char checkboard[] = "checkerboard.png";
char happyface[] = "happyface.png";
char uchicago[] = "uchicago.png";
char horizstripes[] = "horiz_stripes.png";

char checkface_e[] = "checkface_encoded.png";
char checkhoriz_e[] = "checkhoriz_encoded.png";
char happyuchicago_e[] = "happyuchicago_encoded.png";
char horizcheck_e[] = "horizcheck_encoded.png";
char uchicagohappy_e[] = "uchicagohappy_encoded.png";

char checkhoriz_d[] = "checkhoriz_decoded.png";
char happyuchicago_d[] = "happyuchicago_decoded.png";
char horizcheck_d[] = "horizcheck_decoded.png";
char uchicagohappy_d[] = "uchicagohappy_decoded.png";

printf("----- hw4 testing start -----\n");
printf("testing encoding two images of different dimensions\n");
encode(checkboard,happyface,checkface_e);
printf("testing encoding\n");
encode(checkboard,horizstripes,checkhoriz_e);
encode(happyface,uchicago,happyuchicago_e);
encode(horizstripes,checkboard,horizcheck_e);
encode(uchicago,happyface,uchicagohappy_e);
printf("testing decoding\n");
decode(checkhoriz_e,checkhoriz_d);
decode(happyuchicago_e,happyuchicago_d);
decode(horizcheck_e,horizcheck_d);
decode(uchicagohappy_e,uchicagohappy_d);
printf("----- hw4 testing finish -----\n");
}

