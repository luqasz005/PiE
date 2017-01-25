import numpy as np


def open_file(name):
    with open(name, 'r') as infile:
        count = 0
        print ('Nazwa: {}'.format(name))
        size = [int(x) for x in name[:name.rfind('.')].split('x')]
        l = [[] for y in range(size[2])]
        for line in infile:
            line = line.strip()
            z = int(count/size[1])
            if len(line) > 0:
                l[z].append([int(float(a)) for a in line.split()])
            if not line == "":
                count += 1
    return l, size



def open_file_bin(name):
    print ('Nazwa: {}'.format(name))
    size = [int(x) for x in name[:name.rfind('.')].split('x')]
    asize = np.prod(size)
    l = np.fromfile(name, dtype='B', count=asize)
    l = np.reshape(l, (size[2], size[1], size[0]))
    return l, size


def save_file_bin(out_name, matrix):
    out = np.asarray(matrix, 'B')
    out.tofile(out_name)
    print('Zapisano do pliku:{}'.format(out_name))
    


def save_file(out_name, matrix):
    with open(out_name, 'w') as outfile:
        for x in matrix:
            for y in x:
                for z in y:
                    outfile.write('{:<15f} '.format(z))
                outfile.write("\n")
        outfile.write("\n")
    print('Zapisano do pliku:{}'.format(out_name))
