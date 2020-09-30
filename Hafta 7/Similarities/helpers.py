from nltk.tokenize import sent_tokenize

def get_substrings(text, length):
    subs = []
    x = 0
    y = length
    while y <= len(text):
        subs.append(text[x:y])
        x += 1
        y += 1
    return subs


def lines(a, b):
    """Return lines in both a and b"""

    list_a = a.split("\n")
    list_b = b.split("\n")
    similarities = set()
    for x in list_a:
        for y in list_b:
            if x == y:
                similarities.add(x)
    return list(similarities)

def sentences(a, b):
    """Return sentences in both a and b"""
    sentences_a = sent_tokenize(a)
    sentences_b = sent_tokenize(b)
    similarities = set()
    for x in sentences_a:
        for y in sentences_b:
            if x == y:
                similarities.add(x)
    return list(similarities)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    similarities = set()
    words_a = a.split()
    words_b = b.split()
    for x, y in zip(words_a, words_b):
        subs_a = get_substrings(x, n)
        subs_b = get_substrings(b, n)
        for i in subs_a:
            for j in subs_b:
                if i == j:
                    similarities.add(i)
    return (list(similarities))