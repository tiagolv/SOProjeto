# Simulador de Gestao de Processos

## Como compilar e executar

```bash
cd simulador
make
./simulador
```

Opcionalmente, pode passar argumentos:

```bash
./simulador [plan.txt] [control.txt] [quantum] [FCFS|PRIO|SJF|RM|EDF]
```

Exemplo:

```bash
./simulador plan.txt control.txt 4 PRIO
```

Para modo interativo (comandos via stdin), use `-` como ficheiro de controlo:

```bash
./simulador plan.txt - 4 FCFS
```

Comandos disponíveis: `E` (executar quantum), `I` (interromper/bloquear), `D` (escalonador longo prazo), `R` (report), `T` (terminar)
