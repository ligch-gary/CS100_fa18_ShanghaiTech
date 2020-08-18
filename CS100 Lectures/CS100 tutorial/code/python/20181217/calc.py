class Tree():
    def __init__(self, data, leftChild = None, rightChild =None):
        self._data=data
        self._leftChild = leftChild
        self._rightChild = rightChild

    def inOrder(self):
        if self._leftChild!=None:
            self._leftChild.inOrder()
        print(self._data)
        if self._rightChild!=None:
            self._rightChild.inOrder()

    def preorder(self):
        print(self._data)
        if self._leftChild!=None:
            self._leftChild.inOrder()
        if self._rightChild!=None:
            self._rightChild.inOrder()

    def postorder(self):
        if self._leftChild!=None:
            self._leftChild.inOrder()
        if self._rightChild!=None:
            self._rightChild.inOrder()
        print(self._data)

    def computeValue(self):
        if isinstance(self._data,float): # else it is an operator
            return self._data
        elif self._data=="*":
            v1 = self._leftChild.computeValue()
            v2 = self._rightChild.computeValue()
            return v1 * v2
        elif self._data=="+":
            v1 = self._leftChild.computeValue()
            v2 = self._rightChild.computeValue()
            return v1 + v2
        elif self._data=="-":
            v1 = self._leftChild.computeValue()
            v2 = self._rightChild.computeValue()
            return v1 - v2
        elif self._data=="/":
            v1 = self._leftChild.computeValue()
            v2 = self._rightChild.computeValue()
            if v2==0:
                raise ZeroDivisionError
            return v1/v2
        else: raise SyntaxError
 
def parser(s):
    ''' construct a tree from the input expression that is a string s
    '''
    import tokenize
    from io import BytesIO
    import token
    
    s = "(" + s + ")"
    ss = [] # create an empty stack
    tokens = tokenize.tokenize(BytesIO(s.encode('utf-8')).readline)

    exprStack = []
    operatorStack = []
    priority = {"(":1, "+":2, "-":2, "*":3, "/":3}   # assign priority to operators
    
    for tokType, tokVal, _, _, _ in tokens:
        if tokVal == "(": 
            operatorStack.append(tokVal)
        if tokVal == ")":
            while operatorStack!=[] and operatorStack[-1]!="(":
                op = operatorStack.pop()
                right = exprStack.pop()
                left = exprStack.pop()
                expr = Tree(op, left,right)
                exprStack.append(expr)
            if operatorStack[-1]=="(":
                operatorStack.pop()
        if tokType == token.NUMBER:
            expr = Tree(float(tokVal)) 
            exprStack.append(expr)
        if tokVal in {'+','-','*','/'}:
            while operatorStack!=[] and priority[operatorStack[-1]]>=priority[tokVal]:
                op = operatorStack.pop()
                right = exprStack.pop()
                left = exprStack.pop()
                expr = Tree(op, left,right)
                exprStack.append(expr)                
            operatorStack.append(tokVal)     
    t = exprStack.pop()
    return t

if __name__=="__main__":
    import sys 
    if len(sys.argv) !=2:
        print("Usage: calc expr")
    else:
        expr = sys.argv[1]
        t = parser(expr) 
        v = t.computeValue()
        if int(v)==v:
            print(int(v))
        else:
            print(v)
