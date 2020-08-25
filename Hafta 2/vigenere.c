#include <cs50.h>
#include <stdio.h>
#include <string.h>
bool sayiMi(char text[],const int size)
{
    for (int i = 0 ; i < size ; i++)
    {
        if (text[i] >= '0' && text[i] <= '9') return true;
    }
    return false;
}
int keyKontrol(char key){
    if (key >= 'A' && key <= 'Z')
    {
        return key - 'A';
    }
    return key - 'a';
}
void sifrele(char text[],const string keyword,const int size,const int keywordSize)
{

    int a = 0;
    for (int i = 0; i < size; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            char key = keyword[(a++) % keywordSize];
            int key2 = ((text[i] - 'A') + keyKontrol(key)) % 26;
            text[i] = 'A' + key2;
        }
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            char key = keyword[(a++) % keywordSize];
            int key2 = ((text[i] - 'a') +  keyKontrol(key)) % 26;
            text[i] = 'a' + key2;
        }
        else continue;
    }
}
int main(int argc, string argv[])
{
    
    if (argc != 2 || sayiMi(argv[1],strlen(argv[1])))
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    const int keywordSize = strlen(argv[1]);
    string plainText = get_string("plaintext : ");
    sifrele(plainText,argv[1],strlen(plainText),keywordSize);
    printf("ciphertext: %s\n",plainText);
}
