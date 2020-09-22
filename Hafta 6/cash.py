from cs50 import get_float
bozukluklar = [25,10,5,1]

def kac_tane(para):
    sayi = 0
    for bozukluk in bozukluklar:
        sayi += para // bozukluk
        para %= bozukluk
    return int(sayi)

para = get_float("Para ustunu giriniz:")
while para < 0:
    para = get_float("Para ustunu giriniz:")
para *= 100
print(kac_tane(para))