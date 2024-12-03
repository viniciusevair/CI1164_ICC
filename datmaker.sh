#!/bin/bash

RAW_DATA="results"

declare -A MULT_MAT_VET
declare -A MULT_MAT_MAT

while IFS= read -r LINE; do
    SZ=$(echo $LINE | awk '{print $2}')
    METRIC=$(echo $LINE | awk '{print $3}')

    MULT_MAT_VET[$METRIC]="${METRIC}_matVet.dat"
    MULT_MAT_MAT[$METRIC]="${METRIC}_matMat.dat"

    if [[ $METRIC != "FLOPS_DP" ]]; then
        if [[ ! -f "${MULT_MAT_VET[$METRIC]}" ]]; then
            echo "# Marcador \"MultMatVet\" para $METRIC" > "${MULT_MAT_VET[$METRIC]}"
            echo "# n sem_otimizacao com_otimizacao" >> "${MULT_MAT_VET[$METRIC]}"
        fi
        if [[ ! -f "${MULT_MAT_MAT[$METRIC]}" ]]; then
            echo "# Marcador \"MultMatMat\" para $METRIC" > "${MULT_MAT_MAT[$METRIC]}"
            echo "# n sem_otimizacao com_otimizacao" >> "${MULT_MAT_MAT[$METRIC]}"
        fi

        read -r MAT_VET_NORMAL
        read -r MAT_VET_OTIMIZADO
        read -r MAT_MAT_NORMAL
        read -r MAT_MAT_OTIMIZADO

        echo "$SZ $MAT_VET_NORMAL $MAT_VET_OTIMIZADO" >> "${MULT_MAT_VET[$METRIC]}"
        echo "$SZ $MAT_MAT_NORMAL $MAT_MAT_OTIMIZADO" >> "${MULT_MAT_MAT[$METRIC]}"
    else
        if [[ ! -f "${MULT_MAT_VET[$METRIC]}" ]]; then
            echo "# Marcador \"MultMatVet\" para $METRIC" > "${MULT_MAT_VET[$METRIC]}"
            echo "# n sem_otimizacao_dp com_otimizacao_dp sem_otimizacao_avx com_otimizacao_avx" >> "${MULT_MAT_VET[$METRIC]}"
        fi
        if [[ ! -f "${MULT_MAT_MAT[$METRIC]}" ]]; then
            echo "# Marcador \"MultMatMat\" para $METRIC" > "${MULT_MAT_MAT[$METRIC]}"
            echo "# n sem_otimizacao_dp com_otimizacao_dp sem_otimizacao_avx com_otimizacao_avx" >> "${MULT_MAT_MAT[$METRIC]}"
        fi

        read -r MAT_VET_NORMAL_DP
        read -r MAT_VET_NORMAL_AVX
        read -r MAT_VET_OTIMIZADO_DP
        read -r MAT_VET_OTIMIZADO_AVX
        read -r MAT_MAT_NORMAL_DP
        read -r MAT_MAT_NORMAL_AVX
        read -r MAT_MAT_OTIMIZADO_DP
        read -r MAT_MAT_OTIMIZADO_AVX

        echo "$SZ $MAT_VET_NORMAL_DP $MAT_VET_OTIMIZADO_DP $MAT_VET_NORMAL_AVX $MAT_VET_OTIMIZADO_AVX" >> "${MULT_MAT_VET[$METRIC]}"
        echo "$SZ $MAT_MAT_NORMAL_DP $MAT_MAT_OTIMIZADO_DP $MAT_MAT_NORMAL_AVX $MAT_MAT_OTIMIZADO_AVX" >> "${MULT_MAT_MAT[$METRIC]}"
    fi

done < "$RAW_DATA"
