#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define LIMITEJOG 10

//estruturas e enum

enum cursos{INFO = 1,MEC,MAMB,TADS,TGA,CSOC};

typedef enum
{


   Goleiro,
   AlaD,
   AlaE,
   Fixo,
   Pivo

} Eposicao;


char EnumCurso[][5] ={
    "INFO",
    "MEC",
    "MAMB",
    "TADS",
    "TGA",
    "CSOC"
};

char EnumPosicoes[][8] ={
    "Goleiro",
    "AlaD",
    "AlaE",
    "Fixo",
    "Pivo"
};

typedef struct
{
   int dia;
   int mes;
   int ano;
} Tdata;

typedef struct{
    char *nome;
    enum cursos curso;
    int ano;

}Tturma;


typedef struct{
    char *nome;
   char *matricula;
   int num_Camisa;
   Eposicao *posicao;
   Tdata data_Nasc;
   Tturma turma;
   int q_posicao;
}Tjogador;

typedef struct{
    char *nome;
   char *tecnico;
   Tjogador *jogadores;
   Tturma *turmas;
   int q_jogador;
   int q_turma;
}Ttime;


// funções
void mensagemError(int codigoError);
void SalvarTurma();
void RecuperaTime();
void SalvarTime();
void RecuperaTurma();
int verificacao();
void salva();
void recuperacao();
int valido(int dia ,int mes,int ano);

void menuPrincipal();
int opcao_menuPrincipal(int op);

void menu_turma();
void opcao_menuTurma(int op);
int incluirTurma();
Tturma criaTurma();
void menuListarTurma();
int opcao_menuListarTurma(int op);
void listarTurma(int op);
int alterarTurma();
int ALTERARTURMA(int turma);
int menuAlterarAtributo();
int excluirTurma();

void menu_time();
void opcao_menuTime(int op);

int incluirTime();
Ttime criaTime();
Tjogador criaJogador();

void ListarJogador(int i);
void menuListarTime();
int ListarTime(int op);

void menuAtualizarJogador(int i);
void opcao_menuAtualizarJogador(int op,int i);

void menuAlterarTime();
void opcao_menuAlterarTime(int op);

void menuAlterarJogador(int i);
void opcao_menuAlterarJogador(int op, int i);
void adicionaPosicao(char op,int i,int ii);
void excluiJogador(int i);
void EXCLUIJOGADOR(int i,int jogador);
void reorganizarJogadores(int i,int jogador);

void excluirTime();
void EXCLUIRTIME(int op);
void reorganizarTime(int op);




int _qTurmas = 0;
int _qTimes = 0; 
Tturma *_turma;
Ttime *_time;



// main
int main()
{
    menuPrincipal();

    return 0;
}

// funções
void mensagemError(int codigoError){
    switch (codigoError)
    {
    case 0:printf("ERRO : Opcao Invalida!\n");
        break;
    case -6:printf("ERRO : Sem Times, Adicione Times no Menu Time!\n");
        break;
    case -7:printf("ERRO : Limite de Turmas Atingido!");
        break;
    case -8:printf("ERRO : Turma Invalida!\n");
        break;
    case -9:printf("ERRO : Sem Turmas, Adicione Turmas no Menu Turma!\n");
        break;
    case -10:printf("ERRO : Erro de Alocacao de Memoria!\n");
        break;
    
    default:printf("ERRO !! \n");
        break;
    }
    ;
}

void menuPrincipal()
{

    
    int erro=1,op = 1;
    recuperacao();
    while (op != 3)
    {
        if(erro<1){
            mensagemError(erro);
        }
        printf("\nLIGA CORUJA DE FUTSAL\n");
        printf("- 1)TURMA\n");
        printf("- 2)TIME\n");
        printf("- 3)SAIR\n");
        printf(":");
        scanf("%d", &op);
        __fpurge(stdin);

        if(op == 3){
            salva();
        }


        erro = opcao_menuPrincipal(op);

    }

}


int opcao_menuPrincipal(int op){
    if(op<1 || op >2){
        return 0;
    }else{
        if(op == 1){
            menu_turma();
        }else{
            if(_qTurmas >= 1){
                menu_time();
            }else{
                mensagemError(-9);
            }
        }
    }

    return 1;
   
}



void menu_turma()
{

    int op = 1;
    while (op != 5)
    {
       
        ;
        printf("MENU TURMA\n");
        printf("- 1)INCLUIR\n");
        printf("- 2)ALTERAR\n");
        printf("- 3)EXCLUIR\n");
        printf("- 4)LISTAR\n");
        printf("- 5)VOLTAR\n");
        printf(":");
        scanf("%d",&op);
        __fpurge(stdin);

        if(op<1 || op > 5){
            mensagemError(0);
        }else{
            opcao_menuTurma(op);
        }


        

    }
    
}

void opcao_menuTurma(int op){
    ;
    int erro=0;
    if(op < 1 || op > 5){
        mensagemError(0);
    }
    else{

        if(op == 1){
            erro = incluirTurma();
        }else if(op == 2){
            erro = alterarTurma();
        }else if(op == 3){
            erro = excluirTurma();
        }else if(op == 4){   
            menuListarTurma();           
        }
        if(erro < 0){
            mensagemError(erro);
        }

    }
}

int incluirTurma(){
    char aux[MAX];
    if (_qTurmas == 0)
    {
        _turma = (Tturma*) malloc((1) * sizeof(Tturma));
    }else{
        _turma = (Tturma*) realloc(_turma, (_qTurmas + 1) * sizeof(Tturma));
    }
    

    if(!_turma){
        return -10;
    }

    printf("Nome da Turma : ");
    gets(aux);
    _turma[_qTurmas].nome = (char *) malloc ((strlen(aux)+1) * sizeof(char));
    strcpy(_turma[_qTurmas].nome, aux);
    __fpurge(stdin);

    printf("\nDigite o Numero do Respectivo Curso \n(INFO = 1) (MEC = 2) (MAMB = 3) (TADS = 4) (TGA = 5) (CSOC = 6)\n :");
    scanf("%d",&_turma[_qTurmas].curso);
    __fpurge(stdin);

    printf("\nAno da Turma :");
    scanf("%d",&_turma[_qTurmas].ano);
    __fpurge(stdin);


    _qTurmas++;

    return 0;
}

int alterarTurma(){
    int turma = -1,resp;
    if(_qTurmas<1){
        return -9;
    }
    while(turma< 0 || turma >= _qTurmas){
        if(_qTurmas > 1){
            printf("Digite a Turma que deseja Alterar :\n");
            listarTurma(2);
            printf(":");
            scanf("%d",&turma);
            __fpurge(stdin);
        }else{
            turma = 1;
        }


        turma--;
        if(turma< 0 || turma >= _qTurmas){
            mensagemError(-8);
        }else{
            resp = ALTERARTURMA(turma);
        }

    }

    ;
    if(resp>0){
        printf("Nome : %s\n",_turma[turma].nome);
        printf("Turma : %s\n",EnumCurso[_turma[turma].curso -1]);
        printf("Ano : %d\n",_turma[turma].ano);
    } 

    ;

    


}

int ALTERARTURMA(int turma){
    int atributo = 1, erro = -1;
    char op;

    while(atributo > 0){
        atributo = menuAlterarAtributo();

        char aux[MAX];

        switch (atributo)
        {
        case 1:
           op = verificacao();
           __fpurge(stdin);
           if(op == 's' || op == 'S'){
                printf("Digite o Novo Nome da Turma: ");
                gets(aux);
                _turma[turma].nome = (char *) malloc ((strlen(aux)+1) * sizeof(char));
                strcpy(_turma[turma].nome, aux);                 
                __fpurge(stdin);
           }
            
             
            break;
        case 2:
            op = verificacao();
            __fpurge(stdin);
            if(op == 's' || op == 'S'){
                printf("Digite o Novo Curso da Turma (INFO = 1) (MEC = 2) (MAMB = 3) (TADS = 4) (TGA = 5) (CSOC = 6) : ");
                scanf("%d",&_turma[turma].curso);
                __fpurge(stdin);
            }
            break;
        case 3:
            op = verificacao();
            __fpurge(stdin);
            if(op == 's' || op == 'S'){
                printf("Digite o Novo Ano da Turma: ");
                scanf("%d",&_turma[turma].ano);
                __fpurge(stdin); 
            }
            break;
        case 4:
            return -1;
            break;
        

        }
    }


    return 1;
}

int menuAlterarAtributo(){
    int op = -1;
    while(op < 1 || op > 3){
        ;
        printf("Digite o Atributo a Alterar \n");
        printf("- 1)NOME DA Tturma\n");
        printf("- 2)CURSO \n");
        printf("- 3)ANO DO CURSO \n");
        printf("- 4)VOLTAR \n");
        printf(":");
        scanf("%d",&op);
        __fpurge(stdin);

        if(op < 1 || op > 6){
            mensagemError(0);
        }else{
            return op;
        }
    }
}


    

void menuListarTurma(){
    int erro=1,op = 1;

    if(_qTurmas < 1){
        mensagemError(-9);

    }else{
        while (op != 3)
        {
            if(erro<1){
                mensagemError(erro);
            }
            ;
            printf("MENU LISTAR TURMA\n");
            printf("- 1)LISTAR TURMA\n");
            printf("- 2)LISTAR TURMAS\n");
            printf("- 3)VOLTAR\n");
            printf(":");
            scanf("%d",&op);


            erro = opcao_menuListarTurma(op);

        }
    }
    
    
    
    
}

int opcao_menuListarTurma(int op){
    if(op< 1 || op > 3){
        return 0;
    }else if(op < 3){
        listarTurma(op);
    }

    return 1;


}

int excluirTurma(){
    ;
    if(_qTurmas < 1){
        mensagemError(-9);
    }else{
        int op,pos;
        listarTurma(2);
         printf("\nQual Turma Deseja Excluir?\n");
        printf(":");
        scanf("%d",&pos);
        __fpurge(stdin);

        op = verificacao();

        if(op == 's' || op == 'S'){
            for(;pos<_qTurmas;pos++){

                _turma[pos-1] = _turma[pos];

                _turma = (Tturma*) realloc(_turma, (_qTurmas - 1) * sizeof(Tturma)); 
            }
            _qTurmas--;
        }

    
    }
  
}

void listarTurma(int op){
    int i,erro=0;
    if(op == 1){
        ;
        printf("Qual Turma Deseja Ver? :\n");
        for(i=0;i<_qTurmas;i++){
            printf("- %d) %s  \n",i+1,_turma[i].nome);
        }
        do{
            
            erro++;
            if(erro>1){
                mensagemError(0);
            }
            printf(":");
            scanf("%d",&i);
            __fpurge(stdin);

        }while(i>_qTurmas || i< 1);
        
        ;
        printf("Nome : %s\n",_turma[i-1].nome);
        printf("Turma : %s\n",EnumCurso[_turma[i-1].curso -1]);
        printf("Ano : %d\n",_turma[i-1].ano);

        ;
        
    }else{
        ;
        printf("TURMAS\n");
        for(i=0;i<_qTurmas;i++){
            printf("- TURMA %d\n - Nome: %s \n - Turma: %s \n - Ano: %d \n\n ",i+1,_turma[i].nome,EnumCurso[_turma[i].curso-1],_turma[i].ano);
        }

        ;
    }
}
 

void menu_time()
{    
    int op = 1;

    if(_qTurmas < 1){
        mensagemError(-9);
    }
    while (op != 5)
    {
       
        ;
        printf("MENU TIME\n");
        printf("- 1)INCLUIR\n");
        printf("- 2)ALTERAR\n");
        printf("- 3)EXCLUIR\n");
        printf("- 4)LISTAR\n");
        printf("- 5)VOLTAR\n");
        printf(":");
        scanf("%d",&op);
        __fpurge(stdin);

        if(op<1 || op > 5){
            mensagemError(0);
        }else{
            opcao_menuTime(op);
        } 

    }
    
    
}

void opcao_menuTime(int op){

    int erro;

    if(op < 1 || op > 5){
        mensagemError(0);
    }else if(op < 5){
        if(op == 1){
            erro = incluirTime();

        }
        if(op == 2){
            menuAlterarTime();
        }
        if(op == 3){
            excluirTime();
        }
        if(op == 4){
            menuListarTime();
        }

        if(erro < 0){
            mensagemError(erro);
        }

    }


}

int incluirTime(){

    if (_qTimes == 0)
    {
        _time = (Ttime*) malloc((1) * sizeof(Ttime));
    }else{
        _time = (Ttime*) realloc(_time, (_qTimes + 1) * sizeof(Ttime));
    }

    if(!_time){
        return -10;
    }

    _time[_qTimes] = criaTime();

    _qTimes++; 

}

Ttime criaTime(){
    Ttime time;
    time.q_turma = 0;
    time.q_jogador = 0;
    char aux[MAX],op;
    int ret,i;

    printf("Nome do Time : ");
    gets(aux);
    time.nome = (char *) malloc ((strlen(aux)+1) * sizeof(char));
    strcpy(time.nome, aux);
    __fpurge(stdin);


    printf("Nome do Tecnico: ");
    gets(aux);
    time.tecnico = (char *) malloc ((strlen(aux)+1) * sizeof(char));
    strcpy(time.tecnico, aux);
    __fpurge(stdin);

    for(time.q_jogador = 0; time.q_jogador < LIMITEJOG ;){
        ;
        if (time.q_jogador < 1)
        {
            time.jogadores = (Tjogador*) malloc((1) * sizeof(Tjogador));
        }else{
            time.jogadores = (Tjogador*) realloc(time.jogadores, (time.q_jogador + 1) * sizeof(Tjogador));
        }

        if(!time.jogadores){
            mensagemError(-10);
            exit(1);
        }

        

        printf("Adicionando o %d Jogador\n",time.q_jogador+1);
        time.jogadores[time.q_jogador] = criaJogador();
        
        if(time.q_turma == 0){
            time.turmas = (Tturma *) malloc (1*sizeof(Tturma));
            time.turmas[0] = time.jogadores[time.q_jogador].turma;
            time.q_turma++;
            time.q_jogador++;

        }else if(time.q_turma == 1 && time.jogadores[time.q_jogador].turma.curso != time.turmas[0].curso){
            time.turmas = (Tturma *) realloc (time.turmas, (2) *sizeof(Tturma));
            time.turmas[1] = time.jogadores[time.q_jogador].turma;
            time.q_turma++;
            time.q_jogador++;
        }else if(time.q_turma == 2 && time.jogadores[time.q_jogador].turma.curso != time.turmas[0].curso && time.jogadores[time.q_jogador].turma.curso != time.turmas[1].curso){
            time.jogadores = (Tjogador*) realloc(time.jogadores, (time.q_jogador) * sizeof(Tjogador));
            printf("\nAdicione um Jogador Com mesma Turma que as Duas do Time\n");
            continue;

        }else{
            time.q_jogador++;
        }
        


    

        printf("Deseja Adicionar outro jogador? (s/n) : ");
        scanf("%c",&op);
        __fpurge(stdin);
        if(op == 's' || op == 'S'){
            continue;
        }else{
            break;
        }

        
    }





    return time;
}

Tjogador criaJogador(){


    Tjogador jogador;
    jogador.q_posicao = 0;

    char ops,aux[MAX];
    int op = 's',i;

    printf("Nome do Jogador: ");
    gets(aux);
    jogador.nome = (char *) malloc ((strlen(aux)+1) * sizeof(char));
    strcpy(jogador.nome, aux);
    __fpurge(stdin);

    printf("Matricula: ");
    gets(aux);
    jogador.matricula = (char *) malloc ((strlen(aux)+1) * sizeof(char));
    strcpy(jogador.matricula, aux);
    __fpurge(stdin);

    printf("Numero da Camisa: ");
    scanf("%d",&jogador.num_Camisa);
    __fpurge(stdin);

     while (op == 's' || op == 'S')
    {
       if (jogador.q_posicao < 1)
       {
           jogador.posicao = (Eposicao *) malloc (1 * sizeof(Eposicao));
       }
       else
       {
           jogador.posicao = (Eposicao *)realloc(jogador.posicao, (jogador.q_posicao + 1) * sizeof(Eposicao));
       }

       if(jogador.posicao == NULL){
            printf("E\n\n");
            exit(1);

       }

       jogador.q_posicao++;

       printf("Selecione a Posicao/Posicoes\n");

       do{
        printf("\n- (Goleiro = 1)\n- (AlaD = 2)\n- (AlaE = 3)\n- (Fixo = 4)\n- (Pivo = 5)\n:");
        scanf("%d",&jogador.posicao[jogador.q_posicao - 1]);
        __fpurge(stdin);
        


        
       }while(jogador.posicao[jogador.q_posicao - 1] < 1 || jogador.posicao[jogador.q_posicao - 1] > 5);

       printf("Adicionar Outra Posicao? (s/n) :");
       scanf("%c",&op);
       __fpurge(stdin);
    }
    i=0;
    while(i<1){
        printf("Digite a Data de Nascimento: ");
        scanf("%d%d%d",&jogador.data_Nasc.dia,&jogador.data_Nasc.mes,&jogador.data_Nasc.ano);
        __fpurge(stdin);
        i = valido(jogador.data_Nasc.dia,jogador.data_Nasc.mes,jogador.data_Nasc.ano);

    }

    while(op < 1 || op > _qTurmas){
        listarTurma(2);
        printf("\nSelecione a Turma do Jogador\n");
        printf(":");
        scanf("%d",&op);
        __fpurge(stdin);
    }

    
    
    jogador.turma = _turma[op-1];
    








    return jogador;
}

void menuAlterarTime(){
    int op = 1,erro = 0;
    while (op != 4)
    {
        if(_qTimes < 1){
            mensagemError(-6);
            break;
        }
        if(erro < 0){
            mensagemError(erro);
        }
       
        ;
        printf("MENU ALTERAR TIME\n");
        printf("- 1)Nome do Time\n");
        printf("- 2) Nome do Tecnico\n");
        printf("- 3)Jogadores\n");
        printf("- 4)Voltar\n");
        printf(":");
        scanf("%d",&op);
        __fpurge(stdin);

        if(op < 1 || op > 4){
            mensagemError(0);
        }else{
            opcao_menuAlterarTime(op);
        } 

    }
}

void opcao_menuAlterarTime(int op){
    int i = 0;
    char veri,aux[MAX];
    if(op > 4 || op < 1){
        mensagemError(0);
    }else if(op < 4){
        switch (op)
            {
            case 1:
                veri = verificacao();
                if(veri == 's' || veri == 'S'){
                    ListarTime(2);
                    while(i < 1 || i > _qTimes){
                        ListarTime(2);
                        printf("Escolha o Time\n:");
                        scanf("%d",&i);
                    }
                    __fpurge(stdin);
                    printf("Digite o Novo Nome do Time\n:");
                    gets(aux);
                    _time[i-1].nome = (char *) malloc ((strlen(aux)+1) * sizeof(char));
                    strcpy(_time[i-1].nome, aux);
                    __fpurge(stdin);

                }

            break;
            case 2:
                veri = verificacao();
                if(veri == 's' || veri == 'S'){
                    while(i < 1 || i > _qTimes){
                        ListarTime(2);
                        printf("Escolha o Time\n:");
                        scanf("%d",&i);
                    }
                    __fpurge(stdin);
                    printf("Digite o Novo Nome do Tecnico\n:");
                    gets(aux);
                    _time[i-1].tecnico = (char *) malloc ((strlen(aux)+1) * sizeof(char));
                    strcpy(_time[i-1].tecnico, aux);
                    __fpurge(stdin);

                }
                break;
            case 3:
                veri = verificacao();
                if(veri == 's' || veri == 'S'){
                    while(i < 1 || i > _qTimes){
                        ListarTime(2);
                        printf("Escolha o Time\n:");
                        scanf("%d",&i);
                    }
                    __fpurge(stdin);
                    menuAtualizarJogador(i);
                break;
        
            default:
                break;
            }
        }
    }
} 

void menuAtualizarJogador(int i){
    int op = 1,erro = 0;
    while (op != 4)
    {
        if(_qTimes < 1){
            mensagemError(-6);
            break;
        }
        if(erro < 0){
            mensagemError(erro);
        }
       
        ;
        printf("MENU ATUALIZAR JOGADOR\n");
        printf("- 1)Incluir Novo Jogador\n");
        printf("- 2)Alterar Jogador\n");
        printf("- 3)Excluir Jogador\n");
        printf("- 4)Voltar\n");
        printf(":");
        scanf("%d",&op);
        __fpurge(stdin);

        if(op < 1 || op > 4){
            mensagemError(0);
        }else{
            opcao_menuAtualizarJogador(op,i);
        } 

    }

}
void opcao_menuAtualizarJogador(int op,int i){
    int erro;
    char veri;
    int e = 0;
    if(op < 1 || op > 5){
        mensagemError(0);
    }else if(op < 5){
        switch (op)
        {
        case 1:
        
            veri = verificacao();
            __fpurge(stdin);
            if(veri == 's' || veri == 'S'){
                while(e != 1){
                    _time[i - 1].jogadores = (Tjogador*) realloc (_time[i-1].jogadores,(_time[i-1].q_jogador + 1) * sizeof(Tjogador));
                    _time[i-1].jogadores[_time[i-1].q_jogador] = criaJogador();

                    if(_time[i-1].q_turma == 1 && _time[i-1].jogadores[_time[i-1].q_jogador].turma.curso != _time[i-1].turmas[0].curso){
                        _time[i-1].turmas = (Tturma *) realloc (_time[i-1].turmas, (2) *sizeof(Tturma));
                        _time[i-1].turmas[1] = _time[i-1].jogadores[_time[i-1].q_jogador].turma;
                        _time[i-1].q_turma++;
                        _time[i-1].q_jogador++;
                        e = 1;
                    }else if(_time[i-1].q_turma == 2 && _time[i-1].jogadores[_time[i-1].q_jogador].turma.curso != _time[i-1].turmas[0].curso && _time[i-1].jogadores[_time[i-1].q_jogador].turma.curso != _time[i-1].turmas[1].curso){
                        _time[i-1].jogadores = (Tjogador*) realloc(_time[i-1].jogadores, (_time[i-1].q_jogador) * sizeof(Tjogador));
                        printf("\nAdicione um Jogador Com mesma Turma que as Duas do Time\n");
                        continue;

                    }else{
                        _time[i-1].q_jogador++;
                        e = 1;
                    }
                }
                
                
            }

            break;
        case 2:
            menuAlterarJogador(i);
            break;
        case 3:
            excluiJogador(i);
            break;
        
        default:
            break;
        }

    }


}

void excluiJogador(int i){
    int jogador = -1,exc = 0;
    char op;

    if(_time[i-1].q_jogador < 1){
        mensagemError(-6);
    }else{
        while(jogador < 1 || jogador > _time[i-1].q_jogador){
            if(_time[i-1].q_jogador < 2){
    
                
                ListarJogador(i-1);
                printf("Deseja Excluir o Jogador [1]? (s/n):");
                scanf("%c",&op);
                __fpurge(stdin);


                if(op == 's' || op == 'S'){
                    exc = 1;
                    EXCLUIJOGADOR(i,0);
                }

                break;
                
            }else{
                ListarJogador(i-1);
                printf("Digite o Jogador que deseja excluir\n :");
                scanf("%d",&jogador);
                __fpurge(stdin);
                jogador--;

                if(jogador < 0 || jogador >= _time[i-1].q_jogador){
                    mensagemError(0);
                }else{
                    printf("Deseja Excluir o Jogador [%d] (s/n \n:",jogador + 1);
                    scanf("%c",&op);
                    __fpurge(stdin);

                    if(op == 's' || op == 'S'){
                        EXCLUIJOGADOR(i,jogador);
                        exc = 1;
                        break;
                    }
                }
            }
        }
        if(exc){
            printf("\n\nEXCLUSAO BEM SUCEDIDA!!\n\n");
        }
    }
    

    
    
}

void EXCLUIJOGADOR(int i,int jogador){
    if(_time[i-1].q_jogador < 2 || jogador == _time[i-1].q_jogador){
        _time[i-1].jogadores = (Tjogador*) realloc (_time[i-1].jogadores,(_time[i-1].q_jogador - 1) * sizeof (Tjogador));
        _time[i-1].q_jogador--;
    }else{
        reorganizarJogadores(i,jogador);
        _time[i-1].jogadores = (Tjogador*) realloc (_time[i-1].jogadores,(_time[i-1].q_jogador) * sizeof (Tjogador));
    }
}

void reorganizarJogadores(int i,int jogador){
    int j;
    for(j = jogador;j < _time[i-1].q_jogador - 1;j++){
        _time[i-1].jogadores[j] = _time[i-1].jogadores[j+1];
    }
    _time[i-1].q_jogador--;

}

void menuAlterarJogador(int i){
    int op = 1,erro = 0;
    while (op != 7)
    {
        if(_qTimes < 1){
            mensagemError(-6);
            break;
        }
        if(erro < 0){
            mensagemError(erro);
        }
       
        ;
        printf("MENU ALTERAR Jogador\n");
        printf("- 1)Nome do Jogador\n");
        printf("- 2)Matricula\n");
        printf("- 3)Numero da Camisa do Jogador\n");
        printf("- 4)Posicoes\n");
        printf("- 5)Data de Nascimento\n");
        printf("- 6)Turma\n");
        printf("- 7)Voltar\n");
        printf(":");
        scanf("%d",&op);
        __fpurge(stdin);

        if(op < 1 || op > 7){
            mensagemError(0);
        }else{
            opcao_menuAlterarJogador(op,i);
        } 

    }

}

void opcao_menuAlterarJogador(int op, int i){
    int ii;
    char veri,aux[MAX];
    if(op > 7 || op < 1){
        mensagemError(0);
    }else if(op < 7){
        switch (op)
        {
        case 1:
            veri = verificacao();
            if(veri == 's' || veri == 'S'){
                ListarJogador(i - 1);
                printf("\n:");
                scanf("%d",&ii);
                __fpurge(stdin);
                ii--;

                printf("Digite o Novo Nome do Jogador:");
                gets(aux);
                _time[i-1].jogadores[ii].nome = (char *) malloc ((strlen(aux)+1) * sizeof(char));
                strcpy(_time[i-1].jogadores[ii].nome, aux);
                __fpurge(stdin);

            }
            break;
        case 2:
            veri = verificacao();
            if(veri == 's' || veri == 'S'){
                ListarJogador(i - 1);
                printf("\n:");
                scanf("%d",&ii);
                __fpurge(stdin);
                ii--;

                printf("Digite a Nova Matricula:");
                gets(aux);
                _time[i-1].jogadores[ii].matricula= (char *) malloc ((strlen(aux)+1) * sizeof(char));
                strcpy(_time[i-1].jogadores[ii].matricula, aux);
                __fpurge(stdin);

            }
            break;
        case 3:
            veri = verificacao();
            if(veri == 's' || veri == 'S'){
                ListarJogador(i - 1);
                printf("\n:");
                scanf("%d",&ii);
                __fpurge(stdin);
                ii--;

                printf("Digite a Novo Numero de Camiseta:");
                scanf("%d",&_time[i-1].jogadores[ii].num_Camisa);

            }
            break;
        
        case 4:
            veri = verificacao();
            if(veri == 's' || veri == 'S'){
                _time[i - 1].jogadores[ii].q_posicao = 0;
                ListarJogador(i - 1);
                printf("\n:");
                scanf("%d",&ii);
                __fpurge(stdin);
                ii--;

                adicionaPosicao(veri,i,ii);


            }
            break;
        case 5:
            veri = verificacao();
            if(veri == 's' || veri == 'S'){
                ListarJogador(i - 1);
                printf("\n:");
                scanf("%d",&ii);
                __fpurge(stdin);
                ii--;

                printf("Digite a Nova data de Nascimento: ");
                scanf("%d%d%d",&_time[i-1].jogadores[ii].data_Nasc.dia,&_time[i-1].jogadores[ii].data_Nasc.mes,&_time[i-1].jogadores[ii].data_Nasc.ano);
            }
            break;
        case 6:
            veri = verificacao();
            if(veri == 's' || veri == 'S'){
                int op,exc = 0;
                ListarJogador(i - 1);
                printf("\n:");
                scanf("%d",&ii);
                __fpurge(stdin);
                ii--;

                while(exc != 1){
                    listarTurma(2);
                    printf("Digite a Turma Nova\n :");
                    scanf("%d",&op);


                    if(_time[i-1].q_turma == 1 && _time[i-1].turmas[0].curso != _turma[op - 1].curso){
                        _time[i-1].turmas = (Tturma *) realloc (_time[i-1].turmas, (2) *sizeof(Tturma));
                        _time[i-1].turmas[1] = _turma[op-1];
                        _time[i-1].jogadores[ii].turma = _turma[op-1];
                        _time[i-1].q_turma++;

                        exc = 1;
                    
                    }else if(_time[i-1].q_turma == 2 && _time[i-1].turmas[0].curso != _turma[op - 1].curso && _time[i-1].turmas[1].curso != _turma[op - 1].curso){
                        printf("Selecione Uma Turma do Time!\n");
                        continue;
                    }else if(_time[i-1].q_turma == 1 && _time[i-1].turmas[0].curso == _turma[op - 1].curso){
                        _time[i-1].jogadores[ii].turma = _turma[op-1];
                        exc = 1;
                    }else if(_time[i-1].q_turma == 2 && _time[i-1].turmas[0].curso != _turma[op - 1].curso && _time[i-1].turmas[1].curso == _turma[op - 1].curso){
                        _time[i-1].jogadores[ii].turma = _turma[op-1];
                        exc = 1;
                    }else if(_time[i-1].q_turma == 2 && _time[i-1].turmas[0].curso == _turma[op - 1].curso && _time[i-1].turmas[1].curso != _turma[op - 1].curso){
                        _time[i-1].jogadores[ii].turma = _turma[op-1];
                        exc = 1;
                    }
                }


            }
            break;
        
        default:
            break;
        }
    }
}

void adicionaPosicao(char op,int i,int ii){

    //_time[i-1].jogadores[ii].nome

     while (op == 's' || op == 'S')
    {
       if (_time[i-1].jogadores[ii].q_posicao < 1)
       {
           _time[i-1].jogadores[ii].posicao = (Eposicao *) malloc (1 * sizeof(Eposicao));
       }
       else
       {
           _time[i-1].jogadores[ii].posicao = (Eposicao *)realloc(_time[i-1].jogadores[ii].posicao, (_time[i-1].jogadores[ii].q_posicao + 1) * sizeof(Eposicao));
       }

       if(_time[i-1].jogadores[ii].posicao == NULL){
            printf("E\n\n");
            exit(1);

       }

       _time[i-1].jogadores[ii].q_posicao++;

       printf("Selecione a Posicao/Posicoes\n");

       do{
        printf("\n- (Goleiro = 1)\n- (AlaD = 2)\n- (AlaE = 3)\n- (Fixo = 4)\n- (Pivo = 5)\n:");
        scanf("%d",&_time[i - 1].jogadores[ii].posicao[_time[i - 1].jogadores[ii].q_posicao - 1]);
        __fpurge(stdin);
        


        
       }while(_time[i-1].jogadores[ii].posicao[_time[i - 1].jogadores[ii].q_posicao - 1] < 1 || _time[i-1].jogadores[ii].posicao[_time[i - 1].jogadores[ii].q_posicao - 1] > 5);

       printf("Adicionar Outra Posicao? (s/n) :");
       scanf("%c",&op);
       __fpurge(stdin);
    }
}
void menuListarTime(){
    int op = 1,erro = 0;
    while (op != 3)
    {
        if(erro < 0){
            mensagemError(erro);
        }
       
        ;
        printf("MENU TIME\n");
        printf("- 1)Listar Time\n");
        printf("- 2)Listar Times\n");
        printf("- 3)Voltar\n");
        printf(":");
        scanf("%d",&op);
        __fpurge(stdin);

        if(op < 1 || op > 3){
            mensagemError(0);
        }else{
            erro = ListarTime(op);
        } 

    }
    
}

int ListarTime(int op){
    int i,erro = 0;
    int j, j1;

    if(_qTimes < 1){
        return -6;
    }
    if(op == 1){
        ;
        for(i=0;i<_qTimes;i++){
            printf("- %d) %s  \n",i+1,_time[i].nome);
        }
        do{
            
            erro++;
            if(erro>1){
                mensagemError(0);
            }
            printf("Qual Time Deseja Ver?\n");
            printf(":");
            scanf("%d",&i);
            __fpurge(stdin);

        }while(i>_qTimes || i < 1);
        
        ;
        printf("Nome : %s\n",_time[i-1].nome);
        printf("Tecnico : %s\n",_time[i-1].tecnico);
        printf("Turmas Do Time \n");
        for(j=0;j<_time[i-1].q_turma;j++){
            printf("TURMA %d: %s\n",j+1,_time[i-1].turmas[j].nome);
        }
        ListarJogador(i - 1);

        ;
        
    }else if (op == 2){
        ;
        printf("TIMES\n");
        for(i=0;i<_qTimes;i++){
            printf("\n\nTIME %d \n\n",i + 1);
            printf("Nome : %s\n",_time[i].nome);
            printf("Tecnico : %s\n",_time[i].tecnico);
            for(j=0;j<_time[i].q_turma;j++){
            printf("TURMA %d: %s\n",j+1,_time[i].turmas[j].nome);
            }
            ListarJogador(i);
        }
        

        

        ;
    }

    return 0;
}

void ListarJogador(int i){
    int j,jj;

    for(j=0;j<_time[i].q_jogador;j++){
        printf("\nJOGADOR %d\n",j+1);

        printf("Nome :%s\n",_time[i].jogadores[j].nome);
        printf("Matricula :%s\n",_time[i].jogadores[j].matricula);
        printf("Numero da Camiseta :%d\n",_time[i].jogadores[j].num_Camisa);
        printf("Data de Nascimento: %d/%d/%d",_time[i].jogadores[j].data_Nasc.dia,_time[i].jogadores[j].data_Nasc.mes,_time[i].jogadores[j].data_Nasc.ano);
        printf("\n-POSICAO-\n");
            
        for(jj = 0 ; jj < _time[i].jogadores[j].q_posicao; jj++){
            printf("\nPosicao %d \n %s \n",jj + 1,EnumPosicoes[_time[i].jogadores[j].posicao[jj] - 1]);
        }
            
        printf("-TURMA-\n");
        printf("Nome : %s\n",_time[i].jogadores[j].turma.nome);
        printf("Curso : %s\n",EnumCurso[_time[i].jogadores[j].turma.curso - 1]);
        printf("Ano : %d\n",_time[i].jogadores[j].turma.ano);
            

    }
}
    
void excluirTime(){
    int op = 0;
    if(_qTimes < 1){
        mensagemError(-6);
    }else{
        while(op < 1 || op > _qTimes){
            ListarTime(2);
            printf("Qual Time deseja Excluir?\n :");
            scanf("%d",&op);    
        }

        EXCLUIRTIME(op - 1);
    }
    
}

void EXCLUIRTIME(int op){
    if(_qTimes < 2 || op == _qTimes){
        _time = (Ttime*) realloc (_time,(_qTimes - 1) * sizeof (Ttime));
        _qTimes--;
        printf("\nEXCLUSAO FEITA COM SUCESSO\n");
    }else{
        reorganizarTime(op);
        _time = (Ttime*) realloc (_time,(_qTimes) * sizeof (Ttime));
        printf("\nEXCLUSAO FEITA COM SUCESSO\n");
    }
}

void reorganizarTime(int op){
    int j;
    for(j = op;j < _qTimes - 1;j++){
        _time[j] = _time[j+1];
    }
    _qTimes--;
}


void salva(){
    SalvarTurma();
    SalvarTime();
    for (int i = 0; i < _qTurmas; i++) {
        free(_turma[i].nome);
    }

    free(_turma);
}

void recuperacao(){
    RecuperaTurma();
    RecuperaTime();
}

void SalvarTime(){
    int i,j,jj;
    FILE *pTime;

    pTime = fopen("timeBD.txt","w");

    if(pTime == NULL){
        printf("ERRO : Nao foi possivel criar o arquivo");
        exit(0);
    }
    

    for(i=0;i<_qTimes;i++){
        fprintf(pTime, "%s;", _time[i].nome);
        fprintf(pTime, "%s;", _time[i].tecnico);
        for(j=0;j<_time[i].q_turma;j++){
            fprintf(pTime, "%s+", _time[i].turmas[j].nome);
            fprintf(pTime, "%d+", _time[i].turmas[j].curso);
            fprintf(pTime, "%d+", _time[i].turmas[j].ano);
            fprintf(pTime,"%c",'*');
        }

        for(j = 0; j < _time[i].q_jogador; j++){
            fprintf(pTime, "%s!", _time[i].jogadores[j].nome);
            fprintf(pTime, "%s!", _time[i].jogadores[j].matricula);
            fprintf(pTime, "%d!", _time[i].jogadores[j].num_Camisa);
            for(jj = 0; jj < _time[i].jogadores[j].q_posicao;jj++){
                fprintf(pTime, "%d@", _time[i].jogadores[j].posicao[jj]);
            }
            fprintf(pTime ,"%d#", _time[i].jogadores[j].data_Nasc.dia);
            fprintf(pTime, "%d#", _time[i].jogadores[j].data_Nasc.mes);
            fprintf(pTime, "%d#", _time[i].jogadores[j].data_Nasc.ano);
            fprintf(pTime, "%s&", _time[i].jogadores[j].turma.nome);
            fprintf(pTime, "%d&", _time[i].jogadores[j].turma.curso);
            fprintf(pTime, "%d&", _time[i].jogadores[j].turma.ano);

            fprintf(pTime, "%c",'$');
            
        }

        fprintf(pTime, "%c", '\n');

    }

    fclose(pTime);

}

void RecuperaTime(){
    int i, sep,j;
    char str[100],c;

    FILE *pTime;

    pTime = fopen("timeBD.txt","r");

    if(pTime){
        i = 0;
        sep = 0;

        while(!feof(pTime)){
            c = fgetc(pTime);
            if((c != '\n')&& (c != '*')&& (c != '!') && (c != '$') && (c != ';') && (c != '+') && (c!='@') && (c != '#') && (c != '&') && (c!=EOF)){
                str[i] = c;
                i++;
            }else if((c==';') || (c=='+') || (c == '*') || (c=='!') || (c=='@') || (c=='#') || (c=='&') || (c=='$') || (c=='\n') ){
                str[i] = '\0';
                i=0;
                if(c == ';'){
                    if(sep == 0){
                        if(_qTimes == 0){
                            _time = (Ttime *)malloc(1*sizeof(Ttime));
                        }else{
                            _time = (Ttime *)realloc(_time, (_qTimes + 1) *sizeof(Ttime));
                        }

                        _time[_qTimes].nome = (char*) malloc (strlen(str) + 1 * sizeof(char) );
                        strcpy(_time[_qTimes].nome,str);
                        _time[_qTimes].q_jogador = 0;
                        _time[_qTimes].q_turma = 0;
                        sep++;
                    }else if(sep == 1){
                        _time[_qTimes].tecnico = (char*) malloc (strlen(str) + 1 * sizeof(char) );
                        strcpy(_time[_qTimes].tecnico,str);
                        sep=0;
                    }
                }else if(c == '+'){
                    if(sep==0){
                       if(_time[_qTimes].q_turma == 0){
                            _time[_qTimes].turmas = (Tturma *) malloc ((_time[_qTimes].q_turma + 1) * sizeof(Tturma));
                       }else{
                            _time[_qTimes].turmas = (Tturma *) realloc (_time[_qTimes].turmas,(_time[_qTimes].q_turma + 1) * sizeof(Tturma));
                       }
                        _time[_qTimes].turmas[_time[_qTimes].q_turma].nome = (char *) malloc ((strlen(str)+1) * sizeof(char));
                        strcpy(_time[_qTimes].turmas[_time[_qTimes].q_turma].nome,str);
                        sep++;
                    }else if(sep == 1){
                        _time[_qTimes].turmas[_time[_qTimes].q_turma].curso = atoi(str);
                        sep++;
                    }else if(sep == 2){
                        _time[_qTimes].turmas[_time[_qTimes].q_turma].ano = atoi(str);
                        sep = 0;
                    }
                }else if(c == '*'){
                    _time[_qTimes].q_turma++;
                    sep=0;
                }else if(c=='!'){
                    if(sep == 0){
                        if(_time[_qTimes].q_jogador == 0){
                            _time[_qTimes].jogadores = (Tjogador *) malloc (1*sizeof(Tjogador));
                        }else{
                            _time[_qTimes].jogadores = (Tjogador *) realloc (_time[_qTimes].jogadores, (_time[_qTimes].q_jogador + 1)*sizeof(Tjogador));
                        }

                        _time[_qTimes].jogadores[_time[_qTimes].q_jogador].nome = (char*) malloc (strlen(str) + 1 * sizeof(char) );
                        strcpy(_time[_qTimes].jogadores[_time[_qTimes].q_jogador].nome,str);
                        _time[_qTimes].jogadores[_time[_qTimes].q_jogador].q_posicao=0;

                        sep++;
                    }else if(sep == 1){
                        _time[_qTimes].jogadores[_time[_qTimes].q_jogador].matricula = (char*) malloc (strlen(str) + 1 * sizeof(char) );
                        strcpy(_time[_qTimes].jogadores[_time[_qTimes].q_jogador].matricula,str);
                        sep++;
                    }else if(sep == 2){
                        _time[_qTimes].jogadores[_time[_qTimes].q_jogador].num_Camisa = atoi(str);
                        sep = 0;
                    }
                }else if(c=='@'){
                    if(sep == 0){
                        if(_time[_qTimes].jogadores[_time[_qTimes].q_jogador].q_posicao == 0){
                            _time[_qTimes].jogadores[_time[_qTimes].q_jogador].posicao = (Eposicao*) malloc (1*sizeof(Eposicao));
                            j = _time[_qTimes].jogadores[_time[_qTimes].q_jogador].q_posicao; 
                            _time[_qTimes].jogadores[_time[_qTimes].q_jogador].posicao[j] = atoi(str);
                            _time[_qTimes].jogadores[_time[_qTimes].q_jogador].q_posicao++;
                        }else{
                            j = _time[_qTimes].jogadores[_time[_qTimes].q_jogador].q_posicao;
                            _time[_qTimes].jogadores[_time[_qTimes].q_jogador].posicao = (Eposicao*) realloc (_time[_qTimes].jogadores[_time[_qTimes].q_jogador].posicao,(j + 1)*sizeof(Eposicao));
                            _time[_qTimes].jogadores[_time[_qTimes].q_jogador].posicao[j] = atoi(str);
                            _time[_qTimes].jogadores[_time[_qTimes].q_jogador].q_posicao++;
                        }
                    }else{
                        j = _time[_qTimes].jogadores[_time[_qTimes].q_jogador].q_posicao;
                        _time[_qTimes].jogadores[_time[_qTimes].q_jogador].posicao = (Eposicao*) realloc (_time[_qTimes].jogadores[_time[_qTimes].q_jogador].posicao,(j + 1)*sizeof(Eposicao));
                        _time[_qTimes].jogadores[_time[_qTimes].q_jogador].posicao[j] = atoi(str);
                        _time[_qTimes].jogadores[_time[_qTimes].q_jogador].q_posicao++;
                        
                    }
                    if(sep == 1){
                        sep = 0;
                    }
                }else if(c=='#'){
                    if(sep == 0){
                        _time[_qTimes].jogadores[_time[_qTimes].q_jogador].data_Nasc.dia = atoi(str);
                        sep++;
                    }else if(sep == 1){
                        _time[_qTimes].jogadores[_time[_qTimes].q_jogador].data_Nasc.mes = atoi(str);
                        sep++;
                    }else if(sep == 2){
                        _time[_qTimes].jogadores[_time[_qTimes].q_jogador].data_Nasc.ano = atoi(str);
                        sep = 0;
                    }
                }else if(c=='&'){
                    if(sep == 0){
                        _time[_qTimes].jogadores[_time[_qTimes].q_jogador].turma.nome = (char *) malloc ((strlen(str)+1) * sizeof(char));
                        strcpy(_time[_qTimes].jogadores[_time[_qTimes].q_jogador].turma.nome,str);
                        sep++;
                    }else if(sep == 1){
                        _time[_qTimes].jogadores[_time[_qTimes].q_jogador].turma.curso = atoi(str);
                        sep++;
                    }else if(sep== 2){
                        _time[_qTimes].jogadores[_time[_qTimes].q_jogador].turma.ano = atoi(str);
                        sep = 0;
                    }
                }else if(c=='$'){
                    _time[_qTimes].q_jogador++;
                    sep = 0;
                }else{
                    _qTimes++;
                    sep = 0;
                }
            }
        }


        
        
    }
    fclose(pTime);
}


void SalvarTurma(){
    int i;
    FILE *pTurma;

    pTurma = fopen("turmaBD.txt","w");

    if(pTurma == NULL){
        printf("ERRO : Nao foi possivel abrir o arquivo");
        exit(0);
    }

    for(i=0;i<_qTurmas;i++){
        fprintf(pTurma, "%s;", _turma[i].nome);
        fprintf(pTurma, "%d;", _turma[i].curso);
        fprintf(pTurma, "%d;", _turma[i].ano);

        fprintf(pTurma, "%c", '\n');
    }

    

    fclose(pTurma);


}




void RecuperaTurma(){
    int i, sep;
    char str[100],c;

    FILE *pTurma;

    pTurma = fopen("turmaBD.txt","r");
    if(pTurma){
        i = 0;
        sep = 0;
        while(!feof(pTurma)){

            c = fgetc(pTurma);

            if((c != '\n') && (c != ';') && (c != EOF)){
                str[i] = c;
                i++;
            }
            else if((c == ';') || (c == '\n')){
                str[i] = '\0';
                i=0;
                if(c == ';'){
                    if(sep == 0){
                        if (_qTurmas == 0)
                        {
                            _turma = (Tturma*) malloc(1 * sizeof(Tturma));
                        }else{
                            _turma = (Tturma*) realloc(_turma, (_qTurmas + 1) * sizeof(Tturma));
                        }

                        _turma[_qTurmas].nome = (char *) malloc (strlen(str)+1 * sizeof(char));
                        strcpy(_turma[_qTurmas].nome,str);
                        sep++;
                    }else if(sep == 1){
                        _turma[_qTurmas].curso = atoi(str);
                        sep++;
                    }else if(sep == 2){
                        _turma[_qTurmas].ano = atoi(str);
                        sep = 0;
                    }
                }else{
                    sep = 0;
                    _qTurmas++;
                }
            }



        }


    }

    fclose(pTurma);

}

int verificacao(){
    char op;

    printf("Deseja Continuar essa Acao?? (s/n):\n ");
    scanf("%c",&op);


    return op;
}

int valido(int dia ,int mes,int ano){
    if (ano >= 1900 && ano <= 9999)
    {

        if (mes >= 1 && mes <= 12)
        {
          
            if ((dia >= 1 && dia <= 31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)){
                return 1;
            }    
            else if ((dia >= 1 && dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)){
                return 1;
            }
            else if ((dia >= 1 && dia <= 28) && (mes == 2)){
                return 1;
            }    
            else if (dia == 29 && mes == 2 && (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0))){
                return 1;
            }    
            else{
                return 0;
            }  
        }
        else{
            return -1;
        }
    }
    else
    {
        return -2;
    }
}
