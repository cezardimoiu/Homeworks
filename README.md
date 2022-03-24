# Homeworks


.gitconfig file
[filter "lfs"]
	clean = git-lfs clean -- %f
	smudge = git-lfs smudge -- %f
	process = git-lfs filter-process
	required = true
[user]
	name = <name>
	email = <email>

[alias]
    co = checkout
    amend = commit --amend --no-edit
    s = status
    a = add .
    find-merge = "!sh -c 'commit=$0 && branch=${1:-HEAD} && (git rev-list $commit..$branch --ancestry-path | cat -n; git rev-list $commit..$branch --first-parent | cat -n) | sort -k2 -s | uniq -f1 -d | sort -n | tail -1 | cut -f2'"
    show-merge = "!sh -c 'merge=$(git find-merge $0 $1) && [ -n \"$merge\" ] && git show $merge'"
    cp = cherry-pick
    f = fetch
    p = pull
[core]
    autocrlf = true
    editor = 'C:/Program Files/Sublime Text/sublime_text.exe' -multiInst -notabbar -nosession -noPlugin
