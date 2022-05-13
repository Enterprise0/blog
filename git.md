<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [git常用命令](#git常用命令)
- [远程库](#远程库)
- [版本回退和撤销修改](#版本回退和撤销修改)
- [删除文件](#删除文件)
- [分支](#分支)
- [保存工作现场](#保存工作现场)

<!-- /code_chunk_output -->


## git常用命令
----
```bash
git init
git clone
git pull <remote branch> <branch>
git push # 推送指定分支：git push origin <branch>
git add <files> # 存入暂存区，跟踪文件
git commit -m <message> # 提交到分支
git log # 记录commit，版本回退记录也会回退
git reflog # 记录每一次命令，用于寻找回退前的版本
```

- clone时ssh协议速度快，https速度慢。
- git log时减小行数：--graph --pretty=oneline --abbrev-commit（版本号只显示前几个字符）


## 远程库
----
```bash
git remote add origin git@github.com:<github username>/<repo>.git # 添加远程库，命名为origin
git remote -v # 查看关联仓库
git remote rm origin # 取消关联，github仓库还存在
```


## 版本回退和撤销修改
----
```bash
git reset --hard HEAD^ # 回退到上一个版本
git checkout -- <file> # 撤销工作区修改，回到最近一次commit/add状态
git reset HEAD <file> # 撤销暂存区修改
```

- HEAD表示当前版本，HEAD^上个版本，HEAD^^上上版本，HEAD~100上100个版本。
- 可以使用版本号的前几个字符回退和取消回退指定版本


## 删除文件
----
```bash
rm <file>
git rm <file> # 从版本库中删除文件
git commit 
```


## 分支
----
```bash
git branch <branch> # 创建分支
git branch -d <branch> # 删除分支
git checkout <branch> # 切换分支
git checkout -b <branch> <remote branch> # 创建并切换分支，添加<remote branch>则复制远程分支到本地
git switch <branch> # 切换分支
git switch -c <branch> # 创建并切换分支
git merge <branch> # 合并指定分支到当前分支
```

- 如果要合并的两个分支都有新的commit，合并的使用要手动解决冲突。
- 合并时：--no-ff，git log会显示删除的分支记录


## 保存工作现场
----
```bash
git stash # 保存工作内容
git stash apply # 恢复保存的stash
git stash drop # 删除保存的stash
git stash pop # 恢复并删除
git stash apply <stash@{0}> # 恢复指定的stash
git cherry-pick <commit> # 复制提交到当前分支，但是复制后提交的版本号不一样，是2个提交
```
