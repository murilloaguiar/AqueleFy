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
int record_counter();
int random();
void clean_stdin();
void clear();

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
    do{
    clear();
    printf("---------MENU------------\n");
    printf("1-Inserir musicas\n"
          "2-Mostrar musicas\n"
          "3-Procurar musicas\n"
          "4-Tempo total das musicas\n"
          "5-Maior e menor musicas\n"
          "0-Encerrar programa\n");
    
        printf("\nDigite sua escolha: ");
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
        case 0:
            exit(1);
            break;
        default:
            printf("digite um opção válida");
            break;
        }
    }while(option != 0);
    

    //printf("\nDigite enter para sair");
    //getchar();
    return 0;

}

void register_music(){
    FILE *archive;
    int number_records;
    int records = record_counter();
    Song song;

    /*a+ abre o arquivo para leitura e para adicionar novos caracteres. Se não existe o arquivo é criado. Se existe ele é aberto para adição de caracteres no fim*/
    archive = fopen("songs","a+b");
    if(archive==NULL){
        printf("\nErro ao abrir o arquivo");
    }else{
        do{
            printf("\nDigite a quantidade de músicas que deseja cadastrar: ");
            //lendo e limpando o buffer
            scanf("%d%*c", &number_records);
           if(MAX-(number_records+records)<0){
                printf("\nVocê não pode gravar %d musicas, pois ultrapassaria o limite máximo", number_records);
                printf("\nVocê pode gravar mais %d musicas", MAX-records);
            }
            
        }while(number_records <= 0 || number_records+records>MAX); 

        for (int i = 0; i < number_records; i++){
            printf("\nCADASTRO DA %d MÚSICA", i+1);

            song.ID = random();
            
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
            printf("\nTudo certo.Você tem %d espaços", MAX-(record_counter()));
            printf("\nPressione Enter para voltar");
            getchar();
        }else{
            printf("\nAlgo de errado aconteceu ao fechar o arquivo");
        }
    }
}

void show_musics(){
    FILE *archive;
    Song song; 
    
    archive = fopen("songs","a+b");
    if(archive==NULL){
        printf("Não foi possível recuperar músicas");
    }else{
        if((record_counter())==0){
            printf("\nNão existem músicas cadastradas\n");
            printf("\nPressione Enter para voltar");
            getchar();
            return; 
        }

        while((fread(&song, sizeof(Song), 1, archive))==1){
           
            printf("\nID: %d", song.ID);
            printf("\nNOME: %s", song.music_name);
            printf("\nARTISTA/BANDA: %s", song.music_artist);
            printf("\nESTILO: %s", song.music_style);
            printf("\nDURAÇÃO: %ds\n", song.song_duration);
            
        }
    }

    if(fclose(archive)){
        printf("\nAlgo de errado aconteceu ao fechar o arquivo");
    }

    printf("\nPressione Enter para voltar");
    getchar();

}

void search_musics(){
    FILE *archive;
    int ID, control;
    Song song;

    archive = fopen("songs","a+b");
    if (archive==NULL){
        printf("\nErro ao encontrar musicas");
    }else{
        printf("\nQual ID da musica que deseja: ");
        scanf("%d%*c", &ID);

        while(!feof(archive)){
            control = fread(&song, sizeof(Song), 1, archive);
            if (ferror(archive)){
                printf("\nErro ao acessar musicas");
            }else{
                if(control != 0){
                    if (song.ID==ID){
                        printf("\n%s", song.music_name);
                        printf("\n%s", song.music_artist);
                        printf("\n%s", song.music_style);
                        printf("\n%d\n", song.song_duration);
                        printf("Pressione Enter para voltar");
                        getchar();
                        return;
                    }
                }else{
                    printf("\n Não existe musica com esse ID\n");
                }
                
            }
            
        }
    }

    if(fclose(archive)){
        printf("\nErro ao fechar arquivo");
    }

    printf("Pressione Enter para voltar");
    getchar();
}

void total_time_songs(){
    FILE *archive;
    Song song;
    int total_time = 0, count = 0;

    archive = fopen("songs","a+b");
    if (archive == NULL){
        printf("\nErro ao recuperar musicas");
    }else{
        if((record_counter())==0){
            printf("\nNão existem músicas cadastradas\n");
            printf("\nPressione Enter para voltar");
            getchar(); 
            return;
        }

        while ((fread(&song, sizeof(Song), 1, archive))==1){
            total_time+=song.song_duration;
        } 
    }

    printf("\nTempo total das musicas é: %ds", total_time);

    if(!fclose(archive)){
        printf("\nPressione Enter para voltar");
        getchar();
    }else{
        printf("\nErro ao fechar arquivo");
    }
    
}

void longer_time(){
    FILE *archive;
    char name_smaller[TAMANHO], name_larger[TAMANHO];
    Song song, small, large;

    archive = fopen("songs","a+b");
    if(archive == NULL){
        printf("\nErro ao recuperar músicas");
    }else{

        if((record_counter())==0){
            printf("\nNão existem músicas cadastradas\n");
            printf("\nPressione Enter para voltar");
            getchar(); 
            return;
        }

        fread(&song, sizeof(Song), 1, archive);
        small = song;
        large = song;
        //rewind(archive);

        while((fread(&song, sizeof(Song), 1, archive))==1){
            if(ferror(archive)){
                printf("\nErro ao acessar a música");
            }else{
                if(song.song_duration>large.song_duration){
                    large = song;
                }else if (song.song_duration<small.song_duration){
                    small = song;
                }         
            }
        }
    }

    printf("\n%s tem a menor duração %ds",small.music_name,small.song_duration);
    printf("\n%s tem a maior duração %ds",large.music_name,large.song_duration);

    if(fclose(archive)){
        printf("\nAlgo de errado aconteceu ao fechar o arquivo");
    }

    printf("\nPressione Enter para voltar");
    getchar();

    
}

int record_counter(){
    int records = 0;
    FILE *archive;
    Song song;

    archive = fopen("songs","a+b");
    if(archive==NULL){
        printf("\nErro ao recuperar musicas");
    }else{
        while((fread(&song, sizeof(Song),1,archive))==1){
                records++;  
        } 
    }

    if(fclose(archive)){
        printf("\nAlgo de errado aconteceu ao fechar o arquivo");
    }
    return records;
}
    

int random(){
    int random = 0;

    srand(time(NULL));
    random = rand()%1000;

    return random;
}


void clean_stdin(){
  int c;
  do{
    c = getchar();
  }while (c != '\n' && c != EOF);
}

void clear(){
  #if defined(__linux__)||defined(__unix__)
    system("clear");
  #endif

  #if defined(__WIN32)||defined(__WIN64)
    system("cls");
  #endif
}