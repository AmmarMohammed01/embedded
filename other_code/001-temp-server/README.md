# TEMPERATURE SERVER

## How to run

### DEBUG
More info at: https://lldb.llvm.org/use/tutorial.html

Video tutorial: [Learn the lldb debugger basics in 11 minutes | 2021 (Also works on M1 Apple Silicon)](https://www.youtube.com/watch?v=v_C1cvo1biI)

```bash
lldb ./out # "out" is the current target

lldb help
lldb r		# gdb run
lldb b main	# gdb break main, stops execution before running first instruction inside main
lldb n		# gdb next
lldb s		# gdb step
lldb p var	# gdb print var

lldb target create out # restarts the "out" program

# You encounter an issue, look at back trace, use list [line #] to look at those lines of code in backtrace
lldb bt # backtrace, how did you get to current line of code. Stack: oldest place at bottom, newest place at top
lldb list 10 # lists out code snippet at line 10 and below

lldb gui # launches gui
```
