dict1 = {
        'cpu':"i5-6600",
        'vga':"GTX1070Ti", 
        'mem':16,
        'ssd':512,
        'ps':500,
        }

dict2 = dict({'씨피유':6600, '지피유':'1070Ti', '메모리':16.0, 'SSD':512, 'PS':500})

dict3 = dict([('CPU', 6600), ('VGA', '1070Ti')])

dict4 = dict(하나=1, 둘=2, 삼='sam', 넷='four')

print(dict1)
print(dict2)
print(dict3)
print(dict4)


dict5 = {('ten', 10): ['열', 10.0]} #되나?
print(dict5)

print(dict1.get('cpu'))
print(dict1['cpu'])

print(dict1.get('hell'))
# print(dict1['hell']) #오류발생

mydict = {}
print()
print('mydict = ', mydict)
mydict['init'] = 'macbook'
print('mydict["init"]="macbook"', mydict)

del mydict['init']
print("after del mydict['init'] -> ", mydict)

print(dict1.keys())
print(dict1.values())
print(dict1.items())

print('cpu' in dict1)
print('cpa' in dict1)
