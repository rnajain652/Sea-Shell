#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <signal.h>

struct process
{
    char name[1000];
    int pid;
};

int p_cnt, for_proc;
char for_proc_name[1000];
int kjob_stop;
struct process p_arr[1000];
int mypipe1[2], mypipe2[2];
int controlD;
int flag_hyphen;
void echo();
void kjob();
void overkill();
void history_wr();
void hist_show();
void handler();
char *ignorespace();
void compare();
void input();
char *inp, *cmd, *cmdline, *in_cmd, *out_cmd, exe_part[1000];

void redirection();
void piping();

void ls(char *dirname);

void pwd();
void cd();
char cwd[1000], tilde[1000], prev_dir[1000];

#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

void prompt();
char hname[1001], lname[1001];

void syscmd();

void setenvv();
void unsetenvv();
void bg();
void fg();