
globals/data

functions:
    block:
        operations...
        control flow


r self:
    .asciz "Self"
r fmt:
    .asciz "%s\n"

gx main:
    i32 %0 = i32_arg 0
    ptr %1 = ptr_arg 1

    bool %2 = i32_le %0 0
    goto @L2, if %2
    goto @L1
x L1:
    ptr %self.0 = ptr_dereference %1 0
    goto @L2
x L2:
    ptr %self := @self %self.0
    printf @fmt %self

    i32_ret 0
    unreachable
