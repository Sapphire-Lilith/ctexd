# ctexd command

This command is useful if you are writing a LaTeX-style document in subfiles.
It creates the required directories and files by simply specifying the parent directory name.

> (Attention) This command has been created for use on Linux.

## usage

```sh
ctexd [option] [dirname]
```

### option

- `-n` (`--new`)
    - Create directories and files with the following structure.

		```txt
		./[dirname]
		├─src/
		└─main.tex
		```

- `-r` (`--report`)
    - Create directories and files with the following structure. (Please supplement the contents of the file with your own snippets or other information.)

		```txt
		./[dirname]
		├─data/
		├─fig/
		├─script/
		├─src/
		│	├─01_purpose.tex
		│	├─02_content.tex
		│	├─03_result.tex
		│	├─04_discussion.tex
		│	├─05_exercise.tex
		│	└─06_reference.tex
		└─main.tex
		```

- (None)
    - If no options are specified, it is the same as the following.

		```sh
		ctexd -n texd
		```
