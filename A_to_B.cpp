#include <stdio.h>

int main()
{
    int a; int b; 
    scanf_s("%d" "%d", &a, &b); 
    int nbr_of_ops = 0; 
    while (a != b) {
        if (a > b)
        {
            if (a % 2 == 0) {
                a = a / 2;
                nbr_of_ops += 1;
            }
            else {
                a += 1;
                nbr_of_ops += 1;
            }
        }
        if (a < b)
        {
            nbr_of_ops += (b-a);
            break; 
        }
    }

    char buffer[500];
    sprintf_s(buffer, "%d", nbr_of_ops);
    printf_s("%s", buffer);

}
