// FIXME: cmd: echo ''$?''"42" stdout tsika: '0 "42"
// FIXME: echo '''ho"''''l"a''' ;bash: ho"l"a
// TODO: cmd: env | grep HOME meme chose pour cmd: export | grep "HOME" FIXME: leaks

/* FIXME: export HOLA=bonjour
export HOLA=' hola et $HOLA'
echo $HOLA
*/
/* TODO: export HOLA="s -la"
l$HOLA ->devrait executer: ls -la
l"$HOLA" -> command not found
*/

// TODO: check heredoc if limiter: $'USER'
