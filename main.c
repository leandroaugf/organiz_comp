#include "cpu.h"
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char**argv) {

    double tempo_exec;
    clock_t inicio, fim;

    inicio = clock();

    srand(time(NULL));   // Inicializacao da semente para os numeros aleatorios.

    if (argc != 3) {
        printf("Numero de argumentos invalidos! Sao 3.\n");
        printf("Linha de execucao: ./exe TIPO_INSTRUCAO [TAMANHO_RAM|ARQUIVO_DE_INSTRUCOES]\n");
        printf("\tExemplo 1 de execucao: ./exe random 10\n");
        printf("\tExemplo 2 de execucao: ./exe operacao_desejada\n");
        printf("\tExemplo 3 de execucao: ./exe file arquivo_de_instrucoes.txt\n");
        return 0;
    }

    int ramSize; int tam;
    Machine machine;
    Instruction *instructions;

    if (strcmp(argv[1], "random") == 0) {
        ramSize = atoi(argv[2]);
        instructions = generateRandomInstructions(ramSize);
    } else if (strcmp(argv[1], "file") == 0) {
        instructions = readInstructions(argv[2], &ramSize);
    } else if(strcmp(argv[1], "multiplicacao") == 0){
        ramSize = atoi(argv[2]);
        instructions = generateMultiInstructions(rand() % 10 + 1, rand() % 10 + 1);
    } else if(strcmp(argv[1], "divisao") == 0){
        ramSize = atoi(argv[2]);
        instructions = generateDiviInstructions(5, 100);
    } else if(strcmp(argv[1], "exponencial") == 0){
        ramSize = atoi(argv[2]);
        int RAMContent1 = rand() % 30 + 1;
        int RAMContent2 = rand() % 4 + 1;
        tam = RAMContent2 - 1;
        // Instruction *instructions2 = malloc(tam * sizeof(Instruction));
        for (int i = 0; i < tam; i++) {
            // [COMO GRAVAR RAMC1?]
            instructions = generateMultiInstructions(RAMContent1, RAMContent2);
            if (i == 0) {
                start(&machine, instructions, ramSize);
            }
            else { // [EXECUÇÕES POSTERIORES]
                attInstructions(&machine, instructions); 
            }
            run(&machine);
            RAMContent1 = machine.RAM.items[2];
            free(instructions);
        }
    } else {
        printf("Opcao invalida.\n");
        return 0;
    }
    
    printf("Iniciando a maquina...\n");
    start(&machine, instructions, ramSize);
    printRAM(&machine);
    run(&machine);
    printRAM(&machine);
    stop(&machine);
    printf("Finalizando a maquina...\n");

    fim = clock();
    tempo_exec = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %fs\n", tempo_exec);

     return 0;
}