import time

def climbStairs_Recursive(n):
    '''Recurisve function to compute the number of solutions'''
    first3 = {1:1, 2:2, 3:4}
    if n in first3.keys():
        return first3[n]
    else:
        return climbStairs_Recursive(n-1) + \
               climbStairs_Recursive(n-2) + \
               climbStairs_Recursive(n-3)

def climbStairs_NonRecursive(n):
    '''Non-recurisve function to compute the number of solutions'''
    a = 1
    b = 2
    c = 4
    for i in range(n-3):
        c, b, a = a+b+c, c, b
    return c

start = time.time()
print("No.:", climbStairs_Recursive(30),"Time: ", time.time()-start,"seconds")
start = time.time()
print("No.:", climbStairs_NonRecursive(20),"Time: ", time.time()-start,"seconds")
