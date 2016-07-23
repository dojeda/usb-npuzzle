#!/usr/bin/python
import optparse
import sys
import random

def n_puzzle(n):
    lista = range(n+1)
    random.shuffle(lista)
    return lista

def n_perms(puzzle):
    n = 0
    estado = puzzle[:]
    estado.remove(0)
    for i in puzzle:
        if i == 0:
            continue
        n += len([x for x in estado if x < i])
        estado.remove(i)
    return n

parser = optparse.OptionParser(description="generador de n-puzzles",
                               version=0)
parser.add_option("-n",help="tamano del puzzle",type="int",default=8)
parser.add_option("-i",help="numero de instancias",type="int",default=100)

params,args = parser.parse_args()

def puzzleprint(estado):
    aux = "%s"%(estado)
    print aux.replace(" ","")[1:-1]

for i in range(params.i):
    estado = n_puzzle(params.n)
    while (n_perms(estado) % 2):
        estado = n_puzzle(params.n)
    puzzleprint(estado)
