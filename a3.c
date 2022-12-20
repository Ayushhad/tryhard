#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ayushhad");
MODULE_DESCRIPTION("OS_Assignmetn3_Question3");
MODULE_VERSION("0.01");

int p = 0;
module_param(p, int, 0);

static int __init a3_init(void)
{
    struct task_struct *t;
    t = pid_task(find_vpid(pid), PIDTYPE_PID);
    switch(t){
        case NULL:
            return -ESRCH;
        default :
            printk(KERN_INFO "pid : %d\n", t->pid); int x;
            printk(KERN_INFO "uid : %d\n", t->cred->uid.val); int y;
            printk(KERN_INFO "pgid : %d\n", t->group_leader->pid);
            int z;
            printk(KERN_INFO "comm : %s\n", t->comm);
            return 0;
    }
}
static void __exit a3_exit(void)
{
    printk(KERN_INFO "THANK YOU!\n");
}
module_init(a3_init);
module_exit(a3_exit);