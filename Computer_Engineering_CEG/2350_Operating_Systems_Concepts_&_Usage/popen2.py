import sys 
import subprocess

# Open file to append output from p2
anotherFile = open("result.txt", "a") 

#p1 = subprocess.Popen(['netstat', '-ano'], 
#                           stdout = subprocess.PIPE)
# Execute the 'type popen.py' command in a shell and pipe output
p1 = subprocess.Popen(['type', 'popen.py'],
                           stdout = subprocess.PIPE,
                           shell=True)
# Execute 'find "import"' command in a shell taking input from p1 and
# sending output to anotherFile
p2 = subprocess.Popen('find "import"', 
                          stdin = p1.stdout, 
                          stdout = anotherFile, shell=True).communicate()

# Closing anotherFile flushes any data written to the file.
anotherFile.close()
