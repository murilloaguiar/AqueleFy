#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <windows.h> //função Sleep
#define MAX 5

struct musica
{
	int id;
	int data;
	int seg;
    char nome[80];
    char artista[80];
    char estilo[80];
}music[MAX];

void entrada(){
	int slot,id[30];
    register int t,i;
	system("cls");

	slot = find_free();
	if (slot==-1){
		printf("Lista cheia\n");
		Sleep(1500);
		return;
	}


	srand((unsigned)time(NULL));
	music[slot].id = rand() % 1000;

	setbuf(stdin,NULL);
	printf("Digite o nome da música: \n");
	fgets(music[slot].nome,sizeof(music[slot].nome),stdin);

	setbuf(stdin,NULL);
	printf("Digite o artista da música: \n");
	fgets(music[slot].artista,sizeof(music[slot].artista),stdin);

	setbuf(stdin,NULL);
	printf("Digite o estilo da música: \n");
	fgets(music[slot].estilo,sizeof(music[slot].estilo),stdin);

	printf("Digite a data do cadastro: \n" );
	scanf("%d",&music[slot].data);

	printf("Digite a duração da música em segundos: \n" );
	scanf("%d",&music[slot].seg);

}

int find_free (void){
	register int t;
	for (t=0;music[t].nome[0] && t<=MAX; t++);

	if (t==MAX){
		return -1;
	}
	return t;
}


void list(){
	register int t;

	for(t=0;t<MAX;t++){
		if (music[t].nome[0]){
			printf("\nNome: %s", music[t].nome);
			printf("ID: %d\n", music[t].id);
			printf("Artista: %s", music[t].artista);
			printf("Estilo: %s", music[t].estilo);
			printf("Segundos: %d\n", music[t].seg);
			printf("Data cadastro: %d\n", music[t].data);

		}
	}
}

int calc_seg(){
	int i,total=0;
	for(i=0;i<MAX;i++){
		total+=music[i].seg;
	}
	return total;

}

void search (int id){
    register int t;
    int cont=0,ref=0;
    system("cls");
    ref=find_free();
    for (t=0;music[t].nome[0] && t<=MAX; t++){
        if(id==music[t].id){
            printf("Música encontrada! Informações sobre ela: ");
            printf("\nNome: %s", music[t].nome);
			printf("ID: %d\n", music[t].id);
			printf("Artista: %s", music[t].artista);
			printf("Estilo: %s", music[t].estilo);
			printf("Segundos: %d\n", music[t].seg);
			printf("Data cadastro: %d\n", music[t].data);
        }else{
           cont++;
        }
    }
    if(cont==t){
        printf("Música não existe. \n");
    }
}

void seg_maior(){
    int t;
    int maior=0,aux=0,aux1=0,menor=0;
    system("cls");

    for (t=0;music[t].nome[0] && t<MAX; t++){
        if (music[t].seg>maior){
            maior=music[t].seg;
            aux=t;
        }
        menor=music[0].seg;
        if (music[t].seg<maior){
            menor=music[t].seg;
            aux1=t;
        }
    }
    printf("A música com maior duração é %s com %d segundos.\n", music[aux].nome,maior);
    printf("A música com menor duração é %s com %d segundos.\n", music[aux1].nome,menor);
}

int main(){
	int i, num,aux=0, escolha, qtd,srch;
	float total=0;
	//inicializar();
	setlocale(LC_ALL, "Portuguese");

	do{
		printf("-------------------------MENU-------------------------\n");
		printf("1-Cadastro\n"
		   "2-Exibir as músicas cadastradas\n"
		   "3-Pesquisar por ID\n"
		   "4-Tempo total de exbição\n"
		   "5-Mostrar música com maior e menor tempo de execução\n"
		   "6-Encerrar programa\n");
        printf("-------------------------MENU-------------------------\n");

		printf("Opcão: ");
		scanf("%d", &escolha);

		switch (escolha){
			case 1:
				printf("Digite quantas músicas deseja cadastar\n");
				scanf("%d",&num);
				aux+=num;
				if (aux<=MAX){
                    for(i=0;i<num;i++){
                        entrada();
                    }
                    qtd=find_free();
                    if (qtd!=-1){
                        printf("Você têm %d músicas gravadas, você ainda pode cadastar %d músicas.\n",aux,MAX-qtd);
                        Sleep(3500);
                    }
				}else{
                    printf("Você não pode cadastar mais %d musicas porque execede a capacidade!",num);
                    Sleep(3500);
                    aux=num-aux;
				}
				break;
			case 2:
				list();
				system("pause");
				break;
			case 3:
			    printf("Digite um ID para a procura: ");
			    scanf("%d",&srch);
			    search(srch);
			    system("pause");
				break;
			case 4:
				total=calc_seg();
				printf("Tempo em minutos de todas as músicas: %.2f\n",total/60);
				system("pause");
				break;
            case 5:
                seg_maior();
                system("pause");
                break;
            case 6:
                printf("Encerrando programa...\n");
                Sleep(1500);
                break;
			default:
				printf("Digite uma opção válida\n");
				break;
			}
			system("cls");
	} while (escolha != 6);
	return 0;
	system("pause");

}
