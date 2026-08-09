# Linux 101/201（🚧施工中）

> **“享受极客精神与开源文化”**

!!! 相关课程
    - Linux 101：https://101.lug.ustc.edu.cn/
	- Linux 201：https://201.ustclug.org/

---

## Linux 发行版

> Linux 自由、开源的特性注定了它的发展进程必定是一个去中心化的、非线性的形式。
>
> 也正如此，Linux 在短短的三十年里，能在如此繁茂的分支上结出诸多硕果，这便是开源社区文化的强大活力。

### Debian 分支

"Debian GNU/Linux"因坚持自由软件精神和生态环境优良而出名，拥有庞大的用户群体。它也派生了很多发行版（如 Ubuntu），为普通用户提供了一个时新且稳定的 OS。

<div style="display: flex; justify-content: center; align-items: center; gap: 2rem; margin: 1rem 0;">
  <img src="../图片和附件/image%206.png" alt="Debian" style="max-width: 48%;">
  <img src="../图片和附件/image%205.png" alt="Ubuntu" style="max-width: 48%;">
</div>


### Red Hat 分支

Red Hat Linux 是一个历史悠久的发行版，但在 2003 年 Red Hat 公司停止维护，转而将精力都投入企业版 Red Hat Enterprise Linux（简称 RHEL）上了，终究还是走向了商业市场导向。

而在 Red Hat Linux 停止官方更新后，社群启动了 Fedora 发行版，它是一套功能完备且更新迅速的系统，且本身计划受到了 Red Hat 公司的赞助。

但毕竟得遵循 GPL 许可证，编译开源源码可以重新得到可以使用的 OS，称之为 CentOS，适合在要求高度稳定的服务器上运行。不过在 2020 年的时候，CentOS 社区宣布转向 CentOS Stream，这是全新的滚动发行版，成为了 RHEL 的上游发行版，且原 CentOS 版本将不再受支持。

<div style="display: flex; justify-content: center; align-items: center; gap: 1rem; margin: 1rem 0;">
  <img src="../图片和附件/image%208.png" alt="Debian" style="max-width: 48%;">
  <img src="../图片和附件/image%202.png" alt="Ubuntu" style="max-width: 48%;">
  <img src="../图片和附件/image%207.png" alt="Ubuntu" style="max-width: 48%;">
</div>

### Arch Linux 分支

Arch Linux 是一个基于 x86\-64 架构的发行版，因“简单、现代、实在、人本、万能”的宗旨赢得了广泛青睐。但它上手难度较大，因为它重在构建优雅、极简的代码结构，需要使用者去理解 OS 的运作方式。

正因这个特殊的设计理念，为了让一般用户也能用上 Arch Linux 的强大功能，它的变种 Manjaro 发行版于 2011 年问世，它更注重易用。

![image\.png](图片和附件/image.png)

![image\.png](图片和附件/image%201.png)

## 软件安装

### 应用商店

在 Ubuntu 下可以使用 Ubuntu Application Store 来进行安装，比较小白。

### 软件包管理器

相比于前者，显然包管理器的使用会更加广泛，一行命令即可安装，优雅而快速。

包管理系统有很多，具体如下（我还是喜欢 Ubuntu 亿点点，所以默认 apt 啦）：

- Debian、Ubuntu：包管理器 dpkg，前端 apt；

- Fedora、CentOS：包管理器 rpm，前端 dnf；

- Arch Linux、Manjaro：包管理器 pacman。

可以通过调用 `sudo apt install ...` 的方式安装包，不过 Ubuntu 官方源位于国外，往往会有速度与延迟上的限制，可以通过修改官方源为其镜像实现更快的下载速度。具体在 `/etc/apt/sources.list` 中，官方源地址为 `http://archive.ubuntu.com/`，将其改为任何一个镜像，比如 `http://mirrors.ustc.edu.cn`。

## 文件操作

### 查看文件 / 文件夹内容

- `ls` 有个替代品叫 `eza`，输出颜色更丰富。

- `cat` 有个替代品叫 `bat`，输出有语法高亮和分页。

- `less` 很好用，一次显示一页，有很丰富的功能。

### 搜索文件 / 目录

```Bash
$ # 在 PATH（路径）中根据 EXPRESSION（表达式）搜索文件
$ find [OPTION] PATH [EXPRESSION]
```

### 使用 tar 打包、压缩

```Bash
tar -czvf target.tar.gz test/
```

可以将 test/ 文件夹下的所有内容全部打包到 target\.tar\.gz 中。

## 进程、前后台、例行性任务

### 查看进程

`ps` (Process Status) 是常用的输出进程状态的工具。直接调用 `ps` 仅会显示本终端运行的相关进程，而 `ps aux` 会显示所有进程。一个更为现代的指令是 `htop`，它更加可视化，更好用。

### 控制进程

信号用于进程之间相互通信，指令为 `kill`。我们可以粗略地把进程分为三大类：运行态（running）、就绪态（ready）、阻塞态（blocked），据此引出几个常见的信号（描述挺通俗易懂的hhh）：

![image\.png](图片和附件/image%204.png)

### 前后台切换

在 shell 中直接执行命令时，它会挂在前台，当前 shell 无法继续干其他事情。我们可以在指令的后面加个 `&` 让它挂在后台，例如 `ping www.baidu.com &`。

```Bash
$ kill -l
 1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
 6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
63) SIGRTMAX-1  64) SIGRTMAX
```

如果要杀死进程，直接 kill 不带任何参数的话，默认是 15 (SIGTERM)，意味着一个进程的自然死亡。但如果需要立刻结束进程，我们需要使用 `kill -9 PID`，表示 SIGKILL。

### 脱离终端（解耦）

当关闭终端时，它会向每个进程发送 SIGHUP（SIGnal HangUP），意味着退出程序运行，因此我们需要让指令的运行不依赖于终端。

- nohup，字面意思就是不要被 SIGHUP 影响，它的输出默认被重定向到当前目录下的 `nohup.out`。在指令开头加上 `nohup ` 即可。

### 命令行多终端

`tmux` 是一个分屏的、运行在命令行的模拟终端，意味着只要有命令行可用，就可以把多个交互进程集成在一个窗口上。tmux 由会话（session）、窗口（window）、面板（pane）组织起每个 shell 的输入框，会话用于区分不同的工作；窗口是会话中以显示屏为单位的不同页；而面板则是一个窗口上被白线分割的不同区域。

Ctrl\+B 是 tmux 的全局前缀命令，按下该快捷键表示让 tmux 接收命令，具体指令如下：

为了支持鼠标滚轮上下滑动，我们可以在 tmux 后按 Ctrl\+B，然后输入 `:`，接着输入 `set -g mouse on`，这样就 OK 啦。不过这是临时起效，要想一劳永逸，就需要在 `~/.tmux.conf` 中操作，然后 `tmux source ~/.tmux.conf` 即可\~

### 例行性任务

例行性任务是指基于时间的多次周期定时任务。Linux 中主要是 at 和 crontab，但前者只能单次，我真要用肯定也是长期任务，不如用 crontab。

Crontab 的配置格式很简单，前半段为时间，后半段为 shell 指令，具体如下：

```Bash
# 分   时   日   月   星期  | 命令
*  *  *  *  *  echo "hello" >> ~/count
# 每分钟输出 hello 到家目录下 count 文件
0,15,30,45 0-6 * JAN SUN  command
# 随意举一个例子，翻译过来是每年一月份的每个星期日半夜 0 点到早晨 6 点每 15 分钟随便做点什么
```

有的时候，我们需要定时执行一些需要不少时间的任务，例如系统备份。如果这个任务的执行时间超过了 crontab 中两次任务执行的时间间隔，会发生什么事情？如果用 systemd timer，能否避免这个问题？



如果仍然需要使用 crontab，那么可以考虑使用 `flock`。首先指定一个「锁」文件，然后将命令改成这样：`flock -n [锁文件的路径] [你需要执行的命令]`

这样的话，如果其他命令正在执行，那么这个文件锁会被其占用；crontab 尝试再执行命令时，flock 会发现对应的文件已经锁上，因此会立刻退出（`-n` 参数）。

## 用户（组）与权限

### 用户与用户组

root 的家在 `/root`，普通用户的家在 `/home/{user_name}`，平时没啥事不要拿着 root 瞎搞。如果要切换用户，可以用 `su {user_name}` 指令，不填默认 root。

值得一提的是，Ubuntu 默认禁止了 root 用户的密码登录，只能通过 `sudo` 提权，不过我们仍然可以巧妙的使用 `sudo su` 来得到 root 权限。

用户组是用户的集合，通过用户组机制，可以为一批用户设置权限。用 groups 命令，可以查看当前用户所属的用户组有哪些。

```Bash
$ groups
alan233 adm cdrom sudo dip plugdev users docker
```

### 用户配置

- 修改密码：用 `passwd {user_name}`（不填则默认当前用户）。

- 添加用户：用 `adduser 用户名` 添加新用户，`adduser --group 组名` 添加新用户组，`adduser 用户名 组名` 将用户加入指定用户组。

### 文件权限

每个文件和目录都有自己的权限，可以使用 `ls -l` 查看当前目录中文件的详细信息。

```Bash
$ ls -l
total 8
-rwxrw-r-- 1 ustc ustc   40 Feb  3 22:37 a_file
drwxrwxr-x 2 ustc ustc 4096 Feb  3 22:38 a_folder
```

橙色为文件类型，红色为文件所属用户权限，绿色为文件所属用户组权限，黄色为其他人权限。对于每一份权限，第一位 `r` 表示读取，第二位 `w` 表示写入，第三位 `x` 表示执行，若为 `-` 表示无此权限。

紫色表示文件所属用户，蓝色表示文件所属用户组。

涉及到权限不足的问题，可以使用 chmod (change file mode bits) 修改权限、或者 chown (change file owner) 修改文件所有者。

## 文本处理与网络请求

> 我觉得 wc、diff、sed 已经没那么重要了，这更多是古法编程产物，因此略。
> 
> 

### I/O 重定向

这个已经很熟练了，主要是 0 stdin、1 stdout、2 stderr，`>` 默认是 `1>`。这里的重定向，相当于给某个流做一个输出地方的线性变换（一开始默认是终端）。

比如 `2>&1`，就是把错误流输出到目前标准流指向的地方，`./main 2>&1 > /dev/null`，效果等价于只在终端输出错误流、并且 `2>&1` 没起什么效果，因为指令是自左向右解析的。

### 管道

管道（pipe）符号为 `|`，作用为将左边命令的 stdout 接到右边命令的 stdin，管道不会处理 stderr。

![image\.png](图片和附件/image%203.png)

```Bash
$ ls / | grep bin  # 筛选 ls / 输出中所有包含 bin 字符串的行
bin
sbin
```

### 网络下载

- `wget` 是强力方便的下载工具，通过 HTTP 和 FTP 协议从因特网中检索并获取文件。

    - `wget 链接` 即可；如果想要后台下载，可以 `wget -b 链接`。 

- `curl` 是一个利用 URL 语法在命令行下工作的文件传输工具，其中 c 意为 client。它可以自定义各种请求参数，因此在模拟 web 请求方面更擅长；wget 由于支持 FTP 协议和递归遍历，因此在下载文件方面更擅长。

    - `curl 链接` 即可得到响应体，而 `curl -I 链接` 只展示响应头；对应的，`curl -i 链接` 就有响应头\+响应体。

## Docker

> 虚拟机（VM）是完全的虚拟化，包括内核和用户空间；而 Docker 是共用同一个 Linux 内核的。
> 
> 

容器通过 OS Kernel 提供的隔离技术，实现轻量级的虚拟化环境。而 Docker 是 Linux 容器技术中的代表性软件，它为用户提供了方便的接口来创建、使用 Linux 容器。

Docker 官方提供了安装 Docker 社区版本的简易安装脚本：

```Bash
$ curl -fsSL https://get.docker.com -o get-docker.sh
$ sudo sh get-docker.sh
sudo adduser 用户名 docker
```

可以使用官方提供的 Hello World 测试 Docker 是否安装成功：

```Bash
$ docker run --rm hello-world
...
Hello from Docker!
This message shows that your installation appears to be working correctly.
...
```

它的语法也比较自然，可以把挂载宿主机的目录、端口映射，类似下面：

```Bash
docker run -it -v ${PWD}/Linux101-docs:/docs -p 8000:8000 --name test squidfunk/mkdocs-material
```

\-it 是获得可交互的 Shell 所必须的，平时都加上；蓝色就是给当前容器起个名字。

我觉得我只需要会用 docker 就行了，暂时没自己构建容器的需求，这一块不学了。

