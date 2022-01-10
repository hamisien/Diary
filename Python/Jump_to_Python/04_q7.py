f = open("test.txt", 'r')
str = f.read()
f.close()

str.replace('java', 'python')
f = open("test.txt", 'w')
f.write(str)
f.close()

f = open("test.txt", 'r')
print(f.read())
f.close()
