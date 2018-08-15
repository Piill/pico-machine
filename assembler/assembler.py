#!/usr/bin/python3

import sys

if len(sys.argv) < 2:
    sys.exit(-1)

instructions = {
        "PUSH":'!',
        "POP":'"',
        "DUP":"#",
        "SWAP":"$",
        "OVER":"%",
        "ADD":"&",
        "SUB":"'",
        "OR":"(",
        "XOR":")",
        "AND":"*",
        "OC":"+",
        "LOAD":",",
        "STORE":"-",
        "GREATER":".",
        "LESS":"/",
        "EQUALS":"0",
        "IF":"1",
        "NOT":"2",
        "JUMP":"3",
        "SYSCALL":"4"
        }
labels = {}
addr = 0

with open(sys.argv[1], "r") as f:
    content = f.readlines()
    for line in content:
        if line[0] != '#':
            lineCount = 0
            for word in line.split():
                if not word in instructions and not word[0].isdigit() and not word in labels and lineCount == 0:
                    labels[word] = addr
                    addr -= 1
                addr += 1
                lineCount += 1

    addr = 0
    for line in content:
        lineCount = 0
        if line[0] != '#':
            for word in line.split():
                if word in instructions:
                    sys.stdout.write(instructions[word])
                    lineCount += 1
                elif word[0].isdigit():
                    val = int(word)+33
                    sys.stdout.write(str(chr(val)))
                elif word in labels and lineCount > 0:
                    sys.stdout.write(str(chr(labels[word]+33)))
                else:
                    labels[word] = addr
                    addr -= 1

                addr += 1

print()
