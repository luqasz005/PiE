import sys
import getopt
import bib_filtr_wrap
import filtryio
import re


def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "m:u:s:w:")
    except getopt.GetoptError:
        print("\nNie podano nazwy pliku lub zły znak filtru!")
        sys.exit(2)

    if len(opts)==0 and len(args)==0:
        print("\nProgram do trójwymiariej filtracji obrazu")
        print("Podaj nazwę pliku do filtracji zgondie ze wzorem:\n")
        print("\t Filtry znakfiltru nazwapliku\n")
        print("Nazwa pliku musi być w foramcie:\n")
        print("\t <rozmiarX>x<rozmiarY>x<rozmiarZ>.<rozszerzenie>\n")
        print("Znaki filtrów:\n")
        print("-u\tfiltr uśredniajacy")
        print("-w\tfiltr wysotrzajacy")
        print("-m\tfiltr medianowy")
        print("-s\tfiltr Sobla")

    elif len(opts)==1:
        for opt, arg in opts:
            if re.match('^[0-9]*x[0-9]*x[0-9]*.[a-zA-Z]{3}$',arg):
                filetype = arg[(arg.rfind('.')+1):]
                filebin = False

                if filetype in ('raw','bin'):
                    print("Plik binarny")
                    filebin = True
                    mat, size = filtryio.open_file_bin(arg)
                else:
                    print("Plik tekstowy")
                    mat, size = filtryio.open_file(arg)

                if opt == '-m':
                    print('Filtr medianowy')
                    result = bib_filtr_wrap.medianowy(mat, 3)
                    name = "M_{}".format(arg)
                    if filebin:
                        filtryio.save_file_bin(name, result)
                    else:
                        filtryio.save_file(name, result)
                elif opt == "-u":
                    print('Filtr uśredniajacy')
                    result = bib_filtr_wrap.usredniajacy(mat, 3)
                    name = "U_{}".format(arg)
                    if filebin:
                        filtryio.save_file_bin(name, result)
                    else:
                        filtryio.save_file(name, result)
                elif opt == "-w":
                    print('Filtr wysotrzajacy')
                    result = bib_filtr_wrap.wyostrzajacy(mat, 3)
                    name = "W_{}".format(arg)
                    if filebin:
                        filtryio.save_file_bin(name, result)
                    else:
                        filtryio.save_file(name, result)
                elif opt == "-s":
                    print('Filtr Sobla')
                    result = bib_filtr_wrap.sobel3d(mat)
                    name = "S_{}".format(arg)
                    if filebin:
                        filtryio.save_file_bin(name, result)
                    else:
                        filtryio.save_file(name, result)
                else:
                    print("ERROR")

            else:
                print("Nazwa pliku niezgodna z formatem:\n")
                print("\t <rozmiarX>x<rozmiarY>x<rozmiarZ>.<rozszerzenie>")
    else:
        print("Złe argumenty")
    

if __name__ == "__main__":
    main()
