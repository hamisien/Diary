import sys

total = 0
arguments = sys.argv
for i in range(1, len(arguments)):
    total += int(arguments[i]) 
print(total)
