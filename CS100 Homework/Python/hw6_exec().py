import sys,re

class program(object):
    def __init__(self, string):
        self.string = string
        self.define_list=[]
        self.code_list=[]
        self.code_string=""
    def removeLineNum(self,inStr):
        line_string = inStr.split(":")
        if (len(line_string) >= 2):
            return line_string[1]
        else:
            return inStr
    def replace_Exclamatory(self, inStr):
        return inStr.replace("|"," or ").replace("&", " and ").replace("!", " not ")
    def evaluate(self):
        block_list = re.split('\n|\;',self.string)
        progress = 0
        for i in range(0,len(block_list)):
            a = block_list[i].strip()
            if re.match('^\s*main\s*\(', a):
                progress = i + 1
                break
            id = a.replace('bool','').strip().split('=')[0].strip()
            if (re.match('^\d+', id)):
                self.define_list.append(id)
            self.code_string += '\n'+a.replace('bool','').strip()
        self.code_string += '\nis_infinite_while_detected=False'
        need_quota = False
        for i in range(progress, len(block_list)):
            a = block_list[i].strip()
            if re.match('^[a-zA-Z0-9][a-zA-Z0-9_]*\s*\:\s*while\s*\(',a):
                self.code_string += '\ndead_loop_check_flag=0'
                self.code_string += '\n'+self.replace_Exclamatory(self.removeLineNum(a).strip()) + ":"
                self.code_string += '\n\tif (is_infinite_while_detected):'
                self.code_string += '\n\t\tbreak'
                self.code_string += '\n\tdead_loop_check_flag+=1'
                self.code_string += '\n\tif(dead_loop_check_flag==30):'
                self.code_string += '\n\t\tprint ("infinite")'
                self.code_string += '\n\t\tis_infinite_while_detected=True'
                self.code_string += '\n\t\tbreak'
                need_quota = True
            elif re.match('^[a-zA-Z0-9][a-zA-Z0-9_]*\s*\:\s*if\s*\(', a):
                self.code_string += '\n'+self.replace_Exclamatory(self.removeLineNum(a).strip()) + ":"
                self.code_string += '\n\t'
                need_quota = True
            elif re.match('^\s*done\s*$|^\s*fi\s*$',a):
                need_quota = False
                continue
            elif re.match('^\s*\{\s*$|^\s*\}\s*$',a):
                self.code_string += '\n'
                continue
            elif re.match('^[a-zA-Z0-9][a-zA-Z0-9_]*\s*\:\s*return\s+\w+', a):
                return_result = self.replace_Exclamatory(self.removeLineNum(a).strip())
                self.code_string += '\nif ( not is_infinite_while_detected):'
                self.code_string += (return_result.replace('return ', '\n\tprint (')) +')'+'\n'
                break
            else:              
                self.code_string += '\n'
                if need_quota:
                    self.code_string += '\t'
                self.code_string += self.replace_Exclamatory(self.removeLineNum(a).strip())
        for define_var in self.define_list:
                self.code_string = self.code_string.replace(define_var, 'bVar_'+define_var)
        exec(self.code_string, globals(), locals())

def main():
    l = sys.stdin.readlines()
    s = ""
    for i in range(len(l)):
        s += l[i]
    prog = program(s)
    prog.evaluate()

main()

