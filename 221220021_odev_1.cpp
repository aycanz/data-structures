#include <stdio.h>
#include <stdlib.h>

//  
struct Ogrenci {
    int numara;
    char ad[50];
    char soyad[50];
    struct Ogrenci* next;
};

 
struct Ogrenci* bas = NULL;

//  
void Ekle(int numara, char ad[], char soyad[]) {
	
	 if (bas != NULL) {
        struct Ogrenci* temp = bas;
        while (temp != NULL) {
            if (temp->numara == numara) {
                printf("Ayný numaraya sahip kayýt eklenemez.\n");
                return;
            }
              
            temp = temp->next;
        }
    }
    struct Ogrenci* yeniOgrenci = (struct Ogrenci*)malloc(sizeof(struct Ogrenci));
        yeniOgrenci->numara = numara;
    for (int i = 0; i < 50; i++) {
        yeniOgrenci->ad[i] = ad[i];
        yeniOgrenci->soyad[i] = soyad[i];
    }
    yeniOgrenci->next = bas;
    bas = yeniOgrenci;
     
    
}

//
void sil(int silinecekNumara){
	 struct Ogrenci* onceki = NULL;
            struct Ogrenci* temp = bas;
            int siradaki = 1;
            int silindi = 0;

            while (temp != NULL) {
                if (temp->numara == silinecekNumara) {
                    silindi = 1;
                    if (onceki == NULL) {  
                        bas = temp->next; 
                    } else {
                       onceki->next = temp->next; 
                    }
                  
                    free(temp);
                    printf("%d. siradaki ogrenci silindi.  \n", siradaki);
                    break;
                }
                onceki = temp; 
                temp = temp->next;
                siradaki++;
            }

            if (silindi==0) {
                printf("Silinecek ogrenci bulunamadi.\n");
            }
}




 
 void Listele() {
    struct Ogrenci* temp = bas;
    while (temp != NULL) {
        printf("%d#%s#%s\n", temp->numara, temp->ad, temp->soyad);
        temp = temp->next;
    }
}

int karsilastir(char* soyad1, char* soyad2) {
    while (*soyad1 != '\0' && *soyad2 != '\0' && *soyad1 == *soyad2) {
     
        soyad1++;
        soyad2++;
       
    }

    if (*soyad1 == '\0' && *soyad2 == '\0') {
    }  else {
        return -1;  
    }
}

int ListeUzunlugu() {
    struct Ogrenci* temp = bas;
    int uzunluk = 0;
    while (temp != NULL) {
        uzunluk++;
        temp = temp->next;
    }
    return uzunluk;
}
 
  
 //
 void tasima(int numara, int sira) {
 	
    int uzunluk = ListeUzunlugu();

    if (sira< 1 || sira> uzunluk ) {
        printf("Liste boyutu disinda bir deger girdiniz.\n");
        return;
    }
    
     struct Ogrenci* temp = bas;
    struct  Ogrenci* onceki = NULL;

    while (temp != NULL && temp->numara != numara) {
        onceki = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Aranilan kayit bulunamadi.\n");
        return;
    }

    if (onceki != NULL) {
        onceki->next = temp->next;
    } else {
        bas = temp->next;
    }

    if (sira == 1) {
        temp->next = bas;
        bas = temp; //basa eleman ekleme kuralý
    } else {
        struct  Ogrenci* gecici = bas;
        for (int i = 1; i < sira - 1; i++) {
            gecici = gecici->next;//sýradan bir öncesine kadar gidilir    1 4 2 3
        }
        temp->next = gecici->next;
        gecici->next = temp;
    }

    printf("Kayit tasindi.\n");

}
//
     void arama(char* arananSoyad){
      
            int bulundu = 0;
     	  struct Ogrenci* temp = bas;
             int siradaki = 1;   
           while (temp != NULL) {
          if (karsilastir(temp->soyad, arananSoyad) == 0) {
               bulundu = 1;
              printf(" ->> %s %s \n", temp->ad, temp->soyad);
              char cevap;
                printf("aranan ogrenci bulundu mu ?(e/h)");
                 scanf(" %c",&cevap);
                     
			if (cevap == 'e' || cevap == 'E') {
                   printf("kayit %d. sirada bulundu: %d#%s#%s \n",  siradaki,temp->numara, temp->ad, temp->soyad);
                   break;
            }
            
        else if (cevap == 'h' || cevap == 'H') {
        int devamEt = 1;
        while (devamEt) {
          temp = temp->next;
           siradaki++;
        if (temp == NULL) {
            printf("Ayni soyadlý baska ogrenci bulunamadý.\n");
            break;
        }
        if (karsilastir(temp->soyad, arananSoyad) == 0) {
            printf(" ->> %s %s \n", temp->ad, temp->soyad);
            printf("aranan ogrenci bulundu mu (e/h) ? ");
            scanf(" %c", &cevap);
            if (cevap == 'e' || cevap == 'E') {
                printf("kayit %d. sirada bulundu: %d#%s#%s \n", siradaki, temp->numara, temp->ad, temp->soyad);
                break;
            }
		 }
        }
      }
  else {
    printf("Geçersiz cevap.Lütfen 'e', 'E', 'h' veya 'H' girin.\n");
      }
             }
             
           temp = temp->next;
               siradaki++;
         }
             if (!bulundu) {
                printf("Aranan kayit bulunamadi.\n");
            }
     	
	 }


 

int main() {
     FILE* dosya = fopen("veriler.txt", "r");
    if (dosya == NULL) {
        printf("Dosya acilirken hata olustu.\n");
        return 1;
    }

    int numara;
    char ad[50];
    char soyad[50];

    while (fscanf(dosya, "%d#%49[^#]#%49[^\n]\n", &numara, ad, soyad) == 3) {
        Ekle(numara, ad, soyad);
    }

    fclose(dosya);

    int secim;
    while (1) {
        printf("\nYapmak istediginiz islemi secin:\n");
        printf("1. Listeleme\n");
        printf("2. Ekleme\n");
        printf("3. Arama\n");
        printf("4. Silme\n");
        printf("5. Tasima\n");
        printf("6. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        if (secim == 1) {
            printf("Bagli listedeki ogrenciler:\n");
            Listele();
            }
            
			 else if (secim == 2) {
            int yeniNumara;
            char yeniAd[50];
            char yeniSoyad[50];

            printf("Yeni ogrenci bilgilerini girin:\n");
            printf("Numara: ");
            scanf("%d", &yeniNumara);
            printf("Ad: ");
            scanf("%s", yeniAd);
            printf("Soyad: ");
            scanf("%s", yeniSoyad);

 
             Ekle(yeniNumara, yeniAd, yeniSoyad);
           
        } 
		
		else if (secim == 3) {
			
            char arananSoyad[50];
            int bulundu = 0;
            printf("Aranacak soyadi girin: ");
            scanf("%s", arananSoyad);
          arama(arananSoyad);
        } 
        
        
        
		else if (secim == 4) {
            int silinecekNumara;
            printf("Silinecek ogrencinin numarasini girin: ");
            scanf("%d", &silinecekNumara);

           sil(silinecekNumara);
        } 
		
		
		
		else if (secim == 5) {
            int tasinanNumara;
            int hedefSira;
            printf("Tasinacak ogrencinin numarasini ve hedef sira numarasini girin: ");
            scanf("%d %d", &tasinanNumara, &hedefSira);

                 tasima(tasinanNumara,hedefSira);
                 }
                 
                 
		 else if (secim == 6) {
           
            FILE* dosya = fopen("veriler.txt", "w");
            struct Ogrenci* temp = bas;
            while (temp != NULL) {
                fprintf(dosya, "%d#%s#%s\n", temp->numara, temp->ad, temp->soyad);
                temp = temp->next;
            }
            fclose(dosya);
            printf(" Dosya guncellendi ve cikis yapildi.\n");
            break;
        } else {
            printf("Gecersiz islem.\n");
        }
    }

  
    while (bas != NULL) {
        struct Ogrenci* silinecek = bas;
        bas = bas->next;
        free(silinecek);
    }
 
    return 0;
}

