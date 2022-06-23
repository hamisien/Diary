set1 = {} #initiated to dict
set2 = {0, 1, 2, 3} #set
set3 = {"Hello"}
set4 = set("World")

print(set1)
print(set2)
print(set3)
print(set4)

print(type(set1), type(set2), type(set3), type(set4))

set4.add('A')
print(set4)

set4.remove('W')
print(set4)

set4.update('C', 'D', 'E', 'F', 'G', 'A', 'B')
print(set4)

print()

print(set3 | set4)
print(set3 & set4)
print(set3 - set4)
print(set3 ^ set4)
