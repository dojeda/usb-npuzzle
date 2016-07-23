#!usr/bin/python
import optparse
import math

parser = optparse.OptionParser()
parser.add_option("-n",type="int",default=8)
parser.add_option("--header",action="store_true",default=False)
parser.add_option("--footer",action="store_true",default=False)
parser.add_option("--filacol",action="store_true",default=False)
parser.add_option("--defines",action="store_true",default=False)
params, args = parser.parse_args()

n = int(math.sqrt(params.n + 1))

if params.header:
    if params.filacol:
        print "#ifndef __FILACOL__"
        print "#define __FILACOL__"
    else:
        print "#ifndef __MANHATTAN__"
        print "#define __MANHATTAN__"
elif params.footer:
    if params.filacol:
        print "#endif // __FILACOL__"
    else:
        print "#endif // __MANHATTAN__"
elif params.filacol:
    k = int(math.sqrt(n))
    filas = [i/n for i in range(n*n)]
    colus = [i%n for i in range(n*n)]

    print "int filas%d[%d] = {"%(n*n-1,n*n),
    for i in range(0,len(filas)-1):
        print filas[i], ",",
    print filas[-1],"};"
    print "int colus%d[%d] = {"%(n*n-1,n*n),
    for i in range(0,len(colus)-1):
        print colus[i], ",",
    print colus[-1],"};"
elif params.defines:
    sizeofchar = 1
    print "#define N%d %d"%(n*n-1,n)
    print "#define N%d_1 %d"%(n*n-1,n-1)
    print "#define N%dxN%d %d"%(n*n-1,n*n-1,n*n)
    print "#define N%dxN%dxchar %d"%(n*n-1,n*n-1,n*n*sizeofchar)
    

else:
    objetivo = range(0,n*n)
    manhattan = []
    manhattan.append([0]*n*n) # manhattan de la casilla vacia siempre es cero
    # manhattan de las demas casillas
    for i in range(1,n*n):
        x0 = i/n
        y0 = i%n
        valores = [0]*(n*n)
        for j in range(0,n*n):
            xf = j/n
            yf = j%n
            valores[j] = abs(x0-xf) + abs(y0-yf)
        manhattan += [valores]

    print "int manhattan%d[%d][%d] = {\n"%(n*n-1,n*n,n*n),
    for valor in manhattan:
        print "{",
        for i in range(0,len(valor)-1):
            print valor[i],",",
        print valor[-1],
        print "},"
    print "};"
        
