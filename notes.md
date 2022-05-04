### Cas particuliers a gérer

#### Execution des commandes
- Si on unsetenv le PATH, "ls", par exemple, ne marche plus. Par contre, "bin/ls" doit toujours marcher.


#### Parsing
- A partir du moment où une commande donnée au shell contient un slash '/' , le shell n'exécutera pas une commande builtin, même si cette commande contient le nom d'une builtin.
> *Exemple* : "echo" exécutera la commande builtin echo, mais "/bin/echo" ou "./echo" ne le fera pas.

