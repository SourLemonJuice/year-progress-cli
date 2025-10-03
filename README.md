# year-progress-cli

Display how many days did you lost in this year.\
It seems good to put this in `.bashrc`? Maybe

If you like Python or con't build it, check out [year-progress-cli.py](https://github.com/SourLemonJuice/year-progress-cli.py)

## Build

At the root of the repository, run:

- `git submodule init`
- `git submodule update --depth 1`
- `make`

It will pull my ArgParseX library for argument parsing.
Binary file will be named `year-progress`.

## Preview

```text
It's day 53 of the year(365). That's already 14.5%
[-------#######################################]
```

## CLI Flags

Check out the `year-progress --help`.\
The `--version` will display build info.

Use `--width` to set the progress bar width.

## Version semantic

```text
<major>.<minor>.[<patch>]
```

## Todo List

- Looking so normal, it need more colors!!

## License

This software published under MIT license.\
Copyright 2025 酸柠檬猹/SourLemonJuice
