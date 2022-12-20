#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <linux/syscall.h>
#include <linux/sched.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ayushhad");
MODULE_DESCRIPTION("OS_Sys_call");
MODULE_VERSION("0.01");

int pid = 0;
module_param(pid, int, 0);

static int __init a3_init(void)
{
    struct task_struct *t;
    t = pid_task(find_vpid(pid), PIDTYPE_PID);
    printk(KERN_INFO "uid: %d\n", t->cred->uid.val);
    printk(KERN_INFO "pgid: %d\n", t->group_leader->pid);
    printk(KERN_INFO "comm : %s\n", t->comm);
    printk(KERN_INFO "pid: %d\n", t->pid);
    return 0;
}
static void __exit a3_exit(void)
{
    printk(KERN_INFO "Thank You!\n");
}
module_init(a3_init);
module_exit(a3_exit);
