#coding=utf-8

#the first,the vectory

def xf(A):
	f=lambda L:(lambda n:n==0 and "NO" or "YES")((lambda L:(lambda a,b=\
		lambda x,y:x!=len(L) and y(x+1,y)^L[x]:b(a,b))(int ()))(L))
	k=len(A)
	print (A,f(A))
	D=A[:]
	for i in range(k):
		for j in range(D[i]):
			D[i]=j
			if f(D) == "NO":
				return D,f(D)

		D=A[:]

print (xf([4,2,11,44]))