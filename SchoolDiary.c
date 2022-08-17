#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


typedef struct studentReg{
    int registration;
    char name[15];
    float note1, note2, note3, average;
}studentReg;

//Criei uma struct para receber as notas usando typedef

//-----------------------Prototipos---------------------------------
float average(float note1, float note2, float note3);
void sortByRegistration(studentReg *class1, int size);
void sequentialSearch(studentReg *classX, int size);
void printAll(studentReg *classX, int size);
void printNames(studentReg *classX, int size);
void printNamesAndAverage(studentReg*classX, int size);
void bestStudent(studentReg *classX, int size);
void worstStudent(studentReg *classX, int size);
void studentsStatus(studentReg *classX, int size);
void changeNotes(int registraion, studentReg *classX, int size);
void editNotes(studentReg *classX, int size);
void printSortByReg(studentReg *classX, int size);
void saveNewFile(studentReg *classX, int size);
//------------------------------------------------------------------

int main(){
    FILE *arq;
    arq = fopen("alunos.txt", "r");
    //abre o arquivo
    if(arq == NULL){
        printf("Erro na abertura do arquivo.");
    }
    int lines = 1; //comeca com 1, porque a ultima linha nao tem quebra
    char charLine = '\n', c;
    while((c = fgetc(arq)) != EOF){
        if(c == charLine){
            lines++;
        }
    }
    fclose(arq);
    int size = lines;
    arq = fopen("alunos.txt", "r");
    studentReg *class1 = (studentReg*) malloc(size*sizeof(studentReg));
    if(class1 == NULL){
        printf("\nErro: memoria insuficiente!\n");
        exit(1);
    }
    for(int i = 0; i<size; i++){
        fscanf(arq,"%d %s %f %f %f", &class1[i].registration, &class1[i].name, &class1[i].note1, &class1[i].note2, &class1[i].note3);
        class1[i].average = average(class1[i].note1, class1[i].note2, class1[i].note3);
    }
    int option;
    
    for(;;){//loop infinito proposital
        printf("\n\n1. Imprimir todos os elementos do arranjo; \n2. Imprimir apenas os nomes dos alunos;\n3. Imprimir o nome dos alunos e sua respectiva nota final;\n4. Buscar os dados de um aluno usando a busca sequencial;\n5. Imprimir os alunos ordenados de acordo com sua matricula;\n6. Editar as notas de um aluno;\n7. Imprimir a matricula, nome e nota final do aluno que obteve a maior nota de todas;\n8. Imprimir a matricula, nome e nota final do aluno que obteve a menor nota de todas;\n9. Imprimir quantos alunos foram aprovados e quantos alunos foram reprovados;\n0. Salvar e sair do programa;\n\n");
        scanf("%d", &option);
        switch(option){
        case 1:
            system("cls");
            printAll(class1, size);
            break;
        case 2:
            system("cls");
            printNames(class1, size);
            break;
        case 3:
            system("cls");
            printNamesAndAverage(class1, size);
            break;
        case 4:
            system("cls");
            sequentialSearch(class1, size);
            break;
        case 5:
            system("cls");
            printSortByReg(class1, size);
            break;
        case 6:
            system("cls");
            editNotes(class1, size);
            break;
        case 7:
            system("cls");
            bestStudent(class1, size);
            break;
        case 8:
            system("cls");
            worstStudent(class1, size);
            break;
        case 9:
            system("cls");
            studentsStatus(class1, size);
            break;
        case 0:
            system("cls");
            saveNewFile(class1,size);
            exit(0);
        default:
            printf("Opcao invalida!");
        }
    }

free(class1);
return 0;
}

float average(float note1, float note2, float note3){
    return (note1 + note2 + note3)/3.0;
}
//Funcao para calcular a media
void sortByRegistration(studentReg *classX, int size){
    studentReg temp; //variaveis temporarias de mesmo tipo
    for(int count = 1; count < size; count++){
        for(int i = 0; i < size - 1; i++){
            if(classX[i].registration > classX[i + 1].registration){
                temp = classX[i];
                classX[i] = classX[i+1];
                classX[i+1] = temp;
            }
        }
    }
}
//Funcao de ordenar por matricula com bubblesort
void printSortByReg(studentReg *classX, int size){
    sortByRegistration(classX, size);
    printAll(classX, size);
}
//Funcao para ordenar por matricula e printar
void sequentialSearch(studentReg *classX, int size){
    int element = 0;
    printf("\n Digite um numero de matricula: ");
    scanf("%d", &element);
    int index;
    for(int i = 0; i < size; i++){
        if(classX[i].registration == element){
            index = i;
            break;
        }
        else{
            index = -1;
        }
    }
    if(index != -1){
        printf("\n Matricula: %d  Nome: %s  \n Nota 1: %.2f  Nota 1: %.2f  Nota 1: %.2f  \n Media: %.2f", classX[index].registration, classX[index].name, classX[index].note1, classX[index].note2, classX[index].note3, classX[index].average);
    }
    else{
        printf("\n Esse estudante nao existe.");
    }
}
//Funcao para buscar um termo e retornar o indice
void printAll(studentReg *classX, int size){
    for(int i = 0; i < size; i++){
        printf("\n Matricula: %d  Nome: %s  \n Nota 1: %.2f  Nota 2: %.2f  Nota 3: %.2f  Media:%.2f\n", classX[i].registration, classX[i].name, classX[i].note1, classX[i].note2, classX[i].note3, classX[i].average);
    }
}
//Funcao que imprime tudo
void printNames(studentReg *classX, int size){
    for(int i = 0; i < size; i++){
        printf("\n %s", classX[i].name);
    }
}
//Funcao que imprime os nomes
void printNamesAndAverage(studentReg *classX, int size){
    for(int i = 0; i < size; i++){
        printf("\n Nome: %s  Media: %.2f", classX[i].name, classX[i].average);
    }
}
//Funcao que imprime os nomes e as medias
void bestStudent(studentReg *classX, int size){
    float biggerNote = 0;
    int index = 0;
    for(int i = 0; i < size; i++){
        if(classX[i].average > biggerNote){
            biggerNote = classX[i].average;
            index = i;
        }
    }
    printf("\nMatricula: %d \nNome: %s \nMedia: %.2f", classX[index].registration, classX[index].name, classX[index].average);
}
//Funcao que imprime o melhor estudante
void worstStudent(studentReg *classX, int size){
    float lowerNote = 10;
    int index = 0;
    for(int i = 0; i < size; i++){
        if(classX[i].average < lowerNote){
            lowerNote = classX[i].average;
            index = i;
        }
    }
    printf("\nMatricula: %d \nNome: %s \nMedia: %.2f", classX[index].registration, classX[index].name, classX[index].average);
}
//Funcao que imprime o pior estudante
void studentsStatus(studentReg *classX, int size){
    int approved = 0, failed = 0;
    float generalAverage = 0;
    for(int i = 0; i < size; i++){
        generalAverage+= classX[i].average;
        if(classX[i].average >= 6.0){
            approved++;

        }
        else{
            failed++;
        }
    }
    generalAverage/=size;
    //lembrar de mudar average para average
    //Verifiquei o numero de estudantes aprovados e reprovados. Tambem calculei a media geral
    printf("\n %d estudante(s) aprovado(s) e %d estudante(s) reprovado(s). \n Media geral: %.2f", approved, failed, generalAverage);

    int approvedStudents[approved], failedStudents[failed];
    //Criei os arrays do exato tamanho necessario para armazenar os indices dos alunos
    approved = 0;
    failed = 0;
    //Reinicializei as variavies para reaproveita-las
    for(int j = 0; j < size; j++){
        if(classX[j].average >= 6.0){
            approvedStudents[approved] = j;
            approved++;
        }
        else{
            failedStudents[failed] = j;
            failed++;
        }
    }
    printf("\n Estudante(s) aprovado(s): ");
    for (int i = 0; i < approved; i++){
        printf("\n Nome: %s  Media: %.2f", classX[approvedStudents[i]].name, classX[approvedStudents[i]].average);
    }
    printf("\n Estudante(s) reprovado(s): ");
    for (int i = 0; i < failed; i++){
        printf("\n Nome: %s  Media: %.2f", classX[failedStudents[i]].name, classX[failedStudents[i]].average);
    }
}
//Funcao que imprime os status dos estudantes
void changeNotes(int registraion, studentReg *classX, int size){
    for(int i = 0; i < size; i++){
        if(registraion == classX[i].registration){
            printf("\nDigite o novo valor da nota 1: ");
            scanf("%f", &classX[i].note1);
            printf("\nDigite o novo valor da nota 2: ");
            scanf("%f", &classX[i].note2);
            printf("\nDigite o novo valor da nota 3: ");
            scanf("%f", &classX[i].note3);
            classX[i].average = average(classX[i].note1, classX[i].note2, classX[i].note3);
            break;
        }
    }
}
//Funcao que altera os dados do array
void editNotes(studentReg *classX, int size){
    int reg = 0;
    printf("\nDigite o numero de matricula do aluno que deseja editar as notas: ");
    scanf("%d", &reg);
    changeNotes(reg, classX, size);
}
//Funcao  que inicia o processo de alteracao de notas
void saveNewFile(studentReg *classX, int size){
    sortByRegistration(classX, size);
    FILE *newFile;
    newFile = fopen("updatedDiary.txt", "w");
    for(int i = 0; i < 116; i++){
        fprintf(newFile, "Matricula: %d Nome: %s Nota 1: %.2f Nota 2: %.2f Nota 3: %.2f Media: %.2f\n", classX[i].registration, classX[i].name, classX[i].note1, classX[i].note2, classX[i].note3, classX[i].average);
    }
    fclose(newFile);
    printf("\nArquivo salvo com sucesso!");
}
//Funcao que salva o novo arquivo