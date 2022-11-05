/**
 *  KTUN - Bilgisayar Mühendisliği
 *           02.11.2022
 *         Emir  YILDIRIM
 */


// Bu program, kendisine parametre olarak verilen obje (.o) 
// tipindeki programi, parametre olarak verilen sure boyunca 
// calistirir ve sonlandirir.

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>



// olusan childin pid degeri alinacak ve 3 sn den fazla olursa process kill edilecek.
pid_t forkStatus = -1;

// Istenen programi calistirma suresi (default 5sn).
unsigned int killChildInSec = 5;



// Sinyal gonderildigince calisir.
void alarmHandler(int sig);

// Main fonskiyonuna arguman olarak verilen saniye degerini int tipine cevirir.
int toInteger(char *arg, int len);



/**
 * CMD Arguments:
 *   argv[0] = programin ismi
 *   argv[1] = calistirilacak programin dosya yolu
 *   argv[2] = programin kac saniye calistirilacagi
 */
int main(int argc, char *argv[])
{

    if (argc > 1) { // Program arguman ile calistirilirsa

        killChildInSec = toInteger(argv[2], strlen(argv[2]));
        printf("\n[hw1] %dsn boyunca process çaliştirilacak.. %d \n", killChildInSec, getpid());
    }
    else { // Program arguman ile calistirilmazsa

        printf("LUTFEN ARGUMAN GIRINIZ!\n");
        _exit(0);
    }

    // Sinyal'e abone yapiyoruz.
    signal(SIGALRM, (void (*)(int))alarmHandler); // Sinyal geldiginde calisacak fonskiyonu veriyoruz.

    // Arguman olarak verilen programi calistiracak child processi olusturuyoruz.
    forkStatus = fork();

    if (forkStatus == -1) {
        printf("fork edilirken bir problem olustu!\n");
    }

    // Parent process
    if (forkStatus > 0) {

        // Alarm baslatildi.
        alarm(killChildInSec);

        // Istenen sure sonunsa sinyalin gonderilip process'in terminate edilmesini bekle
        wait(NULL);
    }
    
    // Child process
    if (forkStatus == 0) {

        char *args[] = {"test", NULL}; // Calistirilacak programa verilecek argumanlar listesi. NULL ile bitmesi gerekiyor.

        // execv() fonskiyonu, -1 degeri dondururse program caslistirilamadi.
        // execv() fonskiyonu, hicbir deger donmezse dogru calismis olur.
        if (execv(argv[1], args) == -1) {
            printf("\n[hw2] HATA! Verilen program calistirilamadi!\n");
            _exit(0);
        }
    }

    return 0;
}



// Sinyal gonderildigince calisir.
void alarmHandler(int sig)
{
    printf("\n\n[hw1] %dsn sona erdi process kapatiliyor...pid = %d\n", killChildInSec, getpid());
    kill(forkStatus, SIGTERM);
}

// Main fonskiyonuna arguman olarak verilen saniye degerini int tipine cevirir.
int toInteger(char *arg, int len)
{
    int result = 0;

    for (int i = 0; i < len; i++) {
        result = 10 * result + arg[i] - '0';
    }

    return result;
}