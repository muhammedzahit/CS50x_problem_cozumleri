from sys import argv
alphabet = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
alphabet_lower = [letter.lower() for letter in alphabet]

def convert(plain, keyword):
    keyword = keyword.lower()
    i = 0
    len_keyword = len(keyword)
    ciphertext = []
    for letter in plain:
        if letter in [".", "," ," ", "!", "$", "?"]:
            ciphertext.append(letter)
            continue
        if not letter.islower():
            index = (alphabet.index(letter) + alphabet_lower.index(keyword[i % len_keyword] ) ) % 26
            ciphertext.append(alphabet[index])
        else:
            index = (alphabet_lower.index(letter) + alphabet_lower.index(keyword[i % len_keyword] ) ) % 26
            ciphertext.append(alphabet_lower[index])
        i += 1
    return ("".join(ciphertext))

def main():
    if len(argv) != 2 or (not argv[1].isalpha()):
        print("Usage: vigenere.py keyword")
        exit(1)

    plain = input("plaintext: ")
    ciphertext = convert(plain, argv[1])
    print("ciphertext:", ciphertext)

    exit(0)

if __name__ == "__main__":
    main()