#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX 5

int menu_select();
void enter ();
void list();
void delete();
int find_free();
void init_list();
void clear();

struct address{
  char name[30];
  char street[40];
  char city[30];
  char state[15];
  unsigned long int cep;
} endereco[MAX];

int main(void) {

  setlocale(LC_ALL, "Portuguese.Brazil");

  int choice;

  init_list();

  while(1){
    choice = menu_select();
    switch (choice){
      case 1:
        enter();
        break;
      case 2:
        delete();
        break;
      case 3:
        list();
        break;
      case 4:
        exit(1);
        break;
      default:
        exit(1);
    }
  }


  return 0;
}

//inicializa endereço com '\0'
void init_list(){
  int i;
  for(i=0; i<MAX; i++){
    endereco[i].name[0] = '\0';
  }
}

int menu_select(){
  int t;

  clear();
  printf("\n-----------Menu------------\n");
  printf("1 - Inserir um nome \n");
  printf("2 - Excluir um nome \n");
  printf("3 - Listar o arquivo \n");
  printf("4 - Sair \n");

  do{
    printf("\nDigite sua escolha: ");
    //lendo valor e limpando buffer
    scanf("%d%*c", &t);
  }while(t<0 || t>4);

  return t;
}

//entrar com os dados de um endereço
void enter(){
  int slot;

  slot=find_free();

  if(slot==-1){
    printf("\nLista cheia");
    return;
  }

  printf ("\nCADASTRO");
  printf ("\n Digite o nome da pessoa: ");
  fgets(endereco[slot].name,30,stdin);
  endereco[slot].name[strcspn(endereco[slot].name,"\n")] = '\0';

  printf ("\n Digite o nome da rua: ");
  fgets(endereco[slot].street,40,stdin);
  endereco[slot].street[strcspn(endereco[slot].street,"\n")] = '\0';

  printf ("\n Digite o nome da cidade: ");
  fgets(endereco[slot].city,30,stdin);
  endereco[slot].city[strcspn(endereco[slot].city,"\n")] = '\0';

  printf ("\n Digite o nome do estado: ");
  fgets(endereco[slot].state,15,stdin);
  endereco[slot].state[strcspn(endereco[slot].state,"\n")] = '\0';

  printf ("\n Digite o CEP: ");
  scanf("%lu", &endereco[slot].cep);

}

int find_free(){
  int i;

  for (i=0; (endereco[i].name[0] && i<MAX); i++);
  
  /*significa que o for percorreu todo o vetor de struct e não encontrou espaço disponível*/
  if (i==MAX) return -1; 

  return i;
}

void delete(){
  int slot;

  printf("\n Digite o número do registro a ser excluído: ");
  scanf("%d%*c", &slot);
  if(slot >=0 && slot < MAX){
    endereco[slot].name[0] = '\0';
  }
}

void list(){
  for (int i = 0; i<MAX; i++){
    printf("\nREGISTRO[%d]",i);
    printf("\nNome: %s", endereco[i].name);
    printf("\nRua: %s", endereco[i].street);
    printf("\nCidade: %s", endereco[i].city);
    printf("\nEstado: %s", endereco[i].state);
    printf("\nCEP: %lu\n", endereco[i].cep);
  }
  printf("Pressione Enter para voltar");
  getchar();
}

void clear(){
  #if defined(__linux__)||defined(__unix__)
    system("clear");
  #endif

  #if defined(__WIN32)||defined(__WIN64)
    system("cls");
  #endif
}