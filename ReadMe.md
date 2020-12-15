A C++ command line progress bar with style support.

## Example

You can create a customized progress bar, in ths case going to 100, starting at 0, 30 character width, printing the percentage and with styled different characters for the left and right caps and the finished and empty space in the progress bar itself.

```
progresso::progresso p1 = {0, 100, 30, true, {
        '(', ')', '#', '-'
    }};
```
