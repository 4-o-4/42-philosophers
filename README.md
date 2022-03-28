# philosophers

#### Build and running the project
```sh
make && ./philo arg1 arg2 arg3 arg4 (arg5)
```

- arg1 is the number of philosopher
- arg2 is the time to die in ms
- arg3 is the time to eat in ms
- arg4 is the time to sleep in ms
- arg5 (optional) how many times each philosopher should eat

#### Tests
```sh
./philo 0 100 100 100         # exit with error
./philo 1 100 100 100         # should die
./philo 2 2 1 1               # should live
./philo 2 400 200 200         # should live
./philo 2 400 201 200         # should die
./philo 2 399 200 200         # should die
./philo 2 100 300 50          # should die
./philo 2 100 50 100          # should die
./philo 3 99 33 33            # should live
./philo 3 99 34 33            # should die
./philo 4 400 200 200         # should live
./philo 4 500 200 2147483647  # should die
./philo 5 400 200 200         # should die
./philo 5 800 200 200 7       # the simulation stops when each philosopher has eaten 7 times
./philo 21 30 10 10           # should live
./philo 200 210 100 100       # should live
```

#### Ressources
- [System Programming in C for UNIX](https://pub.phyks.me/sdz/sdz/la-programmation-systeme-en-c-sous-unix.html#Lesthreads)
- [Multithreading in C](https://www.geeksforgeeks.org/multithreading-c-2/)
- [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/)
- [How to Use C Mutex Lock Examples for Linux Thread Synchronization](https://www.thegeekstuff.com/2012/05/c-mutex-examples/)
- [Mutex lock for Linux Thread Synchronization](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)
- [French tutorial](https://franckh.developpez.com/tutoriels/posix/pthreads/)
- [How to create and join threads in C](https://youtu.be/uA8X5zNOGw8)
- [Safety and Speed Issues with Threads](https://youtu.be/9axu8CUvOKY)
- [Mutex Synchronization in Linux with Pthreads](https://youtu.be/GXXE42bkqQk)
- [Multithreading Code - Computerphile](https://youtu.be/7ENFeb-J75k)
- [Dining Philosophers Problem with Solution](https://youtu.be/NbwbQQB7xNQ)
