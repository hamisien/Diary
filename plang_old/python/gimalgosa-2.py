J = 0; i = 0; K = 0; KEY = 0; A = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0] #변수선언과 초기화

for J in range(1, 10, 1):
    A[J] = int(input(str(J)+'번째 정수를 입력하십시오: '))

for i in range(2, 10, 1):
    KEY = A[i] #①
    for K in range(i-1, 1, -1):
        if A[K] > KEY:
            A[K+1] = A[K] #②
            #A[K] = KEY
    A[K+1] = KEY #③

for i in range(1, 10):
    print(A[i])
