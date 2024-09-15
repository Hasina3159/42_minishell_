# Minishell TODO

- ## Mandatory part
        - [ ] Prompt
        - [x] history
        - [ ] exec cmd (based on the PATH variable or using a relative or an absolute path)
        - [ ] single quote (T_STRING_S)
        - [ ] double quote (T_STRING_D)
        - [ ] redirection:
            - [x] < input
            - [ ] output >
            - [ ] << heredoc
            - [ ] >> output append
        - [ ] pipes
        - [ ] environment variables
        - [ ] handle $?
        - [ ] signal
            - [ ] ctrl + d
            - [ ] ctrl + c
            - [ ] ctrl + /
        - [x] builtins
- ## Bonus part
        - [ ] operator with parenthesis for priorities
        - [ ] wildcard
- ## Another case
- Leak:
        - [ ] check_leaks.sh
        - [x] builtins child
- expander:
        - [ ] ```bash
              echo $HOME$PWD$HOME$HOME$HOME$HOME$HOME
              ```
        - [ ] ~ to $HOME n'expand pas si quote, ou ~ n'est pas au debut
- fd:
        - [ ] close unused fd
- execution:
        - [ ] heredoc
- cas
        - [ ]

              ```bash
              ls |
              ```


- gestion cmd:
        - [ ]

              ```bash
              ls | cat | awk '{print $1}'
              ```
        - [ ] gestion des { }
        - [ ] fix tokeniser problem
        - [x] get exit_status if signaled or exited
