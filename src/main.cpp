#include <iostream>
#include <vector>
#include <chrono> 
#include <iomanip>

// Nossas estruturas
#include "SensorData.h"
#include "LinkedList.h"
#include "RBTree.h"
#include "SensorHeap.h"
#include "DHTSim.h"

using namespace std;
using namespace std::chrono;

// Estrutura para guardar os resultados da tabela
struct Resultado {
    int N;
    long long tempoListaIns, tempoArvoreIns, tempoHeapIns;
    long long tempoListaBusca, tempoArvoreBusca, tempoHeapBusca;
};

vector<Resultado> resultados;

void testarDesempenho(int quantidade) {
    cout << "\n========================================\n";
    cout << "   TESTE COM N = " << quantidade << " LEITURAS\n";
    cout << "========================================\n";

    LinkedList lista;
    RBTree arvore;
    SensorHeap heap;
    vector<SensorData> dadosTeste;

    // Gerar dados aleatórios
    for(int i=0; i<quantidade; i++) dadosTeste.push_back(DHTSim::ler());

    // --- 1. TESTE DE INSERÇÃO (MUDADO PARA NANOSSEGUNDOS - ns) ---
    cout << "[Status] Inserindo dados..." << endl;

    // Lista (Insertion Sort)
    auto inicio = high_resolution_clock::now();
    for (const auto& d : dadosTeste) lista.insertOrdered(d);
    auto fim = high_resolution_clock::now();
    long long tLista = duration_cast<nanoseconds>(fim - inicio).count();

    // Árvore Rubro-Negra
    inicio = high_resolution_clock::now();
    for (const auto& d : dadosTeste) arvore.insert(d);
    fim = high_resolution_clock::now();
    long long tArvore = duration_cast<nanoseconds>(fim - inicio).count();

    // Heap
    inicio = high_resolution_clock::now();
    for (const auto& d : dadosTeste) heap.insert(d);
    fim = high_resolution_clock::now();
    long long tHeap = duration_cast<nanoseconds>(fim - inicio).count();

    // **TRUQUE ANTI-OTIMIZAÇÃO**: Imprimir tamanhos obriga o código a rodar
    cout << "   -> Dados carregados: A:" << arvore.getSize() << " | H:" << heap.getSize() << endl;


    // --- 2. TESTE DE BUSCA MÁXIMA (Nanossegundos) ---
    cout << "[Status] Buscando maior temperatura..." << endl;
    
    volatile float dummy = 0; // Variável 'volátil' obriga leitura real da memória

    // Lista
    inicio = high_resolution_clock::now();
    dummy += lista.getMax().temp;
    fim = high_resolution_clock::now();
    long long tListaB = duration_cast<nanoseconds>(fim - inicio).count();

    // Árvore
    inicio = high_resolution_clock::now();
    dummy += arvore.getMax().temp;
    fim = high_resolution_clock::now();
    long long tArvoreB = duration_cast<nanoseconds>(fim - inicio).count();

    // Heap
    inicio = high_resolution_clock::now();
    dummy += heap.peekMax().temp;
    fim = high_resolution_clock::now();
    long long tHeapB = duration_cast<nanoseconds>(fim - inicio).count();

    // --- COMPARATIVO IMEDIATO NA TELA ---
    // Mostrando em 'us' (micros) na tela para facilitar leitura rápida, mas na tabela vai 'ns'
    cout << "\n--- RESULTADO DA RODADA (N=" << quantidade << ") ---" << endl;
    cout << "INSERCAO (Menor eh melhor):" << endl;
    cout << "  > Lista:  " << tLista << " ns " << (tLista > 10000000 ? "(LENTO)" : "") << endl;
    cout << "  > Arvore: " << tArvore << " ns" << endl;
    cout << "  > Heap:   " << tHeap << " ns" << endl;
    
    cout << "BUSCA MAX (Menor eh melhor):" << endl;
    cout << "  > Lista:  " << tListaB << " ns" << endl;
    cout << "  > Arvore: " << tArvoreB << " ns" << endl;
    cout << "  > Heap:   " << tHeapB << " ns (VENCEDORA)" << endl;

    // Salva para a tabela final (Tudo em NANOSSEGUNDOS agora)
    resultados.push_back({quantidade, tLista, tArvore, tHeap, tListaB, tArvoreB, tHeapB});
    (void)dummy; // Silencia warning
}

int main() {
    srand(time(NULL));

    cout << "=== Trabalho Final: Estruturas de Dados ===" << endl;
    
    // Bateria de Testes
    testarDesempenho(100);
    testarDesempenho(1000);
    testarDesempenho(10000);
    testarDesempenho(20000);
    
    // Se demorar muito, pode comentar a linha abaixo
    testarDesempenho(50000); 

    // Tabela Final para Excel (Atualizada para ns)
    cout << "\n\n=== TABELA FINAL (Copie para o Excel) ===\n";
    cout << "N\tLista_Ins(ns)\tArvore_Ins(ns)\tHeap_Ins(ns)\tLista_Busca(ns)\tArvore_Busca(ns)\tHeap_Busca(ns)\n";
    
    for(const auto& r : resultados) {
        cout << r.N << "\t" 
             << r.tempoListaIns << "\t" << r.tempoArvoreIns << "\t" << r.tempoHeapIns << "\t"
             << r.tempoListaBusca << "\t" << r.tempoArvoreBusca << "\t" << r.tempoHeapBusca << "\n";
    }

    return 0;
}