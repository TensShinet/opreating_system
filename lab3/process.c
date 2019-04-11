#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>

#define HZ 100 


void cpuio_bound(int last_time, int cpu_time, int io_time);

int main() {

    pid_t ps[10];
    int i = 0;

    for(i = 0; i < 10; i++) {

        pid_t p = fork();
        if(p == 0) {
            // cpuio_bound(20, 2 * i, 20 - 2 * i); // 每个子进程都占用20s
            cpuio_bound(2, 1, 1);
            printf("fuck\n");
            return 0;                           // 执行完cpuio_bound 以后，结束该子进程
        } else if(p < 0) {
            printf("创建子进程失败");
        } else {
            // 父进程
            ps[i] = p;
            // printf("fuck1");
        }
    }


    // 打印所有子进程PID
    for (i = 0; i < 10; i++)
        printf("Child PID: %d\n", ps[i]);
    // 等待所有子进程完成
    wait(&i); /*Linux 0.11 上 gcc要求必须有一个参数, gcc3.4+则不需要*/

    return 0;
}

void cpuio_bound(int last_time, int cpu_time, int io_time) {
    struct tms t1, t2;
    clock_t utime, stime;
    times(&t1);
    while(last_time > 0) {
        // cpu_time
        do {
            
            times(&t2);
            utime = t2.tms_utime - t1.tms_utime;
            stime = t2.tms_stime - t1.tms_stime;
        } while ((utime + stime) / HZ < cpu_time );

        last_time -= cpu_time;

        if(last_time <= 0) {
            break;
        }

        // 用 sleep 模拟 io time
        sleep(io_time);
        last_time -= io_time;
    }
}