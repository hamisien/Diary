class Cat:
    def __init__(self, name):
        self.name = name

    name = "Nyancat"
    age = 7
    health = "good"

    def nyan(self):
        print(self.name + " is meowing...")
        return

nyanCat = Cat('Nyandog')

print(nyanCat.name)
nyanCat.nyan()


class rainbowCat(Cat):
    def __init__(self):
        return
    def nyan(self):
        print(self.name + " is rainbow-colored!!")
        return


rainCat = rainbowCat() #rainbowCat 클래스의 생성자가 부모클래스의 생성자를 오버라이딩하여 name 파라메터를 받지 않음. 즉, rainbowCat()에 인자를 받지 않음.
print(rainCat.name)
rainCat.nyan()

class blackCat(Cat):
    def __init__(self, name, age):
        self.name = name
        self.age = age
        return

blkCat = blackCat('Kuroneko', 70)
print(blkCat.age)
blkCat.nyan()
