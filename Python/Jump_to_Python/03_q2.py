a = 1
total = 0

while a >= 1 and a <= 1000:
    if a % 3 == 0:
        total = total + a
    a = a + 1

print(total)
