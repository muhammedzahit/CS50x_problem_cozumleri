#include <stdio.h>
#include <cs50.h>

void hesapla(int* kacTane,int para_ustu){
    if (para_ustu / 25){
        *kacTane += (para_ustu / 25);
        para_ustu = para_ustu % 25;
    }
    if (para_ustu / 10){
        *kacTane += (para_ustu / 10);
        para_ustu = para_ustu % 10; 
    }
    if (para_ustu / 5){
        *kacTane += (para_ustu / 5);
        para_ustu = para_ustu % 5; 
    }
    if (para_ustu / 1){
        *kacTane += (para_ustu / 1);
        para_ustu = para_ustu % 1; 
    }
}

int main(){
    double a = get_double("Para ustunu girin : ");
    if (a < 0) a = get_double("Pozitif bir para ustunu girin : ");
    int b = a * 100;
    int c = 0;
    hesapla(&c,b);
    printf("%d\n",c);
}
