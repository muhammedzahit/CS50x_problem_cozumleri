#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct block{
    unsigned char bytes[512];
};

struct jpeg
{
    struct block blocks[2000];
};

struct image
{
    struct jpeg jpegs[50];
};

void assign(unsigned char a[],unsigned char b[])
{
    for (int i=0; i<512; i++)
    {
        b[i] = a[i];
    }
}

int check(char string[],int len)
{
    int write = 0;
    char name[10];
    int k = 0;
    for (int i=0; i<len; i++)
    {
        if (string[i] == '.') write = 1;
        if (write)
        {
            name[k++] = string[i];
        }
    }
    name[k] = '\0';
    char usage[5] = ".raw";
    if (strcmp(name,usage) == 0) return 1;
    return 0;
}

int controlJPEG(unsigned char b[])
{
    return (b[0] == 0xff && b[1] == 0xd8 && b[2] == 0xff && (b[3] & 0xf0) == 0xe0);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage dir\n");
        return 1;
    }
    if (!check(argv[1],strlen(argv[1])))
    {
        printf("usage .raw file\n");
        return 2;
    }
    FILE *file;
    file = fopen(argv[1],"r");
    if (!file)
    {
        printf("file can not opened\n");
        return 3;
    }
    int find = 0;
    int first = 0;
    struct image *images = malloc(sizeof(struct image));
    int blockNum = 0;
    int jpegNum = 0;
    int sizes[50];
    while(!feof(file))
    {
        struct block block1;
        if(fread(&block1.bytes,1,512,file) != 512) break ;
        if (controlJPEG(block1.bytes))
        {
            if (first)
            {
                printf("find another %d\n",blockNum);
                jpegNum++;
                blockNum = 0;
                assign(block1.bytes,images->jpegs[jpegNum].blocks[blockNum++].bytes) ;
            }
            else
            {
                assign(block1.bytes,images->jpegs[jpegNum].blocks[blockNum++].bytes) ;
                if (!first) first = 1;
            }
            find = 1;
        }
        else if (find)
        {
            assign(block1.bytes,images->jpegs[jpegNum].blocks[blockNum++].bytes) ;
            sizes[jpegNum] = blockNum;
        }
        
    }
    
    
    
    for (int i=0; i<=jpegNum; i++)
    {
        char fileName[20];
        sprintf(fileName,"%03i.jpg",i);
        FILE *img = fopen(fileName,"w");
        for (int j = 0; j < sizes[i]; j++)
             fwrite(images->jpegs[i].blocks[j].bytes,512,1,img);
        fclose(img);
    }
    

    fclose(file);

}
