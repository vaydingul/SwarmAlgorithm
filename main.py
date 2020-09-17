import os

def makeHeaderFile(className):
    lines = []
    clsNameUpper = className.upper()

    temp = "#ifndef " + clsNameUpper + "\n" + "#define " + clsNameUpper + "\n"
    lines.append(temp)

    temp = "class " + className + "\n" + "{" + "\n" + "public:" + "\n" + className + "();" + "\n" + "~" + className + "();" + "\n"
    lines.append(temp)

    temp = "private:" + "\n" + "protected:" + "\n" + "};" + "\n"
    lines.append(temp)

    temp = "#include " + "\"../source/" + className + ".cpp\"" + "\n" 
    lines.append(temp)

    temp = "#endif"
    lines.append(temp)

    fname = "header/" + className + ".h"
    with open(fname, 'w') as fileWrite:
        for line in lines:
            fileWrite.writelines(line)


def makeSourceFile(className):
    lines = []
    clsNameUpper = className.upper()

    temp = className + "::" + className + "()" + "{" + "\n\n" + "}" + "\n\n"
    lines.append(temp)

    temp = className + "::" + "~" + className + "()" + "{" + "\n\n" + "}" + "\n\n"
    lines.append(temp)


    fname = "source/" + className + ".cpp"
    with open(fname, 'w') as fileWrite:
        for line in lines:
            fileWrite.writelines(line)




 
#Config file stream
file = open('class.config', 'r')
classes = file.read() #read file
classes = classes.split() #parse file

#Creation of headers and sources folders
cmd = "md header source"
os.system(cmd)

#Header file creation
for _class in classes:
    makeHeaderFile(_class)
    makeSourceFile(_class)



