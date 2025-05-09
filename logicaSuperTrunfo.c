#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    char codigo[20];
    char estado[50];
    float area;
    float pib; // Em bilhões
    unsigned long int populacao;
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
} Cidade;

// Função para preencher os dados da carta
void preencherCarta(Cidade *carta, int numero) {
    printf("\nDigite os dados da carta %d:\n", numero);

    printf("Nome da cidade: ");
    scanf(" %[^\n]", carta->nome);

    printf("Código da carta: ");
    scanf(" %s", carta->codigo);

    printf("Estado: ");
    scanf(" %[^\n]", carta->estado);

    printf("Área (km²): ");
    scanf("%f", &carta->area);

    printf("PIB (em bilhões): ");
    scanf("%f", &carta->pib);

    printf("População: ");
    scanf("%lu", &carta->populacao);

    printf("Número de pontos turísticos: ");
    scanf("%d", &carta->pontos_turisticos);

    // Cálculos
    carta->densidade_populacional = carta->populacao / carta->area;
    carta->pib_per_capita = (carta->pib * 1e9) / carta->populacao;
}

// Função para exibir os dados da carta
void exibirCarta(Cidade carta, int numero) {
    printf("\nCarta %d:\n", numero);
    printf("Cidade: %s (%s)\n", carta.nome, carta.estado);
    printf("Código: %s\n", carta.codigo);
    printf("População: %lu\n", carta.populacao);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: %.2f bilhões\n", carta.pib);
    printf("Pontos turísticos: %d\n", carta.pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta.densidade_populacional);
    printf("PIB per capita: %.2f reais\n", carta.pib_per_capita);
}

// Função para obter o valor de um atributo
float obterValorAtributo(Cidade c, int opcao) {
    switch(opcao) {
        case 1: return c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return c.pontos_turisticos;
        case 5: return c.densidade_populacional;
        case 6: return c.pib_per_capita;
        default: return -1;
    }
}

// Função para exibir o nome de um atributo
const char* nomeAtributo(int opcao) {
    switch(opcao) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica";
        case 6: return "PIB per Capita";
        default: return "Desconhecido";
    }
}

// Menu para escolher atributos
int escolherAtributo(int usado) {
    int opcao;

    do {
        printf("\nEscolha um atributo para comparar:\n");
        if(usado != 1) printf("1 - População\n");
        if(usado != 2) printf("2 - Área\n");
        if(usado != 3) printf("3 - PIB\n");
        if(usado != 4) printf("4 - Pontos Turísticos\n");
        if(usado != 5) printf("5 - Densidade Demográfica\n");
        if(usado != 6) printf("6 - PIB per Capita\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        if(opcao < 1 || opcao > 6 || opcao == usado) {
            printf("Opção inválida ou já usada. Tente novamente.\n");
        }
    } while(opcao < 1 || opcao > 6 || opcao == usado);

    return opcao;
}

// Função para comparar duas cartas com base em dois atributos
void compararCartas(Cidade c1, Cidade c2) {
    int atributo1 = escolherAtributo(0);
    int atributo2 = escolherAtributo(atributo1);

    float v1_attr1 = obterValorAtributo(c1, atributo1);
    float v2_attr1 = obterValorAtributo(c2, atributo1);
    float v1_attr2 = obterValorAtributo(c1, atributo2);
    float v2_attr2 = obterValorAtributo(c2, atributo2);

    int resultado1 = 0, resultado2 = 0;

    // Comparar primeiro atributo
    if (atributo1 == 5) { // densidade demográfica (menor vence)
        if (v1_attr1 < v2_attr1) resultado1++;
        else if (v2_attr1 < v1_attr1) resultado2++;
    } else {
        if (v1_attr1 > v2_attr1) resultado1++;
        else if (v2_attr1 > v1_attr1) resultado2++;
    }

    // Comparar segundo atributo
    if (atributo2 == 5) {
        if (v1_attr2 < v2_attr2) resultado1++;
        else if (v2_attr2 < v1_attr2) resultado2++;
    } else {
        if (v1_attr2 > v2_attr2) resultado1++;
        else if (v2_attr2 > v1_attr2) resultado2++;
    }

    float soma1 = v1_attr1 + v1_attr2;
    float soma2 = v2_attr1 + v2_attr2;

    // Exibição
    printf("\n--- Resultado da Comparação ---\n");
    printf("Atributo 1: %s\n", nomeAtributo(atributo1));
    printf("Carta 1 (%s): %.2f\n", c1.nome, v1_attr1);
    printf("Carta 2 (%s): %.2f\n", c2.nome, v2_attr1);

    printf("\nAtributo 2: %s\n", nomeAtributo(atributo2));
    printf("Carta 1 (%s): %.2f\n", c1.nome, v1_attr2);
    printf("Carta 2 (%s): %.2f\n", c2.nome, v2_attr2);

    printf("\nSoma dos Atributos:\n");
    printf("Carta 1 (%s): %.2f\n", c1.nome, soma1);
    printf("Carta 2 (%s): %.2f\n", c2.nome, soma2);

    if (soma1 > soma2) {
        printf("\nResultado: Carta 1 (%s) venceu!\n", c1.nome);
    } else if (soma2 > soma1) {
        printf("\nResultado: Carta 2 (%s) venceu!\n", c2.nome);
    } else {
        printf("\nResultado: Empate!\n");
    }
}

int main() {
    Cidade carta1, carta2;

    printf("Cadastro da Carta 1:\n");
    preencherCarta(&carta1, 1);

    printf("\nCadastro da Carta 2:\n");
    preencherCarta(&carta2, 2);

    printf("\nExibindo cartas cadastradas:\n");
    exibirCarta(carta1, 1);
    exibirCarta(carta2, 2);

    compararCartas(carta1, carta2);

    return 0;
}
