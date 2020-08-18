from math import sqrt

class Vector:
    def __init__(self,*p):
        self._data = list(p)

    def __add__(self, other):
        v = (x+y for x,y in zip(self._data,other._data))
        return Vector(*v)

    def __sub__(self, other):
        v = (x-y for x,y in zip(self._data,other._data))
        return Vector(*v)

    def __mul__(self, n):
        v = (x*n for x in self._data)
        return Vector(*v)

    def __truediv__(self, n):
        assert n!=0
        v = (x/n for x in self._data)
        return Vector(*v)

    @property
    def length(self):
        return sqrt(sum(x**2 for x in self._data))

    def __str__(self):
        s = "Vector("
        num = len(self._data)
        if num==0:
            return s + ")"
        s = s+ "{" + str(self._data[0]) + "}"
        for i in range(1,num):
            s = s + ",{" + str(self._data[i]) + "}"
        s = s + ")"
        return s

v1 = Vector(3, 4, 5)
v2 = Vector(5, 6, 7)
print(v1)
print(v1+v2)
print(v1-v2)
print(v1*3)
print(v1/2)
print(v1.length)


    

        
