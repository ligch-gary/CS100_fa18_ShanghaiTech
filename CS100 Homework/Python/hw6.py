import sys,re

class program(object):
    def __init__(self, string):
        self.str = string
        self.l = []
        self.define_list = []
        self.code_list = []
    def evaluate(self):
        vars = {}
        l = self.str.split("\n")
        for i in range(len(l)):
            l[i]=l[i].strip()
            if 'main()' not in l[i]:
                if (l[i] != ""):
                    a = (l[i].replace("bool", "")).strip(';')
                    c = a.split('=')
                    if eval(c[1]):
                        vars[c[0].replace(" ","")] = eval(c[1])
                        vars['!'+c[0].replace(" ","")] = False
                    else:
                        vars[c[0].replace(" ","")] = eval(c[1])
                        vars['!'+c[0].replace(" ","")] = True
            else:
                break
        globals().update(vars)
        block_list = []
        list=[]
        for j in range(len(l)):
            b = ''.join(l[j].split())
            b = b.replace(";",' ')
            if re.match('^\w*\:.',b): 
                list.append(b)
            elif re.match('^fi$',b):
                list.append(b)
            elif re.match('^done$',b):
                list.append(b)
            elif re.match('^pass$',b):
                list.append(b)
            else:
                continue
        list2 = []  
        templist=[]
        for m in range (len(list)):
            if re.match('^\w*\:if\(.',list[m]):
                templist.append(list[m])
                list2.append(templist)
                templist=[]
            elif re.match('^\w*\:while\(.',list[m]):
                if templist:
                    list2.append(templist)
                    templist=[]
                    templist.append(list[m])
                    list2.append(templist)
                    templist=[]
                else:
                    templist.append(list[m])
                    list2.append(templist)
                    templist=[]
            elif re.match('^fi$',list[m]):
                if templist:
                    templist.append(list[m])
                    list2.append(templist)
                    templist=[]
                else:
                    continue
            elif re.match('^done$',list[m]):
                if templist:
                    templist.append(list[m])
                    list2.append(templist)
                    templist=[]
                else:
                    continue
            elif re.match('^\w*\:return',list[m]):
                if re.match('^\w*\:return\w*\=',list[m]):
                    templist.append(list[m])
                else:
                    templist.append(list[m])
                    list2.append(templist)
                    templist=[]
            else:
                templist.append(list[m])
        print(list2)
        for k in range(len(list2)):
            for o in range(len(list2[k])):
                list2[k][o] = re.sub("^\w*\:","",list2[k][o]) 
        for ii in range(len(list2)):
            for jj in range(len(list2[ii])):
                    list2[ii][jj] = list2[ii][jj].replace("|",' or ')
                    list2[ii][jj] = list2[ii][jj].replace("&",' and ')
                    list2[ii][jj] = list2[ii][jj].replace("(",' ( ')
                    list2[ii][jj] = list2[ii][jj].replace(")",' ) ')
                    list2[ii][jj] = list2[ii][jj].replace('=',' = ')
        t = True
        for kk in range(len(list2)):
            for mm in range(len(list2[kk])):
                if t == True:
                    if "if (" in list2[kk][mm]:
                        tempstr = list2[kk][mm].replace("if (","(")
                        for key in vars:
                            if ' '+key+' ' in tempstr:
                                tempstr = tempstr.replace(" "+key+" "," "+str(vars[key])+" ")
                            else:
                                continue
                        t = eval(tempstr) 
                    elif "while (" in list2[kk][mm]:
                        tempstr = list2[kk][mm].replace("while (","(")
                        for key in vars:
                            if ' '+key+' ' in tempstr:
                                tempstr = tempstr.replace(" "+key+" "," "+str(vars[key])+" ")
                            else:
                                continue
                        t = eval(tempstr)
                        cnt = 0
                        while t == True and cnt < 40:
                            cnt += 1
                            for pp in range(len(list2[kk+1])) :
                                if list2[kk+1][pp]  != 'done' and 'pass ' not in list2[kk+1][pp]:
                                    tempstr = (list2[kk+1][pp].split('='))[1]
                                    for key in vars:
                                        if ' '+key+' ' in tempstr:
                                            tempstr = tempstr.replace(" "+key+" "," "+str(vars[key])+" ")
                                        else:
                                            continue
                                    t = eval(tempstr)
                                    vars["!"+(list2[kk+1][pp].split('='))[0].strip()] = not t
                                    vars[(list2[kk+1][pp].split('='))[0].strip()] = t
                                else:
                                    continue
                            tempstr = list2[kk][mm].replace('while (','(')
                            for key in vars:
                                if ' '+key+' ' in tempstr:
                                    tempstr = tempstr.replace(" "+key+" "," "+str(vars[key])+" ")
                                else:
                                    continue
                            t = eval(tempstr)
                        if cnt >= 40:
                            print('infinite')
                            exit()
                        else :
                            continue
                    elif list2[kk][mm] == 'pass ' or list2[kk][mm] == 'done' or list2[kk][mm] == 'fi':
                        continue
                    elif kk == len(list2)-1 and mm == len(list2[kk])-1:
                        continue
                    else:
                        if kk-1 >= 0 and 'while (' in list2[kk-1][0]:
                            continue
                        else:
                            tempstr = (list2[kk][mm].split('='))[1]
                            for key in vars:
                                if ' '+key+' ' in tempstr:
                                    tempstr = tempstr.replace(" "+key+" "," "+str(vars[key])+" ")
                                else:
                                    continue
                            t = eval(tempstr)
                            vars["!"+(list2[kk][mm].split('='))[0].strip()] = not t
                            vars[(list2[kk][mm].split('='))[0].strip()] = t
                            t = True
                else:
                    t == True
                    break
        result = (re.sub('^return','',list2[-1][-1])).strip()
        print(vars[result])
def main():
    l = sys.stdin.readlines()
    s = ""
    for i in range(len(l)):
        s += l[i]
    prog = program(s)
    prog.evaluate()

main()