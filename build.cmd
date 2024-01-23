mkdir tmp
bin\scpp.exe src/main.c tmp/cc.i
bin\scc.exe tmp/cc.i tmp/cc.asm
bin\asm.exe tmp/cc.asm geoconstruct.exe tmp/cc.map