f = open("test.txt", 'a')
str = input("Input Any values: ")
f.write(str)
f.close()

f = open("test.txt", 'r')
print(f.read())
f.close()
