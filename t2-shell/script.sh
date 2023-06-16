#!/bin/bash

# Função para remover as linhas do 2º semestre de 2022
remove_2nd_semester_2022() {
    input_file="$1"
    output_file="$2"

    awk -F',' '!($3 == 2022 && $4 == 2)' "$input_file" > "$output_file"
}

# Função para calcular o número de indivíduos únicos para cada status
calculate_unique_individuals_by_status() {
    input_file="$1"

    # Extrair coluna "status" (coluna 10) e contar o número de ocorrências únicas
    awk -F',' 'NR > 1 { status[$10]++ } 
               END { 
                  for (s in status) {
                      print "Status:", s, "| Número de Indivíduos Únicos:", status[s]
                  }
               }' "$input_file"
}

# Exemplo de uso
calculate_unique_individuals_by_status "historico-alg1_SIGA_ANONIMIZADO.csv"

# Função para calcular o máximo de vezes que um indivíduo cursou antes de ser aprovado
calculate_max_attempts_before_approval() {
    input_file="$1"

    # Cria um array associativo para armazenar o número de vezes que cada indivíduo cursou antes de ser aprovado
    declare -A attempts

    # Lê o arquivo linha por linha, ignorando o cabeçalho
    while IFS=',' read -r matricula _ _ _ _ _ _ _ _ status _ _ _ _ _ _; do
        if [[ $status == "Aprovado" || $status == "R-freq" || $status == "R-nota" ]]; then
            ((attempts[$matricula]++))
        fi
    done < "$input_file"

    max_attempts=0
    count=0

    # Percorre o array de tentativas para encontrar o número máximo de vezes cursadas antes da aprovação
    for attempts_count in "${attempts[@]}"; do
        if ((attempts_count > max_attempts)); then
            max_attempts=$attempts_count
            count=1
        elif ((attempts_count == max_attempts)); then
            ((count++))
        fi
    done

    echo
    echo "Máximo de vezes cursadas antes de ser aprovado: $max_attempts"
    echo "Número de indivíduos com o máximo de vezes cursadas: $count"
    echo
}

# Exemplo de uso
calculate_max_attempts_before_approval "historico-alg1_SIGA_ANONIMIZADO.csv"

# Função para calcular a porcentagem de aprovação/reprovação por ano (ignorando casos de cancelamento)
calcular_porcentagem_aprovacao_reprovacao_por_ano() {
    arquivo_entrada="$1"

    # Obter a lista de anos presentes no arquivo
    anos=$(awk -F ',' 'NR > 1 {print $5}' "$arquivo_entrada" | sort -u)

    # Percorrer os anos e calcular as porcentagens
    while read -r ano; do
        total=$(awk -F ',' -v ano="$ano" 'NR > 1 && $5 == ano && $10 != "Cancelado" {count++} END {print count}' "$arquivo_entrada")
        aprovacoes=$(awk -F ',' -v ano="$ano" 'NR > 1 && $5 == ano && $10 == "Aprovado" {count++} END {print count}' "$arquivo_entrada")
        reprovacoes=$(awk -F ',' -v ano="$ano" 'NR > 1 && $5 == ano && ($10 == "R-freq" || $10 == "R-nota") {count++} END {print count}' "$arquivo_entrada")

        echo "Ano: $ano"
        echo "Total: $total"
        echo "Aprovações: $aprovacoes"
        echo "Reprovações: $reprovacoes"

        if [[ $total -gt 0 ]]; then
            porcentagem_aprovacao=$(awk -v aprovacoes="$aprovacoes" -v total="$total" 'BEGIN{ printf "%.2f", (aprovacoes * 100) / total }')
            porcentagem_reprovacao=$(awk -v reprovacoes="$reprovacoes" -v total="$total" 'BEGIN{ printf "%.2f", (reprovacoes * 100) / total }')
        else
            porcentagem_aprovacao=0
            porcentagem_reprovacao=0
        fi

        echo "Porcentagem de Aprovação: $porcentagem_aprovacao%"
        echo "Porcentagem de Reprovação: $porcentagem_reprovacao%"
        echo
    done <<< "$anos"
}

# Exemplo de uso
calcular_porcentagem_aprovacao_reprovacao_por_ano "historico-alg1_SIGA_ANONIMIZADO.csv"

# Função para calcular a média de nota dos aprovados
calcular_media_nota_aprovados() {
    arquivo_entrada="$1"

    media_total=0
    count_total=0

    # Obter a média de nota dos aprovados para o período total
    media_total=$(awk -F ',' '$10 == "Aprovado" {sum+=$8; count++} END {if (count > 0) printf "%.2f", sum/count}' "$arquivo_entrada")
    count_total=$(awk -F ',' '$10 == "Aprovado" {count++} END {print count}' "$arquivo_entrada")

    echo "Média de Nota dos Aprovados (Período Total): $media_total"
    echo "Total de Aprovados (Período Total): $count_total"
    echo

    # Obter a média de nota dos aprovados por ano
    anos=$(awk -F ',' 'NR > 1 {print $5}' "$arquivo_entrada" | sort -u)

    while read -r ano; do
        media_ano=$(awk -F ',' -v ano="$ano" '$5 == ano && $10 == "Aprovado" {sum+=$8; count++} END {if (count > 0) printf "%.2f", sum/count}' "$arquivo_entrada")
        count_ano=$(awk -F ',' -v ano="$ano" '$5 == ano && $10 == "Aprovado" {count++} END {print count}' "$arquivo_entrada")

        echo "Média de Nota dos Aprovados (Ano $ano): $media_ano"
        echo "Total de Aprovados (Ano $ano): $count_ano"
        echo
    done <<< "$anos"
}

# Função para calcular a média de nota dos reprovados por nota
calcular_media_nota_reprovados() {
    arquivo_entrada="$1"

    media_total=0
    count_total=0

    # Obter a média de nota dos reprovados por nota para o período total
    media_total=$(awk -F ',' '$10 == "R-nota" {sum+=$8; count++} END {if (count > 0) printf "%.2f", sum/count}' "$arquivo_entrada")
    count_total=$(awk -F ',' '$10 == "R-nota" {count++} END {print count}' "$arquivo_entrada")

    echo "Média de Nota dos Reprovados por Nota (Período Total): $media_total"
    echo "Total de Reprovados por Nota (Período Total): $count_total"
    echo

    # Obter a média de nota dos reprovados por nota por ano
    anos=$(awk -F ',' 'NR > 1 {print $5}' "$arquivo_entrada" | sort -u)

    while read -r ano; do
        media_ano=$(awk -F ',' -v ano="$ano" '$5 == ano && $10 == "R-nota" {sum+=$8; count++} END {if (count > 0) printf "%.2f", sum/count}' "$arquivo_entrada")
        count_ano=$(awk -F ',' -v ano="$ano" '$5 == ano && $10 == "R-nota" {count++} END {print count}' "$arquivo_entrada")

        echo "Média de Nota dos Reprovados por Nota (Ano $ano): $media_ano"
        echo "Total de Reprovados por Nota (Ano $ano): $count_ano"
        echo
    done <<< "$anos"
}

# Função para calcular a média de frequência dos reprovados por nota
calcular_media_frequencia_reprovados() {
    arquivo_entrada="$1"

    media_total=0
    count_total=0

    # Obter a média de frequência dos reprovados por nota para o período total
    media_total=$(awk -F ',' '$10 == "R-nota" {sum+=$9; count++} END {if (count > 0) printf "%.2f", sum/count}' "$arquivo_entrada")
    count_total=$(awk -F ',' '$10 == "R-nota" {count++} END {print count}' "$arquivo_entrada")

    echo "Média de Frequência dos Reprovados por Nota (Período Total): $media_total"
    echo "Total de Reprovados por Nota (Período Total): $count_total"
    echo

    # Obter a média de frequência dos reprovados por nota por ano
    anos=$(awk -F ',' 'NR > 1 {print $5}' "$arquivo_entrada" | sort -u)

    while read -r ano; do
        media_ano=$(awk -F ',' -v ano="$ano" '$5 == ano && $10 == "R-nota" {sum+=$9; count++} END {if (count > 0) printf "%.2f", sum/count}' "$arquivo_entrada")
        count_ano=$(awk -F ',' -v ano="$ano" '$5 == ano && $10 == "R-nota" {count++} END {print count}' "$arquivo_entrada")

        echo "Média de Frequência dos Reprovados por Nota (Ano $ano): $media_ano"
        echo "Total de Reprovados por Nota (Ano $ano): $count_ano"
        echo
    done <<< "$anos"
}

# Função para calcular a porcentagem de evasões
calcular_porcentagem_evasoes() {
    arquivo_entrada="$1"

    total_alunos=$(awk -F ',' 'NR > 1 {count++} END {print count}' "$arquivo_entrada")
    total_evasoes=$(awk -F ',' '$10 == "Cancelado" {count++} END {print count}' "$arquivo_entrada")

    porcentagem_evasoes=$(awk -v total_evasoes="$total_evasoes" -v total_alunos="$total_alunos" 'BEGIN{ printf "%.2f", (total_evasoes * 100) / total_alunos }')

    echo "Porcentagem de Evasões (Período Total): $porcentagem_evasoes%"
    echo

    # Calcular porcentagem de evasões por ano
    anos=$(awk -F ',' 'NR > 1 {print $5}' "$arquivo_entrada" | sort -u)

    while read -r ano; do
        total_alunos_ano=$(awk -F ',' -v ano="$ano" '$5 == ano {count++} END {print count}' "$arquivo_entrada")
        total_evasoes_ano=$(awk -F ',' -v ano="$ano" '$5 == ano && $10 == "Cancelado" {count++} END {print count}' "$arquivo_entrada")

        porcentagem_evasoes_ano=$(awk -v total_evasoes_ano="$total_evasoes_ano" -v total_alunos_ano="$total_alunos_ano" 'BEGIN{ printf "%.2f", (total_evasoes_ano * 100) / total_alunos_ano }')

        echo "Porcentagem de Evasões (Ano $ano): $porcentagem_evasoes_ano%"
        echo
    done <<< "$anos"
}

calcular_media_nota_aprovados "historico-alg1_SIGA_ANONIMIZADO.csv"

calcular_media_nota_reprovados "historico-alg1_SIGA_ANONIMIZADO.csv"

calcular_media_frequencia_reprovados "historico-alg1_SIGA_ANONIMIZADO.csv"

calcular_porcentagem_evasoes "historico-alg1_SIGA_ANONIMIZADO.csv"

# Função para comparar o rendimento durante os anos de pandemia
comparar_rendimento_pandemia() {
    local arquivo_entrada=$1

    # Anos de pandemia
    local anos_pandemia="2020 2021"

    # Total de alunos nos anos de pandemia
    local total_alunos_pandemia=0

    # Total de aprovados nos anos de pandemia
    local total_aprovados_pandemia=0

    # Total de reprovados nos anos de pandemia
    local total_reprovados_pandemia=0

    # Total de cancelamentos nos anos de pandemia
    local total_cancelamentos_pandemia=0

    # Total de alunos nos anos anteriores à pandemia
    local total_alunos_anteriores=0

    # Total de aprovados nos anos anteriores à pandemia
    local total_aprovados_anteriores=0

    # Total de reprovados nos anos anteriores à pandemia
    local total_reprovados_anteriores=0

    # Total de cancelamentos nos anos anteriores à pandemia
    local total_cancelamentos_anteriores=0

    # Loop pelos anos para calcular os totais
    while IFS= read -r linha; do
        local ano=$(echo "$linha" | cut -d',' -f5)
        local status=$(echo "$linha" | cut -d',' -f10)

        # Verificar se o ano está dentro dos anos de pandemia
        if [[ $anos_pandemia =~ $ano ]]; then
            ((total_alunos_pandemia++))

            if [[ $status == "Aprovado" ]]; then
                ((total_aprovados_pandemia++))
            elif [[ $status == "Reprovado" ]]; then
                ((total_reprovados_pandemia++))
            elif [[ $status == "Cancelado" ]]; then
                ((total_cancelamentos_pandemia++))
            fi
        else
            ((total_alunos_anteriores++))

            if [[ $status == "Aprovado" ]]; then
                ((total_aprovados_anteriores++))
            elif [[ $status == "Reprovado" ]]; then
                ((total_reprovados_anteriores++))
            elif [[ $status == "Cancelado" ]]; then
                ((total_cancelamentos_anteriores++))
            fi
        fi
    done < "$arquivo_entrada"

    # Cálculo dos percentuais
    local percentual_aprovados_pandemia=$(awk -v total_aprovados_pandemia="$total_aprovados_pandemia" -v total_alunos_pandemia="$total_alunos_pandemia" 'BEGIN{ printf "%.2f", (total_aprovados_pandemia * 100) / total_alunos_pandemia }')
    local percentual_reprovados_pandemia=$(awk -v total_reprovados_pandemia="$total_reprovados_pandemia" -v total_alunos_pandemia="$total_alunos_pandemia" 'BEGIN{ printf "%.2f", (total_reprovados_pandemia * 100) / total_alunos_pandemia }')
    local percentual_cancelamentos_pandemia=$(awk -v total_cancelamentos_pandemia="$total_cancelamentos_pandemia" -v total_alunos_pandemia="$total_alunos_pandemia" 'BEGIN{ printf "%.2f", (total_cancelamentos_pandemia * 100) / total_alunos_pandemia }')

    local percentual_aprovados_anteriores=$(awk -v total_aprovados_anteriores="$total_aprovados_anteriores" -v total_alunos_anteriores="$total_alunos_anteriores" 'BEGIN{ printf "%.2f", (total_aprovados_anteriores * 100) / total_alunos_anteriores }')
    local percentual_reprovados_anteriores=$(awk -v total_reprovados_anteriores="$total_reprovados_anteriores" -v total_alunos_anteriores="$total_alunos_anteriores" 'BEGIN{ printf "%.2f", (total_reprovados_anteriores * 100) / total_alunos_anteriores }')
    local percentual_cancelamentos_anteriores=$(awk -v total_cancelamentos_anteriores="$total_cancelamentos_anteriores" -v total_alunos_anteriores="$total_alunos_anteriores" 'BEGIN{ printf "%.2f", (total_cancelamentos_anteriores * 100) / total_alunos_anteriores }')

    # Exibir os resultados
    echo "Comparação de rendimento durante a pandemia:"
    echo "------------------------------------------"
    echo "Anos de pandemia: 2020 e 2021"
    echo "------------------------------------------"
    echo "Percentual de aprovados: $percentual_aprovados_pandemia%"
    echo "Percentual de reprovados: $percentual_reprovados_pandemia%"
    echo "Percentual de cancelamentos: $percentual_cancelamentos_pandemia%"
    echo ""
    echo "Anos anteriores à pandemia:"
    echo "------------------------------------------"
    echo "Percentual de aprovados: $percentual_aprovados_anteriores%"
    echo "Percentual de reprovados: $percentual_reprovados_anteriores%"
    echo "Percentual de cancelamentos: $percentual_cancelamentos_anteriores%"
}

# Chamar a função passando o nome do arquivo como argumento
comparar_rendimento_pandemia "historico-alg1_SIGA_ANONIMIZADO.csv"

