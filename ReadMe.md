A C++ command line progress bar with style support.

## Example

You can create a customized progress bar, in this case going to 100, starting at 0, 30 character width, printing the percentage and with styled different characters for the left and right caps and the finished and empty space in the progress bar itself.

```
progresso::progresso p1 = {0, 100, 30, true, {
        '(', ')', '#', '-'
    }};
```

Progresso handles printing out unicode symbols as well.  You can define styles for progress bars, including colors to use and wheter a percentage or value should be printed.  For instance in the following we create a download progress bar with 'climbing' blocks:

auto p2 = progresso::progresso(0, 1024*1024*30, 40, {
        u8"\u2595", // Right 1/8th block
        u8"\u258f", // Left 1/8th block
        u8"\u2588", // Full block
        { u8"\u2598", u8"\u259a", u8"\u2599", u8"\u2588"}, 
        u8"\u2588", // Full block,
        true,
        progresso::color::foreground::BoldWhiteColor,
        progresso::color::ResetColor,

        progresso::color::foreground::BoldYellowColor,
        progresso::color::background::BlueColor,

        progresso::color::foreground::BlueColor,
        progresso::color::background::BlueColor},
        progresso::ValueDisplayStyle::ValueMaxWithSuffix,
        1024*1024,
        "MB");

