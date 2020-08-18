import sys,re

class program(object):
    def __init__(self, string):
        self.string = string
        self.define_list=[]
        self.code_list=[]
        self.code_string=""

    def __del__(self):
        return
    def pre_process(self):
        block_list = self.string.split('\n')
        progress = 0
        for i in range(0,len(block_list)):
            a = block_list[i].strip()
            if re.match('^\s*main\s*\(', a):
                progress = i
                break
            self.define_list.append(a.replace('bool',''))
        templist=[]
        for i in range(progress, len(block_list)):
            a = block_list[i].strip()
            if re.match('^[a-zA-Z0-9]+\s*\:\s*while\s*\(|^[a-zA-Z0-9]+\s*\:\s*if\s*\(',a):
                if (templist):
                    self.code_list.append(templist)
                    templist = []
                templist.append(a)
            elif re.match('^\s*done\s*$|^\s*fi\s*$|^[a-zA-Z0-9]+\s*\:\s*return\s*\w+',a):
                templist.append(a)
                self.code_list.append(templist)
                templist = []
            else:
                templist.append(a)
    def removeLineNum(self,inStr):
        p=re.compile(r'\D*\d+\s?[.|:|\]|\)]?\s')
        return p.sub('',inStr,count=1).strip('\n')
    def has_Exclamatory(self, inStr):
        if (-1 == inStr.find('!')):
            return False
        return True
    def replace_Exclamatory(self, inStr):
        return inStr.replace("|"," or ").replace("&", " and ").replace("!", " not ")
    '''def replace_Exclamatory(self, inStr):
        if (not self.has_Exclamatory(inStr)):
            return inStr
        while(self.has_Exclamatory(inStr)):
            if (re.search('\([^()]*\)', inStr)):
                tempString = re.findall('\([^()]*\)', inStr)
                for str in tempString:
                    newstr = str
                    while (self.has_Exclamatory(newstr)):
                        tempSting2 = re.findall('!\s*\w+', newstr)
                        for temp in tempSting2:
                            newstr = newstr.replace(temp, " [ not " + temp[1:]+" ] ")
                    newstr=newstr.replace('(','[').replace(')',']')
                    inStr = inStr.replace(str, newstr)
                    inStr = inStr.replace(str, newstr)
            else:
                while (re.search('\!\s*\w+', inStr)):
                    temp = re.search('\!\s*\w+', inStr).group()
                    inStr = inStr.replace(temp, " [ not " + temp[1:]+" ] ")
        return inStr.replace('[','(').replace(']',')')'''
    def evaluate(self):
        block_list = self.string.split('\n')
        progress = 0
        for i in range(0,len(block_list)):
            a = block_list[i].strip()
            if re.match('^\s*main\s*\(', a):
                progress = i + 2
                break
            self.define_list.append(a.replace('bool','').split('=')[0].strip())
            self.code_string += '\n'+a.replace('bool','').strip()
        self.code_string += '\nis_infinite_while_detected=False'
        need_quota = False
        for i in range(progress, len(block_list)):
            a = block_list[i].strip()
            if re.match('^[a-zA-Z0-9]+\s*\:\s*while\s*\(',a):
                self.code_string += '\ndead_loop_check_flag=0'
                self.code_string += '\n'+self.replace_Exclamatory(self.removeLineNum(a).strip()) + ":"
                self.code_string += '\n\tif (is_infinite_while_detected):'
                self.code_string += '\n\t\tbreak;'
                self.code_string += '\n\tdead_loop_check_flag+=1'
                self.code_string += '\n\tif(dead_loop_check_flag==30):'
                self.code_string += '\n\t\tprint ("infinite");'
                self.code_string += '\n\t\tis_infinite_while_detected=True;'
                self.code_string += '\n\t\tbreak;'
                need_quota = True
            elif re.match('^[a-zA-Z0-9]+\s*\:\s*if\s*\(', a):
                self.code_string += '\n'+self.replace_Exclamatory(self.removeLineNum(a).strip()) + ":"
                self.code_string += '\n\t'
                need_quota = True
            elif re.match('^\s*done\s*$|^\s*fi\s*$',a):
                need_quota = False
                continue
            elif re.match('^\s*\{\s*$|^\s*\}\s*$',a):
                self.code_string += '\n'
                continue
            elif re.match('^[a-zA-Z0-9]+\s*\:\s*return\s+\w+', a):
                return_result = self.replace_Exclamatory(self.removeLineNum(a).strip())
                return_result.replace('return ', '\nprint ')
                self.code_string += '\nif ( not is_infinite_while_detected):'
                self.code_string += (return_result.replace('return ', '\n\tprint (')).replace(';',')') +'\n'
                break
            else:
                self.code_string += '\n'
                if need_quota:
                    self.code_string += '\t'
                self.code_string += self.replace_Exclamatory(self.removeLineNum(a).strip())
        self.define_list.sort(key = lambda i:len(i),reverse=True)
        for define_var in self.define_list:
            self.code_string = self.code_string.replace(define_var, 'bVar_'+define_var)
        exec(self.code_string, globals(), locals())
    def dump(self):
        print(self.code_list)
        print(self.define_list)

def main():
    l = sys.stdin.readlines()
    s = ""
    for i in range(len(l)):
        s += l[i]
    prog = program(s)
    prog.evaluate()
main()

