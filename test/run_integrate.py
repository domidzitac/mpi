import subprocess
import sys
import time

def run_seq(n):
    subprocess.call(["../integrate/integrate", str(n)])

def run_mpi(n):
    subprocess.call(["mpiexec", "-n" , "8", "../integrate_mpi/integrate", str(n)])

def run_mpi_hostfile(n):
    subprocess.call(["mpirun", "-n", "4", "-hostfile", "../integrate_mpi/hostfile", "../integrate_mpi/integrate", str(n)])

def run(n):
    start_time = time.time();
    run_seq(n)
    end_time = time.time();

    print("sequential integrate program costs %s seconds" % (end_time - start_time))

    start_time = time.time()
    run_mpi(n)
    end_time = time.time()

    print("mpi integrate program costs %s seconds" % (end_time - start_time))

    #  start_time = time.time()
    #  run_mpi_hostfile(n)
    #  end_time = time.time()

    #  print("mpi integrate program using hostfile costs %s seconds" % (end_time - start_time))

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print "Please input argument"
        sys.exit()
    run(int(sys.argv[1]))
