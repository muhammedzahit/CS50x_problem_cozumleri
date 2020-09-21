from cs50 import get_int
def harfYaz(harf, tekrar):
    for j in range(tekrar):
        print(harf,end="")

yukseklik = get_int("Yukseklik:")
while yukseklik < 1 or yukseklik > 8:
    yukseklik = get_int("Yukseklik:")
yildiz_sayisi = 1
bosluk_sayisi = yukseklik-1

for i in range(yukseklik):
    harfYaz(" ",bosluk_sayisi)
    harfYaz("#",yildiz_sayisi)
    print("  ",end="")

    harfYaz("#",yildiz_sayisi)
    print()

    bosluk_sayisi -= 1
    yildiz_sayisi += 1