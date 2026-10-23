# Lab 2 — Linux Navigation and File Management: Individual Report

- Student name/ID: HAO Ratha / e20230769
- Ubuntu username: gic-hao-ratha
- My values (`oslab values lab2`): file1 = `tax summary.txt`, file2 = `cash flow.txt`, owner = `Sale`, reader = `Marketing`, third = `Engineering`
- Files: `evidence/paths.txt`, `evidence/tree.txt`, `evidence/checkpoint.txt`

## What I Did

| Step | My command | Current folder when I ran it |
|---|---|---|
| Move the first file (relative destination) | `mv "incoming/cash flow.txt" reports/` | `lab2/` |
| Move the second file (absolute paths) | `mv "$OSLAB_WORKSPACE/lab2/incoming/tax summary.txt" "$OSLAB_WORKSPACE/lab2/reports/"` | `lab2/` |
| Read the report from my reader department (relative path) | `cat "../Sale/archive/first-original.txt"` | `TechCorp/<reader>/` |
| The path error I made on purpose, and its message | `cat "reports/$file1"` — `No such file or directory` | `TechCorp/<reader>/` |
| The relative path that fixed it | `cat "../../reports/$file1"` | `TechCorp/<reader>/` |

## Explanation

A correct file name can still produce “No such file or directory” when the path is incorrect or the command is run from a different current directory. Relative paths depend on the directory I am currently in, while absolute paths specify a location from the root or workspace path. I used `mv` to move reports from `incoming/` to `reports/`. I used `cp` to copy reports into my owner department while keeping the originals in `reports/`.

## What My Tests Do Not Prove

The `ls` command shows file names and directory contents, but it does not prove that two files contain identical data. The `cmp` command checks whether two files are byte-for-byte identical, but this alone does not prove that the files are correct or that every lab requirement has been satisfied.

## Plus / Challenge (only if you did them)

For the plus task, I used `mv ../a/b/"lost file.txt" found.txt` from `mess/c` to move and rename the file in one command. From `mess/a/b`, I used a relative path with `..` to copy `found.txt` into my third department.

For the wildcard challenge, I used `cp reports/*.txt "TechCorp/$third/"`. Quoting `"*.txt"` prevents normal wildcard expansion by the shell. The wildcard does not normally match hidden files such as `.hidden.txt`.

## AI Note (optional)

An AI tool suggested using a relative path with `..` to reach a file outside my current directory. I tested the command in the terminal and checked the result with `cat` and `ls`.
