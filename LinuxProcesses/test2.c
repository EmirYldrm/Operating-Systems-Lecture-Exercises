/**
 *  KTUN - Bilgisayar Mühendisliği
 *           02.11.2022
 *         Emir  YILDIRIM
 */

// Surekli calisan program ornegi.

#include <stdio.h>
#include <unistd.h>

int main(void)
{
        fflush(stdout);
        printf("\n[T2] test2 programiyim ve sürekli çalişiyorum... pid = %d\n", getpid());
        int d=0;

        while(1) {
                printf("\n[T2] %d. saniye",++d);
                fflush(stdout);
                sleep(1);
        }
}