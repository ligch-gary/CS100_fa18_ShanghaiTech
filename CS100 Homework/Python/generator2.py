import os
import sys
import random


class BoolFuction(object):

    def __init__(self):
        self.varibles = {}
        self.statments = []
        self.bin_opreators = ['&', '|']

    def random_name(self, length):
        legal_char = "ifFIreturnwhiledonepass1234567890_"
        illegal_case = ["if", "fi", "while", "done", "return"]
        res = random.choice(illegal_case)
        for _ in range(length):
            res += random.choice(legal_char)
        if res in illegal_case:
            self.random_name(length)
        else:
            return res
            
    def generate_varibles(self, var_num, var_length = 1):
        # default varible length is 1, i.e. "x", "y"...
        count = 0
        while count < var_num:
            var_name = self.random_name(var_length)
            if var_name not in self.varibles:
                self.varibles[var_name] = random.choice([True, False])
                count += 1
        return 
    
    def generate_expression(self, space = False):
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

    def generate_stmts(self, stmtsize, sp = False):
        space = " " if sp == True else ""
        stmts = []
        for _ in range(stmtsize):
            pass_prob = random.randint(1,10)
            if pass_prob > 1:
                var = str(random.sample(self.varibles.keys(), 1)[0])
                exp = self.generate_expression(sp)
                res = var + space + "=" + space + exp + space + ";"
                stmts.append(res)
            else:
                res = "pass" + space + ";"
                stmts.append(res)
        return stmts

    def generate_proc(self, space = False):
        sp = " " if space == True else ""
        stmts_len = 5
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
                i = random.randint(0,10)
                if (i <= 3):
                     self.statments.append("\n")
                stmt_size = random.randint(1,assign_per_block)
                exprs = self.generate_stmts(stmt_size, space)
                for expr in exprs:
                    line_count += 1
                    legal_expr = str(line_count) + ": " + sp + expr
                    self.statments.append(legal_expr)
                line_count += 1
                if_stmt = self.generate_expression(space)
                if_expr = str(line_count) + ": " + sp + "if" + sp + "(" + sp + if_stmt + sp + ")"
                self.statments.append(if_expr)
                base = 3
                continue
            elif (base == 1):
                i = random.randint(0,10)
                if (i <= 3):
                     self.statments.append("\n")
                line_count += 1
                while_stmt = self.generate_expression(space)
                while_expr = str(line_count) + ": " + sp + "while" + sp +"(" + sp + while_stmt + sp +")"
                self.statments.append(while_expr)
                base = 4
                continue
            elif (base == 2):
                i = random.randint(0,10)
                if (i <= 3):
                     self.statments.append("\n")
                stmt_size = random.randint(1,assign_per_block)
                exprs = self.generate_stmts(stmt_size, space)
                for expr in exprs:
                    line_count += 1
                    legal_expr = str(line_count) + ": " + sp + expr
                    self.statments.append(legal_expr)
                base = 1
                continue
            elif (base == 3):
                i = random.randint(0,10)
                if (i <= 3):
                     self.statments.append("\n")
                stmt_size = random.randint(1,assign_per_block)
                exprs = self.generate_stmts(stmt_size, space)
                for expr in exprs:
                    line_count += 1
                    legal_expr = str(line_count) + ": " + sp + expr
                    self.statments.append(legal_expr)
                self.statments.append(" fi")
                base = random.randint(0, 2)
                continue
            elif (base == 4):
                i = random.randint(0,10)
                if (i <= 3):
                     self.statments.append("\n")
                stmt_size = random.randint(1,assign_per_block)
                exprs = self.generate_stmts(stmt_size, space)
                for expr in exprs:
                    line_count += 1
                    legal_expr = str(line_count) + ": " + sp + expr
                    self.statments.append(legal_expr)
                self.statments.append(" done")
                base = random.randint(0, 2)
                continue
        # finally add the return stmts
        stmt_size = random.randint(1,assign_per_block)
        exprs = self.generate_stmts(stmt_size, space)
        for expr in exprs:
            line_count += 1
            legal_expr = str(line_count) + ": " + sp + expr
            self.statments.append(legal_expr)
        line_count += 1
        re_expr = str(line_count) + ": " + sp + "return " + sp +  str(random.sample(self.varibles.keys(), 1)[0]) + sp + ";"
        self.statments.append(re_expr)
        return
        
    def generate_prog(self , var_num = 10 , var_length = 2 , space = False):
        self.generate_varibles(var_num, var_length)
        self.generate_proc(space)
        proc = self.statments
        item_list = list(self.varibles.keys())
        for item in item_list:
            line = "bool " + item + " = " + str(self.varibles[item]) + " ;"
            print(line)
        print("    main()")
        print("{")
        for stmt in proc:
            print(stmt)
        print("}")


def main():
    t = BoolFuction()
    t.generate_prog(4, 5, True)

if __name__ == "__main__":
    main()

