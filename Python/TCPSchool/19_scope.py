def func():
    global var
    var = 30
    return

var = 10
print(var)

func()

print(var)
