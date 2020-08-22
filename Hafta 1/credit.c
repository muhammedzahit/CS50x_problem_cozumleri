#include <stdio.h>
#include <cs50.h>

int kac_haneli(long card,int* character){
    int hane = 0;
    while (card > 0){
        if (card > 10 && card < 100) *character = card;
        hane++; card /= 10;
    }
    return hane;
}

bool kontrol(long card){
    int a =0, b=0;
    while (card > 0){
        a += card % 10;
        card /= 10;
        if (card > 0){
            int c = (card % 10)*2;
            b += c/10;
            b += c%10;
            card /= 10;
        }
    }
    int kalan = (a+b)%10;
    if (kalan == 0) return true;
    return false;
}

int main(){

    long card = get_long("kredi karti numaranizi giriniz : ");
    if (card <= 0) card = get_long("lutfen gecerli bir kredi karti numarasi giriniz : ");
    int character = 0;
    int hane = kac_haneli(card,&character);
    if (hane < 13 || hane > 16 || hane == 14 || !kontrol(card)) printf("INVALID\n");
    else{
        if (character == 34 && hane == 15) printf("AMERICAN EXPRESS\n");
         if (character == 37 && hane == 15) printf("AMEX\n");
        else if ((character / 10 == 4) && (hane == 13 || hane == 16)) printf("VISA\n");
        else if ((character == 51 || character == 52 ||character == 53 ||character ==54 || character ==55) && hane == 16) printf("MASTERCARD\n");
        else printf("INVALID\n");
    }

}
