# NWHex

__NWHex__ is a part of [NoWare-Tools](https://github.com/NoWare-Development/noware-tools).

__NWHex__ is a simple HEX viewer written in Rust.

## Usage
```
$ nwhex [flags] <file>
```

## Available flags
* `--help -?` -- display help message
* `--ascii -A` -- display ASCII representation of data
* `--output -O <file>` -- output read data to a file

## Examples
We have file that content this:
```
Hello! I'm a test file!
How are you doing?
```

Output of this file will look like this:
```
$ nwhex test.txt
| Address    | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |
| ---------- | ----------------------------------------------- |
| 0x00000000 | 48 65 6C 6C 6F 21 20 49 27 6D 20 61 20 74 65 73 |
| 0x00000010 | 74 20 66 69 6C 65 21 0A 48 6F 77 20 61 72 65 20 |
| 0x00000020 | 79 6F 75 20 64 6F 69 6E 67 3F 0A                |
```

And like this with `--ascii` flag:
```
| Address    | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F | ASCII            |
| ---------- | ----------------------------------------------- | ---------------- |
| 0x00000000 | 48 65 6C 6C 6F 21 20 49 27 6D 20 61 20 74 65 73 | Hello! I'm a tes |
| 0x00000010 | 74 20 66 69 6C 65 21 0A 48 6F 77 20 61 72 65 20 | t file!.How are  |
| 0x00000020 | 79 6F 75 20 64 6F 69 6E 67 3F 0A                | you doing?       |
```
