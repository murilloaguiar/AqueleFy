#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX 30


typedef struct Song{
    int ID;
    char music_name[80];
    char music_artist[80];
    char music_style[80];
    int song_duration;
    char registration_data;

}Song;

int main(){
    setlocale(LC_ALL,"Portuguese");

    






    printf("\nDigite enter para sair");
    getchar();
    return 0;

}