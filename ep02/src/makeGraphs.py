from matplotlib import pyplot as plt
import csv
import os

# Salva o perfData em um csv separado por ","
def salva_perfData(perfData):
    with open('perfData.csv', mode='a', newline=None) as perfCsv:
        writer = csv.writer(perfCsv, delimiter=',')
        writer.writerows(perfData)


def montaPerfDict(perfData) -> dict[str, list[float]]:
    perfDict = {}
    chaves = ['tamanhos', 'tempoVM', 'tempoMM', 
              'DP_FLOPS_VM', 'AVX_FLOPS_VM', 'DP_FLOPS_MM', 
              'AVX_FLOPS_MM', 'L3_bw_VM', 'L3_bw_MM', 'L2_miss_VM',
              'L2_miss_MM', 'energy_VM', 'energy_MM']
    for idx, chave in enumerate(chaves):
        perfDict[chave] = perfData[idx]
    
    return perfDict


# Monta uma estrutura de performaces de acordo com cada tamanho de matriz.
# O formato de estrutura retornada fica da seguinte forma:
#   chaves = ['tamanhos', 'tempoVM', 'tempoMM', 
#              'DP_FLOPS_VM', 'AVX_FLOPS_VM', 'DP_FLOPS_MM', 
#              'AVX_FLOPS_MM', 'L3_bw_VM', 'L3_bw_MM', 'L2_miss_VM',
#              'L2_miss_MM', 'energy_VM', 'energy_MM']
#
def montaPerfData(arq) -> dict[str, list[float]]:
    perfData = [list() for _ in range(13)]
    with open(arq+'_tempos.txt', 'r', newline=None) as file:
        for idx, row in enumerate(file):
            perfData[idx % 3].append(float(row))
    
    perfData[1] = [x/1000 for x in perfData[1]]
    perfData[2] = [x/1000 for x in perfData[2]]

    with open(arq+'_metrics.csv', 'r') as file:
        file_csv = csv.reader(file, delimiter=',')
        for i, row in enumerate(file_csv):
            perfData[i%10 + 3].append(float(row[1]))

    return montaPerfDict(perfData)


def visualizarGraficos(title, ylabel):
    plt.title(title, fontsize=14)
    plt.xlabel('Tamanho matriz em log2()', fontsize=12)
    plt.ylabel(ylabel, fontsize=12)
    plt.xscale('log', base=2)
    # plt.yscale('log', base=2)
    plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
    plt.subplots_adjust(right=0.7)
    plt.savefig('graphs/'+title.replace('/', '').replace(' ', '_'), bbox_inches='tight')
    # plt.show()
    plt.close()
    # plt.yticks(y_ticks)


# PerfG = grupo de performace.
def makePlotPerfData(perfG, ylabel, title=None):
    if title is None:
        title = perfG
    plt.plot(perfData['tamanhos'], perfData[perfG+'_VM'], label=title+' vetMat')
    plt.plot(perfData['tamanhos'], perfDataOTM[perfG+'_VM'], label=title+' vetMat OTM')
    plt.plot(perfData['tamanhos'], perfData[perfG+'_MM'], label=title+' matMat')
    plt.plot(perfData['tamanhos'], perfDataOTM[perfG+'_MM'], label=title+' matMat OTM')
    visualizarGraficos(title, ylabel)


perfData = montaPerfData('metricas/matmult')
perfDataOTM = montaPerfData('metricas/matmultOTM')

os.makedirs('graphs', exist_ok=True)

plt.plot(perfData['tamanhos'], perfData['tempoMM'], label='Tempo matMat')
plt.plot(perfData['tamanhos'], perfDataOTM['tempoMM'], label='Tempo matMat OTM')
visualizarGraficos('Tempo de execução MM', 'Segundos')

plt.plot(perfData['tamanhos'], perfData['tempoVM'], label='Tempo vetMat')
plt.plot(perfData['tamanhos'], perfDataOTM['tempoVM'], label='Tempo vetMat OTM')
visualizarGraficos('Tempo de execução VM', 'Segundos')

makePlotPerfData('DP_FLOPS', 'MFLOPS/s')
makePlotPerfData('AVX_FLOPS', 'MFLOPS/s')
makePlotPerfData('L3_bw', 'MBytes/s', 'L3 bandwidth')
makePlotPerfData('L2_miss', 'Taxa', 'L2 miss ratio')
makePlotPerfData('energy', 'Joules')
