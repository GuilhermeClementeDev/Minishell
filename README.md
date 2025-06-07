# 🐚 Minishell

Minishell é um projeto da 42 School cujo objetivo é recriar um shell simplificado em C, com suporte a múltiplos comandos, redirecionamentos, pipes, variáveis de ambiente e tratamento de sinais, seguindo o comportamento do `bash`.

---

## 📜 Regras do Projeto

- Trabalhar em C e seguir as normas do [Norminette](https://github.com/42School/norminette).
- Sem uso de `system()` ou `execvp()` — toda a lógica deve ser implementada.
- Implementar comandos internos (builtins) como `cd`, `echo`, `pwd`, `exit`, etc.
- Suporte a redirecionamentos (`>`, `<`, `>>`, `<<`) e pipes (`|`).
- Expansão de variáveis de ambiente (`$USER`, `$?`, etc.).
- Tratamento adequado dos sinais `SIGINT` (Ctrl+C) e `SIGQUIT` (Ctrl+\).

---

## ⚙️ Como usar

### 🔧 Compilar

```bash
make
```

### ▶️ Executar

```bash
./minishell
```
(Para rodar com o arquivo de supressão)
```bash
make run
```

Você verá um prompt onde poderá digitar comandos como:

```bash
echo hello | grep h > output.txt
cat < output.txt
```

---

## ✅ Funcionalidades implementadas

- ✅ Prompt interativo com `readline`
- ✅ Execução de comandos com argumentos
- ✅ Pipes (`|`)
- ✅ Redirecionamentos (`>`, `>>`, `<`, `<<`)
- ✅ Variáveis de ambiente (`$USER`, `$?`, etc.)
- ✅ Builtins:
  - `echo`
  - `cd`
  - `pwd`
  - `exit`
  - `env`
  - `export`
  - `unset`
- ✅ Tratamento de sinais (`Ctrl+C`, `Ctrl+\`)
- ✅ Status de saída (`$?`)
- ✅ Parsing com suporte a aspas simples e duplas

---

## 🛠️ Dependências

- Biblioteca `readline` (necessária para o prompt com histórico)

Instale no Linux com:

```bash
sudo apt-get install libreadline-dev
```

---

## 🧠 Estrutura Geral

A execução segue essas etapas:

1. **Leitura da linha de comando** (`readline`)
2. **Tokenização** (quebra do input em pedaços)
3. **Parsing** (estruturação dos comandos e redirecionamentos)
4. **Expansão de variáveis** (`$VAR`, `$?`)
5. **Execução**:
   - Comandos externos via `execve`
   - Builtins tratados internamente
   - Redirecionamentos e pipes com uso de `dup2`, `pipe`, `fork`

---

## 🧪 Exemplos

```bash
echo "Hello, $USER"
cat << EOF
This is a heredoc.
EOF

ls | grep minishell > result.txt
```

---

## 👥 Autores

- [guclemen](https://github.com/GuilhermeClementeDev)
- [gda-conc](https://github.com/BieldoJT)

---

## 📁 Observações

Este projeto foi desenvolvido como parte do currículo da [42 School](https://42.fr/), com o objetivo de aprofundar os conhecimentos em:

- Processos (`fork`, `execve`, `waitpid`)
- Manipulação de arquivos e FDs (`open`, `dup2`, etc)
- Parsing e análise léxica
- Redirecionamentos e heredocs
- Sinais (`SIGINT`, `SIGQUIT`)
- Estruturação e modularização em C

---
