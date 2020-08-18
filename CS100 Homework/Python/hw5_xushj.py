import re
s=""
line=input()
line=line+"\n"
block=[]
while(True):
     s=s+line
     line=input()
     line=line+"\n"
     if("}" in line):
        break
tmp = [''.join(i) for i in re.findall(r"([a-zA-Z0-9][a-zA-Z0-9_]*)\s*:|\b(if|fi|while|done)\b", s)];
tmp.reverse()
basiclist = []
for i in range(len(tmp)):
    if tmp[i] == 'while':
        basiclist.append(tmp[i-1])
        basiclist.append(tmp[i])
        basiclist.append(tmp[i+1])
    elif tmp[i] in ['if', 'fi', 'done']:
        basiclist.append(tmp[i-1])
        basiclist.append(tmp[i])
basiclist.append(tmp[-1])
basiclist.reverse()
baseblock = sorted(set(filter(lambda x: x not in ['if', 'fi', 'while', 'done'], basiclist)))
blocksets = {}
for i in range(len(baseblock)):
    this = baseblock[i]
    if this not in ['if', 'fi', 'while', 'done']:
        blocksets[this] = i
sentences = s.split("\n")
sentences = list(filter(lambda x: x != '', sentences))
sen = []
counter = 0
def blocklink(i):
    if cat(i) == 'if':
        link(i, i+2)
        link(i , i+4)
        link(i+2 , i+4)
    if cat(i) == "while":
        link(i , i+2)
        link(i+2 , i)
        link(i , i+4)
        if cat(i - 2) == "None":
            link(i-1 , i)
def cat(i):
    i += 1
    if i < 0 or i >= len(basiclist):
        return "nope"
    category = basiclist[i]
    if category in ['if', 'fi', 'while', 'done']:
        return category
    else:
        return "None"
def link(i,j):
    if basiclist[i] == basiclist[j]:
        return
    matrix[blocksets[basiclist[i]]][blocksets[basiclist[j]]] = 1
n = len(baseblock)
matrix = []
answermatrix = []
startlist = [(i, block[i][0][0][1]) for i in range(len(block))]
startlist2 = sorted(startlist, key=lambda t:t[1])
for i in range(n):
    matrix.append([0 for j in range(n)])
    answermatrix.append([0 for j in range(n)])
for i in range(len(basiclist)):
    blocklink(i)
CFG=str(matrix)
CFG = CFG.replace(" ","")
CFG = CFG.replace("],",";")
CFG = CFG.replace("]","")
CFG = CFG.replace("[","")
CFG = "["+CFG+"]"
print(CFG)
