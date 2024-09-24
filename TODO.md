# Minishell TODO

- ## Mandatory part
        - [x] Prompt
        - [x] history
        - [x] exec cmd (based on the PATH variable or using a relative or an absolute path)
        - [x] single quote (T_STRING_S)
        - [x] double quote (T_STRING_D)
        - [x] redirection:
            - [x] < input
            - [x] output >
            - [x] << heredoc
            - [x] >> output append
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
        - [ ]

              ```bash
              echo $HOME$PWD$HOME$HOME$HOME$HOME$HOME
              ```
        - [ ] ~ to $HOME n'expand pas si quote, ou ~ n'est pas au debut (pas obligatoire)
        - [ ] expand toujours meme si unset un variable
- cas
        - [ ] (obli ou pas ?)

              ```bash
              ls |
              ```
        - [ ] gerer SIGPIPE

              ```bash
              cat | cat | ls
              ```
- here-doc (obli ?)
        - [ ] expander here-doc
        - [ ] ctrl + c sur le prompt here-doc
