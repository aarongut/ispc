import re
import sys

def floating2float(function, idx):
    typ = 'floating<' + str(idx) + '>'
    return function.replace(typ, 'float')

def floating2double(function, idx):
    typ = 'floating<' + str(idx) + '>'
    return function.replace(typ, 'double')

def number2float(function, idx):
    typ = 'number<' + str(idx) + '>'
    return function.replace(typ, 'float')

def number2double(function, idx):
    typ = 'number<' + str(idx) + '>'
    return function.replace(typ, 'double')

def number2int(function, idx):
    typ = 'number<' + str(idx) + '>'
    return function.replace(typ, 'int')

def number2long(function, idx):
    typ = 'number<' + str(idx) + '>'
    return function.replace(typ, 'long')

def number2short(function, idx):
    typ = 'number<' + str(idx) + '>'
    return function.replace(typ, 'short')

def number2char(function, idx):
    typ = 'number<' + str(idx) + '>'
    return function.replace(typ, 'char')

def integer2int(function, idx):
    typ = 'integer<' + str(idx) + '>'
    return function.replace(typ, 'int')

def integer2long(function, idx):
    typ = 'integer<' + str(idx) + '>'
    return function.replace(typ, 'long')

def integer2short(function, idx):
    typ = 'integer<' + str(idx) + '>'
    return function.replace(typ, 'short')

def integer2char(function, idx):
    typ = 'integer<' + str(idx) + '>'
    return function.replace(typ, 'char')

def strip_types(fun, i):
    return fun.replace('export', '').replace('void', '').replace('float', '') \
            .replace('double', '').replace('char','').replace('short','') \
            .replace('int','').replace('long','').replace('[]','') \
            .replace('*','').replace('(','_' + str(i) + '(') \
            .replace('uniform','')

if __name__ == '__main__':
    if (len(sys.argv) != 2):
        print 'usage:\n\tpython ',
        print sys.argv[0],
        print '[file.ispc]'
        exit(1)

    f = open(sys.argv[1], 'r')
    function = f.read()
    fun_def = re.findall(r'export [^{]*\)', function)[0]
    print fun_def
    f.close()

    floating = 0
    number = 0
    integer = 0

    while ('floating<' + str(floating) + '>' in function):
        floating += 1

    while ('number<' + str(number) + '>' in function):
        number += 1

    while ('integer<' + str(integer) + '>' in function):
        integer += 1

    for i in range(len(re.findall(r'floating[\s+]', function))):
        function = function.replace('floating ',
                                    'floating<' + str(floating) + '> ', 1)
        fun_def = fun_def.replace('floating ',
                                  'floating<' + str(floating) + '> ', 1)
        floating += 1

    for i in range(len(re.findall(r'number[\s+]', function))):
        function = function.replace('number ',
                                    'number<' + str(number) + '> ', 1)
        fun_def = fun_def.replace('number ',
                                  'number<' + str(number) + '> ', 1)
        number += 1

    for i in range(len(re.findall(r'integer[\s+]', function))):
        function = function.replace('integer ',
                                    'integer<' + str(integer) + '> ', 1)
        fun_def = fun_def.replace('integer ',
                                  'integer<' + str(integer) + '> ', 1)
        integer += 1

    floats = [[(fun_def, function)]]

    for i in range(floating):
        floats.append([])
        for (h, f) in floats[i]:
            floats[i+1].append((floating2float(h, i),
                                floating2float(f, i)
                               ))
            floats[i+1].append((floating2double(h, i),
                                floating2double(f, i)
                               ))

    numbers = [[]]

    for f in floats[floating]:
        numbers[0].append(f)

    for i in range(number):
        numbers.append([])
        for (h, f) in numbers[i]:
            numbers[i+1].append((number2float(h, i),
                                 number2float(f, i)
                               ))
            numbers[i+1].append((number2double(h, i),
                                 number2double(f, i)
                               ))
            numbers[i+1].append((number2int(h, i),
                                 number2int(f, i)
                               ))
            numbers[i+1].append((number2long(h, i),
                                 number2long(f, i)
                               ))
            numbers[i+1].append((number2short(h, i),
                                 number2short(f, i)
                               ))
            numbers[i+1].append((number2char(h, i),
                                 number2char(f, i)
                               ))

    integers = [[]]

    for f in numbers[number]:
        integers[0].append(f)

    for i in range(integer):
        integers.append([])
        for (h, f) in integers[i]:
            integers[i+1].append((integer2int(h, i),
                                 integer2int(f, i)
                                ))
            integers[i+1].append((integer2long(h, i),
                                 integer2long(f, i)
                                ))
            integers[i+1].append((integer2short(h, i),
                                 integer2short(f, i)
                                ))
            integers[i+1].append((integer2char(h, i),
                                 integer2char(f, i)
                                ))

    o = open(sys.argv[1] + '.pre.ispc', 'w')
    hdr = open(sys.argv[1] + '.h', 'w')

    hdr.write('#include "' + '.'.join(sys.argv[1].split('.')[:-1]) + '.h"\n\n')
    hdr.write('#ifndef _' + sys.argv[1].upper().replace('.', '_') + '_H_\n')
    hdr.write('#define _' + sys.argv[1].upper().replace('.', '_') + '_H_\n')
    hdr.write('namespace ispc {\n')

    fun_name = re.findall(r'[a-zA-Z_][a-zA-Z0-9_]*\(', function)[0][:-1]

    i = 0
    for (h, f) in integers[integer]:
        o.write(f.replace(fun_name, fun_name+'_'+str(i), 1))
        hdr.write(h.replace('uniform','').replace('export','') \
                  + '\n{\n\treturn ' + strip_types(h, i) + ';\n}\n\n')

        i += 1

    o.close()
    hdr.write('}\n')
    hdr.write('#endif\n')
    hdr.close()

    exit(0)
