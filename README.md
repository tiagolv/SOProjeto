# Simulador de Gestao de Processos - Notas

## Explicacao do output (exemplo)
- TEMPO ACTUAL: 8 -> foram executadas 8 unidades de tempo ate ao R. Cada instrucao executada incrementa o tempo.
- PROCESSO EM EXECUCAO: (nenhum) -> depois de cada E, o `exec_quantum()` devolve o processo a fila de prontos e deixa `running = -1`. Como o R acontece logo a seguir, a CPU aparece "vazia" nesse instante.
- PROCESSOS PRONTOS: -> aparecem o pai (pid=1) e os filhos (pid=2, pid=3) criados pelos C no programa. Todos estao prontos porque ainda nao foram escalonados de novo apos o R.
- var=132 nos filhos -> o C copia o contexto do pai, incluindo o valor da variavel, por isso os filhos herdam o var atual do pai.
- start=6/7/0 -> aqui e o tempo de criacao (`start_time`), nao o endereco em memoria. O pai nasce no tempo 0 e os filhos nos tempos em que o C foi executado.
- ESTATISTICAS GLOBAIS -> isto e impresso no final do simulador, depois dos comandos seguintes (E, D, E, T). E por isso que aparece pid=2 como terminado, mesmo que no snapshot anterior ele ainda estivesse em prontos.

## O que falta
O esqueleto cobre o fluxo base, mas ainda faltam partes para cumprir o enunciado completo. O que considero em falta:

- Escalonamento "a serio": implementar RM e EDF com deadline/periodo reais, e tornar SJF/prioridade preemptivos quando chega um processo melhor.
- Gestao de memoria mais fiel: reaproveitar programas ja carregados (tabela de programas), libertar/compactar quando necessario e tratar L com troca de programa e limpeza correta.
- Entrada mais rica: permitir campos extra no `plan.txt` (prioridade, deadline, periodo), ordenar por chegada, e aceitar comandos por stdin quando `control.txt` nao existir.
- Escalonador de longo prazo: desbloqueio aleatorio/probabilistico e possivelmente desbloquear mais do que um processo por chamada.
- Report/estatisticas: turnaround, tempo de espera, tempo de resposta, PC atual e nome do programa em cada estado.
- Identidade do gestor: tratar explicitamente o processo gestor com pid 0 (nem que seja so no report).