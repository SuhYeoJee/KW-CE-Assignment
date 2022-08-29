
infile = open('phone.txt','r')
'''
line = infile.readline()
while line !='':
    line = line.rstrip()
    print(line)
    line= infile.readline()
infile.close()
'''
for line in infile:
    line = line.rstrip()
    print(line)
infile.close()
