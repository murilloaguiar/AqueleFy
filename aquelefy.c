#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX 30

void register_music();
void show_musics();

typedef struct song{
    int ID;
    char music_name[80];
    char music_artist[80];
    char music_style[80];
    int song_duration;
    //char registration_data;

}Song;

int main(){
    setlocale(LC_ALL,"Portuguese");
    int option; 

    scanf("%d%*c", &option);
    switch (option)
    {
    case 1:
        register_music();
        break;
    case 2:
        show_musics();
        break;

    default:
        break;
    }


    //printf("\nDigite enter para sair");
    //getchar();
    return 0;

}

void register_music(){
    FILE *archive;
    int number_recordes;

    Song song;

    /*a+ abre o arquivo para leitura e para adicionar novos caracteres. Se não existe o arquivo é criado. Se existe ele é aberto para adição de caracteres no fim*/
    archive = fopen("songs","a+b");
    if(archive==NULL){
        printf("\nErro ao abrir o arquivo");
    }else{
        do{
            printf("\nDigite a quantidade de músicas que deseja cadastrar");
            //lendo e limpando o buffer
            scanf("%d%*c", &number_recordes);
        }while(number_recordes > MAX || number_recordes <= 0); 

        for (int i = 0; i < number_recordes; i++){
            printf("\nCADASTRO DA %d MÚSICA", i+1);

            song.ID = i;

            printf("\nNome da música: ");
            fgets(song.music_name,80, stdin);
            song.music_name[strcspn(song.music_name,"\n")] = '\0'; 

            printf("\nNome do artista/banda: ");
            fgets(song.music_artist,80, stdin);
            song.music_artist[strcspn(song.music_artist,"\n")] = '\0'; 

            printf("\nEstilo da música: ");
            fgets(song.music_style,80, stdin);
            song.music_style[strcspn(song.music_style,"\n")] = '\0'; 

            printf("\nTempo da música em segundos: ");
            scanf("%d%*c", &song.song_duration);

            fwrite(&song, sizeof(Song), 1, archive);

            if(ferror(archive)){
                printf("\n%s não gravada!",song.music_name);
            }else{
                 printf("\n%s gravada com sucesso!",song.music_name);
            }

        }
        
        if(!fclose(archive)){
            printf("\nTudo certo");
        }else{
            printf("\nAlgo de errado aconteceu ao fechar o arquivo");
        }

        

    }
}

void show_musics(){
    FILE *archive;
    Song song;
    int control; 
    
    archive = fopen("songs","a+b");
    if(archive==NULL){
        printf("Não foi possível recuperar músicas");
    }else{ 
        while(!feof(archive)){
            control = fread(&song, sizeof(Song), 1, archive);
            
            if (ferror(archive)){
                printf("\n Erro ao mostrar musicas");
            }else{
                if(control != 0){
                    printf("\n%s", song.music_name);
                    printf("\n%s", song.music_artist);
                    printf("\n%s", song.music_style);
                    printf("\n%d", song.song_duration);
                }
            }
        }
    }

}