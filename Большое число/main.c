#include <stdio.h>
#include "my_string.h"
#include <stdio.h>
#include "big_number.h"

int main()
{
    char str[] = "6133123131313";
    char str2[] = "-1133131";



    BigNumber* bn1_ = CreateBN(str);
    if (bn1_ == NULL)
        printf("bn == NULL!\n");

    BigNumber* bn2_ = CreateBN(str2);
    if (bn1_ == NULL)
        printf("bn == NULL!\n");



    PrintBN(bn1_);
    PrintBN(bn2_);
    SubBN(bn1_, bn2_);
    free(bn1_);
    free(bn2_);
    return 0;
}