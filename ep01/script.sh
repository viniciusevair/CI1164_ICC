#!/bin/bash

################################################################
# Script feito por Luiz Henrique Murback Wiedmer GRR20221234 e #
#   Vinicius Evair da Silva GRR20221251 para a disciplina de   #
#         Introdução à Computação Científica (CI1164)          #
################################################################
#
# Este script executa o programa 'perfSL' com diversos sistemas lineares como
# entrada, e utiliza o likwid-perfctr para medir e filtrar as taxas de
# desempenho em MFLOP/s (megaflops por segundo). Os resultados de cada sistema
# linear são armazenados em arquivos de saída separados.


# Função que filtra a saída do likwid para extraír apenas MFLOP/s
parse_output () {
    PROG_OUTPUT="$1"        # Saída do programa 'perfSL'.
    FILTERED_OUTPUT="$2"    # Arquivo de saída final.

    # Função que reorganiza a saída do programa e a saída do likwid de cada
    # método. Também filtra a saída do likwid, guardando apenas o MFLOP/s
    filter_results () {
        PATTERN="$1"
        LABEL="$2"

        cat ${PROG_OUTPUT} | grep "${PATTERN}" -A3 >> ${FILTERED_OUTPUT}
        awk -v label="${LABEL}" '$0 ~ "^" label {region=$0; r=1} /DP MFLOP\/s/{if (r) { printf "%s\n%s\n", region, $0; r=0 }}' ${PROG_OUTPUT} >> ${FILTERED_OUTPUT}
        echo " " >> ${FILTERED_OUTPUT}
    }

    # Limpa o arquivo de saída caso este já exista.
    if [ -f "${FILTERED_OUTPUT}" ]; then
        rm -f "${FILTERED_OUTPUT}"
    fi
    filter_results "EG clássico" "Region eg_classico"
    filter_results "GS clássico" "Region gs_classico"
    filter_results "EG 3-diagonal" "Region eg_trid"
    filter_results "GS 3-diagonal" "Region gs_trid"

    sed -i 's/| *DP *\([^ ]*\) *| *\([^ ]*\) *|/\1 \2/' ${FILTERED_OUTPUT}
}

# Cria o diretório para guardar as saídas caso este ainda não exista.
if [ ! -d "outputs" ]; then
    mkdir "outputs"
fi

# Cria um arquivo temporário que será utilizado como saída do programa para ser
# filtrado pela função acima.
TEMP_FILE=$(mktemp -p .)

# Itera por todos os arquivos dentro do diretório de entradas.
# Cada arquivo contém um dos exemplos do arquivo sistemas.dat.
for INPUT_FILE in inputs/input*; do
    # Guarda o número do arquivo de entrada.
    ID=$(basename "$INPUT_FILE" | awk -F 'input' '{print $2}')
    # Cria o arquivo de saída.
    OUTPUT_FILE="outputs/output$ID"

    # Executa o programa utilizando o likwid.
    likwid-perfctr -C 3 -g FLOPS_DP -m ./perfSL < "$INPUT_FILE" > $TEMP_FILE
    parse_output "$TEMP_FILE" "$OUTPUT_FILE"
done

# Remove o arquivo auxiliar temporário.
rm $TEMP_FILE
