#!/bin/bash

parse_output () {
    PROG_OUTPUT="$1"
    FILTERED_OUTPUT="$2"

    filter_results () {
        PATTERN="$1"
        LABEL="$2"

        cat ${PROG_OUTPUT} | grep "${PATTERN}" -A3 >> ${FILTERED_OUTPUT}
        awk -v label="${LABEL}" '$0 ~ "^" label {region=$0; r=1} /DP MFLOP\/s/{if (r) { printf "%s\n%s\n", region, $0; r=0 }}' ${PROG_OUTPUT} >> ${FILTERED_OUTPUT}
        echo " " >> ${FILTERED_OUTPUT}
    }

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

# Itera por todos os arquivos dentro do diretório de entradas.
# Cada arquivo contém um dos exemplos do arquivo sistemas.dat.
for INPUT_FILE in inputs/input*; do
    # Guarda o número do arquivo de entrada.
    ID=$(basename "$INPUT_FILE" | awk -F 'input' '{print $2}')
    # Cria o arquivo de saída.
    OUTPUT_FILE="outputs/output$ID"

    # Executa o programa utilizando o likwid.
    likwid-perfctr -C 3 -g FLOPS_DP -m ./perfSL < "$INPUT_FILE" | parse_output - "$OUTPUT_FILE"
done
