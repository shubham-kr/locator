import re
import matplotlib.pyplot as plt
from optparse import OptionParser

def ReadLogFile(LogFile):
    global x, y
    global x_filt, y_filt
    try:
        with open(LogFile, 'r') as log: all_lines = log.read().split('\n')
    except:
        print("Error!!!  log file cannot be opened\n" + LogFile)
        exit()
        
    for line in all_lines:
        if (re.search('WLS,',line)):
            tmpline = line.split(',')
            
            x.append(float(tmpline[3]))
            y.append(float(tmpline[4]))
            
        if (re.search('FFIX,',line)):
            tmpline = line.split(',')
            
            x_filt.append(float(tmpline[3]))
            y_filt.append(float(tmpline[4]))

x =  []
y = []
x_filt = []
y_filt = []
    
def main():   
    parser = OptionParser ()
    parser.add_option ("-f", "--log",type="str", dest="file", default="",help="Processedfile")

    (options, args) = parser.parse_args ()
  
    if options.file:
        print('Processing logfile name:' + options.file)
        
        ReadLogFile(options.file)
        groups = ("Raw", "Filtered")
        colors = ("blue", "yellow")
        
        fig = plt.figure()
        ax = fig.add_subplot(1, 1, 1)
        
        ax.scatter(x, y, c=colors[0], label = groups[0])
        ax.scatter(x_filt, y_filt, c=colors[1], label=groups[1])
        plt.title('Scatter plot User Position')
        plt.legend()
        #plt.show()
        plt.savefig('Plot.png')
    
    else:
        print("Missing log file")
  
  
if __name__ == '__main__':
    main()