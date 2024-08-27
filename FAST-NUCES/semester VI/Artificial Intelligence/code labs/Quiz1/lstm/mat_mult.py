import numpy as np
from scipy.special import softmax
# wf=[
#     [2,2,2,6,0,6,4,]
# ]

wi = [
    [6,5,5,0,1,5,0,1],
    [3,2,2,6,2,1,5,6],
    [3,2,1,3,0,2,3,2],
    [4,4,1,5,4,1,4,0]
]
bi = [0,0,1,6]

wo = [
    [5,4,3,5,1,3,2,4],
    [4,2,2,1,5,0,1,2],
    [3,0,4,0,2,1,1,5],
    [4,1,5,3,5,3,3,6]
    ]
bo =[6,4,0,8]
wc=[
    [0,5,6,0,5,4,0,3],
    [0,1,5,6,0,3,3,6],
    [0,0,5,5,0,5,3,4],
    [2,0,6,5,5,5,6,2]
    ]
bc = [0,2,0,2]
wf = [
    [2, 2, 2, 6, 0, 6, 4, 6],
    [4, 1, 1, 0, 2, 0, 3, 5],
    [1, 2, 1, 3, 4, 5, 1, 6],
    [2, 2, 2, 4, 1, 1, 5, 2]
] # Matrix for multiplication
bf = [0, 2, 1, 0] # Bias vector
w_softmax = [
    [6,2,6,0],
    [1,3,4,1],
    [5,5,4,1],
    [6,1,2,1],
    [4,5,2,3],
    [2,2,2,5],
    [4,4,2,6],
    [1,3,4,6]
]

habhi= [[3.99,4,3.95,4]]
bsoftmax = [3,2,0,0,3,0,3,0]
def sigmoid(matrix):
    list_sigmoid=[]
    for i in range(len(matrix)):
        n = 1/(1+np.exp(-matrix[i]))
        list_sigmoid.append(n)
    return list_sigmoid
def func(I,w,b):
    # I = [[2.99,3,2.9,3,1,3,0,2]] # Input matrix
    
    I = [[3.9,4,3.9,3.9]]
    matrix1 = np.array(I)
    matrix2 = np.array(w)

    mult = np.dot(matrix2, matrix1.T) # Matrix multiplication with transposed matrix2
    print("Matrix\n",mult)
    print("Bias\n",b)
    ans = np.sum(mult, axis=1) +b# Adding bias
    print("ANS->\n",ans)
    cdawg =softmax(ans)
    return cdawg
    # return sigmoid(ans)

if __name__ == '__main__':
    I=[[2.9,3,2.9,2.9,0.5,2,1,1.5]]
    mat = func(I,w_softmax,bsoftmax)
    print("sigmoid\n",mat)
    