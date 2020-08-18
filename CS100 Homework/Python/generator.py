import random

'''
Author: 小圆
注意：case生成器已经经过了较多次的验证（大概几万次吧……）
    目前没发现生成的代码有逻辑问题。
    然后 main函数里有一行
    t.generate_prog(10, 7, True)
    这里的10是变量的个数， 7是每个变量的字符长度， True是运算符之间是不是有空格
    x=!y; //这个没有空格
    x = ! y ; //这个有空格
    所以 上面那几个参数你们可以自己调整

    另外 如果大家想要调整每个block中代码的行数 找到下面这一段 把assign_per_block改了就行（默认三行以内）
    def generate_proc(self, space = False):
    sp = " " if space == True else ""
    stmts_len = 10
    assign_per_block = 3

    最后 结尾有惊喜（跑
'''

class BoolFuction(object):

    def __init__(self):
        self.varibles = {}
        self.statments = []
        self.bin_opreators = ['&', '|']

    def __random_name__(self, length):
        legal_char = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm_"
        illegal_case = ["if", "fi", "while", "done", "return"]
        res = ""
        for _ in range(length):
            res += random.choice(legal_char)
        if res in illegal_case:
            self.__random_name__(length)
        else:
            return res
            
    def __generate_varibles__(self, var_num, var_length = 1):
        # default varible length is 1, i.e. "x", "y"...
        count = 0
        while count < var_num:
            var_name = self.__random_name__(var_length)
            if var_name not in self.varibles:
                self.varibles[var_name] = random.choice([True, False])
                count += 1
        return 
    
    def __generate_expression__(self, space = False):
        sp = " " if space == True else ""
        temp_statement = []
        # default rhs has at most 5 varibles (per expression)
        # to generate single expression i.e. 'x', '!y'...
        for _ in range(random.randint(1, 5)):
            flag = random.choice([True, False])
            if (flag):
                temp_statement.append(str(random.sample(self.varibles.keys(), 1)[0]))
            else:
                 temp_statement.append("!" + sp + str(random.sample(self.varibles.keys(), 1)[0]))
        # to union these expressions into an expression
        # we should do all things by random choice, include whether the expr has '()'
        while (len(temp_statement) > 1):
            expr1 = temp_statement.pop()
            expr2 = temp_statement.pop()
            opr   = random.choice(self.bin_opreators)
            frac  = random.choice([True, False])
            if (frac):
                res = "(" + sp + expr1 + sp + opr + sp + expr2 + sp + ")"
            else:
                res = expr1 + sp + opr + sp + expr2
            temp_statement.append(res)
        return temp_statement[0]

    def __generate_stmts__(self, stmtsize, sp = False):
        space = " " if sp == True else ""
        stmts = []
        for _ in range(stmtsize):
            pass_prob = random.randint(1,10)
            if pass_prob > 1:
                var = str(random.sample(self.varibles.keys(), 1)[0])
                exp = self.__generate_expression__(sp)
                res = var + space + "=" + space + exp + space + ";"
                stmts.append(res)
            else:
                res = "pass" + space + ";"
                stmts.append(res)
        return stmts

    def generate_proc(self, space = False):
        sp = " " if space == True else ""
        stmts_len = 10
        assign_per_block = 3
        curr = 0
        # that is how many blocks of stmts in the main proc
        line_count = 0
        '''
        case = 0:   a block end with "if"
                    we should append some stmts end with "fi"
        case = 1:   a block end with "while"
                    we should append some stmts end with "done"
        case = 2:   a block end with nothing
                    we should append a while stmts below
        case = 3:   fi
        case = 4:   done
        '''
        base = random.randint(0,2)
        while True :
            curr += 1
            if (curr > stmts_len) and (base in [0, 1, 2]):
                break
            if (base == 0):
                stmt_size = random.randint(1,assign_per_block)
                exprs = self.__generate_stmts__(stmt_size, space)
                for expr in exprs:
                    line_count += 1
                    legal_expr = str(line_count) + ": " + sp + expr
                    self.statments.append(legal_expr)
                line_count += 1
                if_stmt = self.__generate_expression__(space)
                if_expr = str(line_count) + ": " + sp + "if" + sp + "(" + sp + if_stmt + sp + ")"
                self.statments.append(if_expr)
                base = 3
                continue
            elif (base == 1):
                line_count += 1
                while_stmt = self.__generate_expression__(space)
                while_expr = str(line_count) + ": " + sp + "while" + sp +"(" + sp + while_stmt + sp +")"
                self.statments.append(while_expr)
                base = 4
                continue
            elif (base == 2):
                stmt_size = random.randint(1,assign_per_block)
                exprs = self.__generate_stmts__(stmt_size, space)
                for expr in exprs:
                    line_count += 1
                    legal_expr = str(line_count) + ": " + sp + expr
                    self.statments.append(legal_expr)
                base = 1
                continue
            elif (base == 3):
                stmt_size = random.randint(1,assign_per_block)
                exprs = self.__generate_stmts__(stmt_size, space)
                for expr in exprs:
                    line_count += 1
                    legal_expr = str(line_count) + ": " + sp + expr
                    self.statments.append(legal_expr)
                self.statments.append("\t fi")
                base = random.randint(0, 2)
                continue
            elif (base == 4):
                stmt_size = random.randint(1,assign_per_block)
                exprs = self.__generate_stmts__(stmt_size, space)
                for expr in exprs:
                    line_count += 1
                    legal_expr = str(line_count) + ": " + sp + expr
                    self.statments.append(legal_expr)
                self.statments.append("\t done")
                base = random.randint(0, 2)
                continue
        # finally add the return stmts
        stmt_size = random.randint(1,assign_per_block)
        exprs = self.__generate_stmts__(stmt_size, space)
        for expr in exprs:
            line_count += 1
            legal_expr = str(line_count) + ": " + sp + expr
            self.statments.append(legal_expr)
        line_count += 1
        re_stmt = self.__generate_expression__(space)
        re_expr = str(line_count) + ": " + sp + "return " + sp +  str(random.sample(self.varibles.keys(), 1)[0]) + sp + ";"
        self.statments.append(re_expr)
        return
        
    def generate_prog(self , var_num = 10 , var_length = 2 , space = False):
        res = """"""
        self.__generate_varibles__(var_num, var_length)
        self.generate_proc(space)
        proc = self.statments
        item_list = list(self.varibles.keys())
        for item in item_list:
            line = "bool " + item + " = " + str(self.varibles[item]) + " ;\n"
            res += line
        res += "main()\n"
        res += "{\n"
        for stmt in proc:
            res += stmt
            res += "\n"
        res += "}\n"
        return res

def main():
    t = BoolFuction()
    print(t.generate_prog(15, 8, False))

if __name__ == "__main__":
    main()
    
'''
一首《white album》送给wa(wrong answer)的各位， 祝大家早日AC

すれ违う毎日が 増えてゆくけれど
お互いの気持ちはいつも 侧にいるよ
ふたり会えなくても 平気だなんて
强がり言うけど 溜め息まじりね

过ぎてゆく季节に 置いてきた宝物
大切なピースの欠けた パズルだね
白い雪が街に 优しく积もるように
アルバムの空白を全部 埋めてしまおう

降り积もるさびしさに 负けてしまいそうで
ただひとり 不安な日々を过ごしてても
大丈夫だよって 肩をたたいて
あなたは笑颜で 元気をくれるね

たとえ离れていても その言叶があるから
心から幸せと言える 不思议だね
淡い雪がわたしの ひそかな想い込めて
纯白のアルバムの ページ染めてくれる

过ぎてゆく季节に 置いてきた宝物
大切なピースの欠けた パズルだね
白い雪が街に 优しく积もるように
アルバムの空白を全部 埋めてしまおう
'''