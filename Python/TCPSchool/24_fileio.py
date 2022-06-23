fp = open('fileio.txt', 'w+')
fp.write("Hello, world!\n안녕 세상!\n")
fp.seek(0)
print(fp.read())
fp.close()

with open('fileio.txt', 'at+') as fp2:
    fp2.write("Hell, world!\n지옥같은 세상!")
    fp2.seek(0)
    print(fp2.read())
