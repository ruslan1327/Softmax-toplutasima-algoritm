//Ad-Soyad: RUSLAN ZHUMAYEV
//Öðr. No: 5230505113

#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

#define MAHALLE_SAYISI 3
#define KRITER_SAYISI 5

typedef struct {
    char* isim;
    
    double kriterler[KRITER_SAYISI];
    double agirlikli_skor;
    double softmax_skor;
} Mahalle;

   //Softmax fonksiyonu
void softmax(Mahalle mahalleler[], int n) {
    double max_skor = mahalleler[0].agirlikli_skor;
    for (int i = 1; i < n; i++) {
        if (mahalleler[i].agirlikli_skor > max_skor) {
            max_skor = mahalleler[i].agirlikli_skor;
        }
    }

    double toplam = 0.0;
    for (int i = 0; i < n; i++) {
        mahalleler[i].softmax_skor = exp(mahalleler[i].agirlikli_skor - max_skor);
        toplam += mahalleler[i].softmax_skor;
    }

    for (int i = 0; i < n; i++) {
        mahalleler[i].softmax_skor /= toplam;
    }
}

int main() {
    Mahalle mahalleler[MAHALLE_SAYISI] = {
        {"Merkez", {0}},
        {"Karakas", {0}},
        {"Pinar", {0}}
    };

  // Rastgele veri oluþturma
    srand(0);
    for (int i = 0; i < MAHALLE_SAYISI; i++) {
        for (int j = 0; j < KRITER_SAYISI; j++) {
            mahalleler[i].kriterler[j] = (rand() % 100) / 10.0;
        }
    }

  // Aðýrlýklar
    double agirliklar[KRITER_SAYISI] = {0.3, 0.25, 0.2, 0.15, 0.1};
  
  // Aðýrlýklý skor hesaplama
    for (int i = 0; i < MAHALLE_SAYISI; i++) {
        mahalleler[i].agirlikli_skor = 0;
        for (int j = 0; j < KRITER_SAYISI; j++) {
            mahalleler[i].agirlikli_skor += mahalleler[i].kriterler[j] * agirliklar[j];
        }
    }

   // Softmax uygula
    softmax(mahalleler, MAHALLE_SAYISI);

    printf("Mahalle Skorlari:\n");
    for (int i = 0; i < MAHALLE_SAYISI; i++) {
        printf("%s: %.2f\n", mahalleler[i].isim, mahalleler[i].softmax_skor);
    }

  // En uygun güzergahý belirleme
    int en_uygun_index = 0;
    for (int i = 1; i < MAHALLE_SAYISI; i++) {
        if (mahalleler[i].softmax_skor > mahalleler[en_uygun_index].softmax_skor) {
            en_uygun_index = i;
        }
    }

    printf("\nEn uygun guzergah: %s\n", mahalleler[en_uygun_index].isim);
    return 0;
}
