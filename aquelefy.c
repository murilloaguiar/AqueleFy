#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX 30
#define TAMANHO 80

void register_music();
void show_musics();
void search_music();
void total_time_songs();
void longer_time();
void shorter_time();


typedef struct song{
    int ID;
    char music_name[TAMANHO];
    char music_artist[TAMANHO];
    char music_style[TAMANHO];
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
    case 3:
        search_musics();
        break;
    case 4:
        total_time_songs();
        break;
    case 5:
        longer_time();
        break;
    case 6:
        
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
            fgets(song.music_name,TAMANHO, stdin);
            song.music_name[strcspn(song.music_name,"\n")] = '\0';
            //limpar o buffer de entrada e não deixar a string passar da quantidade de caracteres
            if(strcspn(song.music_name, "\0") == (TAMANHO-1)){
                clean_stdin();
            }

            printf("\nNome do artista/banda: ");
            fgets(song.music_artist,TAMANHO, stdin);
            song.music_artist[strcspn(song.music_artist,"\n")] = '\0';
            if(strcspn(song.music_artist, "\0") == (TAMANHO-1)){
                clean_stdin();
            } 

            printf("\nEstilo da música: ");
            fgets(song.music_style,TAMANHO, stdin);
            song.music_style[strcspn(song.music_style,"\n")] = '\0'; 
            if(strcspn(song.music_style, "\0") == (TAMANHO-1)){
                clean_stdin();
            }

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
                //impedir de mostrar o ultimo elemento duas vezes
                if(control != 0){
                    printf("\n%s", song.music_name);
                    printf("\n%s", song.music_artist);
                    printf("\n%s", song.music_style);
                    printf("\n%d\n", song.song_duration);
                }
            }
        }
    }

    if(!fclose(archive)){
            printf("\nTudo certo");
    }else{
        printf("\nAlgo de errado aconteceu ao fechar o arquivo");
    }

}

void search_musics(){
    FILE *archive;
    int ID;
    Song song;

    archive = fopen("songs","a+b");
    if (archive==NULL){
        printf("\nErro ao encontrar musicas");
    }else{
        printf("\nQual ID da musica que deseja: ");
        scanf("%d%*c", &ID);

        while(!feof(archive)){
            fread(&song, sizeof(Song), 1, archive);

            if (ferror(archive)){
                printf("\nErro ao acessar musicas");
            }else{
                if (song.ID==ID){
                    printf("\n%s", song.music_name);
                    printf("\n%s", song.music_artist);
                    printf("\n%s", song.music_style);
                    printf("\n%d\n", song.song_duration);
                    return;
                }
                
            }
            
        }
    }

    if(!fclose(archive)){
        printf("\nTudo certo");
    }else{
        printf("\nAlgo de errado aconteceu ao fechar o arquivo");
    }
}

void total_time_songs(){
    FILE *archive;
    Song song;
    int total_time = 0;
    int control;

    archive = fopen("songs","a+b");
    if (archive == NULL){
        printf("\nErro ao recuperar musicas");
    }else{
        while (!feof(archive)){
            control = fread(&song, sizeof(Song), 1, archive);

            if(ferror(archive)){
                printf("\nErro ao acessar as musicas");
            }else{
                //impedir de somar o valor da ultima musica duas vezes
                if(control != 0){
                    total_time+=song.song_duration;
                } 
            }
        } 
    }

    printf("\nTempo total das musicas é: %d", total_time);

    if(!fclose(archive)){
        printf("\nTudo certo");
    }else{
        printf("\nAlgo de errado aconteceu ao fechar o arquivo");
    }
    
}

void longer_time(){
    FILE *archive;
    //int smaller = 0, larger = 0;
    int control;
    char name_smaller[TAMANHO], name_larger[TAMANHO];
    Song song, small, large;

    archive = fopen("songs","a+b");
    if(archive == NULL){
        printf("\nErro ao recuperar músicas");
    }else{
        fread(&song, sizeof(Song), 1, archive);
        small = song;
        large = song;
        //rewind(archive);

        while(!feof(archive)){
            control = fread(&song, sizeof(Song), 1, archive);
            if(ferror(archive)){
                printf("\nErro ao acessar a música");
            }else{
                if(control != 0){
                    if(song.song_duration>large.song_duration){
                        large = song;
                    }else if (song.song_duration<small.song_duration){
                        small = song;
                    }         
                }
            }
        }
    }

    printf("\n%s tem a menor duração %d",small.music_name,small.song_duration);
    printf("\n%s tem a maior duração %d",large.music_name,large.song_duration);

    if(!fclose(archive)){
        printf("\nTudo certo");
    }else{
        printf("\nAlgo de errado aconteceu ao fechar o arquivo");
    }

    
}


void clean_stdin(){
  int c;
  do{
    c = getchar();
  }while (c != '\n' && c != EOF);
}

void scopy(char *t, char *s){
    int i = 0;

    while((*t++ = *s++)!='\0');
}