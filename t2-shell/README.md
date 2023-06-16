* Planilha (dataset) Notas

Vamos obter informações sobre o rendimento de alunos de um curso em algumas disciplinas ao longo dos anos.

O arquivo historico-alg1_SIGA_ANONIMIZADO.csv refere-se ao aproveitamento de estudantes na disciplina ALGORITMOS 1 entre os anos de 2011 e 2022.

A primeira linha do arquivo é o cabeçalho, isto é, contém os nomes de cada coluna.

A primeira coluna ("matricula") é composta por números inteiros, onde cada número representa um indivíduo. Assim, repetições nessa coluna indicam que o estudante fez mais de uma vez a mesma matéria.

A coluna chamada "status" diz a situação de cada indivíduo (se cancelou a matéria, foi aprovado, reprovou, etc.).

Atenção: R-nota indica REPROVAÇÃO POR NOTA e R-freq REPROVAÇÃO POR FALTA. R-freq precede R-nota. Frequências < 75 causam reprovação por falta; Médias abaixo de 50 causam reprovação por nota.

Analise o dataset do referido arquivo para responder as seguintes perguntas:

1- Remova todas as linhas que façam parte do 2o semestre de 2022 (periodo 2, ano 2022);

2- Para cada status, calcule o número de indivíduos únicos naquele status;

3- Qual o máximo de vezes que um indíviduo cursou a discplina antes de ser aprovado? Quantos indivíduos possuem o mesmo número máximo de vezes cursadas até a aprovação?

4- Qual a porcentagem de aprovação/reprovação por ano?

5- Qual é a média de nota dos aprovados (no período total e por ano)?

6- Qual é a média de nota dos reprovados por nota (período total e ano)?

7- Qual é a média da frequência dos reprovados por nota (período total e por ano)?

8- Qual a porcentagem de evasões (total e anual)?

9- Como os anos de pandemia impactaram no rendimento dos estudantes em relação aos anos anteriores? 

10- Calcule em percentual o rendimento dos aprovados, a taxa de cancelamento e de reprovações. Considere como anos de pandemia os anos de 2020 e 2021. (EXEMPLO: qual o percentual de aumento ou diminuição de notas, frequências, aprovações/reprovações e cancelamentos).

11- Compare a volta às aulas híbrida (2022 período 1) com os anos de pandemia e os anos anteriores em relação às aprovações, reprovações, mediana das notas e cancelamentos.

Faça um script shell com funções que respondam as questões acima. Vocês podem usar arquivos intermediários para obtenção dos resultados finais.