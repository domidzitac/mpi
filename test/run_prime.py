import subprocess
import sys
import time

def run_seq(n):
    subprocess.call(["../prime/prime", str(n)])

def run_mpi(n):
    subprocess.call(["mpiexec", "-n" , "8", "../prime_mpi/prime", str(n)])

def run(n):
    start_time = time.time();
    run_seq(n)
    end_time = time.time();

    print("sequential prime program costs %s seconds" % (end_time - start_time))

    start_time = time.time()
    run_mpi(n)
    end_time = time.time()

    print("mpi prime program costs %s seconds" % (end_time - start_time))

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print "Please input argument"
        sys.exit()
    run(int(sys.argv[1]))
