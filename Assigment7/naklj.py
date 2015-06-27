import random

f = open("nak2", "wb")

for i in xrange(1000000):
    niz = "\\x%02x"%random.randint(0,255)
    f.write(eval('"'+niz+'"'))

