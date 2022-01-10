def avg(*args):
    total = 0
    for arg in args:
        total += arg
    avg = total / len(args)
    return avg

print(avg(1, 2, 3, 4, 5, 6, 7, 8, 9, 10))
