import os

path = "drones/"
filesToDelete = os.listdir(path)

for file in filesToDelete:
    file = path + file
    os.remove(file)