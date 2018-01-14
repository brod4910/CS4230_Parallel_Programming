# Analyis script file for illustrating false sharing to students of Parallel
# Programming CS 4230

class FalseSharing(object):
    """docstring for FalseSharing."""
    def __init__(self, arg):
        super(FalseSharing, self).__init__()
        self.arg = arg

    def genData(arg):
    # invoke program with cartesian product of the padding x num_threads
    # a system call here
    for p in padding:
        for t in num_threads:
            # ./FalseSharing.exe p t

    # |--> edit executable to write out the arguments and time consumed

    def analyzeData(arg):
        # read the .dat file
        # plot 3d graph
        # X-axis : padding
        # Y-axis : num_threads
        # Z-axis : elapsed time

def main():
    # create a data structure containing values of padding
    padding     = [2,8,32,64,128,256,512]

    # create a data structure containing values of num_threads
    num_threads = [2,4,8]
    FalseSharing f;
    f.genData()
    f.analyzeData(

if __name__ == '__main__':
    main()
