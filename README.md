# 🐚 Minishell

**Minishell** is a project from 42 School that aims to recreate a simplified shell in C. It supports multiple commands, redirections, pipes, environment variable expansion, and signal handling — following the behavior of `bash`.

---

## 📜 Project Rules

- Must be written in C and follow the [Norminette](https://github.com/42School/norminette) style guide.
- Do not use `system()` or `execvp()` — all logic must be implemented manually.
- Implement built-in commands such as `cd`, `echo`, `pwd`, `exit`, etc.
- Support for redirections (`>`, `<`, `>>`, `<<`) and pipes (`|`).
- Expansion of environment variables (`$USER`, `$?`, etc.).
- Proper handling of signals `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\).

---

## ⚙️ How to Use

### 🔧 Compile

```bash
make
```

### ▶️ Run

```bash
./minishell
```

(To run with the suppression file:)

```bash
make run
```

You will see an interactive prompt where you can enter commands such as:

```bash
echo hello | grep h > output.txt
cat < output.txt
```

---

## ✅ Features Implemented

- ✅ Interactive prompt using `readline`
- ✅ Execution of commands with arguments
- ✅ Pipes (`|`)
- ✅ Redirections (`>`, `>>`, `<`, `<<`)
- ✅ Environment variable expansion (`$USER`, `$?`, etc.)
- ✅ Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `exit`
  - `env`
  - `export`
  - `unset`
- ✅ Signal handling (`Ctrl+C`, `Ctrl+\`)
- ✅ Exit status (`$?`)
- ✅ Parsing with support for single and double quotes

---

## 🛠️ Dependencies

- `readline` library (required for prompt and history functionality)

To install on Linux:

```bash
sudo apt-get install libreadline-dev
```

---

## 🧠 Execution Flow

The shell follows these main steps:

1. **Read** the command line using `readline`
2. **Tokenize** the input into manageable pieces
3. **Parse** the tokens into structured commands and redirections
4. **Expand** environment variables (`$VAR`, `$?`)
5. **Execute**:
   - External commands using `execve`
   - Built-in commands handled internally
   - Redirections and pipes managed with `dup2`, `pipe`, `fork`, etc.

---

## 🧪 Examples

```bash
echo "Hello, $USER"
cat << EOF
This is a heredoc.
EOF

ls | grep minishell > result.txt
```

---

## 👥 Authors

- [guclemen](https://github.com/GuilhermeClementeDev)
- [gda-conc](https://github.com/BieldoJT)

---

## 📁 Notes

This project was developed as part of the [42 School](https://42.fr/) curriculum, aiming to deepen understanding in:

- Processes (`fork`, `execve`, `waitpid`)
- File and FD manipulation (`open`, `dup2`, etc.)
- Input parsing and lexical analysis
- Redirections and heredocs
- Signal handling (`SIGINT`, `SIGQUIT`)
- Clean and modular C architecture

---
