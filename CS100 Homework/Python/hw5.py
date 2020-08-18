import sys
import re

class Pairs(object):
    def __init__(self):
        self.__data = []
    
    def addPoint(self, point1, point2):
        pair = (point1, point2)
        self.__data.append(pair)

    def getPairs(self):
        return self.__data
    
    def getIndexs(self):
        indexs = []
        for per_pair in self.__data:
            if per_pair[0] not in indexs:
                indexs.append(per_pair[0])
            elif per_pair[1] not in indexs:
                indexs.append(per_pair[1])
        return indexs
       
class CFG_matrix(object):
    def __init__(self, size):
        self.__mat = []
        for i in range(size):
            temp = []
            for j in range(size):
                temp.append(0)
            self.__mat.append(temp)
    
    def setPosition(self,i ,j):
        self.__mat[i][j] = 1

    def printMatrix(self):
        if (str(self.__mat) == "[[1]]"):
            print("[0]")
            return
        res = "["
        for row in self.__mat:
            per_row = ""
            for item in row:
                per_row = per_row + str(item) + ","
            per_row = per_row[:-1]
            per_row += ";"
            res += per_row
        res = res[:-1]
        res += "]"
        print(res)

class program(object):
    def __init__(self, string):
        self.str = string
        self.dic = {}
        self.l = []

    def getCFG(self):
        vars={}
        l = self.str.split("\n")
        for i in range(len(l)):
            if 'main()' not in l[i]:
                if (l[i] != ""):
                    a = (l[i].replace("bool", "")).strip(';')
                    c = a.split('=')
                    vars[c[0].replace(" ","")] = eval(c[1])
            else:
                break  
        list2=[]
        for j in range(len(l)):
            b = ''.join(l[j].split())
            if re.match('^\w*\:.',b):
                list2.append(b)
            elif re.match('fi',b):
                list2.append(b)
            elif re.match('done',b):
                list2.append(b)
            elif re.match('pass',b):
                list2.append(b)
            else:
                continue
        list3 = []
        for k in range(len(list2)):
            c= list2[k]
            for key in list(vars.keys()):
                while key in c and key not in 'while' and key not in 'if' and key not in 'return' and key not in 'pass' and key not in 'done':
                    c = c.replace(key,'')
            list3.append(c)
        list4 = []
        templist=[]
        for m in range (len(list3)):
            if re.match('^\w*\:if.',list3[m]):
                templist.append(list3[m])
                list4.append(templist)
                templist=[]
            elif re.match('^\w*\:while.',list3[m]):
                if templist:
                    list4.append(templist)
                    templist=[]
                    templist.append(list3[m])
                    list4.append(templist)
                    templist=[]
                else:
                    templist.append(list3[m])
                    list4.append(templist)
                    templist=[]
            elif re.match('fi',list3[m]):
                if templist:
                    templist.append(list3[m])
                    list4.append(templist)
                    templist=[]
                else:
                    continue
            elif re.match('done',list3[m]):
                if templist:
                    templist.append(list3[m])
                    list4.append(templist)
                    templist=[]
                else:
                    continue
            elif re.match('^\w*\:return',list3[m]):
                templist.append(list3[m])
                list4.append(templist)
                templist=[]
            else:
                templist.append(list3[m])
        x = Pairs()
        for n in range (len(list4)):
            for p in range (len(list4[n])):
                if 'if' in list4[n][p]:
                    if n+2 < len(list4):
                        x.addPoint((list4[n][0].split(':'))[0],(list4[n+2][0].split(':'))[0]) 
                        x.addPoint((list4[n+1][0].split(':'))[0],(list4[n+2][0].split(':'))[0])
                        x.addPoint((list4[n][0].split(':'))[0],(list4[n+1][0].split(':'))[0])
                    else:  
                        x.addPoint((list4[n][0].split(':'))[0],(list4[n+1][0].split(':'))[0])
                elif 'while' in list4[n][p]:
                    if n-1 >= 0 and n+2 < len(list4):
                        x.addPoint((list4[n-1][0].split(':'))[0],(list4[n][0].split(':'))[0])
                        x.addPoint((list4[n][0].split(':'))[0],(list4[n+1][0].split(':'))[0])
                        x.addPoint((list4[n][0].split(':')[0]),(list4[n+2][0].split(':'))[0])
                        x.addPoint((list4[n+1][0].split(':'))[0],(list4[n][0].split(':'))[0])
                    else:
                        x.addPoint((list4[n][0].split(':'))[0],(list4[n+1][0].split(':'))[0])

                        x.addPoint((list4[n+1][0].split(':'))[0],(list4[n][0].split(':'))[0])
                elif 'return' in list4[n][p]:
                        if 'done' not in list4[n-1][-1] and 'fi' not in list4[n-1][-1]:
                            x.addPoint((list4[n-1][0].split(':'))[0],(list4[n][0].split(':'))[0])
                        else:
                            x.addPoint((list4[n-2][0].split(':'))[0],(list4[n][0].split(':'))[0])
                else:
                    continue
        pp = list(set(x.getPairs()))
        linename = x.getIndexs()
        linename.sort()
        total_length = len(linename)
        tag_map = {}
        for i in range(total_length):
            tag_map[linename[i]] = i
        result = CFG_matrix(total_length)
        for item in pp:
            result.setPosition(tag_map[item[0]], tag_map[item[1]])
        result.printMatrix()

def main():
    l = sys.stdin.readlines()
    s = ""
    for i in range(len(l)):
        s += l[i]
    prog = program(s)
    prog.getCFG()

main()
        
        
        
        
    
    


    
    
                
        




            


                
        




            


        

    
        
        



        
    