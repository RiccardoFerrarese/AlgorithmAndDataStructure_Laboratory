# Algorithm and DataStructure Laboratory Exam

This is my work for the laboratory of asd. 
It consists in the implementation of algorithms and the related analysis of complexity, theoretical and practical.

There are two parts with the following assignments: 

## K'th smaller element in unsorted array 

La prima parte del progetto richiede l'implementazione e l'analisi dei tempi medi di esecuzione di tre algoritmi di selezione (calcolo del k-esimo elemento più piccolo in un vettore non ordinato di interi). I tre algoritmi di selezione, denominati rispettivamente "quick select", "heap select" e "median-of-medians select", dovranno avere le seguenti caratteristiche:

### Quick select

Si tratta di una variante dell'algoritmo di ordinamento "quick sort", in cui ogni chiamata ricorsiva su un intervallo [i,j] del vettore fornito in input termina in tempo costante ogniqualvolta il parametro k non sia contenuto nell'intervallo [i,j]. L'algoritmo deve avere complessità temporale asintotica Θ(n2) nel caso pessimo e O(n) nel caso medio, dove n è il numero di elementi del vettore.

### Heap select

Questo algoritmo di selezione utilizza due min-heap, denominate H1 e H2. La prima heap H1 é costruita a partire dal vettore fornito in input in tempo lineare e non viene modificata. La seconda heap H2 contiene inizialmente un solo nodo, corrispondente alla radice di H1. All'i-esima iterazione, per i che va da 1 a k−1, l'algoritmo estrae la radice di H2, che corrisponde a un nodo xi in H1, e reinserisce in H2 i nodi successori (figli sinistro e destro) di xi nella heap H1. Dopo k−1 iterazioni, la radice di H2 corrisponderà al k-esimo elemento più piccolo del vettore fornito in input.
L'algoritmo descritto ha complessità temporale O(n+klogk) sia nel caso pessimo che in quello medio. Per k sufficientemente piccolo, quindi, l'algoritmo "heap select" sarà preferibile, almeno nel caso pessimo, all'algoritmo "quick select". È possibile implementare una variante che utilizzi opportunamente min-heap o max-heap, a seconda del valore di k.

### Median-of-medians select

L'algoritmo è basato sulla suddivisione del vettore fornito in input in blocchi di dimensione limitata e sul calcolo della mediana delle mediane. Più precisamente, l'algoritmo esegue le seguenti operazioni:
- divisione dell'array in blocchi di 5 elementi, escluso eventualmente l'ultimo blocco che potrà contenere meno di 5 elementi,
- ordinamento e calcolo della mediana di ciascun blocco,
- calcolo della mediana M delle mediate dei blocchi, attraverso chiamata ricorsiva allo stesso algoritmo
- partizionamento dell'intero array attorno alla mediana M, attraverso una variante della procedura "partition" dell'algoritmo "quick sort"
- chiamata ricorsiva nella parte di array che sta a sinistra o a destra della mediana M, in funzione del valore k fornito in input.
Il modo più semplice per implementare quest'algoritmo consiste nell'allocare, ad ogni chiamata ricorsiva, un nuovo vettore per memorizzare le mediane dei blocchi. Esiste tuttavia un approccio più efficiente e "in place" che riutilizza lo spazio allocato per il vettore originariamente fornito in input. La valutazione del progetto terrà conto della variante implementata (quella "in place", essendo più complicata ma anche più efficiente, sarà valutata con un punteggio più alto).
Indipendentemente dalla variante implementata, nel caso pessimo l'algoritmo dovrà avere complessità, sia temporale che spaziale, pari a Θ(n).

## Differet types of tree structures

### Alberi binari di ricerca semplici

Si ricorda che un albero binario di ricerca semplice deve soddisfare la seguente proprietà: per ogni nodo x che non sia una foglia e per ogni nodo y nel sotto-albero sinistro (rispettivamente, destro) di x, la chiave associata a x è strettamente maggiore (rispettivamente, minore) della chiave associata a y. Si faccia riferimento all'Esercizio 16 per la descrizione delle operazioni di inserimento e ricerca di un nodo.

### Alberi binari di ricerca di tipo AVL

Si ricorda che un albero binario di ricerca di tipo AVL, oltre a soddisfare la proprietà di un albero di ricerca semplice, deve soddisfare anche la seguente proprietà: per ogni nodo x, le altezze dei sotto-alberi di sinistra e di destra nel nodo x differiscono al più di 1. Si faccia riferimento all'Esercizio 18 per la descrizione delle operazioni di ribilanciamento in seguito a inserimento di un nodo.

### Alberi binari di ricerca di tipo Red-Black

Si ricorda che in un albero binario di ricerca di tipo Red-Black, ogni nodo ha associato un colore associato, che può essere rosso o nero. L'altezza nera del sottoalbero radicato in un nodo x è definita come il massimo numero di nodi neri lungo un possibile cammino da x a una foglia. Un albero binario di ricerca Rosso-Nero deve soddisfare anche la seguente proprietà: per ogni nodo x, le altezze nere dei sotto-alberi di sinistra e di destra nel nodo x coincidono. 


### Complessità media ammortizzata

Si richiede una stima dei tempi medi e ammortizzati per l'esecuzione di n operazioni di inserimento e ricerca nei tre tipi di alberi binari di ricerca sopra descritti. Per tale stima si potrà procedere nel modo seguente. Al variare del parametro n, ad esempio, fra 1000 e 1000000, si eseguono n volte le seguenti operazioni su un albero di ricerca inizialmente vuoto: si genera in modo pseudo-casuale un valore intero k, si ricerca un nodo con chiave k nell'albero e, qualora il nodo non esistesse, si inserisce un nuovo nodo con chiave k nell'albero. Si noti che al termine di tale procedura saranno state eseguite esattamente n operazioni di ricerca e m operazioni di inserimento, per un opportuno m≤n (l'albero binario di ricerca conterrà quindi al più n nodi). Nell'ipotesi che i numeri generati in modo pseudo-casuale varino in un dominio sufficientemente grande, il valore di m sarà probabilmente simile a quello di n e potrà quindi essere sostituito con n.


## Execute analysis
Each dir have a *main* program, with it you can run the analysis
