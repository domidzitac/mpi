import subprocess
import sys
import time

def run_seq(n, f):
    subprocess.call(["../prime/prime", str(n)], stdout=f)

def run_mpi(n, f):
    subprocess.call(["mpiexec", "-n" , "8", "../prime_mpi/prime", str(n)], stdout=f)

def run(n):
    interval = n / 100;
    progress = 0;
    f_seq = open("result_seq.txt", "w")
    start_time = time.time();
    for i in range(11, n):
        run_seq(i, f_seq)
    end_time = time.time();
    f_seq.close()

    print("sequential prime program costs %s seconds" % (end_time - start_time))

    f_mpi = open("result_mpi.txt", "w")
    start_time = time.time()
    for i in range(11, n):
        run_mpi(i, f_mpi)
    end_time = time.time()
    f_mpi.close()

    print("mpi prime program costs %s seconds" % (end_time - start_time))

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print "Please input argument"
        sys.exit()
    run(int(sys.argv[1]))
