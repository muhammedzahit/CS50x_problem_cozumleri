from cs50 import get_string
from sys import argv

def sansurle(text):
    sansur = []
    for i in range(len(text)):
        sansur.append("*")
    return "".join(sansur)

def main():

    if len(argv) != 2:
        print("Usage: python bleep.py dictionary")
        exit(1)

    with open(argv[1],"r") as file:
        string = input("What message would you like to censor: ")
        texts = string.split()
        for i in range(len(texts)):
            for j in file:
                if j.strip("\n") == texts[i].lower():
                    texts[i] = sansurle(texts[i])
                    break
            # dosyanın başına döndük
            file.seek(0)
        print(" ".join(texts))

    exit(0)

if __name__ == "__main__":
    main()
