import csv
import cs50
import sys



headerdb = 0
bodydb = list()
#tem que realizar a contagem de sequências de DNA CONSECUTIVAS
database = sys.argv[1]
fileset = sys.argv[2]
#abrindo e lendos os conteúdos
with open(database,"r") as database:
    read = csv.reader(database)
    headerdb = next(read)
    sequences = headerdb[1:]
    #print(sequences)
    for row in read:
        bodydb.append(row)#copiando cada linha sendo nome + sequências

    with open(fileset,"r") as fileset:
        sequences_values = list([0]*len(sequences))#lista vazia para contar as quatd max de vezes que a cadeia apareceu
        line = fileset.readline()#capturar somente toda a linha 01
        #print(line)
        for code in sequences:#ele vai repetir o cód 1 - "TAAGC" 2- "GATGC" ....
            countcodes=0
            # for i in range(0,len(line)):
            #     if line[i:i+len(code)] == code:
            #         countcodes += 1
            #         #print(sequences[sequences.index(line[i:i+len(code)])])
            #     else:
            #         countcodes = 0
            index=0#rastrear a posição do cursor ao ler a linha de DNA
            while index <= len(line):
                if line[index:index+len(code)] == code:
                    #print(f"{line[index:index+len(code)]} - {index}")
                    countcodes += 1
                    index+=len(code) #jogar o cursor para o próx caractere depois do final do cursor
                elif sequences_values[sequences.index(code)] < countcodes:
                    sequences_values[sequences.index(code)] = countcodes
                    countcodes = 0
                    index+=1
                else:
                    countcodes = 0
                    index+=1
        sequences_values = [str(x) for x in sequences_values]#convertendo em str
        #print(sequences_values)
    for people in bodydb:#número de vezes que houve semelhança
        if (sequences_values == people[1:]):
            print(people[0])
            sys.exit(0)

    print("No match")
    sys.exit(0)


#with open(fileset,"r") as fs:  #name | AGATC | TTTTTTCT | AATG | TCTAG | GATA | TATC | GAAA | TCTG
#ATTAGGATAGTCAGTAGA
