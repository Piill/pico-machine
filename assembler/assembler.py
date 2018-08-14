#!/usr/bin/python3

import sys

if len(sys.argv) < 2:
    sys.exit(-1)

with open(sys.argv[1], "r") as f:
    content = f.readlines()
    for line in content:
        if line[0] != '#':
            for word in line.split():
                if word == "PUSH":
                    sys.stdout.write('!')
                elif word == "POP":
                    sys.stdout.write('"')
                elif word == "DUP":
                    sys.stdout.write("#")
                elif word == "SWAP":
                    sys.stdout.write("$")
                elif word == "OVER":
                    sys.stdout.write("%")
                elif word == "ADD":
                    sys.stdout.write("&")
                elif word == "SUB":
                    sys.stdout.write("'")
                elif word == "OR":
                    sys.stdout.write("(")
                elif word == "XOR":
                    sys.stdout.write(")")
                elif word == "AND":
                    sys.stdout.write("*")
                elif word == "OC":
                    sys.stdout.write("+")
                elif word == "LOAD":
                    sys.stdout.write(",")
                elif word == "STORE":
                    sys.stdout.write("-")
                elif word == "GREATER":
                    sys.stdout.write(".")
                elif word == "LESS":
                    sys.stdout.write("/")
                elif word == "EQUALS":
                    sys.stdout.write("0")
                elif word == "IF":
                    sys.stdout.write("1")
                elif word == "NOT":
                    sys.stdout.write("2")
                elif word == "JUMP":
                    sys.stdout.write("3")
                elif word == "SYSCALL":
                    sys.stdout.write("4")
                else:
                    val = int(word)+33
                    sys.stdout.write(str(chr(val)))

print()
