# Class Activity 2 — Process Creation

- **Student Name:** [HAO Ratha]
- **Student ID:** e20230769
- **Date:** [11 Nov 2026]

---

## Task 1: Process Creation on Linux (`fork` + `exec`)

**Describe your implementation:** `forkchild.c` calls `fork()` to create a child process. The child prints its PID and its parent's PID, sleeps for 30 seconds so the process tree can be observed, and then replaces itself with `ls -la` using `execlp()`. The parent waits for the child with `waitpid()`, prints the child's exit status, and then prints a final message.

### Program output (Terminal 1)

<!-- Screenshot: gcc forkchild.c -o forkchild && ./forkchild -->
![forkchild output](screenshots/task1_forkchild_output.png)

### Process tree observation (Terminal 2)

<!-- Screenshot: ps -ef --forest | grep forkchild  (run while the child is sleeping) -->
![process tree](screenshots/task1_process_tree.png)

```
$ ps -ef --forest | grep forkchild
ratha      10052     403  0 08:49 pts/0    00:00:00  |           \_ ./forkchild
ratha      10053   10052  0 08:49 pts/0    00:00:00  |               \_ ./forkchild
ratha      10147    9675  0 08:49 pts/2    00:00:00              \_ grep --color=auto forkchild
```

### `ls -la` result produced by the child

```
total 32
drwxr-xr-x 2 ratha ratha  4096 Oct 30 08:41 .
drwxr-xr-x 7 ratha ratha  4096 Oct 30 08:30 ..
-rwxr-xr-x 1 ratha ratha 16400 Oct 30 08:41 forkchild
-rw-r--r-- 1 ratha ratha  1431 Oct 30 08:41 forkchild.c
-rw-r--r-- 1 ratha ratha     0 Oct 30 08:41 result_forkchild.txt
```

### Questions

1. **What does `fork()` return to the parent? What does it return to the child?**

   > `fork()` returns twice, once in each process. In the parent it returns the PID of the new child (10053 in my run). In the child it returns `0`. If it fails, it returns `-1` to the parent and no child is created. The program uses this return value to decide which branch to run: `pid == 0` is the child code, and `pid > 0` is the parent code.

2. **What happens if you remove the `waitpid()` call? Why might the output look different?**

   > Without `waitpid()`, the parent does not wait for the child. It prints "Parent: done." and exits right away, while the child is still sleeping for 30 seconds. Two things change:
   > - **Output order:** the shell prompt returns immediately, and the child's messages and the `ls -la` listing appear 30 seconds later, after the prompt and mixed with whatever I type. The parent's final message no longer comes after the child's output.
   > - **Process state:** the child becomes an orphan and is adopted by `init`/`systemd` (its PPID changes). If the parent kept running without waiting, a finished child would stay as a zombie, because nobody collects its exit status.
   >
   > `waitpid()` makes the parent block until the child ends, so the output is ordered and the child's exit status can be read.

3. **What does `execlp()` do? Why don't we see "execlp failed" when it succeeds?**

   > `execlp("ls", "ls", "-la", NULL)` replaces the current process image with a new program. It searches for `ls` in the directories listed in `PATH`, loads it, and starts running it with the arguments `ls -la` (the list ends with `NULL`). The PID stays the same, but the code, data, and stack of the old program are gone.
   >
   > Because the old program no longer exists after a successful `exec`, the lines after it (`perror("execlp")` and `exit`) are never reached. `execlp()` only returns if it fails, for example when the command is not found. So "execlp failed" would print only on an error.

4. **Draw the process tree for your program (parent → child). Include PIDs from your output.**

   > ```
   > bash (PID 403, pts/0)
   >  └── ./forkchild  (PID 10052)   ← parent
   >       └── ./forkchild  (PID 10053, PPID 10052)   ← child
   >             └── after exec: ls -la (same PID 10053)
   > ```
   >
   > The shell started the parent, the parent created the child with `fork()`, and the child later turned into `ls -la` with `execlp()` while keeping PID 10053.

5. **Which command did you use to view the process tree (`ps --forest`, `pstree`, or `htop`)? What information does each column show?**

   > I used `ps -ef --forest | grep forkchild` from a second terminal while the child was sleeping.
   >
   > | Column | Meaning |
   > |---|---|
   > | UID | user that owns the process (`ratha`) |
   > | PID | process ID (10052 parent, 10053 child) |
   > | PPID | parent process ID (the child's PPID is 10052, the parent's is 403, the shell) |
   > | C | CPU utilization (0, because both processes are sleeping) |
   > | STIME | time the process started (08:49) |
   > | TTY | terminal it is attached to (`pts/0`) |
   > | TIME | total CPU time used (00:00:00) |
   > | CMD | the command, drawn as a tree by `--forest` (`\_` shows a child under its parent) |
   >
   > The PPID column is the key one: the child's PPID equals the parent's PID, which proves the parent-child relationship. The `grep` line in the output is just my search command and can be ignored.

---

## Reflection

What did you learn from this activity?

> [Write your reflection here. Example: I learned that `fork()` creates a copy of the running process and returns different values to the parent and child, and that `exec()` replaces the child's program while keeping its PID. I also saw how `waitpid()` keeps the parent from finishing before the child, and how the PPID column in `ps` shows the parent-child relationship.]
