#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLO_BOYUTU 10

typedef struct Node {
    int takipNo;
    char gonderici[100];
    char alici[100];
    char kargoDurum[100];
    struct Node *next;
} Kargo;

Kargo *hashtablo[TABLO_BOYUTU];

void hashtablosu() {
    for (int i = 0; i < TABLO_BOYUTU; i++) {
        hashtablo[i] = NULL;
    }
}

int hashHesapla(int takipNo) {
    return takipNo % TABLO_BOYUTU;
}

int HashHesapla2(int takipNo, int deneme) {
    int konum1 = hashHesapla(takipNo);
    int konum2 = 7 - (takipNo % 7);
    return (konum1 + deneme * konum2) % TABLO_BOYUTU;
}

 

 void dosyadanOku() {
    FILE *dosya = fopen("kargo.txt", "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

    int takipNo;
    char gonderici[100], alici[100], kargoDurum[100];

    while (fscanf(dosya, "%d %99[^ ] %99[^ ] %99[^\n]\n", &takipNo, gonderici, alici, kargoDurum) != EOF) {
        int indeks = hashHesapla(takipNo);

        if (hashtablo[indeks] == NULL) {
            Kargo *yeniKargo = (Kargo *)malloc(sizeof(Kargo));
            yeniKargo->takipNo = takipNo;
            strcpy(yeniKargo->gonderici, gonderici);
            strcpy(yeniKargo->alici, alici);
            strcpy(yeniKargo->kargoDurum, kargoDurum);
            yeniKargo->next = NULL;
            hashtablo[indeks] = yeniKargo;
            printf("%d takip nolu kargo %d. indekse eklendi.\n", takipNo, indeks);
        } else {
            int deneme = 1;
            while (1) {
                int konum2 = HashHesapla2(takipNo, deneme);
         

                if (hashtablo[konum2] == NULL) {
                    Kargo *yeniKargo = (Kargo *)malloc(sizeof(Kargo));
                    yeniKargo->takipNo = takipNo;
                    strcpy(yeniKargo->gonderici, gonderici);
                    strcpy(yeniKargo->alici, alici);
                    strcpy(yeniKargo->kargoDurum, kargoDurum);
                    yeniKargo->next = NULL;
                    hashtablo[konum2] = yeniKargo;
                    printf("%d takip nolu kargo %d. indekse eklendi.\n", takipNo, konum2);
                    break;
                }
                deneme++;

                if (deneme >= TABLO_BOYUTU) {
                    printf("Tablo dolu!\n");
                    break;
                }
            }
        }
    }

    fclose(dosya);
}



void insertKargo(int takipNo, char *gonderici, char *alici, char *kargoDurumu) {
    Kargo *KargoDugumu = (Kargo *)malloc(sizeof(Kargo));

    KargoDugumu->takipNo = takipNo;
    strcpy(KargoDugumu->gonderici, gonderici);
    strcpy(KargoDugumu->alici, alici);
    strcpy(KargoDugumu->kargoDurum, kargoDurumu);
    KargoDugumu->next = NULL;

    int konum = hashHesapla(takipNo);

    if (hashtablo[konum] == NULL) {
        hashtablo[konum] = KargoDugumu;
        printf("%d: Hash tablosunun %d. indeksine eklendi.\n", takipNo, konum);
    } else {
        int deneme = 1;
        while (1) {
            int konum2 = HashHesapla2(takipNo, deneme);
            if (hashtablo[konum2] == NULL) {
                hashtablo[konum2] = KargoDugumu;
                printf("%d: Hash tablosunun %d. indeksine eklendi.\n", takipNo, konum2);
                break;
            }
            deneme++;

            if (deneme >= 10) {
                printf("Tablo dolu!\n");
                free(KargoDugumu);
                break;
            }
        }
    }
}

 
  void dosyaya_yaz() {
    FILE *dosya = fopen("kargo.txt", "a");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        return;
    }

     
    for (int i = 0; i < TABLO_BOYUTU; i++) {
        if (hashtablo[i] != NULL) {
            fprintf(dosya, "%d\t%s\t%s\t%s\n", hashtablo[i]->takipNo, hashtablo[i]->gonderici,
                    hashtablo[i]->alici, hashtablo[i]->kargoDurum);
        }
    }

    fclose(dosya);
}






   void listele() {
   	
    printf("-- Tum Kargolar --\n");
    printf("Takip No-Gonderici-Alici-Kargo Durumu\n");

    for (int i = 0; i < TABLO_BOYUTU; i++) {
        if (hashtablo[i] != NULL) {
            printf("%d\t%s\t%s\t%s\n", hashtablo[i]->takipNo, hashtablo[i]->gonderici,
                    hashtablo[i]->alici, hashtablo[i]->kargoDurum);
        }
    }
}


 void kargoSil(int silinecekTakipNo) {
 		 	
    int indeks = hashHesapla(silinecekTakipNo);
    int deneme = 0;
     if (hashtablo[indeks]->takipNo == silinecekTakipNo){
     	  free(hashtablo[indeks]);  
     	 hashtablo[indeks] = NULL; 
     	 printf("%d takip no'lu kargo teslim edildi.\n", silinecekTakipNo);
	 }
	 else {
            int deneme = 1;
            while (1) {
                int konum2 = HashHesapla2(silinecekTakipNo, deneme);
                if (hashtablo[konum2]->takipNo  == silinecekTakipNo) {
                	 free(hashtablo[konum2]);  
     	       hashtablo[konum2] = NULL; 
     	       printf("%d takip no'lu kargo teslim edildi.\n", silinecekTakipNo);
     	       break;
	 }
	 deneme++;
       }
         if (deneme >= TABLO_BOYUTU) {
          printf("Takip numarasi %d olan kargo bulunamadi, teslim edilemedi.\n", silinecekTakipNo);                     
	 
                }

 	
 }
}
void kargoTakip(int arananTakipNo) {
	int deneme = 0;
    int indeks = hashHesapla(arananTakipNo);
      if (hashtablo[indeks]->takipNo==arananTakipNo){
      	   printf("Takip numarasi %d, %d adimda bulundu.\n", arananTakipNo, deneme);
      	     printf("Kargo Bilgileri:\n");
        printf("Takip No: %d\nGonderici: %s\nAlici: %s\nKargo Durumu: %s\n",
               hashtablo[indeks]->takipNo, hashtablo[indeks]->gonderici,
               hashtablo[indeks]->alici, hashtablo[indeks]->kargoDurum);
			 }
			 
			 else{
			 	 int deneme = 1;
            while (1) {
                int konum2 = HashHesapla2(arananTakipNo, deneme);
                if (hashtablo[konum2]->takipNo  == arananTakipNo) {
                	  printf("Takip numarasi %d, %d adimda bulundu.\n", arananTakipNo, deneme);
                   printf("Kargo Bilgileri:\n");
        printf("Takip No: %d\nGonderici: %s\nAlici: %s\nKargo Durumu: %s\n",
               hashtablo[konum2]->takipNo, hashtablo[konum2]->gonderici,
               hashtablo[konum2]->alici, hashtablo[konum2]->kargoDurum);
     	       break;
	 }
	 deneme++;
       }
			 	
			 
			   if (deneme >= TABLO_BOYUTU) {
          printf("Takip numarasi %d olan kargo bulunamadi.", arananTakipNo);                     
	 
                }
      	
	  }
}

 
int main() {
	int secim;
	do {
        printf("\n-- Kargo Takip Sistemi --\n");
        printf("0 - Textten veri girisi yap\n");
        printf("1 - Tum kategorileri listele\n");
        printf("2 - Kargo girisi\n");
        printf("3 - Kargo takip\n");
        printf("4 - Kargoyu teslim et\n");
        printf("5 - Cikis\n");
        printf("Seciminizi girin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 0:
                
          hashtablosu();
          dosyadanOku();
                break;
            
			
			case 1:
          
		   listele();  
        
		      break;
                
                
            case 2:
                 
    int takipNo;
    char gonderici[100], alici[100], kargoDurumu[100];

    printf("Takip Numarasi: ");
    scanf("%d", &takipNo);
    printf("Gonderici: ");
    scanf("%s", gonderici);
    printf("Alici: ");
    scanf("%s", alici);
    printf("Kargo Durumu: ");
    scanf("%s", kargoDurumu);

    insertKargo(takipNo, gonderici, alici, kargoDurumu);
				   
                break;
            
			
			case 3:

            				
       int arananTakipNo;
       printf("Aranacak kargonun takip numarasini girin: ");
       scanf("%d", &arananTakipNo);
      kargoTakip(arananTakipNo); 
                break;
			
			
		    case 4:
        
		int silinecekTakipNo;
       printf("Teslim edilecek kargonun takip numarasini girin: ");
       scanf("%d", &silinecekTakipNo);
       kargoSil(silinecekTakipNo);
	          break;
           
		    case 5:
            	
        printf("Cikis yapildi.\n");
                break;
            default:
                printf("Gecersiz secim! Lutfen tekrar deneyin.\n");
                break;
        }

    } while (secim != 5);


    return 0;
}

