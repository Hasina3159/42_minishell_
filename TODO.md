# Minishell TODO

- ## Mandatory part
        - [x] Prompt
        - [x] history
        - [x] exec cmd (based on the PATH variable or using a relative or an absolute path)
        - [x] single quote (T_STRING_S)
        - [x] double quote (T_STRING_D)
        - [ ] redirection:
            - [x] < input
            - [ ] output >
            - [x] << heredoc
            - [ ] >> output append
        - [ ] pipes
        - [x] environment variables
        - [x] handle $?
        - [x] signal
            - [x] ctrl + d
            - [x] ctrl + c
            - [x] ctrl + /
        - [x] builtins
- ## Bonus part
        - [ ] operator with parenthesis for priorities
        - [ ] wildcard
- ## Another case
- Leak:
        - [ ] check_leaks.sh
        - [x] builtins child
- expander:
        - [x] ```bash
              echo $HOME$PWD$HOME$HOME$HOME$HOME$HOME
              ```
        - [ ] ~ to $HOME n'expand pas si quote, ou ~ n'est pas au debut (pas obligatoire)
- fd:
        - [ ] close unused fd
- execution:
        - [x] heredoc
- cas
    - (obli ou pas ?)
            - [ ] ```bash
                  ls |
                  ```
            - [ ] ```bash
                  cat | cat | ls
                  ```
- gestion cmd:
        - [ ] ```bash
              > out cat
              ```
        - [ ] redirection out avant la commande ne se comporte pas comme bash
        - [x] get exit_status if signaled or exited
- here-doc
        - [ ] expander here-doc
        - [ ] ctrl + c sur le prompt here-doc
