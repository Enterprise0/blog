<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [## diff and log](#-diff-and-log)
- [## commit、pull and push](#-commitpull-and-push)
- [## 远程库](#-远程库)
- [## 版本回退、撤销修改和删除文件](#-版本回退撤销修改和删除文件)
- [## 分支](#-分支)
- [## 保存工作现场（临时修改bug时用到）](#-保存工作现场临时修改bug时用到)
- [## 合并提交](#-合并提交)
- [## 标签](#-标签)
- [merge/pull request](#mergepull-request)

<!-- /code_chunk_output -->


## diff and log
----
```bash
git diff # 查看工作区距离上一次commit后的修改
git diff <HEAD/commit id> -- <file> # 查看工作区和特定版本的文件的修改
git log # 记录commit，版本回退记录也会回退
git log --graph --pretty=oneline --abbrev-commit
git reflog # 记录本地每一次git命令，用于寻找回退前的版本
```
- clone时ssh协议速度快，https速度慢。

## commit、pull and push
----
```bash
git commit --amend # 追加到上一次提交
git pull <remote branch> <branch>
git push # 推送指定分支到远程仓库对应分支：git push origin <branch>，如果远程仓库没有对应分支，需要先关联本地分支和远程分支
git branch --set-upstream-to=origin/<branch> <branch> # 关联本地分支和远程分支
```

## 远程库
----
```bash
git remote add origin <repo> # 添加远程库，命名为origin
git remote -v # 查看关联仓库
git remote rm origin # 取消关联，github仓库还存在
```

## 版本回退、撤销修改和删除文件
----
```bash
git reset --hard HEAD^ # 回退到上一个版本
git reset --hard <commit id> # 回退到特定版本
git checkout -- <file> # 撤销工作区修改，回到最近一次commit/add状态
git reset HEAD <file> # 撤销暂存区修改，回到工作区
rm <file> 后 git rm <file> # 从版本库中删除文件
```
- HEAD表示当前版本，HEAD^上个版本，HEAD^^上上版本，HEAD~100上100个版本。
- 可以使用版本号的前几个字符回退和取消回退指定版本

## 分支
----
```bash
git branch <branch> # 创建分支
git branch -d <branch> # 删除分支
git checkout <branch> # 切换分支
git checkout -b <branch> <remote branch> # 创建并切换分支，添加<remote branch>则复制远程分支到本地
git switch <branch> # 切换分支
git switch -c <branch> # 创建并切换分支
git merge <branch> # 合并指定分支到当前分支，默认fast forward合并
git merge --no-ff -m "commit message" <branch> # 合并分支并提交，禁用fast forward合并
git cherry-pick <commit id> # 复制指定commit到当前分支,但是复制后commit的版本号不一样，是2个提交
```
- 如果要合并的两个分支都有新的commit，merge时要手动解决冲突。
    ```bash
    <<<<<<< HEAD
    Creating a new branch is quick & simple.
    =======
    Creating a new branch is quick AND simple.
    >>>>>>> feature1
    ```
    解决冲突后，add + commit
- 合并时：--no-ff，git log会显示删除的分支记录
- main：稳定分支。dev：不稳定分支。其他分支为bug修复或添加新特性。

## 保存工作现场（临时修改bug时用到）
----
```bash
git stash # 保存工作内容
git stash list
git stash apply # 恢复保存的stash
git stash drop # 删除保存的stash
git stash pop # 恢复并删除
git stash apply <stash@{id}> # 恢复指定的stash
```

## 合并提交
----
```bash
git rebase # rebase操作可以把本地未push的分叉提交历史整理成直线；
git rebase -i <commit id> # 合并head到commit id-1
git rebase --continue
git rebase --bort
```
- pick：保留该commit（缩写:p）
- reword：保留该commit，并修改该commit的注释（缩写:r）
- edit：保留并修改该commit(不仅仅修改注释)（缩写:e）
- squash：将该commit和前一个commit合并（缩写:s）
- fixup：将该commit和前一个commit合并，但不保留该commit的message（缩写:f）
- exec：执行shell命令（缩写:x）
- drop：丢弃该commit（缩写:d）
>在确保没有问题前不要push到main，好习惯应该是新建分支，确保无误后合并到main。

## 标签
----
```bash
git show <tag> # 显示指定tag的详细信息，否则显示有几个tag
git tag v0.1 <commit id> # 不加commit id则标签默认打在最新commit上
git tag -a <tag> -m "message" <commit id> # 带message的标签
git tag -d <tag>
git push origin <tag> # 推送指定tag
git push origin --tags # 推送所有未推送的本地tag
git push origin :refs/tags/<tag> # 删除远程tag，要先删除本地tag
```

## merge/pull request
1. fork别人的仓库为自己的仓库
2. clone到本地并修改，add、commit
3. push到自己的仓库
4. 在自己的仓库创建pull request，选择你要merge的已修改分支和远程分支。在作者同意merge之前可以多次push（你要merge的已修改分支），github会自动记录修改并同步到pull request。
5. 作者同意merge request，自己成为项目的contributor。