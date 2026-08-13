# SadServers

> 修复一些 Linux 服务器出现的问题
> 
> 所有题目的运行环境为 Debian 11

!!! warning "温馨提示"
    正在维护🔧，这个页面暂时先别看！

|   *   |                     Problem                     | Type  |  Tag  |
| :---: | :---------------------------------------------: | :---: | :---: |
|   √   | "Saint John": what is writing to this log file? |  Fix  | bash  |
|   √   |           "Saskatoon": counting IPs.            |  Do   | bash  |
|   √   |           "The Command Line Murders"            |  Do   | bash  |
|       |            "Taipei": Come a-knocking            | Hack  |       |
|       |                                                 |       |
|   √   |               "Lhasa": Easy Math                |  Do   | bash  |
|       |         "Minneapolis": Break a CSV file         |

- https://notes.hatedabamboo.me/sad-servers-pt-2/

- `wc -l data.csv`: 获取文件行数

## "The Command Line Murders"

> Scenario: "The Command Line Murders"
> 
> Level: Easy
> 
> Description: This is the Command Line Murders with a small twist as in the solution is different
> 
> Enter the name of the murderer in the file /home/admin/mysolution, for example `echo "John Smith" > ~/mysolution`
> 
> Hints are at the base of the /home/admin/clmystery directory. Enjoy the investigation!
> 
> Test: `md5sum ~/mysolution` returns `9bba101c7369f49ca890ea96aa242dd5`
> 
> (You can always see /home/admin/agent/check.sh to see how the solution is evaluated).
> 
> Time to Solve: 20 minutes.
> 
> OS: Debian 11
> 
> Root (sudo) Access: No

首先观察目录结构以及获取基本线索,

```bash
admin@ip-10-1-13-163:~/clmystery/mystery$ ls
crimescene  interviews  memberships  people  streets  vehicles

admin@ip-10-1-13-163:~/clmystery/mystery$ grep "CLUE" crimescene
CLUE: Footage from an ATM security camera is blurry but shows that the perpetrator is a tall male, at least 6'.
CLUE: Found a wallet believed to belong to the killer: no ID, just loose change, and membership cards for Rotary_Club, Delta SkyMiles, the local library, and the Museum of Bash History. The cards are totally untraceable and have no name, for some reason.
CLUE: Questioned the barista at the local coffee shop. He said a woman left right before they heard the shots. The name on her latte was Annabel, she had blond spiky hair and a New Zealand accent.
```

可以看到凶手是一个身高超过 6' 的高个子、是 Rotary_Club 等俱乐部会员, 并且有一个女目击者, 名字为 Annabel, 有 blond spiky hair 和 New Zealand 口音.

凶手的信息较为模糊, 我们从目击者作为突破口, 输入 `grep "Annabel" people`, 有 $4$ 个可能的目击者 (其实只有 $2$ 个, 因为性别是女), 根据她们的 address 去寻找对应的 interview, 看看她们都说了啥. 最后锁定目击者是 `Annabel Church`.

```bash
admin@ip-10-1-13-163:~/clmystery/mystery$ grep "Annabel" people
Annabel Sun     F       26      Hart Place, line 40
Oluwasegun Annabel      M       37      Mattapan Street, line 173
Annabel Church  F       38      Buckingham Place, line 179
Annabel Fuglsang        M       40      Haley Street, line 176

admin@ip-10-1-13-163:~/clmystery/mystery/interviews$ cat interview-699607
Interviewed Ms. Church at 2:04 pm.  Witness stated that she did not see anyone she could identify as the shooter, that she ran away as soon as the shots were fired.

However, she reports seeing the car that fled the scene.  Describes it as a blue Honda, with a license plate that starts with "L337" and ends with "9"
```


根据车牌号的信息, 以 "L337" 打头, "9" 结尾, 同时还是 a blue Honda, 在 `vehicle` 文件中查找, 只可能是 `Joe Germuska` 或 `Jeremy Bowers`.

最后根据俱乐部信息, 锁定只能是 `Joe Germuska`.