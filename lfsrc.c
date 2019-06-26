#include <stdio.h>
#include <stdint.h>

#define SEED 0x0000F0FA
#define NUM_INTERVALOS 16
#define FREQ_ESPERADA 1048576

uint32_t freqObservada[NUM_INTERVALOS];
double quiQuadrado = 0;

void separaIntervalos(uint32_t lfsr) {
    if (lfsr < 1000000u) {
        freqObservada[0]++;
    }
    else if (lfsr < 2000000u) {
        freqObservada[1]++;
    }
    else if (lfsr < 3000000u) {
        freqObservada[2]++;
    }
    else if (lfsr < 4000000u) {
        freqObservada[3]++;
    }
    else if (lfsr < 5000000u) {
        freqObservada[4]++;
    }
    else if (lfsr < 6000000u) {
        freqObservada[5]++;
    }
    else if (lfsr < 7000000u) {
        freqObservada[6]++;
    }
    else if (lfsr < 8000000u) {
        freqObservada[7]++;
    }
    else if (lfsr < 9000000u) {
        freqObservada[8]++;
    }
    else if (lfsr < 10000000u) {
        freqObservada[9]++;
    }
    else if (lfsr < 11000000u) {
        freqObservada[10]++;
    }
    else if (lfsr < 12000000u) {
        freqObservada[11]++;
    }
    else if (lfsr < 13000000u) {
        freqObservada[12]++;
    }
    else if (lfsr < 14000000u) {
        freqObservada[13]++;
    }
    else if (lfsr < 15000000u) {
        freqObservada[14]++;
    }
    else if (lfsr < 16000000u) {
        freqObservada[15]++;
    }
}

void calculaQuiQuadrado() {
    double freqEsperada = FREQ_ESPERADA;
    printf("Frequencia esperada: %lf\n", freqEsperada);
    for (int i = 0; i < NUM_INTERVALOS; i++) {
        double aux = (freqObservada[i] - freqEsperada);
        quiQuadrado += (aux*aux) / freqEsperada;
    }
}

int randNASM(uint32_t lfsr);

int main () {
    uint32_t lfsr = SEED;
    uint32_t bit;
    uint32_t cnt = 0;

    printf("\n--------- C --------\n\n");


    for (int i = 0; i < NUM_INTERVALOS; i++) {
        freqObservada[i] = 0;
    }

    do {
        bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ^ (lfsr >> 7) ^ (lfsr >> 13)) & 1u;
        lfsr = (lfsr >> 1) | (bit << 23);
        lfsr &= 0x00FFFFFF;
        separaIntervalos(lfsr);
        cnt++;
    } while(cnt < 16000000);

    for (int i = 0; i < NUM_INTERVALOS; i++) {
        printf("[%02d] %u\n", i+1, freqObservada[i]);
    }

    calculaQuiQuadrado();
    printf("Qui-Quadrado: %lf\n", quiQuadrado);

    /************************************************ Parte do NASM *****************************************/
    printf("\n--------- NASM --------\n\n");

    lfsr = SEED;
    cnt = 0;
    for (int i = 0; i < NUM_INTERVALOS; i++) {
        freqObservada[i] = 0;
    }

    do {
        lfsr = randNASM(lfsr);
        separaIntervalos(lfsr);
        cnt++;
    } while(cnt < 16000000);

    for (int i = 0; i < NUM_INTERVALOS; i++) {
        printf("[%02d] %u\n", i+1, freqObservada[i]);
    }

    quiQuadrado = 0;
    calculaQuiQuadrado();

    printf("Qui-Quadrado: %lf\n", quiQuadrado);

    return 0;
}