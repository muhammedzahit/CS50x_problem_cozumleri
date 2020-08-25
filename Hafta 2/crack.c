#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <crypt.h>

char harfDondur(int key){
    if (key == 0) return 'a';
    else key--;
    if (key < 26) return 'a' + key;
    return 'A' + (key % 26);
}

int basamak (int sayi){
    int k = 53;
    int basamak = 1;
    while (sayi > k){
        basamak++;
        k *= 53;
    }
    return basamak;

}

void kontrol(int sayi,char sifre[],int size){
    int k = 1;
	
    for (int i=0; i<size-1 ; i++)
    k *= 53;
		
    for (int i=0; i<size; i++)
    {
	sifre[i] =  harfDondur((sayi/k) % 53);
	k /= 53;
    }
}

bool hashKontrol(string a,string b)
{
    for (int i=0; i<13 ; i++)
    {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
    }
    else 
    {
        char salt[3];
        salt[0] = argv[1][0];
        salt[1] = argv[1][1];
	salt[2] = '\0';
        //printf("%s",crypt("LAF",salt));
        int passwordNum = 0;
        for (int i=1; i<(53*53*53*53*53) ; i++)
	{
            int size = basamak(i);
	    char sifre[size+1];	
	    sifre[size] = '\0';
	    kontrol(i,sifre,size);
            string hash2 = crypt(sifre,salt);
            if (hashKontrol(argv[1],hash2))
            {
                passwordNum = i;
                printf("%d\n",passwordNum);
                break;
            }
        }
        int size = basamak(passwordNum);
	char password[size+1];
	password[size] = '\0';
        kontrol(passwordNum,password,size);
        printf("%s\n",password);
    }
    
}

/*
    ORNEK SİFRELER:
    ATAM : 50K6v0paBlyx2
    LOL :  50cI2vYkF0YU2
    CRACK : 502xg9uaUHtkI (kodun bu ornegi bulması biraz uzun sürüyor. yaklaşık 10-15 dk)
    AT : 50fXBl4nfF3Jc
    LAF : 509Ho.lzyjgok1477
*/
