// TODO: si commande echo ""$?"" bash: 0 minishell: "0
// FIXME: cmd: echo ""$?"" | cat -e stdout tsika: "0   | cat -e
// TODO: echo $?"42" bash: 042 minishell: 0 42
// FIXME: cmd: echo ''$?''"42" stdout tsika: '0 "42"
// TODO: cmd: echo $"HOME" .bash: HOME .minishell: $ HOME
// ? ary le wildcard marina ve nataonlah iany?
// TODO: cmd: ">>" asd .bash: >> devient une commande .minishell: >> toujours redirection
// FIXME: operator et redir dans single '' ou double quote "" devient T_WORD
