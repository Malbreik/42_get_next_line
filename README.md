# 📖 get_next_line - Read Lines Like a Pro

> 🎯 **Read a file line by line** - Master static variables and file descriptors!

---

## 📖 What is get_next_line?

**get_next_line** (GNL) is a function that reads a line from a file descriptor. Each time you call it, it returns the next line. This project teaches you:

- 📂 **File descriptors** - How files are accessed in C
- 🧠 **Static variables** - Variables that remember their value between function calls
- 💾 **Dynamic memory** - Allocating exactly what you need
- 📏 **Buffer management** - Reading chunks of data efficiently

---

## 🎯 How It Works

```
📄 File Content:          🔄 Function Calls:
┌─────────────────┐
│ Hello World     │       get_next_line(fd) → "Hello World\n"
│ This is line 2  │       get_next_line(fd) → "This is line 2\n"  
│ Last line       │       get_next_line(fd) → "Last line"
└─────────────────┘       get_next_line(fd) → NULL (end of file)
```

---

## 🎣 The Fishing Analogy

This implementation uses a **fishing analogy** to make the code easier to understand:

| Function | What it Does | Fishing Term |
|----------|-------------|--------------|
| `cast_net_into_lake` | Read from file into buffer | Casting net to catch fish |
| `join_and_free_basket` | Combine buffers | Adding fish to basket |
| `extract_line_from_basket` | Get one complete line | Taking one fish out |
| `split_basket_with_knife` | Save leftover for next call | Keeping remaining fish |

---

## 📁 Project Structure

```
get_next_line/
├── 📄 get_next_line.h       # Header with prototypes
├── 📄 get_next_line.c       # Main GNL logic
├── 📄 get_next_line_utils.c # Helper functions
└── 📄 main.c                # Test file
```

---

## 🔑 Key Concept: Static Variables

```c
char *get_next_line(int fd)
{
    static char *basket = NULL;  // 👈 Remembers value between calls!
    ...
}
```

### How Static Works:
```
Call 1: basket = "Hello\nWorld\n" → returns "Hello\n" → basket = "World\n"
Call 2: basket = "World\n"        → returns "World\n" → basket = ""
Call 3: basket = ""               → returns NULL
```

---

## 🔑 Key Concept: BUFFER_SIZE

```c
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42  // 👈 How many bytes to read at once
#endif
```

| BUFFER_SIZE | Behavior |
|-------------|----------|
| `1` | Reads 1 byte at a time (slow, but works) |
| `42` | Reads 42 bytes at a time (default) |
| `10000` | Reads 10KB at a time (faster for big files) |

**You can change it at compile time:**
```bash
cc -D BUFFER_SIZE=100 get_next_line.c get_next_line_utils.c
```

---

## 🔑 Key Concept: File Descriptors

```c
int fd = open("file.txt", O_RDONLY);  // fd = 3 (or any number)
char *line = get_next_line(fd);        // Read from fd
close(fd);                             // Don't forget to close!
```

| FD | Description |
|----|-------------|
| `0` | Standard Input (keyboard) |
| `1` | Standard Output (screen) |
| `2` | Standard Error |
| `3+` | Your opened files |

---

## 💡 Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>  // For open()

int main(void)
{
    int     fd;
    char    *line;

    // Open a file
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);

    // Read all lines
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);  // Print the line
        free(line);          // 🚨 Don't forget to free!
    }

    close(fd);  // Close the file
    return (0);
}
```

---

## 📊 Visual Flow

```
┌─────────────────────────────────────────────────────────┐
│                    get_next_line(fd)                    │
└─────────────────────────────────────────────────────────┘
                          │
                          ▼
              ┌──────────────────────┐
              │  Is basket empty?    │
              └──────────────────────┘
                    │           │
                   Yes          No
                    │           │
                    ▼           │
         ┌─────────────────┐    │
         │ cast_net_into   │    │
         │ lake (read)     │    │
         └─────────────────┘    │
                    │           │
                    └─────┬─────┘
                          ▼
              ┌──────────────────────┐
              │ extract_line_from    │
              │ basket               │
              └──────────────────────┘
                          │
                          ▼
              ┌──────────────────────┐
              │ split_basket_with    │
              │ knife (save rest)    │
              └──────────────────────┘
                          │
                          ▼
                   Return line ✅
```

---

## 🛠️ Compilation

```bash
# Basic compilation
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl

# With custom buffer size
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl

# Run
./gnl
```

---

## ✅ Testing Checklist

Test these scenarios:

- [ ] Empty file
- [ ] File with no newline at end
- [ ] File with only newlines
- [ ] Very long lines (longer than BUFFER_SIZE)
- [ ] BUFFER_SIZE = 1
- [ ] BUFFER_SIZE = 10000000
- [ ] Invalid fd (-1, 42 without opening)
- [ ] Reading from standard input (fd = 0)
- [ ] Multiple files at the same time (bonus)

---

## ⚠️ Common Mistakes

### 1. Memory Leaks
```c
// ❌ WRONG - Never freeing
while ((line = get_next_line(fd)))
    printf("%s", line);

// ✅ CORRECT - Always free after use
while ((line = get_next_line(fd)))
{
    printf("%s", line);
    free(line);  // 👈 Important!
}
```

### 2. Forgetting to Close Files
```c
// ❌ WRONG
fd = open("file.txt", O_RDONLY);
// ... use fd ...
// forgot close(fd)!

// ✅ CORRECT
fd = open("file.txt", O_RDONLY);
// ... use fd ...
close(fd);  // 👈 Always close!
```

### 3. Not Handling NULL
```c
// ❌ WRONG
line = get_next_line(fd);
printf("%s", line);  // Crash if line is NULL!

// ✅ CORRECT
line = get_next_line(fd);
if (line)
    printf("%s", line);
```

---

## 🧪 Quick Test File

Create `test.txt`:
```
Hello World
This is line 2
Last line without newline
```

Expected output:
```
Hello World
This is line 2
Last line without newline
```

---

## 📚 Helper Functions

| Function | Description |
|----------|-------------|
| `ft_strlen` | Get string length |
| `ft_strjoin` | Join two strings |
| `ft_strchr` | Find character in string |
| `ft_bzero` | Zero out memory |
| `ft_calloc` | Allocate zeroed memory |

---

## 🔍 Debugging Tips

```bash
# Check for memory leaks
valgrind --leak-check=full ./gnl

# Test with different buffer sizes
for size in 1 42 1000; do
    cc -D BUFFER_SIZE=$size *.c -o gnl
    ./gnl
done

# Check norminette
norminette *.c *.h
```

---

## 👤 Author

**malbreik** - 42 Abu Dhabi Student

---

## ⭐ Pro Tips

1. 🎣 **Understand the static variable** - It's the heart of GNL
2. 📏 **Draw the buffer** on paper to visualize what happens
3. 🧪 **Test with BUFFER_SIZE=1** - If it works, your logic is solid
4. 🔍 **Use valgrind** - Memory leaks are the #1 issue in this project
5. ✂️ **Handle the edge cases** - No newline at EOF, empty files

---

*Made with ❤️ at 42 School*
