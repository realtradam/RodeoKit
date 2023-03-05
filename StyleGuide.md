# Rodeo Style Guide

The intent of this style guide is to not only have a unified style across the entire library, but to also remove as much ambiguity as possible as well as to try and improve readability. I will be changing this as the software evolves and I find something that doesnt work or find something new that does.

### 1 Underscores in function/variable/type names are treated as namespaces
This means that whenever there is an object and there is a function that operates specifically on those objects then it will be "namespaced" under that object. The intent is to enforce a "directory  type" in the code.
```c
void rodeo_window_create() {}
// rodeo library -> window "class/object" -> create a new one
```

### 2 Prefix
#### 2.1 Everything is prefixed with the library name(rodeo)
```c
void rodeo_init()
```

#### 2.2 If something is a macro then it is prefixed with 'm' before the library name
```c
#define mrodeo_math_pi 3.14
```

#### 2.3 If something is internal to the library and not supposed to be visible to users of the library then it is prefixed with an 'i' before the 
```c
void irodeo_error_exit() {}
```

#### 2.4 If something is a macro and internal the macro designation always goes first
```c
#define mirodeo_error_do() something()
```

### 3 Suffix

#### 3.1 Types are suffixed with a `_t`
```c
typedef struct { /* stuff */ } rodeo_window_t
typedef enum { /* stuff */ } rodeo_renderer_t
```

#### 3.2 Deffered and scoped macros are always suffixed with `_do`
```c
mrodeo_draw_do()
{

}
```

### 4 Enum and Struct types are always typedefs and anonymous
```c
typedef enum
{
    rodeo_renderer_vulkan,
    rodeo_renderer_gles,
    rodeo_renderer_gl
}
rodeo_renderer_t;

typedef struct
{
    int something;
}
rodeo_something_t;
```

### 5 Spacing

#### 5.1 Curly braces are always on new lines. If statements always require curly braces.
```c
if(something)
{
    do_something_else();
}
```

#### 5.2 If the parameter list is too long inside of the round brackets then they may be split onto new lines. When doing this each parameter must be on its own line and be on new lines.
```c
something(
    first_param,
    second_param,
    third_param
)
{
    do_something();
}
```

#### 5.3 No spacing between a function and the brackets. Same applies to loop or anything else that uses brackets in this way
```c
// no space between the 'g' and the '('
something();
```

#### 5.4 Spaces between math operators
```c
c = a + b;
c = (a - c) * 3;
```

#### 5.5 No incremental/decremental operators
```c
c++; // bad
c += 1; // good
```

#### 5.6 One space after commas in any list of items. No other spaces.
```c
[1, 3, 5]
my_function(item_one, item_two);
```

### 6 Naming

#### 6.1 When returning a handle of a new object name the functions that do this with "create" and "destroy"
```c
rodeo_window_create();
rodeo_window_destroy();
```

#### 6.2 When (de)initializing internal state name the functions that do this with "init" and "deinit"
```c
rodeo_init();
rodeo_deinit();
```

### 7 Macros: avoid macros whenever possible except in the following cases where it is preferable to use a macro

#### 7.1 Defer and scoped macro
Whenever you have a "begin" and an "end" pair of functions or a single end function where you have specific actions you want to do between make or use a defer macro for it.
```c
// This is without the macro(prefer not to do this)
rodeo_draw_begin()
    // do some stuff
rodeo_draw_end()

// This is using a macro. Much better and less prone to an error.
mrodeo_draw_do()
{
    // do some stuff
}
```
Look in the source code to see how these macros are defined.

#### 7.2 `__FILE__`, `__LINE__`, and `__func__`(but not __FUNC__ or __FUNCTION__) macros are ok when using them for logging and error reporting.

#### 7.3 If you must make a macro and the macro requires a terminator ( ; ) at the end then do not have it in the macro, instead let the programmer manually add it themselves when utilizing the macro
```c
#define mrodeo_test() mrodeo_some_func(3, 4)

// using the macro
mrodeo_test();
```

### 8 STD/LIBC

#### 8.1 Use stdint instead of the built in integer types(dont use int, short, long, etc)
```c
int16_t var_a;
u_int16_t var_b;
int32_t var_c;
u_int32_t var_d;
// etc.
```
<!-- not sure yet how I want error handling to work.
### 9 Error Handling

#### 9.1 If giving a struct/object to a function and the function can fail then the struct/object should have a built in error code that reports this.

#### 9.2 If a function can fail but does not handle a struct/object then it should return the error.
-->
