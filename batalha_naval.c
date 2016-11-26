// PIC18F4620 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

unsigned int tecla;
unsigned int municoes = 10;
unsigned char input_config[2];
unsigned char ENTER[2] = {13, 0};
unsigned int random = 0;
unsigned const int encouracados_posicoes = 5;
unsigned int encouracados_qtd = 2;
unsigned const int porta_avioes_posicoes = 6;
unsigned int porta_avioes_qtd = 1;
unsigned const int hidroavioes_posicoes = 3;
unsigned int hidroavioes_qtd = 5;
unsigned const int submarinos_posicoes = 1;
unsigned int submarinos_qtd = 4;
unsigned const int cruzadores_posicoes = 2;
unsigned int cruzadores_qtd = 3;
unsigned const int tamanho_matriz = 15;
signed int matriz[15][15];
unsigned char printLinhaColuna;
unsigned char JOGO_DA_VELHA = 35;

unsigned int getPosicao() {
    // return rand() / 2184;
    return 0;
}

unsigned int isPosicaoValida(unsigned int *linha, unsigned int *coluna, unsigned int tamanho) {
    unsigned int valorLinha = *linha;
    unsigned int valorColuna = *coluna;
    signed int valorPosicao = matriz[valorLinha][valorColuna];
    if (valorPosicao != -1) {
        (*coluna)++;
        if (*coluna > (tamanho_matriz - tamanho)) {
            *coluna = 0;
            (*linha)++;
            if (*linha > tamanho_matriz) {
                *linha = 0;
            }
        }
        return 0;
    }
    return 1;
}

struct Acertos {
    int lin;
    int col;
    int acertou;
};

struct {
    struct Acertos posicoes[encouracados_posicoes];
} encouracados[2];

struct {
    struct Acertos posicoes[porta_avioes_posicoes];
} porta_avioes[1];

struct {
    struct Acertos posicoes[hidroavioes_posicoes];
} hidroavioes[5];

struct {
    struct Acertos posicoes[submarinos_posicoes];
} submarinos[4];

struct {
    struct Acertos posicoes[cruzadores_posicoes];
} cruzadores[3];

void escreverMatriz(unsigned int linha, unsigned int coluna, unsigned char valor) {
    matriz[linha][coluna] = valor;
}

void initMatriz() {
    unsigned int i = 0;
    unsigned int j = 0;
    for (i = 0; i < tamanho_matriz; i++) {
        for (j = 0; j < tamanho_matriz; j++) {
            matriz[i][j] = -1;
        }
    }
}

void initEncouracados() {
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int linha = 0;
    unsigned int coluna = 0;
    unsigned int posicaoValida = 0;

    linha = getPosicao();
    coluna = getPosicao();
    posicaoValida = isPosicaoValida(&linha, &coluna, encouracados_posicoes);
    while (!posicaoValida) {
        posicaoValida = isPosicaoValida(&linha, &coluna, encouracados_posicoes);
    }

    for (i = 0; i < encouracados_qtd; i++) {
        for (j = 0; j < encouracados_posicoes; j++) {
            encouracados[i].posicoes[j].lin = linha;
            encouracados[i].posicoes[j].col = coluna;
            encouracados[i].posicoes[j].acertou = 0;
            escreverMatriz(linha, coluna, '0');
            coluna++;
        }
		
        if ((i + 1) < encouracados_qtd) {
			linha = getPosicao();
			coluna = getPosicao();
            posicaoValida = isPosicaoValida(&linha, &coluna, encouracados_posicoes);
            while (!posicaoValida) {
                posicaoValida = isPosicaoValida(&linha, &coluna, encouracados_posicoes);
            }
        }        
    }
}

void initPortaAvioes() {
    unsigned int i = 0;
    unsigned int linha = 0;
    unsigned int coluna = 0;
	unsigned int posicaoValida = 0;

    linha = getPosicao();
    coluna = getPosicao();	
	posicaoValida = isPosicaoValida(&linha, &coluna, porta_avioes_posicoes);
    while (!posicaoValida){
		posicaoValida = isPosicaoValida(&linha, &coluna, porta_avioes_posicoes);
	}

    for (i = 0; i < porta_avioes_posicoes; i++) {
        porta_avioes[0].posicoes[i].lin = 0;
        porta_avioes[0].posicoes[i].col = 0;
        porta_avioes[0].posicoes[i].acertou = 0;
		escreverMatriz(linha, coluna, '0');
    }
	
	if((i + 1) < porta_avioes_qtd){
		linha = getPosicao();
		coluna = getPosicao();		
		posicaoValida = isPosicaoValida(&linha, &coluna, porta_avioes_posicoes);
		while (!posicaoValida){
			posicaoValida = isPosicaoValida(&linha, &coluna, porta_avioes_posicoes);
		}
	}
}

void initHidroavioes() {
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int linha = 0;
    unsigned int coluna = 0;
	unsigned int posicaoValida = 0;

    linha = getPosicao();
    coluna = getPosicao();
	posicaoValida = isPosicaoValida(&linha, &coluna, hidroavioes_posicoes);
    while (!posicaoValida){
		posicaoValida = isPosicaoValida(&linha, &coluna, hidroavioes_posicoes);
	}

    for (i = 0; i < hidroavioes_qtd; i++) {
        for (j = 0; j < hidroavioes_posicoes; j++) {
            hidroavioes[i].posicoes[j].lin = linha;
            hidroavioes[i].posicoes[j].col = coluna;
            hidroavioes[i].posicoes[j].acertou = 0;
			escreverMatriz(linha, coluna, '0');
            coluna++;
        }
		
		if((i + 1) < hidroavioes_qtd){
		    linha = getPosicao();
			coluna = getPosicao();
			posicaoValida = isPosicaoValida(&linha, &coluna, hidroavioes_posicoes);
			while (!posicaoValida){
				posicaoValida = isPosicaoValida(&linha, &coluna, hidroavioes_posicoes);
			}
		}
    }
}

void initSubmarinos() {
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int linha = 0;
    unsigned int coluna = 0;
	unsigned int posicaoValida = 0;

    linha = getPosicao();
    coluna = getPosicao();
	posicaoValida = isPosicaoValida(&linha, &coluna, submarinos_posicoes);
    while (!posicaoValida){
		posicaoValida = isPosicaoValida(&linha, &coluna, submarinos_posicoes);
	}

    for (i = 0; i < submarinos_qtd; i++) {
        for (j = 0; j < submarinos_posicoes; j++) {
            submarinos[i].posicoes[j].lin = linha;
            submarinos[i].posicoes[j].col = coluna;
            submarinos[i].posicoes[j].acertou = 0;
			escreverMatriz(linha, coluna, '0');
            coluna++;
        }
		
		if((i + 1) < submarinos_qtd){
			linha = getPosicao();
			coluna = getPosicao();
			posicaoValida = isPosicaoValida(&linha, &coluna, submarinos_posicoes);
			while (!posicaoValida){
				posicaoValida = isPosicaoValida(&linha, &coluna, submarinos_posicoes);
			}
		}
    }
}

void initCruzadores() {
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int linha = 0;
    unsigned int coluna = 0;
	unsigned int posicaoValida = 0;

    linha = getPosicao();
    coluna = getPosicao();
	posicaoValida = isPosicaoValida(&linha, &coluna, cruzadores_posicoes);
    while (!posicaoValida){
		posicaoValida = isPosicaoValida(&linha, &coluna, cruzadores_posicoes);
	}

    for (i = 0; i < cruzadores_qtd; i++) {
        for (j = 0; j < cruzadores_posicoes; j++) {
            cruzadores[i].posicoes[j].lin = linha;
            cruzadores[i].posicoes[j].col = coluna;
            cruzadores[i].posicoes[j].acertou = 0;
			escreverMatriz(linha, coluna, '0');
            coluna++;
        }

        if((i + 1) < cruzadores_qtd){
		    linha = getPosicao();
			coluna = getPosicao();
			posicaoValida = isPosicaoValida(&linha, &coluna, cruzadores_posicoes);
			while (!posicaoValida){
				posicaoValida = isPosicaoValida(&linha, &coluna, cruzadores_posicoes);
			}
		}
    }
}

void quebraLinha() {
    // UART1_Write(13);
    // UART1_Write(10);
}

/*
 void initRandom() {
    // UART1_Write_Text("Pressione uma tecla ");
    while (1) {
        random++;
        // UART1_Read_Text(input_config, ENTER, 30);
        tecla = atoi(input_config);
        if (tecla != 255) {
           srand(random);
           break;
        }
    }
    quebraLinha();
}
 */


void imprimirMatriz(unsigned int isImprimirTelaInicial) {
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned char letra_A = 65;
    unsigned char printLetra;
    signed int valorPosicao;
    /*
    UART1_Write_Text("|   |");
    UART1_Write_Text(" 1 |");
    UART1_Write_Text(" 2 |");
    UART1_Write_Text(" 3 |");
    UART1_Write_Text(" 4 |");
    UART1_Write_Text(" 5 |");
    UART1_Write_Text(" 6 |");
    UART1_Write_Text(" 7 |");
    UART1_Write_Text(" 8 |");
    UART1_Write_Text(" 9 |");
    UART1_Write_Text(" 10 |");
    UART1_Write_Text(" 11 |");
    UART1_Write_Text(" 12 |");
    UART1_Write_Text(" 13 |");
    UART1_Write_Text(" 14 |");
    UART1_Write_Text(" 15 |");
    quebraLinha();
     */

    for (i = 0; i < tamanho_matriz; i++) {
        // UART1_Write_Text("| ");
        printLetra = letra_A + i;
        // UART1_Write(printLetra);
        // UART1_Write_Text(" |");
        for (j = 0; j < tamanho_matriz; j++) {
            valorPosicao = matriz[i][j];
            // UART1_Write(' ');
            if (valorPosicao == -1 || valorPosicao == 0 || isImprimirTelaInicial) {
                // UART1_Write('~');
            } else {
                // IntToStr(valorPosicao, printLetra);
                // UART1_Write(printLetra);
            }
            // UART1_Write_Text(" |");
        }
        quebraLinha();
    }
}

unsigned int isGanhou() {
    unsigned int total_acertos_qtd = 0;
    total_acertos_qtd = encouracados_acertos + porta_avioes_acertos + hidroavioes_acertos + submarinos_acertos + cruzadores_acertos;
    return total_acertos_qtd == 15;
}

void executarSomAcertou() {
}

void executarSomAfundou() {
}

unsigned int isAcertouEncouracado(unsigned int linha, unsigned int coluna) {
    unsigned int i = 0;
    unsigned int j = 0;
    for (i = 0; i < encouracados_qtd; i++) {
        for (j = 0; j < encouracados_posicoes; j++) {
            if (encouracados[i].posicoes[j].lin == linha &&
                    encouracados[i].posicoes[j].col == coluna &&
                    encouracados[i].posicoes[j].acertou == 0) {
                encouracados[i].posicoes[j].acertou = 1;
                return &(encouracados[i]);
            }
        }
    }
    return 0;
}

unsigned int isAfundouEncouracado(signed int *encouracadoAcertado) {
    unsigned int j = 0;
    for (j = 0; j < encouracados_posicoes; j++) {
        if (encouracados[*encouracadoAcertado].posicoes[j].acertou != 1) {
            return 0;
        }
    }
    return 1;
}

unsigned int isAcertouPortaAvioes(unsigned int linha, unsigned int coluna) {
    unsigned int i = 0;
    unsigned int j = 0;
    for (i = 0; i < porta_avioes_qtd; i++) {
        for (j = 0; j < porta_avioes_posicoes; j++) {
            if (porta_avioes[i].posicoes[j].lin == linha &&
                    porta_avioes[i].posicoes[j].col == coluna &&
                    porta_avioes[i].posicoes[j].acertou == 0) {
                porta_avioes[i].posicoes[j].acertou = 1;
                return &(porta_avioes[i]);
            }
        }
    }
    return 0;
}

unsigned int isAfundouPortaAvioes(signed int *portaAvioesAcertado) {
    unsigned int j = 0;
    for (j = 0; j < porta_avioes_posicoes; j++) {
        if (porta_avioes[*portaAvioesAcertado].posicoes[j].acertou != 1) {
            return 0;
        }
    }
    return 1;
}

unsigned int isAcertouHidroAviao(unsigned int linha, unsigned int coluna) {
    unsigned int i = 0;
    unsigned int j = 0;
    for (i = 0; i < hidroavioes_qtd; i++) {
        for (j = 0; j < hidroavioes_posicoes; j++) {
            if (hidroavioes[i].posicoes[j].lin == linha &&
                    hidroavioes[i].posicoes[j].col == coluna &&
                    hidroavioes[i].posicoes[j].acertou == 0) {
                hidroavioes[i].posicoes[j].acertou = 1;
                return &(hidroavioes[i]);
            }
        }
    }
    return 0;
}

unsigned int isAfundouHidroAviao(unsigned int *hidroAviaoAcertado) {
    unsigned int j = 0;
    for (j = 0; j < hidroavioes_posicoes; j++) {
        if (hidroavioes[*hidroAviaoAcertado].posicoes[j].acertou != 1) {
            return 0;
        }
    }
    return 1;
}

unsigned int isAcertouSubmarino(unsigned int linha, unsigned int coluna) {
    unsigned int i = 0;
    unsigned int j = 0;
    for (i = 0; i < submarinos_qtd; i++) {
        for (j = 0; j < submarinos_posicoes; j++) {
            if (submarinos[i].posicoes[j].lin == linha &&
                    submarinos[i].posicoes[j].col == coluna &&
                    submarinos[i].posicoes[j].acertou == 0) {
                submarinos[i].posicoes[j].acertou = 1;
                return &(submarinos[i]);
            }
        }
    }
    return 0;
}

unsigned int isAfundouSubmarino(unsigned int *submarinoAcertado) {
    unsigned int j = 0;
    for (j = 0; j < submarinos_posicoes; j++) {
        if (submarinos[*submarinoAcertado].posicoes[j].acertou != 1) {
            return 0;
        }
    }
    return 1;
}

unsigned int isAcertouCruzador(unsigned int linha, unsigned int coluna) {
    unsigned int i = 0;
    unsigned int j = 0;
    for (i = 0; i < cruzadores_qtd; i++) {
        for (j = 0; j < cruzadores_posicoes; j++) {
            if (cruzadores[i].posicoes[j].lin == linha &&
                    cruzadores[i].posicoes[j].col == coluna &&
                    cruzadores[i].posicoes[j].acertou == 0) {
                cruzadores[i].posicoes[j].acertou = 1;
                return &(cruzadores[i]);
            }
        }
    }
    return 0;
}

unsigned int isAfundouCruzador(unsigned int *cruzadorAcertado) {
    unsigned int j = 0;
    for (j = 0; j < cruzadores_posicoes; j++) {
        if (cruzadores[*cruzadorAcertado].posicoes[j].acertou != 1) {
            return 0;
        }
    }
    return 1;
}

void verificarJogada(unsigned int linha, unsigned int coluna) {
    signed int *encouracadoAcertado = isAcertouEncouracado(linha, coluna);
    if (*encouracadoAcertado) {
        municoes += 2;
        executarSomAcertou();
        escreverMatriz(linha, coluna, 'E');
        if (isAfundouEncouracado(&encouracadoAcertado)) {
            municoes += 3;
            executarSomAfundou();
        }
    } else {
        signed int *portaAvioesAcertado = isAcertouPortaAvioes(linha, coluna);
        if (*portaAvioesAcertado) {
            municoes += 2;
            executarSomAcertou();
            escreverMatriz(linha, coluna, 'P');
            if (isAfundouPortaAvioes(&portaAvioesAcertado)) {
                municoes += 3;
                executarSomAfundou();
            }
        } else {
            signed int hidroAviaoAcertado = isAcertouHidroAviao(linha, coluna);
            if (*hidroAviaoAcertado) {
                municoes += 2;
                executarSomAcertou();
                escreverMatriz(linha, coluna, 'H');
                if (isAfundouHidroAviao(&hidroAviaoAcertado)) {
                    municoes += 3;
                    executarSomAfundou();
                }
            } else {
                signed int submarinoAcertado = isAcertouSubmarino(linha, coluna);
                if (*submarinoAcertado) {
                    municoes += 2;
                    executarSomAcertou();
                    escreverMatriz(linha, coluna, 'S');
                    if (isAfundouSubmarino(&submarinoAcertado)) {
                        municoes += 3;
                        executarSomAfundou();
                    }
                } else {
                    signed int cruzadorAcertado = isAcertouCruzador(linha, coluna);
                    if (*cruzadorAcertado) {
                        municoes += 2;
                        executarSomAcertou();
                        escreverMatriz(linha, coluna, 'C');
                        if (isAfundouCruzador(&cruzadorAcertado)) {
                            municoes += 3;
                            executarSomAfundou();
                        }
                    } else {
                        escreverMatriz(linha, coluna, '.');
                    }
                }
            }
        }
    }

}

void main() {
    // UART1_Init(19200); // Initialize UART module at 19200 bps

    unsigned int linha;
    unsigned int coluna;

    initMatriz();
    initEncouracados();
    /*
    initPortaAvioes();
    initHidroavioes();
    initSubmarinos();
    initCruzadores();
    initRandom();

    imprimirMatriz(1);
    */
    
    // REMOVER
    verificarJogada(0, 0);

    while (municoes > 0) {

        /*
        UART1_Write_Text("Informe uma linha: ");
        while (!UART1_Data_Ready());
        UART1_Read_Text(input_config, ENTER, 30);
        UART1_Write_Text(input_config);
        linha = atoi(input_config);
        
        quebraLinha();
        
        UART1_Write_Text("Informe uma coluna: ");
        while (!UART1_Data_Ready());
        UART1_Read_Text(input_config, ENTER, 30);
        UART1_Write_Text(input_config);        
         
        if(input_config == JOGO_DA_VELHA){
           // Imprimir posicoes da matriz 
        } else {
            coluna = atoi(input_config);

            quebraLinha();
            municoes--;
            verificarJogada(linha, coluna);

            imprimirMatriz(0);        
        }
        */
    }

}
