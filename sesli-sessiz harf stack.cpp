#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 
struct node {
    char data;
    struct node *next;
    struct node *prev;
};

struct node *top = NULL;

 
struct node *nodeOlustur(char value) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = newNode->prev = NULL;
    return newNode;
}
 
void push(char value) {
    struct node *newNode = nodeOlustur(value);
    if (top != NULL) {
        newNode->next = top;
        top->prev = newNode;
    }
    top = newNode;
}

 
 
char pop() {
    if (top == NULL) {
        return '\0';  
    }

    char poppedValue = top->data;
    struct node *temp = top;
    top = top->next;
    if (top != NULL) {
        top->prev = NULL;
    }
    free(temp);
    return poppedValue;
}

 int isVowel(char harf) {
    
    return ( harf == 'a' || harf == 'e' || harf == 'i' || harf == 'o' || harf == 'u');
}
 
 int ayniTipMi() {
    if (top == NULL || top->next == NULL) {
        return 0;  
    }

    char topData = top->data;
    char nextData = top->next->data;

      
 if ((isVowel(topData) && isVowel(nextData)) || (!isVowel(topData) && !isVowel(nextData))) {
        return 1;  
    } else {
        return 0;  
    }
} 
 

int main() {
 char harfler[10];
     char sessiz[] = "bcdfghjklmnpqrstvwxyz";
        char sesli[] = "aeiou";
        srand(time(0));
   int i;
      for (i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            harfler[i] = sesli[rand() % 5];
        } else {
            harfler[i] = sessiz[rand() % 21];
        } 
    }

      //Oluþturduðum diziyi karýþtýrýyorum
         for (int i = 9; i > 0; i--) { 
        int j = rand() % (i + 1);
        char temp = harfler[i];
        harfler[i] = harfler[j];
        harfler[j] = temp;
    }

 
    printf("  Dizi: ");
    for (int i = 0; i < 10; i++) {
        printf("%c ", harfler[i]);
    }
    printf("\n");
    
    
       int elemanSayisi = 0;
      do{
	  
        for (i = 0; i < 10; i++) {
            char mevcutHarf = harfler[i];
        
		    push(mevcutHarf);
         
     if( ayniTipMi()==0) {
 	  
          elemanSayisi++;
           if(elemanSayisi==6){
           	break;
		   }
    }
   if(ayniTipMi()==1) {
                
                pop();
            }
	  }
	  
}while(elemanSayisi<6);
      
                
 

  printf("Stack: ");
    while (top != NULL) {
        printf("%c ", pop());
    }
    printf("\n");

    return 0;
}

