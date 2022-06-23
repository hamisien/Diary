list = []

print('print list:', list)
print('print length of list:', len(list))

list.append('hello, world!')

print('after appending string:', list)

list.insert(0, 'index option')
list.insert(0, 'icecream')
list.insert(0, 'sands')

print('after indexing sting:', list)

print('------------')
for i in list:
    print(i)
print('------------')

print(list)

print("slicing[1:3]:", list[1:3])
print("slicing[:3]:", list[:3])
print("slicing[:]:", list[:])

print("pop list:", list.pop())

print("after pop list:", list)

list.clear()

print("after clear list:", list)

copy = list
copy.append('copy')
print("copy = list")
print('copy:', copy)
print('list:', list)
list.pop()

copy = list[:]
copy.append('copy')
print("copy = list[:]")
print('copy:', copy)
print('list:', list)
